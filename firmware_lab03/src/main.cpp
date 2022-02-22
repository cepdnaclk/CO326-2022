/*

https://arduino.esp8266.com/stable/package_esp8266com_index.json

ls -l /dev/ttyUSB*
sudo usermod -a -G dialout el-01
sudo chmod ug+rwx /dev/ttyUSB0

*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <PubSubClient.h>

char tempString1[255];

// WiFi
const char *ssid = "com-TF-wifi"; // Enter your WiFi name
const char *password = "netlab12";  // Enter WiFi password

#define MQTT_SUB_MSG "co326/lab3/dev/%d/pot/"
#define MQTT_SUB_RESP "co326/lab3/dev/%d/pot/resp/"

#define DEVICE_ID 1

int received = false;
int respNum = 0;

// MQTT Broker
const char *mqtt_broker = "68.183.188.135";
const char *mqtt_username = "swarm_user";
const char *mqtt_password = "swarm_usere15";
const int mqtt_port = 1883;

int counter = 0;
int retryCount = 0;

unsigned long previousMillis = 0;
unsigned long interval = 30000;

WiFiClient espClient;
PubSubClient client(espClient);

// -----------------------------------------------------------------------------
// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
const int potPin = 18;


// -----------------------------------------------------------------------------

// Subscribe to MQTT topics
void subscribe(){
    sprintf(tempString1, MQTT_SUB_MSG, DEVICE_ID);
    Serial.printf("Subscribing to %s\n", tempString1);
    client.subscribe(tempString1);
}

// Reconnect
void reconnect() {
    uint8_t reconnectCount = 0;

    while (!client.connected()) {
        if(reconnectCount>100) ESP.restart(); // more than 25 seconds

        Serial.print("Attempting MQTT connection...");

        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());

        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("connected");
            subscribe();
        } else {
            reconnectCount++;
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again");
            delay(250);
        }
    }
}

// MQTT topic responses
void callback(char *topic, byte *payload, unsigned int length) {
    char msg[length + 1];
    msg[length] = '\0';

    msg[0] =  (char)payload[0];
    respNum = msg[0] - '0';

    for (int i = 1; i < length; i++) {
        msg[i] =  (char)payload[i];

        // Convert into a number
        respNum = respNum*10 + ((char)payload[i]-'0');
        // Serial.printf("\n>> %d %d\n", respNum, ((char)payload[i]-'0'));
    }

    Serial.printf("\n>> topic: %s msg:'%s'\n", topic, msg);

    // if (1 == sscanf(msg, "%d",  &value)) respNum = value;
    received = true;
    Serial.printf("Resp: %d\n", respNum);

}

// Publish the ACK message
void publish(int val){
    char payload [10];

    sprintf(tempString1, MQTT_SUB_RESP, DEVICE_ID);
    sprintf(payload, "%d", val);

    Serial.printf("Publishing to %s > %s\n", tempString1, payload);
    client.publish(tempString1, payload);
}

void setup() {
    // Set software serial baud to 115200;

    Serial.begin(115200);

    // connecting to a WiFi network
    WiFi.begin(ssid, password);

    int setupRetry = 0;
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connecting to WiFi..");
        setupRetry++;
        if(setupRetry>10) ESP.restart();
        delay(500);
    }

    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);

    Serial.println("Connected to the WiFi network");

    //connecting to the mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);

    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public mqtt broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // publish and subscribe
    subscribe();

    // Setup GPIO
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(potPin, ledChannel);

}

void printWiFiStatus(){
    //print the Wi-Fi status every 30 seconds
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >=interval){
        // switch (WiFi.status()){
        //     case WL_NO_SSID_AVAIL:
        //     Serial.println("Configured SSID cannot be reached");
        //     break;
        //     case WL_CONNECTED:
        //     Serial.println("Connection successfully established");
        //     break;
        //     case WL_CONNECT_FAILED:
        //     Serial.println("Connection failed");
        //     break;
        // }
        Serial.printf("Connection status: %d\n", WiFi.status());
        Serial.print("RRSI: ");
        Serial.println(WiFi.RSSI());
        previousMillis = currentMillis;
        Serial.println("");

        // Just dump some message into MQTT
        client.publish("co326/void", "***");
    }
}

void loop() {
    if (!client.connected()) {
        //safeShutdown();
        reconnect();
    }
    client.loop();

    if(received == true){
        ledcWrite(ledChannel, respNum);
        received = false;
        delay(1000);
        publish(respNum);
    }

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("[Retry] Connecting to WiFi...");
        retryCount++;

        if(retryCount > 10){
            ESP.restart();
        }
    }

    retryCount = 0;
    printWiFiStatus();

    delay(500);
}
