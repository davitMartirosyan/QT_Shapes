#ifndef SHAPE_H
#define SHAPE_H
#include <QString>
#include <QVector>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QGraphicsView>


class Shape
{
public:
    ~Shape();

private:
    QString shapeName;
    QVector<int> coord;
private:
    int coordCount;
public:
    QString const &getName( void ) const;

public:
    void setName(std::string const &name);

public:
    virtual void draw() const = 0;
};

#endif // SHAPE_H
