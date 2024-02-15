# Marching Cubes
## [Goal] The implementation Marching Cubes using OpenCV in C++ 
- Example pointcloud 
   <table>
      <tr>
         <td><img src="./results/input/airplane1.png"/> </td>
         <td><img src="./results/input/airplane2.png"/> </td>
      </tr>
   </table>

## 1. Prerequisites
### 1.1 Dependencies
OpenCV 3.2.0, C++ 11 version

### 1.2. OpenCV Installation
Follow [OpenCV](https://docs.opencv.org/4.x/d2/de6/tutorial_py_setup_in_ubuntu.html)
- Install appropriate OpenCV version: [Here](https://sungjaeshin.github.io/O/opencv-install/).

## 2. Changing Parameters
### Parameters in "parameters.h"
```
// random grid (READ_FILE = 0) or read from file (READ_FILE = 1)
#define READ_FILE 1 

// Maximum Grid Size
#define GRID_MAX 400

// Number of Voxel  
#define NUM_VOXEL 400

// Set ISOVALUE
#define ISOVALUE 0.5
```

## 3. Descriptions
(1) Loopup Table from [http://paulbourke.net/geometry/polygonise/](    http://paulbourke.net/geometry/polygonise/) \
(2) save_ply.h from [https://github.com/nihaljn/marching-cubes/blob/main/src/utilities.cpp](https://github.com/nihaljn/marching-cubes/blob/main/src/utilities.cpp) \
(3) Input file format &rarr; `.ply` & `.txt` \
(4) Output file format &rarr; `.ply` & `.txt` \
(5) Visualized pointcloud or mesh &rarr; `viz3DMesh()` & `viz3DPoints` in `viz_mesh.h` \
(6) Visualization python code also provided in `example` folder &rarr; `viz_ply.py` \
(7) Convert PLY format Binary to ASCII in `example` folder &rarr; `cvt_binary2ascii.py` 

## 4. Build and Run 
Clone the repository and build and run simultaneously:
```
   $ cd ${workspace}
   $ git clone https://github.com/SungJaeShin/Marching_cubes.git
   $ cd Marching_cubes
   $ sh start.sh
```

In `start.sh` file, **there must write the file (PLY or TXT) location and output file (PLY or TXT) location** !!
```
g++ ./src/main.cpp -L /usr/local/include/opencv2 -lopencv_viz -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_features2d -o ./marching
./marching <INPUT_FILE_LOCATION> <OUTPUT_SAVE_LOCATION>
```

## 5. Setting Rules between Vertices and Edges !!
```

    Tables and conventions from
    http://paulbourke.net/geometry/polygonise/

       v4--------v5       *---e4---- *
      /|       / |      / |         /|
     / |      /  |     e7 |       e5 |
    /  |     /   |    /   e8     /  e9
  v7--------v6   |   *----e6---*     |
   |   |    |    |   |    |     |    |
   |  v0----|---v1   |    *---e0|--- *
   |  /     |  /     e11 /     e10  /
   | /      | /      |e3        | e1
   |/       |/       |/         |/
 v3--------v2        *---e2---- *


    Vertex : v0, v1, v2, v3, v4, v5, v6, v7
    Edge   : e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11

    Rules  : (1) find cubeIndex (using vertices) and make 16 bits number
             (2) find edgeIndex (using loopup table)
             (3) find edgePoints (using interpolation)
             (4) make triangles
```

## 6. Results 
- Time consumption
   - Example PLY: `airplane.txt` (# of pointcloud: 1335)
      <table>
         <tr>
            <td> NUM VOXEL </td>
            <td> 400 </td>
            <td> 200 </td>
            <td> 100 </td>
            <td> 50 </td>
            <td> 30 </td>
            <td> 10 </td>
         </tr> 
         <tr>
            <td> # of triangles </td>
            <td> Killed </td>
            <td> 19790413 </td>
            <td> 2550114 </td>
            <td> 334483 </td>
            <td> 76775 </td>
            <td> 4068 </td>
         </tr>
         <tr>
            <td> Pointcloud read time (ms) </td>
            <td> Killed </td>
            <td> 2322.73 </td>
            <td> 2213.96 </td>
            <td> 2174.02 </td>
            <td> 2208.76 </td>
            <td> 2205.52 </td>
         </tr>
         <tr>
            <td> Voxel calculation (ms) </td>
            <td> Killed </td>
            <td> 0.053981 </td>
            <td> 0.053611 </td>
            <td> 0.053692 </td>
            <td> 0.053516 </td>
            <td> 0.053705 </td>
         </tr>
         <tr>
            <td> Marching Cubes (ms) </td>
            <td> Killed </td>
            <td> 889761 </td>
            <td> 114597 </td>
            <td> 14251.6 </td>
            <td> 2846.31 </td>
            <td> 155.389 </td>
         </tr>
      </table>

- Marching cube results


## 7. References
[1] [https://github.com/nihaljn/marching-cubes](https://github.com/nihaljn/marching-cubes) \
[2] [https://www.volume-gfx.com/volume-rendering/marching-cubes/](https://www.volume-gfx.com/volume-rendering/marching-cubes/) \
[3] [http://www.it.hiof.no/~borres/j3d/explain/marching/p-march.html](http://www.it.hiof.no/~borres/j3d/explain/marching/p-march.html) \
[4] [https://paulbourke.net/geometry/polygonise/](https://paulbourke.net/geometry/polygonise/)

