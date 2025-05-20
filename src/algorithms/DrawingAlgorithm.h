#ifndef DRAWINGALGORITHM_H
#define DRAWINGALGORITHM_H

#include <vector>

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
    
    virtual std::vector<Point> draw(std::vector<Point> &inputPoints) = 0;
    virtual ~DrawingAlgorithm() = default;
};

#endif