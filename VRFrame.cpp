
#include "cv.h"
#include "highgui.h"

#include <stdexcept>
#include <math.h>

#include "Histogram.h"
#include "VRFrame.h"
#include "Log.h"

#define HIST_WIDTH  256
#define HIST_HEIGHT 256

/*************************************************************************
* Auxiliar que atualiza as variaveis internas de um objeto VRFrame 
* deve ser usada toda vez que for alterar a imagem de um frame.
*************************************************************************
* param (E): Nenhum
*************************************************************************
* Histórico:
* 29/07/08 - Fabricio Lopes de Souza
* Criação.
************************************************************************/
void VRFrame::setImage(IplImage* imgNew)
{
    Log::writeLog("%s :: old [%x] new [%x]", __FUNCTION__, this->data, imgNew);

    // Se ja tiver algum alocado
    if (this->data)
    {
        // Desaloca
        imgDealloc(this->data);
    }

    // Aponta para a img nova
    this->data = imgNew;

    // Aponta para os valores do IplImage
    this->width =  &this->data->width;
    this->height = &this->data->height;

}

/************************************************************************
* Inicializa todos os atributos com nulo
* Esta função deve ser usada em TODOS os construtores
*************************************************************************
* param (E): Nenhum
*************************************************************************
* Histórico:
* 29/07/08 - Fabricio Lopes de Souza
* Criação.
************************************************************************/
void VRFrame::initAttr()
{
    this->data = NULL;
    this->width =  NULL;
    this->height = NULL;
}

/************************************************************************
* Construtor que somente inicializa as variavies de controle com nulo 
*************************************************************************
* param (E): Nenhum
*************************************************************************
* Histórico:
* 29/07/08 - Fabricio Lopes de Souza
* Criação.
************************************************************************/
VRFrame::VRFrame()
{
    initAttr();
}

/************************************************************************
* Construtor para VRFrame que recebe os valores necessários para plotar
* um histograma. Cria um objeto VRFrame com o desenho do histograma.
*************************************************************************
* param (E): double matrix[] - Valores do Histograma
* param (E): int len_i       - Quantidade de valores em 'matrix'
* param (E): float max_f     - Valor máximo do histograma
* param (E): bool  QT        - True - Significa que esta imagem vai ser
* usada no QT
*************************************************************************
* Histórico:
* 27/06/08 - Fabricio Lopes de Souza
* Criação.
************************************************************************/
VRFrame::VRFrame(double *matrix, int len_i, float max_f, bool QT)
{

    int i;
    int normalized;
    char *frame_cy;
    CvFont font;
    CvPoint point_new  = {0,0};
    CvPoint point_last = {0,0};

    cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 0.5, 0.5, 0, 1, CV_AA);

    frame_cy = (char*)malloc(sizeof(char)*10);

    IplImage* imgHistogram = 0;

    //imgHistogram = cvCreateImage(cvSize(len_i*2, HIST_HEIGHT), 8, 1);
    imgHistogram = imgAlloc(cvSize(len_i, HIST_HEIGHT), 8, 1);

    // Desenha a area de trabalho do histograma
    //cvRectangle(imgHistogram, cvPoint(0,0), cvPoint(len_i*2,HIST_HEIGHT), CV_RGB(255,255,255), -1);
    cvRectangle(imgHistogram, cvPoint(0,0), cvPoint(len_i,HIST_HEIGHT), CV_RGB(255,255,255), -1);

    // Desenhar as linhas do histograma
    for (i=0 ; i < len_i ; i++)
    {
        // Normaliza para ajustar o tamanho
        normalized = cvRound((matrix[i]*HIST_HEIGHT)/max_f);

        Log::writeLog("%s :: Plot Value[%3d] = [%4.0lf] Normalized = [%3d]", __FUNCTION__, i, matrix[i], normalized);

        // Printa a linha do Histograma
        if (QT)
        {
            point_new = cvPoint((i-1), normalized);
        }
        else
        {
            point_new = cvPoint((i-1), HIST_HEIGHT-normalized);
        }

        // Liga os pontos
        cvLine(imgHistogram, point_new, point_new , cvScalar(0,0,0), 1);
        cvLine(imgHistogram, point_last, point_new, cvScalar(0,0,0), 1);

        if (!QT)
        {
            if (i % 32 == 0)
            {
                sprintf(frame_cy, "%d", i);
                cvPutText(imgHistogram, frame_cy, cvPoint(i-1,10), &font, CV_RGB(0,0,0));
            }
        }

        point_last = point_new;
    }

    initAttr();

    setImage(imgHistogram);

}

