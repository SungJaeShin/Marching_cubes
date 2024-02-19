#ifndef UTILITY
#define UTILITY

#include "include.h"
#include "parameters.h"

// ===============================================================
// For random 3D points generation
// ideas from this code: https://github.com/nihaljn/marching-cubes/blob/main/src/generator.cpp
float get_random_number()
{
	float randomNumber = (float)rand() / RAND_MAX;
	randomNumber -= 0.5;
	randomNumber *= 2.0;

	return randomNumber;
}

std::vector<cv::Point3f> generate_random_grid()
{
    std::vector<cv::Point3f> scalarFunction;

	for (int i = 0; i < GRID_MAX; i++)
		for (int j = 0; j < GRID_MAX; j++)
            for (int k = 0; k < GRID_MAX; k++)
                scalarFunction.push_back(cv::Point3f(i, j, k));			

	return scalarFunction;
}

// std::map is not applied cv::Point value !! 
PointCloud add_random_density(std::vector<cv::Point3f> pointcloud)
{
    PointCloud scalarFunction;
    
    for(int i = 0; i < pointcloud.size(); i++)
    {
        cv::Point3f tmp_pt = pointcloud[i];
        scalarFunction.vertices.push_back(tmp_pt);
        scalarFunction.density.push_back(-1);
    }
                
	return scalarFunction;
}
// ===============================================================

std::vector<cv::Point3f> get_pointcloud_from_txt(cv::String ply_path)
{
    std::vector<cv::Point3f> pointcloud;

	float x, y, z;
	FILE* inputFile = fopen(ply_path.c_str(), "r");
	while (fscanf(inputFile, "%f %f %f", &x, &y, &z) != EOF)
        pointcloud.push_back(cv::Point3f((int)x, (int)y, (int)z));

	return pointcloud;
}

std::vector<cv::Point3f> get_pointcloud_from_ply(cv::String ply_path)
{
    // Read Ply files
    cv::viz::Mesh ply_file = cv::viz::readMesh(ply_path);
    cv::Mat tmp_pointcloud = ply_file.cloud;

    // Pointcloud size
    int count = 0;
    std::vector<cv::Point3f> pointcloud;
    for(int i = 0; i < tmp_pointcloud.cols; i++)
    {
        if(count == 2)
        {
            float x = tmp_pointcloud.at<float>(0, i-2);
            float y = tmp_pointcloud.at<float>(0, i-1);
            float z = tmp_pointcloud.at<float>(0, i);
            cv::Point3f tmp_pt((int)x, (int)y, (int)z);

            pointcloud.push_back(tmp_pt);
            count = 0;
            continue;
        }
        count++;
    }

    return pointcloud;
}

// find Max pixel values to make Voxel
void find_max_pixel(std::vector<cv::Point3f> pointcloud, float &max_x, float &max_y, float &max_z)
{
    float tmp_x = pointcloud[0].x;
    float tmp_y = pointcloud[0].y;
    float tmp_z = pointcloud[0].z;
    for(int t = 1; t < pointcloud.size(); t++)
    {
        if(pointcloud[t].x > tmp_x)
            tmp_x = pointcloud[t].x;
        if(pointcloud[t].y > tmp_y)
            tmp_y = pointcloud[t].y;
        if(pointcloud[t].z > tmp_z)
            tmp_z = pointcloud[t].z;
    }

    max_x = tmp_x;
    max_y = tmp_y;
    max_z = tmp_z;
}

// find Max pixel values to make Voxel
void find_min_pixel(std::vector<cv::Point3f> pointcloud, float &min_x, float &min_y, float &min_z)
{
    float tmp_x = pointcloud[0].x;
    float tmp_y = pointcloud[0].y;
    float tmp_z = pointcloud[0].z;
    for(int t = 1; t < pointcloud.size(); t++)
    {
        if(pointcloud[t].x < tmp_x)
            tmp_x = pointcloud[t].x;
        if(pointcloud[t].y < tmp_y)
            tmp_y = pointcloud[t].y;
        if(pointcloud[t].z < tmp_z)
            tmp_z = pointcloud[t].z;
    }

    min_x = tmp_x;
    min_y = tmp_y;
    min_z = tmp_z;
}

void cal_voxel_size(float min_x, float min_y, float min_z, 
                    float max_x, float max_y, float max_z,
                    float &voxel_dx, float &voxel_dy, float &voxel_dz)
{
    float x_diff = std::fabs(max_x - min_x);
    float y_diff = std::fabs(max_y - min_y);
    float z_diff = std::fabs(max_z - min_z);

    voxel_dx = (int)(x_diff / NUM_VOXEL);
    voxel_dy = (int)(y_diff / NUM_VOXEL);
    voxel_dz = (int)(z_diff / NUM_VOXEL);
}

cv::Point3f interpolation(cv::Point3f pt1, cv::Point3f pt2, 
                          float pt1_density, float pt2_density, float isovalue)
{
    float mu = (isovalue - pt1_density) / (pt2_density - pt1_density);

    float inter_x = pt1.x + mu * (pt2.x - pt1.x);
    float inter_y = pt1.y + mu * (pt2.y - pt1.y);
    float inter_z = pt1.z + mu * (pt2.z - pt1.z);

    return cv::Point3f(inter_x, inter_y, inter_z);
}

#endif