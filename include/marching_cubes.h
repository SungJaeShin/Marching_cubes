#ifndef MARCHING_CUBES
#define MARCHING_CUBES

#include "include.h"
#include "utility.h"
#include "loopup_table.h"

void init_voxel_vertices(PointCloud pointcloud, Voxel &voxel, 
                         float cur_x, float cur_y, float cur_z,
                         float diff_x, float diff_y, float diff_z)
{
    cv::Point3f v0(cur_x, cur_y, cur_z);
    cv::Point3f v1(cur_x, cur_y + diff_y, cur_z);
    cv::Point3f v2(cur_x + diff_x, cur_y + diff_y, cur_z);
    cv::Point3f v3(cur_x + diff_x, cur_y, cur_z);
    cv::Point3f v4(cur_x, cur_y, cur_z + diff_z);
    cv::Point3f v5(cur_x, cur_y + diff_y, cur_z + diff_z);
    cv::Point3f v6(cur_x + diff_x, cur_y + diff_y, cur_z + diff_z);
    cv::Point3f v7(cur_x + diff_x, cur_y, cur_z + diff_z);

    voxel.vertices.push_back(v0);
    voxel.vertices.push_back(v1);
    voxel.vertices.push_back(v2);
    voxel.vertices.push_back(v3);
    voxel.vertices.push_back(v4);
    voxel.vertices.push_back(v5);
    voxel.vertices.push_back(v6);
    voxel.vertices.push_back(v7);

    for(int i = 0; i < voxel.vertices.size(); i++)
    {
        cv::Point3f vertex = voxel.vertices[i];
        auto it = std::find(pointcloud.vertices.begin(), pointcloud.vertices.end(), vertex);

        if(it == pointcloud.vertices.end())
            voxel.density.push_back(get_random_number());            
        else
        {
            int idx = it - pointcloud.vertices.begin();
            voxel.density.push_back(pointcloud.density[idx - 1]);
        }
    }
}

int calculate_cubes_index(Voxel voxel, float isolevel)
{
    int cubeindex = 0;
    for(int t = 0; t < voxel.vertices.size(); t++)
        if(voxel.density[t] < isolevel)
            cubeindex |= (1 << t);

    return cubeindex;
}

int get_edge_index(int cubeindex)
{
    return edgeTable[cubeindex];
}

std::vector<cv::Point3f> cal_inter_vertices(Voxel cur_voxel, int edgeIndex, float isolevel)
{
    std::vector<cv::Point3f> inter_points(12);

    if (edgeIndex & 1)
        inter_points[0] = interpolation(cur_voxel.vertices[0], cur_voxel.vertices[1], cur_voxel.density[0], cur_voxel.density[1], isolevel);
    if (edgeIndex & 2)
        inter_points[1] = interpolation(cur_voxel.vertices[1], cur_voxel.vertices[2], cur_voxel.density[1], cur_voxel.density[2], isolevel);
    if (edgeIndex & 4)
        inter_points[2] = interpolation(cur_voxel.vertices[2], cur_voxel.vertices[3], cur_voxel.density[2], cur_voxel.density[3], isolevel);
    if (edgeIndex & 8)
        inter_points[3] = interpolation(cur_voxel.vertices[3], cur_voxel.vertices[0], cur_voxel.density[3], cur_voxel.density[0], isolevel);
    if (edgeIndex & 16)
        inter_points[4] = interpolation(cur_voxel.vertices[4], cur_voxel.vertices[5], cur_voxel.density[4], cur_voxel.density[5], isolevel);
    if (edgeIndex & 32)
        inter_points[5] = interpolation(cur_voxel.vertices[5], cur_voxel.vertices[6], cur_voxel.density[5], cur_voxel.density[6], isolevel);
    if (edgeIndex & 64)
        inter_points[6] = interpolation(cur_voxel.vertices[6], cur_voxel.vertices[7], cur_voxel.density[6], cur_voxel.density[7], isolevel);
    if (edgeIndex & 128)
        inter_points[7] = interpolation(cur_voxel.vertices[7], cur_voxel.vertices[4], cur_voxel.density[7], cur_voxel.density[4], isolevel);
    if (edgeIndex & 256)
        inter_points[8] = interpolation(cur_voxel.vertices[0], cur_voxel.vertices[4], cur_voxel.density[0], cur_voxel.density[4], isolevel);
    if (edgeIndex & 512)
        inter_points[9] = interpolation(cur_voxel.vertices[1], cur_voxel.vertices[5], cur_voxel.density[1], cur_voxel.density[5], isolevel);
    if (edgeIndex & 1024)
        inter_points[10] = interpolation(cur_voxel.vertices[2], cur_voxel.vertices[6], cur_voxel.density[2], cur_voxel.density[6], isolevel);
    if (edgeIndex & 2048)
        inter_points[11] = interpolation(cur_voxel.vertices[3], cur_voxel.vertices[7], cur_voxel.density[3], cur_voxel.density[7], isolevel);

    return inter_points;
}

void make_triangle(std::vector<Triangle> &triangle, std::vector<cv::Point3f> inter_points, int cubeIndex)
{
    for (int i = 0; triangleTable[cubeIndex][i] != -1; i += 3)
    {
        Triangle tmp_triangle;

        cv::Point3f vertex1 = inter_points[triangleTable[cubeIndex][i]];
        cv::Point3f vertex2 = inter_points[triangleTable[cubeIndex][i + 1]];
        cv::Point3f vertex3 = inter_points[triangleTable[cubeIndex][i + 2]];
 
        tmp_triangle.vertices.push_back(vertex1);
        tmp_triangle.vertices.push_back(vertex2);
        tmp_triangle.vertices.push_back(vertex3);

        triangle.push_back(tmp_triangle);
    }
}

#endif