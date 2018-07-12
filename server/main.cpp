#include "server.h"
#include "receiver.h"

void receive()
{
    asio::io_service io;
    Tcp_server receiver(io, 1347);
    io.run();
}


using namespace boost::asio;
using namespace std;

boost::thread_group threads;
int main(int argc, char *argv[])
{
    boost::thread th(&receive);
    QApplication a(argc, argv);

    try
    {
        cout<<"Server start."<<endl;
        Server srv;
        //server s1;

        for(int j = 0;j < 2;++j)
        {
            threads.create_thread(boost::bind(&Server::run,&srv));
            sleep(1000);
        }
        threads.join_all();

    }
    catch (std::exception &e)
    {
        cout<<e.what()<<endl;
    }

    return 0;
}
