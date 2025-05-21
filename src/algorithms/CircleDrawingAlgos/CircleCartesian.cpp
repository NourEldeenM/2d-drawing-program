#include "../DrawingAlgorithm.h"
#include <cmath>
#include <vector>
// #include "CirclePoint.cpp"

using namespace std;

class CircleCartesianAlgorithm : public DrawingAlgorithm
{
public:
    CircleCartesianAlgorithm()
    {
        setName((char *)"Circle Cartesian");
        setRequiredPoints(2);
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {BLACK}) override
    {
        vector<pair<Point, Color>> result;
        if (pts.size() < 2)
            return result;
        Point center = pts[0];
        Point point = pts[1];
        int radius = static_cast<int>(sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2)));
        int x = 0, y = radius;
        vector<Point> points;
        DrawCirclePoints(center, {x, y}, points);
        while (x < y)
        {
            ++x;
            y = round(sqrt(radius * radius - x * x));
            DrawCirclePoints(center, {x, y}, points);
        }
        Color color = drawingColors.empty() ? BLACK : drawingColors[0];
        for (const auto &p : points)
            result.push_back(make_pair(p, color));
        return result;
    }
};
