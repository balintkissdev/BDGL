#ifndef BDGL_VIDEO_H_
#define BDGL_VIDEO_H_

#include "BDGL_Core.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: implement CGA, TGA, EGA and SVGA modes
/* Text display modes   */
#define BDGL_MODE_TEXT_320x200_16_GREY      (0x00)
#define BDGL_MODE_TEXT_320x200_16_COLOR     (0x01)
#define BDGL_MODE_TEXT_640x200_16_GREY      (0x02)
#define BDGL_MODE_TEXT_640x200_16_COLOR     (0x03)
#define BDGL_MODE_TEXT_720x350_MONO         (0x07)
#define BDGL_MODE_TEXT_1056x200_16_COLOR    (0x08)

/* CGA display modes    */
#define BDGL_MODE_CGA_320x200_4_COLOR       (0x04)
#define BDGL_MODE_CGA_320x200_MONO          (0x05)
#define BDGL_MODE_CGA_640x200_MONO          (0x06)

/* Tandy display modes  */
#define BDGL_MODE_TGA_320x200_16_COLOR      (0x09)
#define BDGL_MODE_TGA_640x200_4_COLOR       (0x0A)

/* EGA display modes    */
#define BDGL_MODE_EGA_320x200_16_COLOR      (0x0D)
#define BDGL_MODE_EGA_640x200_16_COLOR      (0x0E)
#define BDGL_MODE_EGA_640x350_MONO          (0x0F)
#define BDGL_MODE_EGA_640x350_4_COLOR       (0x10)

/* VGA display modes    */
#define BDGL_MODE_VGA_640x480_MONO          (0x11)
#define BDGL_MODE_VGA_640x480_16_COLOR      (0x12)
#define BDGL_MODE_VGA_320x200_256_COLOR     (0x13)

/* SVGA display modes   */
#define BDGL_MODE_SVGA_640x400_256_COLOR    (0x100)
#define BDGL_MODE_SVGA_640x480_256_COLOR    (0x101)
#define BDGL_MODE_SVGA_800x600_16_COLOR     (0x102)
#define BDGL_MODE_SVGA_800x600_256_COLOR    (0x103)
#define BDGL_MODE_SVGA_1024x768_16_COLOR    (0x104)
#define BDGL_MODE_SVGA_1024x768_256_COLOR   (0x105)
#define BDGL_MODE_SVGA_1280x1024_16_COLOR   (0x106)
#define BDGL_MODE_SVGA_1280x1024_256_COLOR  (0x107)

/* First 16 colors */
#define BDGL_BLACK          (0x00)
#define BDGL_BLUE           (0x01)
#define BDGL_GREEN          (0x02)
#define BDGL_CYAN           (0x03)
#define BDGL_RED            (0x04)
#define BDGL_MAGENTA        (0x05)
#define BDGL_BROWN          (0x06)
#define BDGL_LIGHT_GRAY     (0x07)
#define BDGL_DARK_GRAY      (0x08)
#define BDGL_LIGHT_BLUE     (0x09)
#define BDGL_LIGHT_GREEN    (0x0A)
#define BDGL_LIGHT_CYAN     (0x0B)
#define BDGL_LIGHT_RED      (0x0C)
#define BDGL_LIGHT_MAGENTA  (0x0D)
#define BDGL_YELLOW         (0x0E)
#define BDGL_WHITE          (0x0F)

/* Screen option flags */
#define BDGL_SCREEN_VSYNC            (0x01)     /* Vertical retrace (VSync) */
#define BDGL_SCREEN_DOUBLE_BUFFER    (0x02)     /* Double buffering         */
// TODO: #define BDGL_SCREEN_PAGE_FLIPPING  (0x03)

/* Data structure of the screen */
typedef struct BDGL_Screen
{
    BDGL_BYTE mode;                 /* Video mode                   */
    BDGL_WORD width, height;        /* Screen dimensions            */
    BDGL_WORD color_number;         /* Number of available colors   */
    BDGL_BYTE current_draw_color;   /* Current drawing color        */
    BDGL_BYTE *vga_memory;          /* Address of VGA memory        */
    BDGL_BYTE *buffer;              /* Buffer address               */
    BDGL_BYTE flags;                /* Option flags                 */
} BDGL_Screen;

/* Rectagular shape */
typedef struct BDGL_Rectangle
{
    int x, y;
    int width, height;
} BDGL_Rectangle;

/* 2D vertex for drawing polygons */
typedef struct BDGL_Vertex
{
    int x, y;
} BDGL_Vertex;

/**
 * Create screen and allocate memory resource for it's properties, like
 * screen dimensions, number of color and the address of the VGA memory,
 * depending on the chosen video mode.
 * Make sure you free the screen with "BDGL_DestroyScreen" at the end of
 * your program.
 *
 * @param video_mode    identifier for the video mode, for example 
 *                      "BDGL_MODE_VGA_320x200_256_COLOR" for 256 VGA mode.
 *
 * @return              pointer to allocated screen resources
 */
BDGL_Screen* BDGL_CreateScreen(const BDGL_BYTE video_mode);

/**
 * Free screen resources. This also nullifies the pointer pointing to it
 * and switches back to text mode.
 *
 * @param screen        screen pointer to deallocate memory resource from
 */
