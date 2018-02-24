#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct SAnimate
{
 int Mode;//режим
 int Frame;//кадр
 int dX;//изменения координат после отработки кадра
 int dY;
};

int RND(int max);//случайное число
void SetAnimate(SAnimate *sAnimatePtr,int Mode,int Frame,int dX,int dY);//задать параметры анимации

#endif //COMMON_H_INCLUDED
