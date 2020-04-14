#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

const byte echo = 26;
const byte trigger = 25;
const byte led = 2;
const uint16_t port = 3000;
const char * host = "localhost"; // ip or dns

void setup()
{
    Serial.begin(115200);
    delay(10);

    pinMode(trigger, OUTPUT);      // set the Trigger pin mode
    pinMode(led, OUTPUT);      // set the LED pin mode
    pinMode(echo, INPUT);      // set the Echo pin mode

    // We start by connecting to a WiFi network
    WiFiMulti.addAP("TIGO-FAMILIA SAAVEDRAMOL-5G", "212401SAAMOL");

    //Serial.println();
    //Serial.println();
    Serial.print("Waiting for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void sendPulse()
{
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);          //Send pulse of 10us
  digitalWrite(trigger, LOW);
}

int convertToDistance(int distance, long timeSensor)
{
   timeSensor = pulseIn(echo, HIGH); //get pulse width
   distance = timeSensor/59;         //calculate the distance of time
   return distance;
}


void loop()
{
    long timeSensor; //time it takes for the echo to return
    int distance; //distance in cm

    Serial.print("Connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("Connection failed.");
        Serial.println("Waiting 2 seconds before retrying...");
        delay(2000);
        return;
    }
    
    sendPulse();
    distance = convertToDistance(distance, timeSensor);
    //delay(100);
    

    client.print(distance);
    //read back one line from the server
    String line = client.readStringUntil('\r');
    //client.println(line);
    Serial.println(line);

    if(line == "Off")
      digitalWrite(led, LOW);
    else if(line == "On")
      digitalWrite(led, HIGH);
      else
      {
        for (int i = 0; i < 5; i++)
        {
          digitalWrite(led, LOW);
          delay(300);
          digitalWrite(led, HIGH);
          delay(300);
        }
      }
    
    Serial.println("Closing connection.");
    //client.stop();

    Serial.println("Waiting 1 seconds before restarting...");
    delay(50);
}
