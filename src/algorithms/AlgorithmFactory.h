#pragma once
#include "DrawingAlgorithm.h"
#include "LineDrawingAlgos/BresenhamLineAlgorithm.cpp"
#include "LineDrawingAlgos/DDALineAlgorithm.cpp"
#include "LineDrawingAlgos/ParametricLineAlgorithm.cpp"
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
#include "FillingAlgos/ConvexFillAlgorithm.cpp"
#include "FillingAlgos/GeneralFillAlgorithm.cpp"
#include "FillingAlgos/FillSquareHermitCurve.cpp"
#include "FillingAlgos/FillRectangleBezierCurve.cpp"


#include <memory>

using namespace std;

class AlgorithmFactory
{
public:
    static unique_ptr<DrawingAlgorithm> createAlgorithm(int algorithmId)
    {
        switch (algorithmId)
        {
        case 0: // Clear Canvas - handled in GUI
            return nullptr;
        // Line Drawing Algorithms
        case 1:
            return make_unique<DDALineAlgorithm>();
        case 2:
            return make_unique<BresenhamLineAlgorithm>();
        case 3:
            return make_unique<ParametricLineAlgorithm>();
        case 4:
            return make_unique<ParametricLineAlgorithm>(); // Colored Parametric

        // Circle Drawing Algorithms
        case 5:
            return make_unique<CircleCartesianAlgorithm>();
        case 6:
            return make_unique<CirclePolarAlgorithm>();
        case 7:
            return make_unique<CirclePolarIterativeAlgorithm>();
        case 8:
            return make_unique<CircleMidPointDDAAlgorithm>();
        case 9:
            return make_unique<CircleMidPointDDAModifiedAlgorithm>();

        // Curve Drawing Algorithms
        case 10:
            return make_unique<QuadraticCurveAlgorithm>();
        case 11:
            return make_unique<BezierCurveAlgorithm>();
        case 12:
            return make_unique<FloodFillAlgorithm>();
        case 13:
            return make_unique<HermiteCurveAlgorithm>();
        case 14:
            return make_unique<CardinalSplineAlgorithm>();

        // Ellipse Drawing Algorithms
        case 15:
            return make_unique<EllipseCartesianAlgorithm>();
        case 16:
            return make_unique<EllipsePolarAlgorithm>();
        case 17:
            return make_unique<EllipsePolar2Algorithm>();
        case 18:
            return make_unique<EllipseMidPointAlgorithm>();
        case 19:
            return make_unique<EllipseMidPointDDAAlgorithm>();
        case 20:
            return make_unique<CircleQuarterLineFilling>();
        // polygon Filling Algorithms
        case 21:
            return make_unique<ConvexFill>();
        case 22:
            return make_unique<GeneralFill>();
        case 23:
            return make_unique<FillSquareHermitCurve>();
        case 24:
            return make_unique<FillRectangleBezierCurve>();
        default:
            return nullptr;
        }
    }
};