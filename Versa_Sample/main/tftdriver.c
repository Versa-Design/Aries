//******************************************************************************
// File: tftdriver.c
// Description: driver for the ILI9341 240x320 screen
// Written by: Juan Ramon Vadillo VERSA DESIGN S.L.
// Licencia: Creative Commons No Comercial (CC BY-NC)
//
// Este archivo está sujeto a la Licencia Creative Commons No Comercial (CC BY-NC).
// Esto significa que puedes compartir, copiar, modificar y distribuir este archivo
// siempre y cuando sea para uso personal y no comercial, y siempre que se proporcione
// atribución al autor original. No se permite el uso comercial de este archivo ni la
// creación de obras derivadas sin el consentimiento expreso del autor.
//
// Para más detalles sobre la Licencia Creative Commons No Comercial (CC BY-NC), puedes
// consultar: [https://creativecommons.org/licenses/by-nc/4.0/]
//******************************************************************************

//******************************************************************************
// INCLUDES

#include "global.h"
#include "pcbdefs.h"
#include "tftdriver.h"
#include "hwplatform.h"

#include "screen_backlight.h"

#define KEY_END     0x00

#define BL_MAX_PWM (1 << BACKLIGHT_PWM_RES)

//******************************************************************************
// VARIABLES

static const uint32_t portValueTable[256] =
{
  0x00000000,0x00000004,0x00000010,0x00000014,
  0x00010000,0x00010004,0x00010010,0x00010014,
  0x00020000,0x00020004,0x00020010,0x00020014,
  0x00030000,0x00030004,0x00030010,0x00030014,
  0x00000020,0x00000024,0x00000030,0x00000034,
  0x00010020,0x00010024,0x00010030,0x00010034,
  0x00020020,0x00020024,0x00020030,0x00020034,
  0x00030020,0x00030024,0x00030030,0x00030034,
  0x00040000,0x00040004,0x00040010,0x00040014,
  0x00050000,0x00050004,0x00050010,0x00050014,
  0x00060000,0x00060004,0x00060010,0x00060014,
  0x00070000,0x00070004,0x00070010,0x00070014,
  0x00040020,0x00040024,0x00040030,0x00040034,
  0x00050020,0x00050024,0x00050030,0x00050034,
  0x00060020,0x00060024,0x00060030,0x00060034,
  0x00070020,0x00070024,0x00070030,0x00070034,
  0x00080000,0x00080004,0x00080010,0x00080014,
  0x00090000,0x00090004,0x00090010,0x00090014,
  0x000A0000,0x000A0004,0x000A0010,0x000A0014,
  0x000B0000,0x000B0004,0x000B0010,0x000B0014,
  0x00080020,0x00080024,0x00080030,0x00080034,
  0x00090020,0x00090024,0x00090030,0x00090034,
  0x000A0020,0x000A0024,0x000A0030,0x000A0034,
  0x000B0020,0x000B0024,0x000B0030,0x000B0034,
  0x000C0000,0x000C0004,0x000C0010,0x000C0014,
  0x000D0000,0x000D0004,0x000D0010,0x000D0014,
  0x000E0000,0x000E0004,0x000E0010,0x000E0014,
  0x000F0000,0x000F0004,0x000F0010,0x000F0014,
  0x000C0020,0x000C0024,0x000C0030,0x000C0034,
  0x000D0020,0x000D0024,0x000D0030,0x000D0034,
  0x000E0020,0x000E0024,0x000E0030,0x000E0034,
  0x000F0020,0x000F0024,0x000F0030,0x000F0034,
  0x00200000,0x00200004,0x00200010,0x00200014,
  0x00210000,0x00210004,0x00210010,0x00210014,
  0x00220000,0x00220004,0x00220010,0x00220014,
  0x00230000,0x00230004,0x00230010,0x00230014,
  0x00200020,0x00200024,0x00200030,0x00200034,
  0x00210020,0x00210024,0x00210030,0x00210034,
  0x00220020,0x00220024,0x00220030,0x00220034,
  0x00230020,0x00230024,0x00230030,0x00230034,
  0x00240000,0x00240004,0x00240010,0x00240014,
  0x00250000,0x00250004,0x00250010,0x00250014,
  0x00260000,0x00260004,0x00260010,0x00260014,
  0x00270000,0x00270004,0x00270010,0x00270014,
  0x00240020,0x00240024,0x00240030,0x00240034,
  0x00250020,0x00250024,0x00250030,0x00250034,
  0x00260020,0x00260024,0x00260030,0x00260034,
  0x00270020,0x00270024,0x00270030,0x00270034,
  0x00280000,0x00280004,0x00280010,0x00280014,
  0x00290000,0x00290004,0x00290010,0x00290014,
  0x002A0000,0x002A0004,0x002A0010,0x002A0014,
  0x002B0000,0x002B0004,0x002B0010,0x002B0014,
  0x00280020,0x00280024,0x00280030,0x00280034,
  0x00290020,0x00290024,0x00290030,0x00290034,
  0x002A0020,0x002A0024,0x002A0030,0x002A0034,
  0x002B0020,0x002B0024,0x002B0030,0x002B0034,
  0x002C0000,0x002C0004,0x002C0010,0x002C0014,
  0x002D0000,0x002D0004,0x002D0010,0x002D0014,
  0x002E0000,0x002E0004,0x002E0010,0x002E0014,
  0x002F0000,0x002F0004,0x002F0010,0x002F0014,
  0x002C0020,0x002C0024,0x002C0030,0x002C0034,
  0x002D0020,0x002D0024,0x002D0030,0x002D0034,
  0x002E0020,0x002E0024,0x002E0030,0x002E0034,
  0x002F0020,0x002F0024,0x002F0030,0x002F0034
};

