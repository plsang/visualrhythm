#ifndef EFFECT_INCLUDE
#define EFFECT_INCLUDE

/**
* Class provides methods for applying effect on frame image
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/
class Effect
{
    /**
    * Abstract method for applying effects.
    */
private:
    char name_cy[50];
    int ID;
    long frameStart;
    long frameEnd;

public:


    virtual VRFrame* applyEffect(VRFrame *frame) = 0;

    void setFrameStart(long pos);
    long getFrameStart();

    void setFrameEnd(long pos);
    long getFrameEnd();

    void setName(char *name);
    char *getName();

    void setID(int ID);
    int getID();

    // Define some effect types
#define EFFECT_COLOR  0
#define EFFECT_ERODE  1
#define EFFECT_DILATE 2
};
#endif
