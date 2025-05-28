#include <raylib.h>
#include <vector>
#include <queue>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include "../algorithms/DrawingAlgorithm.h"
#include "../algorithms/AlgorithmFactory.h"
#include "MenuItem.h"
#include "MenuConfig.h"

namespace fs = filesystem;

using namespace std;

class GUI
{
private:
    DrawingAlgorithm *currentAlgorithm;
    vector<Point> inputPoints;
    vector<vector<pair<Point, Color>>> drawnShapes;
    int screenWidth;
    int screenHeight;
    deque<Color> drawingColor;

    vector<MenuItem> menuItems;
    bool menuExpanded;
    Rectangle menuButton, loadButton, saveButton;
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
        loadButton = {140, 10, 120, 40};
        saveButton = {280, 10, 120, 40};

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
        SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
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
        if (handleLoadButtonClick(mousePoint))
            return;
        if (handleSaveButtonClick(mousePoint))
            return;
        handleCanvasClick(mousePoint);
    }

    bool handleMenuButtonClick(const Vector2 &mousePoint)
    {
        if (CheckCollisionPointRec(mousePoint, menuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            menuExpanded = !menuExpanded;
            cout<<"menu button clicked\n";
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
        if (i == 0)
        { // Clear Canvas
            inputPoints.clear();
            drawnShapes.clear();
            return;
        }

        // // Handle color modifications
        // if (i == 4)
        // { // Colored Parametric Line
        //     if (drawingColor.size() > 1)
        //         drawingColor.pop_back();
        //     drawingColor.push_back(RED);
        // }
        // else if (i == 12)
        // { // Flood Fill
        //     if (drawingColor.size() > 1)
        //         drawingColor.pop_back();
        //     drawingColor.push_back(BLUE);
        // }
        // else if (i == 21)
        // { // Convex Fill
        //     if (drawingColor.size() > 1)
        //         drawingColor.pop_back();
        //     drawingColor.push_back(GREEN);
        // }
        // else if (i == 22)
        // { // General Fill
        //     if (drawingColor.size() > 1)
        //         drawingColor.pop_back();
        //     drawingColor.push_back(YELLOW);
        // }
        // else 
        if (i >= 100 && i <= 106)
        {
            if (drawingColor.size() > 1)
                drawingColor.pop_front();

            switch (i)
            {
                case 100: drawingColor.push_back(BLACK); break;
                case 101: drawingColor.push_back(RED); break;
                case 102: drawingColor.push_back(BLUE); break;
                case 103: drawingColor.push_back(GREEN); break;
                case 104: drawingColor.push_back(YELLOW); break;
                case 105: drawingColor.push_back(MAGENTA); break;
                // case 106: drawingColor.push_back(CYAN); break;
                default: drawingColor.push_back(BLACK); break;
            }
            cout << "Color changed\n";
        }
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
                    vector<pair<Point, Color>> shape = currentAlgorithm->draw(inputPoints, vector<Color> (drawingColor.begin(),drawingColor.end()));
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
        if (menuExpanded)
            drawMenuOptions();
        drawButtons();
        EndDrawing();
    }

    void drawButton(Rectangle button, char *text, Color bgColor, Color borderTextColor)
    {
        DrawRectangleRec(button, bgColor);
        DrawRectangleLinesEx(button, 2, borderTextColor);
        DrawText(text, button.x + 30, button.y + 10, 20, borderTextColor);
    }

    void drawButtons()
    {
        drawButton(menuButton, (char *)"MENU", SKYBLUE, DARKBLUE);
        drawButton(loadButton, (char *)"LOAD", LIGHTGRAY, DARKGRAY);
        drawButton(saveButton, (char *)"SAVE", LIGHTGRAY, DARKGRAY);
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

    bool handleLoadButtonClick(const Vector2 &mousePoint)
    {
        if (CheckCollisionPointRec(mousePoint, loadButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            fs::path filePath = fs::current_path() / "saved_drawings";
            ifstream inFile(filePath, ios::binary);

            if (!inFile)
            {
                cout << "Error: Could not open file for reading\n";
                return false;
            }

            // // Clear existing shapes
            // drawnShapes.clear();

            // Read number of shapes
            size_t numShapes;
            inFile.read(reinterpret_cast<char *>(&numShapes), sizeof(numShapes));

            // Read each shape
            for (size_t i = 0; i < numShapes; i++)
            {
                // Read number of points in this shape
                size_t numPoints;
                inFile.read(reinterpret_cast<char *>(&numPoints), sizeof(numPoints));

                // Create a new shape
                vector<pair<Point, Color>> shape;
                shape.reserve(numPoints);

                // Read each point and its color
                for (size_t j = 0; j < numPoints; j++)
                {
                    Point p;
                    Color c;
                    inFile.read(reinterpret_cast<char *>(&p), sizeof(Point));
                    inFile.read(reinterpret_cast<char *>(&c), sizeof(Color));
                    shape.emplace_back(p, c);
                }

                drawnShapes.push_back(std::move(shape));
            }

            inFile.close();
            cout << "Loaded drawing from: " << filePath << '\n';
            return true;
        }
        return false;
    }
    
    bool handleSaveButtonClick(const Vector2 &mousePoint)
    {
        if (CheckCollisionPointRec(mousePoint, saveButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            fs::path filePath = fs::current_path() / "saved_drawings";
            ofstream outFile(filePath, ios::binary);

            // Write number of shapes
            size_t numShapes = drawnShapes.size();
            outFile.write(reinterpret_cast<const char *>(&numShapes), sizeof(numShapes));

            // Write each shape
            for (const auto &shape : drawnShapes)
            {
                // Write number of points in this shape
                size_t numPoints = shape.size();
                outFile.write(reinterpret_cast<const char *>(&numPoints), sizeof(numPoints));

                // Write each point and its color
                for (const auto &point : shape)
                {
                    outFile.write(reinterpret_cast<const char *>(&point.first), sizeof(Point));
                    outFile.write(reinterpret_cast<const char *>(&point.second), sizeof(Color));
                }
            }

            outFile.close();
            cout << "Saved drawing to: " << filePath << '\n';
            return true;
        }
        return false;
    }

};