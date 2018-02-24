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
 char Name[21];//имя
 int Score;//количество очков
};

class CMenu
{
 protected:
  CSprite cSprite_MenuBack;//спрайт фона меню
  CSprite cSprite_HiScoreBack;//спрайт фона таблицы рекордов
  SHiScore sHiScore[10];//таблица рекордов
  char *Text;//выводимая бегущая строка
  int TextOffset;//смещение бегущей строки
  int TextLength;//размер текста
  //-----------------------------------------------------------
 public:
  CMenu(void);
  ~CMenu();
  //-----------------------------------------------------------
  void Create(char *Path);
  void Release(void);
  //-----------------------------------------------------------
  void SaveHiScore(char *Path);//сохранение таблицы рекордов
  bool LoadHiScore(char *Path);//загрузка таблицы рекордов
  void CreateHiScore(void);//создать таблицу рекордов
  void DrawHiScore(void);//вывести таблицу рекордов
  bool InputHiScore(int score,char *Path);//ввод имени в таблицу рекордов
  //-----------------------------------------------------------
  bool Activate(char *Path,bool &two_duck,int &sensitivity_x,int &sensitivity_y);//запустить на выполнение
  //-----------------------------------------------------------
};

#endif
