#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <jrtplib3/rtpsession.h>
#include <jrtplib3/rtpudpv4transmitter.h>
#include <jrtplib3/rtpipv4address.h>
#include <jrtplib3/rtpsessionparams.h>
#include <jrtplib3/rtperrors.h>
#include <jrtplib3/rtplibraryversion.h>
#include <jrtplib3/rtppacket.h>
#include <boost/thread.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>


using namespace boost;
//-----begin------
using namespace jrtplib;
void checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}
//-----end---------

int main(int argc, const char * argv[]) {

    asio::io_service service;//创建调度器
    asio::ip::tcp::socket sock(service);//创建socket
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 6666);//创建目标地址对象
    //asio::ip::tcp::endpoint ep(asio::ip::address::from_string("192.168.42.29"), 6666);//创建目标地址对象
    //异步连接
    sock.async_connect(ep, [](const boost::system::error_code &error){
        if(error)
        {
            std::cout << error.message() << std::endl;
            return;
        }
        std::cout << "connect succeed" << std::endl;
    });

    //如果不进行run调用的话，程序会直接结束，所以这里会等待async_connect结束，
    //因此上面connect同步还是异步其实是一样的
    service.run();

    char data[512];
    boost::system::error_code ec;
    size_t len;
//--------rtp code begin------------
    RTPSession sess;
    uint16_t portbase = 5000;//jrtplib client port
    int status;
    bool done = false;

    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;
    sessparams.SetOwnTimestampUnit(1.0/10.0);

    sessparams.SetAcceptOwnPackets(true);

    transparams.SetPortbase(portbase);
    //std::cout << "2" << std::endl;
    status = sess.Create(sessparams,&transparams);//multi clients failed to create.
    //std::cout << "3" << std::endl;
    checkerror(status);//cout << error and finish program.

    //std::cout << "4" << std::endl;
    sess.BeginDataAccess();
    RTPTime delay(0.020);
    RTPTime starttime = RTPTime::CurrentTime();
    //std::cout << "1" << std::endl;

    while (!done)
    {
        status = sess.Poll();
        checkerror(status);

       // std::cout<<"h"<<std::endl;
        if (sess.GotoFirstSourceWithData())
        {
            std::cout<<"hi"<<std::endl;
            do
            {
                RTPPacket *pack;

                while ((pack = sess.GetNextPacket()) != NULL)
                {
                    //std::cout<<"h"<<std::endl;
                    std::cout << pack->GetPayloadData() << std::endl;
                    sess.DeletePacket(pack);
                }
            } while (sess.GotoNextSourceWithData());
        }

        RTPTime::Wait(delay);
        RTPTime t = RTPTime::CurrentTime();
        t -= starttime;
        if (t > RTPTime(60.0))
            done = true;
    }

    sess.EndDataAccess();
    delay = RTPTime(10.0);
    sess.BYEDestroy(delay,0,0);

//--------rtp code end--------------


    return 0;
}
