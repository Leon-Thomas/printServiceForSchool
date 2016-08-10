#include <QMdiArea>
#include <QFont>
#include <QPushButton>
#include <QFontDatabase>
#include <QSettings>
#include <QDebug>

#include "previewwindow.h"
#include "mdisubwindow.h"
#include "location.h"

PreviewWindow::PreviewWindow(QWidget *parent)
    : QMainWindow(parent)
{ 
    //A4 width
    this->setFixedWidth(793);
    this->resize(793,1123);
    //mdirArea
    mdiarea = new QMdiArea();
    this->setCentralWidget(mdiarea);
    //location
    this->rects = new Location();
    //Initialize
    loadInit();

    //connect(posButton, &QPushButton::clicked, this, &PreviewWindow::saveRects);

}

PreviewWindow::~PreviewWindow()
{
    this->saveRects();
}

Location PreviewWindow::getLocation()
{
    return Location(*rects);
}

void PreviewWindow::saveRects()
{
    QSettings settings(tr("settings.ini"),QSettings::IniFormat);
    QPoint offset(13,13);
    this->rects->rect_photo       = QRect(this->mdi_photo->pos()   - offset ,this->mdi_photo->size());
    this->rects->rect_barCode     = QRect(this->mdi_barCode->pos() - offset ,this->mdi_barCode->size());
    this->rects->rect_name1       = QRect(this->mdi_name1->pos()   - offset ,this->mdi_name1->size());
    this->rects->rect_collage     = QRect(this->mdi_collage->pos() - offset ,this->mdi_collage->size());
    this->rects->rect_major       = QRect(this->mdi_major->pos()   - offset ,this->mdi_major->size());
    this->rects->rect_layer       = QRect(this->mdi_layer->pos()   - offset ,this->mdi_layer->size());
    this->rects->rect_date1       = QRect(this->mdi_date1->pos()   - offset ,this->mdi_date1->size());
    this->rects->rect_date2       = QRect(this->mdi_date2->pos()       - offset ,this->mdi_date2->size());
    this->rects->rect_barCodeText = QRect(this->mdi_barCodeText->pos() - offset ,this->mdi_barCodeText->size());
    this->rects->rect_siasLabel   = QRect(this->mdi_siasLabel->pos()   - offset ,this->mdi_siasLabel->size());
    this->rects->rect_name2       = QRect(this->mdi_name2->pos()       - offset ,this->mdi_name2->size());
    this->rects->date1  = mdi_date1->getText();
    this->rects->date2  = mdi_date2->getText();
    settings.beginGroup("previewwindow");
    settings.setValue("rect_photo"      ,QRect(this->mdi_photo->pos()        ,this->mdi_photo->size()       ));
    settings.setValue("rect_barCode    ",QRect(this->mdi_barCode->pos()      ,this->mdi_barCode->size()     ));
    settings.setValue("rect_name1      ",QRect(this->mdi_name1->pos()        ,this->mdi_name1->size()       ));
    settings.setValue("rect_collage    ",QRect(this->mdi_collage->pos()      ,this->mdi_collage->size()     ));
    settings.setValue("rect_major      ",QRect(this->mdi_major->pos()        ,this->mdi_major->size()       ));
    settings.setValue("rect_layer      ",QRect(this->mdi_layer->pos()        ,this->mdi_layer->size()       ));
    settings.setValue("rect_date1      ",QRect(this->mdi_date1->pos()        ,this->mdi_date1->size()       ));
    settings.setValue("text_date1      ",mdi_date1->getText()   );
    settings.setValue("rect_date2      ",QRect(this->mdi_date2->pos()        ,this->mdi_date2->size()       ));
    settings.setValue("text_date2      ",mdi_date2->getText()   );
    settings.setValue("rect_barCodeText",QRect(this->mdi_barCodeText->pos()  ,this->mdi_barCodeText->size() ));
    settings.setValue("rect_siasLabel  ",QRect(this->mdi_siasLabel->pos()    ,this->mdi_siasLabel->size()   ));
    settings.setValue("rect_name2      ",QRect(this->mdi_name2->pos()        ,this->mdi_name2->size()       ));
    settings.endGroup();
}

void PreviewWindow::loadInit()
{
    QSettings settings("settings.ini",QSettings::IniFormat);
    QRect initR(0,0,50,30);


    //midwindows
    mdi_photo = new MdiSubWindow(PHOTO);
    mdi_barCode = new MdiSubWindow(TEXT,tr("1610001"));
    mdi_name1        = new MdiSubWindow(TEXT,tr("姓名"));
    mdi_collage      = new MdiSubWindow(TEXT,tr("电子信息工程学院"));
    mdi_major        = new MdiSubWindow(TEXT,tr("计算机科学与技术（**方向）"));
    mdi_layer        = new MdiSubWindow(TEXT,tr("本科"));
    mdi_date1        = new MdiSubWindow(TEXT,tr("七"));
    mdi_date2        = new MdiSubWindow(TEXT,tr("十五"));
    QFont barCodefont;
    int fid = QFontDatabase::addApplicationFont(QString("SIAS_OK.TTF"));
    if(fid != -1)
    {
        QStringList flist = QFontDatabase::applicationFontFamilies(fid);
        if(flist.size())
        {
            QFont tmp(flist[0]);
            barCodefont = tmp;
        }
    }

    mdi_barCodeText  = new MdiSubWindow(TEXT,tr("1510001"),barCodefont);
    mdi_siasLabel    = new MdiSubWindow(TEXT,tr("郑州大学西亚斯国际学院某某某"));
    mdi_name2        = new MdiSubWindow(TEXT,tr("姓名"));

    mdiarea->addSubWindow(this->mdi_photo      );
    mdiarea->addSubWindow(this->mdi_barCode    );
    mdiarea->addSubWindow(this->mdi_name1      );
    mdiarea->addSubWindow(this->mdi_collage    );
    mdiarea->addSubWindow(this->mdi_major      );
    mdiarea->addSubWindow(this->mdi_layer      );
    mdiarea->addSubWindow(this->mdi_date1      );
    mdiarea->addSubWindow(this->mdi_date2      );
    mdiarea->addSubWindow(this->mdi_barCodeText);
    mdiarea->addSubWindow(this->mdi_siasLabel  );
    mdiarea->addSubWindow(this->mdi_name2      );

    settings.beginGroup("previewwindow");
    mdi_photo      ->setGeometry(settings.value("rect_photo      ",initR).toRect());
    mdi_barCode    ->setGeometry(settings.value("rect_barCode    ",initR).toRect());
    mdi_name1      ->setGeometry(settings.value("rect_name1      ",initR).toRect());
    mdi_collage    ->setGeometry(settings.value("rect_collage    ",initR).toRect());
    mdi_major      ->setGeometry(settings.value("rect_major      ",initR).toRect());
    mdi_layer      ->setGeometry(settings.value("rect_layer      ",initR).toRect());
    mdi_date1      ->setGeometry(settings.value("rect_date1      ",initR).toRect());
    mdi_date1      ->setText(settings.value("text_date1      "    ,tr("date1")).toString());
    mdi_date2      ->setGeometry(settings.value("rect_date2      ",initR).toRect());
    mdi_date2      ->setText(settings.value("text_date2      "    ,tr("date2")).toString());
    mdi_barCodeText->setGeometry(settings.value("rect_barCodeText",initR).toRect());
    mdi_siasLabel  ->setGeometry(settings.value("rect_siasLabel  ",initR).toRect());
    mdi_name2      ->setGeometry(settings.value("rect_name2      ",initR).toRect());

    settings.endGroup();
}




