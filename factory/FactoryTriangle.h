#ifndef FACTORYTRIANGLE_H
#define FACTORYTRIANGLE_H
#include "Factory.h"

class FactoryTriangle : public Factory
{
public:
    Shape* create(ShapeData const &data) override;
};

#endif // FACTORYTRIANGLE_H
