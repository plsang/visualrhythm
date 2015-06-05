

/**
* Class Filters
* Do Image Filtering.
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/

#ifndef FILTERS_INCLUDE
#define FILTERS_INCLUDE

#define SOBEL_VERTICAL	  0
#define SOBEL_HORIZONTAL  1
#define SOBEL_COMPLETE	  2

class Filters 
{
public:
    void Sobel(VRFrame* frame, int direction);
    void lowPass(VRFrame* frame, int size);
    void highPass(VRFrame* frame, int typeMask);
    void segment(VRFrame* frame, int threshold);
    void Canny(VRFrame* frame, double thresholdMin, double thresholdMax, int size);
};

#endif
