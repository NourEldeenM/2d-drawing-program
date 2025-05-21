#ifndef DRAWINGALGORITHM_H
#define DRAWINGALGORITHM_H

#include <vector>
#include <raylib.h>

struct Point
{
    int x, y;
};

class DrawingAlgorithm
{
    char * name;
    int requiredPoints;

public:
    char * getName() {
        return name;
    }
    void setName(char *n) {
        name = n;
    }

    int getRequiredPoints() {
        return requiredPoints;
    }

    void setRequiredPoints(int rp) {
        requiredPoints = rp;
    }
    
    virtual std::vector<std::pair<Point, Color>> draw(std::vector<Point> &inputPoints, std::vector<Color> drawingColors = {BLACK}) = 0;
    virtual ~DrawingAlgorithm() = default;
};

#endif