#include "LCD_SPI.h"
#include "lcdfont.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void LCD_writeIndex(uint8_t dat)			//д����
{	
	LCD_CS(0);
    LCD_DC(0);
	HAL_SPI_Transmit(&hspi1,&dat,1,500);
	LCD_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void LCD_writeData(uint8_t dat)			//д����
{
	LCD_CS(0);
    LCD_DC(1);
	HAL_SPI_Transmit(&hspi1,&dat,1,500);
	LCD_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ����ã��û��������
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void LCD_writedata_16bit(uint16_t dat)	//��Һ����дһ��16λ����
{
	uint8_t h,l;
	h = dat >> 8;
	l = (uint8_t)dat;
	LCD_CS(0);
	LCD_DC(1);
	HAL_SPI_Transmit(&hspi1,&h,1,500);
	HAL_SPI_Transmit(&hspi1,&l,1,500);
	LCD_CS(1);
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      1.14�� IPSҺ����ʼ��
//  @return     void
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void LCD_Init(void)
{

	LCD_CS(1);
	HAL_GPIO_WritePin(LCD_BLK_GPIO_Port,LCD_BLK_Pin,(GPIO_PinState)1);
	
    LCD_RST(0);
    HAL_Delay(200);
    
    LCD_RST(1);
    HAL_Delay(100);
	
    LCD_writeIndex(0x36);
    
    if      (LCD_DISPLAY_DIR==0)    LCD_writeData(0x00);
    else if (LCD_DISPLAY_DIR==1)    LCD_writeData(0xC0);
    else if (LCD_DISPLAY_DIR==2)    LCD_writeData(0x70);
    else                            LCD_writeData(0xA0);
    
    LCD_writeIndex(0x3A); 
    LCD_writeData(0x05);

    LCD_writeIndex(0xB2);
    LCD_writeData(0x0C);
    LCD_writeData(0x0C);
    LCD_writeData(0x00);
    LCD_writeData(0x33);
    LCD_writeData(0x33); 

    LCD_writeIndex(0xB7); 
    LCD_writeData(0x35);  

    LCD_writeIndex(0xBB);
    LCD_writeData(0x37);

    LCD_writeIndex(0xC0);
    LCD_writeData(0x2C);

    LCD_writeIndex(0xC2);
    LCD_writeData(0x01);

    LCD_writeIndex(0xC3);
    LCD_writeData(0x12);   

    LCD_writeIndex(0xC4);
    LCD_writeData(0x20);  

    LCD_writeIndex(0xC6); 
    LCD_writeData(0x0F);    

    LCD_writeIndex(0xD0); 
    LCD_writeData(0xA4);
    LCD_writeData(0xA1);

    LCD_writeIndex(0xE0);
    LCD_writeData(0xD0);
    LCD_writeData(0x04);
    LCD_writeData(0x0D);
    LCD_writeData(0x11);
    LCD_writeData(0x13);
    LCD_writeData(0x2B);
    LCD_writeData(0x3F);
    LCD_writeData(0x54);
    LCD_writeData(0x4C);
    LCD_writeData(0x18);
    LCD_writeData(0x0D);
    LCD_writeData(0x0B);
    LCD_writeData(0x1F);
    LCD_writeData(0x23);

    LCD_writeIndex(0xE1);
    LCD_writeData(0xD0);
    LCD_writeData(0x04);
    LCD_writeData(0x0C);
    LCD_writeData(0x11);
    LCD_writeData(0x13);
    LCD_writeData(0x2C);
    LCD_writeData(0x3F);
    LCD_writeData(0x44);
    LCD_writeData(0x51);
    LCD_writeData(0x2F);
    LCD_writeData(0x1F);
    LCD_writeData(0x1F);
    LCD_writeData(0x20);
    LCD_writeData(0x23);

    LCD_writeIndex(0x21); 

    LCD_writeIndex(0x11); 
    HAL_Delay(120); 

    LCD_writeIndex(0x29);
    LCD_clear(LCD_BGCOLOR);
}




void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(LCD_DISPLAY_DIR==0)
	{
		LCD_writeIndex(0x2a);//�е�ַ����
		LCD_writedata_16bit(x1+52);
		LCD_writedata_16bit(x2+52);
		LCD_writeIndex(0x2b);//�е�ַ����
		LCD_writedata_16bit(y1+40);
		LCD_writedata_16bit(y2+40);
		LCD_writeIndex(0x2c);//������д
	}
	else if(LCD_DISPLAY_DIR==1)
	{
		LCD_writeIndex(0x2a);//�е�ַ����
		LCD_writedata_16bit(x1+53);
		LCD_writedata_16bit(x2+53);
		LCD_writeIndex(0x2b);//�е�ַ����
		LCD_writedata_16bit(y1+40);
		LCD_writedata_16bit(y2+40);
		LCD_writeIndex(0x2c);//������д
	}
	else if(LCD_DISPLAY_DIR==2)
	{
		LCD_writeIndex(0x2a);//�е�ַ����
		LCD_writedata_16bit(x1+40);
		LCD_writedata_16bit(x2+40);
		LCD_writeIndex(0x2b);//�е�ַ����
		LCD_writedata_16bit(y1+53);
		LCD_writedata_16bit(y2+53);
		LCD_writeIndex(0x2c);//������д
	}
	else
	{
		LCD_writeIndex(0x2a);//�е�ַ����
		LCD_writedata_16bit(x1+40);
		LCD_writedata_16bit(x2+40);
		LCD_writeIndex(0x2b);//�е�ַ����
		LCD_writedata_16bit(y1+52);
		LCD_writedata_16bit(y2+52);
		LCD_writeIndex(0x2c);//������д
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ����������
//  @param      color     		��ɫ����
//  @return     void
//  @since      v1.0
//  Sample usage:               LCD_clear(LCD_YELLOW);// ȫ������Ϊ��ɫ
//-------------------------------------------------------------------------------------------------------------------
void LCD_clear(uint16_t color)
{
    uint16_t i,j;
	LCD_Address_Set(0,0,LCD_X_MAX-1,LCD_Y_MAX-1);
    for(i=0;i<LCD_X_MAX;i++)
    {
        for (j=0;j<LCD_Y_MAX;j++)
	   	{
        	LCD_writedata_16bit(color);	 			 
	    }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Һ������
//  @param      x     	        ����x��������
//  @param      y     	        ����y��������
//  @param      dat       	    ��Ҫ��ʾ����ɫ
//  @return     void
//  @since      v1.0
//  Sample usage:               LCD_drawpoint(0,0,LCD_RED);  //����0,0��һ����ɫ�ĵ�
//-------------------------------------------------------------------------------------------------------------------
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
    LCD_Address_Set(x,y,x,y);
    LCD_writedata_16bit(color);
}

/******************************************************************************
      ����˵��������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   �ߵ���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ������� 
	else if (delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ�� 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/****************************************************************************
* ���ƣ�GUI_HLine()
* ���ܣ���ˮƽ�ߡ�
* ��ڲ����� x0     ˮƽ����������е�λ��
*           y0      ˮƽ����������е�λ��
*           x1      ˮƽ���յ������е�λ��
*           color   ��ʾ��ɫ(���ںڰ�ɫLCM��Ϊ0ʱ��Ϊ1ʱ��ʾ)
* ���ڲ�������
* ˵�������ڵ�ɫ��4���Ҷȵ�Һ������ͨ���޸Ĵ˺�����ͼ����ٶȣ��絥ɫLCM������һ�θ�
*      ��8���㣬������Ҫһ����һ�����д��LCM�С�
****************************************************************************/
void  GUI_HLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t color)
{
    uint8_t  temp;
    if(x0>x1)               // ��x0��x1��С�������У��Ա㻭ͼ
    {
        temp = x1;
        x1 = x0;
        x0 = temp;
    }
    do
    {
        LCD_DrawPoint(x0, y0, color);   // �����ʾ�������ֱ��
        x0++;
    }
    while(x1>=x0);
}
/****************************************************************************
* ���ƣ�GUI_RLine()
* ���ܣ�����ֱ�ߡ�
* ��ڲ����� x0     ��ֱ����������е�λ��
*           y0      ��ֱ����������е�λ��
*           y1      ��ֱ���յ������е�λ��
*           color   ��ʾ��ɫ
* ���ڲ�������
* ˵�������ڵ�ɫ��4���Ҷȵ�Һ������ͨ���޸Ĵ˺�����ͼ����ٶȣ��絥ɫLCM������һ�θ�
*      ��8���㣬������Ҫһ����һ�����д��LCM�С�
****************************************************************************/
void  GUI_RLine(uint16_t x0, uint16_t y0, uint16_t y1, uint16_t color)
{
    uint8_t  temp;
    if(y0>y1)       // ��y0��y1��С�������У��Ա㻭ͼ
    {
        temp = y1;
        y1 = y0;
        y0 = temp;
    }
    do
    {
        LCD_DrawPoint(x0, y0, color);   // �����ʾ�������ֱ��
        y0++;
    }
    while(y1>=y0);
}

/****************************************************************************
* ���ƣ�GUI_LineWith()
* ���ܣ�����������֮���ֱ�ߣ����ҿ������ߵĿ�ȡ�
* ��ڲ����� x0		ֱ������x����ֵ
*           y0		ֱ������y����ֵ
*           x1      ֱ���յ��x����ֵ
*           y1      ֱ���յ��y����ֵ
*           with    �߿�(0-50)
*           color	��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_LineWith(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t with, uint16_t color)
{  int16_t   dx;						// ֱ��x���ֵ����
   int16_t   dy;          			// ֱ��y���ֵ����
   int8_t    dx_sym;					// x����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
   int8_t    dy_sym;					// y����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
   int16_t   dx_x2;					// dx*2ֵ���������ڼӿ������ٶ�
   int16_t   dy_x2;					// dy*2ֵ���������ڼӿ������ٶ�
   int16_t   di;						// ���߱���
   
   int16_t   wx, wy;					// �߿����
   int16_t   draw_a, draw_b;
   
   /* �������� */
   if(with==0) return;
   if(with>50) with = 50;
   
   dx = x1-x0;						// ��ȡ����֮��Ĳ�ֵ
   dy = y1-y0;
   
   wx = with/2;
   wy = with-wx-1;
   
   /* �ж��������򣬻��Ƿ�Ϊˮƽ�ߡ���ֱ�ߡ��� */
   if(dx>0)							// �ж�x�᷽��
   {  dx_sym = 1;					// dx>0������dx_sym=1
   }
   else
   {  if(dx<0)
      {  dx_sym = -1;				// dx<0������dx_sym=-1
      }
      else
      {  /* dx==0������ֱ�ߣ���һ�� */
         wx = x0-wx;
         if(wx<0) wx = 0;
         wy = x0+wy;
         
         while(1)
         {  x0 = wx;
            GUI_RLine(x0, y0, y1, color);
            if(wx>=wy) break;
            wx++;
         }
         
      	 return;
      }
   }
   
   if(dy>0)							// �ж�y�᷽��
   {  dy_sym = 1;					// dy>0������dy_sym=1
   }
   else
   {  if(dy<0)
      {  dy_sym = -1;				// dy<0������dy_sym=-1
      }
      else
      {  /* dy==0����ˮƽ�ߣ���һ�� */
         wx = y0-wx;
         if(wx<0) wx = 0;
         wy = y0+wy;
         
         while(1)
         {  y0 = wx;
            GUI_HLine(x0, y0, x1, color);
            if(wx>=wy) break;
            wx++;
         }
      	 return;
      }
   }
    
   /* ��dx��dyȡ����ֵ */
   dx = dx_sym * dx;
   dy = dy_sym * dy;
 
   /* ����2����dx��dyֵ */
   dx_x2 = dx*2;
   dy_x2 = dy*2;
   
   /* ʹ��Bresenham�����л�ֱ�� */
   if(dx>=dy)						// ����dx>=dy����ʹ��x��Ϊ��׼
   {  di = dy_x2 - dx;
      while(x0!=x1)
      {  /* x����������������y���򣬼�����ֱ�� */
         draw_a = y0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = y0+wy;
         GUI_RLine(x0, draw_a, draw_b, color);
         
         x0 += dx_sym;				
         if(di<0)
         {  di += dy_x2;			// �������һ���ľ���ֵ
         }
         else
         {  di += dy_x2 - dx_x2;
            y0 += dy_sym;
         }
      }
      draw_a = y0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = y0+wy;
      GUI_RLine(x0, draw_a, draw_b, color);
   }
   else								// ����dx<dy����ʹ��y��Ϊ��׼
   {  di = dx_x2 - dy;
      while(y0!=y1)
      {  /* y����������������x���򣬼���ˮƽ�� */
         draw_a = x0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = x0+wy;
         GUI_HLine(draw_a, y0, draw_b, color);
         
         y0 += dy_sym;
         if(di<0)
         {  di += dx_x2;
         }
         else
         {  di += dx_x2 - dy_x2;
            x0 += dx_sym;
         }
      }
      draw_a = x0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = x0+wy;
      GUI_HLine(draw_a, y0, draw_b, color);
   } 
  
}

/******************************************************************************
      ����˵����������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   ���ε���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      ����˵������Բ
      ������ݣ�x0,y0   Բ������
                r       �뾶
                color   Բ����ɫ
      ����ֵ��  ��
******************************************************************************/
void draw_circle(uint16_t xc, uint16_t yc, uint16_t x, uint16_t y, uint16_t c)
{
	LCD_DrawPoint(xc + x, yc + y, c);

	LCD_DrawPoint(xc - x, yc + y, c);

	LCD_DrawPoint(xc + x, yc - y, c);

	LCD_DrawPoint(xc - x, yc - y, c);

	LCD_DrawPoint(xc + y, yc + x, c);

	LCD_DrawPoint(xc - y, yc + x, c);

	LCD_DrawPoint(xc + y, yc - x, c);

	LCD_DrawPoint(xc - y, yc - x, c);
}
void Draw_Circle(uint16_t xc, uint16_t yc, uint8_t r, uint16_t color, uint8_t fill)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill) 
	{
		// �����䣨��ʵ��Բ��
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
				draw_circle(xc, yc, x, yi, color);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else 
	{
		// �������䣨������Բ��
		while (x <= y) {
			draw_circle(xc, yc, x, y, color);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}


///******************************************************************************
//      ����˵������ʾ���ִ�
//      ������ݣ�x,y��ʾ����
//                *s Ҫ��ʾ�ĺ��ִ�
//                fc �ֵ���ɫ
//                bc �ֵı���ɫ
//                sizey �ֺ� ��ѡ 16 24 32
//                mode:  0�ǵ���ģʽ  1����ģʽ
//      ����ֵ��  ��
//******************************************************************************/
//void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	while(*s!=0)
//	{
//		if(sizey==12) LCD_ShowChinese12x12(x,y,s,fc,bc,sizey,mode);
//		else if(sizey==16) LCD_ShowChinese16x16(x,y,s,fc,bc,sizey,mode);
//		else if(sizey==24) LCD_ShowChinese24x24(x,y,s,fc,bc,sizey,mode);
//		else if(sizey==32) LCD_ShowChinese32x32(x,y,s,fc,bc,sizey,mode);
//		else return;
//		s+=2;
//		x+=sizey;
//	}
//}

///******************************************************************************
//      ����˵������ʾ����12x12����
//      ������ݣ�x,y��ʾ����
//                *s Ҫ��ʾ�ĺ���
//                fc �ֵ���ɫ
//                bc �ֵı���ɫ
//                sizey �ֺ�
//                mode:  0�ǵ���ģʽ  1����ģʽ
//      ����ֵ��  ��
//******************************************************************************/
//void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//������Ŀ
//	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
//	uint16_t x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	                         
//	HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);	//ͳ�ƺ�����Ŀ
//	for(k=0;k<HZnum;k++) 
//	{
//		if((tfont12[k].Index[0]==*(s))&&(tfont12[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//�ǵ��ӷ�ʽ
//					{
//						if(tfont12[k].Msk[i]&(0x01<<j))LCD_writedata_16bit(fc);
//						else LCD_writedata_16bit(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//���ӷ�ʽ
//					{
//						if(tfont12[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//��һ����
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
//	}
//} 

///******************************************************************************
//      ����˵������ʾ����16x16����
//      ������ݣ�x,y��ʾ����
//                *s Ҫ��ʾ�ĺ���
//                fc �ֵ���ɫ
//                bc �ֵı���ɫ
//                sizey �ֺ�
//                mode:  0�ǵ���ģʽ  1����ģʽ
//      ����ֵ��  ��
//******************************************************************************/
//void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//������Ŀ
//	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
//	uint16_t x0=x;
//  TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//ͳ�ƺ�����Ŀ
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//�ǵ��ӷ�ʽ
//					{
//						if(tfont16[k].Msk[i]&(0x01<<j))LCD_writedata_16bit(fc);
//						else LCD_writedata_16bit(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//���ӷ�ʽ
//					{
//						if(tfont16[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//��һ����
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
//	}
//} 


///******************************************************************************
//      ����˵������ʾ����24x24����
//      ������ݣ�x,y��ʾ����
//                *s Ҫ��ʾ�ĺ���
//                fc �ֵ���ɫ
//                bc �ֵı���ɫ
//                sizey �ֺ�
//                mode:  0�ǵ���ģʽ  1����ģʽ
//      ����ֵ��  ��
//******************************************************************************/
//void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//������Ŀ
//	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
//	uint16_t x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//ͳ�ƺ�����Ŀ
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//�ǵ��ӷ�ʽ
//					{
//						if(tfont24[k].Msk[i]&(0x01<<j))LCD_writedata_16bit(fc);
//						else LCD_writedata_16bit(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//���ӷ�ʽ
//					{
//						if(tfont24[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//��һ����
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
//	}
//} 

///******************************************************************************
//      ����˵������ʾ����32x32����
//      ������ݣ�x,y��ʾ����
//                *s Ҫ��ʾ�ĺ���
//                fc �ֵ���ɫ
//                bc �ֵı���ɫ
//                sizey �ֺ�
//                mode:  0�ǵ���ģʽ  1����ģʽ
//      ����ֵ��  ��
//******************************************************************************/
//void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
//{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//������Ŀ
//	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
//	uint16_t x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//ͳ�ƺ�����Ŀ
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//�ǵ��ӷ�ʽ
//					{
//						if(tfont32[k].Msk[i]&(0x01<<j))LCD_writedata_16bit(fc);
//						else LCD_writedata_16bit(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//���ӷ�ʽ
//					{
//						if(tfont32[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//��һ����
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
//	}
//}


/******************************************************************************
      ����˵������ʾ�����ַ�
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ���ַ�
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t,m=0;
	uint16_t i,TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //�õ�ƫ�ƺ��ֵ
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //���ù��λ�� 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //����6x12����
		else if(sizey==16)temp=ascii_1608[num][i];		 //����8x16����
		else if(sizey==24)temp=ascii_2412[num][i];		 //����12x24����
		else if(sizey==32)temp=ascii_3216[num][i];		 //����16x32����
		else if(sizey==48)temp=ascii_4824[num][i];		 //����16x32����
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//�ǵ���ģʽ
			{
				if(temp&(0x01<<t))LCD_writedata_16bit(fc);
				else LCD_writedata_16bit(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//����ģʽ
			{
				if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//��һ����
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
      ����˵������ʾ�ַ���
      ������ݣ�x,y��ʾ����
                *p Ҫ��ʾ���ַ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t fc,uint16_t bc,const uint8_t *p,uint8_t sizey,uint8_t mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}


/******************************************************************************
      ����˵������ʾ����
      ������ݣ�m������nָ��
      ����ֵ��  ��
******************************************************************************/
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
      ����˵������ʾ��������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ��������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	uint8_t sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,1);
	}
} 
void LCD_ShowflashNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	uint8_t sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


/******************************************************************************
      ����˵������ʾ��λС������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾС������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}

/******************************************************************************
      ����˵������ʾ����24x24����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t i,j,m=0;
	uint16_t k;
	uint16_t HZnum;//������Ŀ
	uint16_t TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//�ǵ��ӷ�ʽ
					{
						if(tfont24[k].Msk[i]&(0x01<<j))LCD_writedata_16bit(fc);
						else LCD_writedata_16bit(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//���ӷ�ʽ
					{
						if(tfont24[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//��һ����
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
} 


/******************************************************************************
      ����˵������ʾͼƬ
      ������ݣ�x,y�������
                length ͼƬ����
                width  ͼƬ���
                pic[]  ͼƬ����    
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[])
{
	uint16_t i,j;
	uint32_t k=0;
	LCD_Address_Set(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_writedata_16bit(pic[k*2]);
			LCD_writedata_16bit(pic[k*2+1]);
			k++;
		}
	}			
}

/*****************************************************************************
 * @name       :void Gui_Drawbmp16(uint16_t x,uint16_t y,const unsigned char *p)
 * @date       :2018-08-09 
 * @function   :Display a 16-bit BMP image
 * @parameters :x:the bebinning x coordinate of the BMP image
                y:the bebinning y coordinate of the BMP image
								p:the start address of image array
 * @retvalue   :None
******************************************************************************/ 
void Gui_Drawbmp16(uint16_t x,uint16_t y,uint16_t l, uint16_t w, const unsigned char *p) //��ʾ40*40 QQͼƬ
{
	int i; 
	unsigned char picH,picL; 
	LCD_Address_Set(x,y,x+l-1,y+w-1);//��������
	for(i=0;i<l*w;i++)
	{	
	 	picL=*(p+i*2);	//���ݵ�λ��ǰ
		picH=*(p+i*2+1);				
		LCD_writedata_16bit(picH<<8|picL);  						
	}	
	//LCD_Address_Set(0,0,lcddev.width-1,lcddev.height-1);//�ָ���ʾ����Ϊȫ��	
}

