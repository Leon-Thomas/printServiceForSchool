#include "query.h"

#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>

#include <QSqlError>
#include <QThread>

Query::Query()
{

}

Query::~Query()
{

}

bool Query::init()
{
    data_list.clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    const QString temp(QObject::trUtf8("郑州大学西亚斯国际学院"));

    QString url = QObject::trUtf8("Driver={Microsoft Excel Driver (*.xls)};Readonly=0;DriverId=790;Dbq=") +
            this->data_absoluteFilePath +
            QObject::trUtf8(";DefaultDir=") +
            this->data_absolutePath;

    db.setDatabaseName(url);

    QString sel = QObject::trUtf8("select 考生号,姓名,条形码号,学院,层次,录取专业,性别,联系电话 from [") + this->data_baseName + QObject::trUtf8("$]");
    if ( db.open()){
        //        qDebug() << db.tables();
        QSqlQuery query;
        query.exec(sel);

        while (query.next()) {
            InfoData temp_Infodata;
            temp_Infodata.cid             = query.value(0).toString();
            temp_Infodata.name            = query.value(1).toString();
            temp_Infodata.barCode         = query.value(2).toString();
            temp_Infodata.college         = query.value(3).toString();
            temp_Infodata.leyar           = query.value(4).toString();
            temp_Infodata.major           = query.value(5).toString();
            temp_Infodata.sex             = query.value(6).toString();
            temp_Infodata.telephoneNumber = query.value(7).toString();

            temp_Infodata.siasLabel  = temp + temp_Infodata.name;
            //            for(int i = 0; i < 1000; ++i )
            this->data_list.append(temp_Infodata);
        }
    }
    else {
        QMessageBox::critical(0, "警告","打开数据库失败");
        QMessageBox::critical(0, "警告","请先选择资源文件路径！！！");
        return false;
    }

    db.close();
    return true;
}


QList<InfoData> Query::find_num(int n)
{
    QList<InfoData> que;
    que.append(data_list[n-1]);
    return que;
}


QList<InfoData> Query::find_nums(int m, int n)
{
    QList<InfoData> que;

    for(int i = m; i <= n; ++i)
        que.append(data_list[i-1]);
    return que;
}


void Query::setAbsoluteFilePath(QString& str)
{
    this->data_absoluteFilePath = str;
}

void Query::setAbsolutePath(QString& str)
{
    this->data_absolutePath = str;
}

void Query::setBaseName(QString& str)
{
    this->data_baseName = str;
}

void Query::setDreiveToExcel(QString &str)
{
    this->dataDreiveToExcel = str;
}

QString&  Query::getBaseName()
{
    return this->data_baseName;
}

QList<InfoData> Query::getAllData()
{
    return QList<InfoData> (this->data_list);
}

int  Query::getSizeofList()
{
    return this->data_list.size();
}

bool Query::hasData()
{
    return (!data_list.isEmpty());
}

void Query::createExcel()
{
    QString sSql;

    QSqlDatabase db2 = QSqlDatabase::addDatabase("QODBC","excelexport");
    if( !db2.isValid())
    {
        qDebug() << "excel is not valid.";
        return;   //! type error
    }
    else
        qDebug() << "db2.";

    if(!QSqlDatabase::drivers().contains("QODBC"))
    {
        QMessageBox::information(NULL, "tip", "System can't install ODBC driver!");
        return;
    }
    else
        qDebug() << "odbc";
    QString name = this->data_baseName + "导出表";
    QString dir = this->dataDreiveToExcel;
    QString dbq = dir + "/" +name;
    QString dbName = QObject::trUtf8("Driver={Microsoft Excel Driver (*.xls)};Readonly=0;DriverId=790;Dbq=") + dbq + QObject::trUtf8(";DefaultDir=") + dir;
    db2.setDatabaseName(dbName);

    QSqlQuery query(db2);
    // open connection
    if( !db2.open())
    {
        qDebug()<<"error";
        QString err = QObject::trUtf8("打开库失败\n");
        QMessageBox::critical(NULL,QObject::trUtf8("打开失败"),err,QMessageBox::Yes,QMessageBox::Yes);
        return;  //! db error
    }

    sSql = "CREATE TABLE [" + name + QObject::trUtf8("] (序号 varchar(200), 考生号 varchar(200), 姓名 varchar(200), 性别 varchar(200), 电话 varchar(200), 录取专业 varchar(200), 条码号 varchar(200))");

    if( !query.exec(sSql))
    {
        qDebug() << query.lastError();
        QMessageBox::critical(0, "警告","文件已存在,请重新选择导出路径");
        db2.close();
        return;
    }
    else
        qDebug() << "create xls OK.";

    int j = data_list.size();

    for (int i = 0; i < j; i++)
    {
        QString sql;
        sql = "INSERT INTO [" + name + "$] VALUES(" +  "'" + QString::number(i+1) + "'" + ","
                + "'" + data_list[i].cid + "'" + "," + "'" + data_list[i].name + "'" + "," + "'" + data_list[i].sex + "'" +
                "," + "'" + data_list[i].telephoneNumber + "'" + "," + "'" + data_list[i].major + "'" + "," + "'" + data_list[i].barCode + "'" + ")";
        if( !query.exec(sql))
        {
            qDebug() << query.lastError();
            db2.close();
            return;
        }
        if((int)(i*100000.000/j)%5000==0)
            QThread::usleep(1000);
    }

    qDebug() << "insert success";
    QMessageBox::information(0, "excel已生成","请查看"+name);

    db2.close();
}
