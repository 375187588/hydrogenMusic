#include "multimedia.h"


#include <QDebug>

#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#define SDL_AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIO_FRAME_SIZE 192000

//this value control auio play and pause
bool isPause;
int allSongSchedule = 0;
int currentSongSchedule = 0;
float scheduleRate = 0.0;

typedef struct AudioParams {
    int freq;
    int channels;
    int64_t channel_layout;
    enum AVSampleFormat fmt;
    int frame_size;
    int bytes_per_sec;
} AudioParams;

int sample_rate, nb_channels;
int64_t channel_layout;
AudioParams audio_hw_params_tgt;
AudioParams audio_hw_params_src;
AVFormatContext *pFormatCtx = NULL;
int audioStream = 0;

int resample(AVFrame * af, uint8_t * audio_buf, int * audio_buf_size);

struct SwrContext * swr_ctx = NULL;


int resample(AVFrame * af, uint8_t * audio_buf, int * audio_buf_size)
{
    int data_size = 0;
    int resampled_data_size = 0;
    int64_t dec_channel_layout;
    data_size = av_samples_get_buffer_size(NULL,
                                           av_frame_get_channels(af),
                                           af->nb_samples,
                                           (AVSampleFormat)af->format,
                                           1);

    dec_channel_layout =
            (af->channel_layout && av_frame_get_channels(af) == av_get_channel_layout_nb_channels(af->channel_layout)) ?
                af->channel_layout : av_get_default_channel_layout(av_frame_get_channels(af));
    if( 	af->format 		 	!= audio_hw_params_src.fmt 				||
            af->sample_rate 	!= audio_hw_params_src.freq 	 		||
            dec_channel_layout 	!= audio_hw_params_src.channel_layout 	||
            !swr_ctx) {
        swr_free(&swr_ctx);
        swr_ctx = swr_alloc_set_opts(NULL,
                                     audio_hw_params_tgt.channel_layout, audio_hw_params_tgt.fmt, audio_hw_params_tgt.freq,
                                     dec_channel_layout, (AVSampleFormat)af->format, af->sample_rate,
                                     0, NULL);
        if (!swr_ctx || swr_init(swr_ctx) < 0) {
            av_log(NULL, AV_LOG_ERROR,
                   "Cannot create sample rate converter for conversion of %d Hz %s %d channels to %d Hz %s %d channels!\n",
                   af->sample_rate, av_get_sample_fmt_name((AVSampleFormat)af->format), av_frame_get_channels(af),
                   audio_hw_params_tgt.freq, av_get_sample_fmt_name(audio_hw_params_tgt.fmt), audio_hw_params_tgt.channels);
            swr_free(&swr_ctx);
            return -1;
        }
        printf("swr_init\n");
        audio_hw_params_src.channels = av_frame_get_channels(af);
        audio_hw_params_src.fmt = (AVSampleFormat)af->format;
        audio_hw_params_src.freq = af->sample_rate;
    }

    if (swr_ctx) {
        const uint8_t **in = (const uint8_t **)af->extended_data;
        uint8_t **out = &audio_buf;
        int out_count = (int64_t)af->nb_samples * audio_hw_params_tgt.freq / af->sample_rate + 256;
        int out_size  = av_samples_get_buffer_size(NULL, audio_hw_params_tgt.channels, out_count, audio_hw_params_tgt.fmt, 0);
        int len2;
        if (out_size < 0) {
            av_log(NULL, AV_LOG_ERROR, "av_samples_get_buffer_size() failed\n");
            return -1;
        }
        av_fast_malloc(&audio_buf, (unsigned int *)audio_buf_size, out_size);
        if (!audio_buf)
            return AVERROR(ENOMEM);
        len2 = swr_convert(swr_ctx, out, out_count, in, af->nb_samples);
        if (len2 < 0) {
            av_log(NULL, AV_LOG_ERROR, "swr_convert() failed\n");
            return -1;
        }
        if (len2 == out_count) {
            av_log(NULL, AV_LOG_WARNING, "audio buffer is probably too small\n");
            if (swr_init(swr_ctx) < 0)
                swr_free(&swr_ctx);
        }
        resampled_data_size = len2 * audio_hw_params_tgt.channels * av_get_bytes_per_sample(audio_hw_params_tgt.fmt);
    } else {
        audio_buf = af->data[0];
        resampled_data_size = data_size;
    }

    return resampled_data_size;
}

