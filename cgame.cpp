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
 //задаём прозрачный цвет
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
 //создаём анимацию оружия
 sAnimate_PistolPtr=new SAnimate[200];//анимация пистолета
 sAnimate_ShotgunPtr=new SAnimate[200];//анимация дробовика
 int index=0;
 //основное состояние пистолета
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_NORMAL,PISTOL_BASIC,0,0);index++;
 //огонь
 sPlayer.PistolFireFrame=index;//кадр начала стрельбы из пистолета
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_FIRE_1,0,0);index++;
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_FIRE_2,0,0);index++;
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_FIRE_1,0,0);index++;
 SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_NORMAL,PISTOL_BASIC,0,0);index++;
 //опускание оружия
 sPlayer.PistolHideFrame=index;//кадр убирания пистолета
 int ph=sPlayer.PistolFrameSizeY/20+1;
 for(n=0;n<=ph;n++)
 {
  if (n!=ph) SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_BASIC,0,20);
        else SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_HIDE,PISTOL_BASIC,0,20);
  index++;
 }
 //подъём оружия
 sPlayer.PistolShowFrame=index;//кадр поднимания пистолета
 for(n=0;n<=ph;n++)
 {
  if (n!=ph) SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_ANIMATE,PISTOL_BASIC,0,-20);
        else SetAnimate(sAnimate_PistolPtr+index,WEAPON_MODE_NORMAL,PISTOL_BASIC,0,-20);
  index++;
 }
 //основное состояние дробовика
 index=0;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_NORMAL,SHOTGUN_BASIC,0,0);index++;
 //огонь
 sPlayer.ShotgunFireFrame=index;//кадр начала стрельбы из дробовика
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_1,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_2,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_1,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_3,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_4,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_5,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_4,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_FIRE_3,0,0);index++;
 SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_NORMAL,SHOTGUN_BASIC,0,0);index++;
 //смена оружия
 sPlayer.ShotgunHideFrame=index;//кадр убирания дробовика
 ph=sPlayer.ShotgunFrameSizeY/20+1;
 for(n=0;n<=ph;n++)
 {
  if (n!=ph) SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_ANIMATE,SHOTGUN_BASIC,0,20);
        else SetAnimate(sAnimate_ShotgunPtr+index,WEAPON_MODE_HIDE,SHOTGUN_BASIC,0,20);
  index++;
 }
 //подъём оружия
 sPlayer.ShotgunShowFrame=index;//кадр поднимания дробовика
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
 //ищем свободную картику
 int index=1;
 while(done==false)
 {
  sprintf(FileName,"%sscreen/screen%i.tga",Path,index);
  SceUID SceUID_File;
  SceUID_File=sceIoOpen(FileName,PSP_O_RDONLY,0777);//открываем файл
  if (SceUID_File<0) break;//такого файла нет
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
 sPlayer.SelectedWeapon=0;//выбран пистолет
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
  //начинаем уровень
  sPlayer.Ammo[0]=30;
  sPlayer.Ammo[1]=-1;//дробовика нет
  if (sPlayer.Level>=10) sPlayer.Ammo[1]=30;//даём дробовик
  sPlayer.SlipAmount=0;//промахов нет
  int dl=(int)((sPlayer.Level-1)*0.3);
  if (dl>9) dl=9;
  sPlayer.SlipMax=9-dl;
  if (two_duck==true) sPlayer.SlipMax*=2;//если утки запускались по две, то удваиваем количество допустимых промахов
  cDuckMap.InitLevel(sPlayer.Level);
  cDogMap.InitLevel();
  sPlayer.Duck=0;
  while(1)
  {
   if (done==true) break;
   sceRtcGetCurrentTick(&begin_tick);//текущее значение частоты
   cDuckMap.DuckControl();//управляем утками
   //запускаем уток
   int dog_mode=cDogMap.GetDogMode();
   if (dog_mode==DOG_MODE_BASIC)//собаки нет, можно начинать
   {
    //запускаем уток, если нужно
    if (cDuckMap.LaunchDuck()==true) sPlayer.Bullet=4;//даём патроны игроку, если мы запускали уток
    int res=cDuckMap.CheckEndDuckHunt();
    if (res>=0)//утки отлетали
    {
     //поместим собаку в случайном месте
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
   //анимация оружия
   WeaponProcessing();
   if (Control(Path,sensitivity_x,sensitivity_y)==false) return(sPlayer.Score);//нажали выход
   bool duck1_enabled;//при загрузке состояния может изменить количество уток, поэтому будем это отслеживать
   bool duck2_enabled;
   cDuckMap.GetEnabledDuck(duck1_enabled,duck2_enabled);
   if (duck1_enabled==true && duck2_enabled==true) two_duck=true;//режим с двумя утками
                                              else two_duck=false;//режим с одной уткой
   //вывод графики
   cSprite_Back.Put(0,0,false);
   //рисуем фон и собаку
   if (dog_mode!=DOG_MODE_BASIC && dog_mode!=DOG_MODE_BASIC_FINAL)
   {
    if (!(dog_mode==DOG_MODE_ANIMATE_BACK || dog_mode==DOG_MODE_ANIMATE_BACK_AND_LAUGH || dog_mode==DOG_MODE_ANIMATE_BACK_LOL)) DrawGameMap();//сначала собака закрывает фон
    cDogMap.PutDog();
    if (dog_mode==DOG_MODE_ANIMATE_BACK || dog_mode==DOG_MODE_ANIMATE_BACK_AND_LAUGH || dog_mode==DOG_MODE_ANIMATE_BACK_LOL) DrawGameMap();//потом фон закрывает собаку
    cDogMap.Processing();
   }
   else DrawGameMap();//рисуем фон, если собаки нет
   //рисуем перекрестье прицела
   DrawCross();
   //рисуем панель статуса
   cSprite_Status.Put(WorkingAreaWidth,0,false);
   //выводим состояние игрока
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

   if (dog_mode==DOG_MODE_BASIC_FINAL)//отработана анимация с подъёмом уток
   {
    if (sAnimate_ShotgunPtr[sPlayer.ShotgunFrame].Mode!=WEAPON_MODE_ANIMATE && sAnimate_PistolPtr[sPlayer.PistolFrame].Mode!=WEAPON_MODE_ANIMATE)
    {
     cDogMap.DogBasic();
     cDuckMap.InitLevel(sPlayer.Level);
     sPlayer.Duck++;
     if (sPlayer.Duck==10) break;//уровень закончен
    }
   }
   Video_ViewDisplayPage();
   Video_ChangeDisplayPage();
   //синхронизируем по таймеру
   while(done==false)
   {
    sceRtcGetCurrentTick(&current_tick);//текущее значение частоты
    double time_span=((double)(current_tick-begin_tick))/(double)tick_frequency;//прошедшее время
    if (time_span>=0.02) break;//50 FPS
   }
  }
  //проверим достижения игрока
  if (sPlayer.SlipMax<sPlayer.SlipAmount) //конец игры
  {
   //выводим "Конец игры"
   cFontA.PrintAt(150,WorkingAreaHeight/2-4,"КОНЕЦ ИГРЫ.",true);
   Video_ViewDisplayPage();
   Video_ChangeDisplayPage();
   sceKernelDelayThread(tick_frequency);
   sceKernelDelayThread(tick_frequency);
   sceKernelDelayThread(tick_frequency);
   sceKernelDelayThread(tick_frequency);
   break;
  }
  sPlayer.Level++;
  //выводим "Конец игры"
  cFontA.PrintAt(150,WorkingAreaHeight/2-4,"УРОВЕНЬ ПРОЙДЕН.",true);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
 }
 if (done==true) return(-1);//экстренный выход из игры
 return(sPlayer.Score);//возвращаем набранные очки
}
bool CGame::Control(char *Path,int sensitivity_x,int sensitivity_y)
{
 SceCtrlData pad;
 sceCtrlReadBufferPositive(&pad,1);//считываем клавиши и джойстик
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
  //сохраняем достижения игрока
  if (SaveState(Path)==true) cFontA.PrintAt(150,WorkingAreaHeight/2-4,"ИГРА ЗАПИСАНА.",true);
                        else cFontA.PrintAt(150,WorkingAreaHeight/2-4,"ОШИБКА ЗАПИСИ.",true);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  u64 tick_frequency=sceRtcGetTickResolution();
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
 }
 if (pad.Buttons&PSP_CTRL_UP && pad.Buttons&PSP_CTRL_RIGHT)
 {
  //загружаем достижения игрока
  if (LoadState(Path)==true) cFontA.PrintAt(150,WorkingAreaHeight/2-4,"ИГРА ЗАГРУЖЕНА.",true);
                        else cFontA.PrintAt(150,WorkingAreaHeight/2-4,"ОШИБКА ЗАГРУЗКИ.",true);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  u64 tick_frequency=sceRtcGetTickResolution();
  sceKernelDelayThread(tick_frequency);
  sceKernelDelayThread(tick_frequency);
 }
 if (pad.Buttons&PSP_CTRL_TRIANGLE)
 {
  cFontA.PrintAt(10,WorkingAreaHeight/2-4,"ПАУЗА.ДЛЯ ВОЗОБНОВЛЕНИЯ ИГРЫ НАЖМИТЕ `КРУГ`.",true);
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  while(1)
  {
   sceCtrlReadBufferPositive(&pad,1);//считываем клавиши и джойстик
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
   sPlayer.SelectedNextWeapon=0;//выбран пистолет
   sPlayer.ShotgunFrame=sPlayer.ShotgunHideFrame;//убираем дробовик
   sPlayer.WeaponAnimateCounter=0;
  }
 }
 if (pad.Buttons&PSP_CTRL_LTRIGGER && sPlayer.Ammo[1]>=0)
 {
  if (sAnimate_ShotgunPtr[sPlayer.ShotgunFrame].Mode==WEAPON_MODE_ANIMATE) return(true);
  if (sAnimate_PistolPtr[sPlayer.PistolFrame].Mode==WEAPON_MODE_ANIMATE) return(true);
  if (sPlayer.SelectedWeapon!=1)
  {
   sPlayer.SelectedNextWeapon=1;//выбран дробовик
   sPlayer.PistolFrame=sPlayer.PistolHideFrame;//убираем пистолет
   sPlayer.WeaponAnimateCounter=0;
  }
 }
 if (pad.Buttons&PSP_CTRL_CROSS && sPlayer.Bullet>0)//нажали огонь
 {
  int dog_mode=cDogMap.GetDogMode();
  if (dog_mode!=DOG_MODE_BASIC && dog_mode!=DOG_MODE_ANIMATE_BACK_LOL) return(true);//нельзя стрелять
  if (sPlayer.Ammo[sPlayer.SelectedWeapon]>0)//есть патроны
  {
   if (sPlayer.SelectedWeapon==0)//стрельба из пистолета
   {
    SAnimate sAnimate=sAnimate_PistolPtr[sPlayer.PistolFrame];
    if (sAnimate.Mode!=WEAPON_MODE_NORMAL) return(true);//пистолет не готов
    sPlayer.PistolFrame=sPlayer.PistolFireFrame;//стреляем
    sPlayer.WeaponAnimateCounter=0;
    cSoundControl.Play(SOUND_FIRE_PISTOL);
   }
   if (sPlayer.SelectedWeapon==1)//стрельба из дробовика
   {
    SAnimate sAnimate=sAnimate_ShotgunPtr[sPlayer.ShotgunFrame];
    if (sAnimate.Mode!=WEAPON_MODE_NORMAL) return(true);//дробовик не готов
    sPlayer.ShotgunFrame=sPlayer.ShotgunFireFrame;//стреляем
    sPlayer.WeaponAnimateCounter=0;
    cSoundControl.Play(SOUND_FIRE_SHOTGUN);
   }
   sPlayer.Bullet--;
   sPlayer.Ammo[sPlayer.SelectedWeapon]--;
   sPlayer.Score+=cDuckMap.Fire(sPlayer.XCross,sPlayer.YCross,sPlayer.SelectedWeapon+1);
   if (dog_mode==DOG_MODE_ANIMATE_BACK_LOL)//стрельба по смеющейся собаке :)
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
 //рисуем уток
 cDuckMap.PutDuck();
 //рисуем пейзаж
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
 //рисуем перекрестье прицела
 cSprite_Cross.Put(sPlayer.XCross-(cSprite_Cross.GetWidth()>>1),sPlayer.YCross-(cSprite_Cross.GetHeight()>>1),true);
 //рисуем оружие
 int dy=((20*sPlayer.YCross)/WorkingAreaHeight);
 if (sPlayer.SelectedWeapon==0)//выбран пистолет
 {
  x=sPlayer.XCross-(sPlayer.PistolFrameSizeX>>2);
  y=WorkingAreaHeight-sPlayer.PistolFrameSizeY+dy+sPlayer.PistoldY;
  frame=sAnimate_PistolPtr[sPlayer.PistolFrame].Frame;
  cSprite_Pistol.PutSpriteItem(x,y,frame*sPlayer.PistolFrameSizeX,0,sPlayer.PistolFrameSizeX,sPlayer.PistolFrameSizeY,true);
 }
 if (sPlayer.SelectedWeapon==1)//выбран дробовик
 {
  x=sPlayer.XCross-(sPlayer.ShotgunFrameSizeX>>1);
  y=WorkingAreaHeight-sPlayer.ShotgunFrameSizeY+dy+sPlayer.ShotgundY;
  frame=sAnimate_ShotgunPtr[sPlayer.ShotgunFrame].Frame;
  cSprite_Shotgun.PutSpriteItem(x,y,frame*sPlayer.ShotgunFrameSizeX,0,sPlayer.ShotgunFrameSizeX,sPlayer.ShotgunFrameSizeY,true);
 }
}
//анимация оружия
void CGame::WeaponProcessing(void)
{
 if (sPlayer.WeaponAnimateCounter>=5)
 {
  sPlayer.WeaponAnimateCounter=0;
  SAnimate sAnimate;
  if (sPlayer.SelectedWeapon==0)//анимация пистолета
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
  if (sPlayer.SelectedWeapon==1)//анимация дробовика
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
//сохранить состояние игрока
bool CGame::SaveState(char *Path)
{
 char *FileName=new char[strlen(Path)+256];
 sprintf(FileName,"%ssave\\state.set",Path);
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_WRONLY|PSP_O_CREAT,0777);//открываем файл
 if (SceUID_File>=0)
 {
  sceIoWrite(SceUID_File,&sPlayer,sizeof(SPlayer));//записываем состояние игрока
  cDuckMap.SaveState(SceUID_File);//записываем состояние уток
  cDogMap.SaveState(SceUID_File);//записываем состояние собак
  sceIoClose(SceUID_File);
  delete(FileName);
  return(true);
 }
 delete(FileName);
 return(false);
}
//загрузить состояние игрока
bool CGame::LoadState(char *Path)
{
 char *FileName=new char[strlen(Path)+256];
 sprintf(FileName,"%ssave\\state.set",Path);
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_RDONLY,0777);//открываем файл
 if (SceUID_File>=0)
 {
  sceIoRead(SceUID_File,&sPlayer,sizeof(SPlayer));//читаем состояние игрока
  cDuckMap.LoadState(SceUID_File);//читаем состояние уток
  cDogMap.LoadState(SceUID_File);//читаем состояние собак
  sceIoClose(SceUID_File);
  delete(FileName);
  return(true);
 }
 delete(FileName);
 return(false);
}

