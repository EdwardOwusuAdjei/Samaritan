#include "facial.h"

facial::facial()
{

}

void facial::startfacial()
{
    string path = "/home/edward/build-ComputerVision-CVision-Debug/openface/demos/classifier_webcam.py&";
    system(path.c_str());
}

void facial::stopfacial()
{
    //killall now needs to be installed on client machine here
    //i used archlinux so pacman -S install it
    //other guys can apt-get install it
    //just for project demonstration--to show this can be started by program
    string command = "killall python2";
    system(command.c_str());
}
