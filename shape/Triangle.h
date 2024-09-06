#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"

class Triangle : public Shape
{
private:
    double x1, y1, x2, y2, x3, y3;
public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3, const QPen &pen, const QBrush &brush);
    virtual void draw(QGraphicsScene *scene) override;
};

#endif // TRIANGLE_H
