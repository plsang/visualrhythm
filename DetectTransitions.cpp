#include "cv.h"
#include "highgui.h"
#include <vector>


#include "Histogram.h"
#include "time.h"
#include "VRFrame.h"

#include "opencv/Video.h"
#include "Transition.h"
#include "DetectTransitions.h"


#include "Cut.h"


#include "Log.h"


/*
* Default constructor
*/
DetectTransitions::DetectTransitions()
{
    setLogFile("log.txt");
    this->vrType = VR_SUBSAMBLING;
}

/************************************************************************
* Detect transition from video
************************************************************************/

void DetectTransitions::detectTransitions(Video* vdo, std::vector<Transition>* transitionList)
{

}

/************************************************************************
* Check if a position is a transition point.
************************************************************************/
bool DetectTransitions::validateTransition(long position, std::vector<Transition>* transitionList)
{
    unsigned long i;
    Transition* currentTransition;

    Log::writeLog("%s :: position = %ld", __FUNCTION__, position);

    for(i=0; i<transitionList->size(); i++)
    {
        currentTransition = &transitionList->at(i);
        Log::writeLog("%s :: currentTransition = %ld", __FUNCTION__, currentTransition->getPosTransition());

        if (position == currentTransition->getPosTransition())
        {
            Log::writeLog("%s :: Transição inválida!!! Já existe uma transição na posição[%d].", __FUNCTION__, position);
            return FALSE;
        }
    }

    Log::writeLog("%s :: Transição válida!!! Posição[%d].", __FUNCTION__, position);
    
    return TRUE;

}

void DetectTransitions::setLogFile(char *str)
{
    strcpy(logFileName, str);
}


char* DetectTransitions::getLogFile()
{
    return logFileName;
}


void DetectTransitions::setVRType(int type)
{
    this->vrType = type;
}
