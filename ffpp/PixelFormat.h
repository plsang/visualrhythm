#ifndef PIXELFORMAT_H_
#define PIXELFORMAT_H_

#include <libavutil/avutil.h>

/* copied from libavcodec/imgconvert.c .. this is useful for pixel access :) */

#define FF_COLOR_RGB	  0 /**< RGB color space */
#define FF_COLOR_GRAY	  1 /**< gray color space */
#define FF_COLOR_YUV	  2 /**< YUV color space. 16 <= Y <= 235, 16 <= U, V <= 240 */
#define FF_COLOR_YUV_JPEG 3 /**< YUV color space. 0 <= Y <= 255, 0 <= U, V <= 255 */

#define FF_PIXEL_PLANAR   0 /**< each channel has one component in AVPicture */
#define FF_PIXEL_PACKED   1 /**< only one components containing all the channels */
#define FF_PIXEL_PALETTE  2  /**< one components containing indexes for a palette */

typedef struct {
	const char *name;
	uint8_t nb_channels;      /**< number of channels (including alpha) */
	uint8_t color_type;       /**< color type (see FF_COLOR_xxx constants) */
	uint8_t pixel_type;       /**< pixel storage type (see FF_PIXEL_xxx constants) */
	uint8_t is_alpha : 1;     /**< true if alpha can be specified */
	uint8_t x_chroma_shift;   /**< X chroma subsampling factor is 2 ^ shift */
	uint8_t y_chroma_shift;   /**< Y chroma subsampling factor is 2 ^ shift */
	uint8_t depth;            /**< bit depth of the color components */
} PixFmtInfo;


/* this table gives more information about formats */
static PixFmtInfo pix_fmt_info[PIX_FMT_NB];

