#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

#include "../cv_utils/connectedComponents.hpp"

using namespace std;

int main()
{
    cv::Mat image = cv::imread("../data/light.jpeg");
    image = image(cv::Rect(1000, 600, 960, 540));
    cv::resize(image, image, cv::Size(320, 170));
    cv::namedWindow("src_img", cv::WINDOW_NORMAL);
    cv::imshow("src_img", image);
    cv::Mat thres_image, gray;
    cv::Mat label, stats, centroids;

    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, thres_image, 127, 255, cv::THRESH_BINARY);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    int num = cv::connectedComponentsWithStats(thres_image, label, stats, centroids);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> cost = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "1 It takes " << cost.count() * 1000 << "ms" << std::endl;
    std::cout << "num: " << num << std::endl;
    // cv::namedWindow("label", cv::WINDOW_NORMAL);
    // cv::imshow("label", label);

    cv::namedWindow("thres_img", cv::WINDOW_NORMAL);
    cv::imshow("thres_img", thres_image);
    unsigned char* dst_img = new unsigned char[thres_image.cols * thres_image.rows];
    unsigned char* mask    = new unsigned char[thres_image.cols * thres_image.rows];
    memset(mask, 0, sizeof(mask));
    start = std::chrono::steady_clock::now();
    MyconnectedComponents(thres_image.data, mask, thres_image.cols, thres_image.rows);
    end = std::chrono::steady_clock::now();
    cost = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "2 It takes " << cost.count() * 1000 << "ms" << std::endl;
    // cv::namedWindow("src_img image);", cv::WINDOW_NORMAL);
    // cv::imshow("src_img",



    cv::Mat res(thres_image.rows, thres_image.cols, CV_8UC1, mask);
    cv::namedWindow("mask", cv::WINDOW_NORMAL);
    cv::imshow("mask", res);

    cv::waitKey(0);

    delete[] dst_img;
    delete[] mask;
    return 0;
}