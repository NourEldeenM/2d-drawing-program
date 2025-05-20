# 2d-drawing-program

Used *raylib* (checkout [raylib documentation](https://www.raylib.com/index.html)) for cheatsheets and examples.
## How to setup raylib for GUI
1. Go to [Raylib's GitHub releases](https://github.com/raysan5/raylib/releases)
2. Download the latest `raylib-5.0_win64_mingw-w64.zip` (for MinGW) or `raylib-5.0_win64_msvc20XX.zip` (for MSVC)
3. Extract the zip file to a location like `C:\raylib`

## Build and Run
1. Open Command Palette (Ctrl+Shift+P)
2. Run "Tasks: Run Build Task"
3. Run the executable from terminal:
```bash
.\game.exe
```

## Folder Structure

```plaintext
GraphicsApp/
├── src/
│   ├── algorithms/
│   │   ├── DrawingAlgorithm.h
|   |   ├── LineDDA.cpp
│   │   ├── BresenhamCircle.cpp
│   │   └── ...
│   ├── ui/
│   │   └── GUI.cpp
│   ├── utils/
│   │   └── matrixUtils.cpp
│   └── main.cpp
├── .gitignore
├── Project Description.pdf
└── README.md
```
