#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QMainWindow>
#include "location.h"
#include "infodata.h"
class QMdiArea;
class MdiSubWindow;

class PreviewWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PreviewWindow(QWidget *parent = 0);
    ~PreviewWindow();

    Location getLocation();

signals:

public slots:
    void saveRects();
    //void loadSettings();

private:
    QMdiArea     *mdiarea;
    MdiSubWindow *mdi_photo;
    MdiSubWindow *mdi_barCode;
    MdiSubWindow *mdi_name1;
    MdiSubWindow *mdi_collage;
    MdiSubWindow *mdi_major;
    MdiSubWindow *mdi_layer;
    MdiSubWindow *mdi_date1;
    MdiSubWindow *mdi_date2;
    MdiSubWindow *mdi_barCodeText;
    MdiSubWindow *mdi_siasLabel;
    MdiSubWindow *mdi_name2;

    Location     *rects;

    void loadInit();


};

#endif // PREVIEWWINDOW_H
