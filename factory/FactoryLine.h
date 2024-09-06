#ifndef FACTORYLINE_H
#define FACTORYLINE_H
#include "Factory.h"

class FactoryLine : public Factory
{
public:
    Shape* create(ShapeData const &data) override;
};


#endif // FACTORYLINE_H
