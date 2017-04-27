
//AS3935 SCL = A5
//AS3935 SDA = A4
//AS3935 IRQ = D5
//AQM1602 SCL = A5
//AQM1602 SDA = A4
//USE 5V PWR

#include <ST7032.h> // LCD library
#include <Wire.h>
#include <FreqCounter.h>

#define AS3935_ADRS 0x00
#define LCD_ADRS 0x3E 

#define AFE_GB  0x1F  // ANALOG FRONT END GAIN BOOST = 12(Indoor) 0x00 to 0x1F
#define NF_LEV  0x02  // NOIS FLOOR LEVEL 0x00 to 0x07
#define WDTH    0x02  // WATCH DOG THRESHOLD 0x00 to 0x0F

ST7032 lcd;

String LCD_STRING;
byte reg0,reg1,reg2,reg3,reg4,reg5,reg6,reg7,reg8,reg3A,reg3B,reg3C,reg3D,regDUMMY;
unsigned long enargy;
unsigned int distance;
long int freq;
long int OLD_BUFFER = 10000;
long int NOW_BUFFER = 0;
int C;
long int F;
byte CAP_RESULT;

// Thunder mark character
byte Lightning[8] = {
	0b00010,
	0b00100,
	0b01100,
	0b11111,
	0b00110,
	0b00100,
	0b01000,
	0b10000
};

void ByteWrite(byte reg, byte data)
{
  Wire.beginTransmission(AS3935_ADRS);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
  delay(50);
}

