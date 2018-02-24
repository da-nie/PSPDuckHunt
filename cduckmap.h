#ifndef CDUCKMAP_H_INCLUDED
#define CDUCKMAP_H_INCLUDED

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "csprite.h"
#include "video.h"
#include "common.h"
#include "csoundcontrol.h"

#define DUCK_DOWN_LEFT_1    0
#define DUCK_DOWN_LEFT_2    1
#define DUCK_DOWN_LEFT_3    2
#define DUCK_DOWN_RIGHT_1   3
#define DUCK_DOWN_RIGHT_2   4
#define DUCK_DOWN_RIGHT_3   5
#define DUCK_UP_RIGHT_1     6
#define DUCK_UP_RIGHT_2     7
#define DUCK_UP_LEFT_1      8
#define DUCK_UP_LEFT_2      9
#define DUCK_UP_1           10
#define DUCK_UP_2           11
#define DUCK_UP_3           12
#define DUCK_HIT            13
#define DUCK_FALL_1         14
#define DUCK_FALL_2         15


//утка не запускалась
#define DUCK_MODE_NONE 0
//утка летает
#define DUCK_MODE_FLY  1
//в утку попали
#define DUCK_MODE_HIT  2
//утка падает
#define DUCK_MODE_FALL 3
//утра засчитана как добыча
#define DUCK_MODE_ITEM 4
//утка улетела
#define DUCK_MODE_FAIL 5

struct SDuck
{
 bool Enabled;//летает ли эта утка
 int DuckMode;//режим полёта утки
 int Score;//очки за утку
 float X;//координаты центра утки
 float Y;
 float dX;
 float dY;
 float Speed;//скорость полёта
 int Frame;//выводимый кадр
 int FlyCounter;//счётчик до смены направления полёта
 int DirectCounter;//счётчик метаний до улетания утки
 int SpriteCounter;//номер анимации полёта (не номер спрайта!)
 int SpriteDirectCounter;//направление анимации спрайта
 int SpriteAnimateCounter;//счётчик до смены анимации
};

//поле уткок
class CDuckMap
{
 protected:
  int WorkingAreaWidth;//рабочая зона по X
  int WorkingAreaHeight;//рабочая зона по Y
  int DuckFrameSizeX;//размер кадра утки по X
  int DuckFrameSizeY;//размер кадра утки по Y
  int GrassHeight;//высота травы
  int Level;//уровень игры
  CSprite *cSprite_DuckPtr;//указатель на спрайты
  SDuck sDuck[2];//утки
 public:
  CDuckMap(void);//конструктор
  ~CDuckMap();//деструктор
  void Init(int AreaWidth,int AreaHeight,int GrassHeightLevel,CSprite *cSprite_Duck);//инициализация
  void SetEnabledDuck(bool duck1_enabled,bool duck2_enabled);//установить разрешение на полёт уток
  void GetEnabledDuck(bool &duck1_enabled,bool &duck2_enabled);//получить разрешение на полёт уток
  void InitLevel(int level);//настроить уток на начало уровня
  void DuckControl(void);//управление утками
  void PutDuck(void);//вывести уток
  bool LaunchDuck(void);//запуск уток, если нужно
  int CheckEndDuckHunt(void);//проверить, как идёт охота
  int Fire(int cX,int cY,int r);//по уткам стрельнули
  void SaveState(SceUID SceUID_File);//записать состояние
  void LoadState(SceUID SceUID_File);//загрузить состояние
};
#endif
