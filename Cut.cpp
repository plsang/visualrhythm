#include <stdio.h>
#include <vector>

#include "cv.h"
#include "highgui.h"

#include "time.h"
#include "Histogram.h"
#include "VRFrame.h"
//#include "Video.h"

#include "Transition.h"
#include "VisualRhythm.h"

#include "Effect.h"

#include "Cut.h"

#include "Filters.h"
#include "Log.h"

#include <iostream>
#include <fstream>
using namespace std;

/************************************************************************
* Default constructor
************************************************************************/

#define DEBUG_OUT 0

Cut::Cut()
{
    this->threshold = 0;
    this->userThreshold = 0;
}

/************************************************************************
* Scene cut detection using visual rhythm
************************************************************************/
void Cut::detectTransitions(Video* vdo, std::vector<Transition>* transitionList)
{ 
    VRFrame* visualRythim= new VRFrame();

    VisualRhythm *vr = new VisualRhythm();

    int threshold = 0;
    int thresholdBin = 0;
    int *trans = 0;
    long i = 0;
    long long totalFrames = vdo->numOfFrames();

    // Se a posicao do video não for a inicial, aponto para o primeiro frame.
    
    vdo->seek((long long)0);
    /**
    * Create a visual rhythm
    */
    cout << "Creating visual rhythm..." << endl;
    if(vrType == VR_SUBSAMBLING)
        visualRythim = vr->createVR(vdo);  // visual rhythm base on image subsampling
    else
        visualRythim = vr->createVRH2(vdo); // visual rhythm base on histogram
   
    if(DEBUG_OUT)
        visualRythim->writeFile("../dump/RV_start.jpg");

    /**
    * Remove less significant information and reduce size from both top and bottom
    * of the visual rhythm frame 
    */

    // visualRythim->removeWide();
    if(DEBUG_OUT)
        visualRythim->writeFile("../dump/RV_widen.jpg");

    // Create a copy of this visual frame that will be used for validating transition later
    VRFrame* visual = new VRFrame(visualRythim);

    // Apply canny edge detection on visual rhythm frame
    cout << "Edge detection ..." << endl;
    this->createBorderMap(visualRythim);

    if(DEBUG_OUT)
        visualRythim->writeFile("../dump/RV_canny.jpg");

    // Define threshold for a scene cut
    threshold = this->defineThreshold(visualRythim->getHeight());

    // Define threshold for image binarizing
    thresholdBin = (visualRythim->getMaxLum())/2;

    // Binarize the image
    cout << "Binarize the image ..." << endl;
    visualRythim->binarizeImage(thresholdBin);

    if(DEBUG_OUT)
        visualRythim->writeFile("../dump/RV_binary.jpg");

    // caculate a mapping array
    cout << "Count points ..." << endl;
    trans = countPoints(visualRythim, threshold);

    cout << "Finalizing ..." << endl;
    for(i=0; i<visualRythim->getWidth(); i++ )
    {
        if(trans[i] > 0) 
        {
            //if(validateCut(visual, i))
            {
                Transition* newTransition = new Transition(TRANSITION_CUT, i, "Corte");

                //if(this->validateTransition(i, transitionList))
                transitionList->push_back(*newTransition);
            }
        }
    }

    // release memory
    delete visualRythim;
    delete visual;
    delete vr;

}

/************************************************************************
* Create border map of a visual rhythm by applying canny filer
************************************************************************/

void Cut::createBorderMap(VRFrame* visualRythim)
{
    Filters* canny = new Filters();
    int minCannyThreshold = 100;
    int maxCannyThreshold = 200;

    // Crio o mapa de bordas do RV com o operador Canny.

    if(DEBUG_OUT)
    {
        Log::writeLog("%s :: min = %d", __FUNCTION__, minCannyThreshold);
        Log::writeLog("%s :: max = %d", __FUNCTION__, maxCannyThreshold);
    }

    canny->Canny(visualRythim, (double)minCannyThreshold, (double)maxCannyThreshold, 3);

    delete canny;

}

/************************************************************************
* Define threshold for a scene cut base on frame height
************************************************************************/

int Cut::defineThreshold(int height)
{
    //double userThreshold = 65.0; /* this threshold use for detecting logo in soccer video/ use with sub-sampling visual rhythm */
    //double userThreshold = 40.0; /* for normal use */
    double sysThreshold = 0.0;

    if (userThreshold)
        userThreshold = ((double)height * (userThreshold/100.0));
    else
        sysThreshold = height * 0.45;

    setThreshold(userThreshold > 0 ? (int)userThreshold : (int)sysThreshold);

    //	Log::writeLog("%s :: threshold(%d) ", __FUNCTION__, this->threshold);

    return (getThreshold());

}

/************************************************************************
* Countpoints
* Build a map between frame number and its map value. If this value is 1
* then this frame is a potential cut point
************************************************************************/

