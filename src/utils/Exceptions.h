#include <stdexcept>
#include <string>

using namespace std;

class DrawingException : public runtime_error
{
public:
    DrawingException(const string &message) : runtime_error(message) {}
};

/* Usage in code
try {
    currentAlgorithm->draw(inputPoints, drawingColors);
} catch (const DrawingException& e) {
    cout << "Drawing error: " << e.what() << endl;
}
*/