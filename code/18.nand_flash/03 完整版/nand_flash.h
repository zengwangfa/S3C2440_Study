#ifndef __NAND_FLASH_H
#define __NAND_FLASH_H

/* nand初始化 */
void nand_init(void);

/* NAND FLASH功能菜单 */
void nand_flash_menu(void);

/* nand 读取数据 */
void read_nand_flash(unsigned int addr,unsigned char *buf,unsigned int len);

#endif