int* Cut::countPoints(VRFrame* borderMap, int threshold)
{
    // Coluna do mapa de bordas que estou analisando.
    int column = 0;
    int width = borderMap->getWidth();
    int height = borderMap->getHeight();

    int* transitions;
    int* points;
    int luminance = 0;	

    transitions = (int*)malloc(sizeof(int)*width);
    points = (int*)malloc(sizeof(int)*width);

    memset(transitions, 0, sizeof(int)*width);
    memset(points, 0, sizeof(int)*width);

    /**
    * After applying Canny detection and binarizing the result image, 
    * then this is black-white image. This section will count 
    * the number of white pixels at every column (a frame in the visual rhythm)
    ***/

    for (column = 2; column < width; column++)	
    {
        for (int y=0; y < height; y++)
        {
            luminance = borderMap->getPixel(column, y);
            if(luminance == 255)
            {
                points[column]++;
            }
        }
        // If number of points greater or equal threshold then mark it 1 - a potential cut position
        
        /* Consider two consicutive frame cause gradient may get extreme in both sides*/
        if(points[column] + points[column-1] >= threshold)
        {
            if(points[column] > points[column-2])
            {
                transitions[column] = 1;
                transitions[column-1] = 0;
                transitions[column-2] = 0;
            }
        }

        //transitions[column] = points >= threshold ? 1 : 0;
        //fout << "column : " << column << " -> " << points[column] << endl;
    }

    return (transitions);	
}

/*************************************************************************
* Get threshold for a scene cut
*************************************************************************/

int Cut::getThreshold(void)
{
    return (this->threshold);
}

/************************************************************************
* Set threshold for a scene cut
************************************************************************/

int Cut::setThreshold(int threshold)
{
    this->threshold = threshold;

    return 0;
}

/************************************************************************
* Check if there is a cut at a specified position
************************************************************************/

int Cut::validateCut(VRFrame* visual, int position)
{
    int width = visual->getWidth();
    int height = visual->getHeight();

    long totalPixels = height*2;
    long totalNextLum = 0; // Soma total da luminancia dos pixels dos proximos 2 frames.
    long totalPreviousLum = 0;

    long nextAvarage = 0;
    long previousAvarage = 0;

    long difference = 0;

    //	Log::writeLog("%s :: position[%d]", __FUNCTION__, position);	

    // Verifico os próximos 2 frames
    for(int x=position+1; x<=position+2 && x<width; x++)
    {
        for(int y=0; y<height; y++)
        {
            totalNextLum = totalNextLum + visual->getPixel(x,y);
        }
    }

    // Se for Fade-In, totalNextLum = 0, ou valor muito baixo.

    nextAvarage = totalNextLum/totalPixels;

    //	Log::writeLog("%s :: totalNextLum = %ld, nextAvarage = %ld", __FUNCTION__, totalNextLum, nextAvarage);	

    for(int x=position-1; x>=position-2 && x>0; x--)
    {
        for(int y=0; y<height; y++)
        {
            totalPreviousLum = totalPreviousLum + visual->getPixel(x,y);
        }
    }

    previousAvarage = totalPreviousLum/totalPixels;

    //	Log::writeLog("%s :: totalPreviousLum = %ld, previousAvarage = %ld", __FUNCTION__, totalPreviousLum, previousAvarage);	

    difference = nextAvarage - previousAvarage;

    //	Log::writeLog("%s :: difference = %ld", __FUNCTION__, difference);	

    /**
    *  Como posso ter a transição de uma cena mais clara para uma mais escura
    *  ainda preciso considerar estas diferenças. Portanto se a diferença for
    *  negativa, até certo ponto ainda é válida, por exemplo, uma cena possui média
    *  50 e vai para uma em que a média da luminosidade é 40, a diferença será -10,
    *  porém isto não é um fade-in, então considero como corte.
    **/
    if( difference < -15 )
    {
        /**
        *	Como posso ter o corte entre uma cena extremamente clara (media da luminancia 
        *	acima de 100) para uma em que a média é extremamente baixa, devo considerar 
        *	que a diferença vai ser absurda, porém não deixa de ser um corte.
        *	Os valores aqui usados foram baseados em testes deste trabalho. Não há menção disso
        *	em nenhum dos trabalhos relacionados estudados.
        * **/
        if (previousAvarage >= 100 && nextAvarage >= 10)		
        {
            return (TRUE);
        }
        // Saiu de uma cena e foi para um FADE-IN
        return (FALSE);
    }
    /**
    *	Se a diferença entre as médias for muito alta, ou a média da luminância dos frames
    *	anteriores for muito baixa, significa que está vindo de um fade-out, portanto não
    *	podemos considerar isto como um corte.
    * **/
    else if( previousAvarage < 10 ) // 10 será o padrão. TALVEZ será possível que o usuário altere isso.	
    {
        // Veio de fade-out
        return (FALSE);
    }
    /**
    *	Se a diferença das luminâncias for 0 ou muito baixa, a probabilidade de ter
    *	ocorrido um erro é significamente alta, visto que em uma única cena a luz não
    *	varia tanto (com excessão de alguns casos), portanto não podemos considerar
    *	um corte se a alteração da luminância não for significativa.
    * **/
    else if(difference >= 0 && difference < 20) // Chute!
    {
        // Objeto de cena
        return (FALSE);
    }

    // Diferença de luminâncias válida se encontra entre 31,99.
    return (TRUE);
}

/*
* Set user threshold value
* This is percentage of frame height that use to count for a scene cut
* 0<= value <= 100
*/
void Cut::setUserThreshold(double value)
{
    this->userThreshold = value;
}


/*
* Set user threshold value
*/
double Cut::getUserThreshold()
{
    return this->userThreshold;
}