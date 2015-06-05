#include "cv.h"
#include "highgui.h"

#include "time.h"

#include "Histogram.h"
#include "VRFrame.h"
#include "opencv/Video.h"
#include "opencv/IplImageWrapper.h"
#include "VisualRhythm.h"

#include "Effect.h"
#include "Color.h"

#include "Log.h"

#include <stdio.h>

/************************************************************************
* Create a visual rhythm by sub-sampling
* Pixels in main diagonal are used for sub-sampling
************************************************************************/
VRFrame* VisualRhythm::createVR(Video* vdo)
{

    VRFrame *frameVR = 0;
    VRFrame* frame = 0;
    VRFrame* frameGray = 0;
    VRFrame *frameAux = 0;

    Color *color = 0;

    //int lum;

    double width;
    double heigth;

    Log::writeLog("%s :: param: Video[%x]", __FUNCTION__, vdo);

    color = new Color();

    // Pego o primeiro frame do vídeo e sua diagonal	
    
    width =  vdo->getWidth();
    heigth = vdo->getHeight();

    //const IplImageWrapper iplImage = vdo->getFrame();
    
    frame =  new VRFrame((const IplImage*)(vdo->getFrame()));

    frameVR = new VRFrame(frame->getDiagonal());

    while(true)
    {
        Log::writeLog("%s :: Convert2Gray VRFrame[%x] VRFrame->data[%x]", __FUNCTION__, frame, frame->data);

        // Convert to grayscale image
        frameGray = color->convert2Gray(frame);

        // Get diagonal frame.
        frameAux = frameGray->getDiagonal();

        // Concatenate with those frames together to make the visual rhythm
        *frameVR += *frameAux;

        // Deallocate memory
        delete frameAux;
        delete frame;
        delete frameGray;

        if (!vdo->nextFrame())
            break;
        frame = new VRFrame((const IplImage*)(vdo->getFrame()));
    }

    Log::writeLog("%s :: max_frames[%.f]", __FUNCTION__, vdo->numOfFrames());
    return (frameVR);
}

/************************************************************************
* Create a visual rhythm based on histogram
************************************************************************/

double* VisualRhythm::createVRH(Video* vdo)
{
    VRFrame* frame = new VRFrame(); 
    Histogram* histogram;
    Color *color = new Color();
    VRFrame* frameGray = 0;
    VRFrame *frameDiagonal = 0;

    long long totalFrames = vdo->numOfFrames();

    int posic = 0;

    /**
    * Crio um array com o numero de posicoes = ao nro de frames do video
    * para guardar o valor máximo de cada histograma que será gerado.
    * Obs.: Será gerado 1 histograma por frame.
    **/
    double* hist; // Este é o RVH.

    hist = (double*)malloc(sizeof(double)*cvRound(totalFrames));

    memset(hist, '\0',     sizeof(double)*cvRound(totalFrames));

    // Pego o primeiro frame
    frame = NULL;
    if(vdo->nextFrame())
        frame = new VRFrame((const IplImage*)(vdo->getFrame()));

    while(frame != NULL)
    {

        if (posic >= totalFrames)
        {
            Log::writeLog("%s :: BOOOOOOM!", __FUNCTION__);
        }

        // Converto o frame para escala de cinza.
        frameGray = color->convert2Gray(frame);

        // Pega a diagonal
        frameDiagonal = frameGray->getDiagonal();

        // Pega o histograma da diagonal
        histogram = frameDiagonal->createHistogram();

        // Pega o pico deste histograma.
        //hist[posic] = histogram->getMaxLuminance();

        // Guardo a media do valor de luminancia da diagonal.
        hist[posic] = frameGray->calcLuminanceAvarage();

        //		Log::writeLog("%s :: hist[%d] = %lf", __FUNCTION__, posic, hist[posic]);

        /**
        * Deleto os objetos criados anteriormente para desalocamento de
        * memoria.
        **/
        delete frameDiagonal;
        delete frameGray;
        delete histogram;
        delete frame;

        // Pego o proximo
        if(!vdo->nextFrame())
            break;

        frame = new VRFrame((const IplImage*)(vdo->getFrame()));
        posic++;

    }

    delete color;

    return (hist);
}

/**
* Create a frame from a histogram
* This frame has size of [1 x number of bins] 
*/
VRFrame* VisualRhythm::createFrame(Histogram *h)
{
    int x = 0;

    int bins = 256;

    VRFrame* frameHist;

    IplImage* imgHist = VRFrame::imgAlloc(cvSize(1, bins), 8, 1);

    frameHist = new VRFrame(imgHist);

    // Update pixel info for the histogram frame.
    for (x=0; x < bins ; x++)
    {
        frameHist->setPixel(0, x, h->data[x]);
    }	

    VRFrame::imgDealloc(imgHist);

    return(frameHist);
}

/**
* Create a visual rhythm based on histogram
* The previous version of this histogram is rather simple
* @See createVRH(Video* vdo)
*/
VRFrame* VisualRhythm::createVRH2(Video* vdo)
{
    VRFrame* frame = 0; 
    Histogram* histogram = 0;
    Color *color = new Color();
    VRFrame* frameGray = 0;
    VRFrame *frameVR = 0;
    VRFrame *frameAux = 0;


    frame = NULL;
    if(vdo->nextFrame())
        frame = new VRFrame((const IplImage*)(vdo->getFrame()));

    while(frame != NULL)
    {
        // Converto o frame para escala de cinza.
        frameGray = color->convert2Gray(frame);
        histogram = frameGray->createHistogram();
        frameAux = this->createFrame(histogram);

        if(frameVR == 0)
            frameVR = new VRFrame(frameAux);
        else
            *frameVR += *frameAux; 

        delete frameGray;
        delete histogram;
        delete frame;
        delete frameAux;

        // Go to next frame
        if(!vdo->nextFrame())
            break;

        frame = new VRFrame((const IplImage*)(vdo->getFrame()));
    }

    delete color;
    return (frameVR);
}