/************************************************************************
* Constructor: create a frame from a image file
* First create an image from that file then set the frame image
* to this image
************************************************************************/
VRFrame::VRFrame(char *filename_cy)
{
    IplImage* img;

    img = cvLoadImage(filename_cy, 1);

    if (img == NULL)
    {
        throw "Cant open file";
    }

    initAttr();
    setImage(img);
}

/************************************************************************
* Construtor: create a frame from an image
************************************************************************/
VRFrame::VRFrame(const IplImage *img_src)
{
    IplImage *imgNew;

    Log::writeLog("%s :: Constructor param: IplImage[%x]", __FUNCTION__, img_src);
    initAttr();

    imgNew = imgAlloc(cvSize(img_src->width, img_src->height), img_src->depth, img_src->nChannels);

    imgCopy(img_src, imgNew);

    setImage(imgNew);
}
/************************************************************************
* Construtor: create a frame from a frame
************************************************************************/
VRFrame::VRFrame(VRFrame *frame)
{
    IplImage *img;

    // allocate memory for the image
    img = imgAlloc(cvSize(frame->getWidth(), frame->getHeight()), frame->data->depth, frame->data->nChannels);

    imgCopy(frame->data, img);

    initAttr();
    setImage(img);

}

/************************************************************************
* Get frame width
************************************************************************/
int VRFrame::getWidth()
{
    return(*this->width);
}

/************************************************************************
* Get frame height
************************************************************************/
int VRFrame::getHeight()
{
    return(*this->height);
}

/************************************************************************
* Get the diagonal and create a vertical frame 
************************************************************************/
VRFrame * VRFrame::getDiagonal()
{
    int x = 0; // x da equacao da reta
    int y = 0; // y da equacao da reta

    VRFrame* frameDiagonal;

    double a = 0; // angle coefficent

    Log::writeLog("%s :: diagonal img width[%d] height[%d]", __FUNCTION__, 1, this->getWidth());

    IplImage* imgDiagonal = imgAlloc(cvSize(1, this->getWidth()-1), 8, 1);

    frameDiagonal = new VRFrame(imgDiagonal);


    /** calculate angle coefficent: in this case x0 = y0 = 0
    * this->getHeight = y - yo
    * this->getWidth  = x - xo
    * y - yo = m*(x - xo)
    **/
    a = (float)(this->getHeight()/(float)this->getWidth());

    // update pixel value for the diagonal frame
    for (x=0; x < this->getWidth()-1 ; x++)
    {
        y = cvRound(a * x);

        frameDiagonal->setPixel(0, x, this->getPixel(x, y));
    }	

    imgDealloc(imgDiagonal);

    return(frameDiagonal);
}

/************************************************************************
* Set pixel value at a position in frame
************************************************************************/
void VRFrame::setPixel(int x, int y, int lum)
{
    CvScalar s;

    s.val[0] = lum;

    cvSet2D(this->data, y, x, s);
}

/************************************************************************
* Get pixel value at a position in frame
************************************************************************/
int VRFrame::getPixel(int x, int y)
{
    //return ((uchar*)(this->data->imageData + this->data->widthStep*y))[x];


    CvScalar s;
    try
    {
        s = cvGet2D(this->data, y, x);
    }
    catch(...)
    {

    }

    return cvRound(s.val[0]);
}

/************************************************************************
* Destructor: release image memory
************************************************************************/
VRFrame::~VRFrame()
{
    if (this->data)
    {
        Log::writeLog("%s :: Deleting [%x]", __FUNCTION__, this->data);
        imgDealloc(this->data);
    }
}

