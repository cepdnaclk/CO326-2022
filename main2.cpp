// #include <ESP8266WiFi.h>
// #include <PubSubClient.h>
//
// char tempString1[255];
//
// // WiFi
// const char *ssid = "com-TF-wifi"; // Enter your WiFi name
// const char *password = "netlab12";  // Enter WiFi password
//
// #define MQTT_SUB_MSG "co326/lab1/dev/%d/btn%d"
// #define MQTT_SUB_RESP "co326/lab1/dev/%d/btn%d/resp/"
//
// #define DEVICE_ID 1
// #define BTN_1 1
// #define BTN_2 2
// // #define BTN_IND_1 3
// // #define BTN_IND_2 4
//
// const char *topic = "co326/lab1/dev/1/";
// uint8_t btnStatus[2];
//
// char status = '0';
// int received = false;
// int counter = 0;
//
// // MQTT Broker
// const char *mqtt_broker = "68.183.188.135";
// const char *mqtt_username = "swarm_user";
// const char *mqtt_password = "swarm_usere15";
// const int mqtt_port = 1883;
//
// WiFiClient espClient;
// PubSubClient client(espClient);
//
// void publish(uint8_t btn, int val){
//     char payload [10];
//
//     sprintf(tempString1, MQTT_SUB_RESP, DEVICE_ID, btn);
//     sprintf(payload, "%d", val);
//
//     Serial.printf("Publishing to %s\n", tempString1);
//     client.publish(tempString1, payload);
// }
//
// void callback(char *topic, byte *payload, unsigned int length) {
//     Serial.print("Message arrived in topic: ");
//     Serial.println(topic);
//     Serial.printf("Message: %c \n", payload[0]);
//     // for (unsigned int i = 0; i < length; i++) {
//         // Serial.print((char) payload[i]);
//     // }
//     Serial.println();
//     Serial.println("-----------------------");
//
//     received = true;
//     status = payload[0];
//
// }
//
// void changeButton(int btn, int val){
//     if (btn==1){
//         digitalWrite(BTN_1, HIGH);
//         // publish(1, 1);
//         delay(1000);
//         digitalWrite(BTN_1, LOW);
//         // publish(1, 0);
//
//     }else if (btn==2){
//         digitalWrite(BTN_2, HIGH);
//         // publish(2, 1);
//         delay(1000);
//         digitalWrite(BTN_2, LOW);
//         // publish(2, 0);
//
//     }
// }
//
// void subscribe(uint8_t btn){
//     sprintf(tempString1, MQTT_SUB_MSG, DEVICE_ID, btn);
//     Serial.printf("Subscribing to %s\n", tempString1);
//     client.subscribe(tempString1);
// }
//
//
//
// void setup() {
//     // Set software serial baud to 115200;
//     Serial.begin(115200);
//     // connecting to a WiFi network
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.println("Connecting to WiFi..");
//     }
//     Serial.println("Connected to the WiFi network");
//     //connecting to a mqtt broker
//     client.setServer(mqtt_broker, mqtt_port);
//     client.setCallback(callback);
//     while (!client.connected()) {
//         char client_id[64];
//         sprintf(client_id, "esp8266-client-%d", WiFi.macAddress()[0]);
//
//         // Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());
//
//         if (client.connect(client_id, mqtt_username, mqtt_password)) {
//             delay(1000);
//             Serial.print(F("Connected\n"));
//         } else {
//             Serial.print("failed with state ");
//             Serial.print(client.state());
//             delay(2000);
//         }
//     }
//     Serial.println("------");
//
//     // publish and subscribe
//     // subscribe(1);
//     // subscribe(2);
//
//     // Setup GPIO
//     pinMode(BTN_1, OUTPUT);
//     pinMode(BTN_2, OUTPUT);
//
//     changeButton(0,0);
//     changeButton(1,0);
//
//     // pinMode(BTN_IND_1, OUTPUT);
//     // pinMode(BTN_IND_2, OUTPUT);
//
// }
//
//
// void loop() {
//     client.loop();
//
//     // if(received == true){
//     //     Serial.printf("Received: %c\n", status);
//     //     received = false;
//     // }
//
//     // publish(1, counter++);
//     // publish(2, counter++);
//     delay(1000);
// }
