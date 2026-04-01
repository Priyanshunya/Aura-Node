#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct struct_message {
  int msgType; 
  float lat;
  float lng;
  float maxGForce;
} struct_message;

struct_message sosPayload;
esp_now_peer_info_t peerInfo;

float G_FORCE_CRASH_THRESHOLD = 3.8; 
float G_FORCE_WARNING_THRESHOLD = 2.0;

unsigned long impactStartTime = 0;
bool potentialCrash = false;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // Serial.print("send status: ");
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "ok" : "fail");
}

void setup() {
  Serial.begin(115200);
  
  if (!mpu.begin()) {
    Serial.println("mpu error");
    while (1) { delay(10); }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); 
  
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("esp now fail");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false; 
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("peer fail");
    return;
  }
  Serial.println("ready");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // magnitude vector math
  float x2 = pow(a.acceleration.x, 2);
  float y2 = pow(a.acceleration.y, 2);
  float z2 = pow(a.acceleration.z - 9.81, 2);
  float magnitude = sqrt(x2 + y2 + z2) / 9.81; 


  if (magnitude > G_FORCE_CRASH_THRESHOLD) {
    if (!potentialCrash) {
      potentialCrash = true;
      impactStartTime = millis();
    } else {
      if (millis() - impactStartTime > 25) { // 25ms filter
        triggerGoldenHourSOS(magnitude);
        potentialCrash = false; 
        delay(5000); 
      }
    }
  } else {
    potentialCrash = false; 
  }

  if (magnitude > G_FORCE_WARNING_THRESHOLD && magnitude < G_FORCE_CRASH_THRESHOLD) {
     broadcastFogWarning();
     delay(1000); 
  }

  delay(10); 
}

void triggerGoldenHourSOS(float peakG) {
  Serial.println("CRASH DETECTED");
  
  sosPayload.msgType = 2;
  sosPayload.maxGForce = peakG;
  
  // Sir I will integrate NEO-6M gps module later, hardcoding coordinates for demo
  sosPayload.lat = 28.6139; 
  sosPayload.lng = 77.2090;

  esp_now_send(broadcastAddress, (uint8_t *) &sosPayload, sizeof(sosPayload));
}

void broadcastFogWarning() {
  sosPayload.msgType = 1;
  esp_now_send(broadcastAddress, (uint8_t *) &sosPayload, sizeof(sosPayload));
}
