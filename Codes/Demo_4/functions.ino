//developed by mohammed rezwanul islam @ shuzonudas@gamil.com
//modified version of adafruit 1.8" TFT library

#include <avr/io.h> 
#include <avr/pgmspace.h>
#include <SPI.h>

#define TFA  21  //Top Fixed Area (height)
#define BFA  11  // Bottom Fixed Area - best leave a multiple of font height for scroll area to avoid blank lines.

#define swap(a, b) { int16_t t = a; a = b; b = t; }

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

byte _CE =9;
byte _DATA=11;
byte _CLK=13;


uint8_t _setBackColorRed = 0x00;
uint8_t _setBackColorGreen = 0xFF;
uint8_t _setBackColorBlue = 0xF0;
 
uint8_t _fontSize=2;
 
uint8_t _x_pos=1;
uint8_t _y_pos=1;
 
uint8_t _LCD_x=128;
uint8_t _LCD_y=160;
 
uint8_t _textColorRed=00;
uint8_t _textColorBlue=255;
uint8_t _textColorGreen=255;



 static const byte ASCII[][5]  PROGMEM =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c �
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ?
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f ?
};



void setTextSize(uint8_t x)
{
  _fontSize = x;
  if (x <1) {  _fontSize = 1;}
}

void setCursor( uint8_t x,uint8_t y)
{
  _x_pos=x;
  _y_pos=y;
}

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h) 
{
  for (int16_t i=x; i<x+w; i++) 
  {
    drawFastVLine(i, y, h);
  }
}

void fillRoundRect(int16_t x, int16_t y, int16_t w,
				 int16_t h, int16_t r) {
  // smarter version
  fillRect(x+r, y, w-2*r, h );

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1 );
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1 );
}

void drawRoundRect(int16_t x, int16_t y, int16_t w,
  int16_t h, int16_t r) {
  // smarter version
  drawFastHLine(x+r  , y    , w-2*r ); // Top
  drawFastHLine(x+r  , y+h-1, w-2*r ); // Bottom
  drawFastVLine(x    , y+r  , h-2*r ); // Left
  drawFastVLine(x+w-1, y+r  , h-2*r ); // Right
  // draw four corners
  drawCircleHelper(x+r    , y+r    , r, 1 );
  drawCircleHelper(x+w-r-1, y+r    , r, 2 );
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4 );
  drawCircleHelper(x+r    , y+h-r-1, r, 8 );
}

void drawRect(int16_t x, int16_t y,int16_t w, int16_t h)
{
  drawFastHLine(x, y, w);
  drawFastHLine(x, y+h-1, w);
  drawFastVLine(x, y, h);
  drawFastVLine(x+w-1, y, h);
}

void drawFastHLine(int16_t x, int16_t y,int16_t w) 
{
  drawLine(x, y, x+w-1, y);
}

void fillCircle(int16_t x0, int16_t y0, int16_t r)
{
  drawFastVLine(x0, y0-r, 2*r+1);
  fillCircleHelper(x0, y0, r, 3, 0);
}

void fillCircleHelper(int16_t x0, int16_t y0, int16_t r,uint8_t cornername, int16_t delta)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta);
    }
  }
}

void drawFastVLine(int16_t x, int16_t y,int16_t h) 
{
  drawLine(x, y, x, y+h-1);
}

void drawCircleHelper( int16_t x0, int16_t y0,
               int16_t r, uint8_t cornername) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y );
      drawPixel(x0 + y, y0 + x );
    } 
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y );
      drawPixel(x0 + y, y0 - x );
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x );
      drawPixel(x0 - x, y0 + y );
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x );
      drawPixel(x0 - x, y0 - y );
    }
  }
}
// Draw a circle outline
void drawCircle(int16_t x0, int16_t y0, int16_t r) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0  , y0+r);
  drawPixel(x0  , y0-r);
  drawPixel(x0+r, y0);
  drawPixel(x0-r, y0);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(x0 + x, y0 + y);
    drawPixel(x0 - x, y0 + y );
    drawPixel(x0 + x, y0 - y );
    drawPixel(x0 - x, y0 - y );
    drawPixel(x0 + y, y0 + x );
    drawPixel(x0 - y, y0 + x );
    drawPixel(x0 + y, y0 - x );
    drawPixel(x0 - y, y0 - x );
  }
}

void setBackColor( uint8_t red, uint8_t green, uint8_t blue)
{
  _setBackColorRed = red;
  _setBackColorGreen = green;
  _setBackColorBlue = blue;
}

void fillScreen(void)
{
  // set column
cmd(0x2A);
data(0x00);
data(0x01);
data(0x00);

if(_LCD_x==128)
{data(0x81);}
else
{data(0xA0);}

// set row
cmd(0x2B);
data(0x00);
data(0x01);
data(0x00);
data(0xA0);


cmd(0x2C);
  
int i=0;
for(i=0;i<20800;i++)
{
  data(_setBackColorRed);
  data(_setBackColorGreen);
  data(_setBackColorBlue);
}

//write data to ram
cmd(0x2C);

}


