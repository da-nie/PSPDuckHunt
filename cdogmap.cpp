#include "cdogmap.h"

extern CSoundControl cSoundControl;

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CDogMap::CDogMap(void)
{
 sAnimate_DogPtr=new SAnimate[1000];
 //инициализируем собаку
 int n;
 int index=0;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_MOVE_1,6,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_MOVE_2,6,0);index++;
 for(n=0;n<10;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_MOVE_3,6,0);index++;
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_MOVE_4,6,0);index++;
 }
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_1,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_2,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_1,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_2,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_1,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_2,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_MOVE_1,6,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_MOVE_2,6,0);index++;
 for(n=0;n<4;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_MOVE_3,6,0);index++;
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_MOVE_4,6,0);index++;
 }
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_1,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_2,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_1,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_2,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_1,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_SNIFF_2,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_AND_YIP,DOG_EXCITEMENT,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_EXCITEMENT,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_DASHES_1,10,-15);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_DASHES_1,10,-15);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE,DOG_DASHES_1,10,-15);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_DASHES_2,10,15);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_DASHES_2,10,15);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_DASHES_2,10,15);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_DASHES_2,10,15);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_DASHES_2,10,15);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_DASHES_2,10,15);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_DASHES_2,10,15);index++;
 DogFrameBasic=index;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_BASIC,DOG_DASHES_2,0,0);index++;
 DogFrameLol=index;//собака смеётся
 for(n=0;n<4;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_LOL_1,0,-8);index++;
 }
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK_AND_LAUGH,DOG_LOL_1,0,-8);index++;
 for(n=0;n<5;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK_LOL,DOG_LOL_1,0,0);index++;
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK_LOL,DOG_LOL_2,0,0);index++;
 }
 for(n=0;n<5;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_LOL_2,0,8);index++;
 }
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_BASIC_FINAL,DOG_LOL_2,0,0);index++;
 DogFrameOneDuck=index;//собака с одной уткой
 for(n=0;n<5;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_ONE_DUCK,0,-8);index++;
 }
 for(n=0;n<5;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_ONE_DUCK,0,0);index++;
 }
 for(n=0;n<5;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_ONE_DUCK,0,8);index++;
 }
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_BASIC_FINAL,DOG_ONE_DUCK,0,0);index++;
 DogFrameTwoDuck=index;//собака с двумя утками
 for(n=0;n<5;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_TWO_DUCK,0,-8);index++;
 }
 for(n=0;n<5;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_TWO_DUCK,0,0);index++;
 }
 for(n=0;n<5;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_TWO_DUCK,0,8);index++;
 }
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_BASIC_FINAL,DOG_TWO_DUCK,0,0);index++;
 //в смеющуюся собаку попали
 DogFrameHit=index;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_HIT,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_HIT,0,0);index++;
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_HIT,0,0);index++;
 for(n=0;n<5;n++)
 {
  SetAnimate(sAnimate_DogPtr+index,DOG_MODE_ANIMATE_BACK,DOG_HIT,0,8);index++;
 }
 SetAnimate(sAnimate_DogPtr+index,DOG_MODE_BASIC_FINAL,DOG_HIT,0,0);index++;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CDogMap::~CDogMap()
{
 delete(sAnimate_DogPtr);
}

