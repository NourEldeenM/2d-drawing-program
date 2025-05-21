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
#include "../algorithms/QuadAndCubicCurvesAlgos/QuadraticCurveAlgorithm.cpp"


using namespace std;

class GUI
{
private:
    DrawingAlgorithm *currentAlgorithm;
    vector<Point> inputPoints;
    vector<vector<pair<Point, Color>>> drawnShapes;
    int screenWidth;
    int screenHeight;
    vector<Color> drawingColor;

    bool menuExpanded;
    Rectangle menuButton;
    vector<Rectangle> menuOptions;
    vector<const char *> menuOptionLabels;
    int selectedOption;
    bool isColoredLine;

public:
    GUI()
    {
        currentAlgorithm = new DDALineAlgorithm();
        isColoredLine = false;
        drawingColor.push_back(BLACK);

        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
        cout << screenHeight << " " << screenWidth << endl;

        // inputPoints.clear();

        menuExpanded = false;
        menuButton = {10, 10, 120, 40};
        selectedOption = -1;

        menuOptionLabels = {
            "Line (DDA)",
            "Line (Bresenham)",
            "Line (Parametric)",
            "Colored Line (Parametric)",
            "Circle (Cartesian)",
            "Circle (Polar)",
            "Circle (Polar Iterative)",
            "Circle (MidPoint DDA)",
            "Circle (Enhanced MidPoint DDA)",
            "Quadratic Curve",
            "Bezier Curve",
            "Clear Canvas"};

        for (int i = 0; i < menuOptionLabels.size(); i++)
        {
            menuOptions.push_back({10, 60 + i * 45, 200, 40});
        }
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

        // Check for menu button click
        if (CheckCollisionPointRec(mousePoint, menuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            menuExpanded = !menuExpanded;
            return;
        }

        // Check for menu option selection if menu is expanded
        if (menuExpanded)
        {
            for (int i = 0; i < menuOptions.size(); i++)
            {
                if (CheckCollisionPointRec(mousePoint, menuOptions[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    switch (i)
                    {
                    case 0: // Line (DDA)
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new DDALineAlgorithm();
                        isColoredLine = false;
                        break;

                    case 1: // Line (Bresenham)
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new BresenhamLineAlgorithm();
                        isColoredLine = false;
                        break;

                    case 2: // Line (Parametric)
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new ParametricLineAlgorithm();
                        isColoredLine = false;
                        break;

                    case 3: // Colored Line (Parametric)
                    {
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        auto paramLine = new ParametricLineAlgorithm();
                        drawingColor.push_back(YELLOW);
                        currentAlgorithm = paramLine;
                        isColoredLine = true;
                        break;
                    }
                    case 4: // Circle (Cartesian)
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new CircleCartesianAlgorithm();
                        isColoredLine = false;
                        break;
                    case 5: // Circle (Polar)
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new CirclePolarAlgorithm();
                        isColoredLine = false;
                        break;
                    case 6: // Circle (Polar Iterative)
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new CirclePolarIterativeAlgorithm();
                        isColoredLine = false;
                        break;
                    case 7: // Circle (MidPoint DDA)
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new CircleMidPointDDAAlgorithm();
                        isColoredLine = false;
                        break;
                    case 8: // Circle (Enhanced MidPoint DDA)
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new CircleMidPointDDAModifiedAlgorithm();
                        isColoredLine = false;
                        break;
                    case 9: // Quadratic Curve
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new QuadraticCurveAlgorithm();
                        isColoredLine = false;
                        break;
                    case 10: // Bezier Curve
                        if (currentAlgorithm)
                            delete currentAlgorithm;
                        currentAlgorithm = new BezierCurveAlgorithm();
                        isColoredLine = false;
                        break;
                    case 11: // Clear Canvas
                        inputPoints.clear();
                        drawnShapes.clear();
                        break;
                    }
                    menuExpanded = false;
                    selectedOption = i;
                    return;
                }
            }
        }

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
                    {
                        drawnShapes.push_back(shape); // Store the shape
                    }
                    inputPoints.clear(); // Reset for next line
                }
            }
        }
    }

    void render()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw menu button
        DrawRectangleRec(menuButton, SKYBLUE);
        DrawRectangleLinesEx(menuButton, 2, DARKBLUE);
        DrawText("Menu", menuButton.x + 30, menuButton.y + 10, 20, DARKBLUE);

        if (menuExpanded)
        {
            for (int i = 0; i < menuOptions.size(); i++)
            {
                Color bgColor = (selectedOption == i) ? LIGHTGRAY : RAYWHITE; // highlight selected option
                DrawRectangleRec(menuOptions[i], bgColor);
                DrawRectangleLinesEx(menuOptions[i], 1, DARKGRAY);
                DrawText(menuOptionLabels[i], menuOptions[i].x + 10, menuOptions[i].y + 10, 20, DARKGRAY);
            }
        }

        // Draw all stored shapes
        for (const auto &shape : drawnShapes)
        {
            for (const auto &p : shape)
            {
                DrawPixel(p.first.x, p.first.y, p.second);
            }
        }

        // if (isColoredLine && dynamic_cast<ParametricLineAlgorithm *>(currentAlgorithm))
        // {
        //     auto paramAlgorithm = dynamic_cast<ParametricLineAlgorithm *>(currentAlgorithm);
        //     const auto &coloredPoints = paramAlgorithm->getColoredPoints();

        //     if (!coloredPoints.empty() && !drawnShapes.empty())
        //     {
        //         for (const auto &cp : coloredPoints)
        //         {
        //             DrawPixel(cp.x, cp.y, Color{(unsigned char)cp.r, (unsigned char)cp.g, (unsigned char)cp.b, 255});
        //         }
        //     }
        // }

        // Draw current input points
        for (const Point &p : inputPoints)
        {
            DrawCircle(p.x, p.y, 3, RED);
        }

        EndDrawing();
    }
};