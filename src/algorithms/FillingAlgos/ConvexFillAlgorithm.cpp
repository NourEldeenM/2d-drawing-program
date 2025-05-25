#include "../DrawingAlgorithm.h"
#include "../LineDrawingAlgos/DDALineAlgorithm.cpp"
#include <algorithm>

using namespace std;

class ConvexFill : public DrawingAlgorithm
{
private:
    struct EdgeEntry
    {
        int xLeft = INT_MAX;
        int xRight = INT_MIN;
    };

    vector<EdgeEntry> edgeTable;

    void pushLinesToResult(const vector<vector<pair<Point, Color>>> &lineResults,
                           vector<pair<Point, Color>> &result)
    {
        for (const auto &line : lineResults)
        {
            result.insert(result.end(), line.begin(), line.end());
        }
    }

    void initEdgeTable(const vector<Point> &pts)
    {
        // Find y bounds
        int minY = pts[0].y, maxY = pts[0].y;
        for (const auto &p : pts)
        {
            minY = min(minY, p.y);
            maxY = max(maxY, p.y);
        }

        // Resize edge table to fit the polygon
        edgeTable.resize(maxY - minY + 1);

        // Initialize edge table entries
        for (auto &entry : edgeTable)
        {
            entry.xLeft = INT_MAX;
            entry.xRight = INT_MIN;
        }
    }

    void polygonToTable(const vector<Point> &pts)
    {
        int n = pts.size();
        int minY = INT_MAX;
        for (auto p : pts)
            minY = (p.y < minY) ? p.y : minY;

        for (int i = 0; i < n; i++)
        {
            Point v1 = pts[i];
            Point v2 = pts[(i + 1) % n];
            edgeToTable(v1, v2, minY);
        }
    }

    void edgeToTable(Point v1, Point v2, int minY)
    {
        if (v1.y == v2.y)
            return; // Skip horizontal edges

        // Ensure v1 is above v2
        if (v1.y > v2.y)
            swap(v1, v2);

        double x = v1.x;
        double slopeInv = static_cast<double>(v2.x - v1.x) / (v2.y - v1.y);

        for (int y = v1.y; y < v2.y; y++)
        {
            int tableIndex = y - minY;
            if (tableIndex >= 0 && tableIndex < edgeTable.size())
            {
                edgeTable[tableIndex].xLeft = min(edgeTable[tableIndex].xLeft, static_cast<int>(ceil(x)));
                edgeTable[tableIndex].xRight = max(edgeTable[tableIndex].xRight, static_cast<int>(floor(x)));
            }
            x += slopeInv;
        }
    }

    vector<vector<pair<Point, Color>>> fillPolygon(const Color &fillColor, int minY)
    {
        DDALineAlgorithm lineDrawer;
        vector<vector<pair<Point, Color>>> lines;

        for (size_t i = 0; i < edgeTable.size(); i++)
        {
            if (edgeTable[i].xLeft <= edgeTable[i].xRight)
            {
                Point p1{edgeTable[i].xLeft, static_cast<int>(i + minY)};
                Point p2{edgeTable[i].xRight, static_cast<int>(i + minY)};
                vector<Point> points = {p1, p2};
                lines.push_back(lineDrawer.draw(points, {fillColor}));
            }
        }
        return lines;
    }

public:
    ConvexFill()
    {
        setName((char *)"Convex Fill");
        setRequiredPoints(4);
    }

    vector<pair<Point, Color>> draw(vector<Point> &pts, vector<Color> drawingColors = {BLACK}) override
    {
        if (pts.size() < 3)
            return {}; // Need at least 3 points for a polygon
        if (drawingColors.size() < 2)
            drawingColors.push_back(GREEN); // Default fill color

        vector<pair<Point, Color>> result;

        // Draw polygon outline
        vector<vector<pair<Point, Color>>> outlineResults = drawPolygon(pts, {drawingColors[0]});
        pushLinesToResult(outlineResults, result);

        // Find minimum Y coordinate
        int minY = pts[0].y;
        for (const auto &p : pts)
        {
            minY = min(minY, p.y);
        }

        // Initialize and fill edge table
        initEdgeTable(pts);
        polygonToTable(pts);

        // Fill polygon
        vector<vector<pair<Point, Color>>> fillResults = fillPolygon(drawingColors[1], minY);
        pushLinesToResult(fillResults, result);

        // Clear edge table
        edgeTable.clear();

        return result;
    }

    vector<vector<pair<Point, Color>>> drawPolygon(vector<Point> pts, vector<Color> drawingColors)
    {
        DDALineAlgorithm lineDrawer;
        int n = pts.size();
        vector<vector<pair<Point, Color>>> result;
        for (int i = 0; i < n; ++i)
        {
            vector<Point> v;
            v.push_back(pts[i]);
            v.push_back(pts[(i + 1) % n]);
            result.push_back(lineDrawer.draw(v, drawingColors));
        }
        return result;
    }
};