static void sigterm_handler(int sig)
{
    exit(123);
}

typedef struct PacketQueue {
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;

PacketQueue audioq;

int quit = 0;

void packet_queue_init(PacketQueue *q) {
    memset(q, 0, sizeof(PacketQueue));
    q->mutex = SDL_CreateMutex();
    q->cond = SDL_CreateCond();
}
int packet_queue_put(PacketQueue *q, AVPacket *pkt) {

    AVPacketList *pkt1;
    if(av_dup_packet(pkt) < 0) {
        return -1;
    }
    pkt1 = (AVPacketList *)av_malloc(sizeof(AVPacketList));
    if (!pkt1)
        return -1;
    pkt1->pkt = *pkt;
    pkt1->next = NULL;


    SDL_LockMutex(q->mutex);

    if (!q->last_pkt)
        q->first_pkt = pkt1;
    else
        q->last_pkt->next = pkt1;
    q->last_pkt = pkt1;
    q->nb_packets++;
    q->size += pkt1->pkt.size;
    SDL_CondSignal(q->cond);

    SDL_UnlockMutex(q->mutex);
    return 0;
}
static int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block)
{
    AVPacketList *pkt1;
    int ret;

    SDL_LockMutex(q->mutex);

    for(;;) {

        if(quit) {
            ret = -1;
            break;
        }

        pkt1 = q->first_pkt;
        if (pkt1) {
            q->first_pkt = pkt1->next;
            if (!q->first_pkt)
                q->last_pkt = NULL;
            q->nb_packets--;
            q->size -= pkt1->pkt.size;
            *pkt = pkt1->pkt;
            av_free(pkt1);
            ret = 1;
            break;
        } else if (!block) {
            ret = 0;
            break;
        } else {
            SDL_CondWait(q->cond, q->mutex);
        }
    }
    SDL_UnlockMutex(q->mutex);
    return ret;
}


AVFrame frame;
int audio_decode_frame(AVCodecContext *aCodecCtx, uint8_t *audio_buf, int buf_size) {

    static AVPacket pkt;
    static uint8_t *audio_pkt_data = NULL;
    static int audio_pkt_size = 0;

    int hh = buf_size;
    int len1, data_size = 0;

    for(;;) {
        while(audio_pkt_size > 0) {

            if(isPause)
            {
                SDL_Delay(10);
                continue;
            }

            int got_frame = 0;
            len1 = avcodec_decode_audio4(aCodecCtx, &frame, &got_frame, &pkt);
            currentSongSchedule = frame.pts * av_q2d(pFormatCtx->streams[audioStream]->time_base) * 1000;
            if(len1 < 0) {
                /* if error, skip frame */
                audio_pkt_size = 0;
                break;
            }
            audio_pkt_data += len1;
            audio_pkt_size -= len1;
            data_size = 0;
            if(got_frame) {
                data_size = resample(&frame, audio_buf, &buf_size);
                // data_size = av_samples_get_buffer_size(NULL,
                // 		aCodecCtx->channels,
                // 		frame.nb_samples,
                // 		aCodecCtx->sample_fmt,
                // 		1);
                assert(data_size <= buf_size);
                // memcpy(audio_buf, frame.data[0], data_size);
            }
            if(data_size <= 0) {
                /* No data yet, get more frames */
                continue;
            }
            // memcpy(audio_buf, frame.data[0], data_size);

            /* We have data, return it and come back for more later */
            return data_size;
        }
        if(pkt.data)
            av_free_packet(&pkt);

        if(quit) {
            return -1;
        }
        if(isPause)
        {
            SDL_Delay(10);
            continue;
        }

        if(packet_queue_get(&audioq, &pkt, 1) < 0) {
            return -1;
        }
        audio_pkt_data = pkt.data;
        audio_pkt_size = pkt.size;
    }
}

