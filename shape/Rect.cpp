#include "Rect.h"

Rect::Rect(double x1, double y1, double x2, double y2, const QPen &pen, const QBrush &brush) : Shape(pen, brush), x1(x1), y1(y1), x2(x2), y2(y2)
{

}

void Rect::draw(QGraphicsScene *scene)
{
    scene->addRect(x1, y1, x2, y2, pen, brush);
}
