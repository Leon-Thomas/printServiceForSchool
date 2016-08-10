#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QInputDialog>
#include <QFileDialog>
#include <QDebug>
#include "mdisubwindow.h"

MdiSubWindow::MdiSubWindow(MdiType paint_type,const QString &def_text,const QFont &f, QWidget *parent, Qt::WindowFlags flags)
    :QMdiSubWindow(parent,flags),type(paint_type),content(def_text),font(f)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMinimumSize(30,20);
    this->resize(50,30);
}

MdiSubWindow::~MdiSubWindow()
{

}

void MdiSubWindow::paintEvent(QPaintEvent *paintEvent)
{
    if(this->type == PHOTO)
    {
        paintPhoto();
    }
    else if(this->type == TEXT)
    {
        paintText();
    }

    QMdiSubWindow::paintEvent(paintEvent);

}

void MdiSubWindow::mousePressEvent(QMouseEvent *mouseEvent)
{
    this->mv_pos = this->pos() - mouseEvent->globalPos();
    QMdiSubWindow::mousePressEvent(mouseEvent);
}

void MdiSubWindow::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    this->move( mouseEvent->globalPos() + this->mv_pos );
    QMdiSubWindow::mouseReleaseEvent(mouseEvent);
}

void MdiSubWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->key() == Qt::Key_Up)
    {
        this->move(this->pos() + QPoint(0,-1));
    }
    else if(keyEvent->key() == Qt::Key_Down)
    {
        this->move(this->pos() + QPoint(0,1));
    }
    else if(keyEvent->key() == Qt::Key_Left)
    {
        this->move(this->pos() + QPoint(-1,0));
    }
    else if(keyEvent->key() == Qt::Key_Right)
    {
        this->move(this->pos() + QPoint(1,0));
    }
    else
        QMdiSubWindow::keyPressEvent(keyEvent);
}

void MdiSubWindow::mouseDoubleClickEvent(QMouseEvent *mouseEvent)
{
    if(this->type == TEXT)
    {
        QString text = QInputDialog::getText(this,tr("Input text"),tr("New text"));
        this->content = text;
        repaint();
    }
    else if(this->type == PHOTO)
    {
        QString filepath = QFileDialog::getOpenFileName(this,tr("Pick photo"),
                                                        tr("."),tr("Photo(*.JPG *.jpg)"));
        this->fullname = filepath;
        repaint();
    }
    else
        QMdiSubWindow::mouseDoubleClickEvent(mouseEvent);
}

void MdiSubWindow::setPhotoPath(const QString filename)
{
    this->fullname = filename;
    repaint();
}

void MdiSubWindow::setText(const QString &str, const QFont &font)
{
    this->content = str;
    this->font    = font;
    repaint();
}

QString MdiSubWindow::getText()
{
    return this->content;
}

void MdiSubWindow::paintPhoto()
{
    QPainter    painter;
    QPixmap     photo;

    painter.begin(this);
    if( !photo.load(fullname) )
    {
        //qDebug()<<"mdi: load photo faild!";
        painter.drawText(0,this->height()/2,tr("load failed"));
        painter.end();
        return ;
    }
    painter.drawPixmap(0,0,this->width(),this->height(),photo);

    painter.end();
}

void MdiSubWindow::paintText()
{
    QPainter painter;

    painter.begin(this);
    font.setPixelSize(this->height()*5/7);
    painter.setFont(font);
    painter.drawText(0,0,this->width(),this->height(),Qt::AlignTop,content);

    painter.end();
}