/************************************************************************
* overload operator += to plus two frame
************************************************************************/
VRFrame & VRFrame::operator+=(VRFrame &frame)
{
    IplImage *imgDst;

    Log::writeLog("%s :: this->data[%x]", __FUNCTION__, this->data);

    // As imagens tem que ter obrigatoriamente a mesma altura
    if (this->getHeight() != frame.getHeight())
        throw;

    // Crio uma imagem com a largura igual a soma das larguras
    imgDst = imgAlloc(cvSize(this->getWidth() + frame.getWidth(), this->getHeight()), this->data->depth, this->data->nChannels);

    Log::writeLog("%s :: img_dst width[%d] height[%d]", __FUNCTION__, imgDst->width, imgDst->height);
    Log::writeLog("%s :: this x[%d] y[%d] width[%d] height[%d]", __FUNCTION__, 0, 0, this->getWidth(), this->getHeight());

    // Na imagem destino, seto a area de interesse o espaco que a primeira imagem ira ocupar
    cvSetImageROI(imgDst,
        cvRect
        (
        0,
        0,
        this->getWidth(),
        this->getHeight())
        );

    // então copio esta imagem para esta área
    imgCopy(this->data,imgDst);

    Log::writeLog("%s :: frame x[%d] y[%d] width[%d] height[%d]", __FUNCTION__, this->getWidth(), 0, frame.getWidth(), frame.getHeight());

    // Agora, seto a area de interesse o espaco que a segunda imagem irá ocupar
    cvSetImageROI(imgDst,
        cvRect
        (
        this->getWidth(),
        0,
        frame.getWidth(),
        frame.getHeight())
        );

    // Copia a segunda parte do frame
    imgCopy(frame.data,imgDst);

    // Removo as áreas de interesse da imagem
    cvResetImageROI(imgDst);

    // Seta pra imagem nova
    setImage(imgDst);

    return *this;

}

/************************************************************************
* Create a histogram from the image of a frame
************************************************************************/

Histogram* VRFrame::createHistogram()
{
    return new Histogram(this->data);
}

/************************************************************************
* Write the image to a specified file name (in image format)
************************************************************************/
void VRFrame::write(char *filename_cy)
{
    Log::writeLog("%s :: write file = [%s]", __FUNCTION__, filename_cy);

    if (this->data)
    {
        if(!cvSaveImage(filename_cy, this->data))
        {
            printf("Could not save: %s\n",filename_cy);
        }
    }
    else
    {
        Log::writeLog("%s :: No image to save", __FUNCTION__);
    }
}

/************************************************************************
* Write the image to a specified file name (in image format)
* Including horizontal coordinate information
************************************************************************
* 22/05/2011 - Sang L. Phan
************************************************************************/
void VRFrame::writeFile(char *filename_cy)
{
    Log::writeLog("%s :: write file = [%s]", __FUNCTION__, filename_cy);

    IplImage *newImg = (IplImage *)cvCloneImage(this->data);

    for(int i=0; i<newImg->width; i+=10)
    {
        CvFont font;
        cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 1, CV_AA);
        char buf[8];

        if(i%100==0)
        {
            cvLine(newImg,                         /* the dest image */
                cvPoint(i, newImg->height - 1),             /* start point */
                cvPoint(i, newImg->height - 21),            /* end point */
                cvScalar(255, 255 , 0, 0),      /* the color; green */
                1, 8, 0);                    /* thickness, line type, shift */
            sprintf(buf, "%d", i);
            cvPutText(newImg, buf, cvPoint(i, newImg->height - 25), &font, cvScalar(255, 0, 0 , 0));
        }
        else
            cvLine(newImg,                         /* the dest image */
            cvPoint(i, newImg->height - 1),             /* start point */
            cvPoint(i, newImg->height - 11),            /* end point */
            cvScalar(255, 0 , 0, 0),      /* the color; green */
            1, 8, 0);                    /* thickness, line type, shift */
    }

    if (newImg)
    {
        if(!cvSaveImage(filename_cy, newImg))
        {
            printf("Could not save: %s\n",filename_cy);
        }
    }
    else
    {
        Log::writeLog("%s :: No image to save", __FUNCTION__);
    }
}

