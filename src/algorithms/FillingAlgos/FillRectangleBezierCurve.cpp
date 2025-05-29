#pragma once
#include "../DrawingAlgorithm.h"
#include "../QuadAndCubicCurvesAlgos/BezierCurveAlgorithm.h"
#include <algorithm>

class FillRectangleBezierCurve : public DrawingAlgorithm {
public:
    FillRectangleBezierCurve() {
        setName((char *)"Fill Rectangle Bezier Curve");
        // top left and bottom right of the Rectangle
        setRequiredPoints(2);
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {RED}) override {
        // ensure that first point is smallest
        std::sort(pts.begin(), pts.end());

        vector<pair<Point, Color>> outputPoints;
        BezierCurveAlgorithm curve;

        vector<Point> p = {pts[0], Point(0, 0), Point(5, 5), pts[1]};
        vector<pair<Point, Color>> curvePoints = curve.draw(p, drawingColors);
        for (auto &&i : curvePoints) {
            outputPoints.push_back(i);
        }
        return outputPoints;
    }
};
