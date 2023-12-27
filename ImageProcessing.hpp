#pragma once

#include "opencv2/opencv.hpp"

#include <cstdint>

class ImageProcessing
{
  public:
    cv::Mat erodeImage(const cv::Mat& inputImage, std::uint8_t erosionSize);
};