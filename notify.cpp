#include "notify.h"

notify::notify()
{

}

int notify::notifyselected(vector<string> &ip)
{
    int sock;
    struct sockaddr_in server;
    //ADD ME: Check if its passed as valid ip
    string alert = "MOTION";
    char message[alert.size()+1];//to cater for the null term

    //Create socket
    for(int i = 0 ;i < ip.size(); i++)
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
            return 1;
        }


        strcpy(message, alert.c_str());

     //  size_t imgsize = img.total()*img.elemSize();

        if( send(sock , message , strlen(message), 0) < 0)
        {

            return 1;
        }



        // shutdown(sock,2);
        close(sock);
    }
    ip.clear();
    ip.resize(0);
    return 0;
}
