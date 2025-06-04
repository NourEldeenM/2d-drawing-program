#include <raylib.h>
#include "../MenuItem.h"
#include <vector>
#include "../../core/DrawingState.cpp"
#include "../../utils/FileManager.cpp"
#include "../../algorithms/AlgorithmFactory.h"
#include "../MenuConfig.h"
#include <memory>

using namespace std;

class MenuBar
{
private:
    unique_ptr<DrawingState> &drawingState;
    unique_ptr<FileManager> &fileManager;
    vector<MenuItem> menuItems;
    bool menuExpanded;
    Rectangle menuButton;
    Rectangle loadButton;
    Rectangle saveButton;

public:
    MenuBar(unique_ptr<DrawingState> &state, unique_ptr<FileManager> &fm)
        : drawingState(state), fileManager(fm), menuExpanded(false)
    {
        menuButton = {10, 10, 120, 40};
        loadButton = {140, 10, 120, 40};
        saveButton = {280, 10, 120, 40};
        menuItems = MenuConfig::createMainMenu();
    }

    bool isMenuExpanded() const { return menuExpanded; }

    void render()
    {
        drawButtons();
        if (menuExpanded)
        {
            drawMenuOptions();
        }
    }

    void drawButtons()
    {
        drawButton(menuButton, (char *)"MENU", SKYBLUE, DARKBLUE);
        drawButton(loadButton, (char *)"LOAD", LIGHTGRAY, DARKGRAY);
        drawButton(saveButton, (char *)"SAVE", LIGHTGRAY, DARKGRAY);
    }

    void drawButton(Rectangle button, char *text, Color bgColor, Color borderTextColor)
    {
        DrawRectangleRec(button, bgColor);
        DrawRectangleLinesEx(button, 2, borderTextColor);
        DrawText(text, button.x + 30, button.y + 10, 20, borderTextColor);
    }

    void drawMenuOptions()
    {
        float yOffset = menuButton.y + menuButton.height + 5;

        for (auto &item : menuItems)
        {
            item.bounds = {menuButton.x, yOffset, 200, 40};
            DrawRectangleRec(item.bounds, RAYWHITE);
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

    bool handleInput(const Vector2 &mousePoint)
    {
        if (handleMenuButtonClick(mousePoint))
            return true;
        if (handleMenuOptionSelection(mousePoint))
            return true;
        if (handleLoadButtonClick(mousePoint))
            return true;
        if (handleSaveButtonClick(mousePoint))
            return true;
        return false;
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
        if (i == 0)
        { // Clear Canvas
            drawingState->clear();
            return;
        }

        if (i >= 100 && i <= 106)
        {
            Color newColor;
            switch (i)
            {
            case 100:
                newColor = BLACK;
                break;
            case 101:
                newColor = RED;
                break;
            case 102:
                newColor = BLUE;
                break;
            case 103:
                newColor = GREEN;
                break;
            case 104:
                newColor = YELLOW;
                break;
            case 105:
                newColor = MAGENTA;
                break;
            default:
                newColor = BLACK;
                break;
            }
            drawingState->setColor(newColor);
            return;
        }

        auto newAlgorithm = AlgorithmFactory::createAlgorithm(i);
        if (newAlgorithm)
        {
            drawingState->setAlgorithm(move(newAlgorithm));
        }
    }

    bool handleLoadButtonClick(const Vector2 &mousePoint)
    {
        if (CheckCollisionPointRec(mousePoint, loadButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            cout << "Load button clicked\n";
            vector<vector<pair<Point, Color>>> shapes;
            bool success = fileManager->loadDrawings(shapes, "saved_drawings");
            if (!success)
                return false;

            drawingState->clear(); // Clear existing shapes before loading
            for (const auto &shape : shapes)
            {
                drawingState->addShape(shape);
            }
            return true;
        }
        return false;
    }

    bool handleSaveButtonClick(const Vector2 &mousePoint)
    {
        if (CheckCollisionPointRec(mousePoint, saveButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            fileManager->saveDrawings(drawingState->getShapes(), "saved_drawings");
            cout << "Drawing saved successfully\n";
            return true;
        }
        return false;
    }
};