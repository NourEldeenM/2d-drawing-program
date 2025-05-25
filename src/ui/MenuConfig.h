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
            MenuItem("Clear Canvas", 20)
        };

        // Line algorithms
        menuItems[0].subItems = {
            MenuItem("DDA", 0),
            MenuItem("Bresenham", 1),
            MenuItem("Parametric", 2),
            MenuItem("Colored Parametric", 3)
        };

        // Circle algorithms
        menuItems[1].subItems = {
            MenuItem("Cartesian", 4),
            MenuItem("Polar", 5),
            MenuItem("Polar Iterative", 6),
            MenuItem("MidPoint DDA", 7),
            MenuItem("Enhanced MidPoint DDA", 8)
        };
        
        // Ellipse algorithms
        menuItems[2].subItems = {
            MenuItem("Cartesian", 14),
            MenuItem("Polar", 15),
            MenuItem("Polar Iterative", 16),
            MenuItem("MidPoint", 17),
            MenuItem("MidPoint DDA", 18)
        };

        // Curve algorithms
        menuItems[3].subItems = {
            MenuItem("Quadratic", 9),
            MenuItem("Bezier", 10),
            MenuItem("Hermite", 12),
            MenuItem("Cardinal Spline", 13)
        };
        
        // Filling Algorithms
        menuItems[4].subItems = {
            MenuItem("Flood Fill", 11)
        };
        
        // Circle Quarter Filling Algorithms
        menuItems[5].subItems = {
            MenuItem("Circle Quarter Line Fill", 19),
        };
        return menuItems;
    }
};