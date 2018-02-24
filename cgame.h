#ifndef CGAME_H_INCLUDED
#define CGAME_H_INCLUDED

#include "csprite.h"
#include <pspctrl.h>
#include <math.h>
#include "video.h"
#include "cduckmap.h"
#include "cdogmap.h"
#include "cfonta.h"
#include "csoundcontrol.h"

//нормальное состояние оружия
#define WEAPON_MODE_NORMAL 0
//идёт анимация оружия
#define WEAPON_MODE_ANIMATE 1
//оружие убрано
#define WEAPON_MODE_HIDE    2

#define PISTOL_BASIC  0
#define PISTOL_FIRE_1 1
#define PISTOL_FIRE_2 2

#define SHOTGUN_BASIC  0
#define SHOTGUN_FIRE_1 1
#define SHOTGUN_FIRE_2 2
#define SHOTGUN_FIRE_3 3
#define SHOTGUN_FIRE_4 4
#define SHOTGUN_FIRE_5 5

class CGame
{
 protected:
  CSprite cSprite_Back;//фон
  CSprite cSprite_Status;//панель состояния
  CSprite cSprite_Grass;//трава
  CSprite cSprite_TreeLittle;//дерево малое
  CSprite cSprite_TreeBig;//дерево большое
  CSprite cSprite_Cross;//прицел
  CSprite cSprite_Dog;//собака
  CSprite cSprite_Duck;//утки
  CSprite cSprite_Pistol;//пистолет
  CSprite cSprite_Shotgun;//ружьё
  //-----------------------------------------------------------
  SAnimate *sAnimate_PistolPtr;//анимация пистолета
  SAnimate *sAnimate_ShotgunPtr;//анимация дробовика
  //-----------------------------------------------------------
  int WorkingAreaWidth;//рабочая зона по X
  int WorkingAreaHeight;//рабочая зона по Y
  //-----------------------------------------------------------
  struct SPlayer
  {
   int XCross;//прицел
   int YCross;
   int Score;//набранные очки
   int Level;//уровень игры
   int Ammo[2];//количество патронов в пистолете и в дробовике
   int SelectedWeapon;//выбранное оружие
   int SelectedNextWeapon;//следующее выбранное оружие
   int Bullet;//выстрелов на уровень
   int SlipAmount;//количество промахов
   int SlipMax;//максимально промахов

   int PistolFrameSizeX;//размер кадра пистолета
   int PistolFrameSizeY;

   int ShotgunFrameSizeX;//размер кадра ружья
   int ShotgunFrameSizeY;

   int PistoldY;//изменение по высоте пистолета
   int PistolFrame;//кадры анимации пистолета
   int ShotgundY;//изменение по высоте дробовика
   int ShotgunFrame;//кадры анимации дробовика

   int PistolFireFrame;//кадр начала стрельбы из пистолета
   int ShotgunFireFrame;//кадр начала стрельбы из дробовика
   int PistolHideFrame;//кадр убирания пистолета
   int ShotgunHideFrame;//кадр убирания дробовика
   int PistolShowFrame;//кадр доставания пистолета
   int ShotgunShowFrame;//кадр доставания дробовика

   int WeaponAnimateCounter;//счётчик задержки анимации

   int Duck;//число уток

  } sPlayer;
  //-----------------------------------------------------------
  CDuckMap cDuckMap;//поле уток
  //-----------------------------------------------------------
  CDogMap cDogMap;//поле собак
 public:

  CGame(void);
  ~CGame();
  //-----------------------------------------------------------
  void Create(char *Path);
  void Release(void);
  //-----------------------------------------------------------
  int Activate(char *Path,bool two_duck,int sensitivity_x,int sensitivity_y);//запуск игры
  //-----------------------------------------------------------
 protected:
  void SaveScreenShot(char *Path);//сохранить скриншот
  bool Control(char *Path,int sensitivity_x,int sensitivity_y);//управление
  void DrawGameMap(void);//нарисовать игровое поле с утками
  void DrawCross(void);//нарисовать перекрестье прицела
  void WeaponProcessing(void);//анимация оружия
  bool SaveState(char *Path);//сохранить состояние игрока
  bool LoadState(char *Path);//загрузить состояние игрока
};

#endif