byte ByteRead(byte reg)
{
  byte data = 0;
  Wire.beginTransmission(AS3935_ADRS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(AS3935_ADRS,1);
  data = Wire.read();      // Receive 1 byte
  return data;
}

void resistorRead(void)
{
  Wire.beginTransmission(AS3935_ADRS);
  Wire.write(0);
  Wire.endTransmission(false);
  Wire.requestFrom(AS3935_ADRS,9);
  reg0 = Wire.read();
  reg1 = Wire.read();
  reg2 = Wire.read();
  reg3 = Wire.read();
  reg4 = Wire.read();
  reg5 = Wire.read();
  reg6 = Wire.read();
  reg7 = Wire.read();
  reg8 = Wire.read();
  Wire.beginTransmission(AS3935_ADRS);
  Wire.write(0x3A);
  Wire.endTransmission(false);
  Wire.requestFrom(AS3935_ADRS,4);
  reg3A = Wire.read();
  reg3B = Wire.read();
  reg3C = Wire.read();
  reg3D = Wire.read();
  
}

void setup()
{
  pinMode(2,INPUT);
  
  Wire.begin();
  Serial.begin(9600);          // start serial communication at 9600bps
  Serial.println("READY");   // print the reading
  // create a new character
  lcd.createChar(5, Lightning);
  
  INIT_LCD();
  DISP_OPENNING();
  INIT_AS3935();
}

void loop()
{
  writeCommand(0x01); // Clear Display  
  while(1)
  {
  if (digitalRead(5)== HIGH) INT_DETECTS(); 
  }
}

void INT_DETECTS(void)
{
  digitalWrite(4, HIGH);  // LED ON
  byte reg3buffer;
  delay(4);
  resistorRead();
  reg3buffer = reg3 & 0x0F;
  if (reg3buffer == 0x01) INT_NH();
  if (reg3buffer == 0x04) INT_D();
  if (reg3buffer == 0x08) INT_L();
  digitalWrite(4, LOW);  // LED OFF
}

void INT_NH(void)  //noise level too high
{
  writeCommand(0x01); // Clear Display  
  LCD_STRING = "Nois Level High ";
  LCD_DISP_16_1();
  LCD_STRING = "el High ";
  LCD_DISP_16_2();
  delay(700);
  writeCommand(0x01); // Clear Display  
  LCD_STRING = "Watching........ ";
  LCD_DISP_16_1();
}

void INT_D(void)  //disturber detected
{
  writeCommand(0x01); // Clear Display  
  LCD_STRING = "Disturbe";
  LCD_DISP_16_1();
  LCD_STRING = "r DETect";
  LCD_DISP_16_2();
  delay(1500);
  writeCommand(0x01); // Clear Display  
  LCD_STRING = "Watching........";
  LCD_DISP_16_1();
}

void INT_L(void)  //lightning interrupt
{
  writeCommand(0x01); // Clear Display  
  enargy = (((reg6 & 0x0F) * 65536)+ (reg5 * 256)+ (reg4)) & 0x0FFFFF;
  distance = (reg7 );
  lcd.setCursor(0, 0);
  lcd.write(5);
  LCD_STRING = "E=" + String(enargy) ;
  lcd.setCursor(1, 0);
  LCD_DISP_16_1();
  LCD_STRING = "D=" + String(distance) + "km";

  if(reg7 == 0x01)  LCD_STRING = "E=" + String(enargy) + " OvrHed";
  if(reg7 == 0x3F)  LCD_STRING = "E=" + String(enargy) + " OutRng";
  LCD_DISP_16_2();
  serialDisplay();
  delay(5000);
  writeCommand(0x01); // Clear Display  
  LCD_STRING = "Watching........";
  LCD_DISP_16_1();
}

void INIT_AS3935(void)
{
  ByteWrite(0x3C,0x96);
  ByteWrite(0x3D,0x96);
  ByteWrite(0x00,(AFE_GB << 1));  // SET ANALOG FRONT END GAIN BOOST
  ByteWrite(0x01,((NF_LEV << 4) | WDTH));
  ByteWrite(0x03,0x00);           // FRQ DIV RATIO = 1/16
  CALIB_LCO();
}

void CALIB_LCO(void)
{
  writeCommand(0x01); // Clear Display  
  delay(20);
  LCD_STRING = "NOW CALIBRATION ";
  LCD_DISP_16_1();
  LCD_STRING = "C=000pF F=500000";
  LCD_DISP_16_2();
  FREQ_COUNT();    //DUMMY
  for ( byte b = 0; b < 0x10 ; b++)
  {
    ByteWrite(0x08,(0x80 | b));
    delay(50);
    FREQ_COUNT();
    NOW_BUFFER = abs(freq - 3125);
    if(OLD_BUFFER > NOW_BUFFER) CAP_RESULT = b;
    OLD_BUFFER = NOW_BUFFER;
    Serial.print("CAP = ");
    Serial.print(b,DEC);
    Serial.print(" freq = ");
    Serial.println((freq * 16 * 10 ),DEC );
    LCD_STRING = String(b * 8);
    writeCommand(0x40+0x82);
    for(int i = 0; i < 3; i++)
    {
      writeData(LCD_STRING[i]);
    }
    LCD_STRING = String(freq * 16 * 10);
    writeCommand(0x40+0x8A);
    for(int i = 0; i < 7 ; i++)
    {
      writeData(LCD_STRING[i]);
    }
    delay(300);
  }
  writeCommand(0x01); // Clear Display 
  Serial.print("CAP_RESULT=");
  Serial.print(CAP_RESULT);
  Serial.print("   ");
  Serial.print(CAP_RESULT * 8);
  Serial.println("pF");
  ByteWrite(0x08,(0x80 | CAP_RESULT));
  delay(100);
  FREQ_COUNT();
  LCD_STRING = "CALIBRATION DONE";
  LCD_DISP_16_1();
  LCD_STRING = "pF 5000000Hz    ";
  LCD_DISP_16_2();
  LCD_STRING = String(CAP_RESULT * 8); 
  writeCommand(0x40+0x80);
  for (int i = 0; i < 3; i++)
  {
    writeData(LCD_STRING[i]);
  }
  LCD_STRING = String(freq * 16 * 10);
  writeCommand(0x40+0x87);
  for (int i = 0; i < 7; i++)
  {
    writeData(LCD_STRING[i]);
  }
  ByteWrite(0x08,CAP_RESULT);
  delay(3000);
}

void  FREQ_COUNT(void)
{
    FreqCounter::f_comp = 10;
    FreqCounter::start(100);
    while (FreqCounter::f_ready == 0);
    freq = FreqCounter::f_freq;
}  

void DISP_OPENNING(void)
{
  LCD_STRING = "Lightning Sensor";
  LCD_DISP_16_1();
  writeCommand(0x40+0x80);
  LCD_STRING = "   AS3935 DEMO  ";
  LCD_DISP_16_2();
  delay(2000);
}
  
//Write Data
void writeData(byte t_data)
{
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x40);
  Wire.write(t_data);
  Wire.endTransmission();
delay(1);
}
//Write Command
void writeCommand(byte t_command)
{
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x00);
  Wire.write(t_command);
  Wire.endTransmission();
delay(10);
}

//Initialize LCD
void INIT_LCD() 
{
    lcd.begin(8, 2);      // LCD range
    lcd.setContrast(30);  // Contrast setting 
    lcd.setCursor(0, 0);  // Cursor position
}

void LCD_DISP_16_1(void)
{
  for(int i = 0; i < 16; i++)
  {
    writeData(LCD_STRING[i]);
  }
}

void LCD_DISP_16_2(void)
{
  writeCommand(0x40+0x80);
  for(int i = 0; i < 16; i++)
  {
    writeData(LCD_STRING[i]);
  }
}


void serialDisplay(void)
{
  Serial.print(LCD_STRING); 
  Serial.print(" reg0=");
  Serial.print(reg0,HEX);
  Serial.print(" reg1=");
  Serial.print(reg1,HEX);
  Serial.print(" reg2=");
  Serial.print(reg2,HEX);
  Serial.print(" reg3=");
  Serial.print(reg3,HEX);
  Serial.print(" reg4=");
  Serial.print(reg4,HEX);
  Serial.print(" reg5=");
  Serial.print(reg5,HEX);
  Serial.print(" reg6=");
  Serial.print(reg6,HEX);
  Serial.print(" reg7=");
  Serial.print(reg7,HEX);
  Serial.print(" reg8=");
  Serial.println(reg8,HEX);
}


