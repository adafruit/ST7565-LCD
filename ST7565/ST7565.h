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
#ifndef _ST7565_H
#define _ST7565_H

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SPIDevice.h>
#include <SPI.h>

#define BLACK 1
#define WHITE 0

#define LCDWIDTH 128
#define LCDHEIGHT 64

#define CMD_DISPLAY_OFF   0xAE
#define CMD_DISPLAY_ON    0xAF

#define CMD_SET_DISP_START_LINE  0x40
#define CMD_SET_PAGE  0xB0

#define CMD_SET_COLUMN_UPPER  0x10
#define CMD_SET_COLUMN_LOWER  0x00

#define CMD_SET_ADC_NORMAL  0xA0
#define CMD_SET_ADC_REVERSE 0xA1

#define CMD_SET_DISP_NORMAL 0xA6
#define CMD_SET_DISP_REVERSE 0xA7

#define CMD_SET_ALLPTS_NORMAL 0xA4
#define CMD_SET_ALLPTS_ON  0xA5
#define CMD_SET_BIAS_9 0xA2 
#define CMD_SET_BIAS_7 0xA3

#define CMD_RMW  0xE0
#define CMD_RMW_CLEAR 0xEE
#define CMD_INTERNAL_RESET  0xE2
#define CMD_SET_COM_NORMAL  0xC0
#define CMD_SET_COM_REVERSE  0xC8
#define CMD_SET_POWER_CONTROL  0x28
#define CMD_SET_RESISTOR_RATIO  0x20
#define CMD_SET_VOLUME_FIRST  0x81
#define  CMD_SET_VOLUME_SECOND  0
#define CMD_SET_STATIC_OFF  0xAC
#define  CMD_SET_STATIC_ON  0xAD
#define CMD_SET_STATIC_REG  0x0
#define CMD_SET_BOOSTER_FIRST  0xF8
#define CMD_SET_BOOSTER_234  0
#define  CMD_SET_BOOSTER_5  1
#define  CMD_SET_BOOSTER_6  3
#define CMD_NOP  0xE3
#define CMD_TEST  0xF0

class ST7565 : public Adafruit_GFX {
 public:
  ST7565(int8_t sclk_pin, int8_t din_pin, int8_t dc_pin,
                   int8_t cs_pin, int8_t rst_pin);
  ST7565(int8_t dc_pin, int8_t cs_pin, int8_t rst_pin,
                   SPIClass *theSPI = &SPI);

  bool begin(uint8_t contrast = 12);
  
  void command(uint8_t c);
  void data(uint8_t c);
  
  void setContrast(uint8_t val);
  uint8_t getContrast(void);
  
  void clearDisplay(void);
  void display();
  void updateBoundingBox(uint8_t xmin, uint8_t ymin, uint8_t xmax,
                         uint8_t ymax);

  void drawPixel(int16_t x, int16_t y, uint16_t color);
  void setPixel(int16_t x, int16_t y, bool color, uint8_t *buffer);
  bool getPixel(int16_t x, int16_t y, uint8_t *buffer);
  
  void initDisplay();
  void invertDisplay(bool i);
  void scroll(int8_t vpixels, int8_t hpixels);

 private:
  Adafruit_SPIDevice *spi_dev = NULL;
  int8_t _rstpin = -1, _dcpin = -1;
  
  uint8_t _contrast;        ///< Contrast level, Vop
  uint8_t xUpdateMin, xUpdateMax, yUpdateMin, yUpdateMax;
};

#endif
