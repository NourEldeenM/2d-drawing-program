#include "../DrawingAlgorithm.h"
#include <cmath>
#include <vector>
#include "CirclePoint.cpp"

using namespace std;

#ifndef CIRCLE_MID_POINT_DDA_MODIFIED_ALGORITHM_CPP
#define CIRCLE_MID_POINT_DDA_MODIFIED_ALGORITHM_CPP

class CircleMidPointDDAModifiedAlgorithm : public DrawingAlgorithm
{
public:
    CircleMidPointDDAModifiedAlgorithm()
    {
        setName((char *)"Circle Mid Point DDA Modified");
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
        int x = 0, y = radius, d = 1 - radius;
        int d1 = 3, d2 = ((x - y) << 1) + 5;
        Color color = drawingColors.empty() ? BLACK : drawingColors.back();
        DrawCirclePoints(center, {x, y}, color, result);
        while (x < y)
        {
            if (d < 0)
                d += d1,
                    d2 += 2;
            else
                --y,
                    d += d2,
                    d2 += 4;
            ++x;
            d1 += 2;
            DrawCirclePoints(center, {x, y}, color, result);
        }
        return result;
    }
};

#endif // CIRCLE_MID_POINT_DDA_MODIFIED_ALGORITHM_CPP