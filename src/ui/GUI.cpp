#include <raylib.h>
#include <vector>
#include <queue>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include "../core/DrawingState.cpp"
#include "../utils/FileManager.cpp"
#include "./components/MenuBar.cpp"
#include "../algorithms/AlgorithmFactory.h"
#include "config/MenuItem.h"
#include "config/MenuConfig.h"

namespace fs = filesystem;
using namespace std;

class GUI
{
private:
    unique_ptr<DrawingState> drawingState;
    unique_ptr<FileManager> fileManager;
    unique_ptr<MenuBar> menuBar;
    int screenWidth;
    int screenHeight;

public:
    GUI()
    {
        drawingState = make_unique<DrawingState>();
        fileManager = make_unique<FileManager>();
        menuBar = make_unique<MenuBar>(drawingState, fileManager);
        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
    }

    void run()
    {
        InitWindow(screenWidth, screenHeight, "2d drawing program");
        SetTargetFPS(60);
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
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
        if (!menuBar->handleInput(mousePoint))
        {
            handleCanvasClick(mousePoint);
        }
    }

    void handleCanvasClick(const Vector2 &mousePoint)
    {
        if (!menuBar->isMenuExpanded() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Point p = {GetMouseX(), GetMouseY()};
            drawingState->addPoint(p);
        }
    }

    void render()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawingState->render();
        menuBar->render();
        EndDrawing();
    }
};