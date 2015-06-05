#ifndef HISTOGRAM_INCLUDE
#define HISTOGRAM_INCLUDE

/**
* Class provides methods for histogram calculation
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/
class Histogram 
{
private:

    /**
    * Max position and max value
    */
    float max; 
    int maxLum; 

    /**
    * Min position and min value
    */
    float min;
    int minLum;

public:

    double data[256];
    Histogram();
    Histogram(IplImage* img);
    double* getMatrix();
    float getMax();
    float getMin();
    int getMaxLuminance();
    int getMinLuminance();

};
#endif
