#include <QPainter>
#include <QPrinter>
#include <QFontDatabase>
#include <QPixmap>
#include <QThread>
//#include <QDebug>

#include "printworker.h"


PrintWorker::PrintWorker(QObject *parent) : QObject(parent)
{

    //    this->photosPath     = QString("/home/leon/图片");
    //    this->barCodePath    = QString("/home/leon/图片");
    this->rects          = new Location();

    int fid = QFontDatabase::addApplicationFont(QString("SIAS_OK.TTF"));
    if(fid != -1)
    {
        this->barCodefont = new QFont(QFontDatabase::applicationFontFamilies(fid).first());
    }
    else
        this->barCodefont = new QFont();
}


/*slots*/
bool PrintWorker::doPrint()
{
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPrinter::A4);
    //    printer.setOutputFileName(QString("/home/leon/图片/testh.pdf"));
    printer.setOutputFileName(this->outFileName);
    //    qDebug()<<printer.pageRect()<<printer.paperRect();

    QPainter painter;
    uint     finished = 0;
    uint     total = print_queue.size();
    double offset = (printer.paperRect().width() - printer.pageRect().width())/2.0;
    double factor = offset/13.0;
    //    qDebug()<<"factor:"<<factor;

    painter.begin(&printer);
    QRectF &&t = QRectF();
    QFont font = painter.font();
    while( !print_queue.isEmpty() )
    {
        InfoData data = print_queue.dequeue();
        //photo
        QPixmap photo;
        QString phpath(photosPath + "/" + data.cid + ".JPG");
        if( !photo.load(phpath) )
        {
            //            qDebug()<<data.cid<<" :photo failed!";
            return false;
        }
        t = this->rects->rect_photo;
        painter.drawPixmap(QRectF(t.left()*factor,t.top()*factor,
                                  t.size().width()*factor,t.size().height()*factor),
                           photo,QRectF(0,0,0,0));
        //barcode
        t = this->rects->rect_barCode;

        font.setPixelSize(t.size().height()*factor*5/7);
        painter.setFont(font);
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),data.barCode);
        //name
        t = this->rects->rect_name1;
        //        font = painter.font();
        font.setPixelSize(t.size().height()*factor*5/7);
        painter.setFont(font);
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),data.name);
        //college
        t = this->rects->rect_collage;
        //        font = painter.font();
        font.setPixelSize(t.size().height()*factor*5/7);
        painter.setFont(font);
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),data.college);
        //major
        t = this->rects->rect_major;
        //        font = painter.font();
        font.setPixelSize(t.size().height()*factor*5/7);
        painter.setFont(font);
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),data.major);
        //leyar
        t = this->rects->rect_layer;
        //        font = painter.font();
        font.setPixelSize(t.size().height()*factor*5/7);
        painter.setFont(font);
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),data.leyar);
        //date
        t = this->rects->rect_date1;
        //        font = painter.font();
        font.setPixelSize(t.size().height()*factor*5/7);
        painter.setFont(font);
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),rects->date1);
        t = this->rects->rect_date2;
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),rects->date2);
        //barCodeText
        t = this->rects->rect_barCodeText;
        //sias barCode font
        barCodefont->setPixelSize(t.size().height()*factor*5/7);
        font = painter.font();
        painter.setFont(*barCodefont);
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),data.barCode);
        painter.setFont(font);      //restored font

        //label string
        t = this->rects->rect_siasLabel;
        //        font = painter.font();
        font.setPixelSize(t.size().height()*factor*5/7);
        painter.setFont(font);
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),data.siasLabel);

        //name_last
        t = this->rects->rect_name2;
        //        font = painter.font();
        font.setPixelSize(t.size().height()*factor*5/7);
        painter.setFont(font);
        painter.drawText(QPointF(t.left()*factor,t.top()*factor),data.name);


        if ((int)(++finished*100000.000/total)%5000==0)
        {

            //            qDebug() << (int)(finished*100000.0/total) << i;
            emit unitFinished(finished);
        }
        if( !print_queue.isEmpty() )
            printer.newPage();

        QThread::usleep(5);
    }

    painter.end();
    //    emit allFinished();

    return true;
}


