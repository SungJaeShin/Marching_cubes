#ifndef VIZ_MESH
#define VIZ_MESH

#include "opencv2/opencv.hpp"
#include "opencv2/viz/types.hpp"
#include "opencv2/viz/viz3d.hpp"
#include "opencv2/viz/widgets.hpp"

// Visualization 3D Mesh using PLY file
void viz3DMesh(cv::String mesh_path)
{
    // Get Mesh files
    cv::viz::WMesh viz_mesh = cv::viz::readMesh(mesh_path);

    // creating a Viz window
    cv::viz::Viz3d window("3D Mesh");
    window.showWidget("World Coordinate", cv::viz::WCoordinateSystem());
    
    // visualized Mesh
    window.showWidget("Mesh Widget", viz_mesh);
    window.spin();
}

// Visualization 3D Mesh using PLY file
void viz3DPoints(cv::String ply_path)
{
    // Get ply file
    cv::viz::Mesh ply_file = cv::viz::readMesh(ply_path);
    cv::viz::WCloud pointcloud(ply_file.cloud, cv::viz::Color::white());

    // creating a Viz window
    cv::viz::Viz3d window("3D Points");
    window.showWidget("World Coordinate", cv::viz::WCoordinateSystem());
    
    // visualized pointcloud 
    window.showWidget("Pointcloud Widget", pointcloud);
    window.spin();
}

#endif