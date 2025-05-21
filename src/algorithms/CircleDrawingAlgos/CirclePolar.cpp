#include "../DrawingAlgorithm.h"
// #include <windows.h>
#include <cmath>
#include <vector>
#include "CirclePoint.cpp"

using namespace std;

class CirclePolarAlgorithm : public DrawingAlgorithm
{
public:
    CirclePolarAlgorithm()
    {
        setName((char *)"Circle Polar");
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
        double theta = 0, piOver4 = 3.14159 / 4, thetaInc = 1.0 / radius;
        vector<Point> points;
        while (theta < piOver4)
        {
            int x = round(radius * cos(theta));
            int y = round(radius * sin(theta));
            DrawCirclePoints(center, {x, y}, points);
            theta += thetaInc;
        }
        Color color = drawingColors.empty() ? BLACK : drawingColors[0];
        for (const auto &p : points)
            result.push_back({p, color});
        return result;
    }
};
