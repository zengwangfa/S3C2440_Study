
#ifndef _FONT_H
#define _FONT_H

void lcd_font_init(void);
void fb_print_char(int x, int y, char c, unsigned int color);
void fb_print_string(int x, int y, char* str, unsigned int color);

#endif /* _FONT_H */

