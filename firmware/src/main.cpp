#include <ESP8266WiFi.h>
#include <PubSubClient.h>

char tempString1[255];

// WiFi
const char *ssid = "com-TF-wifi"; // Enter your WiFi name
const char *password = "netlab12";  // Enter WiFi password

#define MQTT_SUB_MSG "co326/lab1/dev/%d/"
#define MQTT_SUB_RESP "co326/lab1/dev/%d/btn%d/resp/"

#define DEVICE_ID 1
#define BTN_1 D1
#define BTN_2 D2
#define BTN_3 D3
#define BTN_4 D4

uint8_t btnStatus[4];
uint8_t btn_gpio[4] = {BTN_1, BTN_2, BTN_3, BTN_4};

int received = false;
char respNum = 0;

// MQTT Broker
const char *mqtt_broker = "68.183.188.135";
const char *mqtt_username = "swarm_user";
const char *mqtt_password = "swarm_usere15";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    // for (unsigned int i = 0; i < length; i++) {
    //     Serial.print((char) payload[i]);
    // }
    respNum = payload[0]- '0';
    received = true;
    Serial.printf("Resp: %d\n", respNum);

    // Serial.println();
    // Serial.println("-----------------------");

}

void subscribe(){
    sprintf(tempString1, MQTT_SUB_MSG, DEVICE_ID);
    Serial.printf("Subscribing to %s\n", tempString1);
    client.subscribe(tempString1);
}

void publish(uint8_t btn, int val){
    char payload [10];

    sprintf(tempString1, MQTT_SUB_RESP, DEVICE_ID, btn);
    sprintf(payload, "%d", val);

    Serial.printf("Publishing to %s > %s\n", tempString1, payload);
    client.publish(tempString1, payload);
}

void changeButton(int btn, int val){
    digitalWrite(btn_gpio[btn], (val==1) ? HIGH: LOW);
    publish(btn, val);
}


void setup() {
    // Set software serial baud to 115200;
    Serial.begin(115200);
    // connecting to a WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp8266-client-";
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
    pinMode(BTN_1, OUTPUT);
    pinMode(BTN_2, OUTPUT);
    pinMode(BTN_3, OUTPUT);
    pinMode(BTN_4, OUTPUT);

    changeButton(0,0);
    changeButton(1,0);
    changeButton(2,0);
    changeButton(3,0);
}


int counter = 0;

void loop() {
    client.loop();

    if(received == true){
        Serial.println("Received+");
        received = false;

        changeButton(respNum, 1);
        delay(1000);
        changeButton(respNum, 0);
    }

    delay(500);
}
