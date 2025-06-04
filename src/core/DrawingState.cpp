#pragma once
#include <vector>
#include <deque>
#include <memory>
#include <raylib.h>
#include "../algorithms/DrawingAlgorithm.h"

using namespace std;

class DrawingState
{
private:
    unique_ptr<DrawingAlgorithm> currentAlgorithm;
    vector<Point> inputPoints;
    vector<vector<pair<Point, Color>>> drawnShapes;
    deque<Color> drawingColors;

private:
    void drawShapes() const
    {
        for (const auto &shape : drawnShapes)
        {
            for (const auto &p : shape)
            {
                DrawPixel(p.first.x, p.first.y, p.second);
            }
        }
    }
    void drawInputPoints() const
    {
        for (const Point &p : inputPoints)
        {
            DrawCircle(p.x, p.y, 3, RED);
        }
    }

public:
    DrawingState()
    {
        drawingColors.push_back(BLACK); // Default color
    }
    ~DrawingState() = default;

    // Algorithm management
    void setAlgorithm(unique_ptr<DrawingAlgorithm> algorithm)
    {
        currentAlgorithm = move(algorithm);
        inputPoints.clear(); // Reset input points when changing algorithms
    }
    const DrawingAlgorithm *getCurrentAlgorithm() const { return currentAlgorithm.get(); }

    // Drawing operations
    void addPoint(const Point &point)
    {
        inputPoints.push_back(point);

        if (canCompleteDraw())
        {
            auto shape = currentAlgorithm->draw(inputPoints,
                                                vector<Color>(drawingColors.begin(), drawingColors.end()));

            if (!shape.empty())
            {
                drawnShapes.push_back(shape);
                inputPoints.clear();
            }
        }
    }
    void addShape(const vector<pair<Point, Color>> &shape)
    {
        if (!shape.empty())
        {
            drawnShapes.push_back(shape);
        }
    }
    void clear()
    {
        inputPoints.clear();
        drawnShapes.clear();
    }

    // Color management
    void setColor(Color color)
    {
        if (drawingColors.size() > 1)
        {
            drawingColors.pop_front();
        }
        drawingColors.push_back(color);
    }
    void addColor(Color color)
    {
        drawingColors.push_back(color);
    }
    const deque<Color> &getColors() const { return drawingColors; }

    // State queries
    bool canCompleteDraw() const
    {
        return currentAlgorithm &&
               inputPoints.size() >= currentAlgorithm->getRequiredPoints();
    }
    const vector<Point> &getInputPoints() const { return inputPoints; }
    const vector<vector<pair<Point, Color>>> &getShapes() const { return drawnShapes; }

    // Rendering
    void render() const
    {
        drawShapes();
        drawInputPoints();
    }
};