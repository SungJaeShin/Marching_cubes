#ifndef INCLUDE
#define INCLUDE

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cstdlib> 
#include <ctime>
#include <string>
#include <cmath>
#include <chrono>
#include <map>

#include <opencv2/viz.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

struct PointCloud 
{
    std::vector<cv::Point3f> vertices;
    std::vector<float> density;
};

struct Triangle
{
    std::vector<cv::Point3f> vertices;
};

struct Voxel
{
    std::vector<cv::Point3f> vertices;
    std::vector<float> density;
};

#endif