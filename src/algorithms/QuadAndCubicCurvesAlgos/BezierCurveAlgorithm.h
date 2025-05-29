#ifndef BEZIERCURVEALGORITHM_H
#define BEZIERCURVEALGORITHM_H

#include "../DrawingAlgorithm.h"
#include <vector>
#include <cmath>

using namespace std;

class BezierCurveAlgorithm : public DrawingAlgorithm {
public:
    BezierCurveAlgorithm();

    vector<pair<Point, Color>> draw(vector<Point>& pts, vector<Color> drawingColors) override;
};

#endif // BEZIERCURVEALGORITHM_H
