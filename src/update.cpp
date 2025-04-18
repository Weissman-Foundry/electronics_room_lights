
// we include the h file so its accessable to other h files
#include "update.h"
// this also uses "" not the <> like the others "" denotes a local import and <> is from librarys

// these are our standard libraries we need
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>


#define UPDATE_SITE "test"
#define UPDATE_PATH "test"
#ifndef WIFI_SSID
#define WIFI_SSID "SSID"
#define WIFI_PASS "PASSWORD"
#endif

const char *ssid = WIFI_SSID;
const char *pass = WIFI_PASS;

void wifi_setup(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
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
    t_httpUpdate_return ret = httpUpdate.update(client, UPDATE_SITE, 80, UPDATE_PATH, "optional current version string here");
}
WiFiClient client;