void PrintWorker::setPhotosPath(const QString &srcdir)
{
    this->photosPath = srcdir;
}

//void PrintWorker::setBarCodesPath(const QString &srcdir)
//{
//    this->barCodePath = srcdir;
//}

void PrintWorker::setOutFileName(const QString &filename)
{
    this->outFileName = filename;
}

void PrintWorker::setLocations(const Location &l)
{
    *this->rects  = l;
}


void PrintWorker::appendDataToQueue(QList<InfoData> &data_list)
{
    this->print_queue.append(data_list);
}







/*bool PrintWorker::generatePdf()
{
    QPrinter text_printer;
    QString outFilename(data.distPath + "/" + data.cid + ".pdf");

    text_printer.setOutputFormat(QPrinter::PdfFormat);
    text_printer.setPageSize(QPrinter::A4);
    text_printer.setOutputFileName(outFilename); //直接设置输出文件路径，相对或者绝对路径
    qDebug()<<"PageSize:"<<text_printer.pageRect();

    QPainter text_painter;

    text_painter.begin(&text_printer);

    QPixmap pixmap;
    QString filename(data.photosPath + "/"+ data.cid + QString(".JPG"));

    qDebug()<<"photo:"<<filename;

    pixmap.load(filename);
    if(pixmap.isNull())
    {
         qDebug()<<data.cid<<":photo load failed!";
         return false;
    }

    float factor = (float)2/7;      //缩放比例
    int w = pixmap.rect().width()*factor, h = pixmap.rect().height()*factor;

    qDebug()<<"pho_width:"<<w<<"pho_heigh:"<<h;

    QPixmap tmp = pixmap.scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //photo;
    text_painter.drawPixmap(QPoint(600,50),tmp,tmp.rect());
    //text_painter.drawPixmap(QPoint(0,50),tmp,tmp.rect());
    //barCode
    text_painter.drawText(QPointF(420,160),data.barCode);
    //name
    QFont font = text_painter.font();
    font.setPixelSize(25);
    text_painter.setFont(font);
    text_painter.drawText(QPointF(100,205),data.name);
    //college
    font = text_painter.font();
    font.setPixelSize(19);
    text_painter.setFont(font);
    text_painter.drawText(QPointF(443,250),data.college);
    //major
    font = text_painter.font();
    font.setPixelSize(19);
    text_painter.setFont(font);
    text_painter.drawText(QPointF(65,295),data.major);
    //leyar
    font = text_painter.font();
    font.setPixelSize(25);
    text_painter.setFont(font);
    text_painter.drawText(QPointF(433,297),data.leyar);
    //date
    font = text_painter.font();
    font.setPixelSize(15);
    text_painter.setFont(font);
    text_painter.drawText(QPointF(553,435),data.date);
    //barCode
    QPixmap bar_pic;
    QString bar_filename(data.barCodePath + "/" + data.barCode + ".JPG");

    qDebug()<<"barCode:"<<bar_filename;

    if( !bar_pic.load(bar_filename) )
    {
        qDebug()<<data.cid<<":bar_pic load faied!";
        return false;
    }
    float fac_w = 1.0/2,fac_h = 1.0/3;
    int bar_w = fac_w*bar_pic.rect().width();
    int bar_h = fac_h*bar_pic.rect().height();
    tmp = bar_pic.scaled(bar_w,bar_h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    text_painter.drawPixmap(QPoint(60,505),tmp,tmp.rect());


    //label string
    font = text_painter.font();
    font.setPixelSize(14);
    text_painter.setFont(font);
    text_painter.drawText(QPointF(75,595),data.sth);

    //name_last
    font = text_painter.font();
    font.setPixelSize(19);
    text_painter.setFont(font);
    text_painter.drawText(QPointF(105,675),data.name);

    text_painter.end();

    return true;
}*/


