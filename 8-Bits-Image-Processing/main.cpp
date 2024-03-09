#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

static void threshold(cv::Mat& img, int threshold)
{
    // 32fp image
    for (size_t y = 0; y < img.rows; y++)
        for (size_t x = 0; x < img.cols; x++)
            img.at< uint8_t >(y, x) = img.at< uint8_t >(y, x) >= threshold ? 255 : 0;

}

enum algorithm { THRESHOLD = 1 };

int main()
{
	cv::VideoCapture cap(0);

    if (!cap.isOpened()) 
    {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    cv::Mat frame, frameT;
    int thresholdVal = 128;
    int algoChoice{};

    cout << "Choose algorithm: \n" <<
        "1. Threshold";
    cin >> algoChoice;

    while (1) {

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        frameT = frame.clone();

        if(algoChoice == algorithm::THRESHOLD) threshold(frameT, thresholdVal);

        // Display the resulting frame
        cv::imshow("Frame", frame);
        cv::imshow("FrameT", frameT);

        // Press ESC on keyboard to exit
        char c = static_cast< char >( cv::waitKey( 25 ) );
        if (c == 27)
            break;
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    cv::destroyAllWindows();

    return 0;
}