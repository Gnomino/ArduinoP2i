#include  <SPI.h>
#include  <RF24.h>
#include "packet.h"

int sensorPin = A0;
RF24 radio(9,10);
uint8_t address[6] = {110,0xCE,0xCC,0xCE,0xCC};   // Adresse du pipe
uint8_t nbVals; // Nombre de valeurs en memoire
payload_t payload;
int nbPackets = 0; // Compteur de paquets
unsigned long nbTotalVals = 0;
void setup() {
  //Serial.begin(115200);    // Initialiser la communication série 
  nbVals = 0;
  radio.begin();
  radio.setChannel(110);
  radio.setRetries(0,0);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(address);    // Ouvrir le Pipe en écriture
  radio.stopListening();             
}

void loop(void) {
  payload.tensions[nbVals++] = analogRead(sensorPin);
  if(nbVals == 15) {
    payload.pkt_id = nbPackets++;
    radio.write(&payload,sizeof(payload));
    nbVals = 0;
  }
  unsigned long nextT = (++nbTotalVals)*500;
  if(nextT > micros())
    delayMicroseconds(nextT-micros());
}
