#include "cv.h"

#include "Histogram.h"
#include "VRFrame.h"
#include "Effect.h"

/*************************************************************************
* Get the start frame
************************************************************************/
long Effect::getFrameStart()
{
    return frameStart;
}

/*************************************************************************
* Get the end frame
************************************************************************/
long Effect::getFrameEnd()
{
    return frameEnd;
}

/*************************************************************************
* Get the ID variable
************************************************************************/
int Effect::getID()
{
    return ID;
}

/*************************************************************************
* Get name of effect
************************************************************************/
char *Effect::getName()
{
    return name_cy;
}

/*************************************************************************
* Set effect name
************************************************************************/
void Effect::setName(char *name)
{
    strcpy(this->name_cy, name);
}

/*************************************************************************
* Set ID
************************************************************************/
void Effect::setID(int ID)
{
    this->ID = ID;
}

/*************************************************************************
* Set start frame
************************************************************************/
void Effect::setFrameStart(long pos)
{
    this->frameStart = pos;
}

/*************************************************************************
* Set end frame
************************************************************************/
void Effect::setFrameEnd(long pos)
{
    this->frameEnd = pos;
}
