
#include <vector>

#include "DetectTransitions.h"

#ifndef CUT_INCLUDE
#define CUT_INCLUDE

/**
* Class provides methods for scene cut detection
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/

class Cut : public DetectTransitions
{
private:
    int threshold;
    
    /*
    * user threshold, percentage of frame height
    * this threshold helps to define threshold
    * and set by user
    */
    
    double userThreshold;

public:

    // Construtor
    Cut(); 

    // Passa o filtro de Canny sobre o Ritmo Visual
    void createBorderMap(VRFrame* visualRythim);

    void detectTransitions(Video* vdo, std::vector<Transition>* transitionList);

    int getThreshold();

    int setThreshold(int threshold);

    // Define count points threshold base on height
    int defineThreshold(int height);

    // Count number of points that greater than a defined threshold
    // at every frames in the visual rhythm image after applying canny
    // edge detection
    int* countPoints(VRFrame* borderMap, int threshold);

    // Check if there is a cut at a specified position
    int validateCut(VRFrame* visual, int position);

    //
    void setUserThreshold(double);
    double getUserThreshold();

};
#endif