static const uint8_t initSeqMultiInno[] =
{
  0x3A, 1,0x05, 
  0x36, 1,0x00,   // Memory Access Control 
  0xB2, 5,0x05,0x05,0x00,0x33,0x33, // Frame rate
  0xB7, 1,0x35, 
  0xBB, 1,0x3F,    // Power setting
  0xC0, 1,0x2C, 
  0xC2, 1,0x01, 
  0xC3, 1,0x0F, 
  0xC4, 1,0x20, 
  0xC6, 1,0x11, 
  0xD0, 2,0xA4, 0xA1,
  0xE8, 1,0x03, 
  0xE9, 3,0x09, 0x09, 0x08, 
  0xE0, 14, 
    0xD0,0x05,0x09,0x09,0x08,0x14,0x28,0x33,0x3F,0x07,0x13,0x14,0x28,0x30,
  0xE1, 15, 
    0xD0,0x05,0x09,0x09,0x08,0x03,0x24,0x32,0x32,0x3B,0x38,0x14,0x13,0x28,0x2F,
  0x21, 0,  //Display inversion
  0x2A, 4, 0x00,0x00,0x00,0xEF,
  0x2B, 4, 0x00,0x00,0x01,0x3F,  
  KEY_END
};

static uint8_t tftid[3];
static uint8_t lcdDriverID[3];

// Back light PWM
static uint16_t blTarget = BL_MAX_PWM;
static volatile uint16_t blCurrent = 0;
static uint16_t blRate = 8;

//******************************************************************************
// FUNCTIONS

//******************************************************************************
static inline void ByteWrite(uint8_t pData)
//******************************************************************************
{
  uint32_t val = portValueTable[pData];
  GPIO.out_w1tc = GPIO_LCD_DATA_BUS_MASK;  // Clear the bits
  GPIO.out_w1ts = val;  // Set the bits
  TFT_WR_LO();
  TFT_WR_HI();
 }

//******************************************************************************
static void WriteReg8Bit(uint8_t b)
//******************************************************************************
{
  TFT_RS_LO(); 
  TFT_CS_LO(); 
  ByteWrite(b);
  TFT_CS_HI();
  TFT_RS_HI();  
}

//******************************************************************************
static void WriteDat8Bit(uint8_t b)
//******************************************************************************
{
  TFT_RS_HI();
  TFT_CS_LO(); 
  ByteWrite(b);
  TFT_CS_HI();  
}

//******************************************************************************
static void LCD_StartWriteOperation(void)
//******************************************************************************
{
  WriteReg8Bit(ILI9341_CMD_MEMORY_WRITE);
}

//******************************************************************************
static void LCD_WriteData(uint16_t w)
//******************************************************************************
{
  TFT_RS_HI();
  TFT_CS_LO(); 
  ByteWrite(w >> 8);
  ByteWrite(w & 0xFF);
  TFT_CS_HI();
}

//******************************************************************************
static void LCD_FillData(uint16_t w, uint32_t n)
//******************************************************************************
{
  LCD_StartWriteOperation();
  TFT_RS_HI();
  while (n--)
  {
    TFT_CS_LO(); 
    ByteWrite(w >> 8);
    ByteWrite(w & 0xFF);
    TFT_CS_HI();
  }
}

