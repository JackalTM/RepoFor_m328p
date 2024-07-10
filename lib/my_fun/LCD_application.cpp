/*
 * LCD_application.h
 *
 * Created: 05.05.2024 
 *  Author: Wiki
 */ 
#include "LCD_application.h"
#ifdef _INC_LCD_APPLICATION

/*****************************************************************************************************
 * @name		void
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_application: LCD_DataControl, LCD_016N002B_CFH_ET
 * @brief		Constructor for class LCD_application: LCD_DataControl, LCD_016N002B_CFH_ET
 * @param[in]	row_n Amount of rows
 * @param[in]   col_n Amount od columns
 * @note		void
 * @return		void
 */
LCD_application::LCD_application(uint8_t row_n, uint8_t col_n): 
	LCD_DataControl(row_n, col_n), 
	LCD_016N002B_CFH_ET(row_n, col_n),
    row_n(row_n), col_n(col_n)
{;}
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_application: LCD_DataControl, LCD_016N002B_CFH_ET
 * @brief		Deconstructor for class LCD_application: LCD_DataControl, LCD_016N002B_CFH_ET
 * @param[in]	void
 * @note		void
 * @return		void
 */
LCD_application::~LCD_application(){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		InitializeDevice: LCD_016N002B_CFH_ET.Initialize_8bitInterface()
 * @brief		Thid method use inheritanced method from device class
 * @param[in]	void
 * @note		Method to call is Initialize_8bitInterface()
 * @return		void
 */
void LCD_application::InitializeDevice(void)
{
    Initialize_8bitInterface();
}
//====================================================================================================

/*****************************************************************************************************
 * @name		ClearDisplayData
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
void LCD_application::ClearDisplayData(void)
{
	LCD_DataControl::ClearData();
	LCD_016N002B_CFH_ET::ClearDisplay();
}
//====================================================================================================

/*****************************************************************************************************
 * @name		ReturnCursorHome
 * @brief		Thid method call children methods
 * @param[in]	void
 * @note		Thid method clear wirtual data and LCD data 
 * @return		void
 */
void LCD_application::ReturnCursorHome(void)
{
	LCD_DataControl::ReturnHome(); 
	LCD_016N002B_CFH_ET::ReturnHome(); 
}
//====================================================================================================

/*****************************************************************************************************
 * @name		OrderDisplay_IRQ
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
void LCD_application::OrderDisplay_IRQ(uint8_t data)
{
    if(_display_data_order_active == FALSE)
    {
        _data_from_keypad_IRQ = data;
        _display_data_order_active = TRUE;
    }
    else{;}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintStr
 * @brief		Put array of string on LCD display
 * @param[in]	arrString	String array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		void	
 * @return		void
 */
void LCD_application::PrintStr(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i, tByte;

	// 1. Set cursor placement for LCD.
	LCD_DataControl::SetCurrsorToPosition(&n_row, &n_col);
	if(n_col == 0x00)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_1);}
	else // (n_col == 0x01)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_2);}

	// 2. Cheque posible characters amount. And asign lenght for loop.
	strLen = LCD_DataControl::PrintStr(arrString, strLen);

	// 3. Send data for LCD display.
	for(i=0; i<strLen; i++)
	{
		tByte = (uint8_t)arrString[i];
		LCD_016N002B_CFH_ET::PutData(tByte);
	}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintStr
 * @brief		Put array of string on LCD display
 * @param[in]	arrString	String array buffer
 * @param[in]	strLen		String lenght
 * @param[in]	n_row		Row place to display
 * @param[in]	n_col		Column place to display
 * @note		void	
 * @return		void
 */
void LCD_application::PrintStr(char* arrString, uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i, tByte;

	// 1. Set cursor placement for LCD.
	LCD_DataControl::SetCurrsorToPosition(&n_row, &n_col);
	if(n_col == 0x00)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_1);}
	else // (n_col == 0x01)
	{	LCD_016N002B_CFH_ET::SetCurrsorToPosition(n_row, DISPLAY_LINE_2);}

	// 2. Cheque posible characters amount. And asign lenght for loop.
	strLen = LCD_DataControl::PrintStr(arrString, strLen);

	// 3. Send data for LCD display.
	for(i=0; i<strLen; i++)
	{
		tByte = (uint8_t)arrString[i];
		LCD_016N002B_CFH_ET::PutData(tByte);
	}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Order_PrintStr
 * @brief		void
 * 
 * @param[in]	arrString
 * @param[in]	strLen
 * @param[in]	n_row
 * @param[in]	n_col
 * 
 * @note		void
 * @return		void
 */
void LCD_application::Order_PrintStr(char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i=0;

	if(_display_data_order_active == false)	
	{ 	
		if(strLen > 16) {strLen = 16;}
		else{;}

		while(i<strLen)
		{	
			_arrBuffer[i] = arrString[i];
			i++;
		}

		_strLen = strLen;
		_n_row = n_row;
		_n_col = n_col;
		
		_display_data_order_active = true;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Execute_PrintStr
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
void LCD_application::Execute_PrintStr(void)
{
	if(_display_data_order_active == true)	
	{ 	
		PrintStr(_arrBuffer, _strLen, _n_row, _n_col);

		_display_data_order_active = false;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		DisplayDataMenagment
 * @brief		Cyclical call for display data 
 * @note		Depend on key presed diffrent operation is taken
 */
void LCD_application::MenuTest(void)
{
	uint8_t tData;

	if(_display_data_order_active == true)
	{	tData = _data_from_keypad_IRQ;

		switch (tData)
		{
		case KEYCODE_10: // STOP
			ClearDisplayData();

			PrintStr("RED", 3, 0, 0);
			PrintStr("BLU", 3, 0, 1);
			break;

		case KEYCODE_11: // GO
			ReturnCursorHome();
			break;

		case KEYCODE_12: // LOCK
			PrintStr("Ticket 1", 8, LCD_APP_ROW_START, 0);
			break;

		case KEYCODE_13: // ON / OFF
			PrintStr("Ticket 2", 8, LCD_APP_ROW_START, 1);
			break;

		case KEYCODE_14: // ESC
			;
			break;

		case KEYCODE_15: // ENT
			;
			break;
		
		default:
			LCD_DataControl::PutOneChar(tData);
			LCD_016N002B_CFH_ET::PutData(tData);
			break;
		}

		_display_data_order_active = FALSE;
	}
	else{;}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		MenuTwoTeamsIncrease
 * @brief		void
 * @note		void
 */
void LCD_application::MenuTwoTeamsIncrease(void)
{
	uint8_t tData;

	if(_display_data_order_active == true)
	{	tData = _data_from_keypad_IRQ;

		switch (tData)
		{
		case KEYCODE_10: // STOP
			ClearDisplayData();

			PrintStr("RED", 3, 0, 0);
			PrintStr("BLU", 3, 0, 1);
			break;

		case KEYCODE_11: // GO
			ReturnCursorHome();
			break;

		case KEYCODE_12: // LOCK
			PrintStr("Ticket 1", 8, LCD_APP_ROW_START, 0);
			break;

		case KEYCODE_13: // ON / OFF
			PrintStr("Ticket 2", 8, LCD_APP_ROW_START, 1);
			break;

		case KEYCODE_14: // ESC
			;
			break;

		case KEYCODE_15: // ENT
			;
			break;
		
		default: // For key code fom (0 to 9)
			break;
		}

		_display_data_order_active = FALSE;
	}
	else{;}
}
//====================================================================================================
#endif // _INC_LCD_APPLICATION
//====================================================================================================