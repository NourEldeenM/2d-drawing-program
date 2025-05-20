#include <vector>

struct Point
{
    int x, y;
};

class DrawingAlgorithm
{
public:
    virtual std::vector<Point> draw(const std::vector<Point> &inputPoints) = 0;
    virtual ~DrawingAlgorithm() = default;
};