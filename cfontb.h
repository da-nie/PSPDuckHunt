#ifndef CFONTB_H_INCLUDED
#define CFONTB_H_INCLUDED

#include "csprite.h"

//�����
class CFontB
{
 protected:
  CSprite cSprite_Font;//������ ������
 public:
  CFontB(void);//�����������
  ~CFontB();//����������
  bool Load(char *FileName,unsigned char alpha_r,unsigned char alpha_g,unsigned char alpha_b);//��������� �����
  void Release(void);//������� �����
  void PrintAt(int x,int y,char *string,bool alpha);//���������� ������
};
#endif
