#ifndef HA_SCREENPRESENTER_HPP
#define HA_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HA_screenView;

class HA_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    HA_screenPresenter(HA_screenView& v);

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

#ifndef SIMULATOR
    static void test(Sensor *s, uint8_t n) {};

    virtual void addNewSensor(Sensor sens);
#endif

    virtual ~HA_screenPresenter() {};


private:
    HA_screenPresenter();

    HA_screenView& view;
};

#endif // HA_SCREENPRESENTER_HPP
