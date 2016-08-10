#ifndef QUERY_H
#define QUERY_H

#include "infodata.h"
#include <QList>


class Query
{
public:
    Query();
    ~Query();
    bool init();

    QList<InfoData> find_num(int n);
    QList<InfoData> find_nums(int m, int n);
    QList<InfoData> getAllData();

    void setAbsoluteFilePath(QString& str);
    void setAbsolutePath(QString& str);
    void setBaseName(QString& str);
    void setDreiveToExcel(QString& str);
    QString &getBaseName();
    int getSizeofList();
    bool hasData();
    void createExcel();

private:
    QList<InfoData> data_list;
    QString data_absoluteFilePath;
    QString data_absolutePath;
    QString data_baseName;
    QString dataDreiveToExcel;
};

#endif // QUERY_H

