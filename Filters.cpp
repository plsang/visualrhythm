#include "cv.h"
#include "highgui.h"

#include "Log.h"

#include "Histogram.h"
#include "VRFrame.h"
#include "Filters.h"

/************************************************************************
* Image segmentation using a threshold
************************************************************************/
void Filters::segment(VRFrame* frame, int threshold)
{
    IplImage* img_dst;
    //	VRFrame *frameNew;

    Log::writeLog("%s :: param: frame[%x] threshold[%d]", __FUNCTION__, frame, threshold);

    // allocate memory for temporary image
    img_dst = VRFrame::imgAlloc(cvGetSize(frame->data),frame->data->depth,frame->data->nChannels);

    Log::writeLog("%s :: cvThreshold: frame_src[%x] frame_dst[%d] thresh[%d] maxValue[%d] CvThresh[%s]", __FUNCTION__, frame->data, img_dst, threshold, 255, "CV_THRESH_BINARY_INV");

    // apply threshold
    cvThreshold(frame->data, img_dst, threshold, 255, CV_THRESH_BINARY_INV);

    //	frameNew = new VRFrame(img_dst);

    frame->setImage(img_dst);

}

/************************************************************************
* Filter using sobel mask
*************************************************************************
* param (E): VRFrame* frame: frame to be filtered.
* param (E): int direction:
* 				 0 - Vertical
* 				 1 - Horizontal
* 				 2 - Vertical e Horizontal
************************************************************************/

void Filters::Sobel(VRFrame* frame, int direction)
{
    IplImage* img_dst;

    Log::writeLog("%s :: param: frame[%x] direction[%d]", __FUNCTION__, frame, direction);

    img_dst = VRFrame::imgAlloc(cvGetSize(frame->data),frame->data->depth,frame->data->nChannels);

    switch(direction)
    {

    case 0: //Vertical

        Log::writeLog("%s :: cvSobel : frame_src[%x] frame_dst[%d] dx[%d] dy[%d] apertureSize[%d]",
            __FUNCTION__, frame->data, img_dst, 1, 0, 3);

        cvSobel(frame->data,img_dst,1,0,3);
        break;
    case 1: //Horizontal

        Log::writeLog("%s :: cvSobel : frame_src[%x] frame_dst[%d] dx[%d] dy[%d] apertureSize[%d]",
            __FUNCTION__, frame->data, img_dst, 0, 1, 3);

        cvSobel(frame->data,img_dst,0,1,3);
        break;
    case 2: //Both

        Log::writeLog("%s :: cvSobel : frame_src[%x] frame_dst[%d] dx[%d] dy[%d] apertureSize[%d]",
            __FUNCTION__, frame->data, img_dst, 1, 1, 3);

        cvSobel(frame->data,img_dst,1,1,3);
        break;

    }	

    frame->setImage(img_dst);

}

/************************************************************************
* Canny Filter
*************************************************************************
* cvCanny( const CvArr* image, CvArr* edges, double threshold1, 
* 			  double threshold2, int aperture_size=3 );
************************************************************************/

void Filters::Canny(VRFrame* frame, double thresholdMin, double thresholdMax, int size)
{
    IplImage* img_dst;

    img_dst = VRFrame::imgAlloc(frame);

    Log::writeLog("%s :: thresholdMin[%lf], thresholdMax[%lf], size[%d]", __FUNCTION__, thresholdMin, thresholdMax, size);

    cvCanny(frame->data, img_dst, thresholdMin, thresholdMax, size);

    frame->setImage(img_dst);
}

/************************************************************************
* Low Pass filter
************************************************************************/

