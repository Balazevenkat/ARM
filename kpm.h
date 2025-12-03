//kpm.h
#ifndef __KPM_H__
#define __KPM_H__
#include"types.h"
void Init_KPM(void);
u32 Colscan(void);
u32 Rowcheck(void);
u32 Colcheck(void);
u32 Keyscan(void);
u32 get_digit();
u32 get_key();
u32 get_two_digit_value();
#endif