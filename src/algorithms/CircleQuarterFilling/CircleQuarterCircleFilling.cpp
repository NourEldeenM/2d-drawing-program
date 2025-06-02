#include "../DrawingAlgorithm.h"
#include "../LineDrawingAlgos/BresenhamLineAlgorithm.cpp"
#include "../CircleDrawingAlgos/CircleMidPointDDAModified.cpp"

#include <cmath>
#include <vector>
#include <queue>

using namespace std;

class CircleQuarterCircleFilling : public DrawingAlgorithm
{
public:
    CircleQuarterCircleFilling(){
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
    
    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors) override{
        Point center = pts[0];
        Point point = pts[1];
        auto circleAlgo = CircleMidPointDDAModifiedAlgorithm();
        auto result = circleAlgo.draw(pts, drawingColors);
        int radius = static_cast<int>(sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2)));
        Point quarter = pts.size() > 2 ? pts[2] : Point{center.x + 1, center.y};
        int dx[] = {1, 1, -1, -1};
        int dy[] = {1, -1, 1, -1};
        int idx;
        if (quarter.x > center.x)
            idx = quarter.y > center.y ? 0 : 1;
        else
            idx = quarter.y > center.y ? 2 : 3;
        int size = result.size();
        int innerCircleRadius = 5;
        for (int i = 0; i <= radius + innerCircleRadius; i += innerCircleRadius * 2) {
            for (int j = 0; j <= radius + innerCircleRadius; j += innerCircleRadius * 2) {
                Point innerCenter = {center.x + dx[idx] * i, center.y + dy[idx] * j};
                int dist = sqrt(pow(innerCenter.x - center.x, 2) + pow(innerCenter.y - center.y, 2));

                if (dist > radius + innerCircleRadius)
                    break;

                vector<Point> innerCircle = {innerCenter, {innerCenter.x + innerCircleRadius, innerCenter.y}};
                auto innerCirclePoints = circleAlgo.draw(innerCircle, drawingColors);
                for (const auto &pointColor : innerCirclePoints) 
                    if (inQuarter(center, pointColor.first, radius, idx)) 
                        result.push_back(pointColor);
            }
        }
        return result;
    }

    bool inQuarter(Point center, Point p,int radius, int idx) {
        int dx = p.x - center.x;
        int dy = p.y - center.y;
        if (dx * dx + dy * dy > radius * radius)
            return false;
        if (idx == 0)
            return p.x >= center.x && p.y >= center.y; // First quadrant
        if (idx == 1)
            return p.x >= center.x && p.y <= center.y; // Second quadrant
        if (idx == 2)
            return p.x <= center.x && p.y >= center.y; // Third quadrant
        return p.x <= center.x && p.y <= center.y; // Fourth quadrant
    }
};
