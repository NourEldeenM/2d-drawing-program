#include <raylib.h>
#include <vector>
#include "../algorithms/DrawingAlgorithm.h"
#include "../algorithms/LineDDA.cpp"
#include <iostream>
#include <map>

using namespace std;

// map<int, DrawingAlgorithm> mp = {
//     {1, LineDDA}
// };

class GUI
{
private:
    DrawingAlgorithm *currentAlgorithm;
    std::vector<Point> inputPoints;

    const int screenWidth = 800;
    const int screenHeight = 450;

public:
    GUI() {
        currentAlgorithm = new LineDDA();
    }

    void run() {
        InitWindow(screenWidth, screenHeight, "2d drawing program");
        SetTargetFPS(60);
        

        while (!WindowShouldClose())
        {
            handleInput();
            render();
        }

        CloseWindow();
    }

    void handleInput() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Point p = {GetMouseX(), GetMouseY()};
            inputPoints.push_back(p);
            cout << "recorded Left Button click: " << p.x << ' ' << p.y << '\n';
            // If we have enough points for the current algorithm
        }
    }
    
    void render() {
        BeginDrawing();
        if (inputPoints.size() >= 2) {
            vector<Point> points = currentAlgorithm->draw(inputPoints);
            for (const Point &p : points) {
                DrawPixel(p.x, p.y, WHITE);
            }
            inputPoints.clear();
        }
        EndDrawing();
    }
};