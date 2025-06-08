# 🎨 2D Drawing Program

A modern C++ application for creating 2D graphics using various drawing algorithms. Built with raylib for GUI rendering.

![project overview](public/project%20overview.png)

## ✨ Features

- 📝 Line Drawing Algorithms
  - DDA
  - Bresenham
  - Parametric
  - Colored Parametric

- ⭕ Circle Drawing
  - Cartesian
  - Polar
  - Polar Iterative
  - MidPoint DDA
  - Enhanced MidPoint DDA

- 🔄 Ellipse Drawing
  - Cartesian
  - Polar
  - Polar Iterative
  - MidPoint
  - MidPoint DDA

- 📊 Curve Drawing
  - Quadratic Curves
  - Bezier Curves
  - Hermite Curves
  - Cardinal Spline

- 🎯 Fill Algorithms
  - Flood Fill
  - Convex Fill

## 🏗️ Architecture

This application uses a modular structure for scalability and clarity. Below is a class diagram of key components.

![class diagram](public/class%20diagram.png)

### Core Components

1. **GUI** ([`src/ui/GUI.cpp`](src/ui/GUI.cpp))
   - Main application controller
   - Handles window management
   - Coordinates user input

2. **DrawingState** ([`src/core/DrawingState.cpp`](src/core/DrawingState.cpp))
   - Manages drawing state
   - Stores shapes and points
   - Handles color management

3. **MenuBar** ([`src/ui/components/MenuBar.cpp`](src/ui/components/MenuBar.cpp))
   - Handles menu interactions
   - Manages algorithm selection
   - Controls file operations

4. **FileManager** ([`src/utils/FileManager.cpp`](src/utils/FileManager.cpp))
   - Handles saving/loading drawings
   - Manages file serialization

## 📁 Project Structure

```plaintext
src/
|── public/
│   ├── class diagram.png
│   └── project overview.png
├── core/               # Core application logic
│   └── DrawingState.cpp # Manages drawing state
├── ui/                 # User interface components
│   ├── components/     # Reusable UI elements
│   |   └── MenuBar.cpp
│   |── config/        # UI configuration
|   |   |── MenuItem.h
│   |   └── MenuConfig.h
│   └── GUI.cpp         # Main GUI controller
├── utils/             # Utility classes
│   ├── FileManager.cpp  # File operations
│   └── Exceptions.h     # Custom exceptions
├── algorithms/        # Drawing algorithms
│   ├── LineDrawingAlgos/
│   ├── CircleDrawingAlgos/
│   ├── EllipseDrawingAlgos/
│   └── FillingAlgos/
└── main.cpp          # Entry point of the application
```

## 🚀 Getting Started

### Prerequisites

- C++ compiler (MinGW-w64 or MSVC)
- [raylib](https://www.raylib.com/) library

### Building the Project

1. Clone the repository

```bash
git clone https://github.com/yourusername/2d-drawing-program.git
cd 2d-drawing-program
```

2. Install raylib

- Download from [Raylib's GitHub releases](https://github.com/raysan5/raylib/releases)
- Extract to `C:\raylib`

3. Build the project using tasks.json file

```plaintext
CTRL+SHIFT+B
```

4. Run the program

```bash
.\game.exe
```

## 🎮 Usage

1. Launch the application
2. Use the top menu to select drawing algorithms
3. Click on the canvas to place points
4. Use save/load buttons to manage your drawings

## 🛠️ Technical Details

- **Memory Management**: Modern C++ with smart pointers
- **OOP practices**:
  - Factory Pattern for algorithms
  - SOLID principles for maintainability
- **Error Handling**: Custom exceptions for file operations and drawing errors

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

## 👥 Authors

- [Nour Eldeen Mohamed](https://github.com/NourEldeenM)
- [Youssef Abdulmoneim](https://github.com/youssefabdulmoneim)
- [Ebaa Mostafa](https://github.com/ebaaamostafa)
- [Omar Mahmoud](https://github.com/Omar-Mahmoud-25)
- [Moaz Mohamed](https://github.com/moazmesmail)

## 🙏 Acknowledgments

- [raylib](https://www.raylib.com/) for the awesome graphics library
- Computer Graphics course materials and references
