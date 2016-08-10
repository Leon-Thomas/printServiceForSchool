#ifndef PRINTWORKER_H
#define PRINTWORKER_H

#include <QObject>
#include <QQueue>
#include <QList>
#include "infodata.h"
#include "location.h"

class QFont;

class PrintWorker : public QObject
{
    Q_OBJECT
public:
    explicit PrintWorker(QObject *parent = 0);

    void setPhotosPath(const QString &srcdir);
    //void setBarCodesPath(const QString &srcdir);
    void setOutFileName(const QString &filename);
    void setLocations(const Location &l);
    void appendDataToQueue(QList<InfoData> &data_list);

signals:
    void unitFinished(uint num_finished);
    void allFinished();

public slots:
    bool doPrint();
    //    void pereview(QPrinter *printer);
    //    bool generatePdf();

private:

    QQueue<InfoData> print_queue;

    QString photosPath;
    //QString barCodePath;
    QString outFileName;
    Location *rects;

    QFont *barCodefont;

};

#endif // PRINTWORKER_H
