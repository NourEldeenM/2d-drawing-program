#include "DrawingAlgorithm.h"
#include <cmath>

using namespace std;


class LineDDA : public DrawingAlgorithm
{
public:
    vector<Point> draw(vector<Point> &inputPoints) override {
        vector<Point> linePoints;

        if (inputPoints.size() != 2)
            return linePoints; // Return empty vector if input is invalid

        int x1 = inputPoints[0].x;
        int y1 = inputPoints[0].y;
        int x2 = inputPoints[1].x;
        int y2 = inputPoints[1].y;

        int dx = x2 - x1;
        int dy = y2 - y1;

        int steps = max(abs(dx), abs(dy));

        if (steps == 0)
        {
            linePoints.push_back({x1, y1});
            return linePoints;
        }

        float xIncrement = static_cast<float>(dx) / steps;
        float yIncrement = static_cast<float>(dy) / steps;

        float x = static_cast<float>(x1);
        float y = static_cast<float>(y1);

        for (int i = 0; i <= steps; ++i)
        {
            linePoints.push_back({static_cast<int>(round(x)), static_cast<int>(round(y))});
            x += xIncrement;
            y += yIncrement;
        }

        return linePoints;
    }

};