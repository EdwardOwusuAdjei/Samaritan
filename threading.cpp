#include "threading.h"
#include "coreprocess.h"
#include <future>


Threading::Threading(QObject *parent) : QThread(parent)
{

}

void Threading::run()
{
    //coreprocess *pp = new coreprocess();
//    QImage img;
//    coreprocess cp;
//    //this;
//    MainWindow *ww;

//    cp.EntryPoint(ww,3,1,2,img,this);
    //  img;
    //    std::thread t;
    //    t = std::thread(&coreprocess::EntryPoint,this,w,3,1,2,img);
    //    t.joinable();
    //   std::async(std::launch::async,&coreprocess::EntryPoint,w,3,1,2,img);
    // std::async(std::launch::async,[img,cp]()mutable {cp.EntryPoint(w,3,1,2,img);});
    //    while(true)
    //    {d


    // emit liveupdate(img);


    //    }
}

void Threading::emitthis(QImage& img)
{
    emit liveupdate(img);
}
