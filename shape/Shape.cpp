#include "Shape.h"

Shape::~Shape()
{

}

void Shape::setName(std::string const &name)
{
    shapeName = QString::fromStdString(name);
}

QString const &Shape::getName( void ) const
{
    return (shapeName);
}
