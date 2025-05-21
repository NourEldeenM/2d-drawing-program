#include "../DrawingAlgorithm.h"
#include <vector>
using namespace std;

void DrawPoints(Point center, Point p, vector<Point>& points){
	int dx[] = { p.x, -p.x, p.x, -p.x, p.y, -p.y, p.y, -p.y };
	int dy[] = { p.y, p.y, -p.y, -p.y, p.x, p.x, -p.x, -p.x };
	for (int i = 0; i < 8; i++)
        points.push_back({center.x + dx[i], center.y + dy[i]});
}