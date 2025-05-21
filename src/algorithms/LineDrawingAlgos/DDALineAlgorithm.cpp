#include "DrawingAlgorithm.h"
#include <algorithm>
#include <cmath>
using namespace std;

class DDALineAlgorithm : public DrawingAlgorithm
{
public:
    DDALineAlgorithm()
    {
        setName((char *)"DDA Line Algorithm");
        setRequiredPoints(2); // Start and end points
    }

    int Round(double x)
    {
        return static_cast<int>(x + 0.5);
    }

    vector<pair<Point, Color>> draw(vector<Point> &inputPoints, vector<Color> drawingColor = {BLACK}) override
    {
        vector<pair<Point, Color>> outputPoints;

        if (inputPoints.size() < 2)
        {
            return outputPoints;
        }

        int x1 = inputPoints[0].x;
        int y1 = inputPoints[0].y;
        int x2 = inputPoints[1].x;
        int y2 = inputPoints[1].y;

        int dx = x2 - x1, dy = y2 - y1;

        // Add first point
        Point p = {x1, y1};
        outputPoints.push_back({p, drawingColor[0]});

        if (abs(dx) >= abs(dy))
        {
            if (x1 > x2)
            {
                std::swap(x1, x2);
                std::swap(y1, y2);
                dx = x2 - x1;
                dy = y2 - y1;
            }
            double m = (dx == 0) ? 0 : (double)dy / dx;
            int x = x1;
            double y = y1;
            while (x < x2)
            {
                x++;
                y += m;
                Point p = {x, Round(y)};
                outputPoints.push_back({p, drawingColor[0]});
            }
        }
        else
        {
            if (y1 > y2)
            {
                std::swap(x1, x2);
                std::swap(y1, y2);
                dx = x2 - x1;
                dy = y2 - y1;
            }
            double mi = (dy == 0) ? 0 : (double)dx / dy;
            int y = y1;
            double x = x1;
            while (y < y2)
            {
                y++;
                x += mi;
                Point p = {Round(x), y};
                outputPoints.push_back({p, drawingColor[0]});
            }
        }

        return outputPoints;
    }
};