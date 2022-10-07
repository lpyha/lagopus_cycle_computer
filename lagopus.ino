#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <TinyGPSPlus.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

TinyGPSPlus gps;
static const int GPS_RX_PIN = 8, GPS_TX_PIN = 9;
static const uint32_t GPSBaud = 4800;
SoftwareSerial ss(GPS_RX_PIN, GPS_TX_PIN);

static const int DF_RX_PIN = 3, DF_TX_PIN = 4;
SoftwareSerial mySoftwareSerial(DF_RX_PIN, DF_TX_PIN); 
DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  ss.begin(GPSBaud);

  //while(!SD.begin(chipSelect)) {
  //  Serial.println("Card failed, or not present");
  //}

  mySoftwareSerial.listen();
  while (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30);
  myDFPlayer.play(1);
}

void loop() {
  ss.listen();
  Serial.print("DOP:  ");
  Serial.print(gps.hdop.hdop());
  Serial.print("longitude: ");
  Serial.print(gps.location.lng(),6);
  Serial.print("latitude: ");
  Serial.print(gps.location.lat(),6);
  Serial.print("speed: ");
  Serial.print(gps.speed.mps());
  Serial.print("altitude: ");
  Serial.println(gps.altitude.meters());
  //File dataFile = SD.open("datalog.txt", FILE_WRITE);
  //if (dataFile) {
  //  dataFile.print("longitude: ");
  //  dataFile.print(gps.location.lng(),6);
  //  dataFile.print("latitude: ");
  //  dataFile.print(gps.location.lat(),6);
  //  dataFile.print("speed: ");
  //  dataFile.print(gps.speed.mps());
  //  dataFile.print("altitude: ");
  //  dataFile.println(gps.altitude.meters());
  //  dataFile.close();
  //}
}
