#include "application.h"
#include "main.h"
#include "cmsis_os.h"
#include "climate.h"
#include <stdlib.h>
#include <string.h>
#include "esp.h"
#include <time.h>
#include "fatfs.h"
#include "sht2x.h"

#define MSG_SIZE 100

struct tm ap_ttm = {0};
bool ap_wlan_status = false;

const osThreadAttr_t ClimateTask_attributes = {
  .name = "ClimateTask",
  .stack_size = 512 * 10,
  .priority = (osPriority_t) osPriorityNormal,
};

osMessageQueueId_t wlanQueue;
extern osMessageQueueId_t climateQueueHandle;
extern DMA2D_HandleTypeDef hdma2d;
extern LTDC_HandleTypeDef hltdc;

void StartClimateTask(void *argument)
{
  srand(10);
  climateData climate;

  for(;;)
  {
	  /*while(!in_message.has_wlan_rssi == true)
	  {
		  memset(inMsg, NULL, MSG_SIZE);
		  serial_receive_msg(inMsg, MSG_SIZE);
		  pb_istream_t stream = pb_istream_from_buffer(inMsg, MSG_SIZE);
		  bool status = pb_decode(&stream, EspMsg_fields, &in_message);
		  if(in_message.has_wlan_rssi == true){
		 	        wlanData wd = {0};
		 	        wd.rssi = in_message.wlan_rssi;
		 	        osMessageQueuePut(wlanQueue, &wd, 0, 0);
		 	 }
	  }*/

	//check mode change
	//if(HAL_GPIO_ReadPin(B3_GPIO_Port, B3_Pin) == 1) isEmulatorMode = !isEmulatorMode;

	uint8_t outMsg[MSG_SIZE];

	climate.co2 = (rand() % 50 + 700);
	climate.temperature = SHT2x_GetInteger(SHT2x_GetTemperature(1));
	climate.humidity = SHT2x_GetInteger(SHT2x_GetRelativeHumidity(1));
	//climate.outtemperature = 5;

    osMessageQueuePut(climateQueueHandle, &climate, 0, 0);

    EspMsg climate_message = {0};
    climate_message.has_climate = 1;
    climate_message.climate.has_insideTemperature = 1;
    climate_message.climate.has_insideHumidity = 1;
    climate_message.climate.has_insideCO2 = 1;

    climate_message.climate.insideTemperature = climate.temperature;
    climate_message.climate.insideHumidity = climate.humidity;
    climate_message.climate.insideCO2 = climate.co2;

    /*climate_message.climate.has_temperature_topic = 1;
    climate_message.climate.has_humidit_topic = 1;
    climate_message.climate.has_co2_topic = 1;

    strcpy(climate_message.climate.temperature_topic, "home/temperature");
    strcpy(climate_message.climate.humidit_topic, "home/humidity");
    strcpy(climate_message.climate.co2_topic, "home/co2");*/

    pb_ostream_t out_stream = pb_ostream_from_buffer(outMsg, MSG_SIZE);
    pb_encode(&out_stream, EspMsg_fields, &climate_message);

    serial_send_msg(outMsg, MSG_SIZE);


    osDelay(2000);
  }
}

void LoadAssetsFromSd(uint32_t* assets_location_in_sdram)
{
	 FATFS SDFatFs;
	 FRESULT fr1;
	 FIL ResourceFile;
	 UINT br;
	 fr1 = f_mount(&SDFatFs, "", 1);
	 fr1 = f_open(&ResourceFile, "images.bin", FA_READ);
	 //screenQueueHandle = osMessageQueueNew(1, sizeof(uint8_t), &screenQueue_attributes);
	 while(f_eof(&ResourceFile) == 0)
	 {
	   fr1 = f_read(&ResourceFile, assets_location_in_sdram, 32, &br);
	   if(fr1 != FR_OK) TFT_FillScreen(0xFFFF0000);
	   assets_location_in_sdram+=8;
	 }
}

void TFT_FillScreen(uint32_t color)
{
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.OutputOffset = 0;
  if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
  {
    if (HAL_DMA2D_Start(&hdma2d, color, SDRAM_BANK_ADDR,
    hltdc.LayerCfg[0].ImageWidth, hltdc.LayerCfg[0].ImageHeight) == HAL_OK)
    {
      HAL_DMA2D_PollForTransfer(&hdma2d, 10);
    }
  }
}
