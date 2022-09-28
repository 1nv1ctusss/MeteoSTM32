#include "stm32h7xx_hal.h"

#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "Meteo.pb.h"

void esp_serial_init(void);
void serial_send_msg(uint8_t* msg, uint16_t size);
void serial_receive_msg(uint8_t* msg, uint32_t size);

typedef struct
{
  int rssi;
  uint8_t wlan_status;
  char ip[20];
}wlanData;
