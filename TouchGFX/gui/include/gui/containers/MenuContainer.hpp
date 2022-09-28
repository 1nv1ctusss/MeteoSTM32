#ifndef MENUCONTAINER_HPP
#define MENUCONTAINER_HPP

#include <gui_generated/containers/MenuContainerBase.hpp>
#include <BitmapDatabase.hpp>
#include <math.h>

class MenuContainer : public MenuContainerBase
{
public:
    MenuContainer();
    virtual ~MenuContainer() {}

    virtual void initialize();

	//Adjusts the position of the text and the icon, based in the calculated offset(x)
	void offset(int16_t x)
	{
		//iconMenu.moveTo(30 + x, iconMenu.getY());
		buttonMenu.moveTo(30 + x, buttonMenu.getY());
		textMenu.moveTo(120 + x, textMenu.getY());
	}

	//The new declaration and implementation of the setY() function
	virtual void setY(int16_t y)
	{
		//set Y as normal
		MenuContainerBase::setY(y);

		const int circleRadius = 400;

		//center around middle of background
		y = y + getHeight() / 2 - 480 / 2;

		//calculate x
		float x_f = circleRadius - sqrtf((float)((circleRadius * circleRadius) - (y * y)));
		int16_t x = (int16_t)(x_f + 0.5f);

		offset(x);
	}
	void setNumber(int no)
    {
        Unicode::itoa(no, textMenuBuffer, TEXTMENU_SIZE, 20);
        switch (no % 6)
        {
        case 0:
		buttonMenu.setBitmaps(Bitmap(BITMAP_CHROMATIC_ID), Bitmap(BITMAP_CHROMATIC_ID));
            break;
        case 1:
		buttonMenu.setBitmaps(Bitmap(BITMAP_FRACTION_ID), Bitmap(BITMAP_FRACTION_ID));
            break;
        case 2:
		buttonMenu.setBitmaps(Bitmap(BITMAP_GYROSCOPE_ID), Bitmap(BITMAP_GYROSCOPE_ID));
            break;
        case 3:
		buttonMenu.setBitmaps(Bitmap(BITMAP_SEED_OF_LIFE_ID), Bitmap(BITMAP_SEED_OF_LIFE_ID));
            break;
        case 4:
		buttonMenu.setBitmaps(Bitmap(BITMAP_SETTINGS_ID), Bitmap(BITMAP_SETTINGS_ID));
            break;
        case 5:
		buttonMenu.setBitmaps(Bitmap(BITMAP_SMILE_ID), Bitmap(BITMAP_SMILE_ID));
            break;
        }
    }
protected:
};

#endif // MENUCONTAINER_HPP
