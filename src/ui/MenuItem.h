#pragma once
#include <string>
#include <vector>
#include <raylib.h>

struct MenuItem
{
    string label;
    vector<MenuItem> subItems;
    int algorithmId;
    Rectangle bounds;
    bool isExpanded;

    MenuItem(string l, int id = -1) : label(l), algorithmId(id), isExpanded(false) {}
};