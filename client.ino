#include <SocketIOclient.h>
#include <WiFi.h>

const char* ssid = "ssid";
const char* pass = "pass";
SocketIOclient socketIO;

void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case sIOtype_DISCONNECT:
          Serial.println("disconnect");
          break;
        case sIOtype_CONNECT:
            Serial.println("connect");
            // 기본 네임스페이스에 가입(소켓에는 자동 가입 없음).IO V3)
            socketIO.send(sIOtype_CONNECT, "/");
            break;
        case sIOtype_EVENT:
            Serial.println("event");
        case sIOtype_ACK:
            Serial.println("ack");
        case sIOtype_ERROR:
            Serial.println("error");
        case sIOtype_BINARY_EVENT:
            Serial.println("b-event");
        case sIOtype_BINARY_ACK:
            Serial.println("b-ack");
    }
}

void setup() {
  // ...인터넷에 연결
  Serial.begin(115200);
  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
  // server address, port and URL
  socketIO.begin("ip address", port);

  socketIO.onEvent(socketIOEvent);
}

void loop() {
  socketIO.loop();
  socketIO.sendEVENT("hello");
}