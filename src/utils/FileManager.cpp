#pragma once
#include <vector>
#include <string>
#include <raylib.h>
#include <fstream>
#include <filesystem>
#include "../algorithms/DrawingAlgorithm.h"
#include <iostream>

using namespace std;

namespace fs = filesystem;

class FileManager
{
private:
    static void serializeShape(ofstream &out, const vector<pair<Point, Color>> &shape)
    {
        // Write number of points in this shape
        size_t numPoints = shape.size();
        out.write(reinterpret_cast<const char *>(&numPoints), sizeof(numPoints));

        // Write each point and its color
        for (const auto &point : shape)
        {
            out.write(reinterpret_cast<const char *>(&point.first), sizeof(Point));
            out.write(reinterpret_cast<const char *>(&point.second), sizeof(Color));
        }
    }
    
    static void deserializeShape(ifstream &in, vector<pair<Point, Color>> &shape)
    {
        // Read number of points in this shape
        size_t numPoints;
        in.read(reinterpret_cast<char *>(&numPoints), sizeof(numPoints));

        // Reserve space for efficiency
        shape.reserve(numPoints);

        // Read each point and its color
        for (size_t j = 0; j < numPoints; j++)
        {
            Point p;
            Color c;
            in.read(reinterpret_cast<char *>(&p), sizeof(Point));
            in.read(reinterpret_cast<char *>(&c), sizeof(Color));
            shape.emplace_back(p, c);
        }
    }

public:
    static void saveDrawings(const vector<vector<pair<Point, Color>>> &shapes, const string &filename)
    {
        fs::path filePath = fs::current_path() / filename;
        ofstream outFile(filePath, ios::binary);

        // Write number of shapes
        size_t numShapes = shapes.size();
        outFile.write(reinterpret_cast<const char *>(&numShapes), sizeof(numShapes));

        // Write each shape
        for (const auto &shape : shapes)
            serializeShape(outFile, shape);

        outFile.close();
    }

    static bool loadDrawings(vector<vector<pair<Point, Color>>> &shapes, const string &filename)
    {
        fs::path filePath = fs::current_path() / filename;
        ifstream inFile(filePath, ios::binary);

        if (!inFile)
        {
            return false;
        }

        // Read number of shapes
        size_t numShapes;
        inFile.read(reinterpret_cast<char *>(&numShapes), sizeof(numShapes));

        // Clear existing shapes
        shapes.reserve(numShapes);

        // Read each shape
        for (size_t i = 0; i < numShapes; i++)
        {
            vector<pair<Point, Color>> shape;
            deserializeShape(inFile, shape);
            shapes.push_back(std::move(shape));
        }

        inFile.close();
        return true;
    }
};