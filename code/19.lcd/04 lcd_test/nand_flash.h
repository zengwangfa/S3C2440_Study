
#ifndef _NAND_FLASH_H
#define _NAND_FLASH_H

void nand_init(void);
void nand_read(unsigned int addr, unsigned char *buf, unsigned int len);

#endif /* _NAND_FLASH_H */

