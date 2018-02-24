#ifndef CDOGMAP_H_INCLUDED
#define CDOGMAP_H_INCLUDED

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "video.h"
#include "csprite.h"
#include "common.h"
#include "csoundcontrol.h"

#define DOG_MOVE_1     0
#define DOG_MOVE_2     1
#define DOG_MOVE_3     2
#define DOG_MOVE_4     3
#define DOG_SNIFF_1    4
#define DOG_SNIFF_2    5
#define DOG_EXCITEMENT 6
#define DOG_DASHES_1   7
#define DOG_DASHES_2   8
#define DOG_LOL_1      9
#define DOG_LOL_2      10
#define DOG_HIT        11
#define DOG_ONE_DUCK   12
#define DOG_TWO_DUCK   13

#define DOG_MODE_BASIC                  0
#define DOG_MODE_ANIMATE                1
#define DOG_MODE_ANIMATE_BACK           2
#define DOG_MODE_ANIMATE_AND_YIP        3
#define DOG_MODE_ANIMATE_BACK_AND_LAUGH 4
#define DOG_MODE_ANIMATE_BACK_LOL       5
#define DOG_MODE_BASIC_FINAL            6




struct SDog
{
 int DogFrameIndex;
 int DogCounter;
 int DogX;
 int DogY;
};

//поле собак
class CDogMap
{
 protected:
  int WorkingAreaWidth;//рабочая зона по X
  int WorkingAreaHeight;//рабочая зона по Y
  int GrassHeight;//высота травы
  int DogFrameSizeX;//размер кадра собаки по X
  int DogFrameSizeY;//размер кадра собаки по Y
  int DogFrameLol;//собака смеётся
  int DogFrameOneDuck;//собака с одной уткой
  int DogFrameTwoDuck;//собака с двумя утками
  int DogFrameHit;//в смеющуюся собаку попали
  int DogFrameBasic;//исходное состояние
  CSprite *cSprite_DogPtr;//спрайты
  SAnimate *sAnimate_DogPtr;//последовательность анимации собаки
  SDog sDog;//собака
 public:
  CDogMap(void);//конструктор
  ~CDogMap();//деструктор
  void Init(int AreaWidth,int AreaHeight,int GrassHeightLevel,CSprite *cSprite_Dog);//инициализация
  void InitLevel(void);//настроить собаку на начало уровня
  int GetDogMode(void);//получить режим собаки
  void PutDog(void);//вывести собак
  void DogLOL(void);//начать анимацию "собака смеётся"
  void DogOneDuck(void);//начать анимацию "собака с одной уткой"
  void DogTwoDuck(void);//начать анимацию "собака с двумя утками"
  void DogBasic(void);//привести собаку в исходное состояние
  void Processing(void);//анимация
  void SaveState(SceUID SceUID_File);//записать состояние
  void LoadState(SceUID SceUID_File);//загрузить состояние
  void Fire(int cX,int cY,int r);//стрельба по смеющейся собаке
};
#endif
