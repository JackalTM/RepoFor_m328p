/*
 * LCD_data_control.h
 *
 * Created: 04.05.2024 
 *  Author: Wiki
 */ 
#include "LCD_data_control.h"
#ifdef _INC_LCD_DATA_CONTROL
/*****************************************************************************************************
 * 
*/

/*****************************************************************************************************
 * @name		void
 * @brief		void
 * @param[in]	void
 * @note		void
 * @return		void
 */
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_DataControl
 * @brief		Constructor for class LCD_DataControl
 * @param[in]	void
 * @note		void
 * @return		void
 */
LCD_DataControl::LCD_DataControl(uint8_t row_n, uint8_t col_n): _idx_row(0), _idx_col(0)
{	ClearData();}
//====================================================================================================

/*****************************************************************************************************
 * @name		LCD_DataControl
 * @brief		Deconstructor for class LCD_DataControl
 * @param[in]	void
 * @note		void
 * @return		void
 */
LCD_DataControl::~LCD_DataControl(){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		_PutData
 * @brief		void
 * @param[in]	data Input data 
 * @note		void
 * @return		Status if data was added
 */
 uint8_t LCD_DataControl::_PutDataBuffer(uint8_t data)
 {
	if(_idx_row < DISPLAY_BUFFER_MAX_ROW_AMOUT) 
	{
		_arrDisplayData[_idx_col][_idx_row] = data;
		_idx_row++;

		return TRUE;
	}
	else
	{
		if(_idx_col == DISPLAY_BUFFER_LINE_1)
		{
			_idx_row = 0;
			_idx_col = DISPLAY_BUFFER_LINE_2;
			_PutDataBuffer(data);
		} 
		else{;}
	}
	return FALSE; 
 }
//====================================================================================================

/*****************************************************************************************************
 * @name		_ClearData
 * @brief		Clear LCD data buffer 
 * @param[in]	void
 * @note		void
 */
void LCD_DataControl::ClearData(void)
{
	uint8_t i, j;

	_idx_row = 0;
	_idx_col = 0;

	for(j=0; j<DISPLAY_BUFFER_MAX_COL_AMOUT; j++)
	{	for(i=0; i<DISPLAY_BUFFER_MAX_ROW_AMOUT; i++)
		{	_arrDisplayData[j][i] = 0x00; }}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		_ReturnHome
 * @brief		Return cursor to start position
 * @param[in]	void
 * @note		void
 */
void LCD_DataControl::ReturnHome(void)
{
	_idx_row = 0;
	_idx_col = 0;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		CursorCurrentLoc
 * @brief		Gets amout of characters from current cursor place to begin of LCD
 * @param[in]	void
 * @note		
 * @return		Amount of characters from current place to begin of LCD
 */
uint8_t LCD_DataControl::AmountCharsToBegin(void)
{
	return (_idx_row + 1);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		CursorSpaceToEnd
 * @brief		Gets amout of characters from current cursor place end of LCD
 * @param[in]	void
 * @note		
 * @return		Amount of characters from current place to end of LCD
 */
uint8_t LCD_DataControl::AmountCharsToEnd(void)
{
	return (DISPLAY_BUFFER_MAX_ROW_AMOUT - _idx_row);
}
//====================================================================================================

/*****************************************************************************************************
 * @name		SetCurrsorToPosition
 * @brief		Cursor is placed to certain position
 * 
 * @param[in]	row_n Certain row is set 
 * @param[in]	col_n Certain col is set
 * 
 * @note		Data is set when input atays in range
 */
void LCD_DataControl::SetCurrsorToPosition(uint8_t* p_nRow, uint8_t* p_nCol)
{
	if(*p_nCol < DISPLAY_BUFFER_MAX_COL_AMOUT)
	{	_idx_col = *p_nCol; }
	else
	{	*p_nCol = _idx_col;}

	if(*p_nRow < DISPLAY_BUFFER_MAX_ROW_AMOUT)
	{	_idx_row = *p_nRow; }
	else
	{	*p_nRow = _idx_row;}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PutOneChar
 * @brief		void
 * @param[in]	data Input data to insert into data array
 * @note		void
 * @return		void
 */
uint8_t LCD_DataControl::PutOneChar(uint8_t data)
{
	uint8_t iMAX;

	iMAX = AmountCharsToEnd();
	if(iMAX == 0) {return FALSE;}
	else{;}

	_arrDisplayData[_idx_col][_idx_row] = data;
	_idx_row++;

	if(_idx_row > DISPLAY_BUFFER_CURRSOR_IDX_END)
	{	_idx_row = DISPLAY_BUFFER_CURRSOR_IDX_END;}
	else{;}

	return TRUE;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		PrintStr
 * @brief		Print array of characters on LCD screen
 * 
 * @param[in]	pStr Constatnt array of pointers to pint on LCD screen
 * @param[in]	strLen Lenght of a constant array of characters
 * 
 * @note		Amount of characters that will not be printed return as uint8_t
 * 				To print on certain place method SetCurrsorToPosition need to be used
 * @return		Amout of printed characters
 */
uint8_t LCD_DataControl::PrintStr(const char pStr[], uint8_t strLen)
{
	uint8_t i, iMAX;

	iMAX = AmountCharsToEnd();
	if(iMAX == 0) { return 0; }
	else{;}

	if(strLen > iMAX)
	{	strLen = iMAX;}
	else{;}

	for(i=0; i<strLen; i++)
	{
		_arrDisplayData[_idx_col][_idx_row] = pStr[i];
		_idx_row++;
	}

	if(_idx_row > DISPLAY_BUFFER_CURRSOR_IDX_END)
	{	_idx_row = DISPLAY_BUFFER_CURRSOR_IDX_END;}
	else{;}

	return strLen;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		DeletStr
 * @brief		Print array of characters on LCD screen
 * 
 * @param[in]	pStr Constatnt array of pointers to pint on LCD screen
 * @param[in]	strLen Lenght of a constant array of characters
 * 
 * @note		Amount of characters that will not be printed return as uint8_t
 * 				To print on certain place method SetCurrsorToPosition need to be used
 * @return		Amout of printed characters
 */
uint8_t LCD_DataControl::DeletStr(const char pStr[], uint8_t strLen)
{
	uint8_t i, iMAX;

	iMAX = AmountCharsToBegin();
	if(iMAX == 0) { return 0; }
	else{;}

	if(strLen > iMAX)
	{	strLen = iMAX;}
	else{;}

	for(i=0; i<strLen; i++)
	{
		_arrDisplayData[_idx_col][_idx_row] = pStr[i];
		_idx_row--;
	}

	if(_idx_row > DISPLAY_BUFFER_CURRSOR_IDX_END)
	{	_idx_row = DISPLAY_BUFFER_CURRSOR_IDX_END;}
	else{;}

	return strLen;
}
//====================================================================================================
#endif // _INC_LCD_DATA_CONTROL
//====================================================================================================