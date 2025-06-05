#include "../../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
#include "../../LineDrawingAlgos/BresenhamLineAlgorithm.cpp"
#include "../../CircleDrawingAlgos/CircleMidPointDDAModified.cpp"
using namespace std;

class CircularPolygonClipping : public DrawingAlgorithm {
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
    BresenhamLineAlgorithm lineAlgo;

    bool clipEdge(Point origP1, Point origP2, Point &clippedP1, Point &clippedP2, const Circle &circle) {
        double dx = origP2.x - origP1.x;
        double dy = origP2.y - origP1.y;
        double fx = origP1.x - circle.center.x;
        double fy = origP1.y - circle.center.y;

        double a = dx*dx + dy*dy;
        double b = 2*(fx*dx + fy*dy);
        double c = fx*fx + fy*fy - circle.radius*circle.radius;
        double d = b*b - 4*a*c;

        if (d < 0) return false;

        d = sqrt(d);
        double t1 = (-b - d) / (2 * a);
        double t2 = (-b + d) / (2 * a);

        t1 = max(0.0, min(1.0, t1));
        t2 = max(0.0, min(1.0, t2));
        if (t1 > t2) swap(t1, t2);

        clippedP1 = {
            static_cast<int>(origP1.x + dx * t1),
            static_cast<int>(origP1.y + dy * t1)
        };
        clippedP2 = {
            static_cast<int>(origP1.x + dx * t2),
            static_cast<int>(origP1.y + dy * t2)
        };

        return true;
    }


public:
    CircularPolygonClipping() {
        setName((char *)"Circle Polygon Clipping");
        setRequiredPoints(7); // 2 for circle, 5 for polygon
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> colors = {BLACK}) override {
        vector<pair<Point, Color>> res;
        if (pts.size() < 7) return res;

        Circle circle(pts[0], pts[1]);
        vector<Point> circlePts = {circle.center, {circle.center.x + circle.radius, circle.center.y}};
        auto circlePixels = circleAlgo.draw(circlePts, {RED});
        res.insert(res.end(), circlePixels.begin(), circlePixels.end());

        Color originalColor = {128, 128, 128};
        Color clippedColor = colors.empty() ? BLACK : colors.back();

        vector<Point> poly(pts.begin() + 2, pts.begin() + 7);

        for (int i = 0; i < 5; ++i) {
            Point p1 = poly[i];
            Point p2 = poly[(i + 1) % 5];
            vector<Point> edge = {p1, p2};
            auto origPixels = lineAlgo.draw(edge, {originalColor});
            res.insert(res.end(), origPixels.begin(), origPixels.end());
        }

        for (int i = 0; i < 5; ++i) {
            Point p1 = poly[i];
            Point p2 = poly[(i + 1) % 5];
            Point clippedP1, clippedP2;

            if (circle.contains(p1) && circle.contains(p2)) {
                vector<Point> insideEdge = {p1, p2};
                auto insidePixels = lineAlgo.draw(insideEdge, {clippedColor});
                res.insert(res.end(), insidePixels.begin(), insidePixels.end());
            } else if (clipEdge(p1, p2, clippedP1, clippedP2, circle)) {
                vector<Point> clippedEdge = {clippedP1, clippedP2};
                auto clippedPixels = lineAlgo.draw(clippedEdge, {clippedColor});
                res.insert(res.end(), clippedPixels.begin(), clippedPixels.end());
            }
        }

        return res;
    }
};