//******************************************************************************
static uint8_t ByteRead(void)
//******************************************************************************
{
  uint8_t pData;
  uint32_t portVal;
  TFT_RD_LO();
  pData = 0;
  portVal = GPIO.in;
  if (portVal & (1UL<<GPIO_LCD_D0)) pData |= 0x01;
  if (portVal & (1UL<<GPIO_LCD_D1)) pData |= 0x02;
  if (portVal & (1UL<<GPIO_LCD_D2)) pData |= 0x04;
  if (portVal & (1UL<<GPIO_LCD_D3)) pData |= 0x08;
  if (portVal & (1UL<<GPIO_LCD_D4)) pData |= 0x10;
  if (portVal & (1UL<<GPIO_LCD_D5)) pData |= 0x20;
  if (portVal & (1UL<<GPIO_LCD_D6)) pData |= 0x40;
  if (portVal & (1UL<<GPIO_LCD_D7)) pData |= 0x80;
  asm("nop");
  asm("nop");
  asm("nop");
  TFT_RD_HI();
  asm("nop");
  asm("nop");
  asm("nop");
  return pData;
}

//******************************************************************************
static void TFT_DataGPIODirOutput(void)
//******************************************************************************
{
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE; // disable interrupt
  io_conf.mode = GPIO_MODE_OUTPUT; //set as output mode
  io_conf.pin_bit_mask = GPIO_LCD_DATA_BUS_MASK;
  io_conf.pull_down_en = 0; //disable pull-down mode
  io_conf.pull_up_en = 0;   //disable pull-up mode
  gpio_config(&io_conf);    //configure GPIO with the given settings
}

//******************************************************************************
static void TFT_DataGPIODirInput(void)
//******************************************************************************
{
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE; // disable interrupt
  io_conf.mode = GPIO_MODE_INPUT; //set as input mode
  io_conf.pin_bit_mask = GPIO_LCD_DATA_BUS_MASK;
  io_conf.pull_down_en = 0; //disable pull-down mode
  io_conf.pull_up_en = 1;   //enable pull-up mode
  gpio_config(&io_conf);    //configure GPIO with the given settings
}

//******************************************************************************
static void write_reg_16bit(uint16_t w)
//******************************************************************************
{
  TFT_RS_HI();
  TFT_CS_LO(); 
  ByteWrite(w >> 8);
  ByteWrite(w & 0xFF);
  TFT_CS_HI();
  TFT_RS_HI();
}

//******************************************************************************
static void TFTSetActiveWindow(uint16_t  start_x,uint16_t start_y ,
                               uint16_t endx,uint16_t endy)
//******************************************************************************
{			   
  WriteReg8Bit(ILI9341_CMD_COLUMN_ADDRESS_SET); // Set Column Address
  WriteDat8Bit( (start_x&0x0100)>>8);
  WriteDat8Bit(  start_x&0xff      ); // Column Start address=00
  WriteDat8Bit( (endx   &0x0100)>>8   );
  WriteDat8Bit(  endx   &0xff         ); // Column End address =239

  WriteReg8Bit(ILI9341_CMD_PAGE_ADDRESS_SET); // Set Page Address
  WriteDat8Bit((start_y&0x0100)>>8);  
  WriteDat8Bit(start_y&0xff); // Page Start address=00
  WriteDat8Bit((endy&0x0100)>>8);
  WriteDat8Bit(endy&0xff); // Page End address =319
   
}

//******************************************************************************
static void TFT_GPIOInit(void)
//******************************************************************************
// Description: this function initializes the GPIOs for normal operation
{
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE; // disable interrupt
  io_conf.mode = GPIO_MODE_OUTPUT; //set as output mode
  io_conf.pin_bit_mask = GPIO_LCD_CTRL_BUS_MASK;
  io_conf.pull_down_en = 0; //disable pull-down mode
  io_conf.pull_up_en = 0;   //disable pull-up mode
  gpio_config(&io_conf);    //configure GPIO with the given settings
  TFT_CS_HI();
  TFT_RS_LO();
  TFT_RD_HI();
  TFT_WR_HI();
  TFT_DataGPIODirOutput();  
}

//******************************************************************************
static void TFT_ExecuteConfigSeq(uint8_t *seq)
//******************************************************************************
// Description: this function initializes the screen with a given configuration
// sequence
// Parameters: uint8_t *seq: sequence to initialize the TFT display
// Returns: nothig (Display controller initialized)
//******************************************************************************
{
  uint8_t n;
  while (*seq != KEY_END)
  {
    WriteReg8Bit(*seq++);  // Send the command
    n = *seq++;               // Get the number of parameters
    while (n-->0) WriteDat8Bit(*seq++); 
  }
}

