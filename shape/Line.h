#ifndef LINE_H
#define LINE_H
#include "Shape.h"

class Line : public Shape
{
public:
    Line( void );
    ~Line();
public:
    virtual void draw() const;
};

#endif // LINE_H
