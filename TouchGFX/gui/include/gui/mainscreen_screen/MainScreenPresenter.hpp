#ifndef MAINSCREENPRESENTER_HPP
#define MAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MainScreenView;

class MainScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainScreenPresenter(MainScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MainScreenPresenter() {};

    void setClimateData(int temp, int co2, int hum);
    void setOutTemp(int temp, int hum, char* weather);
//    void setOutHum(int hum);
    //void setWeather(int cond);
    void setWLANstatus();
    void setClockData(uint32_t timestamp);

private:
    MainScreenPresenter();

    MainScreenView& view;
};

#endif // MAINSCREENPRESENTER_HPP
