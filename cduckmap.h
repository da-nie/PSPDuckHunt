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


//���� �� �����������
#define DUCK_MODE_NONE 0
//���� ������
#define DUCK_MODE_FLY  1
//� ���� ������
#define DUCK_MODE_HIT  2
//���� ������
#define DUCK_MODE_FALL 3
//���� ��������� ��� ������
#define DUCK_MODE_ITEM 4
//���� �������
#define DUCK_MODE_FAIL 5

struct SDuck
{
 bool Enabled;//������ �� ��� ����
 int DuckMode;//����� ����� ����
 int Score;//���� �� ����
 float X;//���������� ������ ����
 float Y;
 float dX;
 float dY;
 float Speed;//�������� �����
 int Frame;//��������� ����
 int FlyCounter;//������� �� ����� ����������� �����
 int DirectCounter;//������� ������� �� �������� ����
 int SpriteCounter;//����� �������� ����� (�� ����� �������!)
 int SpriteDirectCounter;//����������� �������� �������
 int SpriteAnimateCounter;//������� �� ����� ��������
};

//���� �����
class CDuckMap
{
 protected:
  int WorkingAreaWidth;//������� ���� �� X
  int WorkingAreaHeight;//������� ���� �� Y
  int DuckFrameSizeX;//������ ����� ���� �� X
  int DuckFrameSizeY;//������ ����� ���� �� Y
  int GrassHeight;//������ �����
  int Level;//������� ����
  CSprite *cSprite_DuckPtr;//��������� �� �������
  SDuck sDuck[2];//����
 public:
  CDuckMap(void);//�����������
  ~CDuckMap();//����������
  void Init(int AreaWidth,int AreaHeight,int GrassHeightLevel,CSprite *cSprite_Duck);//�������������
  void SetEnabledDuck(bool duck1_enabled,bool duck2_enabled);//���������� ���������� �� ���� ����
  void GetEnabledDuck(bool &duck1_enabled,bool &duck2_enabled);//�������� ���������� �� ���� ����
  void InitLevel(int level);//��������� ���� �� ������ ������
  void DuckControl(void);//���������� ������
  void PutDuck(void);//������� ����
  bool LaunchDuck(void);//������ ����, ���� �����
  int CheckEndDuckHunt(void);//���������, ��� ��� �����
  int Fire(int cX,int cY,int r);//�� ����� ����������
  void SaveState(SceUID SceUID_File);//�������� ���������
  void LoadState(SceUID SceUID_File);//��������� ���������
};
#endif