//----------------------------------------------------------------------------------------------------
//инициализация
//----------------------------------------------------------------------------------------------------
void CDogMap::Init(int AreaWidth,int AreaHeight,int GrassHeightLevel,CSprite *cSprite_Dog)
{
 WorkingAreaHeight=AreaHeight;
 WorkingAreaWidth=AreaWidth;
 cSprite_DogPtr=cSprite_Dog;
 DogFrameSizeX=cSprite_DogPtr->GetWidth()/14;
 DogFrameSizeY=cSprite_DogPtr->GetHeight();
 GrassHeight=GrassHeightLevel;
}
//----------------------------------------------------------------------------------------------------
//настроить собаку на начало уровня
//----------------------------------------------------------------------------------------------------
void CDogMap::InitLevel(void)
{
 sDog.DogFrameIndex=0;
 sDog.DogCounter=10;
 sDog.DogX=-DogFrameSizeX;
 sDog.DogY=WorkingAreaHeight-1-DogFrameSizeY-10;
}
//----------------------------------------------------------------------------------------------------
//получить режим собаки
//----------------------------------------------------------------------------------------------------
int CDogMap::GetDogMode(void)
{
 SAnimate sAnimate_dog=sAnimate_DogPtr[sDog.DogFrameIndex];
 return(sAnimate_dog.Mode);
}
//----------------------------------------------------------------------------------------------------
//вывести собак
//----------------------------------------------------------------------------------------------------
void CDogMap::PutDog(void)
{
 SAnimate sAnimate_dog=sAnimate_DogPtr[sDog.DogFrameIndex];
 cSprite_DogPtr->PutSpriteItem(sDog.DogX,sDog.DogY,sAnimate_dog.Frame*DogFrameSizeX,0,DogFrameSizeX,DogFrameSizeY,true);
}
//----------------------------------------------------------------------------------------------------
//начать анимацию "собака смеётся"
//----------------------------------------------------------------------------------------------------
void CDogMap::DogLOL(void)
{
 sDog.DogFrameIndex=DogFrameLol;
 sDog.DogX=RND(WorkingAreaWidth-DogFrameSizeX*4)+DogFrameSizeX;
 sDog.DogY=WorkingAreaHeight-GrassHeight;
 sDog.DogCounter=10;
}
//----------------------------------------------------------------------------------------------------
//начать анимацию "собака с одной уткой"
//----------------------------------------------------------------------------------------------------
void CDogMap::DogOneDuck(void)
{
 sDog.DogFrameIndex=DogFrameOneDuck;
 sDog.DogX=RND(WorkingAreaWidth-DogFrameSizeX*4)+DogFrameSizeX;
 sDog.DogY=WorkingAreaHeight-GrassHeight;
 sDog.DogCounter=10;
}
//----------------------------------------------------------------------------------------------------
//начать анимацию "собака с двумя утками"
//----------------------------------------------------------------------------------------------------
void CDogMap::DogTwoDuck(void)
{
 sDog.DogFrameIndex=DogFrameTwoDuck;
 sDog.DogX=RND(WorkingAreaWidth-DogFrameSizeX*4)+DogFrameSizeX;
 sDog.DogY=WorkingAreaHeight-GrassHeight;
 sDog.DogCounter=10;
}
//----------------------------------------------------------------------------------------------------
//привести собаку в исходное состояние
//----------------------------------------------------------------------------------------------------
void CDogMap::DogBasic(void)
{
 sDog.DogFrameIndex=DogFrameBasic;
 sDog.DogCounter=10;
}
//----------------------------------------------------------------------------------------------------
//анимация
//----------------------------------------------------------------------------------------------------
void CDogMap::Processing(void)
{
 SAnimate sAnimate_dog=sAnimate_DogPtr[sDog.DogFrameIndex];
 if (sAnimate_dog.Mode==DOG_MODE_BASIC || sAnimate_dog.Mode==DOG_MODE_BASIC_FINAL) return;//анимация не требуется
 sDog.DogCounter--;
 if (sDog.DogCounter==0)
 {
  if (sAnimate_dog.Mode==DOG_MODE_ANIMATE_AND_YIP) cSoundControl.Play(SOUND_DOG);//запускаем лай
  if (sAnimate_dog.Mode==DOG_MODE_ANIMATE_BACK_AND_LAUGH) cSoundControl.Play(SOUND_LAUGH);//собака смеётся
  sDog.DogCounter=10;
  sDog.DogX+=sAnimate_dog.dX;
  sDog.DogY+=sAnimate_dog.dY;
  sDog.DogFrameIndex++;
 }
}
//----------------------------------------------------------------------------------------------------
//записать состояние
//----------------------------------------------------------------------------------------------------
void CDogMap::SaveState(SceUID SceUID_File)
{
 if (SceUID_File<0) return;//ошибка
 sceIoWrite(SceUID_File,&sDog,sizeof(SDog));//записываем состояние собаки
}
//----------------------------------------------------------------------------------------------------
//загрузить состояние
//----------------------------------------------------------------------------------------------------
void CDogMap::LoadState(SceUID SceUID_File)
{
 if (SceUID_File<=0) return;//ошибка
 sceIoRead(SceUID_File,&sDog,sizeof(SDog));//читаем состояние собаки
}
//----------------------------------------------------------------------------------------------------
//стрельба по смеющейся собаке
//----------------------------------------------------------------------------------------------------
void CDogMap::Fire(int cX,int cY,int r)
{
 SAnimate sAnimate_dog=sAnimate_DogPtr[sDog.DogFrameIndex];
 if (sAnimate_dog.Mode!=DOG_MODE_ANIMATE_BACK_LOL) return;//нельзя стрелять по собаке
 //проверяем попадание
 if (cX>=sDog.DogX && cX<=sDog.DogX+DogFrameSizeX && cY>=sDog.DogY && cY<=sDog.DogY+DogFrameSizeY)
 {
  sDog.DogFrameIndex=DogFrameHit;//в собаку попали
 }
}

