#pragma once
#include "DrawingAlgorithm.h"
#include "LineDrawingAlgos/BresenhamLineAlgorithm.cpp"
#include "LineDrawingAlgos/DDALineAlgorithm.cpp"
#include "LineDrawingAlgos/ParametricLineAlgorithm.cpp"
#include "LineDrawingAlgos/ColoredParametricLineAlgorithm.cpp"
#include "CircleDrawingAlgos/CircleCartesian.cpp"
#include "CircleDrawingAlgos/CircleMidPointDDA.cpp"
#include "CircleDrawingAlgos/CircleMidPointDDAModified.cpp"
#include "CircleDrawingAlgos/CirclePolar.cpp"
#include "CircleDrawingAlgos/CirclePolarIterative.cpp"
#include "QuadAndCubicCurvesAlgos/BezierCurveAlgorithm.h"
#include "QuadAndCubicCurvesAlgos/HermiteCurveAlgorithm.cpp"
#include "QuadAndCubicCurvesAlgos/CardinalSplineCurve.cpp"
#include "QuadAndCubicCurvesAlgos/QuadraticCurveAlgorithm.cpp"
#include "FillingAlgos/FloodFillAlgorithm.cpp"
#include "EllipseDrawingAlgos/EllipseCartesianAlgorithm.cpp"
#include "EllipseDrawingAlgos/EllipsePolarAlgorithm.cpp"
#include "EllipseDrawingAlgos/EllipsePolar2Algorithm.cpp"
#include "EllipseDrawingAlgos/EllipseMidPointAlgorithm.cpp"
#include "EllipseDrawingAlgos/EllipseMidPointDDAAlgorithm.cpp"
#include "CircleQuarterFilling/CircleQuarterLineFilling.cpp"
#include "CircleQuarterFilling/CircleQuarterCircleFilling.cpp"
#include "FillingAlgos/ConvexFillAlgorithm.cpp"
#include "FillingAlgos/GeneralFillAlgorithm.cpp"
#include "FillingAlgos/FillSquareHermitCurve.cpp"
#include "FillingAlgos/FillRectangleBezierCurve.cpp"
#include "Clipping/Square/PointClipping.cpp"
#include "Clipping/Square/CohenSutherlandLineClipping.cpp"
#include "Clipping/Rectangle/PointClippingRectangle.cpp"
#include "Clipping/Rectangle/LineClippingRectangle.cpp"
#include "Clipping/Rectangle/PolygonClippingRectangle.cpp"
#include "Clipping/Circle/point.cpp"
#include "Clipping/Circle/line.cpp"
#include "Clipping/Circle/polygon.cpp"

#include <memory>
using namespace std;

