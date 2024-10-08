/*
 * LCD_application.h
 *
 * Created: 17.05.2024 
 *  Author: Wiki
 */
#include "converion_methods.h"
#ifdef _INC_CONVERSION_METHODS

/*****************************************************************************************************
 * @name		  void
 * @brief		  void
 * @param[in]	void
 * @note		  void
 * @return		void
 */
//====================================================================================================

/*****************************************************************************************************
 * @name		  itoa_simple_helper
 * @brief		  void
 * @param[in]	dest Pointer to destination array with strig data 
 * @note		  void
 * @return		void
 */
char* NumbersConversion::itoa_simple_helper(char *dest, int i) 
{
  if (i <= -10) 
  {
    dest = itoa_simple_helper(dest, i/10);
  }
  
  *dest++ = '0' - i%10;
  return dest;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  itoa_simple
 * @brief		  void
 * @param[in]	dest Pointer to destination array with strig data 
 * @note		  void
 * @return		void
 */
char* NumbersConversion::itoa_simple(char *dest, int i) 
{
  char *s = dest;
  if (i < 0) 
  {
    *s++ = '-';
  } 
  else 
  {
    i = -i;
  }
  *itoa_simple_helper(s, i) = '\0';
  return dest;
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  Uint_to_str_dec
 * @brief		  Recurent function to convert number of type int to string format
 * @param[in]	pStr Pointer to destination array with strig data 
 * @param[in] uint Number to convert into string
 * @note		  void
 * @return		Pointer to next addr where char will be placed
 */
 char* NumbersConversion::Uint_to_str_dec(char *pStr, uint8_t uint)
{
  _Str_n++;
  if(_Str_n < _StrMax)
  {// Only when char array max len is not reached
    if (uint >= 10) 
    {
      pStr = Uint_to_str_dec(pStr, uint/10);
    }
    
    *pStr++ = '0' + (uint%10);
    return pStr;
  }
  else
  {// char array max lenght is reached then return 
    return pStr;
  }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  Uint_to_str_hex
 * @brief		  Recurent function to convert number of type int to string format
 * @param[in]	pStr Pointer to destination array with strig data 
 * @param[in] uint Number to convert into string
 * @note		  void
 * @return		Pointer to next addr where char will be placed
 */
 char* NumbersConversion::Uint_to_str_hex(char *pStr, uint8_t uint)
{
  _Str_n++;
  if(_Str_n < _StrMax)
  {// Only when max len is not reached
    if (uint >= 0x10) 
    {
      pStr = Uint_to_str_hex(pStr, uint/0x10);
    }
    uint = (uint%0x10);

  // In ASCI: '7'(55) + 10 = 'A'(65)
  // Specyfic calculation for this aspect
    if(uint > 9)  { uint = ('7' + uint);} // '7' + 10 = 'A'
    else          { uint = ('0' + uint);}
    
    *pStr++ = uint;

    return pStr;
  }
  else
  {// char array max lenght is reached then return 
    return pStr;
  }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		FormatConvert
 * @brief		Constructor
 */
FormatConvert::FormatConvert(void){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		~FormatConvert
 * @brief		Deconstructor
 */
FormatConvert::~FormatConvert(){;}
//====================================================================================================

/*****************************************************************************************************
 * @name		  SetCharArray
 * @brief		  Fill array with input character 
 * @param[in]	arrChar Pointer to character array to fill with.
 * @param[in]	strLen  Character array lenght
 * @param[in]	inChar  Character to fill array with
 * @note		  void
 * @return		void
 */
void FormatConvert::_SetCharArray(char arrChar[], uint8_t strLen, char inChar)
{
  uint8_t i;
  for(i=0; i<strLen; i++) { arrChar[i] = inChar;}
}
//====================================================================================================

/*****************************************************************************************************
 * @name		NumToString
 * @brief		This method convert number to string in format decimal
 * 
 * @param[in] number Number that will be converted to string
 * @param[in]	arrChar[] Pointer to array of chars
 * @param[in] DecimalNumberStringSize destination string size
 * 
 * @note		void
 * @return	void
 */
void FormatConvert::NumToString(uint8_t number, char arrChar[], DecimalNumberStringSize strSize)
{
  _SetCharArray(arrChar, strSize, ' ');
  NumbersConversion::SetMaxStringLenght(strSize);
  *(NumbersConversion::Uint_to_str_dec(arrChar, number))  = '\0';
}
//====================================================================================================

/*****************************************************************************************************
 * @name		NumToString
 * @brief		This method convert number to string in format hexadecimal
 * 
 * @param[in] number Number that will be converted to string
 * @param[in]	arrChar[] Pointer to array of chars
 * @param[in] HexadeciNumberStringSize destination string size
 * 
 * @note		void
 * @return	void
 */
void FormatConvert::NumToString(uint8_t number, char arrChar[], HexadeciNumberStringSize strSize)
{
  _SetCharArray(arrChar, strSize, ' ');
  NumbersConversion::SetMaxStringLenght(strSize);
  *(NumbersConversion::Uint_to_str_hex(arrChar, number))  = '\0';
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  ToStrFormat
 * @brief		  Convert string from front to end of a string array 
 * 
 * @param[in]	arrSRC Pointer to source array 
 * @param[in]	lenSRC Lenght of source array 
 * @param[in]	arrDST Pointer to destination array 
 * @param[in]	lenDST Lenght of destination array 
 * 
 * @note		  Input lenght need to be widhout '\0' marker on the end
 *            This string is formating specyfic
 * @return		void
 */

void FormatConvert::ToStrFormatDec(char arrSRC[], uint8_t lenSRC, char arrDST[], uint8_t lenDST)
{
  uint8_t i, j;
  char tChar;

  // destination array of chars is prepared for conversion
  for(i=0; i<lenDST; i++) { arrDST[i] = ' '; }

  i = lenSRC - 1;
  j = lenDST - 1; // Varibale in overflof and it will be 0xFF
  while((i < lenSRC) && (j < lenDST))
  {
    tChar = arrSRC[i];
    i--;

    //if(tChar == '\0') { break; }
    //else{;}

    if((tChar >= '0') && (tChar <= '9'))
    {
      arrDST[j] = tChar;
      j--;
    }
    else{;}
  }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  ToStrFormat
 * @brief		  Convert string from front to end of a string array 
 * 
 * @param[in]	arrSRC Pointer to source array 
 * @param[in]	lenSRC Lenght of source array 
 * @param[in]	arrDST Pointer to destination array 
 * @param[in]	lenDST Lenght of destination array 
 * 
 * @note		  Input lenght need to be widhout '\0' marker on the end
 *            This string is formating specyfic
 * @return		void
 */

void FormatConvert::ToStrFormatHex(char arrSRC[], uint8_t lenSRC, char arrDST[], uint8_t lenDST)
{
  uint8_t i, j;
  char tChar;

  // destination array of chars is prepared for conversion
  for(i=0; i<lenDST; i++) { arrDST[i] = ' '; }

  i = lenSRC - 1;
  j = lenDST - 1; // Varibale in overflof and it will be 0xFF
  while((i < lenSRC) && (j < lenDST))
  {
    tChar = arrSRC[i];
    i--;

    //if(tChar == '\0') { break; }
    //else{;}

    if((tChar >= '0') && (tChar <= '9'))
    {
      arrDST[j] = tChar;
      j--;
    }
    else if((tChar >= 'A') && (tChar <= 'F'))
    {
      arrDST[j] = tChar;
      j--;
    }
    else if((tChar >= 'a') && (tChar <= 'f'))
    {
      arrDST[j] = tChar;
      j--;
    }
    else{;}
  }
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  TimeToStr
 * @brief		  Time data format convert to string format
 * @param[in]	pTime Pointer to data_time::conv_time_t fromat data
 * @note		  void
 * @return		void
 */
void FormatConvert::TimeToStr(data_time::time_t *pTime, char arrChar[])
{
  char tArray[8];
  NumToString(pTime->hour, (char*)&tArray[0], TYPE_DEC_time_t);
  NumToString(pTime->minute, (char*)&tArray[3], TYPE_DEC_time_t);
  NumToString(pTime->second, (char*)&tArray[7], TYPE_DEC_time_t);

  ToStrFormatDec((char*)&tArray[0], 2, (char*)&arrChar[0], 2);
  ToStrFormatDec((char*)&tArray[3], 2, (char*)&arrChar[3], 2);
  ToStrFormatDec((char*)&tArray[7], 2, (char*)&arrChar[7], 2);

  arrChar[2] = ':';
  arrChar[6] = ':';
}
//====================================================================================================

/*****************************************************************************************************
 * @name		  TimeToStr
 * @brief		  Time data format convert to string format
 * @param[in]	hour Value of a hour
 * @param[in] minute Value of a minute 
 * @param[in] second Value of a second
 * @note		  void
 * @return		void
 */
void FormatConvert::TimeToStr(uint8_t hour, uint8_t minute, uint8_t second, char arrChar[])
{
  char tArray[8];
  NumToString(hour, (char*)&tArray[0], TYPE_DEC_time_t);
  NumToString(minute, (char*)&tArray[3], TYPE_DEC_time_t);
  NumToString(second, (char*)&tArray[7], TYPE_DEC_time_t);

  ToStrFormatDec((char*)&tArray[0], 2, (char*)&arrChar[0], 2);
  ToStrFormatDec((char*)&tArray[3], 2, (char*)&arrChar[3], 2);
  ToStrFormatDec((char*)&tArray[7], 2, (char*)&arrChar[7], 2);

  arrChar[2] = ':';
  arrChar[6] = ':';
}
//====================================================================================================

//====================================================================================================
#endif // _INC_CONVERSION_METHODS
//====================================================================================================