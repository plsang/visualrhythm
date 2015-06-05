
#ifndef VISUAL_RHYTHM
#define VISUAL_RHYTHM

#include "opencv/Video.h"

/**
* Class represents a visual rhythm (a space-time image for a video)
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/
class VisualRhythm
{
public:

    /**
    * Create a visual rhythm by sub-sampling
    */
    VRFrame *createVR(Video* vdo);

    /**
    * Create a visual rhythm based on histogram
    */
    double* createVRH(Video* vdo); 

    /**
    * Calculate first derivative of curve in the visual rhythm
    */
    float calcDerivatives();


    ///
    /// Added by Sang L. Phan
    ///

    /**
    * Create a frame from a histogram
    * This frame has size of [1 x number of bins] 
    */
    VRFrame* createFrame(Histogram *);

    /**
    * Creat a visual rhythm based on histogram
    * The previous version of this histogram is rather simple
    * @See createVRH(Video* vdo)
    */
    VRFrame* createVRH2(Video* vdo);
};
#endif
