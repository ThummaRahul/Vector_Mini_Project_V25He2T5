#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__
#include "types.h"

int check_password(void);
int my_strcmp(s8 *s1,s8 *s2);
int Edit_RTC_Info(void);
int change_password(void);
void my_strcpy(s8 *dest, s8 *src);
int Edit_EAT_Info(int *start_hr,int *end_hr,int *start_mn,int *end_mn);
#endif
