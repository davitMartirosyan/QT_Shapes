#ifndef FACTORYRECT_H
#define FACTORYRECT_H
#include "Factory.h"

class FactoryRect : public Factory
{
public:
    Shape* create(ShapeData const &data) override;
};

#endif // FACTORYRECT_H
