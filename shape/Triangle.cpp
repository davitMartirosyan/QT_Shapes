#include "Triangle.h"

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3, const QPen &pen, const QBrush &brush)
    : Shape(pen, brush), x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3)
{

}

void Triangle::draw(QGraphicsScene *scene)
{
    QPolygonF poly;
    poly << QPointF(x1, y1)
         << QPointF(x2, y2)
         << QPointF(x3, y3);
    QGraphicsPolygonItem *triangle = new QGraphicsPolygonItem(poly);
    triangle->setPen(pen);
    triangle->setBrush(brush);
    scene->addItem(triangle);
}
