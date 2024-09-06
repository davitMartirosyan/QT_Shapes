#ifndef LINE_H
#define LINE_H
#include "Shape.h"

class Line : public Shape
{
private:
    double x1, y1, x2, y2;
public:
    Line(double x1, double y1, double x2, double y2, const QPen& pen, const QBrush &brush);
    virtual void draw(QGraphicsScene *scene) override;
};


#endif // LINE_H
