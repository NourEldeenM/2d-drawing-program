#include "../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
using namespace std;

class CardinalSplineAlgorithm : public DrawingAlgorithm
{
private:
    double tension; // Cardinal spline tension parameter

    vector<Point> drawHermiteCurve(Point p1, double u1, double v1, Point p2, double u2, double v2)
    {
        vector<Point> points;

        // Hermite basis matrix coefficients
        double Cx[4];
        Cx[0] = 2 * p1.x + 1 * u1 - 2 * p2.x + 1 * u2;
        Cx[1] = -3 * p1.x - 2 * u1 + 3 * p2.x - 1 * u2;
        Cx[2] = 0 * p1.x + 1 * u1 + 0 * p2.x + 0 * u2;
        Cx[3] = 1 * p1.x + 0 * u1 + 0 * p2.x + 0 * u2;

        double Cy[4];
        Cy[0] = 2 * p1.y + 1 * v1 - 2 * p2.y + 1 * v2;
        Cy[1] = -3 * p1.y - 2 * v1 + 3 * p2.y - 1 * v2;
        Cy[2] = 0 * p1.y + 1 * v1 + 0 * p2.y + 0 * v2;
        Cy[3] = 1 * p1.y + 0 * v1 + 0 * p2.y + 0 * v2;

        for (double t = 0; t <= 1.0; t += 0.01)
        {
            double t2 = t * t;
            double t3 = t2 * t;
            double x = Cx[0] * t3 + Cx[1] * t2 + Cx[2] * t + Cx[3];
            double y = Cy[0] * t3 + Cy[1] * t2 + Cy[2] * t + Cy[3];
            points.push_back({static_cast<int>(round(x)), static_cast<int>(round(y))});
        }
        return points;
    }

public:
    CardinalSplineAlgorithm(double t = 0.5) : tension(t)
    {
        setName((char *)"Cardinal Spline");
        setRequiredPoints(4);
    }

    void setTension(double t)
    {
        tension = t;
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {BLACK}) override
    {
        vector<pair<Point, Color>> result;
        int n = pts.size();

        if (n < 4)
            return result;

        double c = tension;
        double c1 = 1 - c;

        // First tangent: T0 = c1 * (P[2] - P[0])
        double T0x = c1 * (pts[2].x - pts[0].x);
        double T0y = c1 * (pts[2].y - pts[0].y);

        Color color = drawingColors.empty() ? BLACK : drawingColors.back();

        for (int i = 2; i < n - 1; i++)
        {
            // Next tangent: T1 = c1 * (P[i+1] - P[i-1])
            double T1x = c1 * (pts[i + 1].x - pts[i - 1].x);
            double T1y = c1 * (pts[i + 1].y - pts[i - 1].y);

            // Draw Hermite curve from P[i-1] to P[i] with tangents T0 and T1
            vector<Point> segmentPoints = drawHermiteCurve(
                pts[i - 1], T0x, T0y, // start point and tangent
                pts[i], T1x, T1y      // end point and tangent
            );

            for (const auto &p : segmentPoints)
            {
                result.push_back({p, color});
            }

            T0x = T1x;
            T0y = T1y;
        }

        return result;
    }
};