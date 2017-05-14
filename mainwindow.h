#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threading.h"
#include <string>


#include "facial.h"
#include <future>
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
    void setWindowAddr(MainWindow window);
    void updater(QImage& img);
    void updater1(QImage& img);
    void updater2(QImage& img);
    void updater3(QImage img);
    void updater4(QImage img);
    void updater5(QImage img);
    void updater6(QImage img);
    void setthispointer(MainWindow* mw);
    ~MainWindow();
    static MainWindow* instance();
    Threading *threads;

    bool breakloop();
    string getTextIP();
    string getTextIP2();
    string getTextIP3();
signals:
    void emithere(QImage img);
public slots:
    void updateit(QImage img);

private slots:


    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_pushButton_clicked();



    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