void audio_callback(void *userdata, Uint8 *stream, int len) {

    AVCodecContext *aCodecCtx = (AVCodecContext *)userdata;
    int len1, audio_size;

    static uint8_t audio_buf[(MAX_AUDIO_FRAME_SIZE * 3) / 2];
    static unsigned int audio_buf_size = 0;
    static unsigned int audio_buf_index = 0;

    while(len > 0) {
        if(audio_buf_index >= audio_buf_size) {
            /* We have already sent all our data; get more */
            audio_size = audio_decode_frame(aCodecCtx, audio_buf, sizeof(audio_buf));
            if(audio_size < 0) {
                /* If error, output silence */
                audio_buf_size = 1024; // arbitrary?
                memset(audio_buf, 0, audio_buf_size);
            } else {
                audio_buf_size = audio_size;
            }
            audio_buf_index = 0;
        }
        len1 = audio_buf_size - audio_buf_index;
        if(len1 > len)
        {
            len1 = len;
        }
        memcpy(stream, (uint8_t *)audio_buf + audio_buf_index, len1);
        len -= len1;
        stream += len1;
        audio_buf_index += len1;
    }
}

int play_mp3(QString url2)
{
    printf("now play_mp3 begin\n");
    if(isPause)
    {
        printf("in the play_mp3 ,isPause is true\n");
    }else{
        printf("in the play_mp3, isPause is false\n");
    }
    std::string url3 = url2.toStdString();
    int length = url3.size();
    char *url = (char *)malloc((length + 1)*sizeof(char));

    url3.copy(url, length, 0);

    //    AVFormatContext *pFormatCtx = NULL;
    int             i;
    AVPacket        packet;

    AVCodecContext  *aCodecCtxOrig = NULL;
    AVCodecContext  *aCodecCtx = NULL;
    AVCodec         *aCodec = NULL;

    SDL_Event       event;
    SDL_AudioSpec   wanted_spec, spec;


    signal(SIGINT , sigterm_handler); /* Interrupt (ANSI).    */
    signal(SIGTERM, sigterm_handler); /* Termination (ANSI).  */


    // Register all formats and codecs
    av_register_all();

    if(SDL_Init(SDL_INIT_AUDIO)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }

    // Open video file
    if(avformat_open_input(&pFormatCtx, url, NULL, NULL)!=0)
        return -1; // Couldn't open file

    // Retrieve stream information
    if(avformat_find_stream_info(pFormatCtx, NULL)<0)
        return -1; // Couldn't find stream information

    // Dump information about file onto standard error
    //    av_dump_format(pFormatCtx, 0, url, 0);

    // Find the first video stream
    audioStream=-1;
    for(i=0; i<pFormatCtx->nb_streams; i++) {
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO &&
                audioStream < 0) {
            audioStream=i;
        }
    }
    // if(videoStream==-1)
    //   return -1; // Didn't find a video stream
    if(audioStream==-1)
        return -1;

    aCodecCtxOrig=pFormatCtx->streams[audioStream]->codec;
    aCodec = avcodec_find_decoder(aCodecCtxOrig->codec_id);
    if(!aCodec) {
        fprintf(stderr, "Unsupported codec!\n");
        return -1;
    }

    // Copy context
    aCodecCtx = avcodec_alloc_context3(aCodec);
    if(avcodec_copy_context(aCodecCtx, aCodecCtxOrig) != 0) {
        fprintf(stderr, "Couldn't copy codec context");
        return -1; // Error copying codec context
    }

    avcodec_open2(aCodecCtx, aCodec, NULL);

    sample_rate = aCodecCtx->sample_rate;
    nb_channels = aCodecCtx->channels;
    channel_layout = aCodecCtx->channel_layout;

    //    printf("channel_layout=%" PRId64 "\n", channel_layout);
    //    printf("nb_channels=%d\n", nb_channels);
    //    printf("freq=%d\n", sample_rate);

    if (!channel_layout || nb_channels != av_get_channel_layout_nb_channels(channel_layout)) {
        channel_layout = av_get_default_channel_layout(nb_channels);
        channel_layout &= ~AV_CH_LAYOUT_STEREO_DOWNMIX;
        printf("correction\n");
    }

    // Set audio settings from codec info
    wanted_spec.freq = sample_rate;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.channels = nb_channels;
    wanted_spec.silence = 0;
    wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
    wanted_spec.callback = audio_callback;
    wanted_spec.userdata = aCodecCtx;

    if(SDL_OpenAudio(&wanted_spec, &spec) < 0) {
        fprintf(stderr, "SDL_OpenAudio: %s\n", SDL_GetError());
        return -1;
    }
    printf("freq: %d\tchannels: %d\n", spec.freq, spec.channels);

    audio_hw_params_tgt.fmt = AV_SAMPLE_FMT_S16;
    audio_hw_params_tgt.freq = spec.freq;
    audio_hw_params_tgt.channel_layout = channel_layout;
    audio_hw_params_tgt.channels =  spec.channels;

    audio_hw_params_tgt.frame_size = av_samples_get_buffer_size(NULL, audio_hw_params_tgt.channels, 1, audio_hw_params_tgt.fmt, 1);

    audio_hw_params_tgt.bytes_per_sec = av_samples_get_buffer_size(NULL, audio_hw_params_tgt.channels, audio_hw_params_tgt.freq, audio_hw_params_tgt.fmt, 1);

    if (audio_hw_params_tgt.bytes_per_sec <= 0 || audio_hw_params_tgt.frame_size <= 0) {
        printf("size error\n");
        return -1;
    }
    audio_hw_params_src = audio_hw_params_tgt;

    // audio_st = pFormatCtx->streams[index]
    packet_queue_init(&audioq);
    SDL_PauseAudio(0);



    allSongSchedule = (pFormatCtx->duration * 1.0 / AV_TIME_BASE) * 1000;


    // Read frames and save first five frames to disk
    i=0;
    while(1)
    {
        if(isPause)
        {
            SDL_Delay(10);
            continue;
        }
        while(av_read_frame(pFormatCtx, &packet)>=0) {
            if(packet.stream_index==audioStream) {
                scheduleRate = (float)currentSongSchedule / (float)allSongSchedule;
                packet_queue_put(&audioq, &packet);
            } else {
                av_free_packet(&packet);
            }
            // Free the packet that was allocated by av_read_frame
            SDL_PollEvent(&event);
            switch(event.type) {
            case SDL_QUIT:
                quit = 1;
                SDL_Quit();
                exit(0);
                break;
            default:
                break;
            }

        }
    }

    while(1) SDL_Delay(1000);

    // Close the codecs
    avcodec_close(aCodecCtxOrig);
    avcodec_close(aCodecCtx);

    // Close the video file
    avformat_close_input(&pFormatCtx);
}

