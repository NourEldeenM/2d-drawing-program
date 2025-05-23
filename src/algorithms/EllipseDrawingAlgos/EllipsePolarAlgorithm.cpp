#include "../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
using namespace std;

class EllipsePolarAlgorithm : public DrawingAlgorithm {
public:
    EllipsePolarAlgorithm() {
        setName((char*)"Ellipse Polar");
        setRequiredPoints(3);
    }
    vector<pair<Point, Color>> draw(vector<Point>& pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.size() < 3) return result;
        Point center = pts[0];
        Point p1 = pts[1], p2 = pts[2];
        int a = abs(p1.x - center.x);
        int b = abs(p2.y - center.y);
        vector<Point> points;
        for (double theta = 0; theta < M_PI / 2; theta += 0.001){
            int x = round(a * cos(theta));
            int y = round(b * sin(theta));
            DrawEllipsePoints(center, {x, y}, points);
        }
        Color color = drawingColors.empty() ? BLACK : drawingColors[0];
        for (const auto& p : points) result.push_back({p, color});
        return result;
    }
};
