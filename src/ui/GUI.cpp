#include <raylib.h>
#include <vector>
#include "../algorithms/DrawingAlgorithm.h"
#include <iostream>
#include <map>
#include "../algorithms/LineDrawingAlgos/BresenhamLineAlgorithm.cpp"
#include "../algorithms/LineDrawingAlgos/DDALineAlgorithm.cpp"
#include "../algorithms/LineDrawingAlgos/ParametricLineAlgorithm.cpp"
#include "../algorithms/CircleDrawingAlgos/CircleCartesian.cpp"
#include "../algorithms/CircleDrawingAlgos/CircleMidPointDDA.cpp"
#include "../algorithms/CircleDrawingAlgos/CircleMidPointDDAModified.cpp"
#include "../algorithms/CircleDrawingAlgos/CirclePolar.cpp"
#include "../algorithms/CircleDrawingAlgos/CirclePolarIterative.cpp"
#include "../algorithms/QuadAndCubicCurvesAlgos/BezierCurveAlgorithm.cpp"
#include "../algorithms/QuadAndCubicCurvesAlgos/HermiteCurveAlgorithm.cpp"
#include "../algorithms/QuadAndCubicCurvesAlgos/CardinalSplineCurve.cpp"
#include "../algorithms/QuadAndCubicCurvesAlgos/QuadraticCurveAlgorithm.cpp"
#include "../algorithms/FillingAlgos/FloodFillAlgorithm.cpp"
#include "../algorithms/EllipseDrawingAlgos/EllipseCartesianAlgorithm.cpp"
#include "../algorithms/EllipseDrawingAlgos/EllipsePolarAlgorithm.cpp"
#include "../algorithms/EllipseDrawingAlgos/EllipsePolar2Algorithm.cpp"
#include "../algorithms/EllipseDrawingAlgos/EllipseMidPointAlgorithm.cpp"
#include "../algorithms/EllipseDrawingAlgos/EllipseMidPointDDAAlgorithm.cpp"

using namespace std;

struct MenuItem
{
    string label;
    vector<MenuItem> subItems;
    int algorithmId;
    Rectangle bounds;
    bool isExpanded;

    MenuItem(string l, int id = -1) : label(l), algorithmId(id), isExpanded(false) {}
};

class GUI
{
private:
    DrawingAlgorithm *currentAlgorithm;
    vector<Point> inputPoints;
    vector<vector<pair<Point, Color>>> drawnShapes;
    int screenWidth;
    int screenHeight;
    vector<Color> drawingColor;

    vector<MenuItem> menuItems;
    bool menuExpanded;
    Rectangle menuButton;
    MenuItem *activeSubmenu;
    // vector<Rectangle> menuOptions;
    // vector<const char *> menuOptionLabels;
    // int selectedOption;

public:
    GUI()
    {
        currentAlgorithm = new DDALineAlgorithm();
        drawingColor.push_back(BLACK);

        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
        cout << screenHeight << " " << screenWidth << endl;

        // inputPoints.clear();

        menuExpanded = false;
        menuButton = {10, 10, 120, 40};

        menuItems = {
            MenuItem("Line", -1),
            MenuItem("Circle", -1),
            MenuItem("Ellipse", -1),
            MenuItem("Curves", -1),
            MenuItem("Fill", -1),
            MenuItem("Clear Canvas", 19)};

        // Add subitems
        menuItems[0].subItems = {
            MenuItem("DDA", 0),
            MenuItem("Bresenham", 1),
            MenuItem("Parametric", 2),
            MenuItem("Colored Parametric", 3)};

        menuItems[1].subItems = {
            MenuItem("Cartesian", 4),
            MenuItem("Polar", 5),
            MenuItem("Polar Iterative", 6),
            MenuItem("MidPoint DDA", 7),
            MenuItem("Enhanced MidPoint DDA", 8)};

        menuItems[2].subItems = {
            MenuItem("Cartesian", 14),
            MenuItem("Polar", 15),
            MenuItem("Polar Iterative", 16),
            MenuItem("MidPoint", 17),
            MenuItem("MidPoint DDA", 18)};

        menuItems[3].subItems = {
            MenuItem("Quadratic", 9),
            MenuItem("Bezier", 10),
            MenuItem("Hermite", 12),
            MenuItem("Cardinal Spline", 13)};

        menuItems[4].subItems = {
            MenuItem("Flood Fill", 11)};

        activeSubmenu = nullptr;
    }

    ~GUI()
    {
        if (currentAlgorithm)
        {
            delete currentAlgorithm;
            currentAlgorithm = nullptr;
        }
    }

    void run()
    {
        InitWindow(screenWidth, screenHeight, "2d drawing program");
        SetTargetFPS(60);
        while (!WindowShouldClose())
        {
            handleInput();
            render();
        }
        CloseWindow();
    }

    void handleInput()
    {
        Vector2 mousePoint = GetMousePosition();
        if (handleMenuButtonClick(mousePoint))
            return;
        if (handleMenuOptionSelection(mousePoint))
            return;
        handleCanvasClick(mousePoint);
    }

