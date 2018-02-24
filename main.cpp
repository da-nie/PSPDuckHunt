#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <pspdisplay.h>
#include <string.h>
//----------------------------------------------------------------------------------------
#include "cgame.h"
#include "video.h"
#include "cfonta.h"
#include "cfontb.h"
#include "csound.h"
#include "cmenu.h"
//----------------------------------------------------------------------------------------
extern CFontA cFontA;
extern CFontB cFontB;
extern CSound cSound;
extern CSoundControl cSoundControl;
//----------------------------------------------------------------------------------------

PSP_MODULE_INFO("DuckHunt", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER|THREAD_ATTR_VFPU);

void dump_threadstatus(void);

bool done=false;

int exit_callback(int arg1,int arg2,void *common)
{
 done=true;
 return(0);
}
void audio_callback(void* buf,unsigned int length,void *userdata)
{
 cSound.CallBack(buf,length,userdata);
}
int CallbackThread(SceSize args, void *argp)
{
 int cbid;
 cbid=sceKernelCreateCallback("Exit Callback",exit_callback,NULL);
 sceKernelRegisterExitCallback(cbid);
 sceKernelSleepThreadCB();
 return(0);
}
int SetupCallbacks(void)
{
 int thid = 0;
 thid=sceKernelCreateThread("update_thread",CallbackThread,0x11,0xFA0,0,0);
 if(thid>=0) sceKernelStartThread(thid, 0, 0);
 return(thid);
}
//----------------------------------------------------------------------------------------
//���������� ��������
void SaveSetting(char *Path,bool two_duck,int sensitivity_x,int sensitivity_y)
{
 char *FileName=new char[strlen(Path)+256];
 sprintf(FileName,"%ssave\\setting.cfg",Path);
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_WRONLY|PSP_O_CREAT,0777);//��������� ����
 if (SceUID_File<=0)//������ �������� �����
 {
  delete(FileName);
  return;
 }
 //��������� ��������
 sceIoWrite(SceUID_File,&two_duck,sizeof(bool));
 sceIoWrite(SceUID_File,&sensitivity_x,sizeof(int));
 sceIoWrite(SceUID_File,&sensitivity_y,sizeof(int));
 sceIoClose(SceUID_File);
 delete(FileName);
}
//�������� ��������
void LoadSetting(char *Path,bool two_duck,int &sensitivity_x,int &sensitivity_y)
{
 char *FileName=new char[strlen(Path)+256];
 sprintf(FileName,"%ssave\\setting.cfg",Path);
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_RDONLY,0777);//��������� ����
 if (SceUID_File<=0)//������ �������� �����
 {
  delete(FileName);
  return;
 }
 sceIoRead(SceUID_File,&two_duck,sizeof(bool));
 sceIoRead(SceUID_File,&sensitivity_x,sizeof(int));
 sceIoRead(SceUID_File,&sensitivity_y,sizeof(int));
 sceIoClose(SceUID_File);
 delete(FileName);
}
//----------------------------------------------------------------------------------------
//�������� ���������
int main(int argc, char  **argv)
{
 int n;
 int argv_len=strlen(argv[0]);
 //��������� ��� �����
 //���������� �� �����
 for(n=argv_len;n>0;n--)
 {
  if (argv[0][n-1]=='/')
  {
   argv[0][n]=0;//�������� ������
   break;
  }
 }
 //������������� �����������
 SetupCallbacks();
 //���������� ������� ��������� ������
 cSound.SetCallBackFunction(audio_callback);
 //�������������� ����
 pspAudioInit();
 //�������������� ����������� �����
 Video_InitDisplay();
 Video_SetDisplayPage(0);
 //����������� ����������
 sceCtrlSetSamplingCycle(0);
 sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
 //��������� �����
 char *FileName=new char[strlen(argv[0])+255];
 sprintf(FileName,"%ssprites\\fonta.tga",argv[0]);
 cFontA.Load(FileName,83,175,71);
 sprintf(FileName,"%ssprites\\fontb.tga",argv[0]);
 cFontB.Load(FileName,0,0,0);
 delete(FileName);
 //��������� �����
 cSoundControl.Create(argv[0]);
 //��������� ����
 CMenu cMenu;
 cMenu.Create(argv[0]);
 CGame cGame;
 cGame.Create(argv[0]);
 bool two_duck=false;
 int sensitivity_x=20;
 int sensitivity_y=20;
 LoadSetting(argv[0],two_duck,sensitivity_x,sensitivity_y);
 while(1)
 {
  if (cMenu.Activate(argv[0],two_duck,sensitivity_x,sensitivity_y)==false) break;//�����
  //����� - ��������� ����
  int score=cGame.Activate(argv[0],two_duck,sensitivity_x,sensitivity_y);
  if (score<0) break;//�����
  //������ ������� ��������
  if (cMenu.InputHiScore(score,argv[0])==false) break;//�����
 }
 SaveSetting(argv[0],two_duck,sensitivity_x,sensitivity_y);
 //��������� ����
 pspAudioEnd();
 //������� �� ���������
 sceKernelExitGame();
 return(0);
}

