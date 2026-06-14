#include <Wire.h>
#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"

const byte MLX90640_address = 0x33;

#define TA_SHIFT 8

float mlx90640To[768];
paramsMLX90640 mlx90640;
#define byte8;

int max1;
float vari;

boolean isConnected()
{
  Wire.beginTransmission((uint8_t)MLX90640_address);
  if (Wire.endTransmission() != 0)
    return (false);
  return (true);
}

void setup() {
  Wire.begin();
  Wire.setClock(100000);

  Serial.begin(115200);

  while (!Serial);

  if (isConnected() == false)
  {
    Serial.println("MLX90640 not detected at default I2C address. Please check wiring. Freezing.");
    //while (1);
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

  Serial.println(max1);
}
