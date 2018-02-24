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

//управление щвуками
class CSoundControl
{
 protected:
  int LastID;//идентификатор последнего воспроизводимого звука
  u64 LastID_tick;//время, когда последний звук был воспроизведён
 public:
  CSoundControl(void);
  void Create(char *Path);//создать звуки
  void Play(int ID);//запустить вопроизведение
  void StopAllSound(void);//остановить воспроизведение всех звуков
  bool CheckEndAllSound(void);//выяснить, закончилось ли воспроизведение по всем каналам
};

#endif
