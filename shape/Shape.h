#ifndef SHAPE_H
#define SHAPE_H
#include <QString>
#include <QVector>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QGraphicsView>

class Shape
{
protected:
    QPen pen;
    QBrush brush;
public:
    Shape(const QPen &pen, const QBrush &brush);
    virtual void draw(QGraphicsScene *scene) = 0;
    virtual ~Shape() = default;
};

#endif // SHAPE_H
