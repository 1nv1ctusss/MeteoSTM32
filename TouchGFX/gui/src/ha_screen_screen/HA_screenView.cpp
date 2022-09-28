#include <gui/ha_screen_screen/HA_screenView.hpp>

#ifndef SIMULATOR
#include "Meteo.pb.h"
#endif


void HA_screenView::scrollList1UpdateItem(ListElementContainer& item, int16_t itemIndex)
{
	#ifndef SIMULATOR
	Unicode::UnicodeChar name_buf[30] = {0};
	Unicode::UnicodeChar unit_buf[5] = {0};
	extern Array sensors;
	scrollList1.setNumberOfItems(sensors.used);
	scrollList1.invalidate();

	if((size_t)itemIndex < sensors.used)
	{
		Unicode::fromUTF8((const uint8_t*)sensors.array[itemIndex].friendly_name, name_buf, 30);
		Unicode::fromUTF8((const uint8_t*)sensors.array[itemIndex].unit, unit_buf, 5);
		//item.set_value(sensors.array[itemIndex].value);
	}
	else
	{
		Unicode::fromUTF8((const uint8_t*)"-", name_buf, 30);
		Unicode::fromUTF8((const uint8_t*)"-", unit_buf, 5);
		//item.set_value(sensors.array[itemIndex].value);
	}
    item.set_name(name_buf);
    item.set_unit(unit_buf);
	#endif
}


HA_screenView::HA_screenView()
{

}

void HA_screenView::setupScreen()
{
  HA_screenViewBase::setupScreen();
  //scrollList1.setNumberOfItems(1);
  //scrollList1.invalidate();
 /* touchgfx::Callback<HA_screenViewBase, touchgfx::DrawableListItemsInterface*, int16_t, int16_t> Callback;
  touchgfx::DrawableListItems<ListElementContainer, 2> scrollList1ListItems;
  scrollList1ListItems[0].initialize();
  scrollList1.setNumberOfItems(1);
  scrollList1.setDrawables(scrollList1ListItems, Callback);
  scrollList1.invalidate();*/
  //scrollList1UpdateItem(item, itemIndex)
}

void HA_screenView::tearDownScreen()
{
    HA_screenViewBase::tearDownScreen();
}
