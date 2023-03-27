#include <xc.h>
#include "I2C_LCD.h"
 
unsigned char RS, BackLight_State = LCD_BACKLIGHT;
unsigned char i2c_add;
 
//---------------[ I2C Routines ]-------------------
//--------------------------------------------------
void I2C_Master_Init()
{      
//     SSPCON  = 0b00101000; //0x28
////    SSPCON1 = 0x00;
////    SSPADD = 19; //100 KHz
////    SSPSTAT = 0b10000000;
//    
//        // Set SSPCON1 for I2C Master mode
//    SSPCON1bits.SSPM = 0b1000; // I2C Master mode, clock = Fosc/(4*(SSPADD+1))
//    SSPCON1bits.SSPEN = 1; // Enable SSP module
//
//    // Set SSPADD for desired I2C clock rate
//    SSPADD = 19;
//
//    // Set SSPSTAT for I2C mode
//    SSPSTATbits.SMP = 0; // Slew rate control disabled
//    SSPSTATbits.CKE = 0; // Enable SMBus specific inputs
    
//    SSPSTATbits.SMP = 0;
//    SSPSTATbits.CKE = 0;
//    SSPSTATbits.DA = 1;
//    SSPSTATbits.RW = 0;
//    
//    SSPCONbits.WCOL = 0;
//    SSPCONbits.SSPOV = 0;
//    SSPCONbits.SSPEN = 1;
//    SSPCONbits.CKP = 1;
//    SSPCONbits.SSPM3 = 1;
//    SSPCONbits.SSPM2 = 0;
//    SSPCONbits.SSPM1 = 1;
//    SSPCONbits.SSPM0 = 1;
    
    SSPCON = 0x28; // SSPEN: Master Synchronous Serial Port Enable bit. I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
    SSPSTAT = 0x80; // Slew rate control is disabled for Standard Speed mode (100 kHz and 1 MHz)
    SSPCONbits.SSPEN = 0; // SEN: Start Condition Enable bit. Start condition Idle 
    PIR1bits.SSPIF = 0; // SSPIF: Master Synchronous Serial Port Interrupt Flag bit. Waiting to transmit/receive
    
    SSPADD = 19;
    
    
    SCL_D = 1;
    SDA_D = 1;
}
 
void I2C_Master_Wait()
{
  while (SSPSTATbits.P == 1 && SSPSTATbits.P == 1);
    //__delay_ms(20);
}
 
void I2C_Master_Start()
{
PIR1bits.SSPIF = 0; //clear flag
while (SSPSTATbits.BF ); // wait for idle condition
SSPCONbits.SSPEN = 1; // initiate START condition
SSPSTATbits.S = 1;
while (!PIR1bits.SSPIF) ; // wait for a flag to be set
PIR1bits.SSPIF = 0; // clear flag
}
 
void I2C_Master_Stop()
{
PIR1bits.SSPIF = 0; // clear flag
while ( SSPSTATbits.BF ) ; // wait for idle condition
SSPSTATbits.P = 1; // Initiate STOP condition
while (!PIR1bits.SSPIF) ; // wait for a flag to be set
PIR1bits.SSPIF = 0; // clear flag
}

 
unsigned char I2C_Master_Write(unsigned char data)
{
  //I2C_Master_Wait();
//  SSPBUF = data;
//  while(SSPSTATbits.BF); // Wait Until Completion;
//    
//  while(SSPSTATbits.BF);//wait for idle
//  SSPBUF = data;
//  while(!PIR1bits.SSPIF); // Wait Until Completion
//  SSPIF = 0;
//
//    return 1;
    
 PIR1bits.SSPIF = 0; // clear interrupt
while ( SSPSTATbits.BF ) ; // wait for idle condition
SSPBUF = data; // Load SSPBUF with i2cWriteData (the value to be transmitted)
while (!PIR1bits.SSPIF) ; // wait for a flag to be set
PIR1bits.SSPIF = 0; // clear flag
return (1); // function returns '1' if transmission is acknowledged
}
 

//======================================================
 
//---------------[ LCD Routines ]----------------
//-----------------------------------------------
 
void LCD_Init(unsigned char I2C_Add)
{
  i2c_add = I2C_Add;
  IO_Expander_Write(0x00);
  __delay_ms(30);
  LCD_CMD(0x03);
  __delay_ms(5);
  LCD_CMD(0x03);
  __delay_ms(5);
  LCD_CMD(0x03);
  __delay_ms(5);
  LCD_CMD(LCD_RETURN_HOME);
  __delay_ms(5);
  LCD_CMD(0x20 | (LCD_TYPE << 2));
  __delay_ms(50);
  LCD_CMD(LCD_TURN_ON);
  __delay_ms(50);
  LCD_CMD(LCD_CLEAR);
  __delay_ms(50);
  LCD_CMD(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
  __delay_ms(50);
}
 
void IO_Expander_Write(unsigned char Data)
{
  I2C_Master_Start();
  I2C_Master_Write(i2c_add);
  I2C_Master_Write(Data | BackLight_State);
  I2C_Master_Stop();
}
 
void LCD_Write_4Bit(unsigned char Nibble)
{
  // Get The RS Value To LSB OF Data
  Nibble |= RS;
  IO_Expander_Write(Nibble | 0x04);
  IO_Expander_Write(Nibble & 0xFB);
  __delay_us(50);
}
 
void LCD_CMD(unsigned char CMD)
{
  RS = 0; // Command Register Select
  LCD_Write_4Bit(CMD & 0xF0);
  LCD_Write_4Bit((CMD << 4) & 0xF0);
}
 
void LCD_Write_Char(char Data)
{
  RS = 1; // Data Register Select
  LCD_Write_4Bit(Data & 0xF0);
  LCD_Write_4Bit((Data << 4) & 0xF0);
}
 
void LCD_Write_String(char* Str)
{
  for(int i=0; Str[i]!='\0'; i++)
    LCD_Write_Char(Str[i]);
}
 
void LCD_Set_Cursor(unsigned char ROW, unsigned char COL)
{
  switch(ROW)
  {
    case 2:
      LCD_CMD(0xC0 + COL-1);
      break;
    case 3:
      LCD_CMD(0x94 + COL-1);
      break;
    case 4:
      LCD_CMD(0xD4 + COL-1);
      break;
    // Case 1
    default:
      LCD_CMD(0x80 + COL-1);
  }
}
 
void Backlight()
{
  BackLight_State = LCD_BACKLIGHT;
  IO_Expander_Write(0);
}
 
void noBacklight()
{
  BackLight_State = LCD_NOBACKLIGHT;
  IO_Expander_Write(0);
}
 
void LCD_SL()
{
  LCD_CMD(0x18);
  __delay_us(40);
}
 
void LCD_SR()
{
  LCD_CMD(0x1C);
  __delay_us(40);
}
 
void LCD_Clear()
{
  LCD_CMD(0x01);
  __delay_us(40);
}



