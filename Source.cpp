#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <Windows.h>
//#include <conio.h>



using namespace std;
using namespace cv;

string path = "Screenshot (143).png";
//VideoCapture cap(0);
//HWND hwnd = GetDesktopWindow();
Mat img = imread(path);
//Mat img;
bool click = false;
int r, g, b, xpos, ypos;



void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDBLCLK)
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        click = true;
        xpos = x;
        ypos = y;
        Vec3b pixel = img.at<Vec3b>(y, x);// to calculate the pixel value;
        b = pixel[0];
        g = pixel[1];
        r = pixel[2];
        cout << "r" << r << "g" << g << "b" << b << endl;
    }

}


int main() {


    namedWindow("color_dectection", 1);
    setMouseCallback("color_dectection", CallBackFunc, NULL);

   while (1) {
       //cap.read(img);
       imshow("color_dectection", img);
            if (click) {

                //rectangle(image, startpoint, endpoint, color, thickness) - 1 fills entire rectangle
                rectangle(img, Point(20, 20), Point(750, 60), Scalar(b, g, r), -1);

                    //Creating text string to display(Color name and RGB values)
                    string text = "R=" + to_string(r) + "G =" + to_string(g) + "B =" + to_string(b);
                    
                    //copy Text to clipbord;
                    OpenClipboard(0);
                    EmptyClipboard();
                    const size_t ln = text.length()+1;
                    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, ln);
                    memcpy(GlobalLock(h), text.c_str(), ln);
                    GlobalUnlock(h);
                    SetClipboardData(CF_TEXT, h);
                    CloseClipboard();
                    GlobalFree(h);


                    //cv2.putText(img, text, start, font(0 - 7), fontScale, color, thickness, lineType)
                    putText(img, text, Point(50,50), 2, 0.8, Scalar(255, 255, 255), 2, LINE_AA);

                    //For very light colours we will display text in black colour
                    if (r + g + b >= 600) {
                        putText(img, text, Point(50, 50), 2, 0.8, Scalar(0, 0, 0), 2, LINE_AA);
                    }
                    click = false;

                        
            }

            if (waitKey(20) && 0xFF == 27)
            if (waitKey(20) && 0xFF == 27)
                break;
    }
   destroyAllWindows();
	return 0;
}