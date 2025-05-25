#include "../DrawingAlgorithm.h"
#include <cmath>
#include <vector>
#include "CirclePoint.cpp"

using namespace std;

class CircleMidPointDDAAlgorithm : public DrawingAlgorithm
{
public:
    CircleMidPointDDAAlgorithm()
    {
        setName((char *)"Circle Mid Point DDA");
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
        int d = 1 - radius;
        Color color = drawingColors.empty() ? BLACK : drawingColors[0];
        DrawCirclePoints(center, {x, y}, color, result);
        while (x < y)
        {
            if (d < 0)
                d += (x << 1) + 3;
            else
                d += ((x - y) << 1) + 5,
                    --y;
            ++x;
            DrawCirclePoints(center, {x, y}, color, result);
        }
        return result;
    }
};
