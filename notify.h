#ifndef NOTIFY_H
#define NOTIFY_H
#include <vector>
#include <string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>
using namespace std;
class notify
{
public:
    notify();
    int notifyselected(vector<string>& ip);
};

#endif // NOTIFY_H
