
#ifndef __PACKET_H__
#define __PACKET_H__

typedef struct payload_t
{
  uint8_t pkt_id;
  uint16_t tensions[15];
} payload_t;

#endif
