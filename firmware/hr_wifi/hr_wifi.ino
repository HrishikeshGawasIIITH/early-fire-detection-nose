#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Wire.h>
#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   24
#define LOGO_WIDTH    64
int minipid;
int vari;
int max1;
int max2;
int max3;
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

long startTimet;
long previousTimet;
int difference;
const byte MLX90640_address = 0x33;

#define TA_SHIFT 8

float mlx90640To[768];
paramsMLX90640 mlx90640;

// TODO: set your WiFi credentials before flashing
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <style>
    body {
      min-width: 310px;
      max-width: 800px;
      height: 400px;
      margin: 0 auto;
    }
    h2 {
      font-family: Arial;
      font-size: 2.5rem;
      text-align: center;
    }
    p {
      font-family: Arial;
      font-size: 2.0rem;
      text-align: center;
    }
  </style>
</head>
<body>
  <h2>ESP32 Data Server</h2>
  <div id="chart-volt" class="container"></div>
  <p>
    <span class="mlx-labels">Temp1</span> 
    <span id="temp1">%TEMP1%</span>
    <sup class="units">deg;C</sup>
  </p>
  <p>
    <span class="mlx-labels">Temp2</span> 
    <span id="temp2">%TEMP2%</span>
    <sup class="units">deg;C</sup>
  </p>
  <p>
    <span class="mlx-labels">Temp3</span> 
    <span id="temp3">%TEMP3%</span>
    <sup class="units">deg;C</sup>
  </p>
</body>
<script>
var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-volt' },
  title: { text: 'MINIPID 2' },
  series: [{
    showInLegend: false,
    data: []
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#059e8a' }
  },
  xAxis: {type: 'datetime',
    dateTimeLabelFormats: { second: '%H:%M:%S' }
  },
  yAxis: {
    title: { text: 'Voltage' }
  },
  credits: { enabled: false }
});
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var x = (new Date()).getTime(),
          y = parseFloat(this.responseText);
      //console.log(this.responseText);
      if(chartT.series[0].data.length > 4000) {
        chartT.series[0].addPoint([x, y], true, true, true);
      } else {
        chartT.series[0].addPoint([x, y], true, false, true);
      }
    }
  };
  xhttp.open("GET", "/minipid", true);
  xhttp.send();
}, 500 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temp1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temp1", true);
  xhttp.send();
}, 500 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temp2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temp2", true);
  xhttp.send();
}, 500 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temp3").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temp3", true);
  xhttp.send();
}, 500 ) ;

</script>
</html>)rawliteral";


String processor(const String& var) {
  if (var == "TEMP1") {
    return String(max1);
  } else if (var == "TEMP2") {
    return String(max2);
  } else if (var == "TEMP3") {
    return String(max3);
  }
  return String();
}

boolean isConnected()
{
  Wire.beginTransmission((uint8_t)MLX90640_address);
  if (Wire.endTransmission() != 0)
    return (false); //Sensor did not ACK
  return (true);
}

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(buzzpin, OUTPUT);
  pinMode(ledpin, OUTPUT);
  Wire.begin();
  Wire.setClock(400000);

  Serial.begin(115200);

  while (!Serial);

  if (isConnected() == false)
  {
    Serial.println("MLX90640 not detected!");
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

  MLX90640_SetRefreshRate(MLX90640_address, 0x02);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/minipid", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String((pid_value + 158) * 0.8050 * 0.09 * 0.5 * 2).c_str());
  });
  server.on("/temp2", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(max2).c_str());
  });
  server.on("/temp3", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(max3).c_str());
  });
  server.on("/temp1", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(max1).c_str());
  });

  server.begin();

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
  long startTime = millis();
  }
  long stopTime = millis();
  max1 = 0;
  for (int x = 0 ; x < 768 ; x++)
  {
    vari = int(mlx90640To[x]);
    if (max1 < vari) {
      max1 = vari;
    }
  }
  max2 = 0;
  for (int x = 0 ; x < 768 ; x++)
  {
    vari = int(mlx90640To[x]);
    if (max2 < vari && vari < max1 ) {
      max2 = vari;
    }
  }
  max3 = 0;
  for (int x = 0 ; x < 768 ; x++)
  {
    vari = int(mlx90640To[x]);
    if (max3 < vari && vari < max2 ) {
      max3 = vari;
    }
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
 /* startTimet = millis();
  difference=startTimet-previousTimet;
  previousTimet = startTimet;
  Serial.print("total");
  Serial.print("\t");
  Serial.println(difference);*/
}
