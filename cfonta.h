#ifndef CFONTA_H_INCLUDED
#define CFONTA_H_INCLUDED

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "csprite.h"

class CFontA
{
 protected:
  CSprite cSprite_Font;//шрифт
 public:
  CFontA(void);//конструктор
  ~CFontA();//деструктор
  void Load(char *FileName,unsigned char alpha_r,unsigned char alpha_g,unsigned char alpha_b);//загрузить шрифт
  void PrintAt(int x,int y,char *string,bool alpha);//вывести строку
  int GetStringWidth(char *string);//получить длину строки в пикселях
  int GetStringHeight(char *string);//получить высоту строки в пикселях
};
#endif // CFONTA_H_INCLUDED
