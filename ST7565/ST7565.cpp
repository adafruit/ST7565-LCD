/*
$Id:$

ST7565 LCD library!

Copyright (C) 2010 Limor Fried, Adafruit Industries

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

// some of this code was written by <cstone@pobox.com> originally; it is in the public domain.
*/

#include "ST7565.h"
#include "Arduino.h"
#include <stdlib.h>

/** the memory buffer for the LCD */
uint8_t st7565_buffer[LCDWIDTH * LCDHEIGHT / 8] = { 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x3, 0x7, 0xF, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x7, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x7F, 0x3F, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x1F, 0x3F, 0x70, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x6, 0x0, 0x0, 0x0, 0x3, 0x3, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xF, 0x7, 0x7, 
0x7, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xF, 0x3F, 
0x70, 0x60, 0x60, 0x60, 0x60, 0x30, 0x7F, 0x3F, 0x0, 0x0, 0x1F, 0x3F, 0x70, 0x60, 0x60, 0x60, 
0x60, 0x39, 0xFF, 0xFF, 0x0, 0x6, 0x1F, 0x39, 0x60, 0x60, 0x60, 0x60, 0x30, 0x3F, 0x7F, 0x0, 
0x0, 0x60, 0xFF, 0xFF, 0x60, 0x60, 0x0, 0x7F, 0x7F, 0x70, 0x60, 0x60, 0x40, 0x0, 0x7F, 0x7F, 
0x0, 0x0, 0x0, 0x0, 0x7F, 0x7F, 0x0, 0x0, 0x0, 0x7F, 0x7F, 0x0, 0x0, 0x60, 0xFF, 0xFF, 
0x60, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x80, 0xF8, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xE7, 0xE7, 0xE3, 
0xF3, 0xF9, 0xFF, 0xFF, 0xFF, 0xF7, 0x7, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 
0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0xF, 0x7, 0x3, 0x0, 0x0, 0x0, 0xC0, 
0xE0, 0x60, 0x20, 0x20, 0x60, 0xE0, 0xE0, 0xE0, 0x0, 0x0, 0x80, 0xC0, 0xE0, 0x60, 0x20, 0x60, 
0x60, 0xE0, 0xE0, 0xE0, 0x0, 0x0, 0x80, 0xC0, 0x60, 0x60, 0x20, 0x60, 0x60, 0xE0, 0xE0, 0x0, 
0x0, 0x0, 0xE0, 0xE0, 0x0, 0x0, 0x0, 0xE0, 0xE0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0xE0, 
0x60, 0x60, 0x60, 0x60, 0xE0, 0x80, 0x0, 0x0, 0x0, 0xE0, 0xE0, 0x0, 0x0, 0x0, 0xE0, 0xE0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x0, 0x0, 0x0, 0x3, 0x7, 0x1F, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xF1, 0xE3, 
0xE3, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFC, 0x7F, 0x3F, 0x3F, 0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF0, 0xE0, 0x80, 0x0, 0x0, 0x0, 0xC, 
0x1C, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7F, 0x7F, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x7, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1C, 0xC, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 

0x0, 0x7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 
0xF8, 0xF0, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 
0xFF, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xE0, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F, 0x0, 0x0, 0x1E, 0x7F, 
0xE1, 0xC0, 0xC0, 0xC0, 0xC0, 0x61, 0xFF, 0xFF, 0x0, 0x0, 0xFE, 0xFF, 0x1, 0x0, 0x0, 0x0, 
0xFF, 0xFF, 0x0, 0x0, 0x21, 0xF9, 0xF8, 0xDC, 0xCC, 0xCF, 0x7, 0x0, 0xC0, 0xFF, 0xFF, 0xC0, 
0x80, 0x0, 0xFF, 0xFF, 0xC0, 0xC0, 0x80, 0x0, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0x1F, 0x7F, 0xF9, 
0xC8, 0xC8, 0xC8, 0xC8, 0x79, 0x39, 0x0, 0x0, 0x71, 0xF9, 0xD8, 0xCC, 0xCE, 0x47, 0x3, 0x0, 

0x0, 0x0, 0x0, 0x0, 0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x0, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0, 0xC0, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xC0, 
0xC0, 0x0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0x80, 
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 
0xC0, 0x80, 0x0, 0x0, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 
0x0, 0x0, 0xC0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0xC0, 0xC0, 0x0, 0x0, 0x0, 0x80, 0xC0, 
0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x0, 0x0, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x0, 0x0, 

0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,};

