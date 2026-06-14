#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   24
#define LOGO_WIDTH    64

#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"

const byte MLX90640_address = 0x33;

#define TA_SHIFT 8

float mlx90640To[768];
paramsMLX90640 mlx90640;
#define byte8;
long stopTime;
long startTime;
long currentTime;
long intervalTime;
long previousTime = 1000;
int delta;
int adin;
int adout;
int vari;
int max1;
int minipid;
int Ben;
int Amm;
int TOL;
int NO2;
int C2H4;
int PTFE;
int buzzpin = 32;
int ledpin = 25;
int analogPin = 34;
int pid_value = 0;
int pid_value1 = 0;
int pid_value2 = 0;
int pid_value3 = 0;
int pid_value4 = 0;
int pid_value5 = 0;
int pid_value6 = 0;
int pid_value7 = 0;
int pid_value8 = 0;
int pid_value9 = 0;
int pid_value10 = 0;

int pid_value11 = 0;
int pid_value12 = 0;
int pid_value13 = 0;
int pid_value14 = 0;
int pid_value15 = 0;
int pid_value16 = 0;
int pid_value17 = 0;
int pid_value18 = 0;
int pid_value19 = 0;
int pid_value20 = 0;

int pid_value21 = 0;
int pid_value22 = 0;
int pid_value23 = 0;
int pid_value24 = 0;
int pid_value25 = 0;
int pid_value26 = 0;
int pid_value27 = 0;
int pid_value28 = 0;
int pid_value29 = 0;
int pid_value30 = 0;

boolean isConnected()
{
  Wire.beginTransmission((uint8_t)MLX90640_address);
  if (Wire.endTransmission() != 0)
    return (false);
  return (true);
}

void setup() {
  startTime = millis();
  pinMode(analogPin, INPUT);
  pinMode(buzzpin, OUTPUT);
  pinMode(ledpin, OUTPUT);

  Wire.begin();
  Wire.setClock(400000);

  Serial.begin(115200);

  while (!Serial);

  if (isConnected() == false)
  {
    Serial.println("MLX90640 not detected at default I2C address. Please check wiring. Freezing.");
    while (1);
  }

  int status;
  uint16_t eeMLX90640[832];
  status = MLX90640_DumpEE(MLX90640_address, eeMLX90640);
  if (status != 0)
    Serial.println("Failed to load system parameters");

  status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);
  if (status != 0)
    Serial.println("Parameter extraction failed");

  MLX90640_I2CWrite(0x33, 0x800D, 6401);

  MLX90640_SetRefreshRate(MLX90640_address, 0x03);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(2000);

  display.clearDisplay();
}




