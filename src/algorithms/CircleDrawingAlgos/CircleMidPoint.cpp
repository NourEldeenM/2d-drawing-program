#include "../DrawingAlgorithm.h"
#include <cmath>
#include <vector>
#include "DrawCirclePoint.cpp"

using namespace std;

class DrawCircleMidPoint : public DrawingAlgorithm {
public:
    vector<pair<Point, Color>> draw(vector<Point>& pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.size() < 2)
            return result;
        Point center = pts[0];
        Point point = pts[1];
        int radius = static_cast<int>(sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2)));
        int x = 0, y = radius;
        vector<Point> points;
        DrawPoints(center, {x, y}, points);
        while (x < y){
            double d = (x + 1) * (x + 1) + (y - 0.5) * (y - 0.5) - radius * radius;
            x++;
            if (d > 0)
                y--;
            DrawPoints(center, {x, y}, points);
        }
        Color color = drawingColors.empty() ? BLACK : drawingColors[0];
        for (const auto& p : points) result.push_back({p, color});
        return result;
    }
};
