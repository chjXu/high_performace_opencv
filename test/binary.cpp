#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

#include "../cv_utils/binaryImage.hpp"

using namespace std;

int main()
{
    cv::Mat image = cv::imread("../data/light.jpeg");
    cv::Mat thres_image;

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    cv::threshold(image, thres_image, 127, 255, cv::THRESH_BINARY);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> cost = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "1 It takes " << cost.count() << "s" << std::endl;

    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    unsigned char* dst_img = new unsigned char[gray.cols * gray.rows];
    start = std::chrono::high_resolution_clock::now();
    MyBinaryImage(gray.data, dst_img, gray.cols, gray.rows, 127);
    end = std::chrono::high_resolution_clock::now();
    cost = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "2 It takes " << cost.count() << "s" << std::endl;
    // cv::namedWindow("src_img image);", cv::WINDOW_NORMAL);
    // cv::imshow("src_img",

    // cv::namedWindow("thres_img", cv::WINDOW_NORMAL);
    // cv::imshow("thres_img", thres_image);

    cv::Mat res(gray.rows, gray.cols, CV_8UC1, dst_img);
    cv::namedWindow("my_thres_img", cv::WINDOW_NORMAL);
    cv::imshow("my_thres_img", res);

    cv::waitKey(0);

    delete[] dst_img;
    return 0;
}