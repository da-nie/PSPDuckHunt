#ifndef CSOUNDCONTROL_H_INCLUDED
#define CSOUNDCONTROL_H_INCLUDED

#include <psprtc.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include "csound.h"

enum
{
 SOUND_FIRE_PISTOL,
 SOUND_FIRE_SHOTGUN,
 SOUND_DUCK,
 SOUND_DOG,
 SOUND_LAUGH
};

//���������� �������
class CSoundControl
{
 protected:
  int LastID;//������������� ���������� ���������������� �����
  u64 LastID_tick;//�����, ����� ��������� ���� ��� ������������
 public:
  CSoundControl(void);
  void Create(char *Path);//������� �����
  void Play(int ID);//��������� ��������������
  void StopAllSound(void);//���������� ��������������� ���� ������
  bool CheckEndAllSound(void);//��������, ����������� �� ��������������� �� ���� �������
};

#endif
