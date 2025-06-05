#include "../DrawingAlgorithm.h"
#include <algorithm>
#include <cmath>
using namespace std;

class ParametricLineAlgorithm : public DrawingAlgorithm
{
public:
    ParametricLineAlgorithm()
    {
        setName((char *)"Parametric Line Algorithm");
        setRequiredPoints(2);
    }

    vector<pair<Point, Color>> draw(vector<Point> &inputPoints, vector<Color> drawingColors = {BLACK}) override
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

        int alpha1 = x2 - x1;
        int alpha2 = y2 - y1;

        // Add the first point
        Point firstPoint = {x1, y1};
        outputPoints.push_back({firstPoint, drawingColors.back()});

        double step = 1.0 / max(abs(alpha1), abs(alpha2));
        for (double t = step; t <= 1; t += step)
        {
            int x = round(x1 + t * alpha1);
            int y = round(y1 + t * alpha2);

            Point p = {x, y};
            outputPoints.push_back({p, drawingColors.back()});
        }
        return outputPoints;
    }
};