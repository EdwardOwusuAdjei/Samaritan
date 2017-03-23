#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coreprocess.h"

#include "facial.h"
#include <future>

static int b = 1;
MainWindow* MainWindow::s_instance = NULL;
static bool loopbreaker;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //  w = this;//you see this shit here..my fucking saviour
    //threads = new Threading(this);//so when gui goes thread goes..
    //  threads = Threading(this);
    //  connect(threads,SIGNAL(liveupdate(QImage)),this,SLOT(updateit(QImage)));
    // connect(threads,SIGNAL(emithere(QImage)),this,SLOT(updateit(QImage)));
    //threads->setval(this);
    //    threads->start();

    //used to be this
}

bool MainWindow::breakloop()
{
    return  loopbreaker;
}

void MainWindow::setWindowAddr(MainWindow window)
{

}


MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::instance()
{

    if(!s_instance)
    {
        s_instance = new MainWindow;
        return s_instance;
    }
}



void MainWindow::updateit(QImage img)
{

    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::updater1(QImage& img)
{


    if(!img.isNull())
    {

        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img));
    }


}
void MainWindow::updater2(QImage& img)
{

    if(!img.isNull())
    {

        ui->label_2->setAlignment(Qt::AlignCenter);
        ui->label_2->setPixmap(QPixmap::fromImage(img));

    }

}
string MainWindow::getTextIP()
{
    return ui->textEdit_2->toPlainText().toStdString();

}
string MainWindow::getTextIP2()
{
    return ui->textEdit_3->toPlainText().toStdString();
}

string MainWindow::getTextIP3()
{
    return ui->textEdit_4->toPlainText().toStdString();
}

void MainWindow::setthispointer(MainWindow *mw)
{

    // w  = mw;
}



void MainWindow::on_radioButton_2_clicked(bool checked)
{



}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if(checked)
    {
        //   ui->comboBox->hide();
        ui->comboBox_2->hide();
        ui->label_7->hide();
    }
    else
    {
        //  ui->comboBox->show();
        ui->comboBox_2->show();
        ui->label_7->show();
    }
}

void MainWindow::on_pushButton_clicked()
{

    loopbreaker = true;


    // coreprocess cp("/home/edward/ComputerVision_/new.avi");
    std::unique_ptr<coreprocess>cp(new coreprocess(0,1));


    loopbreaker = false;
    // cp.EntryPoint(this,3,0);
    cp->EntryPoint();

    //    else
    //    {


    //        loopbreaker = false;
    //        coreprocess cp(0);


    //        b++;
    //        cp.EntryPoint(this,3,0);
    //    }

    //    // delete  ui;
}



void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString selectedvid = ui->comboBox_2->currentText();
    if(selectedvid == "1")
    {

        //control = 1;
        // cv::VideoCapture vc(1);
        //        ui->label->clear();

        // QApplication a();
        //MainWindow w;
        //  aftermain(w,vc);
        //  coreprocess *cp = new coreprocess();
        //capVideo.open(1);

        //  cp->EntryPoint(w,3,1);
    }
    else if(selectedvid == "2")
    {
        facial fac;
        fac.stopfacial();
        // ui->label_2->clear();
    }

}

