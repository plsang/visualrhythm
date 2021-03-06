#include "PixelFormat.h"


//extern static PixFmtInfo pix_fmt_info[PIX_FMT_NB];

#define C99_SUPPORT 0
#if !C99_SUPPORT

#else

extern "C" {
const PixFmtInfo pix_fmt_info[PIX_FMT_NB] = {
	/* YUV formats */
	[PIX_FMT_YUV420P] = {
		.name = "yuv420p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 1, .y_chroma_shift = 1,
	},
	[PIX_FMT_YUV422P] = {
		.name = "yuv422p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 1, .y_chroma_shift = 0,
	},
	[PIX_FMT_YUV444P] = {
		.name = "yuv444p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_YUYV422] = {
		.name = "yuyv422",
		.nb_channels = 1,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 1, .y_chroma_shift = 0,
	},
	[PIX_FMT_UYVY422] = {
		.name = "uyvy422",
		.nb_channels = 1,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 1, .y_chroma_shift = 0,
	},
	[PIX_FMT_YUV410P] = {
		.name = "yuv410p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 2, .y_chroma_shift = 2,
	},
	[PIX_FMT_YUV411P] = {
		.name = "yuv411p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 2, .y_chroma_shift = 0,
	},
	[PIX_FMT_YUV440P] = {
		.name = "yuv440p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 1,
	},

	/* YUV formats with alpha plane */
	[PIX_FMT_YUVA420P] = {
		.name = "yuva420p",
		.nb_channels = 4,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 1, .y_chroma_shift = 1,
	},

	/* JPEG YUV */
	[PIX_FMT_YUVJ420P] = {
		.name = "yuvj420p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV_JPEG,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 1, .y_chroma_shift = 1,
	},
	[PIX_FMT_YUVJ422P] = {
		.name = "yuvj422p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV_JPEG,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 1, .y_chroma_shift = 0,
	},
	[PIX_FMT_YUVJ444P] = {
		.name = "yuvj444p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV_JPEG,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_YUVJ440P] = {
		.name = "yuvj440p",
		.nb_channels = 3,
		.color_type = FF_COLOR_YUV_JPEG,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 1,
	},

	/* RGB formats */
	[PIX_FMT_RGB24] = {
		.name = "rgb24",
		.nb_channels = 3,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_BGR24] = {
		.name = "bgr24",
		.nb_channels = 3,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_RGB32] = {
		.name = "rgb32",
		.nb_channels = 4, .is_alpha = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_RGB565] = {
		.name = "rgb565",
		.nb_channels = 3,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 5,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_RGB555] = {
		.name = "rgb555",
		.nb_channels = 3,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 5,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},

	/* gray / mono formats */
	[PIX_FMT_GRAY16BE] = {
		.name = "gray16be",
		.nb_channels = 1,
		.color_type = FF_COLOR_GRAY,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 16,
	},
	[PIX_FMT_GRAY16LE] = {
		.name = "gray16le",
		.nb_channels = 1,
		.color_type = FF_COLOR_GRAY,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 16,
	},
	[PIX_FMT_GRAY8] = {
		.name = "gray",
		.nb_channels = 1,
		.color_type = FF_COLOR_GRAY,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
	},
	[PIX_FMT_MONOWHITE] = {
		.name = "monow",
		.nb_channels = 1,
		.color_type = FF_COLOR_GRAY,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 1,
	},
	[PIX_FMT_MONOBLACK] = {
		.name = "monob",
		.nb_channels = 1,
		.color_type = FF_COLOR_GRAY,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 1,
	},

	/* paletted formats */
	[PIX_FMT_PAL8] = {
		.name = "pal8",
		.nb_channels = 4, .is_alpha = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PALETTE,
		.depth = 8,
	},
	[PIX_FMT_XVMC_MPEG2_MC] = {
		.name = "xvmcmc",
	},
	[PIX_FMT_XVMC_MPEG2_IDCT] = {
		.name = "xvmcidct",
	},
	[PIX_FMT_UYYVYY411] = {
		.name = "uyyvyy411",
		.nb_channels = 1,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 2, .y_chroma_shift = 0,
	},
	[PIX_FMT_BGR32] = {
		.name = "bgr32",
		.nb_channels = 4, .is_alpha = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_BGR565] = {
		.name = "bgr565",
		.nb_channels = 3,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 5,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_BGR555] = {
		.name = "bgr555",
		.nb_channels = 3,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 5,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_RGB8] = {
		.name = "rgb8",
		.nb_channels = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_RGB4] = {
		.name = "rgb4",
		.nb_channels = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 4,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_RGB4_BYTE] = {
		.name = "rgb4_byte",
		.nb_channels = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_BGR8] = {
		.name = "bgr8",
		.nb_channels = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_BGR4] = {
		.name = "bgr4",
		.nb_channels = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 4,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_BGR4_BYTE] = {
		.name = "bgr4_byte",
		.nb_channels = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_NV12] = {
		.name = "nv12",
		.nb_channels = 2,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 1, .y_chroma_shift = 1,
	},
	[PIX_FMT_NV21] = {
		.name = "nv12",
		.nb_channels = 2,
		.color_type = FF_COLOR_YUV,
		.pixel_type = FF_PIXEL_PLANAR,
		.depth = 8,
		.x_chroma_shift = 1, .y_chroma_shift = 1,
	},

	[PIX_FMT_BGR32_1] = {
		.name = "bgr32_1",
		.nb_channels = 4, .is_alpha = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
	[PIX_FMT_RGB32_1] = {
		.name = "rgb32_1",
		.nb_channels = 4, .is_alpha = 1,
		.color_type = FF_COLOR_RGB,
		.pixel_type = FF_PIXEL_PACKED,
		.depth = 8,
		.x_chroma_shift = 0, .y_chroma_shift = 0,
	},
};

}
#endif
