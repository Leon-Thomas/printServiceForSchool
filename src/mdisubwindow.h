#ifndef MDISUBWINDOW_H
#define MDISUBWINDOW_H

typedef enum{
    NONE,
    PHOTO,
    TEXT
}MdiType;

#include <QMdiSubWindow>

class MdiSubWindow : public QMdiSubWindow
{
public:
    MdiSubWindow(MdiType paint_type = NONE,const QString &def_text = QString("HelloWrold"),const QFont &f= QFont(),
                 QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

    ~MdiSubWindow();

    void setPhotoPath(const QString filename);
    void setText(const QString &str,const QFont &font = QFont());
    QString getText();

protected:
    void paintEvent(QPaintEvent *paintEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent *keyEvent);
    void mouseDoubleClickEvent(QMouseEvent *mouseEvent);



private:
    MdiType     type;
    QPoint      mv_pos;
    QString     fullname;
    QFont       font;
    QString     content;

    void paintPhoto();
    void paintText();

};

#endif // MDISUBWINDOW_H
