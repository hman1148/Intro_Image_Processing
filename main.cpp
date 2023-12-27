#include "ImageProcessing.hpp"

#include <iostream>
#include <memory>

int main()
{
    // Change the path to any path you have on your system. Make sure to include double \ characters
    std::string imagePath = "C:\\data\\Images\\test.jpg";
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cerr << "Could not read the image " << imagePath << std::endl;
        return 1;
    }

    std::shared_ptr<ImageProcessor> processor = std::make_shared<ImageProcessor>();

    std::uint8_t erosion = 1;
    cv::Mat erodedImage = processor->erodeImage(image, erosion);

    cv::imshow("Original Image", image);
    cv::imshow("Eroded Image", erodedImage);

    cv::waitKey(0);
    return 0;
}