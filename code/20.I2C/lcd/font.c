

extern const unsigned char fontdata_8x16[];

static unsigned int fb_base;
static int xres, yres, bpp;

void lcd_font_init(void)
{
	get_lcd_params(&fb_base, &xres, &yres, &bpp);
}

void lcd_print_char(int x,int y,char c,unsigned int color)
{
	int i,j;
	int bit;
	unsigned char data;
	/* 根据c的ASCII码在 font_8x16.c得到点阵数据 */
	unsigned char *dots = (unsigned char *)&fontdata_8x16[c * 16];//获取字符所在地址


   	/* 根据点阵来设置像素颜色 */
	for(j = y; j < y+16; j++){

		data = *dots++;//获取一行的点阵
		bit = 7;

		for(i = x; i < x+8; i++){
			/* 根据点阵的某位决定是否描颜色 */
			if(data & (1<<bit)){
				fb_draw_dot(i,j,color);
			}
			bit--;
		}
	}

}


/* "abc\n\r123" */
void lcd_print_string(int x, int y, char* str, unsigned int color)
{
	int i = 0, j;
	
	while (str[i])
	{
		if(str[i] == '\n'){//换行
			y += 16;
		}
		else if(str[i] == '\r'){//回到行首
			x = 0;
		}
        else{
     		lcd_print_char(x,y,str[i],color);
			x += 8;
			if(x >= xres){//x超过最右边沿,换行
				x = 0;
				y += 16;
			}   	
        }
		i++;
	}
}

