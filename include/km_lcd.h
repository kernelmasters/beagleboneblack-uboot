#ifndef _LCD_H_
#define _LCD_H_

//DECLARE_GLOBAL_DATA_PTR;
/****HARDWARE CONNECTIONS*********/
#define LCD_D4	44	//-->P8.43
#define LCD_D5	45	//-->P8.44
#define LCD_D6	46	//-->P8.45
#define	LCD_D7	47	//-->P8.46
#define LCD_RS	86	//-->P8.39
#define LCD_RW	87	//-->P8.41
#define LCD_EN	88	//-->P8.42
#define BUZZ	9	//-->P8.40
/********************************/
enum{
	OUT=0,
	IN
};

enum{
	OFF=0,
	ON
};

#define DELAY_EN	1
#define HD44780_CONF_BUS	HD44780_FUNC_BUS_4BIT
#define HD44780_CONF_LINES	HD44780_FUNC_LINES_2
#define HD44780_CONF_FONT	HD44780_FUNC_FONT_5x8
#define HD44780_DISP_LENGTH	16
#define HD44780_DISP_ROWS	2
#define HD44780_CONF_SCROLL_MS	20

/************************** COMMANDS ***********************************/
#define HD44780_CMD_RESET            	0x30     	/*!< Resets display - used in init 3x */
#define HD44780_CMD_CLEAR            	0x01     	/*!< Clears display */
#define HD44780_CMD_RETURN_HOME      	0x02     	/*!< Sets DDRAM pointer to 0 */
#define HD44780_CMD_ENTRY_MODE       	0x04     	/*!< Sets how the pointer is updated after a character write */
#define HD44780_CMD_DISPLAY          	0x08     	/*!< Display settings */
#define HD44780_CMD_SHIFT            	0x10     	/*!< Cursor and display movement */
#define HD44780_CMD_FUNCTION         	0x20     	/*!< Screen type setup */
#define HD44780_CMD_CGRAM_ADDR       	0x40     	/*!< Sets CGRAM address */
#define HD44780_CMD_DDRAM_ADDR       	0x80     	/*!< Sets DDRAM address */

/*********************** ENTRY_MODE Command parameters *******************/
#define HD44780_ENTRY_SHIFT_DISP 	0x01	 		/*!< Shift display */
#define HD44780_ENTRY_SHIFT_CURS 	0x00	 		/*!< Shift cursor */
#define HD44780_ENTRY_ADDR_INC   	0x02     	/*!< Increments pointer */
#define HD44780_ENTRY_ADDR_DEC   	0x00	 		/*!< Decrements pointer */

/*********************** DISPLAY Command parameters **********************/
#define HD44780_DISP_ON       		0x04      /*!< Enables the display */
#define HD44780_DISP_OFF      		0x00      /*!< Disables the display */
#define HD44780_DISP_CURS_ON  		0x02      /*!< Enables cursor */
#define HD44780_DISP_CURS_OFF 		0x00      /*!< Disables cursor */
#define HD44780_DISP_BLINK_ON		0x01      /*!< Enables cursor blinking */
#define HD44780_DISP_BLINK_OFF  	0x00      /*!< Disables cursor blinking */

/****************************** SHIFT Command parameters **********************/
#define HD44780_SHIFT_DISPLAY    	0x08      /*!< Shifts the display or shifts the cursor if not set */
#define HD44780_SHIFT_CURSOR    	0x00      /*!< Shifts the display or shifts the cursor if not set */
#define HD44780_SHIFT_RIGHT      	0x04      /*!< Shift to the right */
#define HD44780_SHIFT_LEFT      	0x00      /*!< Shift to the left  */

/******************************* FUNCTION Command parameters *****************/
#define HD44780_FUNC_BUS_8BIT  		0x10      /*!< 8 bit bus */
#define HD44780_FUNC_BUS_4BIT  		0x00      /*!< 4 bit bus */
#define HD44780_FUNC_LINES_4   		(0x08+0x54)      /*!< 4 lines */
#define HD44780_FUNC_LINES_3   		(0x08+0x14)      /*!< 3 lines */
#define HD44780_FUNC_LINES_2   		0x08      /*!< 2 lines */
#define HD44780_FUNC_LINES_1   		0x00      /*!< 1 line */
#define HD44780_FUNC_FONT_5x10 		0x04      /*!< 5x10 font */
#define HD44780_FUNC_FONT_5x8  		0x00      /*!< 5x8 font */

/******************************* Busy Flag - actually not used *****************/
#define HD44780_BUSY_FLAG        	0x80      /*!< Busy flag */

/******************************************************************************/
#define hd44780_clear()                       	  hd44780_wr_cmd( HD44780_CMD_CLEAR )
#define hd44780_home()                        	  hd44780_wr_cmd( HD44780_CMD_RETURN_HOME )
#define hd44780_entry( inc_dec, shift )           hd44780_wr_cmd( ( HD44780_CMD_ENTRY_MODE | inc_dec | shift ) & 0x07 )
#define hd44780_display( on_off, cursor, blink )  hd44780_wr_cmd( ( HD44780_CMD_DISPLAY | on_off | cursor | blink ) & 0x0F )
#define hd44780_shift( inc_dec, shift )           hd44780_wr_cmd( ( HD44780_CMD_SHIFT | inc_dec | shift ) & 0x1F )
#define hd44780_function( bus, lines, font )      hd44780_wr_cmd( ( HD44780_CMD_FUNCTION | bus | lines | font ) & 0x3F )
#define hd44780_cgram_addr( addr )                hd44780_wr_cmd( HD44780_CMD_CGRAM_ADDR | ( addr & 0x3F ) )
#define hd44780_ddram_addr( addr )                hd44780_wr_cmd( HD44780_CMD_DDRAM_ADDR | ( addr & 0x7F ) )
#define hd44780_write_char( c )                   hd44780_wr_data( c & 0xff )

/*******************************************************************************************/
void Init_LCD(void);
void LCD_Write_High_Nibble(unsigned char data );
void LCD_Write_Low_Nibble(unsigned char data );
void HD44780_EN(char Mode);
void hd44780_wr_cmd( unsigned char cmd );
void hd44780_wr_data( unsigned char data );
void hd44780_write( unsigned char data );
void Delay_HD44780(unsigned int Delay);
void HD44780_PutChar(unsigned char c);
void HD44780_GotoXY(unsigned char x, unsigned char y);
void HD44780_PutStr(char *str);
void HD44780_Str_XY(char X, char Y, char *Ptr);
void HD44780_ClrScr(void);
int lcd_bootmenu(int);
void Lcd_Init(void);
void All_Test_Cases(void);
/******************************************************/
void Init_Lcd_Hardware(void);
int Export_Gpio(int Pin);
int Set_Gpio(int Pin,char Mode);
int Write_Gpio_Value(int Pin, int Val);
/******************************************************/

#endif