void loop() {
  
  for (byte x = 0 ; x < 2 ; x++)
  {
    uint16_t mlx90640Frame[834];
    int status = MLX90640_GetFrameData(MLX90640_address, mlx90640Frame);

    float vdd = MLX90640_GetVdd(mlx90640Frame, &mlx90640);
    float Ta = MLX90640_GetTa(mlx90640Frame, &mlx90640);

    float tr = Ta - TA_SHIFT;
    float emissivity = 0.95;

    MLX90640_CalculateTo(mlx90640Frame, &mlx90640, emissivity, tr, mlx90640To);
  }
  

  max1 = 0;
  for (int x = 0 ; x < 768 ; x++)
  {
    vari = int(mlx90640To[x]);
    if (max1 < vari) {
      max1 = vari;
    }
  }
  unsigned char logo_bmp[192];
  for (int x = 0 ; x < 768 ; x += 4)
  {
    bool m[8];
    m[0] = int(mlx90640To[x] / 30);
    m[1] = int(mlx90640To[x] / 30);
    m[2] = int(mlx90640To[x + 1] / 30);
    m[3] = int(mlx90640To[x + 1] / 30);
    m[4] = int(mlx90640To[x + 2] / 30);
    m[5] = int(mlx90640To[x + 2] / 30);
    m[6] = int(mlx90640To[x + 3] / 30);
    m[7] = int(mlx90640To[x + 3] / 30);
    unsigned char c = 0;
    for (int i = 0; i < 8; ++i)
      if (m[i])
        c |= 1 << i;
    int x1 = int(x / 4);
    logo_bmp[x1] = c;
  }

  
  pid_value1 = analogRead(analogPin);
  pid_value2 = analogRead(analogPin);
  pid_value3 = analogRead(analogPin);
  pid_value4 = analogRead(analogPin);
  pid_value5 = analogRead(analogPin);
  pid_value6 = analogRead(analogPin);
  pid_value7 = analogRead(analogPin);
  pid_value9 = analogRead(analogPin);
  pid_value10 = analogRead(analogPin);
  pid_value11 = analogRead(analogPin);
  pid_value12 = analogRead(analogPin);
  pid_value13 = analogRead(analogPin);
  pid_value14 = analogRead(analogPin);
  pid_value15 = analogRead(analogPin);
  pid_value16 = analogRead(analogPin);
  pid_value17 = analogRead(analogPin);
  pid_value18 = analogRead(analogPin);
  pid_value19 = analogRead(analogPin);
  pid_value20 = analogRead(analogPin);
  pid_value21 = analogRead(analogPin);
  pid_value22 = analogRead(analogPin);
  pid_value23 = analogRead(analogPin);
  pid_value24 = analogRead(analogPin);
  pid_value25 = analogRead(analogPin);
  pid_value26 = analogRead(analogPin);
  pid_value27 = analogRead(analogPin);
  pid_value28 = analogRead(analogPin);
  pid_value29 = analogRead(analogPin);
  pid_value30 = analogRead(analogPin);

  pid_value = (pid_value1 + pid_value2 + pid_value3 + pid_value4 + pid_value5 + pid_value6 + pid_value7 + pid_value8 + pid_value9 + pid_value10 + pid_value11 + pid_value12 + pid_value13 + pid_value14 + pid_value15 + pid_value16 + pid_value17 + pid_value18 + pid_value19 + pid_value20 + pid_value21 + pid_value22 + pid_value23 + pid_value24 + pid_value25 + pid_value26 + pid_value27 + pid_value28 + pid_value29 + pid_value30) / 30;

//  //count to AD620 out (pid_value*3.3)/4095
//  adout = (pid_value + 158) * 0.000805;
//  //AD620 out to AD620 in ADOUT*GAIN GAIN=0.09
//  adin = adout * 0.09 * 0.5 * 1000;
//  //A620 IN to minipid ADin*2
//  minipid = adin * 2;
//  //baseline kept at 55mV (ZERO AIR)
//  delta = minipid - 55;
  //ppm based on RF (delta/sensitivity)*RF
//  Ben = round((delta / 0.4) * 0.5);
//  Amm = round((delta / 0.4) * 8.5);
//  NO2 = round((delta / 0.4) * 13);
//  PTFE = round((delta / 0.4) * 15);
//  TOL = round((delta / 0.4) * 0.56);
//  C2H4 = round((delta / 0.4) * 50);
  minipid = (pid_value + 158) * 0.8050 * 0.09 * 0.5 * 2;
  if (minipid > 60 || max1 > 42)
  {
    digitalWrite(ledpin, HIGH);
    digitalWrite(buzzpin, HIGH);
  }
  else {
    digitalWrite(ledpin, LOW);
    digitalWrite(buzzpin, LOW);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 0);
  display.println(max1);
  display.setCursor(85, 0);
  display.println((char)247);
  display.setCursor(95, 0);
  display.println('C');
  display.setCursor(0, 0);
  display.println((pid_value));
  display.println((pid_value + 158) * 0.8050 * 0.09 * 0.5 * 2);
  display.println((pid_value + 158) * 0.8050 * 0.09 * 0.5);
  display.println((pid_value + 158) * 0.000805);
  display.display();

  
}
