
#include <stdlib.h>
#include <string.h>

#include "Transition.h"

/************************************************************************
* Default constructor
************************************************************************/
Transition::Transition()
{
    this->type = 0;
    this->posTransition = 0;
    this->posUserTransition = 0;
    this->selected = false;
}

/************************************************************************
* Construct a Transition by type, position and label
************************************************************************/
Transition::Transition(int type, long posTransition, char *label)
{
    Transition();

    this->type = type;
    this->posTransition = posTransition;
    this->posUserTransition = 0;
    this->selected = false;
    strcpy(this->label, label);
}

/************************************************************************
* Set transition type 
************************************************************************/

void Transition::setType(int type)
{
    this->type = type;
}

/************************************************************************
* Get transition type
************************************************************************/

int Transition::getType()
{
    return (this->type);
}

/************************************************************************
* Set transition's position
************************************************************************/

void Transition::setPosTransition(int posTransition)
{
    this->posTransition = posTransition;
}	

/************************************************************************
* Get transition's position
************************************************************************/

long Transition::getPosTransition()
{
    return (this->posTransition);
}

/************************************************************************
* Set position in frame that mark the transition by user
************************************************************************/

void Transition::setPosUserTransition(int posUser)
{
    this->posUserTransition = posUser;
}

/************************************************************************
* Get position in frame that mark the transition by user
************************************************************************/

long Transition::getPosUserTransition()
{
    return (this->posUserTransition);
}

/************************************************************************
* Set label name that used to annotate transition
************************************************************************/

void Transition::setLabel(char* label)
{
    strcpy(this->label, label);
}

/************************************************************************
* Get label name that used to annotate transition
************************************************************************/

char* Transition::getLabel()
{
    return (this->label);
}

/************************************************************************
* overload operator < to compare two transition
************************************************************************/

bool Transition::operator <(const Transition &Rhs) const
{  
    long pos;
    long posAUX;

    pos = getPosCurrent();
    posAUX = Rhs.getPosCurrent();

    return (pos < posAUX);
}

/************************************************************************
* Get current position
* If user has already defined this position then use it.
* Otherwise, use the position that detect by the system.
************************************************************************/

long Transition::getPosCurrent(void) const
{
    if (this->posUserTransition > 0)
        return this->posUserTransition;
    else
        return this->posTransition;
}
