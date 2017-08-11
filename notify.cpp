#include "notify.h"
//TODO:: Linux - Only. Add Windows. Fix what happens to vector after return vals
notify::notify()
{

}

int notify::notifyselected(vector<string> &ip)
{
    int sock;
    try {
        struct sockaddr_in server;
        string alert = "MOTION";
        char message[alert.size()+1];

        //Create socket
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
                ip.clear();
                ip.resize(0);
                return 1;
            }
            strcpy(message, alert.c_str());
            if( send(sock , message , strlen(message), 0) < 0)
            {
                ip.clear();
                ip.resize(0);
                return 1;
            }

            close(sock);
        }
        ip.clear();
        ip.resize(0);
    } catch (...) {
        ip.clear();
        ip.resize(0);
        close(sock);
    }
    return 0;
}