static void avpicture_init_pixfmtinfo()
{
 pix_fmt_info[PIX_FMT_YUV420P].name = "yuv420p";
 pix_fmt_info[PIX_FMT_YUV420P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUV420P].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_YUV420P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUV420P].depth = 8;
 pix_fmt_info[PIX_FMT_YUV420P].x_chroma_shift = 1;
 pix_fmt_info[PIX_FMT_YUV420P].y_chroma_shift = 1;

 pix_fmt_info[PIX_FMT_YUV422P].name = "yuv422p";
 pix_fmt_info[PIX_FMT_YUV422P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUV422P].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_YUV422P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUV422P].depth = 8,
 pix_fmt_info[PIX_FMT_YUV422P].x_chroma_shift = 1;
 pix_fmt_info[PIX_FMT_YUV422P].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_YUV444P].name = "yuv444p";
 pix_fmt_info[PIX_FMT_YUV444P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUV444P].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_YUV444P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUV444P].depth = 8;
 pix_fmt_info[PIX_FMT_YUV444P].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_YUV444P].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_YUYV422].name = "yuyv422";
 pix_fmt_info[PIX_FMT_YUYV422].nb_channels = 1;
 pix_fmt_info[PIX_FMT_YUYV422].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_YUYV422].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_YUYV422].depth = 8;
 pix_fmt_info[PIX_FMT_YUYV422].x_chroma_shift = 1;
 pix_fmt_info[PIX_FMT_YUYV422].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_UYVY422].name = "uyvy422";
 pix_fmt_info[PIX_FMT_UYVY422].nb_channels = 1;
 pix_fmt_info[PIX_FMT_UYVY422].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_UYVY422].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_UYVY422].depth = 8;
 pix_fmt_info[PIX_FMT_UYVY422].x_chroma_shift = 1;
 pix_fmt_info[PIX_FMT_UYVY422].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_YUV410P].name = "yuv410p";
 pix_fmt_info[PIX_FMT_YUV410P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUV410P].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_YUV410P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUV410P].depth = 8;
 pix_fmt_info[PIX_FMT_YUV410P].x_chroma_shift = 2;
 pix_fmt_info[PIX_FMT_YUV410P].y_chroma_shift = 2;

 pix_fmt_info[PIX_FMT_YUV411P].name = "yuv411p";
 pix_fmt_info[PIX_FMT_YUV411P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUV411P].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_YUV411P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUV411P].depth = 8;
 pix_fmt_info[PIX_FMT_YUV411P].x_chroma_shift = 2;
 pix_fmt_info[PIX_FMT_YUV411P].y_chroma_shift = 0;
 
 pix_fmt_info[PIX_FMT_YUV440P].name = "yuv440p";
 pix_fmt_info[PIX_FMT_YUV440P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUV440P].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_YUV440P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUV440P].depth = 8;
 pix_fmt_info[PIX_FMT_YUV440P].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_YUV440P].y_chroma_shift = 1;
 
 pix_fmt_info[PIX_FMT_YUVA420P].name = "yuva420p";
 pix_fmt_info[PIX_FMT_YUVA420P].nb_channels = 4;
 pix_fmt_info[PIX_FMT_YUVA420P].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_YUVA420P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUVA420P].depth = 8;
 pix_fmt_info[PIX_FMT_YUVA420P].x_chroma_shift = 1;
 pix_fmt_info[PIX_FMT_YUVA420P].y_chroma_shift = 1;

 /* JPEG YUV */
 pix_fmt_info[PIX_FMT_YUVJ420P].name = "yuvj420p";
 pix_fmt_info[PIX_FMT_YUVJ420P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUVJ420P].color_type = FF_COLOR_YUV_JPEG;
 pix_fmt_info[PIX_FMT_YUVJ420P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUVJ420P].depth = 8;
 pix_fmt_info[PIX_FMT_YUVJ420P].x_chroma_shift = 1;
 pix_fmt_info[PIX_FMT_YUVJ420P].y_chroma_shift = 1;

 pix_fmt_info[PIX_FMT_YUVJ422P].name = "yuvj422p";
 pix_fmt_info[PIX_FMT_YUVJ422P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUVJ422P].color_type = FF_COLOR_YUV_JPEG;
 pix_fmt_info[PIX_FMT_YUVJ422P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUVJ422P].depth = 8;
 pix_fmt_info[PIX_FMT_YUVJ422P].x_chroma_shift = 1;
 pix_fmt_info[PIX_FMT_YUVJ422P].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_YUVJ444P].name = "yuvj444p";
 pix_fmt_info[PIX_FMT_YUVJ444P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUVJ444P].color_type = FF_COLOR_YUV_JPEG;
 pix_fmt_info[PIX_FMT_YUVJ444P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUVJ444P].depth = 8;
 pix_fmt_info[PIX_FMT_YUVJ444P].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_YUVJ444P].y_chroma_shift = 0;
 
 pix_fmt_info[PIX_FMT_YUVJ440P].name = "yuvj440p";
 pix_fmt_info[PIX_FMT_YUVJ440P].nb_channels = 3;
 pix_fmt_info[PIX_FMT_YUVJ440P].color_type = FF_COLOR_YUV_JPEG;
 pix_fmt_info[PIX_FMT_YUVJ440P].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_YUVJ440P].depth = 8;
 pix_fmt_info[PIX_FMT_YUVJ440P].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_YUVJ440P].y_chroma_shift = 1;

 /* RGB formats */
 pix_fmt_info[PIX_FMT_RGB24].name = "rgb24";
 pix_fmt_info[PIX_FMT_RGB24].nb_channels = 3;
 pix_fmt_info[PIX_FMT_RGB24].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB24].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB24].depth = 8;
 pix_fmt_info[PIX_FMT_RGB24].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB24].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_BGR24].name = "bgr24";
 pix_fmt_info[PIX_FMT_BGR24].nb_channels = 3;
 pix_fmt_info[PIX_FMT_BGR24].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_BGR24].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_BGR24].depth = 8;
 pix_fmt_info[PIX_FMT_BGR24].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_BGR24].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_RGB32].name = "rgb32";
 pix_fmt_info[PIX_FMT_RGB32].nb_channels = 4;
 pix_fmt_info[PIX_FMT_RGB32].is_alpha = 1;
 pix_fmt_info[PIX_FMT_RGB32].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB32].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB32].depth = 8;
 pix_fmt_info[PIX_FMT_RGB32].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB32].y_chroma_shift = 0;
 
 pix_fmt_info[PIX_FMT_RGB48BE].name = "rgb48be";
 pix_fmt_info[PIX_FMT_RGB48BE].nb_channels = 3;
 pix_fmt_info[PIX_FMT_RGB48BE].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB48BE].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB48BE].depth = 16;
 pix_fmt_info[PIX_FMT_RGB48BE].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB48BE].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_RGB48LE].name = "rgb48le";
 pix_fmt_info[PIX_FMT_RGB48LE].nb_channels = 3;
 pix_fmt_info[PIX_FMT_RGB48LE].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB48LE].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB48LE].depth = 16;
 pix_fmt_info[PIX_FMT_RGB48LE].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB48LE].y_chroma_shift = 0; 
 
 pix_fmt_info[PIX_FMT_RGB565].name = "rgb565";
 pix_fmt_info[PIX_FMT_RGB565].nb_channels = 3;
 pix_fmt_info[PIX_FMT_RGB565].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB565].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB565].depth = 5;
 pix_fmt_info[PIX_FMT_RGB565].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB565].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_RGB555].name = "rgb555";
 pix_fmt_info[PIX_FMT_RGB555].nb_channels = 3;
 pix_fmt_info[PIX_FMT_RGB555].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB555].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB555].depth = 5;
 pix_fmt_info[PIX_FMT_RGB555].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB555].y_chroma_shift = 0;

 /* gray / mono formats */
 pix_fmt_info[PIX_FMT_GRAY16BE].name = "gray16be";
 pix_fmt_info[PIX_FMT_GRAY16BE].nb_channels = 1;
 pix_fmt_info[PIX_FMT_GRAY16BE].color_type = FF_COLOR_GRAY;
 pix_fmt_info[PIX_FMT_GRAY16BE].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_GRAY16BE].depth = 16;

 pix_fmt_info[PIX_FMT_GRAY16LE].name = "gray16le";
 pix_fmt_info[PIX_FMT_GRAY16LE].nb_channels = 1;
 pix_fmt_info[PIX_FMT_GRAY16LE].color_type = FF_COLOR_GRAY;
 pix_fmt_info[PIX_FMT_GRAY16LE].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_GRAY16LE].depth = 16;

 pix_fmt_info[PIX_FMT_GRAY8].name = "gray";
 pix_fmt_info[PIX_FMT_GRAY8].nb_channels = 1;
 pix_fmt_info[PIX_FMT_GRAY8].color_type = FF_COLOR_GRAY;
 pix_fmt_info[PIX_FMT_GRAY8].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_GRAY8].depth = 8;

 pix_fmt_info[PIX_FMT_MONOWHITE].name = "monow";
 pix_fmt_info[PIX_FMT_MONOWHITE].nb_channels = 1;
 pix_fmt_info[PIX_FMT_MONOWHITE].color_type = FF_COLOR_GRAY;
 pix_fmt_info[PIX_FMT_MONOWHITE].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_MONOWHITE].depth = 1;

 pix_fmt_info[PIX_FMT_MONOBLACK].name = "monob";
 pix_fmt_info[PIX_FMT_MONOBLACK].nb_channels = 1;
 pix_fmt_info[PIX_FMT_MONOBLACK].color_type = FF_COLOR_GRAY;
 pix_fmt_info[PIX_FMT_MONOBLACK].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_MONOBLACK].depth = 1;

 /* paletted formats */
 pix_fmt_info[PIX_FMT_PAL8].name = "pal8";
 pix_fmt_info[PIX_FMT_PAL8].nb_channels = 4;
 pix_fmt_info[PIX_FMT_PAL8].is_alpha = 1;
 pix_fmt_info[PIX_FMT_PAL8].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_PAL8].pixel_type = FF_PIXEL_PALETTE;
 pix_fmt_info[PIX_FMT_PAL8].depth = 8;

 pix_fmt_info[PIX_FMT_UYYVYY411].name = "uyyvyy411";
 pix_fmt_info[PIX_FMT_UYYVYY411].nb_channels = 1;
 pix_fmt_info[PIX_FMT_UYYVYY411].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_UYYVYY411].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_UYYVYY411].depth = 8;
 pix_fmt_info[PIX_FMT_UYYVYY411].x_chroma_shift = 2;
 pix_fmt_info[PIX_FMT_UYYVYY411].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_BGR32].name = "bgr32";
 pix_fmt_info[PIX_FMT_BGR32].nb_channels = 4;
 pix_fmt_info[PIX_FMT_BGR32].is_alpha = 1;
 pix_fmt_info[PIX_FMT_BGR32].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_BGR32].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_BGR32].depth = 8;
 pix_fmt_info[PIX_FMT_BGR32].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_BGR32].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_BGR565].name = "bgr565";
 pix_fmt_info[PIX_FMT_BGR565].nb_channels = 3;
 pix_fmt_info[PIX_FMT_BGR565].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_BGR565].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_BGR565].depth = 5;
 pix_fmt_info[PIX_FMT_BGR565].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_BGR565].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_BGR555].name = "bgr555";
 pix_fmt_info[PIX_FMT_BGR555].nb_channels = 3;
 pix_fmt_info[PIX_FMT_BGR555].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_BGR555].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_BGR555].depth = 5;
 pix_fmt_info[PIX_FMT_BGR555].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_BGR555].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_RGB8].name = "rgb8";
 pix_fmt_info[PIX_FMT_RGB8].nb_channels = 1;
 pix_fmt_info[PIX_FMT_RGB8].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB8].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB8].depth = 8;
 pix_fmt_info[PIX_FMT_RGB8].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB8].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_RGB4].name = "rgb4";
 pix_fmt_info[PIX_FMT_RGB4].nb_channels = 1;
 pix_fmt_info[PIX_FMT_RGB4].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB4].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB4].depth = 4;
 pix_fmt_info[PIX_FMT_RGB4].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB4].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_RGB4_BYTE].name = "rgb4_byte";
 pix_fmt_info[PIX_FMT_RGB4_BYTE].nb_channels = 1;
 pix_fmt_info[PIX_FMT_RGB4_BYTE].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB4_BYTE].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB4_BYTE].depth = 8;
 pix_fmt_info[PIX_FMT_RGB4_BYTE].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB4_BYTE].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_BGR8].name = "bgr8";
 pix_fmt_info[PIX_FMT_BGR8].nb_channels = 1;
 pix_fmt_info[PIX_FMT_BGR8].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_BGR8].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_BGR8].depth = 8;
 pix_fmt_info[PIX_FMT_BGR8].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_BGR8].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_BGR4].name = "bgr4";
 pix_fmt_info[PIX_FMT_BGR4].nb_channels = 1;
 pix_fmt_info[PIX_FMT_BGR4].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_BGR4].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_BGR4].depth = 4;
 pix_fmt_info[PIX_FMT_BGR4].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_BGR4].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_BGR4_BYTE].name = "bgr4_byte";
 pix_fmt_info[PIX_FMT_BGR4_BYTE].nb_channels = 1;
 pix_fmt_info[PIX_FMT_BGR4_BYTE].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_BGR4_BYTE].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_BGR4_BYTE].depth = 8;
 pix_fmt_info[PIX_FMT_BGR4_BYTE].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_BGR4_BYTE].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_NV12].name = "nv12";
 pix_fmt_info[PIX_FMT_NV12].nb_channels = 2;
 pix_fmt_info[PIX_FMT_NV12].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_NV12].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_NV12].depth = 8;
 pix_fmt_info[PIX_FMT_NV12].x_chroma_shift = 1;
 pix_fmt_info[PIX_FMT_NV12].y_chroma_shift = 1;

 pix_fmt_info[PIX_FMT_NV21].name = "nv12";
 pix_fmt_info[PIX_FMT_NV21].nb_channels = 2;
 pix_fmt_info[PIX_FMT_NV21].color_type = FF_COLOR_YUV;
 pix_fmt_info[PIX_FMT_NV21].pixel_type = FF_PIXEL_PLANAR;
 pix_fmt_info[PIX_FMT_NV21].depth = 8;
 pix_fmt_info[PIX_FMT_NV21].x_chroma_shift = 1;
 pix_fmt_info[PIX_FMT_NV21].y_chroma_shift = 1;

 pix_fmt_info[PIX_FMT_BGR32_1].name = "bgr32_1";
 pix_fmt_info[PIX_FMT_BGR32_1].nb_channels = 4;
 pix_fmt_info[PIX_FMT_BGR32_1].is_alpha = 1;
 pix_fmt_info[PIX_FMT_BGR32_1].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_BGR32_1].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_BGR32_1].depth = 8;
 pix_fmt_info[PIX_FMT_BGR32_1].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_BGR32_1].y_chroma_shift = 0;

 pix_fmt_info[PIX_FMT_RGB32_1].name = "rgb32_1";
 pix_fmt_info[PIX_FMT_RGB32_1].nb_channels = 4;
 pix_fmt_info[PIX_FMT_RGB32_1].is_alpha = 1;
 pix_fmt_info[PIX_FMT_RGB32_1].color_type = FF_COLOR_RGB;
 pix_fmt_info[PIX_FMT_RGB32_1].pixel_type = FF_PIXEL_PACKED;
 pix_fmt_info[PIX_FMT_RGB32_1].depth = 8;
 pix_fmt_info[PIX_FMT_RGB32_1].x_chroma_shift = 0;
 pix_fmt_info[PIX_FMT_RGB32_1].y_chroma_shift = 0;
}

#endif

