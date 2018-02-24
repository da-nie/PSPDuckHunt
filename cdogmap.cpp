#include "cdogmap.h"

extern CSoundControl cSoundControl;

//----------------------------------------------------------------------------------------------------
//�����������
//----------------------------------------------------------------------------------------------------
CDogMap::CDogMap(void)
{
 sAnimate_DogPtr=new SAnimate[1000];
 //�������������� ������
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
 DogFrameLol=index;//������ ������
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
 DogFrameOneDuck=index;//������ � ����� �����
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
 DogFrameTwoDuck=index;//������ � ����� ������
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
 //� ��������� ������ ������
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
//����������
//----------------------------------------------------------------------------------------------------
CDogMap::~CDogMap()
{
 delete(sAnimate_DogPtr);
}

//----------------------------------------------------------------------------------------------------
//�������������
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
//��������� ������ �� ������ ������
//----------------------------------------------------------------------------------------------------
void CDogMap::InitLevel(void)
{
 sDog.DogFrameIndex=0;
 sDog.DogCounter=10;
 sDog.DogX=-DogFrameSizeX;
 sDog.DogY=WorkingAreaHeight-1-DogFrameSizeY-10;
}
//----------------------------------------------------------------------------------------------------
//�������� ����� ������
//----------------------------------------------------------------------------------------------------
int CDogMap::GetDogMode(void)
{
 SAnimate sAnimate_dog=sAnimate_DogPtr[sDog.DogFrameIndex];
 return(sAnimate_dog.Mode);
}
//----------------------------------------------------------------------------------------------------
//������� �����
//----------------------------------------------------------------------------------------------------
void CDogMap::PutDog(void)
{
 SAnimate sAnimate_dog=sAnimate_DogPtr[sDog.DogFrameIndex];
 cSprite_DogPtr->PutSpriteItem(sDog.DogX,sDog.DogY,sAnimate_dog.Frame*DogFrameSizeX,0,DogFrameSizeX,DogFrameSizeY,true);
}
//----------------------------------------------------------------------------------------------------
//������ �������� "������ ������"
//----------------------------------------------------------------------------------------------------
void CDogMap::DogLOL(void)
{
 sDog.DogFrameIndex=DogFrameLol;
 sDog.DogX=RND(WorkingAreaWidth-DogFrameSizeX*4)+DogFrameSizeX;
 sDog.DogY=WorkingAreaHeight-GrassHeight;
 sDog.DogCounter=10;
}
//----------------------------------------------------------------------------------------------------
//������ �������� "������ � ����� �����"
//----------------------------------------------------------------------------------------------------
void CDogMap::DogOneDuck(void)
{
 sDog.DogFrameIndex=DogFrameOneDuck;
 sDog.DogX=RND(WorkingAreaWidth-DogFrameSizeX*4)+DogFrameSizeX;
 sDog.DogY=WorkingAreaHeight-GrassHeight;
 sDog.DogCounter=10;
}
//----------------------------------------------------------------------------------------------------
//������ �������� "������ � ����� ������"
//----------------------------------------------------------------------------------------------------
void CDogMap::DogTwoDuck(void)
{
 sDog.DogFrameIndex=DogFrameTwoDuck;
 sDog.DogX=RND(WorkingAreaWidth-DogFrameSizeX*4)+DogFrameSizeX;
 sDog.DogY=WorkingAreaHeight-GrassHeight;
 sDog.DogCounter=10;
}
//----------------------------------------------------------------------------------------------------
//�������� ������ � �������� ���������
//----------------------------------------------------------------------------------------------------
void CDogMap::DogBasic(void)
{
 sDog.DogFrameIndex=DogFrameBasic;
 sDog.DogCounter=10;
}
//----------------------------------------------------------------------------------------------------
//��������
//----------------------------------------------------------------------------------------------------
void CDogMap::Processing(void)
{
 SAnimate sAnimate_dog=sAnimate_DogPtr[sDog.DogFrameIndex];
 if (sAnimate_dog.Mode==DOG_MODE_BASIC || sAnimate_dog.Mode==DOG_MODE_BASIC_FINAL) return;//�������� �� ���������
 sDog.DogCounter--;
 if (sDog.DogCounter==0)
 {
  if (sAnimate_dog.Mode==DOG_MODE_ANIMATE_AND_YIP) cSoundControl.Play(SOUND_DOG);//��������� ���
  if (sAnimate_dog.Mode==DOG_MODE_ANIMATE_BACK_AND_LAUGH) cSoundControl.Play(SOUND_LAUGH);//������ ������
  sDog.DogCounter=10;
  sDog.DogX+=sAnimate_dog.dX;
  sDog.DogY+=sAnimate_dog.dY;
  sDog.DogFrameIndex++;
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ���������
//----------------------------------------------------------------------------------------------------
void CDogMap::SaveState(SceUID SceUID_File)
{
 if (SceUID_File<0) return;//������
 sceIoWrite(SceUID_File,&sDog,sizeof(SDog));//���������� ��������� ������
}
//----------------------------------------------------------------------------------------------------
//��������� ���������
//----------------------------------------------------------------------------------------------------
void CDogMap::LoadState(SceUID SceUID_File)
{
 if (SceUID_File<=0) return;//������
 sceIoRead(SceUID_File,&sDog,sizeof(SDog));//������ ��������� ������
}
//----------------------------------------------------------------------------------------------------
//�������� �� ��������� ������
//----------------------------------------------------------------------------------------------------
void CDogMap::Fire(int cX,int cY,int r)
{
 SAnimate sAnimate_dog=sAnimate_DogPtr[sDog.DogFrameIndex];
 if (sAnimate_dog.Mode!=DOG_MODE_ANIMATE_BACK_LOL) return;//������ �������� �� ������
 //��������� ���������
 if (cX>=sDog.DogX && cX<=sDog.DogX+DogFrameSizeX && cY>=sDog.DogY && cY<=sDog.DogY+DogFrameSizeY)
 {
  sDog.DogFrameIndex=DogFrameHit;//� ������ ������
 }
}

