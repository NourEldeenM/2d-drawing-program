#include "../DrawingAlgorithm.h"
#include <cmath>
#include <vector>
#include "CirclePoint.cpp"

using namespace std;

class CircleMidPointAlgorithm : public DrawingAlgorithm {
public:
    CircleMidPointAlgorithm() {
        setName((char*)"Circle Mid Point");
        setRequiredPoints(2);
    }
    vector<pair<Point, Color>> draw(vector<Point>& pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.size() < 2)
            return result;
        Point center = pts[0];
        Point point = pts[1];
        int radius = static_cast<int>(sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2)));
        int x = 0, y = radius;
        Color color = drawingColors.empty() ? BLACK : drawingColors.back();
        DrawCirclePoints(center, {x, y}, color, result);
        while (x < y){
            double d = (x + 1) * (x + 1) + (y - 0.5) * (y - 0.5) - radius * radius;
            x++;
            if (d > 0)
                y--;
            DrawCirclePoints(center, {x, y}, color, result);
        }
        return result;
    }
};
