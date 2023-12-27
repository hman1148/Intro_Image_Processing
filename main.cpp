#include "ImageProcessing.hpp"

#include <iostream>
#include <memory>

int main()
{
    std::string imagePath = "test.jpg ";
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cerr << "Couldn't not read the image" << imagePath << std::endl;
        return 1;
    }

    std::shared_ptr<ImageProcessing> processor = std::make_shared<ImageProcessing>();

    std::uint8_t erosion = 3;
    cv::Mat erodedImage = processor->erodeImage(image, erosion);

    cv::imshow("Original Image", image);
    cv::imshow("Eroded Image", erodedImage);

    cv::waitKey(0);
    return 0;
}