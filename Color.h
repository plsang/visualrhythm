#ifndef COLOR_INCLUDE
#define COLOR_INCLUDE

/************************************************************************
* Class represents color effect
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/

class Color: public Effect
{
public:

    int R;
    int G;
    int B;

    // Convert a frame into grayscale image
    VRFrame* convert2Gray(VRFrame *frame);
    VRFrame* applyEffect(VRFrame* frame);

    Color(long frameStart, long frameEnd);
    Color();

};
#endif
