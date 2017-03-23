#ifndef THREADING_H
#define THREADING_H

#include <QThread>
#include "ui_mainwindow.h" //dont include QTCore..
//#include "coreprocess.h"


class Threading : public QThread
{
    Q_OBJECT
public:
   // MainWindow *ww;
    explicit Threading(QObject *parent = 0);

    void run();
    void emitthis(QImage& img);

signals:
    void liveupdate(QImage img);
public slots:
   // void setchange(QImage img);
};

#endif // THREADING_H
