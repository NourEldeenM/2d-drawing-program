#ifndef DRAWINGALGORITHM_H
#define DRAWINGALGORITHM_H

#include <vector>

struct Point
{
    int x, y;
};

class DrawingAlgorithm
{
public:
    virtual std::vector<Point> draw(std::vector<Point> &inputPoints) = 0;
    virtual ~DrawingAlgorithm() = default;
};

#endif // DUMMYCLASS_H