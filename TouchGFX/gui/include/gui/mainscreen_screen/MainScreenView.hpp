#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <time.h>

class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void updateTemperature(int newValue);
    virtual void updateCO2(int newValue);
    virtual void updateHumidity(int newValue);
    virtual void updateOutTemperature(int newValue);
    virtual void updateOutHumidity(int newValue);
    virtual void updateWeatherCondition(char* weather);
    virtual void SetBrightness(int value);
    virtual void toggleEmulation();
    virtual void printSpace();
    virtual void setWLANstatus();
    virtual void updateClock(uint32_t timestamp);
    virtual void WeatherFalser();
protected:
    bool wlan_status = false;
};

#endif // MAINSCREENVIEW_HPP
