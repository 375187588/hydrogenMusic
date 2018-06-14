LIBS =
INC  =
# Set your own ffmpeg main directory please
# eg: 
# MAIN_DIR = /home/Ansersion/ffmpeg-2.8.4
MAIN_DIR = /usr/lib/ffmpeg2.8
TARGET=tutorial

LIBS += -L$(MAIN_DIR)/libavcodec
LIBS += -L$(MAIN_DIR)/libavformat
LIBS += -L$(MAIN_DIR)/libavutil
LIBS += -L$(MAIN_DIR)/libswscale
LIBS += -L$(MAIN_DIR)/libswresample
LIBS += -L$(MAIN_DIR)/libavfilter
INC  += -I$(MAIN_DIR)

$(TARGET): tutorial.c
	gcc -g -o $@ tutorial.c $(INC) $(LIBS) -lpthread -lswscale -lswresample -lavutil -lavformat -lavcodec -lz -lavutil -lm -lswresample -lavcodec -lpthread -lavutil -lrt `sdl-config --cflags --libs`

clean:
	-rm -rf *.o $(TARGET)
