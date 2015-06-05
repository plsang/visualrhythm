
#include <vector>
#include "opencv/Video.h"

#ifndef DETECTTRANSITIONS_INCLUDE
#define DETECTTRANSITIONS_INCLUDE

/**
* Class provides general methods for transition detection
* Other classes that detect specific transition should derive from this class
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/

#define VR_SUBSAMBLING 0
#define VR_HISTOGRAM 1

class DetectTransitions
{
    char logFileName[64];

protected:
    int vrType;

public:

    DetectTransitions();

    // Detect transition from video
    void detectTransitions(Video* vdo, std::vector<Transition>* tansitionList);

    // Check if a position is a transition point.
    bool validateTransition(long position, std::vector<Transition>* transitionList);

    // Set Log file
    void setLogFile(char *);

    // Get Log file
    char* getLogFile();

    // Set visual rhythm type
    void setVRType(int type);
};

#endif