void Multimediaa::set_url(QString url)
{
    printf("set url function begin\n");

    //    printf("Qstring url is %s\n", url);

    //    QByteArray ba = url.toLatin1();
    //    m_url = ba.data();

    //    std::string p = url.toStdString();
    //    printf("QString url is %s\n", p.data());
    //    int len = p.length();
    //    m_url = (char *)malloc(len*sizeof(char));
    //    p.copy(m_url, len, 0);

    std::string p = url.toStdString();
    int i;
    for(i = 0; i < p.length(); i++)
    {
        m_url[i] = p[i];
    }
    m_url[i] = '\0';

    printf("char * url is %s\n", m_url);
}


int Multimediaa::init_multimedia2()
{
    printf("now the player state is %s\n", m_playerState.data());
//    if(m_playerState != "playing")
//    {
        isPause = false;
        m_playerState = "playing";

        FILE *hh  = fopen(m_url,"rb");
        printf("url is   %s\n", m_url);
        //    m_url = "../hydrogenMusic/assets/music/Taylor Swift - Love Story.mp3";
        if(hh)
        {
            printf("this url is legal\n");
        }else{
            printf("this url is illegal\n");
        }

        if(isPause)
        {
            std::cout<<"playing state isPause is true"<<std::endl;
        }else{
            std::cout<<"playing state isPause is false"<<std::endl;
        }
        boost::thread th(&play_mp3, m_url);
        th.detach();
//    }
}

