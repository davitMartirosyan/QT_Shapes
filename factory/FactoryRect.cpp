#include "FactoryRect.h"

Shape* FactoryRect::create(ShapeData const &data)
{
    for(const auto& [key, value] : data.coord)
    {
        _xy.push_back(value.first); // x
        _xy.push_back(value.second);// y
    }
    QPen pen(Qt::black);
    pen.setWidth(2);
    QBrush brush(Qt::blue);
    if (_xy.size() >= 4)
        return (new Rect(_xy[0],_xy[1],_xy[2],_xy[3], pen, brush));
    return (nullptr);
};
