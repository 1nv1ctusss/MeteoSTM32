#include <gui/ha_screen_screen/HA_screenView.hpp>
#include <gui/ha_screen_screen/HA_screenPresenter.hpp>

HA_screenPresenter::HA_screenPresenter(HA_screenView& v)
    : view(v)
{

}

void HA_screenPresenter::activate()
{
  ModelListener::model->HAScreenActive();
}

void HA_screenPresenter::deactivate()
{

}

#ifndef SIMULATOR
void HA_screenPresenter::addNewSensor(Sensor sens)
{

}
#endif
