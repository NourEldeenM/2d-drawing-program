#include "../DrawingAlgorithm.h"
#include <algorithm>
#include <cmath>
using namespace std;

struct ColoredPoint : Point
{
    int r, g, b;
};

class ParametricLineAlgorithm : public DrawingAlgorithm
{
private:
    int startR = 0, startG = 0, startB = 0;
    int endR = 255, endG = 255, endB = 255;

public:
    ParametricLineAlgorithm()
    {
        setName((char *)"Parametric Line Algorithm");
        setRequiredPoints(2); // Start and end points
    }

    void setColors(Color c1, Color c2)
    {
        startR = c1.r;
        startG = c1.g;
        startB = c1.b;

        endR = c2.r;
        endG = c2.g;
        endB = c2.b;
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

        setColors(drawingColors.back(), drawingColors.back());

        int alpha1 = x2 - x1;
        int alpha2 = y2 - y1;

        int alphaRed = endR - startR;
        int alphaGreen = endG - startG;
        int alphaBlue = endB - startB;

        // Add the first point
        Point firstPoint = {x1, y1};
        outputPoints.push_back({firstPoint, drawingColors.back()});

        double step = 1.0 / max(abs(alpha1), abs(alpha2));
        for (double t = step; t <= 1; t += step)
        {
            int x = round(x1 + t * alpha1);
            int y = round(y1 + t * alpha2);

            int r = round(startR + t * alphaRed);
            int g = round(startG + t * alphaGreen);
            int b = round(startB + t * alphaBlue);

            Point p = {x, y};
            Color c = {r, g, b, 255};
            outputPoints.push_back({p, c});
        }
        return outputPoints;
    }
};