#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/common/FrontendApplication.hpp>

#ifndef SIMULATOR

#include "climate.h"
#include "cmsis_os.h"
#include "Meteo.pb.h"
#include <stdlib.h>
#include <string.h>

extern osMessageQueueId_t climateQueueHandle;
extern osMessageQueueId_t screenQueueHandle;
extern osMessageQueueId_t wlanQueue;
extern osMessageQueueId_t clockQueue;
extern osMessageQueueId_t sensorQueue;
extern osMessageQueueId_t OutClimQueue;

Array sensors;
#endif

Model::Model() : modelListener(0)
{
	#ifndef SIMULATOR
	initArray(&sensors, 1);
	#endif
}

void Model::tick()
{
#ifndef SIMULATOR
  climateData climate = {0};
  Climate outclim = {0};
  wlanData wd = {0};
  uint32_t timestamp = 0;
  Sensor sens = {0};
  if(osMessageQueueGet(climateQueueHandle, &climate, NULL, 0U) == osOK)
  {
    modelListener->setClimateData(climate.temperature, climate.co2, climate.humidity);
  }
  else if(osMessageQueueGet(OutClimQueue, &outclim, NULL, 0U) == osOK)
  {
	modelListener->setOutTemp(outclim.outsideTemperature, outclim.outsideHumidity, outclim.weather_conditions);
  }
  else if(osMessageQueueGet(wlanQueue, &wd, NULL, 0U) == osOK)
  {
    modelListener->setWLANstatus();
  }
  else if(osMessageQueueGet(clockQueue, &timestamp, NULL, 0U) == osOK)
  {
    modelListener->setClockData(timestamp);
  }
  if(osMessageQueueGet(sensorQueue, &sens, NULL, 0U) == osOK)
  {
	  insertArray(&sensors, sens);
  }
#endif
}

#ifndef SIMULATOR
void initArray(Array *a, size_t initialSize) {
      a->array = (Sensor*)malloc(initialSize * sizeof(Sensor));
      a->used = 0;
      a->size = initialSize;
}

void insertArray(Array *a, Sensor element) {
      // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
      // Therefore a->used can go up to a->size
      if (a->used == a->size) {
        a->size *= 2;
        a->array = (Sensor*)realloc(a->array, a->size * sizeof(Sensor));
      }
      a->array[a->used++] = element;
    }

Sensor getSensors(uint8_t n){
	if (sensors.size < n){return sensors.array[n];}
	else
	{
		Sensor sens = {0};
		return sens;
	}
};
#endif
