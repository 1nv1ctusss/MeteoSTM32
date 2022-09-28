#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

MainScreenPresenter::MainScreenPresenter(MainScreenView& v)
    : view(v)
{

}

void MainScreenPresenter::activate()
{

}

void MainScreenPresenter::deactivate()
{

}

void MainScreenPresenter::setClimateData(int temp, int co2, int hum)
{
  view.updateCO2(co2);
  view.updateTemperature(temp);
  view.updateHumidity(hum);
  //view.updateTxt(value);
  //if(value==254) view.printSpace();
}
void MainScreenPresenter::setOutTemp(int temp, int hum, char* weather)
{
  view.updateOutTemperature(temp);
  view.updateOutHumidity(hum);
  view.updateWeatherCondition(weather);
}
//void MainScreenPresenter::setOutHum(int hum)
//{
//  view.updateOutHumidity(hum);
//}
//void MainScreenPresenter::setWeather(int cond)
//{
//  view.updateWeather(cond);
//}

void MainScreenPresenter::setWLANstatus()
{
  view.setWLANstatus();
}

void MainScreenPresenter::setClockData(uint32_t timestamp)
{
  view.updateClock(timestamp);
}
