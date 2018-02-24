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

//���������� ��������� ������
#define WEAPON_MODE_NORMAL 0
//��� �������� ������
#define WEAPON_MODE_ANIMATE 1
//������ ������
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
  CSprite cSprite_Back;//���
  CSprite cSprite_Status;//������ ���������
  CSprite cSprite_Grass;//�����
  CSprite cSprite_TreeLittle;//������ �����
  CSprite cSprite_TreeBig;//������ �������
  CSprite cSprite_Cross;//������
  CSprite cSprite_Dog;//������
  CSprite cSprite_Duck;//����
  CSprite cSprite_Pistol;//��������
  CSprite cSprite_Shotgun;//�����
  //-----------------------------------------------------------
  SAnimate *sAnimate_PistolPtr;//�������� ���������
  SAnimate *sAnimate_ShotgunPtr;//�������� ���������
  //-----------------------------------------------------------
  int WorkingAreaWidth;//������� ���� �� X
  int WorkingAreaHeight;//������� ���� �� Y
  //-----------------------------------------------------------
  struct SPlayer
  {
   int XCross;//������
   int YCross;
   int Score;//��������� ����
   int Level;//������� ����
   int Ammo[2];//���������� �������� � ��������� � � ���������
   int SelectedWeapon;//��������� ������
   int SelectedNextWeapon;//��������� ��������� ������
   int Bullet;//��������� �� �������
   int SlipAmount;//���������� ��������
   int SlipMax;//����������� ��������

   int PistolFrameSizeX;//������ ����� ���������
   int PistolFrameSizeY;

   int ShotgunFrameSizeX;//������ ����� �����
   int ShotgunFrameSizeY;

   int PistoldY;//��������� �� ������ ���������
   int PistolFrame;//����� �������� ���������
   int ShotgundY;//��������� �� ������ ���������
   int ShotgunFrame;//����� �������� ���������

   int PistolFireFrame;//���� ������ �������� �� ���������
   int ShotgunFireFrame;//���� ������ �������� �� ���������
   int PistolHideFrame;//���� �������� ���������
   int ShotgunHideFrame;//���� �������� ���������
   int PistolShowFrame;//���� ���������� ���������
   int ShotgunShowFrame;//���� ���������� ���������

   int WeaponAnimateCounter;//������� �������� ��������

   int Duck;//����� ����

  } sPlayer;
  //-----------------------------------------------------------
  CDuckMap cDuckMap;//���� ����
  //-----------------------------------------------------------
  CDogMap cDogMap;//���� �����
 public:

  CGame(void);
  ~CGame();
  //-----------------------------------------------------------
  void Create(char *Path);
  void Release(void);
  //-----------------------------------------------------------
  int Activate(char *Path,bool two_duck,int sensitivity_x,int sensitivity_y);//������ ����
  //-----------------------------------------------------------
 protected:
  void SaveScreenShot(char *Path);//��������� ��������
  bool Control(char *Path,int sensitivity_x,int sensitivity_y);//����������
  void DrawGameMap(void);//���������� ������� ���� � ������
  void DrawCross(void);//���������� ����������� �������
  void WeaponProcessing(void);//�������� ������
  bool SaveState(char *Path);//��������� ��������� ������
  bool LoadState(char *Path);//��������� ��������� ������
};

#endif
