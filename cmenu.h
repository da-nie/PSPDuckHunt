#ifndef CMENU_H_INCLUDED
#define CMENU_H_INCLUDED

#include <math.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include "cfonta.h"
#include "cfontb.h"
#include "csoundcontrol.h"
#include "csprite.h"
#include "video.h"

struct SHiScore
{
 char Name[21];//���
 int Score;//���������� �����
};

class CMenu
{
 protected:
  CSprite cSprite_MenuBack;//������ ���� ����
  CSprite cSprite_HiScoreBack;//������ ���� ������� ��������
  SHiScore sHiScore[10];//������� ��������
  char *Text;//��������� ������� ������
  int TextOffset;//�������� ������� ������
  int TextLength;//������ ������
  //-----------------------------------------------------------
 public:
  CMenu(void);
  ~CMenu();
  //-----------------------------------------------------------
  void Create(char *Path);
  void Release(void);
  //-----------------------------------------------------------
  void SaveHiScore(char *Path);//���������� ������� ��������
  bool LoadHiScore(char *Path);//�������� ������� ��������
  void CreateHiScore(void);//������� ������� ��������
  void DrawHiScore(void);//������� ������� ��������
  bool InputHiScore(int score,char *Path);//���� ����� � ������� ��������
  //-----------------------------------------------------------
  bool Activate(char *Path,bool &two_duck,int &sensitivity_x,int &sensitivity_y);//��������� �� ����������
  //-----------------------------------------------------------
};

#endif
