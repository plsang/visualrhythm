#ifndef TRANSITION_INCLUDE
#define TRANSITION_INCLUDE
/**
* Class represents a transition
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/

#define TRANSITION_VIDEOSTART   0
#define TRANSITION_CUT          1
#define TRANSITION_FADE			2
#define TRANSITION_FADEIN       3
#define TRANSITION_FADEOUT      4
#define TRANSITION_DISSOLVE     5
#define TRANSITION_ALL			-1

class Transition
{

private:

    /**
    *Transition Type
    *0 - Cut
    *1 - Fade-In
    *2 - Fade-Out
    *3 - Dissolve
    */
    int type;

    /**
    * Position in frame that mark the transition
    */
    long posTransition;

    /**
    * Position in frame that mark the transition by user
    */
    long posUserTransition;

    /**
    * Label used to annotate transition
    */
    char label[256];

public:

    bool selected;

    // Construtores/Destrutores
    Transition();
    Transition(int type, long posTransition, char *label);

    // Get/Set
    void setType(int type);
    int getType();
    void setPosTransition(int posTransition);
    long getPosTransition();
    void setPosUserTransition(int posUser);
    long getPosUserTransition();
    void setLabel(char *label);
    char* getLabel();
    long getPosCurrent(void) const;

    // Operadores
    bool operator <(const Transition& Rhs) const;

};
#endif
