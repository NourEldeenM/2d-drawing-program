#include "../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
using namespace std;

class QuadraticCurveAlgorithm : public DrawingAlgorithm {
public:
    QuadraticCurveAlgorithm() {
        setName((char*)"Quadratic Curve");
        setRequiredPoints(3);
    }
    vector<pair<Point, Color>> draw(vector<Point>& pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.size() < 3)
            return result;
        Point p0 = pts[0], p1 = pts[1], p2 = pts[2];
        vector<Point> points;
        for (double t = 0; t <= 1.0; t += 0.001) {
            double x = pow(1 - t, 2) * p0.x + 2 * (1 - t) * t * p1.x + pow(t, 2) * p2.x;
            double y = pow(1 - t, 2) * p0.y + 2 * (1 - t) * t * p1.y + pow(t, 2) * p2.y;
            points.push_back({static_cast<int>(round(x)), static_cast<int>(round(y))});
        }
        Color color = drawingColors.empty() ? BLACK : drawingColors.back();
        for (const auto& p : points) result.push_back({p, color});
        return result;
    }
};
