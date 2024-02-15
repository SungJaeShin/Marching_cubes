#ifndef SAVE_PLY
#define SAVE_PLY

#include "include.h"
// ===============================================================
// this code following as: https://github.com/nihaljn/marching-cubes/blob/main/src/utilities.cpp
struct Point
{
    float x;
    float y;
    float z;

    bool operator<(const Point& rhs) const
    {
        if (x != rhs.x)
            return x < rhs.x;
        if (y != rhs.y)
            return y < rhs.y;
        return z < rhs.z;
    }
};

struct VertexContainer
{
    std::map<Point, int> vertexMap;
    std::vector<std::vector<int>> triangles;
};

std::vector<std::vector<Point>> triangles_to_point(std::vector<Triangle> triangles)
{
    std::vector<std::vector<Point>> point_triangles;
    for(int i = 0; i < triangles.size(); i++)
    {
        std::vector<Point> tmp;
        for(int j = 0; j < triangles[i].vertices.size(); j++)
        {
            Point pt;
            pt.x = triangles[i].vertices[j].x;
            pt.y = triangles[i].vertices[j].y;
            pt.z = triangles[i].vertices[j].z;

            tmp.push_back(pt);
        }
        point_triangles.push_back(tmp);
    }
    return point_triangles;
}

VertexContainer hash_vertices_to_indices(std::vector<std::vector<Point>> &triangles)
{
    VertexContainer container;
    int cnt = 0;
    for (auto &triangle: triangles)
    {
        std::vector<int> indices;
        for (auto &vertex: triangle)
        {
            if (container.vertexMap.count(vertex) == 0)
            {
                container.vertexMap[vertex] = cnt;
                cnt++;
            }
            indices.push_back(container.vertexMap[vertex]);
        }
        container.triangles.push_back(indices);
    }

    return container;
}

void write_to_ply(std::vector<cv::Point3f> pointcloud, std::vector<Triangle> &triangles, const char* path)
{
    std::vector<std::vector<Point>> cvt_triangles = triangles_to_point(triangles);
    VertexContainer container = hash_vertices_to_indices(cvt_triangles);
    
    std::ofstream outputFile;
    outputFile.open(path);

    outputFile << "ply\n";
    outputFile << "format ascii 1.0\n";
    outputFile << "element vertex " <<  pointcloud.size() << "\n";
    outputFile << "property float32 x\n"; 
    outputFile << "property float32 y\n";
    outputFile << "property float32 z\n";
    outputFile << "element face " << triangles.size() << "\n";
    outputFile << "property list uint8 int32 vertex_indices\n";
    outputFile << "end_header\n";

    std::vector<Point> vertices (container.vertexMap.size());
    for(int i = 0; i < pointcloud.size(); i++)
        outputFile << pointcloud[i].x << " " << pointcloud[i].y << " " << pointcloud[i].z << "\n";    

    for (auto &triangle: container.triangles)
    {
        outputFile << 3 << " ";
        for (int index: triangle)
            outputFile << index << " ";
        outputFile << "\n";
    }
}
// ===============================================================

#endif