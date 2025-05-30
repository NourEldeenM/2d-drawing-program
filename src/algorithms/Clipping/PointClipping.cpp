#include "../DrawingAlgorithm.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class PointClippingAlgorithm : public DrawingAlgorithm
{
private:
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

    bool isPointInside(const Point &p, const ClippingWindow &window)
    {
        return (p.x >= window.xmin && p.x <= window.xmax &&
                p.y >= window.ymin && p.y <= window.ymax);
    }

public:
    PointClippingAlgorithm()
    {
        setName((char *)"Point Clipping");
        setRequiredPoints(3);
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {BLACK}) override
    {
        vector<pair<Point, Color>> result;
        if (pts.size() < 3)
            return result;

        ClippingWindow window(pts[0], pts[1]);
        Point pointToClip = pts[2];

        Color windowColor = RED;
        Color pointColor = drawingColors.empty() ? BLACK : drawingColors.back();
        Color clippedColor = GREEN;

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

        // Check if point is inside
        if (isPointInside(pointToClip, window))
        {
            // Point is inside - draw it in clipped color
            for (int dx = -2; dx <= 2; dx++)
            {
                for (int dy = -2; dy <= 2; dy++)
                {
                    if (dx * dx + dy * dy <= 4)
                    { // Circle
                        result.push_back({{pointToClip.x + dx, pointToClip.y + dy}, clippedColor});
                    }
                }
            }
        }
        else
        {
            // Point is outside - draw it in original color (dimmed)
            for (int dx = -2; dx <= 2; dx++)
            {
                for (int dy = -2; dy <= 2; dy++)
                {
                    if (dx * dx + dy * dy <= 4)
                    { // Circle
                        result.push_back({{pointToClip.x + dx, pointToClip.y + dy}, GRAY});
                    }
                }
            }
        }

        return result;
    }
};