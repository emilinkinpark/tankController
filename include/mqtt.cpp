/*
Main Idea Taken from Rui Santos - https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/
*/

#include <WiFi.h>
#include <PubSubClient.h>

#include "bme680.cpp"

// Replace the next variables with your SSID/Password combination
const char *ssid = "GloryAgro";
const char *password = "Gloryart1!1";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char *mqtt_server = "192.168.0.29";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  //Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    //Serial.print(".");
  }

  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *message, unsigned int length)
{
  //Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  //Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    //Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  //Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  // if (String(topic) == "esp32/output")
  // {
  //   Serial.print("Changing output to ");
  //   if (messageTemp == "on")
  //   {
  //     Serial.println("on");
  //     digitalWrite(ledPin, HIGH);
  //   }
  //   else if (messageTemp == "off")
  //   {
  //     Serial.println("off");
  //     digitalWrite(ledPin, LOW);
  //   }
  // }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    //Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client"))
    {
      //Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    }
    else
    {
      //Serial.print("failed, rc=");
      Serial.print(client.state());
      //Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqtt_init()
{
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void mqttloop()
{                      // This part needs to be in loop
  boolean heartbeat=0; // Heartbeat of the device
  long now = millis(); //MQTT dependant
  if (!client.connected())
  { //Reconnect if network fails
    reconnect();
  }
  client.loop();

  if (now - lastMsg > 5000)
  {
    lastMsg = now;
    char str[50]; //Stores Payload to send out
    char temp[8];

    heartbeat = 1;                                                //Heartbeat publishes 1 to mark start of transmission
    dtostrf(heartbeat, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"heartbeat\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/heartbeat", str);

    dtostrf(air_temp, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"air_temp\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/bme680", str);

    dtostrf(ambient_pressure, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"ambient_pressure\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/bme680", str);
    delay(100);

    dtostrf(ambient_humidity, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"ambient_humidity\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/bme680", str);

    dtostrf(ambient_altitude, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"ambient_altitude\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/bme680", str);
    delay(100);

    heartbeat = 0;                              //Heartbeat publishes 0 to mark end of transmission
    dtostrf(heartbeat, 1, 2, temp);
    strcpy(str, "{");
    strcat(str, "\"heartbeat\"");
    strcat(str, "\:");
    strcat(str, temp);
    strcat(str, "}");
    client.publish("tank1/data/heartbeat", str);
    

    memset(str, 0, sizeof(str)); //Empties array
  }
  //MQTT End
  //Future addition - if server fails 5 times; go to redundancy
}