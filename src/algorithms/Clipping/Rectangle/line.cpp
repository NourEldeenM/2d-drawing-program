#include "../../DrawingAlgorithm.h"
#include "../../LineDrawingAlgos/BresenhamLineAlgorithm.cpp"

#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class LineClippingRectanlgeWindowAlgorithm : public DrawingAlgorithm{

    BresenhamLineAlgorithm bresenhamAlgorithm;


    struct ClippingWindow {
        int xmin, ymin, xmax, ymax;

        ClippingWindow(Point p1, Point p2) {
            xmin = std::min(p1.x, p2.x);
            xmax = std::max(p1.x, p2.x);
            ymin = std::min(p1.y, p2.y);
            ymax = std::max(p1.y, p2.y);
        }
    };

    enum OutCode
    {
        INSIDE = 0, // 0000
        LEFT = 1,   // 0001
        RIGHT = 2,  // 0010
        BOTTOM = 4, // 0100
        TOP = 8     // 1000
    };

    int computeOutCode(int x, int y, const ClippingWindow &window)
    {
        int code = INSIDE;
        if (x < window.xmin)
            code |= LEFT;
        else if (x > window.xmax)
            code |= RIGHT;
        if (y < window.ymin)
            code |= TOP;
        else if (y > window.ymax)
            code |= BOTTOM;
        return code;
    }

    bool clipLine(int &x1, int &y1, int &x2, int &y2, const ClippingWindow &window)
    {
        int outcode1 = computeOutCode(x1, y1, window);
        int outcode2 = computeOutCode(x2, y2, window);
        bool accept = false;

        while (true)
        {
            if (!(outcode1 | outcode2))
            {
                // Both points inside
                accept = true;
                break;
            }
            else if (outcode1 & outcode2)
            {
                break;
            }
            else
            {
                // Intersection point
                int x, y;
                int outcodeOut = outcode1 ? outcode1 : outcode2;

                if (outcodeOut & TOP)
                {
                    x = x1 + (x2 - x1) * (window.ymin - y1) / (y2 - y1);
                    y = window.ymin;
                }
                else if (outcodeOut & BOTTOM)
                {
                    x = x1 + (x2 - x1) * (window.ymax - y1) / (y2 - y1);
                    y = window.ymax;
                }
                else if (outcodeOut & RIGHT)
                {
                    y = y1 + (y2 - y1) * (window.xmax - x1) / (x2 - x1);
                    x = window.xmax;
                }
                else if (outcodeOut & LEFT)
                {
                    y = y1 + (y2 - y1) * (window.xmin - x1) / (x2 - x1);
                    x = window.xmin;
                }

                if (outcodeOut == outcode1)
                {
                    x1 = x;
                    y1 = y;
                    outcode1 = computeOutCode(x1, y1, window);
                }
                else
                {
                    x2 = x;
                    y2 = y;
                    outcode2 = computeOutCode(x2, y2, window);
                }
            }
        }
        return accept;
    }

public:
    LineClippingRectanlgeWindowAlgorithm()
    {
        setName((char *)"Line Clipping Rectangle window");
        setRequiredPoints(4);
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.size() < 4) return result;

        ClippingWindow window(pts[0], pts[1]);
        Point p1 = pts[2];
        Point p2 = pts[3];

        Color windowColor = RED;
        Color clippedLineColor = drawingColors.empty() ? GREEN : drawingColors[0];

        // Draw clipping window border
        for (int x = window.xmin; x <= window.xmax; x++) {
            result.push_back({{x, window.ymin}, windowColor});
            result.push_back({{x, window.ymax}, windowColor});
        }
        for (int y = window.ymin; y <= window.ymax; y++) {
            result.push_back({{window.xmin, y}, windowColor});
            result.push_back({{window.xmax, y}, windowColor});
        }

        int x0 = p1.x, y0 = p1.y;
        int x1 = p2.x, y1 = p2.y;

        // Try to clip the line
        if (clipLine(x0, y0, x1, y1, window)) {
            Point clippedStart = {x0, y0};
            Point clippedEnd = {x1, y1};

            // Use Bresenham to draw the clipped line
            vector<Point> clippedLine = {clippedStart, clippedEnd};
            vector<pair<Point, Color>> linePixels = bresenhamAlgorithm.draw(clippedLine, {clippedLineColor});
            result.insert(result.end(), linePixels.begin(), linePixels.end());
        } else {
            // Optional: draw the original line in gray if it is fully outside
            vector<Point> originalLine = {p1, p2};
            vector<pair<Point, Color>> originalLinePixels = bresenhamAlgorithm.draw(originalLine, {GRAY});
            result.insert(result.end(), originalLinePixels.begin(), originalLinePixels.end());
        }

        return result;
    }



};