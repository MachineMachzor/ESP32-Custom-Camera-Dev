#include "WifiCam.hpp"
#include <WiFi.h>

static const char* WIFI_SSID = "NETGEAR26";
static const char* WIFI_PASS = "melodicpanda708";

esp32cam::Resolution initialResolution;

WebServer server(80);

static auto hiRes = esp32cam::Resolution::find(640,480);
// static auto loRes = esp32cam::Resolution::find(640,480);



void handleBmp() {
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }

  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(), static_cast<int>(frame->size()));

  // if (!frame.toBmp()) {
  //   Serial.println("CONVERT FAIL");
  //   server.send(503, "", "");
  //   return;
  // }

  // Serial.printf("CONVERT OK %dx%d %db\n", frame->getWidth(), frame->getHeight(), static_cast<int>(frame->size()));

  server.setContentLength(frame->size());
  server.send(200, "image/bmp");

  WiFiClient client = server.client();
  frame->writeTo(client);

}

void serveJpg() {
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }

  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(), static_cast<int>(frame->size()));
  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");

  WiFiClient client = server.client();
  frame->writeTo(client);

}

// void handleJpgLo() {
//   if(!esp32cam::Camera.changeResolution(loRes)) {
//     Serial.println("SET-LO-RES FAIL");
//   }
//   serveJpg();
// }

void handleJpgHi() {
  if(!esp32cam::Camera.changeResolution(hiRes)) {
    Serial.println("SET-HI-RES FAIL");
  }
  serveJpg();
}

void handleJpg() {
  server.sendHeader("Location", "/cam-hi.jpg");
  server.send(302, "", "");
}

void handleMjpeg() {
  if(!esp32cam::Camera.changeResolution(hiRes)) {
    Serial.println("SET-HI-RES FAIL Mjpeg");
  }

  Serial.println("STREAM BEGIN");
  WiFiClient client = server.client();
  auto startTime = millis();
  int res = esp32cam::Camera.streamMjpeg(client);
  if (res <= 0) {
    Serial.printf("STREAM ERROR %d\n", res);
    return;
  }
  auto duration = millis() - startTime;
  Serial.printf("STREAM END %dfrm %0.2ffps\n", res, 1000.0 * res / duration);
}

void
setup() {
  Serial.begin(115200);
  Serial.println();
  // {
  //   using namespace esp32cam;
  //   Config cfg;
  //   cfg.setPins(pins::AiThinker);
  //   cfg.setResolution(hiRes);
  //   cfg.setBufferCount(2);
  //   cfg.setJpeg(80); //0 = worst, 100 = best, pixel format to jpeg

  //   bool ok = Camera.begin(cfg);
  //   Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  // }
  esp32cam::setLogger(Serial);
  delay(1000);

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi failure %d\n", WiFi.status());
    delay(5000);
    ESP.restart();
  }
  Serial.println("WiFi connected");
  delay(1000);

  {
    using namespace esp32cam;

    initialResolution = Resolution::find(1024, 768);

    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(initialResolution);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    if (!ok) {
      Serial.println("camera initialize failure");
      delay(5000);
      ESP.restart();
    }
    Serial.println("camera initialize success");
  }

  Serial.println("camera starting");
  Serial.print("http://");
  Serial.println(WiFi.localIP());

  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/cam-hi.jpg");
  server.on("/cam-hi.jpg", handleJpgHi);
  // server.on("/cam-lo.jpg", handleJpgLo);

  addRequestHandlers();
  server.begin();
}

void
loop() {
  server.handleClient();
}