class AlgorithmFactory
{
public:
    static unique_ptr<DrawingAlgorithm> createAlgorithm(int algorithmId)
    {
        switch (algorithmId)
        {
        case 0:
            return nullptr; // Clear Canvas

        // Line Drawing
        case 1:
            cout << "Now using: DDA Line Algorithm\n";
            return make_unique<DDALineAlgorithm>();
        case 2:
            cout << "Now using: Bresenham Line Algorithm\n";
            return make_unique<BresenhamLineAlgorithm>();
        case 3:
            cout << "Now using: Parametric Line Algorithm\n";
            return make_unique<ParametricLineAlgorithm>();
        case 4:
            cout << "Now using: Colored Parametric Line Algorithm\n";
            return make_unique<ColoredParametricLineAlgorithm>();

        // Circle Drawing
        case 5:
            cout << "Now using: Cartesian Circle Algorithm\n";
            return make_unique<CircleCartesianAlgorithm>();
        case 6:
            cout << "Now using: Polar Circle Algorithm\n";
            return make_unique<CirclePolarAlgorithm>();
        case 7:
            cout << "Now using: Iterative Polar Circle Algorithm\n";
            return make_unique<CirclePolarIterativeAlgorithm>();
        case 8:
            cout << "Now using: Midpoint DDA Circle Algorithm\n";
            return make_unique<CircleMidPointDDAAlgorithm>();
        case 9:
            cout << "Now using: Modified Midpoint DDA Circle Algorithm\n";
            return make_unique<CircleMidPointDDAModifiedAlgorithm>();

        // Curve Drawing
        case 10:
            cout << "Now using: Quadratic Curve Algorithm\n";
            return make_unique<QuadraticCurveAlgorithm>();
        case 11:
            cout << "Now using: Bezier Curve Algorithm\n";
            return make_unique<BezierCurveAlgorithm>();
        case 12:
            cout << "Now using: Flood Fill Algorithm\n";
            return make_unique<FloodFillAlgorithm>();
        case 13:
            cout << "Now using: Hermite Curve Algorithm\n";
            return make_unique<HermiteCurveAlgorithm>();
        case 14:
            cout << "Now using: Cardinal Spline Curve Algorithm\n";
            return make_unique<CardinalSplineAlgorithm>();

        // Ellipse Drawing
        case 15:
            cout << "Now using: Cartesian Ellipse Algorithm\n";
            return make_unique<EllipseCartesianAlgorithm>();
        case 16:
            cout << "Now using: Polar Ellipse Algorithm\n";
            return make_unique<EllipsePolarAlgorithm>();
        case 17:
            cout << "Now using: Polar 2 Ellipse Algorithm\n";
            return make_unique<EllipsePolar2Algorithm>();
        case 18:
            cout << "Now using: Midpoint Ellipse Algorithm\n";
            return make_unique<EllipseMidPointAlgorithm>();
        case 19:
            cout << "Now using: Midpoint DDA Ellipse Algorithm\n";
            return make_unique<EllipseMidPointDDAAlgorithm>();

        // Circle Quarter Filling
        case 20:
            cout << "Now using: Circle Quarter Line Filling Algorithm\n";
            return make_unique<CircleQuarterLineFilling>();
        case 27:
            cout << "Now using: Circle Quarter Circle Filling Algorithm\n";
            return make_unique<CircleQuarterCircleFilling>();

        // Polygon Filling
        case 21:
            cout << "Now using: Convex Polygon Fill Algorithm\n";
            return make_unique<ConvexFill>();
        case 22:
            cout << "Now using: General Polygon Fill Algorithm\n";
            return make_unique<GeneralFill>();
        case 23:
            cout << "Now using: Fill Square with Hermite Curve\n";
            return make_unique<FillSquareHermitCurve>();
        case 24:
            cout << "Now using: Fill Rectangle with Bezier Curve\n";
            return make_unique<FillRectangleBezierCurve>();

        // Clipping (Square Window)
        case 25:
            cout << "Now using: Point Clipping with Square Window\n";
            return make_unique<PointClippingAlgorithm>();
        case 26:
            cout << "Now using: Line Clipping (Cohen-Sutherland)\n";
            return make_unique<CohenSutherlandLineClippingAlgorithm>();

        // Clipping (Rectangular Window)
        case 28:
            cout << "Now using: Point Clipping with Rectangular Window\n";
            return make_unique<PointClippingRectangleWindowAlgorithm>();
        case 29:
            cout << "Now using: Line Clipping with Rectangular Window\n";
            return make_unique<LineClippingRectanlgeWindowAlgorithm>();
        case 30:
            cout << "Now using: Polygon Clipping with Rectangular Window\n";
            return make_unique<PolygonClippingRectanlgeWindowAlgorithm>();

        // Clipping (Circular Window)
        case 31:
            cout << "Now using: Point Clipping with Circular Window\n";
            return make_unique<CircularPointClipping>();
        case 32:
            cout << "Now using: Line Clipping with Circular Window\n";
            return make_unique<CircularLineClipping>();
        case 33:
            cout << "Now using: Polygon Clipping with Circular Window\n";
            return make_unique<CircularPolygonClipping>();

        default:
            return nullptr;
        }
    }
};
