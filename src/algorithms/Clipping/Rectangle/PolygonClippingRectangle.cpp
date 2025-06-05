#include "../../DrawingAlgorithm.h"
#include "../../LineDrawingAlgos/BresenhamLineAlgorithm.cpp"

#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class PolygonClippingRectanlgeWindowAlgorithm : public DrawingAlgorithm{
    struct ClippingWindow {
        int xmin, ymin, xmax, ymax;

        ClippingWindow(Point p1, Point p2) {
            xmin = std::min(p1.x, p2.x);
            xmax = std::max(p1.x, p2.x);
            ymin = std::min(p1.y, p2.y);
            ymax = std::max(p1.y, p2.y);
        }
    };
    
    Point getVerticalIntersect(Point p1, Point p2, int xEdge){
        if (p2.x == p1.x) return Point(xEdge, p1.y); // Avoid division by zero
        return Point(xEdge, round(p1.y + (double)(xEdge - p1.x) * (p2.y - p1.y) / (p2.x - p1.x)));
    }

    Point getHorizontalIntersect(Point p1, Point p2, int yEdge){
        if (p2.y == p1.y) return Point(p1.x, yEdge); // Avoid division by zero
        return Point(round(p1.x + (double)(yEdge - p1.y) * (p2.x - p1.x) / (p2.y - p1.y)), yEdge);
    }

    vector<Point> clipLeft(vector<Point>& points,int xLeft){
        vector<Point> clipped;
        for (size_t i = 0; i < points.size(); i++) {
            Point p1 = points[i];
            Point p2 = points[(i + 1) % points.size()];

            if (p1.x >= xLeft && p2.x >= xLeft) 
                clipped.push_back(p2);
            else if (p1.x < xLeft && p2.x >= xLeft) {
                clipped.push_back(getVerticalIntersect(p1, p2, xLeft));
                clipped.push_back(p2);
            } 
            else if (p1.x >= xLeft && p2.x < xLeft) 
                clipped.push_back(getVerticalIntersect(p1, p2, xLeft));
        }
        return clipped;
    }

    vector<Point> clipRight(vector<Point>& points,int xRight){
        vector<Point> clipped;
        for (size_t i = 0; i < points.size(); i++) {
            Point p1 = points[i];
            Point p2 = points[(i + 1) % points.size()];

            if (p1.x <= xRight && p2.x <= xRight) 
                clipped.push_back(p2);
            else if (p1.x > xRight && p2.x <= xRight) {
                clipped.push_back(getVerticalIntersect(p1, p2, xRight));
                clipped.push_back(p2);
            } 
            else if (p1.x <= xRight && p2.x > xRight) 
                clipped.push_back(getVerticalIntersect(p1, p2, xRight));
        }
        return clipped;

    }

    vector<Point> clipTop(vector<Point>& points, int yTop){
        vector<Point> clipped;
        for (size_t i = 0; i < points.size(); i++) {
            Point p1 = points[i];
            Point p2 = points[(i + 1) % points.size()];

            if (p1.y <= yTop && p2.y <= yTop) 
                clipped.push_back(p2);
            else if (p1.y > yTop && p2.y <= yTop) {
                clipped.push_back(getHorizontalIntersect(p1, p2, yTop));
                clipped.push_back(p2);
            } 
            else if (p1.y <= yTop && p2.y > yTop) 
                clipped.push_back(getHorizontalIntersect(p1, p2, yTop));
        }
        return clipped;

    }

    vector<Point> clipBottom(vector<Point>& points, int yBottom){
        vector<Point> clipped;
        for (size_t i = 0; i < points.size(); i++) {
            Point p1 = points[i];
            Point p2 = points[(i + 1) % points.size()];

            if (p1.y >= yBottom && p2.y >= yBottom) 
                clipped.push_back(p2);
            else if (p1.y < yBottom && p2.y >= yBottom) {
                clipped.push_back(getHorizontalIntersect(p1, p2, yBottom));
                clipped.push_back(p2);
            } 
            else if (p1.y >= yBottom && p2.y < yBottom) 
                clipped.push_back(getHorizontalIntersect(p1, p2, yBottom));
        }
        return clipped;

    }

    void polygonClip(vector<Point>& points, int xLeft, int xRight, int yBottom, int yTop) {
        points = clipLeft(points, xLeft);
        points = clipRight(points, xRight);
        points = clipTop(points, yTop);
        points = clipBottom(points, yBottom);
    }

public:
    PolygonClippingRectanlgeWindowAlgorithm()
    {
        setName((char *)"Polygon Clipping Rectangle window");
        // to draw triangle
        setRequiredPoints(7);
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;

        ClippingWindow window(pts[0], pts[1]);
        vector<Point> polygonPoints(pts.begin() + 2, pts.end());

        // Draw clipping window border
        Color windowColor = RED;
        for (int x = window.xmin; x <= window.xmax; x++) {
            result.push_back({{x, window.ymin}, windowColor});
            result.push_back({{x, window.ymax}, windowColor});
        }
        for (int y = window.ymin; y <= window.ymax; y++) {
            result.push_back({{window.xmin, y}, windowColor});
            result.push_back({{window.xmax, y}, windowColor});
        }

        // Clip polygon points to window
        polygonClip(polygonPoints, window.xmin, window.xmax, window.ymin, window.ymax);

        if (polygonPoints.size() < 2) return result; // Nothing to draw

        Color clippedLineColor = drawingColors.empty() ? GREEN : drawingColors[0];

        BresenhamLineAlgorithm lineDrawer;

        // Draw clipped polygon edges
        for (size_t i = 0; i < polygonPoints.size(); i++) {
            Point p1 = polygonPoints[i];
            Point p2 = polygonPoints[(i + 1) % polygonPoints.size()];
            vector<Point> linePoints = {p1, p2};
            vector<pair<Point, Color>> linePixels = lineDrawer.draw(linePoints, {clippedLineColor});
            result.insert(result.end(), linePixels.begin(), linePixels.end());
        }

        return result;
    }



};