// Graphical LCD routines that use a buffer 
// written from scratch - limor@ladyada.net

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h> 
#include "glcd.h"

extern uint8_t PROGMEM font[];

// the most basic function, set a single pixel
void setpixel(uint8_t *buff, uint8_t x, uint8_t y, uint8_t color) {
  if ((x >= LCDWIDTH) || (y >= LCDHEIGHT))
    return;

  // x is which column
  if (color) 
    buff[x+ (y/8)*128] |= _BV(7-(y%8));  
  else
    buff[x+ (y/8)*128] &= ~_BV(7-(y%8)); 
}


void printchar(uint8_t *buff, uint8_t x, uint8_t line, uint8_t c) {
  for (uint8_t i =0; i<5; i++ ) {
    buff[x + (line*128) ] = pgm_read_byte(font+(c*5)+i);
    x++;
  }
}

// the most basic function, clear a single pixel
void clearpixel(uint8_t *buff, uint8_t x, uint8_t y) {
  // x is which column
  buff[x+ (y/8)*128] &= ~_BV(7-(y%8));
}

// bresenham's algorithm - thx wikpedia
void drawline(uint8_t *buff,
	      uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, 
	      uint8_t color) {

  uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  uint8_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int8_t err = dx / 2;
  int8_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}

  for (; x0<x1; x0++) {
    if (steep) {
      setpixel(buff, y0, x0, color);
    } else {
      setpixel(buff, x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

// filled rectangle
void fillrect(uint8_t *buff,
	      uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
	      uint8_t color) {

  // stupidest version - just pixels - but fast with internal buffer!
  for (uint8_t i=x; i<x+w; i++) {
    for (uint8_t j=y; j<y+h; j++) {
      setpixel(buff, i, j, color);
    }
  }
}


// draw a rectangle
void drawrect(uint8_t *buff,
	      uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
	      uint8_t color) {
  // stupidest version - just pixels - but fast with internal buffer!
  for (uint8_t i=x; i<x+w; i++) {
    setpixel(buff, i, y, color);
    setpixel(buff, i, y+h-1, color);
  }
  for (uint8_t i=y; i<y+h; i++) {
    setpixel(buff, x, i, color);
    setpixel(buff, x+w-1, i, color);
  } 
}


// draw a circle
void drawcircle(uint8_t *buff,
	      uint8_t x0, uint8_t y0, uint8_t r, 
	      uint8_t color) {
  int8_t f = 1 - r;
  int8_t ddF_x = 1;
  int8_t ddF_y = -2 * r;
  int8_t x = 0;
  int8_t y = r;

  setpixel(buff, x0, y0+r, color);
  setpixel(buff, x0, y0-r, color);
  setpixel(buff, x0+r, y0, color);
  setpixel(buff, x0-r, y0, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    setpixel(buff, x0 + x, y0 + y, color);
    setpixel(buff, x0 - x, y0 + y, color);
    setpixel(buff, x0 + x, y0 - y, color);
    setpixel(buff, x0 - x, y0 - y, color);
    
    setpixel(buff, x0 + y, y0 + x, color);
    setpixel(buff, x0 - y, y0 + x, color);
    setpixel(buff, x0 + y, y0 - x, color);
    setpixel(buff, x0 - y, y0 - x, color);
    
  }
}


// draw a circle
void fillcircle(uint8_t *buff,
	      uint8_t x0, uint8_t y0, uint8_t r, 
	      uint8_t color) {
  int8_t f = 1 - r;
  int8_t ddF_x = 1;
  int8_t ddF_y = -2 * r;
  int8_t x = 0;
  int8_t y = r;

  for (uint8_t i=y0-r; i<=y0+r; i++) {
    setpixel(buff, x0, i, color);
  }

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    for (uint8_t i=y0-y; i<=y0+y; i++) {
      setpixel(buff, x0+x, i, color);
      setpixel(buff, x0-x, i, color);
    } 
    for (uint8_t i=y0-x; i<=y0+x; i++) {
      setpixel(buff, x0+y, i, color);
      setpixel(buff, x0-y, i, color);
    }    
  }
}


// clear everything
void clear_buffer(uint8_t *buff) {
  memset(buff, 0, 1024);
}
