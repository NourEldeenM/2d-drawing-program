#include "../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
using namespace std;

#ifndef HERMITECURVEALGORITHM_H
#define HERMITECURVEALGORITHM_H

class HermiteCurveAlgorithm : public DrawingAlgorithm
{
public:
    HermiteCurveAlgorithm()
    {
        setName((char *)"Hermite Curve");
        setRequiredPoints(4);
    }
    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {BLACK}) override
    {
        vector<pair<Point, Color>> result;
        if (pts.size() < 4)
            return result;

        // P0 and P3 are the endpoints, P1 and P2 are the tangent vectors
        Point p0 = pts[0], p1 = pts[1], p2 = pts[2], p3 = pts[3];

        // Calculate tangent vectors
        double u1 = p1.x - p0.x, v1 = p1.y - p0.y; // tangent at start
        double u2 = p2.x - p3.x, v2 = p2.y - p3.y; // tangent at end

        // Hermite basis matrix H
        // | 2  1 -2  1 |
        // |-3 -2  3 -1 |
        // | 0  1  0  0 |
        // | 1  0  0  0 |
        // Cx = H * gx, gx = [x1, u1, x2, u2]^T
        double Cx[4];
        Cx[0] = 2 * p0.x + 1 * u1 - 2 * p3.x + 1 * u2;
        Cx[1] = -3 * p0.x - 2 * u1 + 3 * p3.x - 1 * u2;
        Cx[2] = 0 * p0.x + 1 * u1 + 0 * p3.x + 0 * u2;
        Cx[3] = 1 * p0.x + 0 * u1 + 0 * p3.x + 0 * u2;

        // Cy = H * gy, gy = [y1, v1, y2, v2]^T
        double Cy[4];
        Cy[0] = 2 * p0.y + 1 * v1 - 2 * p3.y + 1 * v2;
        Cy[1] = -3 * p0.y - 2 * v1 + 3 * p3.y - 1 * v2;
        Cy[2] = 0 * p0.y + 1 * v1 + 0 * p3.y + 0 * v2;
        Cy[3] = 1 * p0.y + 0 * v1 + 0 * p3.y + 0 * v2;

        vector<Point> points;
        for (double t = 0; t <= 1.0; t += 0.001)
        {
            double t2 = t * t;
            double t3 = t2 * t;

            double x = Cx[0] * t3 + Cx[1] * t2 + Cx[2] * t + Cx[3];
            double y = Cy[0] * t3 + Cy[1] * t2 + Cy[2] * t + Cy[3];

            points.push_back({static_cast<int>(round(x)), static_cast<int>(round(y))});
        }

        Color color = drawingColors.empty() ? BLACK : drawingColors[0];
        for (const auto &p : points)
            result.push_back({p, color});
        return result;
    }
};

#endif