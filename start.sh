export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib
g++ ./src/main.cpp -L /usr/local/include/opencv2 -lopencv_viz -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_features2d -o ./marching
./marching 
