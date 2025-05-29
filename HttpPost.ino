#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "와이파이 이름";
const char* password = "와이파이비번";
const char* serverUrl = "서버주소";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" WiFi connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure(); // SSL 인증서 검증 비활성화(테스트용, 실제 서비스시 인증서 등록 권장)
    HTTPClient https;

    if (https.begin(client, serverUrl)) {
      https.addHeader("Content-Type", "application/json");
      String postData = "{\"beatsPerMinute\": 100, \"interBeatInterval\": 80, \"signal\": 23, \"timeStamp\": \"2024-05-23 21:00:00\"}";

      int httpResponseCode = https.POST(postData);

      if (httpResponseCode > 0) {
        String response = https.getString();
        Serial.print("Server Response: ");
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }
      https.end();
    }
  }
  delay(1000);
}
