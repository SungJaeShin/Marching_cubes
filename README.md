# Marching Cubes
## [Goal] The implementation Marching Cubes using OpenCV in C++ 



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

## 3. Build and Run 
Clone the repository and build and run simultaneously:
```
   $ cd ${workspace}
   $ git clone https://github.com/SungJaeShin/Marching_cubes.git
   $ cd Marching_cubes
   $ sh start.sh
```

In start.sh file, there must write the file (PLY or TXT) location and output file (PLY or TXT) location !!
```
g++ ./src/main.cpp -L /usr/local/include/opencv2 -lopencv_viz -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_features2d -o ./marching
./marching "FILE_LOCATION" "SAVE_LOCATION"
```

## 4. Setting Rules between Vertices and Edges !!
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

## 5. Results 

- Time consumption
- 


## 6. References
[1] [https://github.com/nihaljn/marching-cubes](https://github.com/nihaljn/marching-cubes) \
[2] [https://www.volume-gfx.com/volume-rendering/marching-cubes/](https://www.volume-gfx.com/volume-rendering/marching-cubes/) \
[3] [http://www.it.hiof.no/~borres/j3d/explain/marching/p-march.html](http://www.it.hiof.no/~borres/j3d/explain/marching/p-march.html) \
[4] [https://paulbourke.net/geometry/polygonise/](https://paulbourke.net/geometry/polygonise/)

