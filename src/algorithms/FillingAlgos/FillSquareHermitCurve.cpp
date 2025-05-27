#include "../DrawingAlgorithm.h"
#include "../QuadAndCubicCurvesAlgos/HermiteCurveAlgorithm.cpp"
#include <algorithm>

using namespace std;
class FillSquareHermitCurve : public DrawingAlgorithm{
public:
    FillSquareHermitCurve()
    {
        setName((char *)"Fill Square Hermit Curve");
        // top left and bottom right of the square
        setRequiredPoints(2);
    }
    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {RED}) override
    {
        // ensure that first point is smallest
        sort(pts.begin(),pts.end());

        int width = abs(pts[1].x - pts[0].x);
        int height = abs(pts[1].y - pts[0].y);
        int side = min(width, height);

        Point p0 = pts[0];
        Point p1(p0.x + side, p0.y + side); 

        // set output return 
        vector<pair<Point, Color>> outputPoints;
        HermiteCurveAlgorithm curve;

        for (int x = p0.x; x < p0.x + side; x++)
        {
            Point pt1(x, p0.y);
            Point pt2(x, p1.y);
            vector<Point> p = {pt1, pt1, pt2, pt2};
            vector<pair<Point, Color>> curvePoints = curve.draw(p, drawingColors);
            for (auto &&i : curvePoints)
            {
                outputPoints.push_back(i);
                
            }
            
        }
        
        return outputPoints;
    }
};