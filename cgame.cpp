#include "cgame.h"

extern bool done;
extern CFontA cFontA;
extern CSoundControl cSoundControl;
extern SVideo_DisplaySetting sVideo_DisplaySetting;
//--------------------------------------------------------------------------
CGame::CGame(void)
{
}
CGame::~CGame()
{
 Release();
}
void CGame::Create(char *Path)
{
 int n;
 char *FileName=new char[strlen(Path)+255];
 sprintf(FileName,"%ssprites\\back.tga",Path);
 cSprite_Back.Load(FileName);
 sprintf(FileName,"%ssprites\\status.tga",Path);
 cSprite_Status.Load(FileName);
 sprintf(FileName,"%ssprites\\grass.tga",Path);
 cSprite_Grass.Load(FileName);
 sprintf(FileName,"%ssprites\\treelittle.tga",Path);
 cSprite_TreeLittle.Load(FileName);
 sprintf(FileName,"%ssprites\\treebig.tga",Path);
 cSprite_TreeBig.Load(FileName);
 sprintf(FileName,"%ssprites\\cross.tga",Path);
 cSprite_Cross.Load(FileName);
 sprintf(FileName,"%ssprites\\dog.tga",Path);
 cSprite_Dog.Load(FileName);
 sprintf(FileName,"%ssprites\\duck.tga",Path);
 cSprite_Duck.Load(FileName);
 sprintf(FileName,"%ssprites\\pistol.tga",Path);
 cSprite_Pistol.Load(FileName);
 sprintf(FileName,"%ssprites\\shotgun.tga",Path);
 cSprite_Shotgun.Load(FileName);
 //����� ���������� ����
 cSprite_Grass.SetAlpha(0,83,175,71);
 cSprite_TreeLittle.SetAlpha(0,83,175,71);
 cSprite_TreeBig.SetAlpha(0,83,175,71);
 cSprite_Cross.SetAlpha(0,83,175,71);
 cSprite_Dog.SetAlpha(0,83,175,71);
 cSprite_Duck.SetAlpha(0,83,175,71);
 cSprite_Pistol.SetAlpha(0,83,175,71);
 cSprite_Shotgun.SetAlpha(0,83,175,71);

 WorkingAreaWidth=sVideo_DisplaySetting.ScreenWidth-cSprite_Status.GetWidth();
 WorkingAreaHeight=sVideo_DisplaySetting.ScreenHeight;
 cDuckMap.Init(WorkingAreaWidth,WorkingAreaHeight,cSprite_Grass.GetHeight(),&cSprite_Duck);
 cDogMap.Init(WorkingAreaWidth,WorkingAreaHeight,cSprite_Grass.GetHeight(),&cSprite_Dog);

 sPlayer.PistolFrameSizeX=cSprite_Pistol.GetWidth()/3;
 sPlayer.PistolFrameSizeY=cSprite_Pistol.GetHeight();

 sPlayer.ShotgunFrameSizeX=cSprite_Shotgun.GetWidth()/6;
 sPlayer.ShotgunFrameSizeY=cSprite_Shotgun.GetHeight();
 //������ �������� ������
 sAnimate_PistolPtr=new SAnimate[200];//�������� ���������
 sAnimate_ShotgunPtr=new SAnimate[200];//�������� ���������
 int index=0;
 //�������� ��������� ���������
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_NORMAL,PISTOL_BASIC,0,0);index++;
 //�����
 sPlayer.PistolFireFrame=index;//���� ������ �������� �� ���������
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_FIRE_1,0,0);index++;
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_FIRE_2,0,0);index++;
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_FIRE_1,0,0);index++;
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_NORMAL,PISTOL_BASIC,0,0);index++;
 //��������� ������
 sPlayer.PistolHideFrame=index;//���� �������� ���������
 int ph=sPlayer.PistolFrameSizeY/20+1;
 for(n=0;n<=ph;n++)
 {
  if (n!=ph) SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_BASIC,0,20);
        else SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_HIDE,PISTOL_BASIC,0,20);
  index++;
 }
 //������ ������
 sPlayer.PistolShowFrame=index;//���� ���������� ���������
 for(n=0;n<=ph;n++)
 {
  if (n!=ph) SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_BASIC,0,-20);
        else SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_NORMAL,PISTOL_BASIC,0,-20);
  index++;
 }
 //�������� ��������� ���������
 index=0;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_NORMAL,SHOTGUN_BASIC,0,0);index++;
 //�����
 sPlayer.ShotgunFireFrame=index;//���� ������ �������� �� ���������
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_1,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_2,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_1,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_3,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_4,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_5,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_4,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_3,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_NORMAL,SHOTGUN_BASIC,0,0);index++;
 //����� ������
 sPlayer.ShotgunHideFrame=index;//���� �������� ���������
 ph=sPlayer.ShotgunFrameSizeY/20+1;
 for(n=0;n<=ph;n++)
 {
  if (n!=ph) SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_BASIC,0,20);
        else SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_HIDE,SHOTGUN_BASIC,0,20);
  index++;
 }
 //������ ������
 sPlayer.ShotgunShowFrame=index;//���� ���������� ���������
 for(n=0;n<=ph;n++)
 {
  if (n!=ph) SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_BASIC,0,-20);
        else SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_NORMAL,SHOTGUN_BASIC,0,-20);
  index++;
 }
}
void CGame::Release(void)
{
 cSprite_Back.Release();
 cSprite_Status.Release();
 cSprite_Grass.Release();
 cSprite_TreeLittle.Release();
 cSprite_TreeBig.Release();
 cSprite_Cross.Release();
 cSprite_Dog.Release();
 cSprite_Duck.Release();
 cSprite_Pistol.Release();
 cSprite_Shotgun.Release();
 delete(sAnimate_PistolPtr);
 delete(sAnimate_ShotgunPtr);
}
//--------------------------------------------------------------------------
void CGame::SaveScreenShot(char *Path)
{
 char *FileName=new char[strlen(Path)+256];
 //���� ��������� �������
 int index=1;
 while(done==false)
 {
  sprintf(FileName,"%sscreen/screen%i.tga",Path,index);
  SceUID SceUID_File;
  SceUID_File=sceIoOpen(FileName,PSP_O_RDONLY,0777);//��������� ����
  if (SceUID_File<0) break;//������ ����� ���
  sceIoClose(SceUID_File);
  index++;
 }
 Video_SaveScreenAsTGA(FileName);
 delete(FileName);
}