/*!
  @brief Constructor for software SPI with explicit CS pin
  @param sclk_pin SCLK pin
  @param din_pin  DIN pin
  @param dc_pin   DC pin
  @param cs_pin   CS pin
  @param rst_pin  RST pin
 */
ST7565::ST7565(int8_t sclk_pin, int8_t din_pin,
                                   int8_t dc_pin, int8_t cs_pin, int8_t rst_pin)
    : Adafruit_GFX(LCDWIDTH, LCDHEIGHT) {
  spi_dev = new Adafruit_SPIDevice(cs_pin, sclk_pin, -1, din_pin,
                                   4000000); // 4mhz max speed

  _dcpin = dc_pin;
  _rstpin = rst_pin;
}

/*!
  @brief Constructor for hardware SPI based on hardware controlled SCK (SCLK)
  and MOSI (DIN) pins. CS is still controlled by any IO pin. NOTE: MISO and SS
  will be set as an input and output respectively, so be careful sharing those
  pins!
  @param dc_pin   DC pin
  @param cs_pin   CS pin
  @param rst_pin  RST pin
  @param theSPI   Pointer to SPIClass device for hardware SPI
 */
ST7565::ST7565(int8_t dc_pin, int8_t cs_pin, int8_t rst_pin,
                                   SPIClass *theSPI)
    : Adafruit_GFX(LCDWIDTH, LCDHEIGHT) {
  spi_dev = new Adafruit_SPIDevice(cs_pin, 4000000, SPI_BITORDER_MSBFIRST,
                                   SPI_MODE0, theSPI);

  _dcpin = dc_pin;
  _rstpin = rst_pin;
}

/*!
  @brief Update the bounding box for partial updates
  @param xmin left
  @param ymin bottom
  @param xmax right
  @param ymax top
 */
void ST7565::updateBoundingBox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax) {
  if (xmin < xUpdateMin) xUpdateMin = xmin;
  if (xmax > xUpdateMax) xUpdateMax = xmax;
  if (ymin < yUpdateMin) yUpdateMin = ymin;
  if (ymax > yUpdateMax) yUpdateMax = ymax;
}

/*!
  @brief The most basic function, set a single pixel, in the main buffer
  @param x     x coord
  @param y     y coord
  @param color pixel color (BLACK or WHITE)
 */
void ST7565::drawPixel(int16_t x, int16_t y, uint16_t color) {
  setPixel(x, y, color, st7565_buffer);
}

/*!
  @brief The most basic function, set a single pixel
  @param x     x coord
  @param y     y coord
  @param color pixel color (BLACK or WHITE)
  @param buffer The framebuffer to set the pixel in
 */
void ST7565::setPixel(int16_t x, int16_t y, bool color,
                                uint8_t *buffer) {
  if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
    return;

  int16_t t;
  switch (rotation) {
  case 1:
    t = x;
    x = y;
    y = LCDHEIGHT - 1 - t;
    break;
  case 2:
    x = LCDWIDTH - 1 - x;
    y = LCDHEIGHT - 1 - y;
    break;
  case 3:
    t = x;
    x = LCDWIDTH - 1 - y;
    y = t;
    break;
  }
  updateBoundingBox(x, y, x, y);

  // x is which column
  if (color)
    buffer[x + (y / 8) * LCDWIDTH] |= (1 << (7 - (y % 8)));
  else
    buffer[x + (y / 8) * LCDWIDTH] &= ~(1 << (7 - (y % 8)));
}

/*!
  @brief The most basic function, get a single pixel
  @param  x x coord
  @param  y y coord
  @param buffer The framebuffer to get the pixel from
  @return   color of the pixel at x,y
 */
bool ST7565::getPixel(int16_t x, int16_t y, uint8_t *buffer) {
  if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
    return false;

  int16_t t;
  switch (rotation) {
  case 1:
    t = x;
    x = y;
    y = LCDHEIGHT - 1 - t;
    break;
  case 2:
    x = LCDWIDTH - 1 - x;
    y = LCDHEIGHT - 1 - y;
    break;
  case 3:
    t = x;
    x = LCDWIDTH - 1 - y;
    y = t;
    break;
  }

  return (buffer[x + (y / 8) * LCDWIDTH] >> (7 - (y % 8))) & 0x1;
}

/*!
  @brief Initialize the display.
 */