/************************************************************************
* Overload operator = to assign a frame to another frame
************************************************************************/
VRFrame & VRFrame::operator=(VRFrame &frame)
{
    IplImage *imgNew;

    if (this->data)
    {
        Log::writeLog("%s :: Release: this->data[%x]", __FUNCTION__, this->data);
        imgDealloc(this->data);
    }

    imgNew = imgAlloc(cvSize(frame.getWidth(), frame.getHeight()), frame.data->depth, frame.data->nChannels);

    imgCopy(frame.data, imgNew);

    initAttr();

    setImage(imgNew);

    return *this;

}
/************************************************************************
* Copy image
************************************************************************/
void VRFrame::imgCopy(const IplImage *imgSrc, IplImage *imgDst)
{
    Log::writeLog("%s :: Copy : [%x] to [%x]", __FUNCTION__, imgSrc, imgDst);

    cvCopy(imgSrc, imgDst);

    imgDst->origin = 1;
}

/************************************************************************
* Allocate memory for an image that have same information with 
* the image in frame
************************************************************************/
IplImage* VRFrame::imgAlloc(VRFrame* frame)
{
    IplImage *imgNew;

    imgNew = imgAlloc(cvGetSize(frame->data), frame->data->depth, frame->data->nChannels);

    return imgNew;
}

/************************************************************************
* Allocate memory for an image with size, depth and channels information
************************************************************************/
IplImage* VRFrame::imgAlloc(CvSize size, int depth, int channels)
{
    IplImage *imgNew;

    imgNew = cvCreateImage(size, depth, channels);

    Log::writeLog("%s :: New image: [%x]", __FUNCTION__, imgNew);

    return imgNew;
}

/************************************************************************
* Release memory of an image
************************************************************************/
void VRFrame::imgDealloc(IplImage *img)
{
    Log::writeLog("%s :: Delete image: [%x]", __FUNCTION__, img);
    cvReleaseImage(&img);
}

/************************************************************************
* Binarize a frame to black (0) and white (255) image
* use a threshold to determine which side a certain point is
************************************************************************/
void VRFrame::binarizeImage(int threshold)
{
    int column = 0;
    int y = 0;

    // Percorro todo o frame coluna a coluna, pixel a pixel.
    for( column=0; column<this->getWidth(); column++ )
    {
        for( y=0; y<this->getHeight(); y++ )
        {
            // Se a luminancia for maior q o limiar, o pixel fica branco (é borda)
            if( this->getPixel(column,y) >= threshold )
                this->setPixel(column,y,255);
            else // senao fica preto (é fundo)
                this->setPixel(column,y,0);
        }
    }
}

/************************************************************************
* Calculate average luminace
************************************************************************/

double VRFrame::calcLuminanceAvarage()
{
    int i = 0;
    int height = 0;

    double total = 0; // Total da soma da luminancia dos pixels.
    double avarage = 0; // média da luminancia
    VRFrame* diagonal;

    diagonal = this->getDiagonal(); // Pego a diagonal do frame.
    height = diagonal->getHeight();

    for(i=0;i<height;i++)
    {
        total = total + diagonal->getPixel(0,i); // Função getDiagonal retorna um frame com largura de 1 pixel
    }

    avarage = total / height;

    delete diagonal;

    return (avarage);
}

/*************************************************************************
* Get maximum luminance
************************************************************************/
int VRFrame::getMaxLum()
{
    int height = this->getHeight();
    int width = this->getWidth();
    int auxLum = 0;
    int maxLuminance = 0;

    for (int x=0; x<width; x++)
    {
        for (int y=0; y<height; y++)
        {
            auxLum = this->getPixel(x,y);
            if( auxLum > maxLuminance )
                maxLuminance = auxLum;
        }
    }

    return (maxLuminance);
}