int CGame::Activate(char *Path,bool two_duck,int sensitivity_x,int sensitivity_y)
{
 u64 tick_frequency=sceRtcGetTickResolution();
 u64 begin_tick;
 u64 current_tick;

 sPlayer.Score=0;
 sPlayer.Level=1;
 sPlayer.XCross=0;
 sPlayer.YCross=0;
 sPlayer.SelectedWeapon=0;//������ ��������
 sPlayer.SelectedNextWeapon=sPlayer.SelectedWeapon;
 sPlayer.PistoldY=0;
 sPlayer.ShotgundY=sPlayer.ShotgunFrameSizeY/20+1;
 sPlayer.ShotgundY*=20;
 sPlayer.PistolFrame=0;
 sPlayer.ShotgunFrame=0;
 sPlayer.WeaponAnimateCounter=0;

 cDuckMap.SetEnabledDuck(true,two_duck);
 while(done==false)
 {
  //�������� �������
  sPlayer.Ammo[0]=30;
  sPlayer.Ammo[1]=-1;//��������� ���
  if (sPlayer.Level>=10) sPlayer.Ammo[1]=30;//��� ��������
  sPlayer.SlipAmount=0;//�������� ���
  int dl=(int)((sPlayer.Level-1)*0.3);
  if (dl>9) dl=9;
  sPlayer.SlipMax=9-dl;
  if (two_duck==true) sPlayer.SlipMax*=2;//���� ���� ����������� �� ���, �� ��������� ���������� ���������� ��������
  cDuckMap.InitLevel(sPlayer.Level);
  cDogMap.InitLevel();
  sPlayer.Duck=0;
  while(1)
  {
   if (done==true) break;
   sceRtcGetCurrentTick(&begin_tick);//������� �������� �������
   cDuckMap.DuckControl();//��������� ������
   //��������� ����
   int dog_mode=cDogMap.GetDogMode();
   if (dog_mode==DOG_MODE_BASIC)//������ ���, ����� ��������
   {
    //��������� ����, ���� �����
    if (cDuckMap.LaunchDuck()==true) sPlayer.Bullet=4;//��� ������� ������, ���� �� ��������� ����
    int res=cDuckMap.CheckEndDuckHunt();
    if (res>=0)//���� ��������
    {
     //�������� ������ � ��������� �����
     if (res==0)
     {
      cDogMap.DogLOL();
      sPlayer.SlipAmount++;
      if (two_duck==true) sPlayer.SlipAmount++;
     }
     if (res==1)
     {
      cDogMap.DogOneDuck();
      if (two_duck==true) sPlayer.SlipAmount++;
     }
     if (res==2) cDogMap.DogTwoDuck();
    }
   }
   //�������� ������
   WeaponProcessing();
   if (Control(Path,sensitivity_x,sensitivity_y)==false) return(sPlayer.Score);//������ �����
   bool duck1_enabled;//��� �������� ��������� ����� �������� ���������� ����, ������� ����� ��� �����������
   bool duck2_enabled;
   cDuckMap.GetEnabledDuck(duck1_enabled,duck2_enabled);
   if (duck1_enabled==true && duck2_enabled==true) two_duck=true;//����� � ����� ������
                                              else two_duck=false;//����� � ����� �����
   //����� �������
   cSprite_Back.Put(0,0,false);
   //������ ��� � ������
   if (dog_mode!=DOG_MODE_BASIC && dog_mode!=DOG_MODE_BASIC_FINAL)
   {
    if (!(dog_mode==DOG_MODE_ANIMATE_BACK || dog_mode==DOG_MODE_ANIMATE_BACK_AND_LAUGH || dog_mode==DOG_MODE_ANIMATE_BACK_LOL)) DrawGameMap();//������� ������ ��������� ���
    cDogMap.PutDog();
    if (dog_mode==DOG_MODE_ANIMATE_BACK || dog_mode==DOG_MODE_ANIMATE_BACK_AND_LAUGH || dog_mode==DOG_MODE_ANIMATE_BACK_LOL) DrawGameMap();//����� ��� ��������� ������
    cDogMap.Processing();
   }
   else DrawGameMap();//������ ���, ���� ������ ���
   //������ ����������� �������
   DrawCross();
   //������ ������ �������
   cSprite_Status.Put(WorkingAreaWidth,0,false);
   //������� ��������� ������
   char string[255];
   sprintf(string,"%i",sPlayer.SlipAmount);
   int px=(sVideo_DisplaySetting.ScreenWidth-WorkingAreaWidth-cFontA.GetStringWidth(string))/2+WorkingAreaWidth;
   cFontA.PrintAt(px,10+32*0,string,true);
   sprintf(string,"%i",sPlayer.Bullet);
   px=(sVideo_DisplaySetting.ScreenWidth-WorkingAreaWidth-cFontA.GetStringWidth(string))/2+WorkingAreaWidth;
   cFontA.PrintAt(px,10+32*2,string,true);
   sprintf(string,"%i",sPlayer.SlipMax);
   px=(sVideo_DisplaySetting.ScreenWidth-WorkingAreaWidth-cFontA.GetStringWidth(string))/2+WorkingAreaWidth;
   cFontA.PrintAt(px,5+32*3,string,true);
   sprintf(string,"%i",sPlayer.Level);
   px=(sVideo_DisplaySetting.ScreenWidth-WorkingAreaWidth-cFontA.GetStringWidth(string))/2+WorkingAreaWidth;
   cFontA.PrintAt(px,10+32*4,string,true);
   sprintf(string,"%i",sPlayer.Ammo[0]);
   px=(sVideo_DisplaySetting.ScreenWidth-WorkingAreaWidth-cFontA.GetStringWidth(string))/2+WorkingAreaWidth;
   cFontA.PrintAt(px,5+32*5,string,true);
   if (sPlayer.Ammo[1]>=0) sprintf(string,"%i",sPlayer.Ammo[1]);
                      else sprintf(string,"-");
   px=(sVideo_DisplaySetting.ScreenWidth-WorkingAreaWidth-cFontA.GetStringWidth(string))/2+WorkingAreaWidth;
   cFontA.PrintAt(px,5+32*6,string,true);
   sprintf(string,"%i",sPlayer.Score);
   px=(sVideo_DisplaySetting.ScreenWidth-WorkingAreaWidth-cFontA.GetStringWidth(string))/2+WorkingAreaWidth;
   cFontA.PrintAt(px,10+32*7,string,true);

   if (dog_mode==DOG_MODE_BASIC_FINAL)//���������� �������� � �������� ����
   {
    if (sAnimate_ShotgunPtr[sPlayer.ShotgunFrame].Mode!=WEAPON_MODE_ANIMATE && sAnimate_PistolPtr[sPlayer.PistolFrame].Mode!=WEAPON_MODE_ANIMATE)
    {
     cDogMap.DogBasic();
     cDuckMap.InitLevel(sPlayer.Level);
     sPlayer.Duck++;
     if (sPlayer.Duck==10) break;//������� ��������
    }
   }
   Video_ViewDisplayPage();
   Video_ChangeDisplayPage();
   //�������������� �� �������
   while(done==false)
   {
    sceRtcGetCurrentTick(&current_tick);//������� �������� �������
    double time_span=((double)(current_tick-begin_tick))/(double)tick_frequency;//��������� �����
    if (time_span>=0.02) break;//50 FPS
   }
  }
  //�������� ���������� ������
  if (sPlayer.SlipMax<sPlayer.SlipAmount) //����� ����
  {
   //������� "����� ����"
   cFontA.PrintAt(150,WorkingAreaHeight/2-4,"����� ����.",true);
   Video_ViewDisplayPage();
   Video_ChangeDisplayPage();
   sceKernelDelayThread(tick_frequency);
   sceKernelDelayThread(tick_frequency);
   sceKernelDelayThread(tick_frequency);
   sceKernelDelayThread(tick_frequency);
   break;
  }
  sPlayer.Level++;
  //������� "����� ����"
  cFontA.PrintAt(150,WorkingAreaHeight/2-4,"������� �������.",true);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
 }
 if (done==true) return(-1);//���������� ����� �� ����
 return(sPlayer.Score);//���������� ��������� ����
}
bool CGame::Control(char *Path,int sensitivity_x,int sensitivity_y)
{
 SceCtrlData pad;
 sceCtrlReadBufferPositive(&pad,1);//��������� ������� � ��������
 int dx=(pad.Lx-127);
 int dy=(pad.Ly-127);
 if (fabs(dx)<10) dx=0;
 if (fabs(dy)<10) dy=0;
 dx/=sensitivity_x;
 dy/=sensitivity_y;
 sPlayer.XCross+=dx;
 sPlayer.YCross+=dy;
 if (sPlayer.XCross<(cSprite_Cross.GetWidth()>>1)) sPlayer.XCross=(cSprite_Cross.GetWidth()>>1);
 if (sPlayer.XCross>=WorkingAreaWidth-1-(cSprite_Cross.GetWidth()>>1)) sPlayer.XCross=WorkingAreaWidth-(cSprite_Cross.GetWidth()>>1)-1;
 if (sPlayer.YCross<(cSprite_Cross.GetHeight()>>1)) sPlayer.YCross=(cSprite_Cross.GetHeight()>>1);
 if (sPlayer.YCross>=WorkingAreaHeight-(cSprite_Cross.GetHeight()>>1)) sPlayer.YCross=WorkingAreaHeight-1-(cSprite_Cross.GetHeight()>>1);
 if (pad.Buttons&PSP_CTRL_START) return(false);
 if (pad.Buttons&PSP_CTRL_DOWN && pad.Buttons&PSP_CTRL_RIGHT)
 {
  //��������� ���������� ������
  if (SaveState(Path)==true) cFontA.PrintAt(150,WorkingAreaHeight/2-4,"���� ��������.",true);
                        else cFontA.PrintAt(150,WorkingAreaHeight/2-4,"������ ������.",true);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  u64 tick_frequency=sceRtcGetTickResolution();
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
 }
 if (pad.Buttons&PSP_CTRL_UP && pad.Buttons&PSP_CTRL_RIGHT)
 {
  //��������� ���������� ������
  if (LoadState(Path)==true) cFontA.PrintAt(150,WorkingAreaHeight/2-4,"���� ���������.",true);
                        else cFontA.PrintAt(150,WorkingAreaHeight/2-4,"������ ��������.",true);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  u64 tick_frequency=sceRtcGetTickResolution();
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
 }
 if (pad.Buttons&PSP_CTRL_TRIANGLE)
 {
  cFontA.PrintAt(10,WorkingAreaHeight/2-4,"�����.��� ������������� ���� ������� `����`.",true);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  while(1)
  {
   sceCtrlReadBufferPositive(&pad,1);//��������� ������� � ��������
   if (pad.Buttons&PSP_CTRL_CIRCLE) break;
  }
 }
 if (pad.Buttons&PSP_CTRL_SELECT) SaveScreenShot(Path);
 if (pad.Buttons&PSP_CTRL_RTRIGGER)
 {
  if (sAnimate_ShotgunPtr[sPlayer.ShotgunFrame].Mode==WEAPON_MODE_ANIMATE) return(true);
  if (sAnimate_PistolPtr[sPlayer.PistolFrame].Mode==WEAPON_MODE_ANIMATE) return(true);
  if (sPlayer.SelectedWeapon!=0)
  {
   sPlayer.SelectedNextWeapon=0;//������ ��������
   sPlayer.ShotgunFrame=sPlayer.ShotgunHideFrame;//������� ��������
   sPlayer.WeaponAnimateCounter=0;
  }
 }
 if (pad.Buttons&PSP_CTRL_LTRIGGER && sPlayer.Ammo[1]>=0)
 {
  if (sAnimate_ShotgunPtr[sPlayer.ShotgunFrame].Mode==WEAPON_MODE_ANIMATE) return(true);
  if (sAnimate_PistolPtr[sPlayer.PistolFrame].Mode==WEAPON_MODE_ANIMATE) return(true);
  if (sPlayer.SelectedWeapon!=1)
  {
   sPlayer.SelectedNextWeapon=1;//������ ��������
   sPlayer.PistolFrame=sPlayer.PistolHideFrame;//������� ��������
   sPlayer.WeaponAnimateCounter=0;
  }
 }
 if (pad.Buttons&PSP_CTRL_CROSS && sPlayer.Bullet>0)//������ �����
 {
  int dog_mode=cDogMap.GetDogMode();
  if (dog_mode!=DOG_MODE_BASIC && dog_mode!=DOG_MODE_ANIMATE_BACK_LOL) return(true);//������ ��������
  if (sPlayer.Ammo[sPlayer.SelectedWeapon]>0)//���� �������
  {
   if (sPlayer.SelectedWeapon==0)//�������� �� ���������
   {
    SAnimate sAnimate=sAnimate_PistolPtr[sPlayer.PistolFrame];
    if (sAnimate.Mode!=WEAPON_MODE_NORMAL) return(true);//�������� �� �����
    sPlayer.PistolFrame=sPlayer.PistolFireFrame;//��������
    sPlayer.WeaponAnimateCounter=0;
    cSoundControl.Play(SOUND_FIRE_PISTOL);
   }
   if (sPlayer.SelectedWeapon==1)//�������� �� ���������
   {
    SAnimate sAnimate=sAnimate_ShotgunPtr[sPlayer.ShotgunFrame];
    if (sAnimate.Mode!=WEAPON_MODE_NORMAL) return(true);//�������� �� �����
    sPlayer.ShotgunFrame=sPlayer.ShotgunFireFrame;//��������
    sPlayer.WeaponAnimateCounter=0;
    cSoundControl.Play(SOUND_FIRE_SHOTGUN);
   }
   sPlayer.Bullet--;
   sPlayer.Ammo[sPlayer.SelectedWeapon]--;
   sPlayer.Score+=cDuckMap.Fire(sPlayer.XCross,sPlayer.YCross,sPlayer.SelectedWeapon+1);
   if (dog_mode==DOG_MODE_ANIMATE_BACK_LOL)//�������� �� ��������� ������ :)
   {
    cDogMap.Fire(sPlayer.XCross,sPlayer.YCross,sPlayer.SelectedWeapon+1);
   }
  }
 }
 return(true);
}

