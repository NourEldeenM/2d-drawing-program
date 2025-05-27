#include "../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
using namespace std;

class EllipseCartesianAlgorithm : public DrawingAlgorithm {
public:
    EllipseCartesianAlgorithm() {
        setName((char*)"Ellipse Cartesian");
        setRequiredPoints(3);
    }
    vector<pair<Point, Color>> draw(vector<Point>& pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.size() < 3) return result;
        Point center = pts[0];
        Point p1 = pts[1], p2 = pts[2];
        int a = abs(p1.x - center.x);
        int b = abs(p2.y - center.y);
        int x = 0, y = b;
        Color color = drawingColors.empty() ? BLACK : drawingColors.back();
        DrawEllipsePoints(center, {x, y}, color, result);
        while (x < a){
            ++x;
            y = round(sqrt((1.0 - (double)(x * x) / (a * a))) * b);
            DrawEllipsePoints(center, {x, y}, color, result);
        }
        x = a, y = 0;
        while (y < b){
            ++y;
            x = round(sqrt((1.0 - (double)(y * y) / (b * b))) * a);
            DrawEllipsePoints(center, {x, y}, color, result);
        }
        return result;
    }
};