void Filters::lowPass(VRFrame* frame, int size)
{
    IplImage* imgDst = 0;
    IplImage* imgAux = 0;
    IplImage* imgNew = 0;

    VRFrame* frameAux;

    Log::writeLog("%s :: param: frame[%x] size[%d]", __FUNCTION__, frame, size);

    //Ajuste do tamanho da matriz.
    if (size > 9)
        size = 9;

    int cols_i = size;
    int rows_i = size;
    int total_size = 0;
    CvMat *filter = 0;

    total_size=(int)pow((double)size,2);

    // Máscara para realizar o processo de convolução.
    ///double convMask[total_size];
    double * convMask = new double[total_size];

    // Cria uma imagem com os mesmos parâmetros da original.
    frameAux = new VRFrame(frame);

    imgDst = VRFrame::imgAlloc(frameAux);
    imgAux = VRFrame::imgAlloc(frameAux);
    imgNew = VRFrame::imgAlloc(frameAux);

    // Monta a máscara com o tamanho que foi passado como parâmetro.
    for (int i=0; i<total_size; i++)	
        convMask[i] = (double)1/(double)total_size;

    imgAux->imageData = frameAux->data->imageData;
    imgAux->widthStep = frameAux->data->width;

    imgDst->imageData = imgAux->imageData;
    imgDst->widthStep = imgAux->width;

    filter = cvCreateMatHeader(rows_i, cols_i, CV_64FC1);

    cvSetData(filter, convMask, cols_i*8);

    cvFilter2D(imgAux, imgDst, filter, cvPoint(-1,-1));

    VRFrame::imgCopy(imgDst, imgNew);

    frame->setImage(imgNew);

    // Desaloca os temporários
    VRFrame::imgDealloc(imgAux);
    VRFrame::imgDealloc(imgDst);

    delete[] convMask;
    delete frameAux;

}

/************************************************************************
* High pass filter
*************************************************************************
* param (E): VRFrame* frame: VRFrame that needs to be filtered.
* param (E): int typeMas: Type of mask (0, 1 ou 2).
* 	==========================================================
* 	|	type 0			||		type 1		||		type 2		|
* 	|  	-1 -1 -1 		|| 	0 -1  0 		||		1 -2  1 	|
* 	|  	-1  8 -1 		|| -1  4 -1 		||     -2  4 -2 	|
* 	|  	-1 -1 -1 		|| 	0 -1  0 		||	    1 -2  1 	|
* 	==========================================================
************************************************************************/

void Filters::highPass(VRFrame* frame, int typeMask)
{
    IplImage* imgDst = 0;
    IplImage* imgAux = 0;
    IplImage* imgNew = 0;

    VRFrame* frameAux = 0;

    int cols = 0;
    int rows = 0;
    CvMat *filter = 0;

    // mask type
    double masks[][9] = {
        // Type 1
        { 
            -1, -1, -1,
            -1,  8, -1,
            -1, -1, -1,
        },
        // Type 2
        {
            0, -1,  0,
            -1, 4, -1,
            0, -1,  0,
        },
        // Type 3
        {
            1 , -2,  1,
            -2,  4, -2,
            1 , -2,  1,
        },
    };

    // allocate memory for temporary image
    imgAux = VRFrame::imgAlloc(frame);
    imgDst = VRFrame::imgAlloc(frame);
    imgNew = VRFrame::imgAlloc(frame);

    frameAux = new VRFrame(frame);

    // type 0 is the default mask. set to this type if type not found
    if (typeMask > 3 || typeMask < 0)
        typeMask = 0;

    Log::writeLog("%s :: param: frame[%x] typeMask[%d]", __FUNCTION__, frame, typeMask);

    cols = 3;
    rows = 3;

    imgAux->imageData = frameAux->data->imageData;
    imgAux->widthStep = frameAux->data->width;

    imgDst->imageData = imgAux->imageData;
    imgDst->widthStep = imgAux->width;

    Log::writeLog("%s :: cvCreateMatHeader: rows[%d] cols[%d] CV_64FC1", __FUNCTION__, rows, cols);

    filter = cvCreateMatHeader(rows, cols, CV_64FC1);

    Log::writeLog("%s :: cvSetData: filter[%x] masks[%x] cols[%d]", __FUNCTION__, filter, masks[typeMask], cols*8);

    cvSetData(filter, masks[typeMask], cols*8);

    Log::writeLog("%s :: cvFilter2D: imgAux[%x] imgDst[%x] filter[%x] cvPoint[%x]", __FUNCTION__, imgAux, imgDst, filter, cvPoint(-1,-1));

    cvFilter2D(imgAux, imgDst, filter, cvPoint(-1,-1));

    //
    VRFrame::imgCopy(imgDst, imgNew);

    frame->setImage(imgNew);

    // release memory
    VRFrame::imgDealloc(imgAux);
    VRFrame::imgDealloc(imgDst);
    delete frameAux;

}