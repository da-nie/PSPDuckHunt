#ifndef CFONTB_H_INCLUDED
#define CFONTB_H_INCLUDED

#include "csprite.h"

//шрифт
class CFontB
{
 protected:
  CSprite cSprite_Font;//спрайт шрифта
 public:
  CFontB(void);//конструктор
  ~CFontB();//деструктор
  bool Load(char *FileName,unsigned char alpha_r,unsigned char alpha_g,unsigned char alpha_b);//загрузить шрифт
  void Release(void);//удалить шрифт
  void PrintAt(int x,int y,char *string,bool alpha);//напечатать строку
};
#endif
