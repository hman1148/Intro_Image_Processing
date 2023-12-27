#include "ImageProcessing.hpp"

cv::Mat ImageProcessor::erodeImage(const cv::Mat& inputImage, std::uint8_t erosionSize)
{
    // This is the basic tutorial of how to do a simple erosion to a .jpg
    cv::Mat outputImage;
    cv::Mat erosionFactor = cv::getStructuringElement(cv::MORPH_RECT,
                                                      cv::Size(static_cast<std::uint8_t>(2 * erosionSize + 1), static_cast<std::uint8_t>(2 * erosionSize + 1)),
                                                      cv::Point(erosionSize, erosionSize));

    cv::erode(inputImage, outputImage, erosionFactor);
    return outputImage;
}
