#include "../DrawingAlgorithm.h"
#include "../QuadAndCubicCurvesAlgos/HermiteCurveAlgorithm.cpp"
using namespace std;
class FillSquareHermitCurve : public DrawingAlgorithm{
public:
    FillSquareHermitCurve()
    {
        setName((char *)"Fill Square Hermit Curve");
        // top left and bottom right of the square
        setRequiredPoints(4);
    }
    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {RED}) override
    {
        vector<pair<Point, Color>> outputPoints;
        HermiteCurveAlgorithm curve;
        outputPoints=curve.draw(pts,drawingColors);
        return outputPoints;
    }
};