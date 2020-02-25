
#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>

#define FB_DEVICE_NAME "/dev/fb0"

#define COLOR_BACKGROUND   0xE7DBB5  /* 泛黄的纸 */
#define COLOR_FOREGROUND   0x514438  /* 褐色字体 */

#define DBG_PRINTF(...)      //不打印时定义为空宏
//#define DBG_PRINTF printf  //打印时打开次宏

#endif /* _CONFIG_H */
