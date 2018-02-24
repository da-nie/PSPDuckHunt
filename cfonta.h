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
  CSprite cSprite_Font;//�����
 public:
  CFontA(void);//�����������
  ~CFontA();//����������
  void Load(char *FileName,unsigned char alpha_r,unsigned char alpha_g,unsigned char alpha_b);//��������� �����
  void PrintAt(int x,int y,char *string,bool alpha);//������� ������
  int GetStringWidth(char *string);//�������� ����� ������ � ��������
  int GetStringHeight(char *string);//�������� ������ ������ � ��������
};
#endif // CFONTA_H_INCLUDED
