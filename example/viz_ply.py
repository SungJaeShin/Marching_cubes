# ============= open3d version =============
from open3d import *    

def main():
    ply_path = "/home/sj/workspace/nerf_ws/src/marching_cubes/example/output/marching_cubes_airplane_200.ply" 
    cloud = io.read_point_cloud(ply_path) # Read point cloud
    visualization.draw_geometries([cloud])    # Visualize point cloud      

if __name__ == "__main__":
    main()


# ============= pyntcloud version =============
# from pyntcloud import PyntCloud
# import matplotlib

#ply_path = "/home/sj/workspace/rx_project_ws/src/neuralangelo/logs/kaist_b301/kaist_b301_name/kaist_b301.ply" 
#cloud = PyntCloud.from_file(ply_path)

# cloud.plot(mesh=True, backend="matplotlib")
#cloud.plot(backend="matplotlib", mesh=True, cmap="hsv")
