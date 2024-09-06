#include "Line.h"

Line::Line(double x1, double y1, double x2, double y2, const QPen &pen, const QBrush &brush) : Shape(pen, brush), x1(x1), y1(y1), x2(x2), y2(y2)
{

}

void Line::draw(QGraphicsScene *scene)
{
    scene->addLine(x1, y1, x2, y2, pen);
}
