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

//���� �����
class CDogMap
{
 protected:
  int WorkingAreaWidth;//������� ���� �� X
  int WorkingAreaHeight;//������� ���� �� Y
  int GrassHeight;//������ �����
  int DogFrameSizeX;//������ ����� ������ �� X
  int DogFrameSizeY;//������ ����� ������ �� Y
  int DogFrameLol;//������ ������
  int DogFrameOneDuck;//������ � ����� �����
  int DogFrameTwoDuck;//������ � ����� ������
  int DogFrameHit;//� ��������� ������ ������
  int DogFrameBasic;//�������� ���������
  CSprite *cSprite_DogPtr;//�������
  SAnimate *sAnimate_DogPtr;//������������������ �������� ������
  SDog sDog;//������
 public:
  CDogMap(void);//�����������
  ~CDogMap();//����������
  void Init(int AreaWidth,int AreaHeight,int GrassHeightLevel,CSprite *cSprite_Dog);//�������������
  void InitLevel(void);//��������� ������ �� ������ ������
  int GetDogMode(void);//�������� ����� ������
  void PutDog(void);//������� �����
  void DogLOL(void);//������ �������� "������ ������"
  void DogOneDuck(void);//������ �������� "������ � ����� �����"
  void DogTwoDuck(void);//������ �������� "������ � ����� ������"
  void DogBasic(void);//�������� ������ � �������� ���������
  void Processing(void);//��������
  void SaveState(SceUID SceUID_File);//�������� ���������
  void LoadState(SceUID SceUID_File);//��������� ���������
  void Fire(int cX,int cY,int r);//�������� �� ��������� ������
};
#endif
