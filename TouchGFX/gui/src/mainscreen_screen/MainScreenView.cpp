#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <time.h>

#ifndef SIMULATOR

#include <string.h>
#include "stm32h7xx_hal.h"
#include "climate.h"
extern struct tm ap_ttm;
extern bool ap_wlan_status;
bool EmulatorState = false;
int BrightState = 25000;
struct TempClimateData TempData = {0,0,0,0,0,0,0,0,0};

#endif

MainScreenView::MainScreenView()
{
	brightnessSlider.setValue(BrightState);
	EmulatorButton.forceState(EmulatorState);
	Unicode::snprintf(TempValueBuffer, TEMPVALUE_SIZE, "%d", TempData.intemperature);
	TempValue.invalidate();
	Unicode::snprintf(co2ValueBuffer, CO2VALUE_SIZE, "%d", TempData.co2);
	co2Value.invalidate();
	Unicode::snprintf(humValueBuffer, HUMVALUE_SIZE, "%d", TempData.inhumidity);
	humValue.invalidate();
	Unicode::snprintf(outTempValueBuffer, OUTTEMPVALUE_SIZE, "%d", TempData.outtemperature);
	outTempValue.invalidate();
	Unicode::snprintf(outHumValueBuffer, OUTHUMVALUE_SIZE, "%d", TempData.outhumidity);
	outHumValue.invalidate();
	digitalClock1.setTime24Hour((uint8_t)TempData.hour, (uint8_t)TempData.minutes, 0);
	digitalClock1.invalidate();

	MainScreenView::WeatherFalser(); //set images to invisible

	if (TempData.wetcond == 1)
		Thunder.setVisible(true);
	else if (TempData.wetcond == 2)
		Rain.setVisible(true);
	else if (TempData.wetcond == 3)
		Snow.setVisible(true);
	else if (TempData.wetcond == 4){
		if (TempData.hour >= 18 || TempData.hour <= 6)
			Moon.setVisible(true);
		else
			Sunny.setVisible(true);
	}
	else if (TempData.wetcond == 5)
		Cloudy.setVisible(true);

	Sunny.invalidate();
	Rain.invalidate();
	Cloudy.invalidate();
	Thunder.invalidate();
	Snow.invalidate();
}

void MainScreenView::updateTemperature(int newValue)
{
  if (EmulatorState == true)
  {
	  int val = (rand() % 40 + 5);
	  Unicode::snprintf(TempValueBuffer, TEMPVALUE_SIZE, "%d", val);
	  TempData.intemperature = val;
	  TempValue.invalidate();

	  val = (rand() % 40 + 5);
	  Unicode::snprintf(outTempValueBuffer, OUTTEMPVALUE_SIZE, "%d", val);
	  TempData.outtemperature = val;
	  outTempValue.invalidate();
  }
  else
  {
	  Unicode::snprintf(TempValueBuffer, TEMPVALUE_SIZE, "%d", newValue);
	  TempData.intemperature = newValue;
	  TempValue.invalidate();
  }

}

void MainScreenView::updateCO2(int newValue)
{
	 if (EmulatorState == true)
	 {
		 int val = (rand() % 2000 + 200);
		 Unicode::snprintf(co2ValueBuffer, CO2VALUE_SIZE, "%d", val);
		 TempData.co2 = val;
		 co2Value.invalidate();

		 MainScreenView::WeatherFalser(); //set images to invisible

		 int i = rand() % 5 + 1;
			if(i == 1){
				Thunder.setVisible(true);
				TempData.wetcond = 1;
			}
			else if (i == 2){
				Rain.setVisible(true);
				TempData.wetcond = 2;
			}
			else if (i == 3){
				Snow.setVisible(true);
				TempData.wetcond = 3;
			}
			else if (i == 4){
				int k = rand() % 6 + 1;
				if (k % 2)
					Moon.setVisible(true);
				else
					Sunny.setVisible(true);
				TempData.wetcond = 4;
			}
			else if (i == 5){
				Cloudy.setVisible(true);
				TempData.wetcond = 5;
			}

			Sunny.invalidate();
			Rain.invalidate();
			Cloudy.invalidate();
			Thunder.invalidate();
			Snow.invalidate();
	 }
	 else
	 {
		 //gaugeCO2.updateValue(newValue, 10);
		 Unicode::snprintf(co2ValueBuffer, CO2VALUE_SIZE, "%d", newValue);
		 TempData.co2 = newValue;
		 co2Value.invalidate();
	 }

}