/*************************************************************************
* Remove border of frame
* Remove less significant pixels from both left and right side of frame
************************************************************************/
int VRFrame::removeBorder()
{

    int height = 0;
    int width = 0;

    int sizeWide = 0;
    int minSize = 0;
    int y = 0;
    int x = 0;

    int maxLum = 0;

    height = this->getHeight();
    width = this->getWidth();

    VRFrame* frameAux = new VRFrame(this);

    maxLum = frameAux->getMaxLum();

    frameAux->binarizeImage(maxLum/4);

    Log::writeLog("%s :: height = %d, width = %d ", __FUNCTION__, height, width);

    for( x=0; x<height; x++)
    {	
        // Quando encontrar o pixel diferente de preto eu entro e guardo a altura.
        for( y=0; y<width ;y++)
        {
            Log::writeLog("%s :: x[%d] y[%d]", __FUNCTION__, x , y);
            // Se o pixel for diferente de preto eu atribuo a altura do pixel como
            // sendo a altura do wide.
            if(frameAux->getPixel(y,x))
            {
                sizeWide = y;
                break;
            }
        }

        /**
        * Se logo de cara encontrarmos um pixel não preto, significa que não tem Wide.
        * Se a linha for toda preta sizeWide vai ser 0, mas não posso parar por causa disso,
        * então só paro se sizeWide = 0 e a altura do wide for menor que a altura do frame.
        **/
        if(!sizeWide && y<width)
            break;

        // Se minSize = 0, ainda não encontrou nenhum ponto não preto é porque ainda não encontrei
        // nenhuma altura candidata à altura do wide. Então atribuo a primeira que eu encontrar.
        if (!minSize) 
            minSize = sizeWide;

        /**
        * Se a nova altura do wide encontrada for menor que a encontrada anteriormente, 
        * atribuo esta como sendo a menor altura de wide. Caso contrário ignoro esta 
        * nova altura.
        * **/
        if (sizeWide < minSize )
            minSize = sizeWide;
        else
            sizeWide = minSize;

        // Se o tamanho do wide que achamos, for maior 
        // que metade da altura do frame, non ecziste
        if (sizeWide >= width/2)
            sizeWide = 0;
    }

    Log::writeLog("%s :: sizeWide = %d", __FUNCTION__, sizeWide);

    // Se houver widescreen
    if (sizeWide)
    {

        Log::writeLog("%s :: sizeWide_final = %d", __FUNCTION__, sizeWide);

        IplImage* img_dst;

        // Crio uma imagem nova com o tamanho do RV sem as faixas de widescreen
        img_dst = VRFrame::imgAlloc(cvSize(this->getWidth()-(sizeWide*2),this->getHeight()), this->data->depth, this->data->nChannels);

        // Pego somente a parte de interesse (sem o wide) do RV.
        cvSetImageROI(this->data,
            cvRect
            (
            sizeWide,
            0,
            this->getWidth()-(sizeWide*2),
            this->getHeight()
            )
            );

        // Copio para uma imagem nova
        imgCopy(this->data,img_dst);

        cvResetImageROI(this->data);

        // Seto o frame com o Ritmo Visual sem o wide 
        this->setImage(img_dst);

    }

    delete frameAux;

    return sizeWide;
}

