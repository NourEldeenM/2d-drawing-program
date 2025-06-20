#include "../DrawingAlgorithm.h"
#include "../LineDrawingAlgos/BresenhamLineAlgorithm.cpp"
#include "../CircleDrawingAlgos/CircleMidPointDDAModified.cpp"

#include <cmath>
#include <vector>

using namespace std;

class CircleQuarterLineFilling : public DrawingAlgorithm
{
public:
    CircleQuarterLineFilling(){
        setName((char *)"Circle Quarter Line Filling");
        setRequiredPoints(3);
    }
    void addLine(Point center, Point p, vector<pair<Point,Color>> &points) {
        auto lineAlgo = BresenhamLineAlgorithm();
        vector<Point> v = {center, p};
        auto linePoints = lineAlgo.draw(v);
        if (linePoints.empty())
            return;
        for (const auto pointColor : linePoints) 
            points.push_back(pointColor);
    }
    // vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {BLACK}) override{
    //     vector<pair<Point, Color>> result;
    //     if (pts.size() < 2)
    //         return result;

    //     Point center = pts[0];
    //     Point point = pts[1];
    //     Point quarter = pts.size() > 2 ? pts[2] : Point{center.x + 1, center.y};

    //     int dx[] = {1,1,-1,-1};
    //     int dy[] = {1,-1,1,-1};
    //     int idx;
    //     if (quarter.x > center.x)
    //         idx = quarter.y > center.y ? 0 : 1;
    //     else
    //         idx = quarter.y > center.y ? 2 : 3;

    //     int radius = static_cast<int>(sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2)));
    //     int x = 0, y = radius, d = 1 - radius;
    //     int d1 = 3, d2 = ((x - y) << 1) + 5;
    //     vector<Point> points;
        
    //     DrawCirclePoints(center, {x, y}, points);
    //     while (x < y){
    //         if (d < 0)
    //             d += d1,
    //                 d2 += 2;
    //         else
    //             --y,
    //                 d += d2,
    //                 d2 += 4;
    //         ++x;
    //         d1 += 2;
    //         DrawCirclePoints(center, {x, y}, points);
    //         addLine(center, {center.x + dx[idx] * x, center.y + dy[idx] * y}, points);
    //         addLine(center, {center.x + dx[idx] * y, center.y + dy[idx] * x}, points);
    //     }
    //     Color color = drawingColors.empty() ? BLACK : drawingColors.back();
    //     for (const auto &p : points)
    //         result.push_back(make_pair(p, color));
    //     return result;
    // }
    
    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors) override{
        Point center = pts[0];
        Point point = pts[1];
        auto result = CircleMidPointDDAModifiedAlgorithm().draw(pts, drawingColors);
        Point quarter = pts.size() > 2 ? pts[2] : Point{center.x + 1, center.y};
        int dx[] = {1, 1, -1, -1};
        int dy[] = {1, -1, 1, -1};
        int idx;
        if (quarter.x > center.x)
            idx = quarter.y > center.y ? 0 : 1;
        else
            idx = quarter.y > center.y ? 2 : 3;
        auto lineAlgo = BresenhamLineAlgorithm();
        int size = result.size();
        for (int i = 0; i < size; ++i) {
            Point p = result[i].first;
            if (inQuarter(center, p, idx)) 
                addLine(center, p, result);
        }
        return result;
    }

    bool inQuarter(Point center, Point p, int idx) {
        if (idx == 0)
            return p.x >= center.x && p.y >= center.y; // First quadrant
        if (idx == 1)
            return p.x >= center.x && p.y <= center.y; // Second quadrant
        if (idx == 2)
            return p.x <= center.x && p.y >= center.y; // Third quadrant
        return p.x <= center.x && p.y <= center.y; // Fourth quadrant
    }
};
