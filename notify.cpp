#include "notify.h"
notify::notify()
{

}

int notify::notifyselected(std::vector<std::string> &ip,std::vector<uchar>*& bytes)
{
#ifdef __linux__
    int sock;
#elif __WIN32
    WSAData wsa;
    SOCKET sock;

#endif

    try {
#ifdef __WIN32
        if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            //Couldnt start up.. use WSAGetLastError()
        }

#endif

         struct sockaddr_in server;
        for(unsigned int i = 0 ;i < ip.size(); i++)
        {
            sock = socket(AF_INET , SOCK_STREAM , 0);
            if (sock == -1)
            {
                // printf("Could not create socket");
            }
            server.sin_addr.s_addr = inet_addr(ip[i].c_str());
            server.sin_family = AF_INET;
            server.sin_port = htons( 8888 );

            //Connect to remote server
             if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
            {
                //connection fails then 1 is returned.
                delete bytes;
                ip.clear();
                ip.shrink_to_fit();
                return 1;
            }
#ifdef __linux__
            //uses uchar *
            if(send(sock,bytes->data(),bytes->size(),0)<0)
            {

//                bytes->clear();
//                bytes->shrink_to_fit();
                 delete bytes;

                ip.clear();
                //ip.resize(0);
                ip.shrink_to_fit();
                return 1;
            }
#elif __WIN32
            if(send(sock,reinterpret_cast<const char*>(bytes->data()),bytes->size(),0)<0)
            {
                 delete bytes;

                ip.clear();
                ip.shrink_to_fit();
                return 1;
            }

#endif

#ifdef __linux__
            close(sock);
#elif __WIN32
            closesocket(sock);
#endif
        }
         delete bytes;

        ip.clear();
        ip.shrink_to_fit();
        return 1;
    } catch (...) {
        delete bytes;
        ip.clear();
        ip.shrink_to_fit();
        return 1;
#ifdef __linux__
        close(sock);
#elif __WIN32
        closesocket(sock);
#endif
    }
    return 0;
}


//int notify::notifyselected(vector<string> &ip,vector <uchar> bytes)
//{
//    int sock;
//    try {
//        struct sockaddr_in server;
//        string alert = "MOTION";
//        char message[alert.size()+1];

//        //Create socket
//        for(unsigned int i = 0 ;i < ip.size(); i++)
//        {
//            sock = socket(AF_INET , SOCK_STREAM , 0);
//            if (sock == -1)
//            {
//                // printf("Could not create socket");
//            }
//            server.sin_addr.s_addr = inet_addr(ip[i].c_str());
//            server.sin_family = AF_INET;
//            server.sin_port = htons( 8888 );

//            //Connect to remote server
//            if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
//            {
//                //connection fails then 1 is returned.
//                ip.clear();
//                ip.resize(0);
//                return 1;
//            }
//            strcpy(message, alert.c_str());
//            //send(sock , message , strlen(message), 0) < 0 &&
//            if(send(sock,bytes.data(),bytes.size(),0)<0)
//            {

//                ip.clear();
//                ip.resize(0);
//                return 1;
//            }

//            close(sock);
//        }
//        ip.clear();
//        ip.resize(0);
//    } catch (...) {
//        ip.clear();
//        ip.resize(0);
//        close(sock);
//    }
//    return 0;
//}
