#ifndef RECT_H
#define RECT_H
#include "Shape.h"

class Rect : public Shape
{
private:
    double x1, y1, x2, y2;
public:
    Rect(double x1, double y1, double x2, double y2, const QPen &pen, const QBrush& brush);
    virtual void draw(QGraphicsScene *scene) override;
};


#endif // RECT_H
