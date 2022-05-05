#ifndef _LCD_SPI_H
#define _LCD_SPI_H

#include "main.h"

//-----------------引脚定义------------------------------      
extern SPI_HandleTypeDef hspi1;
#define LCD_DC(x)       HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,(GPIO_PinState)x)
#define LCD_RST(x)     HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,(GPIO_PinState)x)
#define LCD_CS(x)     HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,(GPIO_PinState)x)

#define LCD_W   135
#define LCD_H   240

//-------常用颜色----------
//画笔颜色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色
#define GRAY0       0xEF7D 
#define GRAY1       0x8410      	//灰色1      00000 000000 00000
#define GRAY2       0x4208 
#define OR          0xFD48
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	0X841F //浅绿色
#define LIGHTGRAY       0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)
//定义写字笔的颜色
#define LCD_PENCOLOR    RED

//定义背景颜色
#define LCD_BGCOLOR     BLACK



//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180
//2 横屏模式
//3 横屏模式  旋转180
#define LCD_DISPLAY_DIR 2

#if (0==LCD_DISPLAY_DIR || 1==LCD_DISPLAY_DIR)
#define	LCD_X_MAX	LCD_W	//液晶X方宽度
#define LCD_Y_MAX	LCD_H   	//液晶Y方宽度
     
#elif (2==LCD_DISPLAY_DIR || 3==LCD_DISPLAY_DIR)
#define	LCD_X_MAX	LCD_H	//液晶X方宽度
#define LCD_Y_MAX	LCD_W   	//液晶Y方宽度
     
#else
#error "LCD_DISPLAY_DIR 定义错误"
     
#endif


void LCD_Init(void);
void LCD_clear(uint16_t color);
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);


void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);//在指定位置画一条线
void GUI_LineWith(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t with, uint16_t color);//有宽度的直线
//void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);//在指定位置画一个矩形
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color,uint8_t fill);//在指定位置画一个圆

//void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示汉字串
//void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个12x12汉字
//void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个16x16汉字
void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个24x24汉字
//void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示单个32x32汉字

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//显示一个字符
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t fc,uint16_t bc,const uint8_t *p,uint8_t sizey,uint8_t mode);//显示字符串
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//显示整数变量
void LCD_ShowflashNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//显示两位小数变量

void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);//显示图片

void Gui_Drawbmp16(uint16_t x,uint16_t y,uint16_t l, uint16_t w, const unsigned char *p); //显示40*40 QQ图片
#endif