void MainScreenView::updateHumidity(int newValue)
{
	if (EmulatorState == true)
	{
		int val = (rand() % 6 + 70);
		Unicode::snprintf(humValueBuffer, HUMVALUE_SIZE, "%d", val);
		TempData.inhumidity = val;
		humValue.invalidate();

		Unicode::snprintf(outHumValueBuffer, OUTHUMVALUE_SIZE, "%d", val);
		TempData.outhumidity = val;
		outHumValue.invalidate();

		digitalClock1.setTime24Hour(0, 0, 0);
		TempData.hour = 0;
		TempData.minutes = 0;
	}
	else
	{
		 Unicode::snprintf(humValueBuffer, HUMVALUE_SIZE, "%d", newValue);
		 TempData.inhumidity = newValue;
		 humValue.invalidate();
	}

  //gaugeTemp.invalidate();
  /*memset(textArea1Buffer, 0, TEXTAREA1_SIZE);
  screenView::printSpace();
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", newValue);
    textArea1.resizeToCurrentText();
    textArea1.invalidate();*/
}


void MainScreenView::updateOutTemperature(int newValue)
{
  if (EmulatorState == true)
  {
	  //Блок перенесен в updateTemperature
  }
  else
  {
	  Unicode::snprintf(outTempValueBuffer, OUTTEMPVALUE_SIZE, "%d", newValue);
	  TempData.outtemperature = newValue;
	  outTempValue.invalidate();
  }

}

void MainScreenView::updateOutHumidity(int newValue)
{
  if (EmulatorState == true)
  {
	  //Блок перенесен в updateHumidity
  }
  else
  {
	  Unicode::snprintf(outHumValueBuffer, OUTHUMVALUE_SIZE, "%d", newValue);
	  TempData.outhumidity = newValue;
	  outHumValue.invalidate();
  }

}

void MainScreenView::updateWeatherCondition(char* weather)
{
	MainScreenView::WeatherFalser(); //set images to invisible
	if (EmulatorState == true){
		//Блок перенесен в updateCO2
	}
	else{
		if(strstr(weather,"thunderstorm") != NULL){
			Thunder.setVisible(true);
			TempData.wetcond = 1;
		}
		else if(strstr(weather,"rain") || strstr(weather,"showers") || strstr(weather,"drizzle") != NULL){
			Rain.setVisible(true);
			TempData.wetcond = 2;
		}
		else if(strstr(weather,"snow") || strstr(weather,"hail") != NULL){
			Snow.setVisible(true);
			TempData.wetcond = 3;
		}
		else if(strstr(weather,"clear") != NULL){
			if (TempData.hour >= 18 || TempData.hour <= 6) //Dark time
				Moon.setVisible(true);
			else
				Sunny.setVisible(true);                   //Light time
			TempData.wetcond = 4;
		}
		else if(strstr(weather,"cloudy") || strstr(weather,"overcast") != NULL){
			Cloudy.setVisible(true);
			TempData.wetcond = 5;
		}
	}
	Sunny.invalidate();
	Rain.invalidate();
	Cloudy.invalidate();
	Thunder.invalidate();
	Snow.invalidate();
}


void MainScreenView::setWLANstatus()
{
#ifndef SIMULATOR
  wlan_status = true;
  //ap_wlan_status = wlan_status;
#endif
  //WLANimage.setVisible(wlan_status);
  //WLANimage.invalidate();
}

void MainScreenView::updateClock(uint32_t timestamp)
{
#ifndef SIMULATOR
	if (EmulatorState == true){
		//Блок перенесен в updateHumidity
	}
	else{
		time_t timest = (time_t)timestamp;
		ap_ttm = *localtime(&timest);
		TempData.hour = ap_ttm.tm_hour;
		TempData.minutes = ap_ttm.tm_min;
		digitalClock1.setTime24Hour((uint8_t)TempData.hour, (uint8_t)TempData.minutes, 0);
	}
#endif
}

void MainScreenView::printSpace()
{
  /*
  Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "     ");
  //textArea1.setWidth(3);
  textArea1.invalidate();*/
}

void MainScreenView::setupScreen()
{
#ifndef SIMULATOR
    MainScreenViewBase::setupScreen();
    //wlan_status = ap_wlan_status;
    //WLANimage.setVisible(wlan_status);
    //WLANimage.invalidate();

    //digitalClock1.setTime24Hour((uint8_t)ap_ttm.tm_hour, (uint8_t)ap_ttm.tm_min, 0);
    digitalClock1.setTime24Hour(12,0,0);
#endif
}

void MainScreenView::SetBrightness(int value)
{
#ifndef SIMULATOR
	BrightState = value;
	//min 25000 max 0
	TIM1->CCR1 = (25000 - value);

#endif
}

void MainScreenView::toggleEmulation()
{
#ifndef SIMULATOR
	if (EmulatorButton.getState()) 	EmulatorState = true;
	else EmulatorState = false;
#endif
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

void MainScreenView::WeatherFalser(){
	//Функция делает все картинки погоды на экране неидимыми
	Moon.setVisible(false);
	Sunny.setVisible(false); //sunny = clear
	Rain.setVisible(false);
	Cloudy.setVisible(false);
	Thunder.setVisible(false);
	Snow.setVisible(false);
}
