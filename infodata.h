#ifndef INFODATA_H
#define INFODATA_H
#include <QObject>

class InfoData
{
public:
    InfoData()
    {
        cid            = QString("");
        college        = QString("");
        name           = QString("");
        major          = QString("");
        leyar          = QString("");
        barCode        = QString("");
        //        date1           = QObject::trUtf8("七");
        //        date2           = QObject::trUtf8("十四");
        siasLabel      = QObject::trUtf8("郑州大学西亚斯国际学院");
    }

    ~InfoData() {}


    QString cid;        //考生号
    QString name;       //名字
    QString college;    //学院名
    QString major;      //专业名
    QString leyar;      //层次:本科、专科
    QString barCode;    //条形码号
    //    QString date1;
    //    QString date2;
    QString siasLabel;
    QString sex;
    QString telephoneNumber;

};

#endif // INFODATA_H
