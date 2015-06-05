#include "cv.h"

#include "Histogram.h"
#include "VRFrame.h"
#include "Effect.h"
#include "Color.h"

/************************************************************************
* Convert a frame into a grayscale frame (image).
*************************************************************************
* param (E): VRFrame.
************************************************************************/

VRFrame* Color::convert2Gray(VRFrame* frame)
{
	IplImage *imgGray;
	VRFrame *frameNew;

	// Check if it's already a grayscale frame
	if (frame->data->nChannels == 1)
		return new VRFrame(frame);

	// Allocate memory for a temporary image which has same size
	// with the output frame
	imgGray = VRFrame::imgAlloc(cvGetSize(frame->data),8,1);

	// Convert RGB to grayscale;
	cvCvtColor(frame->data, imgGray, CV_RGB2GRAY);

	frameNew = new VRFrame(imgGray);

	VRFrame::imgDealloc(imgGray);

	return (frameNew);
}

/************************************************************************
* Apply color effect on frame
*************************************************************************
* param (E): VRFrame* frame => frame needs to be applied color effect
************************************************************************/

VRFrame* Color::applyEffect(VRFrame* frame)
{
	return convert2Gray(frame);
}

/************************************************************************
* Construct a Color object that will only apply effect in a fixed range of  
* the original video.
*************************************************************************
* param (E): long frameStart => start frame
* param (E): long frameEnd => end frame
************************************************************************/

Color::Color(long frameStart, long frameEnd)
{
	this->setFrameStart(frameStart);
	this->setFrameEnd(frameEnd);
	this->setName("Conversao para Cinza");
	this->setID(EFFECT_COLOR);
}

/************************************************************************
* Default constructor.
************************************************************************/

Color::Color()
{
	Color(0, 0);
}
