#include <stdbool.h>

typedef struct
{
  int temperature;
  int humidity;
  int co2;
  int pressure;
  int outtemperature;
  int outhumidity;
  int weathercondition;
}climateData;

extern int BrightState;
extern bool EmulatorState;

struct TempClimateData{
  int intemperature;
  int outtemperature;
  int inhumidity;
  int outhumidity;
  int co2;
  int pressure;
  int wetcond;
  int hour;
  int minutes;
};


