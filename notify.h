#ifndef NOTIFY_H
#define NOTIFY_H
#ifdef __linux__
#include<sys/socket.h>
#include<arpa/inet.h>
#elif _WIN32
#include <winsock2.h>
#endif
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/core.hpp>
#include<stdio.h>
#include<string.h>
#include <unistd.h>

class notify
{
public:
    notify();
   // int notifyselected(std::vector<std::string>& ip);
    int notifyselected(std::vector<std::string>& ip,std::vector<uchar>*& matrix);
};

#endif // NOTIFY_H
