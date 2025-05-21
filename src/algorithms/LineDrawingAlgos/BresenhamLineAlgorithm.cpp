#include "../DrawingAlgorithm.h"
#include <algorithm>
#include <cmath>
using namespace std;

class BresenhamLineAlgorithm : public DrawingAlgorithm
{
public:
    BresenhamLineAlgorithm()
    {
        setName((char *)"Bresenham Line Algorithm");
        setRequiredPoints(2); // Start and end points
    }

    vector<pair<Point, Color>> draw(vector<Point> &inputPoints, vector<Color> drawingColor = {BLACK}) override
    {
        std::vector<pair<Point, Color>> outputPoints;

        if (inputPoints.size() < 2)
        {
            return outputPoints; // Not enough points
        }

        int x1 = inputPoints[0].x;
        int y1 = inputPoints[0].y;
        int x2 = inputPoints[1].x;
        int y2 = inputPoints[1].y;

        int x = x1, y = y1;
        int dx, dy, d, d1, d2;
        dx = abs(x2 - x1);
        dy = abs(y2 - y1);

        // Add first point
        Point p = {x, y};
        outputPoints.push_back({p, drawingColor[0]});

        int xinc = (x1 < x2) ? 1 : -1;
        int yinc = (y1 < y2) ? 1 : -1;

        if (dy <= dx)
        { // slope <= 1 || slope >= -1
            d = dx - 2 * dy;
            d1 = -2 * dy;
            d2 = 2 * (dx - dy);
            while (x != x2)
            {
                if (d > 0)
                {
                    d += d1;
                }
                else
                {
                    d += d2;
                    y += yinc;
                }
                x += xinc;
                Point p = {x, y};
                outputPoints.push_back({p, drawingColor[0]});
            }
        }
        else
        { // slope > 1 || slope < -1
            d = 2 * dx - dy;
            d1 = 2 * dx;
            d2 = 2 * (dx - dy);
            while (y != y2)
            {
                if (d > 0)
                {
                    d += d2;
                    x += xinc;
                }
                else
                {
                    d += d1;
                }
                y += yinc;
                Point p = {x, y};
                outputPoints.push_back({p, drawingColor[0]});
            }
        }

        return outputPoints;
    }
};