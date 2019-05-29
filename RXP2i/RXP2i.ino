#include  <SPI.h>
#include  <RF24.h>
#include "packet.h"

RF24 radio(9, 10);
uint8_t address[6] = {110, 0xCE, 0xCC, 0xCE, 0xCC}; // Adresse du pipe
payload_t pkt;

void setup() {
  Serial.begin(115200);    // Initialiser la communication série

  radio.begin();
  radio.setChannel(110);
  radio.setDataRate(RF24_2MBPS);

  radio.openReadingPipe(0, address); // Ouvrir le Pipe en lecture
  radio.startListening();
}

void loop(void) {
 

  while (radio.available())
  {
    radio.read(&pkt, sizeof(payload_t));
    for(int i = 0; i < 15; ++i) {
      Serial.println(pkt.tensions[i]);
    }
  }
}
