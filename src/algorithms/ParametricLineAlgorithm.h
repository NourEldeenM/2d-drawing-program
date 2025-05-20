#ifndef PARAMETRIC_LINE_ALGORITHM_H
#define PARAMETRIC_LINE_ALGORITHM_H

#include "DrawingAlgorithm.h"
#include <algorithm>
#include <cmath>
using namespace std;

struct ColoredPoint : Point {
    int r, g, b; 
};

class ParametricLineAlgorithm : public DrawingAlgorithm
{
private:
    int startR = 0, startG = 0, startB = 0;
    int endR = 255, endG = 255, endB = 255;
    vector<ColoredPoint> coloredPoints;

public:
    ParametricLineAlgorithm() {
        setName((char*)"Parametric Line Algorithm");
        setRequiredPoints(2); // Start and end points
    }

    void setColors(int r1, int g1, int b1, int r2, int g2, int b2) {
        startR = r1; startG = g1; startB = b1;
        endR = r2; endG = g2; endB = b2;
    }

    const vector<ColoredPoint>& getColoredPoints() const {
        return coloredPoints;
    }

    vector<Point> draw(vector<Point> &inputPoints) override {
        vector<Point> outputPoints;
        coloredPoints.clear(); 
        
        if (inputPoints.size() < 2) {
            return outputPoints; // Not enough points
        }
        
        int x1 = inputPoints[0].x;
        int y1 = inputPoints[0].y;
        int x2 = inputPoints[1].x;
        int y2 = inputPoints[1].y;
        
        int alpha1 = x2 - x1;
        int alpha2 = y2 - y1;
        int alphaRed = endR - startR;
        int alphaGreen = endG - startG;
        int alphaBlue = endB - startB;
        
        // Add the first point
        Point firstPoint = {x1, y1};
        outputPoints.push_back(firstPoint);
        
        ColoredPoint coloredPoint = {x1, y1, startR, startG, startB};
        coloredPoints.push_back(coloredPoint);
        
        double step = 1.0 / max(abs(alpha1), abs(alpha2));
        for (double t = step; t <= 1; t += step) {
            int x = round(x1 + t * alpha1);
            int y = round(y1 + t * alpha2);
            
            int r = round(startR + t * alphaRed);
            int g = round(startG + t * alphaGreen);
            int b = round(startB + t * alphaBlue);
            
            Point p = {x, y};
            outputPoints.push_back(p);
            
            ColoredPoint cp = {x, y, r, g, b};
            coloredPoints.push_back(cp);
        }
        
        return outputPoints;
    }
};

#endif // PARAMETRIC_LINE_ALGORITHM_H