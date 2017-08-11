#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolTip>
#include <string>
#include <vector>
#include <future>
#include <QMessageBox>
#include "videointerface.h"
#include "coreprocess.h"


using namespace std;

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    static MainWindow *s_instance;

public:

    MainWindow* w;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow* instance();
    bool breakloop();
    string getTextIP();
    string getTextIP2();
    string getTextIP3();
    bool shouldrecord();
    int sensitivity();
private:
    void updater(QImage& img);
    void updater2(QImage& img);
    void updater3(QImage img);
    void updater4(QImage img);
    void updater5(QImage img);
    void updater6(QImage img);
    void begin(string url);
    void begin(int idx);
    void refresh();
signals:
    void emithere(QImage img);
public slots:
    void updateit(QImage img,int QTlabel);

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_toggled(bool checked);

    void on_horizontalSlider_sliderMoved(int position);


    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
