#include "../../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
#include "../../CircleDrawingAlgos/CircleMidPointDDAModified.cpp"

using namespace std;

class CircularPointClipping : public DrawingAlgorithm {
private:
    struct Circle {
        Point center;
        int radius;
        Circle(Point p1, Point p2) {
            center = p1;
            radius = static_cast<int>(sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
        }
        bool contains(Point p) const {
            int dx = p.x - center.x;
            int dy = p.y - center.y;
            return dx * dx + dy * dy <= radius * radius;
        }
    };

    CircleMidPointDDAModifiedAlgorithm circleAlgo;

public:
    CircularPointClipping() {
        setName((char *)"Circular Point Clipping");
        setRequiredPoints(3); // 2 for circle, 1 point to clip
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> colors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.size() < 3) return result;

        Circle circle(pts[0], pts[1]);

        vector<Point> circlePts = {circle.center, {circle.center.x + circle.radius, circle.center.y}};
        vector<Color> circleColors = {RED};
        auto circleOutline = circleAlgo.draw(circlePts, circleColors);
        result.insert(result.end(), circleOutline.begin(), circleOutline.end());

        Point pointToClip = pts[2];
        bool isInside = circle.contains(pointToClip);

        Color insideColor = GREEN;
        Color outsideColor = GRAY;

        Color displayColor = isInside ? insideColor : outsideColor;
        
        for (int dx = -2; dx <= 2; ++dx) {
            for (int dy = -2; dy <= 2; ++dy) {
                if (dx * dx + dy * dy <= 4) {
                    result.push_back({{pointToClip.x + dx, pointToClip.y + dy}, displayColor});
                }
            }
        }

        return result;
    }
};
