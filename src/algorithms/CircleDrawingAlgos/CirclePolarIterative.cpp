#include "../DrawingAlgorithm.h"
// #include <windows.h>
#include <cmath>
#include <vector>
#include "CirclePoint.cpp"

using namespace std;

class CirclePolarIterativeAlgorithm : public DrawingAlgorithm
{
public:
    CirclePolarIterativeAlgorithm() {
        setName((char*)"Circle Polar Iterative");
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
        double thetaInc = 1.0 / radius;
        double sinTheta = sin(thetaInc), cosTheta = cos(thetaInc);
        double x = radius, y = 0;
        vector<Point> points;
        DrawCirclePoints(center, {static_cast<int>(x), static_cast<int>(y)}, points);
        while (x > y)
        {
            double temp = x * cosTheta - y * sinTheta;
            y = x * sinTheta + y * cosTheta;
            x = temp;
            DrawCirclePoints(center, {static_cast<int>(round(x)), static_cast<int>(round(y))}, points);
        }
        Color color = drawingColors.empty() ? BLACK : drawingColors[0];
        for (const auto &p : points)
            result.push_back({p, color});
        return result;
    }
};
