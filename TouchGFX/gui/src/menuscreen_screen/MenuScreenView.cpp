#include <gui/menuscreen_screen/MenuScreenView.hpp>

#ifndef SIMULATOR
#include "stm32h7xx_hal.h"
#endif

Unicode::UnicodeChar keyboardBuffer[2][18]; // add
uint8_t keyboardSelection = 0; // add

MenuScreenView::MenuScreenView()
{

}

void MenuScreenView::setupScreen()
{
    MenuScreenViewBase::setupScreen();
}

void MenuScreenView::tearDownScreen()
{
    MenuScreenViewBase::tearDownScreen();
}

void MenuScreenView::keyboardSelected(uint8_t value)
{
	keyboardSelection = value;
}

void MenuScreenView::updateScreen()
{
	if (Unicode::strlen(keyboardBuffer[0]) > 0)
	{
		memset(&textAreaSsidBuffer, 0, TEXTAREASSID_SIZE);
		Unicode::strncpy(textAreaSsidBuffer, keyboardBuffer[0], TEXTAREASSID_SIZE - 1);
		textAreaSsidBuffer[TEXTAREASSID_SIZE - 1] = '\0'; // make sure last index is null
		textAreaSsid.invalidate();
	}
	if (Unicode::strlen(keyboardBuffer[1]) > 0)
	{
		char temp[18] = { 0 };
		uint8_t n = (uint8_t)Unicode::strlen(keyboardBuffer[1]);
		Unicode::UnicodeChar unicodeBuf[18] = { 0 };

		memset(&temp, '*', n);

		Unicode::fromUTF8((uint8_t*)temp, unicodeBuf, Unicode::strlen(keyboardBuffer[1]));

		memset(&textAreaPwBuffer, 0, TEXTAREAPW_SIZE);
		Unicode::strncpy(textAreaPwBuffer, unicodeBuf, TEXTAREAPW_SIZE - 1);
		textAreaPwBuffer[TEXTAREAPW_SIZE - 1] = '\0'; // make sure last index is null
		textAreaPw.invalidate();
	}
}


