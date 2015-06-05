
/************************************************************************
* Class provides methods for processing at frame level
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/

#ifndef FRAME_INCLUDE
#define FRAME_INCLUDE
class VRFrame 
{
private:

    /**
    *width of frame
    */
    int *width;

    /**
    *height of frame
    */
    int *height;

public:

    IplImage* data;

    // Construtor/Destrutor
    VRFrame();
    VRFrame(char *filename_cy);
    VRFrame(const IplImage *img_src);
    VRFrame(VRFrame *frame);
    VRFrame(double *matrix, int len_i, float max_f, bool QT = true);
    ~VRFrame();

    // methods
    Histogram* createHistogram();
    VRFrame* getDiagonal();
    VRFrame* verticalCat(VRFrame* frame);
    VRFrame* resize(int width, int height);
    int removeWide();
    int removeBorder();
    void binarizeImage(int treshold);	
    void initAttr();
    void write(char *filename_cy);
    double calcLuminanceAvarage();

    // static methods
    static void imgCopy(const IplImage *imgSrc, IplImage *imgDst);
    static void imgDealloc(IplImage* img);
    static IplImage* imgAlloc(CvSize size, int depth, int channels); 
    static IplImage* imgAlloc(VRFrame *frame);

    // Gets/Sets
    int getWidth();
    int getHeight();
    int getPixel(int x, int y);
    int getMaxLum();
    void setPixel(int x, int y, int lum);
    void setImage(IplImage *imgNew);

    // Operadores
    VRFrame& operator+=(VRFrame& frame);
    VRFrame&  operator=(VRFrame& frame);

    //
    void writeFile(char *);
};
#endif
