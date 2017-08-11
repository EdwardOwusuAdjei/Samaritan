#include "ui_mainwindow.h"
#include "mainwindow.h"
//SOME STATIC STUFF
static vector<QLabel*> labelsvector;
static bool loopbreaker;
static bool recordvideo;
static int sensitiveLevel;
static int b;
//SINGLETON
MainWindow* MainWindow::s_instance = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->horizontalSlider->setRange(1,4);
    ui->horizontalSlider->setSingleStep(1);
    b = 0;
    sensitiveLevel = 30;
    refresh();
}

bool MainWindow::breakloop()
{
    return  loopbreaker;
}
bool MainWindow::shouldrecord()
{
    return recordvideo;
}


MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::sensitivity()
{
    return sensitiveLevel;
}

MainWindow *MainWindow::instance()
{

    if(!s_instance)
    {
        s_instance = new MainWindow;
        return s_instance;
    }
    return s_instance;
}



void MainWindow::updateit(QImage img,int label)
{
    if(!img.isNull())
    {
        labelsvector[label]->setPixmap(QPixmap::fromImage(img));
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
    return ui->lineEdit->text().toStdString();
}
string MainWindow::getTextIP2()
{
    return ui->lineEdit_2->text().toStdString();
}

string MainWindow::getTextIP3()
{
    return ui->lineEdit_3->text().toStdString();
}



void MainWindow::on_pushButton_2_clicked()
{
    loopbreaker = true;
    QApplication::exit(0);
}
void MainWindow::begin(int idx)
{
    QLabel* flag = new QLabel();
    //TODO:: Remove widget when there is an error esp. internal error
    try{
        coreprocess* cp = new coreprocess();
        if(cp->canCapture(idx,b))
        {
            flag->setScaledContents(true);
            ui->gridLayout->addWidget(flag);
            labelsvector.push_back(flag);
            std::thread t = cp->aftermainthread();
            t.detach();
            connect(cp,SIGNAL(liveupdate(QImage,int)),this,SLOT(updateit(QImage,int)));
            b++;
        }
        else
        {
            QMessageBox::information(this,tr("Computer Vision"),tr("Cannot Capture"));
            delete flag;
            delete cp;
        }

    }
    catch(...)
    {
        QMessageBox::information(this,tr("Computer Vision"),tr("Cannot Capture"));
        ui->gridLayout->removeWidget(flag);
        delete flag;
        labelsvector.pop_back();
        std::cout<<"Caught Exception"<<std::endl;
    }
}

void MainWindow::begin(string url)
{
    QLabel* flag = new QLabel();
    //TODO:: Remove widget when there is an error esp. internal error
    try{
        coreprocess* cp = new coreprocess();
        if(cp->canCapture(url,b))
        {
            flag->setScaledContents(true);
            ui->gridLayout->addWidget(flag);
            labelsvector.push_back(flag);
            std::thread t = cp->aftermainthread();
            t.detach();
            connect(cp,SIGNAL(liveupdate(QImage,int)),this,SLOT(updateit(QImage,int)));
            b++;
        }
        else
        {
            QMessageBox::information(this,tr("Computer Vision"),tr("Cannot Capture"));
            delete flag;
            delete cp;
        }

    }
    catch(...)
    {
        QMessageBox::information(this,tr("Computer Vision"),tr("Cannot Capture"));
        ui->gridLayout->removeWidget(flag);
      //  delete flag;
        labelsvector.pop_back();
        std::cout<<"Caught Exception"<<std::endl;
    }
}
void MainWindow::refresh()
{
    ui->comboBox->clear();
    videointerface capinterface;
    vector<int>interfaces = capinterface.getavailablecams();
    for(auto &i : interfaces)
    {
        ui->comboBox->addItem(QString::fromStdString(std::to_string(i)));
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    String url = ui->lineEdit_4->text().toStdString();
    try{
        begin(url);
        ui->lineEdit_4->clear();
    }
    catch(...)
    {
        QMessageBox::information(this,tr("Computer Vision"),tr("Cannot Capture"));
    }
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked)
    {
        QMessageBox::information(this,tr("Computer Vision"),tr("video saving will use more computer resources"));
        recordvideo = true;
    }
    else
    {
        recordvideo = false;
    }

}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->horizontalSlider->statusTip();
    if(position == 1)
    {
        QToolTip::showText(QCursor::pos(),"Normal [Enough Light]");
        sensitiveLevel = 30;
    }
    else if(position == 2)
    {
        QToolTip::showText(QCursor::pos(),"Slightly Sensitive [Enough Light]");
        sensitiveLevel = 25;
    }
    else if(position ==3)
    {
        QToolTip::showText(QCursor::pos(),"Extra Sensitive [Low Light]");
        sensitiveLevel = 20;
    }
    else if(position == 4)
    {
        QToolTip::showText(QCursor::pos(),"Very Sensitive [Very Low Light]");
        sensitiveLevel = 15;
    }


}



void MainWindow::on_pushButton_4_clicked()
{
    //refresh
    refresh();
}

void MainWindow::on_pushButton_clicked()
{
    //add
    int value = stoi(ui->comboBox->currentText().toStdString());
    begin(value);
}
