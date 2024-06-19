/*
 * x01_menu.h
 *
 * Created: 12.06.2024 
 *  Author: Wiki
 */ 
#include "x01_menu.h"
#ifdef _INC_x01_MENU_H

/*****************************************************************************************************
 * @name		Main_Display
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
void MenuApplication::Main_Display(void)
{
	Ref_LCD_application.MenuTest();
}
//====================================================================================================

/*****************************************************************************************************
 * @name		IRQ_TIM1_Display
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
void MenuApplication::IRQ_TIM1_Display(void)
{
    static uint8_t n_TIMER1, someNum;
    switch (n_TIMER1)
	{
	case 0x00:
		n_TIMER1 = 0x11;

		//RefConvertTime.NumToString(someNum, arrChars1, TYPE_DEC_uin8_t);
		//RefConvertTime.ToStrFormatDec(arrChars1, 3, arrChars2, 3);

		Ref_LCD_application.PrintStr(arrChars2, 4,  6, 0);
		break;

	case 0x11:
		n_TIMER1 = 0x22;
		
		//RefConvertTime.NumToString(someNum, arrChars1, TYPE_HEX_uin8_t);
		//RefConvertTime.ToStrFormatHex(arrChars1, 3, arrChars2, 3);

		Ref_LCD_application.PrintStr(arrChars2, 4,  6, 1);
	
		someNum++;
		n_TIMER1 = 0x00;
		break;

	default:
		someNum++;
		n_TIMER1 = 0x00;
		break;
	}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		IRQ_TIM2_Keypad
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
void MenuApplication::IRQ_TIM2_Keypad(void)
{
	_keypad_state = RefKeypad4x4.KeypadStateEvaluation();
	if(_keypad_state != KEYCODE_NOPRESS)
	{
		if(_keypad_state == KEYPAD_KEYPAD_STATE_PULS)
		{	Ref_LCD_application.OrderDisplay_IRQ(RefKeypad4x4.GetKeyCode()); }
		else{;}
	}
	else{;}
}
//====================================================================================================

//====================================================================================================
#endif // _INC_x01_MENU_H
//====================================================================================================