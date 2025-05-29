#pragma once
#include "MenuItem.h"
#include <vector>

using namespace std;

class MenuConfig
{
public:
    static vector<MenuItem> createMainMenu()
    {
        // Main menu items
        vector<MenuItem> menuItems = {
            MenuItem("Line", -1),
            MenuItem("Circle", -1),
            MenuItem("Ellipse", -1),
            MenuItem("Curves", -1),
            MenuItem("Fill", -1),
            MenuItem("CircleQuarterFill", -1),
            MenuItem("Color", -1),
            MenuItem("Clear Canvas", 0)};

        // Line algorithms
        menuItems[0].subItems = {
            MenuItem("DDA", 1),
            MenuItem("Bresenham", 2),
            MenuItem("Parametric", 3),
            MenuItem("Colored Parametric", 4)};

        // Circle algorithms
        menuItems[1].subItems = {
            MenuItem("Cartesian", 5),
            MenuItem("Polar", 6),
            MenuItem("Polar Iterative", 7),
            MenuItem("MidPoint DDA", 8),
            MenuItem("Enhanced MidPoint DDA", 9)};

        // Ellipse algorithms
        menuItems[2].subItems = {
            MenuItem("Cartesian", 15),
            MenuItem("Polar", 16),
            MenuItem("Polar Iterative", 17),
            MenuItem("MidPoint", 18),
            MenuItem("MidPoint DDA", 19)};

        // Curve algorithms
        menuItems[3].subItems = {
            MenuItem("Quadratic", 10),
            MenuItem("Bezier", 11),
            MenuItem("Hermite", 13),
            MenuItem("Cardinal Spline", 14)};

        // Filling Algorithms
        menuItems[4].subItems = {
            MenuItem("Flood Fill", 12),
            MenuItem("Convex Fill", 21),
            MenuItem("General Fill", 22),
            MenuItem("Square Fill Using Hermit Curve", 23),
            MenuItem("Rectangle Fill Using Bezier Curve", 24),
        };

        // Circle Quarter Filling Algorithms
        menuItems[5].subItems = {
            MenuItem("Circle Quarter Line Fill", 20),
        };
        menuItems[6].subItems = {
            MenuItem("Black", 100),
            MenuItem("Red", 101),
            MenuItem("Blue", 102),
            MenuItem("Green", 103),
            MenuItem("Yellow", 104),
            MenuItem("Magenta", 105)
        };
        return menuItems;
    }
};