
#include <asm/emif.h>
#include <asm/gpio.h>
#include <asm/omap_common.h>
#include <asm/omap_sec_common.h>
#include <asm/omap_mmc.h>
#include <asm/davinci_rtc.h>
#include <i2c.h>
#include <miiphy.h>
#include <cpsw.h>
#include <power/tps65217.h>
#include <power/tps65910.h>
#include <environment.h>
#include <watchdog.h>
#include <environment.h>
#include "../common/board_detect.h"
#include "board.h"
#include "hash-string.h"
#include <km_lcd.h>
#include <string.h>

#define GPIO2_BASE_ADD 0X481AC000
#define GPIO0_BASE_ADD 0X44E07000
#define GPIO1_BASE_ADD 0X4804C000
//DATA OFF SET =0X194
//OE OFF SET  =0X134
//gpio1 = (unsigned long *)0X4804C000;


#define GPIO0_DATA_SET     (*(unsigned long *)0x44E07194)
#define GPIO0_DATA_CLEAR   (*(unsigned long *)0x44E07190)

#define GPIO2_DATA_SET     (*(unsigned long *)0x481AC194)
#define GPIO2_DATA_CLEAR   (*(unsigned long *)0x481AC190)

#define GPIO1_DATA_SET     (*(unsigned long *)0x4804C194)
#define GPIO1_DATA_CLEAR   (*(unsigned long *)0x4804C190)

#define GPIO2_DIR          (*(unsigned long *)0x481AC134)
#define GPIO1_DIR          (*(unsigned long *)0x4804C134)
#define GPIO0_DIR          (*(unsigned long *)0x44E07134)
#define GPIO0_DATA_IN      (*(unsigned long *)0x44E07138)
enum status{
	STAY_BOOT=0,
	SD_CARD_BOOT,
	EMMC_BOOT,
	TFTP_BOOT,
	TFTP_KGDB,
	NFS_BOOT,
	SELF_DIAGNOSTIC_TEST

};


DECLARE_GLOBAL_DATA_PTR;

int Write_Gpio_Value(int Pin, int Val){

    
                if (Val == 1)
                GPIO1_DATA_SET  |= (1 << (Pin % 32));
                if (Val == 0)
                GPIO1_DATA_CLEAR = (1 << (Pin % 32));
        return 1;
}

int Write_Gpio_Value_Control(int Pin, int Val){

       
                if (Val == 1)
                GPIO2_DATA_SET |= (1 << (Pin % 32));
                if (Val == 0)
                GPIO2_DATA_CLEAR = (1 << (Pin % 32));
        return 1;
}

void Gpio_Init(void){

		GPIO1_DIR &= ~(1 << (44 % 32));  //set output direction
                GPIO1_DIR &= ~(1 << (45 % 32));  //set output direction
                GPIO1_DIR &= ~(1 << (46 % 32));  //set output direction
                GPIO1_DIR &= ~(1 << (47 % 32));  //set output direction     
                GPIO2_DIR &= ~(1 << (86 % 32));  //set output direction
                GPIO2_DIR &= ~(1 << (87 % 32));  //set output direction
                GPIO2_DIR &= ~(1 << (88 % 32));  //set output direction      
                GPIO0_DIR &= ~(1 <<  (9 % 32));  //set output direction
                GPIO0_DIR &= ~(1 << (10 % 32));  //set output direction       

		 GPIO0_DIR |= (1 << (11 % 32));  //set output direction
		 GPIO0_DIR |= (1 << (26 % 32));  //set output direction
		 GPIO0_DIR |= (1 << (27 % 32));  //set output direction

}



