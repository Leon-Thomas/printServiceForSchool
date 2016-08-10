#ifndef LOCATION_H
#define LOCATION_H
#include <QRect>
class Location
{
public:
    Location() {}
    Location(const Location &l)
    {
        copy(l);
    }
    Location &operator =(const Location &l)
    {
        copy(l);
        return *this;
    }
    ~Location() {}

    QRect rect_photo;
    QRect rect_barCode;
    QRect rect_name1;
    QRect rect_collage;
    QRect rect_major;
    QRect rect_layer;
    QRect rect_date1;
    QRect rect_date2;
    QRect rect_barCodeText;
    QRect rect_siasLabel;
    QRect rect_name2;
    QString date1;
    QString date2;
private:
    void copy(const Location &l){
        rect_photo          =   l.rect_photo      ;
        rect_barCode        =   l.rect_barCode    ;
        rect_name1          =   l.rect_name1      ;
        rect_collage        =   l.rect_collage    ;
        rect_major          =   l.rect_major      ;
        rect_layer          =   l.rect_layer      ;
        rect_date1          =   l.rect_date1      ;
        rect_date2          =   l.rect_date2      ;
        rect_barCodeText    =   l.rect_barCodeText;
        rect_siasLabel      =   l.rect_siasLabel  ;
        rect_name2          =   l.rect_name2      ;
        date1               =   l.date1;
        date2               =   l.date2;
    }

};

#endif // LOCATION_H

