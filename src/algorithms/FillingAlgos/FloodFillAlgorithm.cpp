#include "../DrawingAlgorithm.h"
#include <vector>
#include <queue>
#include <unordered_set>
#include <raylib.h>
using namespace std;

inline bool operator==(const Color& a, const Color& b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

class FloodFillAlgorithm : public DrawingAlgorithm {
public:
    FloodFillAlgorithm() {
        setName((char*)"Flood Fill");
        setRequiredPoints(1);
    }
    vector<pair<Point, Color>> draw(vector<Point>& pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.empty())
            return result;
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        Point start = pts[0];
        Color borderColor = drawingColors.empty() ? BLACK : drawingColors[0];
        Color fillColor = drawingColors.size() > 1 ? drawingColors[1] : BLACK;
        queue<Point> q;
        q.push(start);
        // Load the screen as an image once
        Image img = LoadImageFromScreen();
        int w = img.width, h = img.height;
        vector<vector<bool>> visited(w, vector<bool>(h, false));
        while (!q.empty()) {
            Point p = q.front();
            q.pop();
            if (p.x < 0 || p.x >= w || p.y < 0 || p.y >= h)
                continue;
            if (visited[p.x][p.y])
                continue;
            visited[p.x][p.y] = true;
            Color currentColor = GetImageColor(img, p.x, p.y);
            if (currentColor == fillColor  || currentColor == borderColor)
                continue;
            result.push_back({p, fillColor});
            for (int i = 0; i < 4; ++i)
                q.push({p.x + dx[i], p.y + dy[i]});
        }
        UnloadImage(img);
        return result;
    }
};