    bool handleMenuButtonClick(const Vector2 &mousePoint)
    {
        if (CheckCollisionPointRec(mousePoint, menuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            menuExpanded = !menuExpanded;
            return true;
        }
        return false;
    }

    bool handleMenuOptionSelection(const Vector2 &mousePoint)
    {
        if (!menuExpanded)
            return false;

        for (auto &item : menuItems)
        {
            if (CheckCollisionPointRec(mousePoint, item.bounds))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if (!item.subItems.empty())
                    {
                        // Toggle submenu
                        item.isExpanded = !item.isExpanded;
                        // Close other submenus
                        for (auto &other : menuItems)
                        {
                            if (&other != &item)
                                other.isExpanded = false;
                        }
                    }
                    else if (item.algorithmId >= 0)
                    {
                        handleMenuOptionsSelection(item.algorithmId);
                        menuExpanded = false;
                        return true;
                    }
                    return true;
                }
            }

            if (item.isExpanded)
            {
                for (auto &subItem : item.subItems)
                {
                    if (CheckCollisionPointRec(mousePoint, subItem.bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        if (subItem.algorithmId >= 0)
                        {
                            handleMenuOptionsSelection(subItem.algorithmId);
                            menuExpanded = false;
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    void handleMenuOptionsSelection(int i)
    {
        switch (i)
        {
        case 0: // Line (DDA)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new DDALineAlgorithm();
            break;
        case 1: // Line (Bresenham)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new BresenhamLineAlgorithm();
            break;
        case 2: // Line (Parametric)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new ParametricLineAlgorithm();
            break;
        case 3: // Colored Line (Parametric)
            if (currentAlgorithm)
                delete currentAlgorithm;
            drawingColor.push_back(YELLOW);
            currentAlgorithm = new ParametricLineAlgorithm();
            break;
        case 4: // Circle (Cartesian)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new CircleCartesianAlgorithm();
            break;
        case 5: // Circle (Polar)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new CirclePolarAlgorithm();
            break;
        case 6: // Circle (Polar Iterative)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new CirclePolarIterativeAlgorithm();
            break;
        case 7: // Circle (MidPoint DDA)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new CircleMidPointDDAAlgorithm();
            break;
        case 8: // Circle (Enhanced MidPoint DDA)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new CircleMidPointDDAModifiedAlgorithm();
            break;
        case 9: // Quadratic Curve
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new QuadraticCurveAlgorithm();
            break;
        case 10: // Bezier Curve
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new BezierCurveAlgorithm();
            break;
        case 11: // Flood Fill
            if (currentAlgorithm)
                delete currentAlgorithm;
            drawingColor.push_back(BLUE);
            currentAlgorithm = new FloodFillAlgorithm();
            break;
        case 12: // Hermite Curve
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new HermiteCurveAlgorithm();
            break;
        case 13: // Cardinal Spline
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new CardinalSplineAlgorithm();
            break;
        case 14: // Ellipse (Cartesian)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new EllipseCartesianAlgorithm();
            break;
        case 15: // Ellipse (Polar)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new EllipsePolarAlgorithm();
            break;
        case 16: // Ellipse (Polar Iterative)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new EllipsePolar2Algorithm();
            break;
        case 17: // Ellipse (MidPoint)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new EllipseMidPointAlgorithm();
            break;
        case 18: // Ellipse (MidPoint DDA)
            if (currentAlgorithm)
                delete currentAlgorithm;
            currentAlgorithm = new EllipseMidPointDDAAlgorithm();
            break;
        case 19: // Clear Canvas
            inputPoints.clear();
            drawnShapes.clear();
            break;
        }
    }

    void handleCanvasClick(const Vector2 &mousePoint)
    {
        if (!menuExpanded && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Point p = {GetMouseX(), GetMouseY()};
            // avoid clicks on menu button
            if (p.y > menuButton.y + menuButton.height || p.x > menuButton.x + menuButton.width)
            {
                inputPoints.push_back(p);
                if (currentAlgorithm && inputPoints.size() >= currentAlgorithm->getRequiredPoints())
                {
                    vector<pair<Point, Color>> shape = currentAlgorithm->draw(inputPoints, drawingColor);
                    if (!shape.empty())
                        drawnShapes.push_back(shape); // Store the shape
                    inputPoints.clear();              // Reset for next line
                }
            }
        }
    }

    void render()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawShapes();
        drawInputPoints();
        drawMenuButton();
        if (menuExpanded)
            drawMenuOptions();
        EndDrawing();
    }

    void drawMenuButton()
    {
        DrawRectangleRec(menuButton, SKYBLUE);
        DrawRectangleLinesEx(menuButton, 2, DARKBLUE);
        DrawText("Menu", menuButton.x + 30, menuButton.y + 10, 20, DARKBLUE);
    }

    void drawMenuOptions()
    {
        float yOffset = menuButton.y + menuButton.height + 5;

        for (auto &item : menuItems)
        {
            item.bounds = {menuButton.x, yOffset, 200, 40};
            Color bgColor = RAYWHITE;
            DrawRectangleRec(item.bounds, bgColor);
            DrawRectangleLinesEx(item.bounds, 1, DARKGRAY);
            DrawText(item.label.c_str(), item.bounds.x + 10, item.bounds.y + 10, 20, DARKGRAY);

            if (!item.subItems.empty())
            {
                DrawText(">", item.bounds.x + item.bounds.width - 20, item.bounds.y + 10, 20, DARKGRAY);
            }

            if (item.isExpanded)
            {
                float subX = item.bounds.x + item.bounds.width + 5;
                float subY = item.bounds.y;

                for (auto &subItem : item.subItems)
                {
                    subItem.bounds = {subX, subY, 200, 40};
                    DrawRectangleRec(subItem.bounds, RAYWHITE);
                    DrawRectangleLinesEx(subItem.bounds, 1, DARKGRAY);
                    DrawText(subItem.label.c_str(), subItem.bounds.x + 10, subItem.bounds.y + 10, 20, DARKGRAY);
                    subY += 45;
                }
            }

            yOffset += 45;
        }
    }

    void drawShapes()
    {
        for (const auto &shape : drawnShapes)
            for (const auto &p : shape)
                DrawPixel(p.first.x, p.first.y, p.second);
    }

    void drawInputPoints()
    {
        for (const Point &p : inputPoints)
            DrawCircle(p.x, p.y, 3, RED);
    }
};