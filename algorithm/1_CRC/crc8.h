#ifndef __CRC_H__
#define __CRC_H__
#include <stdio.h>

unsigned char cal_table_high_first(unsigned char value);

unsigned char crc_high_first(unsigned char *ptr, unsigned char len);

void  create_crc_table(void);

unsigned char cal_crc_table(unsigned char *ptr, unsigned char len);

#endif // __CRC_H__
