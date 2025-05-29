#pragma once
#include "../DrawingAlgorithm.h"
#include "../QuadAndCubicCurvesAlgos/BezierCurveAlgorithm.h"
#include <algorithm>

using namespace std;

class FillRectangleBezierCurve : public DrawingAlgorithm {
public:
    FillRectangleBezierCurve() {
        setName((char *)"Fill Rectangle Bezier Curve");
        // top left and bottom right of the Rectangle
        setRequiredPoints(2);
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {RED}) override {
        // ensure that first point is smallest
        int minY = min(pts[0].y, pts[1].y);
        int maxY = max(pts[0].y, pts[1].y);
        int leftX = min(pts[0].x, pts[1].x);
        int rightX = max(pts[0].x, pts[1].x);

        vector<pair<Point, Color>> outputPoints;
        BezierCurveAlgorithm curve;

        for (int y = minY; y <= maxY; y++)
        {
            Point p1(leftX, y);
            Point p2(rightX, y);

            vector<Point> p = {p1, p1,p2, p2};
            vector<pair<Point, Color>> curvePoints = curve.draw(p, drawingColors);
            for (auto &&i : curvePoints) {
                outputPoints.push_back(i);
            }

        }
        

        return outputPoints;
    }
};
