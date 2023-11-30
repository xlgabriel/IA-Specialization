#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#define mqttUser ""
#define mqttPass ""
#define mqttPort 1883
#define Led 2
Adafruit_MPU6050 mpu;
const char* ssid = "xxxxx"; //ssid de la red inalambrica
const char* password = "xxxxxxx"; //password para conectarse a la red
char mqttBroker[] = "broker.mqtt-dashboard.com"; //ip del servidor
char mqttClientId[] = "device1"; //cualquier nombre
char inTopic1[] = "proyecto/topico1";
char inTopic2[] = "proyecto/topico2";
void callback(char* topic, byte* payload, unsigned int length) {
String json=String((char *)payload);
Serial.println();
StaticJsonDocument<300> doc;
DeserializationError error = deserializeJson(doc, json);
if (error) { return; }
int estado = doc["estado"];
Serial.println(estado);
if (estado == 1) {
digitalWrite(Led, HIGH);
}
else {
digitalWrite(Led, LOW);
}
}
WiFiClient BClient;
PubSubClient client(BClient);
void reconnect() {
// Loop until we're reconnected
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
// Attempt to connect
if (client.connect(mqttClientId, mqttUser, mqttPass)) {
Serial.println("connected");
client.subscribe(inTopic2);
} else {
Serial.print("failed, rc=");
Serial.print(client.state());
Serial.println(" try again in 5 seconds");
// Wait 5 seconds before retrying
delay(5000);
}
}
}
void setup()
{
pinMode(Led, OUTPUT);
Serial.begin(115200); //Serial connection
setup_wifi(); //WiFi connection
client.setServer( mqttBroker, mqttPort );
client.setCallback( callback );
Serial.println("Setup done");
delay(1500);
Serial.println("Adafruit MPU6050 test!");
// Try to initialize!
if (!mpu.begin()) {
Serial.println("Failed to find MPU6050 chip");
while (1) {
delay(10);
}
}
Serial.println("MPU6050 Found!");
mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
Serial.print("Accelerometer range set to: ");
switch (mpu.getAccelerometerRange()) {
case MPU6050_RANGE_2_G:
Serial.println("+-2G");
break;
case MPU6050_RANGE_4_G:
Serial.println("+-4G");
break;
case MPU6050_RANGE_8_G:
Serial.println("+-8G");
break;
case MPU6050_RANGE_16_G:
Serial.println("+-16G");
break;
}
mpu.setGyroRange(MPU6050_RANGE_500_DEG);
Serial.print("Gyro range set to: ");
switch (mpu.getGyroRange()) {
case MPU6050_RANGE_250_DEG:
Serial.println("+- 250 deg/s");
break;
case MPU6050_RANGE_500_DEG:
Serial.println("+- 500 deg/s");
break;
case MPU6050_RANGE_1000_DEG:
Serial.println("+- 1000 deg/s");
break;
case MPU6050_RANGE_2000_DEG:
Serial.println("+- 2000 deg/s");
break;
}
mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
Serial.print("Filter bandwidth set to: ");
switch (mpu.getFilterBandwidth()) {
case MPU6050_BAND_260_HZ:
Serial.println("260 Hz");
break;
case MPU6050_BAND_184_HZ:
Serial.println("184 Hz");
break;
case MPU6050_BAND_94_HZ:
Serial.println("94 Hz");
break;
case MPU6050_BAND_44_HZ:
Serial.println("44 Hz");
break;
case MPU6050_BAND_21_HZ:
Serial.println("21 Hz");
break;
case MPU6050_BAND_10_HZ:
Serial.println("10 Hz");
break;
case MPU6050_BAND_5_HZ:
Serial.println("5 Hz");
break;
}
Serial.println("");
delay(100);
}
void setup_wifi() {
delay(10);
// We start by connecting to a WiFi network
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
void loop()
{
if (!client.connected()) {
reconnect();
}
client.loop();
//aquí va el código asociado al sensor y generación del json
sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);
String json;
StaticJsonDocument<300> doc;
doc["accx"] = a.acceleration.x;
doc["accy"] = a.acceleration.y;
doc["accz"] = a.acceleration.z;
doc["rotx"] = g.gyro.x;
doc["roty"] = g.gyro.y;
doc["rotz"] = g.gyro.z;
doc["temp"] = temp.temperature;
serializeJson(doc, json);
Serial.println(json);
int lon = json.length()+1;
char datojson[lon];
json.toCharArray(datojson, lon);
client.publish(inTopic1,datojson);
delay (5000);
}