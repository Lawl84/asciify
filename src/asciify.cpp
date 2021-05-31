#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <sstream>


bool isbetween(int a, int b, int c)
{
    return c > a && c < b;
}

std::vector<int> get_intensities(const cv::Mat& img)
{
    std::vector<int> intensities;
    for (int i = 0; i < img.rows; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            cv::Vec3b intensity = img.at<cv::Vec3b>(i, j);
            std::array<int, 3> rgb;

            for (int k = 0; k < img.channels(); ++k)
            {
                rgb[k] = intensity.val[k];
            }

            int in = (int)(0.2126f * (float)rgb[2] + 0.7152f * (float)rgb[1] + 0.0722f * (float)rgb[0]);

            intensities.emplace_back(in);
        }
    }
    return intensities;
}

std::string asciify(cv::Mat img, int scale = 100)
{
    cv::Mat imgResized;
    cv::resize(img, imgResized, cv::Size(std::floor(img.rows * scale/50), std::floor(img.cols * scale/100)));
    std::vector<int> intensities = get_intensities(imgResized);
    std::string output;
    for (int row_count = 0; row_count < imgResized.rows; row_count++)
    {

        for (int col_count = 0; col_count < imgResized.cols; col_count++)
        {
            if (isbetween(-1, 51, intensities[(row_count * imgResized.cols + col_count)]))
                output += ":";
            else if (isbetween(51, 102, intensities[(row_count * imgResized.cols + col_count)]))
                output += "=";
            else if (isbetween(102, 153, intensities[(row_count * imgResized.cols + col_count)]))
                output += "$";
            else if (isbetween(153, 204, intensities[(row_count * imgResized.cols + col_count)]))
                output += "#";
            else if (isbetween(204, 256, intensities[(row_count * imgResized.cols + col_count)]))
                output += "@";
            else
                output += ".";

        }
        output += "\n";
    }
    return output;
}

int main(int argc, char* argv[])
{
    cv::Mat img = cv::imread(argv[1]);
    int scale = 10;
    std::cout << asciify(img, scale);
}
