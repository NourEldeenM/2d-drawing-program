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
#include "QuadAndCubicCurvesAlgos/BezierCurveAlgorithm.cpp"
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
#include <memory>

using namespace std;

class AlgorithmFactory
{
public:
    static unique_ptr<DrawingAlgorithm> createAlgorithm(int algorithmId)
    {
        switch (algorithmId)
        {
        // Line Drawing Algorithms
        case 0:
            return make_unique<DDALineAlgorithm>();
        case 1:
            return make_unique<BresenhamLineAlgorithm>();
        case 2:
            return make_unique<ParametricLineAlgorithm>();
        case 3:
            return make_unique<ParametricLineAlgorithm>(); // Colored Parametric

        // Circle Drawing Algorithms
        case 4:
            return make_unique<CircleCartesianAlgorithm>();
        case 5:
            return make_unique<CirclePolarAlgorithm>();
        case 6:
            return make_unique<CirclePolarIterativeAlgorithm>();
        case 7:
            return make_unique<CircleMidPointDDAAlgorithm>();
        case 8:
            return make_unique<CircleMidPointDDAModifiedAlgorithm>();

        // Curve Drawing Algorithms
        case 9:
            return make_unique<QuadraticCurveAlgorithm>();
        case 10:
            return make_unique<BezierCurveAlgorithm>();
        case 11:
            return make_unique<FloodFillAlgorithm>();
        case 12:
            return make_unique<HermiteCurveAlgorithm>();
        case 13:
            return make_unique<CardinalSplineAlgorithm>();

        // Ellipse Drawing Algorithms
        case 14:
            return make_unique<EllipseCartesianAlgorithm>();
        case 15:
            return make_unique<EllipsePolarAlgorithm>();
        case 16:
            return make_unique<EllipsePolar2Algorithm>();
        case 17:
            return make_unique<EllipseMidPointAlgorithm>();
        case 18:
            return make_unique<EllipseMidPointDDAAlgorithm>();
        case 19:
            return make_unique<CircleQuarterLineFilling>(); // Circle Quarter Line Filling
        // Special Cases
        case 20: // Clear Canvas - handled in GUI
            return nullptr;

        default:
            return nullptr;
        }
    }
};