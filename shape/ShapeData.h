#ifndef SHAPEDATA_H
#define SHAPEDATA_H
#include <string>
#include <unordered_map>
#include <vector>

struct ShapeData
{
    std::string shape;
    std::string name;
    std::string command;
    std::unordered_map<std::string, std::pair<double, double>> coord;
};

#endif // SHAPEDATA_H
