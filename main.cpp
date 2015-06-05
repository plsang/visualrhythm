
#include "cv.h"
#include "highgui.h"

#include "Histogram.h"
#include "VRFrame.h"
#include "opencv/Video.h"
#include "opencv/IplImageWrapper.h"
#include "Transition.h"
#include "Cut.h"

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    double userThreshold = 0;
    int vrType = 0;
    int minFrame = 0;

    //vdo = new Video("f:\\WORKSPACE\\OPENCV\\data\\indi002.avi");

    if(argc != 7)
    {
        cout << "Usage: VisualRhythm.exe [threshold] [type] [minframe] [videodir] [videofile] [outputfile]" << endl;
        cout << "   + threshold: 0->100: percentage of frame height, used to count for cut point" << endl;
        cout << "   + type: 0 -> visual rhythm by subsampling, 1 -> visual rhythm by histogram" << endl;
        cout << "   + minframe: minimum frame required to process" << endl;
        cout << "   + videodir: path to your video file" << endl;
        cout << "   + videofile: video file name" << endl;
        cout << "   + outputfile: output file name" << endl;
        cout << "   +++ output format: [videofile] [threshold] [vrtype] [min frame] [start frame (0)] [cut frame]... [end frame]" << endl;
        exit(1);
    }

    userThreshold = atof(argv[1]);
    vrType = atoi(argv[2]);
    minFrame = atoi(argv[3]);
    char* videodir = argv[4];
    char* videofile = argv[5];
    char* outputFile = argv[6];

    char video[100];
    sprintf(video, "%s/%s", videodir, videofile);

    Video vdo(video);

    ofstream fout;
    fout.open(outputFile, ios_base::app);
    if(!fout.is_open())
    {
        cout << "Can't open output file for writing!! " << endl;
        exit(1);
    }
    
    cout << "Processing video " << "[" << videofile <<  "] ([Threshold:" << userThreshold \
        << "-vrType:" << vrType << "-minFrame:" << minFrame << "])..." << endl;

    cout << "H-W-FPS-T:  " << vdo.getHeight() << "-" << vdo.getWidth() << "-" <<
        vdo.getFrameRate() << "-" << vdo.numOfFrames() << endl;

    fout << videofile << " " << userThreshold << " " << vrType << " " << minFrame << " " << 0 << " ";

    if(vdo.numOfFrames() < minFrame)
    {
        cout << "Skipped short video..." << endl;
    }
    else
    {
        Cut* DTC = new Cut();
        DTC->setUserThreshold(userThreshold);
        DTC->setVRType(vrType);

        std::vector<Transition> transList;

        cout << "Starting scene cut detection for video " << "[" << videofile <<  "]..."  << endl;
        clock_t start_t, end_t;

        // capture start time
        start_t = clock();

        DTC->detectTransitions(&vdo, &transList);

        // capture end time
        end_t = clock();

        char name[100];

        int duration = (end_t - start_t) / (double)CLOCKS_PER_SEC;;
        sprintf(name, "%02d:%02d", duration/60, duration%60);
        cout << "Duration (mm:ss): " << name << endl;

        cout << "Actual threshold: " << DTC->getThreshold() << endl;
        cout << "Number of scene cuts: " << transList.size() << endl;

        std::vector<Transition>::iterator iter;

        cout << "Writing scene-cut frames..." << endl;

        for(iter = transList.begin(); iter != transList.end(); iter++)
        {
            long pos = iter->getPosTransition();
            fout << pos << " ";

            //vdo.seek((long long)pos);
            //VRFrame * tf = new VRFrame((const IplImage*)(vdo.getFrame()));
            //long msec = vdo.getTime();

            //sprintf(name, "VRFrame %06d - at %02d-%02d-%03d.jpg", pos, msec/1000/60, msec/1000%60, msec % 1000);

            /*
            cvNamedWindow( name, 1);
            cvFlip(tf->data, NULL, 0);
            cvShowImage( name, tf->data );

            while(cvWaitKey(1) != 'c');
            */

            //cvFlip(tf->data, NULL, 0); // flip the frame
            //tf->write(name);
        }
    }
    fout << vdo.numOfFrames() << endl;
    fout.close();
    return 1;
}