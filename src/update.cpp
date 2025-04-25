
// we include the h file so its accessable to other h files
#include "update.h"
// this also uses "" not the <> like the others "" denotes a local import and <> is from librarys

// these are our standard libraries we need
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>


#define UPDATE_SITE "https://github.com/Weissman-Foundry/electronics_room_lights/releases/latest/download/firmware.bin"
#ifndef WIFI_SSID
#define WIFI_SSID "SSID"
#define WIFI_PASS "PASSWORD"
#endif

#pragma message WIFI_SSID


const char *ssid = WIFI_SSID;
const char *pass = WIFI_PASS;

void wifi_setup(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    Serial.printf("Connecting to '%s'\n", ssid);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void update_started() {
    Serial.println("CALLBACK:  HTTP update process started");
  }
  
  void update_finished() {
    Serial.println("CALLBACK:  HTTP update process finished");
  }
  
  void update_progress(int cur, int total) {
    Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
  }
  
  void update_error(int err) {
    Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
  }
  
void wifi_loop(){
    httpUpdate.onStart(update_started);
    httpUpdate.onEnd(update_finished);
    httpUpdate.onProgress(update_progress);
    httpUpdate.onError(update_error);

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    String payload = UPDATE_SITE;
    int httpCode = 302;
    do{
      Serial.println(payload);
      http.begin(client,payload);
      httpCode = http.GET();
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if(httpCode == 302 || httpCode == 301){
        payload = http.getLocation();
      }
      http.end();
    }while(httpCode == 302 || httpCode == 301);

    if(httpCode == 200){
      t_httpUpdate_return ret = httpUpdate.update(client, payload);
    }
}
WiFiClient client;
