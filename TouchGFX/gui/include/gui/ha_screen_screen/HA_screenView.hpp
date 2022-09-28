#ifndef HA_SCREENVIEW_HPP
#define HA_SCREENVIEW_HPP

#include <gui_generated/ha_screen_screen/HA_screenViewBase.hpp>
#include <gui/ha_screen_screen/HA_screenPresenter.hpp>

class HA_screenView : public HA_screenViewBase
{
public:
    HA_screenView();
    virtual ~HA_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void scrollList1UpdateItem(ListElementContainer& item, int16_t itemIndex);
protected:
};

#endif // HA_SCREENVIEW_HPP
