#include <raylib.h>
#include <vector>
#include "../algorithms/DrawingAlgorithm.h"
#include "../algorithms/LineDDA.cpp"
#include <iostream>
#include <map>

using namespace std;

class GUI
{
private:
    DrawingAlgorithm *currentAlgorithm;
    vector<Point> inputPoints;
    vector<vector<Point>> drawnShapes;
    int screenWidth;
    int screenHeight;

    bool menuExpanded;
    Rectangle menuButton;
    vector<Rectangle> menuOptions;
    vector<const char *> menuOptionLabels;
    int selectedOption;

public:
    GUI()
    {
        currentAlgorithm = new LineDDA();

        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
        cout << screenHeight << " " << screenWidth << endl;

        // inputPoints.clear();

        menuExpanded = false;
        menuButton = {10, 10, 120, 40};
        selectedOption = -1;

        menuOptionLabels = {
            "Line (DDA)",
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

    void run() {
        InitWindow(screenWidth, screenHeight, "2d drawing program");
        SetTargetFPS(60);

        while (!WindowShouldClose()) {
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
                        currentAlgorithm = new LineDDA();
                        break;
                    case 1: // Clear Canvas
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
                if (currentAlgorithm && inputPoints.size() >= currentAlgorithm->getRequiredPoints()) {
                    vector<Point> shape = currentAlgorithm->draw(inputPoints);
                    if (!shape.empty())
                        drawnShapes.push_back(shape); // Store the shape
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

        if (menuExpanded) {
            for (int i = 0; i < menuOptions.size(); i++) {
                Color bgColor = (selectedOption == i) ? LIGHTGRAY : RAYWHITE; // highlight selected option
                DrawRectangleRec(menuOptions[i], bgColor);
                DrawRectangleLinesEx(menuOptions[i], 1, DARKGRAY);
                DrawText(menuOptionLabels[i], menuOptions[i].x + 10, menuOptions[i].y + 10, 20, DARKGRAY);
            }
        }
        
        // Draw all stored lines
        for (const auto &shape : drawnShapes) {
            for (const Point &p : shape) {
                DrawPixel(p.x, p.y, BLACK);
            }
        }

        // Draw current input points
        for (const Point &p : inputPoints) {
            DrawCircle(p.x, p.y, 3, RED);
        }

        EndDrawing();
    }
};