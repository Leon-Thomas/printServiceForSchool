#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "infodata.h"
#include "printworker.h"
#include "query.h"


class PreviewWindow;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //MainWindow(){};
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    Query query;
    PrintWorker* printerworker;
    PreviewWindow *preview;
    //    PdfGenerator pdf;

public:

};

#endif // MAINWINDOW_H