void BDGL_DestroyScreen(BDGL_Screen *const screen);

/**
 * Enable display options, like vertical sync or double buffering.
 *
 * @param flags         bit flags to customize screen properties. The following values can be set:
 *
 *                      BDGL_SCREEN_VSYNC:           Enable wait for vertical retrace (VSync)
 *                      BDGL_SCREEN_DOUBLE_BUFFER:   Enable double buffering
 *
 *                      These flags can be chained together, for example
 *
 *                      BDGL_SCREEN_VSYNC | BDGL_SCREEN_DOUBLE_BUFFER
 */
void BDGL_EnableScreenOption(BDGL_Screen *const screen, const BDGL_BYTE flags);

/**
 * Disable display options, like vertical sync or double buffering.
 *
 * @param flags         bit flags to customize screen properties. The following values can be set:
 *
 *                      BDGL_SCREEN_VSYNC:           Disable wait for vertical retrace (VSync)
 *                      BDGL_SCREEN_DOUBLE_BUFFER:   Disable double buffering
 *
 *                      These flags can be chained together, for example
 *
 *                      BDGL_SCREEN_VSYNC | BDGL_SCREEN_DOUBLE_BUFFER
 */
void BDGL_DisableScreenOption(BDGL_Screen *const screen, const BDGL_BYTE flags);

/**
 * Switch to the specified video mode of the screen.
 *
 * @param screen        screen pointer to switch video modes to
 */
void BDGL_InitializeVideo(BDGL_Screen *const screen);

/**
 * Clear screen to draw again.
 *
 * @param screen        screen pointer to be cleared
 */
void BDGL_ClearScreen(BDGL_Screen *const screen);

/**
 * Update screen with double buffering. Until this call, every pixel is written into
 * a temporary buffer before displaying.
 * This also includes waiting for vertical retrace (VSync)
 *
 * @param               screen to update
 */
void BDGL_UpdateScreen(BDGL_Screen *const screen);

/**
 * Set drawing color to draw primitives with.
 *
 * @param screen        screen to set color of
 * @param color         drawing color between 0 and 255
 */
void BDGL_SetDrawColor(BDGL_Screen *const screen, const BDGL_BYTE color);

/**
 * Modify value of color found in VGA palette. Good if you want to implement screen filtering effects or
 * want to define custom colors for yourself, however, you overwrite the default 256 color palette with this.
 *
 * This only works AFTER the screen is already initialized and displayed.
 *
 * @param screen            screen to set palette of
 * @param palette_index     index of the color in the default palette to modify
 * @param red63             red component of RGB between 0 and 63
 * @param green63           green component of RGB between 0 and 63
 * @param blue63            blue component of RGB between 0 and 63
 */
void BDGL_ModifyPaletteColor(const BDGL_BYTE palette_index, 
        const BDGL_BYTE red63, const BDGL_BYTE green63, const BDGL_BYTE blue63);

/**
 * Draw a single point as a pixel on the screen. On negative coordinates, the 
 * point doesn't wrap around the screen.
 *
 * @param screen        screen pointer to draw point on
 * @param x             horizontal x coordinate
 * @param y             vertical y coordinate
 */
void BDGL_DrawPoint(BDGL_Screen *const screen, const int x, const int y);

/**
 * Draw a straight line using Bresenham's algorithm.
 *
 * @param screen        screen pointer to draw line on
 * @param x_start       horizontal x coordinate of line starting point
 * @param y_start       vertical y coordinate of line starting point
 * @param x_end         horizontal x coordinate of line ending point
 * @param y_end         vertical y coordinate of line ending point
 */
void BDGL_DrawLine(BDGL_Screen *const screen, const int x_start, const int y_start, const int x_end, const int y_end);

/**
 * Draw outlines of a rectangle.
 *
 * @param screen        screen pointer to draw rectangle on
 * @param rectangle     rectangle to draw
 */
void BDGL_DrawRectangle(BDGL_Screen *const screen, const BDGL_Rectangle *const rectangle);

/**
 * Draw a filled rectangle.
 *
 * @param screen        screen pointer to draw filled rectangle on
 * @param rectangle     rectangle to draw
 */
void BDGL_DrawFilledRectangle(BDGL_Screen *const screen, const BDGL_Rectangle *const rectangle);

/**
 * Draw polygonal shape specified by series of vertexes.
 *
 * @param screen            screen pointer to draw polygon on
 * @param vertex_number     number of vertices to draw. Due to C decaying array parameters to pointers,
 *                          the function can't determine array size internally and needs to be specified
 *                          outside.
 * @param vertices          series of vertexes to draw
 */
void BDGL_DrawPolygon(BDGL_Screen *const screen, const int vertex_number, BDGL_Vertex const* vertices);

// TODO
/**
 * Draw filled polygonal shape specified by series of vertexes.
 */
//void BDGL_DrawFilledPolygon(BDGL_Screen *screen, const int vertex_number, BDGL_Vertex vertices[],
//                      const BDGL_BYTE color);

// TODO
/**
 * Draw bitmap image
 */
//void BDGL_DrawBMP(BDGL_ImageBMP *image, int x, int y)

#ifdef __cplusplus
}
#endif

#endif  // BDGL_VIDEO_H_
