#include <string.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include "csoundcontrol.h"

extern CSound cSound;

CSoundControl cSoundControl;

CSoundControl::CSoundControl(void)
{
 LastID=-1;
}

void CSoundControl::Create(char *Path)
{
 char *FileName=new char[strlen(Path)+255];
 sprintf(FileName,"%ssound\\pistol.dhs",Path);
 cSound.LoadNewSound(FileName,SOUND_FIRE_PISTOL);
 sprintf(FileName,"%ssound\\shotgun.dhs",Path);
 cSound.LoadNewSound(FileName,SOUND_FIRE_SHOTGUN);
 sprintf(FileName,"%ssound\\dog.dhs",Path);
 cSound.LoadNewSound(FileName,SOUND_DOG);
 sprintf(FileName,"%ssound\\duck.dhs",Path);
 cSound.LoadNewSound(FileName,SOUND_DUCK);
 sprintf(FileName,"%ssound\\laugh.dhs",Path);
 cSound.LoadNewSound(FileName,SOUND_LAUGH);
 delete(FileName);
}
void CSoundControl::Play(int ID)
{
 if (LastID==ID)
 {
  u64 tick_frequency=sceRtcGetTickResolution();//текущее значение частоты
  u64 current_tick;
  sceRtcGetCurrentTick(&current_tick);//текущее значение частоты
  double time_span=((double)(current_tick-LastID_tick))/(double)tick_frequency;//прошедшее время
  if (time_span<0.1) return;//почти одновременные одинаковые звуки запрещаем
 }
 cSound.Play(ID);
 LastID=ID;
 sceRtcGetCurrentTick(&LastID_tick);//запоминаем время
}
void CSoundControl::StopAllSound(void)
{
 LastID=-1;
 cSound.StopAllSound();
}
bool CSoundControl::CheckEndAllSound(void)
{
 return(cSound.CheckEndAllSound());
}
