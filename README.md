# 2d-drawing-program

Used *raylib* (checkout [raylib documentation](https://www.raylib.com/index.html)) for cheatsheets and examples.
## How to setup raylib for GUI
1. Go to [Raylib's GitHub releases](https://github.com/raysan5/raylib/releases)
2. Download the latest `raylib-5.0_win64_mingw-w64.zip` (for MinGW) or `raylib-5.0_win64_msvc20XX.zip` (for MSVC)
3. Extract the zip file to a location like `C:\raylib`

## Configure the Build System
1. Create a `.vscode` folder in your project
2. For MinGW Create `tasks.json` in it with:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build with MinGW",
            "type": "shell",
            "command": "g++",
            "args": [
                "-o",
                "game.exe",
                "main.cpp",
                "-I", "C:\\raylib\\include", // adjust the path if you didn't install it in C:\raylib
                "-L", "C:\\raylib\\lib",
                "-lraylib",
                "-lopengl32",
                "-lgdi32",
                "-lwinmm"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"]
        }
    ]
}
```
4. For MSVC, put this instead:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build with MSVC",
            "type": "shell",
            "command": "cl",
            "args": [
                "/EHsc",
                "/I C:\\raylib\\include",
                "main.cpp",
                "/link",
                "/LIBPATH:C:\\raylib\\lib",
                "raylib.lib",
                "user32.lib",
                "gdi32.lib",
                "winmm.lib",
                "shell32.lib"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$msCompile"]
        }
    ]
}
```

## Build and Run
1. Open Command Palette (Ctrl+Shift+P)
2. Run "Tasks: Run Build Task"
3. Run the executable from terminal:
```bash
.\game.exe
```
