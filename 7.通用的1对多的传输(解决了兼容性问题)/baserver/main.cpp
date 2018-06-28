#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
//字符串处理
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<vector>
#include <jrtplib3/rtpsession.h>
#include <jrtplib3/rtpudpv4transmitter.h>
#include <jrtplib3/rtpipv4address.h>
#include <jrtplib3/rtpsessionparams.h>
#include <jrtplib3/rtperrors.h>
#include <jrtplib3/rtplibraryversion.h>
#define STACK_INIT_SIZE 100

using namespace boost;
using namespace std;
//begin
using namespace jrtplib;
int status;
RTPSession sess;
//end
//split begin-----------
vector<string> split(const string &str,const string &pattern)
{
    //const char* convert to char*
    char * strc = new char[strlen(str.c_str())+1];
    strcpy(strc, str.c_str());
    vector<string> resultVec;
    char* tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL)
    {
        resultVec.push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return resultVec;
}
//split end-------------

using socket_ptr = boost::shared_ptr<asio::ip::tcp::socket>;//包装socket类型的智能指针
//jrtplib deal error begin------
void checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}
//jrtplib deal error end------

void client_session(socket_ptr sock)
{

    auto ep = sock->local_endpoint();
    std::cout<<ep.address().to_string()<<"连接"<<std::endl;

    char data[512];
    boost::system::error_code ec;
    size_t len;
    //----------------------begin----------------------
    int i;
    int num = 0;

    uint16_t destport = 6664;//jrtplib client port
    //uint8_t destip[]={127,0,0,1};
    //-------------get socket ip start-------------
    string dp = ep.address().to_string();
    vector<string> splitresult;
    vector<int> sing_num_vec;
    vector<int> result;
    splitresult = split(dp, ".");

    int tmp = 0;
    for(vector<string>::size_type i=0;i!=splitresult.size();i++)
    {
        for(size_t t=0;t!=splitresult[i].size();t++)
        {
            if((splitresult[i][t]<='9') && (splitresult[i][t]>='0'))
            {
                //cout<<splitresult[i][t];
                int num = splitresult[i][t]-'\0'-48;
                //cout << num << endl;
                sing_num_vec.push_back(num);
            }

        }
        size_t length = sing_num_vec.size();
        for(size_t i = 0; i != length;i++)
        {
            tmp+=sing_num_vec[i]*pow(10,length-1-i);
        }
        result.push_back(tmp);
        tmp = 0;
        sing_num_vec.clear();

    }

    auto s0=splitresult[0];
    auto s1=splitresult[1];
    auto s2=splitresult[2];
    auto s3=splitresult[3];
    char destip_0[20];
    char destip_1[20];
    char destip_2[20];
    char destip_3[20];


    //    int length = dp.copy(destip_,19);
    //    destip_[length] = '\0';
    //    uint8_t *destip = (uint8_t *)destip_;
    int length0 = s0.copy(destip_0,19);
    destip_0[length0] = '\0';
    int length1 = s1.copy(destip_1,19);
    destip_1[length1] = '\0';
    int length2 = s2.copy(destip_2,19);
    destip_2[length2] = '\0';
    int length3 = s3.copy(destip_3,19);
    destip_3[length3] = '\0';
//    uint8_t *i0 = (uint8_t *)destip_0;
//    uint8_t *i1 = (uint8_t *)destip_1;
//    uint8_t *i2 = (uint8_t *)destip_2;
//    uint8_t *i3 = (uint8_t *)destip_3;
    uint8_t i0=result[0];
    uint8_t i1=result[1];
    uint8_t i2=result[2];
    uint8_t i3=result[3];

    uint8_t i5= result[0];

    //uint8_t destip[] = (uint8_t *)destip_;
    //    uint8_t i1=127;
    //    uint8_t i2=0;
    //    uint8_t i3=1;
    uint8_t destip2[]={i0,i1,i2,i3};
    //uint32_t destip[]=ntohl(inet_addr(ep.address().to_string().c_str()));
    //uint32_t destip[]=ntohl(inet_addr("127.0.0.1"));
    //------------get socket ip end------------------


    RTPIPv4Address addr(destip2,destport);
    RTPIPv4Address addr2(destip2,5000);
    //RTPIPv4Address addr2(destip2,destport);

//    sess.ClearDestinations();
//    status = sess.AddDestination(addr);
    //status = sess.AddDestination(addr2);
    checkerror(status);

    for (i = 1 ; i <= 10 ; i++)
    {
        //sess.ClearDestinations();
        status = sess.AddDestination(addr);
        status = sess.AddDestination(addr2);
        printf("\nSending packet %d/%d\n",i,num);

        std::cout << result[3] << std::endl;
        status = sess.SendPacket((void *)"1234567890",10,0,false,10);
        checkerror(status);
        RTPTime::Wait(RTPTime(1,0));
    }

    //sess.BYEDestroy(RTPTime(10,0),0,0);
    //--------------end------------------------------

    //    while(true)
    //    {
    //        len = sock->read_some(asio::buffer(data), ec);


    //        if(ec)
    //        {
    //            std::cout << boost::system::system_error(ec).what() << std::endl;
    //            break;
    //        }

    //        len = sock->write_some(asio::buffer(data), ec);

    //        if(ec)
    //        {
    //            std::cout << boost::system::system_error(ec).what() << std::endl;
    //            break;
    //        }
    //    }

    std::cout<<ep.address().to_string()<<"关闭"<<std::endl;

}

int main(int argc, const char * argv[])
{
    asio::io_service service;//创建调度器
    //asio::ip::tcp::endpoint ep(asio::ip::address::from_string("192.168.42.29"), 6666);//server ep
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 6666);
    asio::ip::tcp::acceptor apt(service, ep);//创建连接器

    //-----------------------start-----------

    uint16_t portbase = 6666;//jrtplib server port
    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;

    sessparams.SetOwnTimestampUnit(1.0/10.0);

    sessparams.SetAcceptOwnPackets(true);
    transparams.SetPortbase(portbase);
    status = sess.Create(sessparams,&transparams);

    checkerror(status);
    //-----------------end------------------

    while(true)
    {
        socket_ptr sock(new asio::ip::tcp::socket(service));
        apt.accept(*sock);//接收新的连接
        boost::thread(boost::bind(client_session, sock));//开辟线程去处理该连接上的事务
    }
    sess.BYEDestroy(RTPTime(10,0),0,0);

}
