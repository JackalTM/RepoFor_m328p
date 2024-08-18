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
 * @note		Chldren class initialization is taken
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
 * @brief		LCD screen data is cleared
 * @param[in]	void
 * @note		Thid method clear virtual data and LCD data 
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
 * @brief		Cursor is moved to home position 0,0
 * @param[in]	void
 * @note		Thid method move cursor to home in virtual data and LCD data 
 * @return		void
 */
void LCD_application::ReturnCursorHome(void)
{
	LCD_DataControl::ReturnHome(); 
	LCD_016N002B_CFH_ET::ReturnHome(); 
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Order_PrintChar
 * @brief		Data is saved for latter display execute
 * @param[in]	data of type uint8_t
 * @note		Usefful in IRQ data display order
 * @return		void
 */
void LCD_application::Order_PrintChar(uint8_t data)
{
    if(_display_data_order_active == false)
    {
        _data_from_keypad_IRQ = data;
        _display_data_order_active = true;
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
 * @brief		String data is saved for latter data display
 * 
 * @param[in]	arrString Constant array of chars for LCD display
 * @param[in]	strLen Lenght of that array of chars
 * @param[in]	n_row Row where start to put data 
 * @param[in]	n_col Column where start to put data
 * 
 * @note		This method is usefull in IRQ str diplsy order
 * @return		void
 */
void LCD_application::Order_PrintStr(const char arrString[], uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i=0;

	if(_display_data_order_active == false)	
	{ 	
		if(strLen > 16) {strLen = 16;}
		else{;}

		while(i < strLen)
		{	_arrBuffer[i] = arrString[i];
			i++;}

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
 * @name		Order_PrintStr
 * @brief		String data is saved for latter data display
 * 
 * @param[in]	arrString Pointer to array of chars for LCD display
 * @param[in]	strLen Lenght of that array of chars
 * @param[in]	n_row Row where start to put data 
 * @param[in]	n_col Column where start to put data
 * 
 * @note		This method is usefull in IRQ str diplsy order
 * @return		void
 */
void LCD_application::Order_PrintStr(char* arrString, uint8_t strLen, uint8_t n_row, uint8_t n_col)
{
	uint8_t i=0;

	if(_display_data_order_active == false)	
	{ 	
		if(strLen > 16) {strLen = 16;}
		else{;}

		while(i<strLen)
		{	_arrBuffer[i] = arrString[i];
			i++;}

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
 * @brief		Ordered string data is executed
 * @param[in]	void
 * @note		When data order is in IRQ and LCD display in main aplication
 * @return		void
 */
void LCD_application::Execute_PrintStr(void)
{
	if(_display_data_order_active == true)	
	{ 	
		PrintStr(_arrBuffer, _strLen, _n_row, _n_col);
		_strLen = 0;

		_display_data_order_active = false;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintInt
 * @brief		Print int data of type uint8_t in certain place
 * @param[in]	number Number to put on LCD display type uint8_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		Int data is converted to string and then displayed
 * @return		void
 */
void LCD_application::PrintInt(uint8_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars_SRC[TYPE_DEC_uin8_t];
	char arr_chars_DST[TYPE_DEC_uin8_t];

	_Convert.NumToString(number, arr_chars_SRC, TYPE_DEC_uin8_t);
	_Convert.ToStrFormatDec(arr_chars_SRC, TYPE_DEC_uin8_t, arr_chars_DST, TYPE_DEC_uin8_t);
	PrintStr(arr_chars_DST, TYPE_DEC_uin8_t, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintInt
 * @brief		Print int data of type uint16_t in certain place
 * @param[in]	number Number to put on LCD display, type uint16_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		Int data is converted to string and then displayed
 * @return		void
 */
void LCD_application::PrintInt(uint16_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars_SRC[TYPE_DEC_uint16_t];
	char arr_chars_DST[TYPE_DEC_uint16_t];

	_Convert.NumToString(number, arr_chars_SRC, TYPE_DEC_uint16_t);
	_Convert.ToStrFormatDec(arr_chars_SRC, TYPE_DEC_uin8_t, arr_chars_DST, TYPE_DEC_uint16_t);
	PrintStr(arr_chars_DST, TYPE_DEC_uint16_t, n_row, n_col);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Order_PrintInt
 * @brief		Data is prepared for print, int is converted to string format
 * @param[in]	number Number to put on LCD display type uint8_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		This method is usefull in IRQ str display order
 * @return		void
 */
void LCD_application::Order_PrintInt(uint8_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars_SRC[TYPE_DEC_uin8_t];
	uint8_t i;

	if(_display_data_order_active == false)	
	{ 	_Convert.NumToString(number, (char*)arr_chars_SRC, TYPE_DEC_uin8_t);

		i = 0;
		while(i < TYPE_DEC_uin8_t)
		{	_arrBuffer[i] = arr_chars_SRC[i];
			i++;}

		_strLen = TYPE_DEC_uin8_t;
		_n_row = n_row;
		_n_col = n_col;
		
		_display_data_order_active = true;
	}
	else	
	{ 	return; }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		Order_PrintInt
 * @brief		Data is prepared for print, int is converted to string format
 * @param[in]	number Number to put on LCD display type uint8_t
 * @param[in]	n_row LCD row index when start display number
 * @param[in]	n_col LCD column index when start display number
 * @note		This method is usefull in IRQ str display order
 * @return		void
 */
void LCD_application::Order_PrintInt(uint16_t number, uint8_t n_row, uint8_t n_col)
{
	char arr_chars_SRC[TYPE_DEC_uint16_t];
	uint8_t i;

	if(_display_data_order_active == false)	
	{ 	_Convert.NumToString(number, (char*)arr_chars_SRC, TYPE_DEC_uint16_t);

		i = 0;
		while(i < TYPE_DEC_uint16_t)
		{	_arrBuffer[i] = arr_chars_SRC[i];
			i++;}

		_strLen = TYPE_DEC_uint16_t;
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
 * @brief		Converted number to string is executed
 * @param[in]	void
 * @note		This method is same like Execute_PrintStr
 * @return		void
 */
void LCD_application::Execute_PrintInt(void)
{
	if(_display_data_order_active == true)	
	{ 	
		PrintStr(_arrBuffer, _strLen, _n_row, _n_col);
		_strLen = 0;

		_display_data_order_active = false;
	}
	else	
	{ 	return; }
}
//====================================================================================================

#endif // _INC_LCD_APPLICATION
//====================================================================================================