void Lcd_Init(void)
{
        int i;
            
        Gpio_Init();
        udelay(1000);
        Write_Gpio_Value_Control(LCD_EN,0);     //Clear EN
        Write_Gpio_Value_Control(LCD_RS,0);     //Clear RS
                                                                                                      
	Write_Gpio_Value_Control(LCD_RW,0);     //Clear RW
        udelay(10);                             //Tas=3uSec
        Write_Gpio_Value_Control(LCD_EN,1);     //Set   EN
        udelay(10);                             //Tas=1uSec
        Write_Gpio_Value_Control(LCD_EN,0);     //Clear EN
        udelay(10);                             //Tas=1uSec

        for(i=0;i<3;i++){
        LCD_Write_High_Nibble(HD44780_CMD_RESET);
        udelay(10);
        }

        LCD_Write_High_Nibble(HD44780_CMD_FUNCTION );
        hd44780_function( HD44780_CONF_BUS, HD44780_CONF_LINES, HD44780_CONF_FONT );
        hd44780_display( HD44780_DISP_ON, HD44780_DISP_CURS_OFF, HD44780_DISP_BLINK_OFF );
        hd44780_clear();
        hd44780_entry( HD44780_ENTRY_ADDR_INC, HD44780_ENTRY_SHIFT_CURS );
        HD44780_ClrScr();
        udelay(10);             //Tas=1uSec
}
 int lcd_bootmenu(int Boot_Selection){
               
       if(Boot_Selection==777){
                         HD44780_ClrScr();
                         HD44780_Str_XY(3,0,"Welcome to ");
                         HD44780_Str_XY(1,1,"Kernel Masters");
                         GPIO0_DATA_CLEAR = (1 <<  (9 % 32));   //clear a Data -->BUZZER ON
                          return 0;
                        }                                     
	switch(Boot_Selection){

                case STAY_BOOT:
                         HD44780_ClrScr();
                         HD44780_Str_XY(2,0,"Welcome to KM");
                         HD44780_Str_XY(0,1,"Stay at Boot Mod");
			printf("To enter bootmenu, run \"km_bootmenu\" command\n");
                        break;
                case SD_CARD_BOOT:
                         HD44780_ClrScr();
                         HD44780_Str_XY(2,0,"Welcome to KM");
                         HD44780_Str_XY(0,1,"Boot From SDcard");
                        break;
                case EMMC_BOOT:
                         HD44780_ClrScr();
                         HD44780_Str_XY(2,0,"Welcome to KM");
                         HD44780_Str_XY(0,1,"Boot From Emmc");
                        break;
                case TFTP_BOOT:
                         HD44780_ClrScr();
                         HD44780_Str_XY(2,0,"Welcome to KM");
                         HD44780_Str_XY(0,1,"Boot From TFTP");
                        break;
                case TFTP_KGDB:  
			 HD44780_ClrScr();
                         HD44780_Str_XY(2,0,"Welcome to KM");
                         HD44780_Str_XY(0,1,"Boot From TFTPGDB");
                        break;
                 case NFS_BOOT:  HD44780_ClrScr();
                         HD44780_Str_XY(2,0,"Welcome to KM");
                         HD44780_Str_XY(0,1,"Boot From Nfs");
                        break;			
                 case SELF_DIAGNOSTIC_TEST:  HD44780_ClrScr();
                         HD44780_Str_XY(2,0,"Welcome to KM");
                         HD44780_Str_XY(0,1," SELF_DIAGNOSTIC_TEST");
			 All_Test_Cases();
                        break;
		 default:
                         HD44780_ClrScr();
                         HD44780_Str_XY(2,0,"Welcome to KM");
                         HD44780_Str_XY(0,1,"Choice Corect opt");
                        break;
                        }
                         udelay(1000);
                         udelay(1000);
                         udelay(1000);
   GPIO0_DATA_CLEAR = (1 <<  (9 % 32));  //clear a Data -->BUZZER OFF
                                                                             
        return 0;
}
void LCD_Write_High_Nibble(unsigned char data ){
        if(data & 0x10)
                Write_Gpio_Value(LCD_D4, 1);
        else
                Write_Gpio_Value(LCD_D4, 0);
        if(data & 0x20)
                Write_Gpio_Value(LCD_D5, 1);
        else
                Write_Gpio_Value(LCD_D5, 0);
        if(data & 0x40)
                Write_Gpio_Value(LCD_D6, 1);
        else
                Write_Gpio_Value(LCD_D6, 0);
        if(data & 0x80)
                Write_Gpio_Value(LCD_D7, 1);
        else
                Write_Gpio_Value(LCD_D7, 0);
        HD44780_EN(ON);
        Delay_HD44780(DELAY_EN);
        HD44780_EN(OFF);
}

void LCD_Write_Low_Nibble(unsigned char data )
{
        if(data & 0x01)
                Write_Gpio_Value(LCD_D4, 1);
        else
                Write_Gpio_Value(LCD_D4, 0);
        if(data & 0x02)
                Write_Gpio_Value(LCD_D5, 1);
        else
                Write_Gpio_Value(LCD_D5, 0);
        if(data & 0x04)
                Write_Gpio_Value(LCD_D6, 1);
        else
                Write_Gpio_Value(LCD_D6, 0);
        if(data & 0x08)
                Write_Gpio_Value(LCD_D7, 1);
        else
                Write_Gpio_Value(LCD_D7, 0);
        HD44780_EN(ON);
        Delay_HD44780(DELAY_EN);
        HD44780_EN(OFF);
}
void HD44780_EN(char Mode){
        if(Mode == ON){
                Write_Gpio_Value_Control(LCD_EN,1);
                return;
        }
        Write_Gpio_Value_Control(LCD_EN,0);
}

void Delay_HD44780(unsigned int Delay){
        int i=0;
        for(i=0;i<Delay;i++)
        udelay(10000);
}

/* 4bit bus version */

void hd44780_write( unsigned char data ){
/* send the data bits - high nibble first */
        LCD_Write_High_Nibble( data );
        LCD_Write_Low_Nibble( data );
}

void hd44780_wr_cmd( unsigned char cmd ){
        Write_Gpio_Value_Control(LCD_RS,0);
        hd44780_write( cmd );
}

void hd44780_wr_data( unsigned char data ){
        Write_Gpio_Value_Control(LCD_RS,1);
        hd44780_write( data );
}

void HD44780_PutChar(unsigned char c){
        hd44780_wr_data(c & 0xff);
}


void HD44780_GotoXY(unsigned char x, unsigned char y){
        unsigned char copy_y=0;
        if(x > (HD44780_DISP_LENGTH-1))
        x = 0;
        if(y > (HD44780_DISP_ROWS-1))
                y = 0;
        switch(y) {
        case 0:  copy_y = 0x80; break;
        case 1:  copy_y = 0xc0; break;
        case 2:  copy_y = 0x94; break;
        case 3:  copy_y = 0xd4; break;
         }
        hd44780_wr_cmd(x + copy_y);
}

void HD44780_PutStr(char *str){
        unsigned int i=0;
        do{
        HD44780_PutChar(str[i]);
        i++;
        }while(str[i]!='\0');
}

void HD44780_ClrScr(void){
        hd44780_wr_cmd(HD44780_CMD_CLEAR);
}

void HD44780_Str_XY(char X, char Y, char *Ptr){
        HD44780_GotoXY(X,Y);
        HD44780_PutStr(Ptr);
}
