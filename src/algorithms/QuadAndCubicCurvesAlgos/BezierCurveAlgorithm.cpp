#include "BezierCurveAlgorithm.h"

BezierCurveAlgorithm::BezierCurveAlgorithm() {
    setName((char*)"Bezier Curve");
    setRequiredPoints(4);
}

vector<pair<Point, Color>> BezierCurveAlgorithm::draw(vector<Point>& pts, vector<Color> drawingColors) {
    vector<pair<Point, Color>> result;
    if (pts.size() < 4)
        return result;

    Point p0 = pts[0], p1 = pts[1], p2 = pts[2], p3 = pts[3];
    vector<Point> points;

    for (double t = 0; t <= 1.0; t += 0.001) {
        double x = pow(1 - t, 3) * p0.x + 3 * pow(1 - t, 2) * t * p1.x + 3 * (1 - t) * pow(t, 2) * p2.x + pow(t, 3) * p3.x;
        double y = pow(1 - t, 3) * p0.y + 3 * pow(1 - t, 2) * t * p1.y + 3 * (1 - t) * pow(t, 2) * p2.y + pow(t, 3) * p3.y;
        points.push_back({static_cast<int>(round(x)), static_cast<int>(round(y))});
    }

    Color color = drawingColors.empty() ? BLACK : drawingColors.back();

    for (const auto& p : points)
        result.push_back({p, color});

    return result;
}
