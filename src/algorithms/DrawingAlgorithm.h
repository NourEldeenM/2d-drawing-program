#ifndef DRAWINGALGORITHM_H
#define DRAWINGALGORITHM_H

#include <vector>
#include <raylib.h>

struct Point
{
    int x, y;
};

inline void DrawCirclePoints(Point center, Point p, std::vector<Point> &points)
{
    int dx[] = {p.x, -p.x, p.x, -p.x, p.y, -p.y, p.y, -p.y};
    int dy[] = {p.y, p.y, -p.y, -p.y, p.x, p.x, -p.x, -p.x};
    for (int i = 0; i < 8; i++)
        points.push_back({center.x + dx[i], center.y + dy[i]});
}

class DrawingAlgorithm
{
    char *name;
    int requiredPoints;

public:
    char *getName()
    {
        return name;
    }
    void setName(char *n)
    {
        name = n;
    }

    int getRequiredPoints()
    {
        return requiredPoints;
    }

    void setRequiredPoints(int rp)
    {
        requiredPoints = rp;
    }

    virtual std::vector<std::pair<Point, Color>> draw(std::vector<Point> &inputPoints, std::vector<Color> drawingColors = {BLACK}) = 0;
    virtual ~DrawingAlgorithm() = default;
};

#endif