#include <vector>
#include "../algorithms/DrawingAlgorithm.h"

class GUI
{
private:
    DrawingAlgorithm *currentAlgorithm;
    std::vector<Point> inputPoints;
    // Menu state, Raylib window settings, etc.
public:
    void run();
    void handleInput();
    void render();
};