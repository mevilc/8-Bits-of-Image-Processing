#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;

static void threshold(cv::Mat& img, float threshold)
{
    // [ 0.0, 1.0 ] --> [ 0, 255 ] 
    int thresholdInt = static_cast< int >(threshold * 255.f);
    for (size_t y = 0; y < img.rows; y++)
        for (size_t x = 0; x < img.cols; x++)
            img.at< uint8_t >(y, x) = img.at< uint8_t >(y, x) >= thresholdInt ? 255 : 0;

}

static void motionDetect(cv::Mat& fr1, cv::Mat& fr2)
{
    // 8bit, 1 channel
    for (size_t y = 0; y < fr1.rows; y++)
        for (size_t x = 0; x < fr1.cols; x++)
            fr2.at< uint8_t >(y, x) = abs( fr2.at< uint8_t >(y, x) - fr1.at< uint8_t >(y, x) );
}

enum algorithm { THRESHOLD = 1, MOTION_DETECTION };

int main()
{
	cv::VideoCapture cap(0);

    if (!cap.isOpened()) 
    {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    cv::Mat unmodFrame, currFrame;
    
    int algoChoice{};

    cout << "Choose algorithm: \n" <<
        "1. Threshold\n" <<
        "2. Motion Detection\n";

    cin >> algoChoice;

    // motion detection
    int n{ 0 };
    cv::Mat prevFrame;

    while (1) 
    {
        // Capture frame-by-frame
        cap >> unmodFrame;

        if (algoChoice == algorithm::MOTION_DETECTION)
        {
            if (n % 2 == 0)
            {
                prevFrame = unmodFrame.clone();
                cv::cvtColor(prevFrame, prevFrame, cv::COLOR_BGR2GRAY);
            }

            currFrame = unmodFrame.clone();

            // If the frame is empty, break immediately
            if (unmodFrame.empty())
                break;

            cv::cvtColor(unmodFrame, unmodFrame, cv::COLOR_BGR2GRAY);
            cv::cvtColor(currFrame, currFrame, cv::COLOR_BGR2GRAY);

            motionDetect(prevFrame, currFrame);

            // Display the resulting frame
            cv::imshow("Frame", unmodFrame);
            cv::imshow("Motion", currFrame);

            n++;

        }

        else if ( algoChoice == algorithm::THRESHOLD )
        {
            // If the frame is empty, break immediately
            if (unmodFrame.empty())
                break;

            currFrame = unmodFrame.clone();
            cv::cvtColor(unmodFrame, unmodFrame, cv::COLOR_BGR2GRAY);
            cv::cvtColor(currFrame, currFrame, cv::COLOR_BGR2GRAY);

            float thresholdVal = 0.2f;
            threshold(currFrame, thresholdVal);

            // Display the resulting frame
            cv::imshow("Frame", unmodFrame);
            cv::imshow("Threshold", currFrame);
        }
        

        // Press ESC on keyboard to exit
        char c = static_cast< char >( cv::waitKey( 5 ) );
        if (c == 27)
            break;
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    cv::destroyAllWindows();

    return 0;
}