/************************************************************************
* Remove wide of frame
* (remove black wide on the top and bottom side of the frame)
************************************************************************/
int VRFrame::removeWide()
{

    int height = 0;
    int width = 0;

    int sizeWide = 0;
    int minSize = 0;
    int y = 0;

    int maxLum = 0;

    height = this->getHeight();
    width = this->getWidth();

    VRFrame* frameAux = new VRFrame(this);

    maxLum = frameAux->getMaxLum();

    frameAux->binarizeImage(maxLum/4);

    //Log::writeLog("%s :: height = %d, width = %d ", __FUNCTION__, height, width);

    for( int x=0; x<width; x++ )
    {	
        // Quando encontrar o pixel diferente de preto eu entro e guardo a altura.
        for( y=0; y<height; y++)
        {
            // Se o pixel for diferente de preto eu atribuo a altura do pixel como
            // sendo a altura do wide.
            if(frameAux->getPixel(x,y))
            {
                sizeWide = y;
                break;
            }
        }

        /**
        * Se logo de cara encontrarmos um pixel não preto, significa que não tem Wide.
        * Se a linha for toda preta sizeWide vai ser 0, mas não posso parar por causa disso,
        * então só paro se sizeWide = 0 e a altura do wide for menor que a altura do frame.
        **/
        if(!sizeWide && y<height)
            break;

        // Se minSize = 0, ainda não encontrou nenhum ponto não preto é porque ainda não encontrei
        // nenhuma altura candidata à altura do wide. Então atribuo a primeira que eu encontrar.
        if (!minSize) 
            minSize = sizeWide;

        /**
        * Se a nova altura do wide encontrada for menor que a encontrada anteriormente, 
        * atribuo esta como sendo a menor altura de wide. Caso contrário ignoro esta 
        * nova altura.
        * **/
        if (sizeWide < minSize )
            minSize = sizeWide;
        else
            sizeWide = minSize;

        // Se o tamanho do wide que achamos, for maior 
        // que metade da altura do frame, non ecziste
        if (sizeWide >= height/2)
            sizeWide = 0;
    }

    //Log::writeLog("%s :: sizeWide = %d", __FUNCTION__, sizeWide);

    // Não existe wideScreen menor do que 10 pixels.
    if (sizeWide < 10)
        sizeWide = 0;

    // Se houver widescreen
    if (sizeWide)
    {

        //Log::writeLog("%s :: sizeWide_final = %d", __FUNCTION__, sizeWide);

        IplImage* img_dst;

        // Crio uma imagem nova com o tamanho do RV sem as faixas de widescreen
        img_dst = VRFrame::imgAlloc(cvSize(width,(height-(sizeWide*2))), this->data->depth, this->data->nChannels);

        // Pego somente a parte de interesse (sem o wide) do RV.
        cvSetImageROI(this->data,
            cvRect
            (
            0,
            sizeWide,
            width,
            height-(sizeWide*2)
            )
            );

        // Copio para uma imagem nova
        imgCopy(this->data,img_dst);

        cvResetImageROI(this->data);

        // Seto o frame com o Ritmo Visual sem o wide 
        this->setImage(img_dst);

    }

    delete frameAux;

    return sizeWide;
}

/************************************************************************
* Resize a frame
************************************************************************/
VRFrame* VRFrame::resize(int width, int height)
{
    IplImage *imgResized;

    imgResized = VRFrame::imgAlloc(cvSize(width,height),
        this->data->depth, this->data->nChannels);

    cvResize(this->data, imgResized);

    return new VRFrame(imgResized);

}

/************************************************************************
* Concatenate this frame with another frame
************************************************************************/
VRFrame* VRFrame::verticalCat(VRFrame* frame)
{
    VRFrame *frameDown;
    VRFrame *frameUp;
    VRFrame *frameNew;
    IplImage *imgDst;

    frameDown = new VRFrame(this);
    frameUp = new VRFrame(frame);

    imgDst = VRFrame::imgAlloc(
        cvSize(frameDown->getWidth(), frameDown->getHeight() + frameUp->getHeight()),
        frameDown->data->depth,
        frameDown->data->nChannels);

    Log::writeLog("%s :: img_dst width[%d] height[%d]", __FUNCTION__, imgDst->width, imgDst->height);

    Log::writeLog("%s :: this x[%d] y[%d] width[%d] height[%d]", __FUNCTION__, 0, 0, frameDown->getWidth(), frameDown->getHeight());

    // Na imagem destino, seto a area de interesse o espaco que a primeira imagem ira ocupar
    cvSetImageROI(imgDst,
        cvRect
        (
        0,
        0,
        frameDown->getWidth(),
        frameDown->getHeight())
        );

    // então copio esta imagem para esta área
    frameDown->imgCopy(frameDown->data,imgDst);

    Log::writeLog("%s :: this x[%d] y[%d] width[%d] height[%d]", __FUNCTION__, 0, frameUp->getHeight()+2, frameUp->getWidth(), frameUp->getHeight());

    // Agora, seto a area de interesse o espaco que a segunda imagem irá ocupar
    cvSetImageROI(imgDst,
        cvRect
        (
        0,
        frameDown->getHeight(),
        frameUp->getWidth(),
        frameUp->getHeight())
        );

    // Copia a segunda parte do frame
    VRFrame::imgCopy(frameUp->data,imgDst);

    // Removo as áreas de interesse da imagem
    cvResetImageROI(imgDst);

    frameNew = new VRFrame(imgDst);

    VRFrame::imgDealloc(imgDst);

    return frameNew;
}
