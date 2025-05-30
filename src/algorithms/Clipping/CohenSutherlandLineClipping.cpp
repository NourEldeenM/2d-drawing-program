#include "../DrawingAlgorithm.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include "../LineDrawingAlgos/BresenhamLineAlgorithm.cpp"
using namespace std;

class CohenSutherlandLineClippingAlgorithm : public DrawingAlgorithm
{
private:
    enum OutCode
    {
        INSIDE = 0, // 0000
        LEFT = 1,   // 0001
        RIGHT = 2,  // 0010
        BOTTOM = 4, // 0100
        TOP = 8     // 1000
    };

    struct ClippingWindow
    {
        int xmin, ymin, xmax, ymax;
        ClippingWindow(Point topLeft, Point bottomRight)
        {
            xmin = topLeft.x;
            ymin = topLeft.y;

            int width = abs(bottomRight.x - topLeft.x);
            int height = abs(bottomRight.y - topLeft.y);

            int squareSize = min(width, height);

            xmax = xmin + squareSize;
            ymax = ymin + squareSize;
        }
    };

    BresenhamLineAlgorithm bresenhamAlgorithm;

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

    void drawLineUsingBresenham(int x1, int y1, int x2, int y2, Color color, vector<pair<Point, Color>> &result)
    {
        vector<Point> linePoints = {{x1, y1}, {x2, y2}};
        vector<Color> colors = {color};

        vector<pair<Point, Color>> lineResult = bresenhamAlgorithm.draw(linePoints, colors);

        result.insert(result.end(), lineResult.begin(), lineResult.end());
    }

public:
    CohenSutherlandLineClippingAlgorithm()
    {
        setName((char *)"Cohen-Sutherland Line Clipping");
        setRequiredPoints(4);
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {BLACK}) override
    {
        vector<pair<Point, Color>> result;
        if (pts.size() < 4)
            return result;

        ClippingWindow window(pts[0], pts[1]);

        int origX1 = pts[2].x, origY1 = pts[2].y;
        int origX2 = pts[3].x, origY2 = pts[3].y;

        int x1 = origX1, y1 = origY1;
        int x2 = origX2, y2 = origY2;

        Color windowColor = RED;
        Color originalLineColor = GRAY;
        Color clippedLineColor = drawingColors.empty() ? BLACK : drawingColors.back();

        // Draw clipping window
        // Top edge
        for (int x = window.xmin; x <= window.xmax; x++)
        {
            result.push_back({{x, window.ymin}, windowColor});
            result.push_back({{x, window.ymax}, windowColor});
        }
        // Left and right edges
        for (int y = window.ymin; y <= window.ymax; y++)
        {
            result.push_back({{window.xmin, y}, windowColor});
            result.push_back({{window.xmax, y}, windowColor});
        }

        // Draw original line in gray (dimmed)
        drawLineUsingBresenham(origX1, origY1, origX2, origY2, originalLineColor, result);

        if (clipLine(x1, y1, x2, y2, window))
        {
            drawLineUsingBresenham(x1, y1, x2, y2, clippedLineColor, result);
        }

        return result;
    }
};