void CGame::DrawGameMap(void)
{
 int x,y;
 //������ ����
 cDuckMap.PutDuck();
 //������ ������
 x=100;
 y=WorkingAreaHeight-cSprite_Grass.GetHeight()-cSprite_TreeBig.GetHeight()+10;
 cSprite_TreeBig.Put(x,y,true);

 x=300;
 y=WorkingAreaHeight-cSprite_Grass.GetHeight()-cSprite_TreeLittle.GetHeight()+10;
 cSprite_TreeLittle.Put(x,y,true);

 y=WorkingAreaHeight-cSprite_Grass.GetHeight();
 for(x=0;x<WorkingAreaWidth;x+=cSprite_Grass.GetWidth()) cSprite_Grass.Put(x,y,true);
}
void CGame::DrawCross(void)
{
 int x,y;
 int frame;
 //������ ����������� �������
 cSprite_Cross.Put(sPlayer.XCross-(cSprite_Cross.GetWidth()>>1),sPlayer.YCross-(cSprite_Cross.GetHeight()>>1),true);
 //������ ������
 int dy=((20*sPlayer.YCross)/WorkingAreaHeight);
 if (sPlayer.SelectedWeapon==0)//������ ��������
 {
  x=sPlayer.XCross-(sPlayer.PistolFrameSizeX>>2);
  y=WorkingAreaHeight-sPlayer.PistolFrameSizeY+dy+sPlayer.PistoldY;
  frame=sAnimate_PistolPtr[sPlayer.PistolFrame].Frame;
  cSprite_Pistol.PutSpriteItem(x,y,frame*sPlayer.PistolFrameSizeX,0,sPlayer.PistolFrameSizeX,sPlayer.PistolFrameSizeY,true);
 }
 if (sPlayer.SelectedWeapon==1)//������ ��������
 {
  x=sPlayer.XCross-(sPlayer.ShotgunFrameSizeX>>1);
  y=WorkingAreaHeight-sPlayer.ShotgunFrameSizeY+dy+sPlayer.ShotgundY;
  frame=sAnimate_ShotgunPtr[sPlayer.ShotgunFrame].Frame;
  cSprite_Shotgun.PutSpriteItem(x,y,frame*sPlayer.ShotgunFrameSizeX,0,sPlayer.ShotgunFrameSizeX,sPlayer.ShotgunFrameSizeY,true);
 }
}
//�������� ������
void CGame::WeaponProcessing(void)
{
 if (sPlayer.WeaponAnimateCounter>=5)
 {
  sPlayer.WeaponAnimateCounter=0;
  SAnimate sAnimate;
  if (sPlayer.SelectedWeapon==0)//�������� ���������
  {
   sAnimate=sAnimate_PistolPtr[sPlayer.PistolFrame];
   if (sAnimate.Mode==WEAPON_MODE_ANIMATE)
   {
    sPlayer.PistoldY+=sAnimate.dY;
    sPlayer.PistolFrame++;
   }
   if (sAnimate.Mode==WEAPON_MODE_HIDE)
   {
    sPlayer.SelectedWeapon=sPlayer.SelectedNextWeapon;
    sPlayer.ShotgunFrame=sPlayer.ShotgunShowFrame;
   }
  }
  if (sPlayer.SelectedWeapon==1)//�������� ���������
  {
   sAnimate=sAnimate_ShotgunPtr[sPlayer.ShotgunFrame];
   if (sAnimate.Mode==WEAPON_MODE_ANIMATE)
   {
    sPlayer.ShotgundY+=sAnimate.dY;
    sPlayer.ShotgunFrame++;
   }
   if (sAnimate.Mode==WEAPON_MODE_HIDE)
   {
    sPlayer.SelectedWeapon=sPlayer.SelectedNextWeapon;
    sPlayer.PistolFrame=sPlayer.PistolShowFrame;
   }
  }
 }
 else sPlayer.WeaponAnimateCounter++;
}
//��������� ��������� ������
bool CGame::SaveState(char *Path)
{
 char *FileName=new char[strlen(Path)+256];
 sprintf(FileName,"%ssave\\state.set",Path);
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_WRONLY|PSP_O_CREAT,0777);//��������� ����
 if (SceUID_File>=0)
 {
  sceIoWrite(SceUID_File,&sPlayer,sizeof(SPlayer));//���������� ��������� ������
  cDuckMap.SaveState(SceUID_File);//���������� ��������� ����
  cDogMap.SaveState(SceUID_File);//���������� ��������� �����
  sceIoClose(SceUID_File);
  delete(FileName);
  return(true);
 }
 delete(FileName);
 return(false);
}
//��������� ��������� ������
bool CGame::LoadState(char *Path)
{
 char *FileName=new char[strlen(Path)+256];
 sprintf(FileName,"%ssave\\state.set",Path);
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_RDONLY,0777);//��������� ����
 if (SceUID_File>=0)
 {
  sceIoRead(SceUID_File,&sPlayer,sizeof(SPlayer));//������ ��������� ������
  cDuckMap.LoadState(SceUID_File);//������ ��������� ����
  cDogMap.LoadState(SceUID_File);//������ ��������� �����
  sceIoClose(SceUID_File);
  delete(FileName);
  return(true);
 }
 delete(FileName);
 return(false);
}

