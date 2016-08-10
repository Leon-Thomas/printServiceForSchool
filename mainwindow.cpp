#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileInfo>
#include <QFileDialog>
#include "previewwindow.h"
#include <QMessageBox>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    preview = new PreviewWindow(this);


    ui->setupUi(this);
    this->setWindowTitle(QObject::trUtf8("SIAS录取通知书生成系统 2.0"));
    this->setFixedSize(this->size());
    this->printerworker = new PrintWorker(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    QLabel * permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permanent->setText(tr("起点工作室制作"));
    permanent->setTextFormat(Qt::RichText);
    ui->statusBar->addPermanentWidget(permanent);

    connect(this->printerworker, &PrintWorker::unitFinished, ui->progressBar, &QProgressBar::setValue);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString file_full;
    QFileInfo fi;
    file_full = QFileDialog::getOpenFileName(this,QObject::trUtf8("Open File"),
                                             "./",
                                             QObject::trUtf8("File (*.xls *.xlsx)"));
    fi = QFileInfo(file_full);

    QString src;
    src = fi.absoluteFilePath();
    //    ui->label->setText(src);
    ui->lineEdit->setText(src);
    query.setAbsoluteFilePath(src);
    src = fi.absolutePath();
    query.setAbsolutePath(src);
    src = fi.baseName();
    query.setBaseName(src);

}


void MainWindow::on_pushButton_2_clicked()
{
    QString src= QFileDialog::getExistingDirectory(this, QObject::trUtf8(""), QObject::trUtf8("./"));
    printerworker->setPhotosPath(src);
    ui->lineEdit_2->setText(src);
}



void MainWindow::on_pushButton_3_clicked()
{
    QString outPath = QFileDialog::getExistingDirectory(this, QObject::trUtf8(""), QObject::trUtf8("./"));
    printerworker->setOutFileName(outPath + "/"+ query.getBaseName() +".pdf");
    ui->lineEdit_3->setText(outPath);
}

void MainWindow::on_pushButton_4_clicked()
{
    preview->saveRects();
    if(!query.hasData())
    {
        QMessageBox::critical(0, "警告","请先初始化！！！");
        return;
    }

    QList<InfoData> *temp = new QList<InfoData>(query.getAllData());
    //    temp.append(query.getAllData());
    ui->progressBar->setMaximum(query.getSizeofList());

    printerworker->appendDataToQueue(*temp);
    delete temp;
    printerworker->setLocations(preview->getLocation());
    printerworker->doPrint();
    QMessageBox::information(0, "PDF生成成功","请继续操作");
}


void MainWindow::on_pushButton_5_clicked()
{
    QWidget::destroy();
}


void MainWindow::on_pushButton_6_clicked()
{
    if(!query.hasData())
    {
        QMessageBox::critical(0, "警告","请先初始化！！！");
        return;
    }
    preview->show();
    //    QMessageBox::information(0, "模板已设置","请继续操作");
}



void MainWindow::on_pushButton_8_clicked()
{
    if(!query.hasData())
    {
        QMessageBox::critical(0, "警告","请先初始化！！！");
        return;
    }
    QString src= QFileDialog::getExistingDirectory(this, QObject::trUtf8(""), QObject::trUtf8("./"));
    query.setDreiveToExcel(src);
    query.createExcel();
}

void MainWindow::on_pushButton_7_clicked()
{
    if(!query.hasData())
    {
        if(!query.init())
            return;
    }

    QMessageBox::information(0, "初始化完成","请继续操作");
}
