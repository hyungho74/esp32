#include <WiFi.h>           // EthernetClient대신 esp32에서 wifi에 연결하기 위한 라이브러리
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

IPAddress server_addr(10,82,17,194);  // mysql의 서버주소를 적음
char user[] = "root";              // mysql서버에 로그인 할 유저이름을 적음
char password[] = "password";        // mysql서버에 로그인 할 password를 적음

// query문
char INSERT_SQL[] = "INSERT INTO esp32.item values('19', '15440987', 'hoxy', 'B49', 'D7699')";

// wifi연결
char ssid[] = "ssid";         // 와이파이 이름
char pass[] = "password";     // 와이파이 password

WiFiClient client;                 // EthernetClient대신에 사용
MySQL_Connection conn(&client);     
MySQL_Cursor* cursor;

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // Begin WiFi section
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, pass); //wifi 연결
  while (WiFi.status() != WL_CONNECTED) { //wifi가 연결될 때까지 반복
    delay(500);
    Serial.print(".");
  }

  // print out info about the connection:
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP()); //연결된 wifi의 ip주소 출력

  Serial.print("Connecting to SQL...  ");
  if (conn.connect(server_addr, 3306, user, password)) //mysql connection 연결
    Serial.println("OK.");
  else
    Serial.println("FAILED.");
  
  // musql 커서 object생성
  cursor = new MySQL_Cursor(&conn);
}

void loop()
{
  if (conn.connected())
    cursor->execute(INSERT_SQL); //sql문 실행

  delay(5000);
}