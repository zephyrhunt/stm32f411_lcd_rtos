#ifndef _LCD_SPI_H
#define _LCD_SPI_H

#include "main.h"

//-----------------���Ŷ���------------------------------      
extern SPI_HandleTypeDef hspi1;
#define LCD_DC(x)       HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,(GPIO_PinState)x)
#define LCD_RST(x)     HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,(GPIO_PinState)x)
#define LCD_CS(x)     HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,(GPIO_PinState)x)

#define LCD_W   135
#define LCD_H   240

//-------������ɫ----------
//������ɫ
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
#define BROWN 			0XBC40 //��ɫ
#define BRRED 			0XFC07 //�غ�ɫ
#define GRAY  			0X8430 //��ɫ
#define GRAY0       0xEF7D 
#define GRAY1       0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2       0x4208 
#define OR          0xFD48
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	0X841F //ǳ��ɫ
#define LIGHTGRAY       0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 		0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE      	0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE          0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
//����д�ֱʵ���ɫ
#define LCD_PENCOLOR    RED

//���屳����ɫ
#define LCD_BGCOLOR     BLACK



//������ʾ����
//0 ����ģʽ
//1 ����ģʽ  ��ת180
//2 ����ģʽ
//3 ����ģʽ  ��ת180
#define LCD_DISPLAY_DIR 2

#if (0==LCD_DISPLAY_DIR || 1==LCD_DISPLAY_DIR)
#define	LCD_X_MAX	LCD_W	//Һ��X�����
#define LCD_Y_MAX	LCD_H   	//Һ��Y�����
     
#elif (2==LCD_DISPLAY_DIR || 3==LCD_DISPLAY_DIR)
#define	LCD_X_MAX	LCD_H	//Һ��X�����
#define LCD_Y_MAX	LCD_W   	//Һ��Y�����
     
#else
#error "LCD_DISPLAY_DIR �������"
     
#endif


void LCD_Init(void);
void LCD_clear(uint16_t color);
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);


void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);//��ָ��λ�û�һ����
void GUI_LineWith(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t with, uint16_t color);//�п�ȵ�ֱ��
//void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);//��ָ��λ�û�һ������
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color,uint8_t fill);//��ָ��λ�û�һ��Բ

//void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ���ִ�
//void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����12x12����
//void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����16x16����
void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����24x24����
//void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����32x32����

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾһ���ַ�
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t fc,uint16_t bc,const uint8_t *p,uint8_t sizey,uint8_t mode);//��ʾ�ַ���
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��������
void LCD_ShowflashNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��λС������

void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);//��ʾͼƬ

void Gui_Drawbmp16(uint16_t x,uint16_t y,uint16_t l, uint16_t w, const unsigned char *p); //��ʾ40*40 QQͼƬ
#endif