void ST7565::initDisplay() {

  // toggle RST low to reset
  if (_rstpin >= 0) {
    pinMode(_rstpin, OUTPUT);
    digitalWrite(_rstpin, LOW);
    delay(1); // 1 ns minimum
    digitalWrite(_rstpin, HIGH);
  }

  // LCD bias select
  command(CMD_SET_BIAS_7);
  // ADC select
  command(CMD_SET_ADC_NORMAL);
  // SHL select
  command(CMD_SET_COM_NORMAL);
  // Initial display line
  command(CMD_SET_DISP_START_LINE);
  
  // turn on voltage converter (VC=1, VR=0, VF=0)
  command(CMD_SET_POWER_CONTROL | 0x4);
  // wait for 50% rising
  delay(50);
  
  // turn on voltage regulator (VC=1, VR=1, VF=0)
  command(CMD_SET_POWER_CONTROL | 0x6);
  // wait >=50ms
  delay(50);
  
  // turn on voltage follower (VC=1, VR=1, VF=1)
  command(CMD_SET_POWER_CONTROL | 0x7);
  // wait
  delay(10);
  
  // set lcd operating voltage (regulator resistor, ref voltage resistor)
  command(CMD_SET_RESISTOR_RATIO | 0x6);
  command(CMD_DISPLAY_ON);
  command(CMD_SET_ALLPTS_NORMAL);
}

/*!
  @brief Set up SPI, initialize the display, set the bounding box
  @param contrast Initial contrast value
  @returns True on initialization success
 */

bool ST7565::begin(uint8_t contrast) {

  if (!spi_dev->begin()) {
    return false;
  }

  // Set common pin outputs.
  pinMode(_dcpin, OUTPUT);
  if (_rstpin >= 0)
    pinMode(_rstpin, OUTPUT);

  _contrast = contrast;
  initDisplay();
  setContrast(_contrast);

  // set up a bounding box for screen updates
  updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);

  return true;
}

/*!
  @brief  Send a command to the LCD
  @param c Command byte
 */
void ST7565::command(uint8_t c) {
  digitalWrite(_dcpin, LOW);
  spi_dev->write(&c, 1);
}

/*!
  @brief  Send data to the LCD
  @param c Data byte
 */
void ST7565::data(uint8_t c) {
  digitalWrite(_dcpin, HIGH);
  spi_dev->write(&c, 1);
}

/*!
  @brief  Set the contrast level
  @param val Contrast value
 */
void ST7565::setContrast(uint8_t val) {
  if (val > 0x3f) {
    val = 0x3f;
  }
  _contrast = val;
  command(CMD_SET_VOLUME_FIRST);
  command(CMD_SET_VOLUME_SECOND | val);
}

/*!
  @brief  Get the contrast level
  @return Contrast value
 */
uint8_t ST7565::getContrast() { return _contrast; }

/*!
  @brief Update the display
 */
void ST7565::display(void) {

  for(uint16_t p = 0; p < 8; p++) {
    command( CMD_SET_PAGE | (7 - p) );

    // start at the beginning of the row
    command(CMD_SET_COLUMN_UPPER | 0);
    command(CMD_SET_COLUMN_LOWER | 0);
  
    for(uint8_t col = 0; col < LCDWIDTH; col++) {
      data(st7565_buffer[ (p * LCDWIDTH) + col ]);
    }
  }
}

/*!
  @brief Clear the entire display
 */
void ST7565::clearDisplay(void) {
  memset(st7565_buffer, 0, LCDWIDTH * LCDHEIGHT / 8);
  updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);
  cursor_y = cursor_x = 0;
}

/*!
  @brief Invert the entire display
  @param i True to invert the display, false to keep it uninverted
 */
void ST7565::invertDisplay(bool i) {
  command(i ? CMD_SET_DISP_REVERSE : CMD_SET_DISP_NORMAL);
}

/*!
  @brief Scroll the display by creating a new buffer and moving each pixel
  @param xpixels The x offset, can be negative to scroll backwards
  @param ypixels The y offset, can be negative to scroll updwards
 */
void ST7565::scroll(int8_t xpixels, int8_t ypixels) {
  uint8_t new_buffer[LCDWIDTH * LCDHEIGHT / 8];
  memset(new_buffer, 0, LCDWIDTH * LCDHEIGHT / 8);

  // negative pixels wrap around
  while (ypixels < 0) {
    ypixels += height();
  }
  ypixels %= height();
  while (xpixels < 0) {
    xpixels += width();
  }
  xpixels %= width();

  for (int x = 0; x < width(); x++) {
    for (int y = 0; y < height(); y++) {
      if (getPixel(x, y, st7565_buffer)) {
        int new_x = (x + xpixels) % _width;
        int new_y = (y + ypixels) % _height;
        setPixel(new_x, new_y, true, new_buffer);
      }
    }
  }
  memcpy(st7565_buffer, new_buffer, LCDWIDTH * LCDHEIGHT / 8);
  updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);
}