//******************************************************************************
static void TFT_ReadDisplayID(void)
//******************************************************************************
// Description: this function reads the display id word
// Parameters: none
// Returns: nothing (tftid variable properly initialized)
//******************************************************************************
{
  TFT_RS_LO(); 
  TFT_CS_LO(); 
  ByteWrite(ILI9341_CMD_READ_DISP_ID);
  TFT_RS_HI();  
  TFT_DataGPIODirInput();
  ByteRead(); // Dummy read
  tftid[0] = ByteRead();
  tftid[1] = ByteRead();
  tftid[2] = ByteRead();
  TFT_CS_HI();
  TFT_DataGPIODirOutput();  
}

//******************************************************************************
static void TFT_ReadLCDDriverICID(void)
//******************************************************************************
// Description: this function reads the extended LCD Driver IC id word
// Parameters: none
// Returns: nothing (lcdDriverID variable properly initialized)
//******************************************************************************
{
  TFT_RS_LO(); 
  TFT_CS_LO(); 
  ByteWrite(ILI9341_CMD_READ_ID4);
  TFT_RS_HI();  
  TFT_DataGPIODirInput();
  ByteRead(); // Dummy read
  lcdDriverID[0] = ByteRead();
  lcdDriverID[1] = ByteRead();
  lcdDriverID[2] = ByteRead();
  TFT_CS_HI();
  TFT_DataGPIODirOutput();  
}

//******************************************************************************
void TFT_Init(void)
//******************************************************************************
// Description: this function initializes both the LCD pins and the 
//******************************************************************************
{
  TFT_GPIOInit();
  
  TFT_RESET_HI(); SysSleep(200);
  TFT_RESET_LO(); SysSleep(200);
  TFT_RESET_HI(); SysSleep(250);

  write_reg_16bit(ILI9341_CMD_SLEEP_OUT);    //Exit Sleep 
  TFT_CS_HI(); SysSleep(250);
  TFT_ReadDisplayID();
  TFT_ReadLCDDriverICID();
  
    TFT_ExecuteConfigSeq((uint8_t *)initSeqMultiInno);

  WriteReg8Bit(ILI9341_CMD_SLEEP_OUT);    //Exit Sleep 
  SysSleep(250);

  WriteReg8Bit(ILI9341_CMD_DISPLAY_ON);    //Display on 
  TFTSetActiveWindow(0,0,239,319);
  LCD_FillData(0, 320*240);

  BKL_Init(500);
}

//******************************************************************************
void LCD_DrawRectangle(uint16_t x,  uint16_t y, 
                       uint16_t sx, uint16_t sy, uint16_t col)
//******************************************************************************
// Description: draws a rectangle starting at x,y with dimensions sx and sy
//******************************************************************************
{
  uint32_t n;
  n = sx; n *= sy;
  TFTSetActiveWindow(x,y,x+sx-1,y+sy-1);
  LCD_StartWriteOperation();
  LCD_FillData(col,n);
}

//******************************************************************************
void PutPixelHiCol(uint16_t x, uint16_t y, uint16_t col)
//******************************************************************************
// Description: draws a pixel of a selected 565 color coding at the given screen 
// coordinates.
// Parameters:
//   uint16_t x, uint16_t y: screen coordinates
//   uint16_t col: color in 16bit per pixel
//******************************************************************************
{
  TFTSetActiveWindow(x,y,239,319);
  LCD_StartWriteOperation();
  LCD_WriteData(col);
}

//******************************************************************************
void TFT_SetBacklight(uint16_t pct)
//******************************************************************************
{
  uint32_t c;
  c = pct;
  c *= BL_MAX_PWM;
  c /= 100;
  blTarget = c;
}

//******************************************************************************
void TFT_BacklightManage(void)
//******************************************************************************
{
  uint16_t diff,inc;
  if (blTarget > blCurrent) 
    diff = blTarget - blCurrent;
  else
    diff = blCurrent - blTarget;
  if (diff == 0) { return;} 
  if (diff > 500) inc = blRate;
  else if (diff > 50) inc = blRate/4;
  else inc = blRate/8;
  if (inc == 0) inc = 1;
  if (blTarget > blCurrent) blCurrent += inc;
  else blCurrent -= inc;
  BKL_Set(blCurrent);
}