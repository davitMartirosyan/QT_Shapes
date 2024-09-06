#include "FactoryTriangle.h"

Shape* FactoryTriangle::create(ShapeData const &data)
{
    for(const auto& [key, value] : data.coord)
    {
        _xy.push_back(value.first); // x
        _xy.push_back(value.second);// y
    }
    QPen pen(Qt::black);
    pen.setWidth(2);
    QBrush brush(Qt::blue);
    if (_xy.size() >= 6)
        return (new Triangle(_xy[0],_xy[1],_xy[2],_xy[3], _xy[4], _xy[5], pen, brush));
    return (nullptr);
};
