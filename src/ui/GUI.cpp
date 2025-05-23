#include <raylib.h>
#include <vector>
#include <iostream>
#include <map>
#include "../algorithms/DrawingAlgorithm.h"
#include "../algorithms/AlgorithmFactory.h"
#include "MenuItem.h"
#include "MenuConfig.h"

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

    vector<MenuItem> menuItems;
    bool menuExpanded;
    Rectangle menuButton;
    MenuItem *activeSubmenu;

public:
    GUI()
    {
        currentAlgorithm = new DDALineAlgorithm();
        drawingColor.push_back(BLACK);
        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();

        menuExpanded = false;
        menuButton = {10, 10, 120, 40};

        menuItems = MenuConfig::createMainMenu();
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
        // Handle special cases first
        if (i == 19)
        { // Clear Canvas
            inputPoints.clear();
            drawnShapes.clear();
            return;
        }

        // Handle color modifications
        if (i == 3)
        { // Colored Parametric Line
            if (drawingColor.size() > 1) 
                drawingColor.pop_back();
            drawingColor.push_back(RED);
        }
        else if (i == 11)
        { // Flood Fill
            if (drawingColor.size() > 1)
                drawingColor.pop_back();
            drawingColor.push_back(BLUE);
        }

        // Create new algorithm
        auto newAlgorithm = AlgorithmFactory::createAlgorithm(i);
        if (newAlgorithm)
        {
            delete currentAlgorithm;
            currentAlgorithm = newAlgorithm.release();
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