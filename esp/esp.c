#include "esp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cmsis_os.h"
#include "climate.h"

#define MSG_SIZE 300

UART_HandleTypeDef esp_uart;
extern osMessageQueueId_t wlanQueue;
osMessageQueueId_t clockQueue;
osMessageQueueId_t sensorQueue;
osMessageQueueId_t OutClimQueue;
//osMessageQueueId_t OutHumQueue;
//osMessageQueueId_t WeatherQueue;
//static osMessageQDef(SerialUartRxChar, 4, char); // Declare a message queue
//static osMessageQId (SerialUartRxCharId); // Declare an ID for the message queue

osMessageQueueId_t SerialUartRxChar;
const osMessageQueueAttr_t SerialUartRxChar_attributes = {
  .name = "SerialUartRxChar"
};

const osThreadAttr_t SerialTask_attributes = {
  .name = "SerialTask",
  .stack_size = 256 * 40,
  .priority = (osPriority_t) osPriorityNormal,
};
const osMessageQueueAttr_t wlanQueue_attributes = {
  .name = "wlanQueue"
};

const osMessageQueueAttr_t clockQueue_attributes = {
  .name = "clockQueue"
};

const osMessageQueueAttr_t sensorQueue_attributes = {
  .name = "sensorQueue"
};
const osMessageQueueAttr_t OutClimQueue_attributes = {
  .name = "OutClimQueue",
};

void EmulateHADevices()
{
  Sensor sensors[5] = {0};
  memcpy(sensors[0].friendly_name, "Влажность", 18);
  //sensors[0].value = 32;
  memcpy(sensors[0].unit, "%", 1);
  while(1){
  osMessageQueuePut(sensorQueue, &(sensors[0]), 0, 0);
  osDelay(2000);
  }
}

void StartSerialTask(void *argument)
{
  uint8_t inMsg[MSG_SIZE] = {0};
  //EmulateHADevices();
  for(;;)
  {
    EspMsg in_message = {0};
    serial_receive_msg(inMsg, MSG_SIZE);

    pb_istream_t stream = pb_istream_from_buffer(inMsg, MSG_SIZE);
    bool status = pb_decode(&stream, EspMsg_fields, &in_message);

    if(in_message.has_wlan_rssi == true){
      wlanData wd = {0};
      wd.rssi = in_message.wlan_rssi;
      osMessageQueuePut(wlanQueue, &wd, 0, 0);
    }

    if(in_message.climate.has_outsideTemperature == true && in_message.climate.has_outsideHumidity == true){
    	Climate outtemp = in_message.climate;
    	//int32_t bg = 30;
        osMessageQueuePut(OutClimQueue, &outtemp, 0, 0);
    }
  /*  if(in_message.has_weather_conditions == true && in_message.weather_conditions[0] != 0){
        uint32_t wethcond = in_message.weather_conditions;  //weather_conditions - массив char а у нас uint32_t
        osMessageQueuePut(WeatherQueue, &wethcond, 0, 0);   //надо думать
    }*/

    if(in_message.has_rtcTimestamp == true && in_message.rtcTimestamp != 0)
    {
      uint32_t ts = in_message.rtcTimestamp;
      osMessageQueuePut(clockQueue, &ts, 0, 0);
    }

    if(in_message.sensor_count > 0)
    {
    	//Send all devices to q one at time
    	for(uint16_t i=0;i<in_message.sensor_count;i++){
    		osMessageQueuePut(sensorQueue, &(in_message.sensor[i]), 0, 0);
    	}
    }

    osDelay(10);
  }
}

void esp_serial_init(void)
{
  esp_uart.Instance = UART8;
  esp_uart.Init.BaudRate = 115200;
  esp_uart.Init.WordLength = UART_WORDLENGTH_8B;
  esp_uart.Init.StopBits = UART_STOPBITS_1;
  esp_uart.Init.Parity = UART_PARITY_NONE;
  esp_uart.Init.Mode = UART_MODE_TX_RX;
  esp_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  esp_uart.Init.OverSampling = UART_OVERSAMPLING_16;
  esp_uart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  esp_uart.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  esp_uart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&esp_uart) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&esp_uart, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&esp_uart, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&esp_uart) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_UART_ReceiverTimeout_Config(&esp_uart, 0x007FFF);
  HAL_UART_EnableReceiverTimeout(&esp_uart);
  SerialUartRxChar = osMessageQueueNew (4, sizeof(char), &SerialUartRxChar_attributes);
  wlanQueue = osMessageQueueNew (1, sizeof(wlanData), &wlanQueue_attributes);
  clockQueue = osMessageQueueNew (1, sizeof(uint32_t), &clockQueue_attributes);
  sensorQueue = osMessageQueueNew(20, sizeof(Sensor), &sensorQueue_attributes);
  OutClimQueue = osMessageQueueNew(1, sizeof(Climate) ,&OutClimQueue_attributes);
}

void serial_send_msg(uint8_t* msg, uint16_t size){

  HAL_UART_Transmit(&esp_uart, msg, size, 0xFFFF);
  //while(HAL_UART_GetState(&esp_uart) != HAL_UART_STATE_READY);
}

void serial_receive_msg(uint8_t* msg, uint32_t size){

  memset(msg, NULL, size);
  HAL_UART_Receive_IT(&esp_uart, msg, size);
  //osMessageGet(SerialUartRxChar, osWaitForever);
  char var = 0;
  osMessageQueueGet(SerialUartRxChar, &var, NULL, osWaitForever);
}

void UART8_IRQHandler(void)
{
  HAL_UART_IRQHandler(&esp_uart);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	char var = 0;
    if (huart == &esp_uart) {

      //osMessagePut(SerialUartRxChar, 0, 0);
      osMessageQueuePut(SerialUartRxChar, &var, 0, 0);
    }
}
