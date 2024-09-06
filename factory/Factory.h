#ifndef FACTORY_H
#define FACTORY_H
#include "shape/ShapeData.h"
#include "shape/Shape.h"
#include "shape/Line.h"
#include "shape/Rect.h"
#include "shape/Triangle.h"

class Factory
{
protected:
    std::vector<double> _xy;
public:
    virtual Shape* create(ShapeData const &data) = 0;
    virtual ~Factory() = default;
};

#endif // FACTORY_H
