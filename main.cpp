#include "coreprocess.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  MainWindow* w;
     MainWindow::instance()->show();
   // w = new MainWindow();
   // w->setthispointer(w);
   //  w->show();
//    w ->
    //coreprocess *cp = new coreprocess();
    //std::unique_ptr<coreprocess>hd(new coreprocess);

   // hd->EntryPoint(w,1,0,1);
//    cp->EntryPoint(w,1,0,1);

//   MainWindow wb;
 //  wb.show();

  //  hd->EntryPoint(w,3,1);




    return a.exec();
}