// Bresenham's algorithm - thx wikpedia
void drawLine(int16_t x0, int16_t y0,int16_t x1, int16_t y1)
{
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0);
    } else {
      drawPixel(x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


void rotate( byte _rotation){
cmd(0x36);
switch (_rotation) {
   case 0:
      data(MADCTL_MX | MADCTL_MY | MADCTL_RGB);
      _LCD_x=128;
      break;
   case 1:
      data(MADCTL_MY | MADCTL_MV | MADCTL_RGB);
      _LCD_x=157;
      break;
  case 2:
       data(MADCTL_RGB);
       _LCD_x=128;
       break;
  case 3:
      data(MADCTL_MX | MADCTL_MV | MADCTL_RGB);
      _LCD_x=157;
      break;
     }
  cmd(0x2C);
}

void println(char *characters)
{
 _x_pos=_fontSize;
// _y_pos= _fontSize;
  while (*characters)
  {
    character(*characters++);
  }
_y_pos=_y_pos + 8* _fontSize;
}

void print(char *characters)
{
  while (*characters)
  {
    character(*characters++);
  }
}

void character(char character)
{
  if(_x_pos < _fontSize)  {_x_pos =  _fontSize;}

for (uint8_t i=0;i<5 ;i++)
{
for (uint8_t j=0;j<8 ;j++)
{  
byte myByte=0;
myByte = pgm_read_byte(&(ASCII[(byte)character - 0x20][i]));

  if(((myByte >> j)  & 0b00000001) == 0b00000001) 

  {// draw font color
  drawFontPixel(_x_pos,_y_pos,_textColorRed,_textColorGreen,_textColorBlue,_fontSize);}
  else
  {//draw back color
  drawFontPixel(_x_pos,_y_pos,_setBackColorRed,_setBackColorGreen,_setBackColorBlue,_fontSize);}

_y_pos = _y_pos + _fontSize;
}
_y_pos = _y_pos - _fontSize*8;
_x_pos = _x_pos + _fontSize;

}
_x_pos = _x_pos + _fontSize;

if(_x_pos > _LCD_x)
  {
    _x_pos=1+_fontSize;
    _y_pos = _y_pos +_fontSize*8;
  }
}

void drawFontPixel(uint8_t x, uint8_t y, uint8_t red,uint8_t green,uint8_t blue,uint8_t pixelSize)
{
  setAddrWindow(x,y,x+pixelSize-1,y+pixelSize-1);
 for (uint8_t i=0;i<pixelSize*pixelSize ;i++)
 {
   data(red);
   data(green);
   data(blue);
 }
}

void setColor( uint8_t red, uint8_t green, uint8_t blue)
{
 _textColorRed=red;
 _textColorBlue=green;
 _textColorGreen=blue;
}

void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1,uint8_t y1)

{
  cmd(0x2A); // Column addr set
  data(0x00);
  data(x0);     // XSTART 
  data(0x00);
  data(x1);     // XEND

  cmd(0x2B); // Row addr set
  data(0x00);
  data(y0);     // YSTART
  data(0x00);
  data(y1);     // YEND

  cmd(0x2C); // write to RAM
}

void drawPixel(int16_t x, int16_t y)
{
  drawPixel(x,y, _textColorRed,_textColorGreen,_textColorBlue);
}

void drawPixel(int16_t x, int16_t y, uint8_t red,uint8_t green,uint8_t blue)
{

  setAddrWindow(x,y,x+1,y+1);
  data(red);
  data(green);
  data(blue);
}

void init_LCD(void)
{
SPI.begin();
SPI.setBitOrder(MSBFIRST);
bitSet(SPSR,0);
bitClear(SPCR,0);
bitClear(SPCR,1);
SPI.setDataMode(SPI_MODE0);
SPI.end();

pinMode(_CE,OUTPUT);
pinMode(_DATA,OUTPUT);
pinMode(_CLK,OUTPUT);

pinMode(13,OUTPUT);

  cmd(0x01);
  delay(120);  
  cmd(0x11);
  delay(500);
// data(0x13);
// data(0x20);
  cmd(0x29);
  delay(500);
    
// color mode 16bit  
cmd(0x3A);
data(0x06);

rotate(3);
}

void data (byte payload)
{
  write(payload,1);
}

void cmd (byte payload)
{
  write(payload,0);
}

void write (byte payload,byte dc)
{
    //select graphicsLCD
  //digitalWrite(_CE, LOW);
  bitClear(PORTB,1);
  //write dc bit
  if(dc==0)
{
  //digitalWrite(_DATA, LOW);
  bitClear(PORTB,3);
}  else {
    //digitalWrite(_DATA, HIGH);
      bitSet(PORTB,3);
} 
  //digitalWrite(_CLK, HIGH);
  bitSet(PORTB,5);
  //digitalWrite(_CLK, LOW);
  bitClear(PORTB,5);

  //write payload 8 bits
SPCR |= _BV(SPE);
//SPI.setBitOrder(MSBFIRST);

        SPDR = payload;                 // send the data
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        while(!(SPSR & (1<<SPIF)));  // wait until transmission is complete

        // if you have multiple slaves, this is where you want to switch
    
//SPI.transfer(payload);
SPCR &= ~_BV(SPE);
  //turn off graphicsLCD cs
  bitSet(PORTB,1);
}
