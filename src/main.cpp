#include "../include/include.h"
#include "../include/parameters.h"
#include "../include/utility.h"
#include "../include/marching_cubes.h"
#include "../include/viz_mesh.h"

int main(int argc, char* argv[])
{
    // ===============================================================
    // Generate Pointcloud with Random density
    auto start_gen_pointcloud = std::chrono::high_resolution_clock::now();

    std::vector<cv::Point3f> pointcloud = generate_random_grid();
    PointCloud pointcloud_with_density;
    if(READ_FILE)
    {
        cv::String ply_path = argv[1];
        pointcloud = get_pointcloud_from_ply(ply_path);
    }
    pointcloud_with_density = add_random_density(pointcloud);

    auto end_gen_pointcloud = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> gen_pointcloud_duration = end_gen_pointcloud - start_gen_pointcloud;
    // ===============================================================

    // ===============================================================
    // Calculate Voxel Size
    auto start_cal_voxel_size = std::chrono::high_resolution_clock::now();

    float min_x, min_y, min_z;
    find_min_pixel(pointcloud, min_x, min_y, min_z);
    float max_x, max_y, max_z;
    find_max_pixel(pointcloud, max_x, max_y, max_z);
    float voxel_dx, voxel_dy, voxel_dz;
    cal_voxel_size(min_x, min_y, min_z, max_x, max_y, max_z, voxel_dx, voxel_dy, voxel_dz);

    auto end_cal_voxel_size = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> cal_voxel_size_duration = end_cal_voxel_size - start_cal_voxel_size;
    // ===============================================================

    // ===============================================================
    // Marching Cubes
    auto start_marching_cubes = std::chrono::high_resolution_clock::now();

    std::vector<Voxel> voxels;
    std::vector<Triangle> triangles;
    for (float z = min_z - voxel_dz; z <= max_z; z += voxel_dz)
    {
        for (float y = min_y - voxel_dy; y <= max_y; y += voxel_dy)
        {
            for (float x = min_x - voxel_dx; x <= max_x; x += voxel_dx)
            {
                Voxel cur_voxel;

                // Initialize Voxel Info
                init_voxel_vertices(pointcloud_with_density, cur_voxel, x, y, z, voxel_dx, voxel_dy, voxel_dz);

                // Calculate cube index
                int cubeIndex = calculate_cubes_index(cur_voxel, ISOVALUE);

                // Get edge index
                int edgeIndex = get_edge_index(cubeIndex);            

                // Get intersection vertices
                std::vector<cv::Point3f> inter_points = cal_inter_vertices(cur_voxel, edgeIndex, ISOVALUE);

                // Make triangles using inter_points and edge index
                make_triangle(triangles, inter_points, cubeIndex);

                voxels.push_back(cur_voxel);
            }
        }
    }

    auto end_marching_cubes = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> marching_cubes_duration = end_marching_cubes - start_marching_cubes;
    // ===============================================================

    // ===============================================================
    // Write PLY file using Triangles
    std::cout << "Number of triangles: " << triangles.size() << std::endl;
    cv::String save_path = argv[2];
    write_to_ply(triangles, save_path.c_str());
    // ===============================================================

    // ===============================================================
    std::cout << "Pointcloud Generation Time: " << gen_pointcloud_duration.count() << " ms" << std::endl;
    std::cout << "Voxel Size Calculation Time: " << cal_voxel_size_duration.count() << " ms" << std::endl;
    std::cout << "Marching Cubes Time: " << marching_cubes_duration.count() << " ms" << std::endl;
    // ===============================================================
    
    return 0;
}