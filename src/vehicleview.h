#ifndef VEHICLEVIEW_H
#define VEHICLEVIEW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

class Vehicle;
class Drawable;


class VehicleView : public QGraphicsEllipseItem
{
public:
    VehicleView(Drawable* d,Vehicle* v,qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event)override;


private:
    Drawable* drawable;
    Vehicle* vehicle;
    QGraphicsTextItem txt;
};

#endif // VEHICLEVIEW_H
