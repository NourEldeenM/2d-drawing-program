#include "../../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
#include "../../LineDrawingAlgos/BresenhamLineAlgorithm.cpp"
#include "../../CircleDrawingAlgos/CircleMidPointDDAModified.cpp"
using namespace std;

class CircularLineClipping : public DrawingAlgorithm {
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

    bool clipLine(Point &p1, Point &p2, const Circle &circle) {
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;
        double fx = p1.x - circle.center.x;
        double fy = p1.y - circle.center.y;

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

        Point q1 = {static_cast<int>(p1.x + dx * t1), static_cast<int>(p1.y + dy * t1)};
        Point q2 = {static_cast<int>(p1.x + dx * t2), static_cast<int>(p1.y + dy * t2)};

        if (!circle.contains(q1) && !circle.contains(q2)) return false;

        p1 = q1;
        p2 = q2;
        return true;
    }

public:
    CircularLineClipping() {
        setName((char *)"Circle Line Clipping");
        setRequiredPoints(4);
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> colors = {BLACK}) override {
        vector<pair<Point, Color>> res;
        if (pts.size() < 4) return res;

        Circle circle(pts[0], pts[1]);
        vector<Point> circlePts = {circle.center, {circle.center.x + circle.radius, circle.center.y}};
        auto circlePixels = circleAlgo.draw(circlePts, {RED});
        res.insert(res.end(), circlePixels.begin(), circlePixels.end());

        Point origP1 = pts[2], origP2 = pts[3];
        Color clippedLineColor = colors.empty() ? BLACK : colors.back();

        Point p1 = origP1, p2 = origP2;
        if (clipLine(p1, p2, circle)) {
            vector<Point> clippedLinePts = {p1, p2};
            vector<Color> clippedColors = {clippedLineColor};
            auto clippedPixels = lineAlgo.draw(clippedLinePts, clippedColors);
            res.insert(res.end(), clippedPixels.begin(), clippedPixels.end());
        }
        return res;
    }
};
