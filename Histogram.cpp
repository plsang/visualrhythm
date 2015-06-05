#include "cv.h"

#include "Histogram.h"
#include "Log.h"

#define HIST_WIDTH  256
#define HIST_HEIGHT 256

/************************************************************************
* Constructor: intinialzie all fields, set to 0
************************************************************************/

Histogram::Histogram()
{
    memset(this->data,'\0',256);
    this->max = 0;
    this->maxLum = 0;
    this->min = 0;
    this->minLum = 0;
}

/************************************************************************
* Constructor: create histogram from an Image
************************************************************************/
Histogram::Histogram(IplImage* img)
{
    // Tamanho de um histograma 1D
    int bins = HIST_WIDTH;
    int hsize[] = {bins};

    //IplImage* imgHistogram = 0;

    CvHistogram* hist = 0;

    //float value;
    //int normalized;

    // Ranges, escala de cinza: 0-255
    float xranges[] = {0, 256};
    float* ranges[] = {xranges};

    int i;

    float max = 0, min = 0;
    int maxLum = 0, minLum = 0;

    IplImage* planes[] = {img};

    // create a histogram
    hist = cvCreateHist(1, hsize, CV_HIST_ARRAY, ranges, 1);

    // calculate histogram
    cvCalcHist(planes, hist, 0, NULL);

    // get extreme position
    cvGetMinMaxHistValue(hist, &min, &max, &minLum, &maxLum);

    // get histogram value
    for (i=0 ; i < bins ; i++)
    {
        // Pega o quantas vezes a escala de cinza 'i' aparece na imagem
        this->data[i] = cvQueryHistValue_1D(hist, i);
    }

    this->max = max;
    this->min = min;
    this->maxLum = maxLum;
    this->minLum = minLum;

}

/************************************************************************
* Get histogram data.
************************************************************************/
double* Histogram::getMatrix()
{
    return this->data;
}

/************************************************************************
* Get position that has maximum luminance
************************************************************************/
float Histogram::getMax()
{
    return this->max;
}

/************************************************************************
* Get position that has mininum luminance
************************************************************************/
float Histogram::getMin()
{
    return this->min;
}

/************************************************************************
* Get maximum luminance
************************************************************************/
int Histogram::getMaxLuminance()
{
    return this->maxLum;
}

/************************************************************************
* Get minimum luminance
************************************************************************/
int Histogram::getMinLuminance()
{
    return this->minLum;
}