void Multimediaa::play_multimedia()
{
    //在暂停状态下播放
    if(m_playerState == "pause")
    {
        isPause = false;
        m_playerState = "playing";
    }
}

void Multimediaa::pause_mulitimedia()
{
    //在播放状态下暂停
    if(m_playerState == "playing")
    {
        isPause = true;
        m_playerState = "pause";
    }
}

void Multimediaa::stop_mulitimedia()
{
    if(m_playerState != "stop")
    {
        //回调音频程序退出，线程退出
        //        quit = 1;
        SDL_LockAudio();
        SDL_CloseAudio();
        SDL_UnlockAudio();
        m_playerState = "stop";

    }
}

int Multimediaa::get_all_schedule()
{
    //    AVFormatContext *pFormatCtx = NULL;

    //    // Register all formats and codecs
    //    av_register_all();

    //    // Open video file,让mp3中文件流的信息填充pFormatCtx
    //    if(avformat_open_input(&pFormatCtx, m_url, NULL, NULL)!=0)
    //        exit (-1); // Couldn't open file

    //    allSongSchedule = (pFormatCtx->duration * 1.0 / AV_TIME_BASE) * 1000;

    return allSongSchedule;

    //    avformat_close_input(&pFormatCtx);
}

int Multimediaa::get_current_schedule()
{
//    printf("--%d--\n",currentSongSchedule);
    return currentSongSchedule;
}
std::vector<std::string> Multimediaa::get_song_infos(char *url)
{
    AVFormatContext *pFormatCtx = NULL;
    AVDictionaryEntry *tag = NULL;

    // Register all formats and codecs
    av_register_all();

    char album[] = "album";
    char title[] = "title";
    char artist[] = "artist";
    char album_artist[] = "album_artist";

    std::string album2;
    std::string title2;
    std::string artist2;
    std::string album_artist2;


    std::vector<std::string>infos;

    // Open video file,让mp3中文件流的信息填充pFormatCtx
    if(avformat_open_input(&pFormatCtx, url, NULL, NULL)!=0)
        exit (-1); // Couldn't open file


    for(int i = 0; i != 4; i ++)
    {

        int j = 0; //j表示是否已经添加了空串
        int k = 0; //k表示是否已经添加了关键值

        int len = sizeof(pFormatCtx->metadata);
        while((tag = av_dict_get(pFormatCtx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
        {
            k++;                           //表示遍历了第几遍了。
            //初始化j的位置很重要！
            //                int j = 0;           //j表示是否已经添加了空串
            //        printf("%s = %s\n",tag->key, tag->value);
            switch (i) {
            case 0:
                if(strcmp(tag->key, artist) == 0)
                {
                    artist2 = tag->value;
                    infos.push_back(artist2);

                }else{
                    //如果第一次遍历没有找到title，就推一个空串
                    //我这里原来用的判断是infos[0].size == ""
                    //段错误，因为都没有添加，哪里来的infos[0]!!
                    //如果这是最后一个
                    if(j == 0 && k == len)
                    {
                        std::string p = " ";
                        infos.push_back(p);
                        j++;
                    }
                }
                break;
            case 1:
                if(strcmp(tag->key, title) == 0)
                {
                    title2 = tag->value;
                    infos.push_back(title2);
                }else{
                    if(j == 0 && k == len)
                    {
                        std::string p = " ";
                        infos.push_back(p);
                        j++;
                    }
                }
                break;
            case 2:
                if(strcmp(tag->key, album) == 0)
                {

                    album2 = tag->value;
                    infos.push_back(album2);

                }else{
                    if(j == 0 && k == len)
                    {
                        std::string p = " ";
                        infos.push_back(p);
                        j++;
                    }
                }
                break;
            case 3:
                if(strcmp(tag->key, album_artist) == 0)
                {
                    album_artist2 = tag->value;
                    infos.push_back(album_artist2);
                }else{
                    if(j == 0 && k == len)
                    {
                        std::string p = " ";
                        infos.push_back(p);
                        j++;
                    }
                }

                break;
            default:
                break;
            }
        }
    }

    for(auto l:infos)
    {
        std::cout<<l<<endl;
    }

    avformat_close_input(&pFormatCtx);



    return infos;


}
