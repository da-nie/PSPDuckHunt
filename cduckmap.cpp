#include "cduckmap.h"

extern CSoundControl cSoundControl;

//----------------------------------------------------------------------------------------------------
//�����������
//----------------------------------------------------------------------------------------------------
CDuckMap::CDuckMap(void)
{
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CDuckMap::~CDuckMap()
{

}
//----------------------------------------------------------------------------------------------------
//�������������
//----------------------------------------------------------------------------------------------------
void CDuckMap::Init(int AreaWidth,int AreaHeight,int GrassHeightLevel,CSprite *cSprite_Duck)
{
 WorkingAreaHeight=AreaHeight;
 WorkingAreaWidth=AreaWidth;
 cSprite_DuckPtr=cSprite_Duck;
 DuckFrameSizeX=cSprite_DuckPtr->GetWidth()/16;
 DuckFrameSizeY=cSprite_DuckPtr->GetHeight();
 GrassHeight=GrassHeightLevel;
}
//----------------------------------------------------------------------------------------------------
//���������� ���������� �� ���� ����
//----------------------------------------------------------------------------------------------------
void CDuckMap::SetEnabledDuck(bool duck1_enabled,bool duck2_enabled)
{
 sDuck[0].Enabled=duck1_enabled;
 sDuck[1].Enabled=duck2_enabled;
}
//----------------------------------------------------------------------------------------------------
//�������� ���������� �� ���� ����
//----------------------------------------------------------------------------------------------------
void CDuckMap::GetEnabledDuck(bool &duck1_enabled,bool &duck2_enabled)
{
 duck1_enabled=sDuck[0].Enabled;
 duck2_enabled=sDuck[1].Enabled;
}
//----------------------------------------------------------------------------------------------------
//��������� ���� �� ������ ������
//----------------------------------------------------------------------------------------------------
void CDuckMap::InitLevel(int level)
{
 sDuck[0].DuckMode=DUCK_MODE_NONE;//���� �� �����������
 sDuck[1].DuckMode=DUCK_MODE_NONE;
 Level=level;
}
//----------------------------------------------------------------------------------------------------
//���������� ������
//----------------------------------------------------------------------------------------------------
void CDuckMap::DuckControl(void)
{
 for(int n=0;n<2;n++)
 {
  SDuck *sDuckPtr=&sDuck[n];
  if (sDuckPtr->Enabled==false) continue;//���� �� �������������
  if (sDuckPtr->DuckMode==DUCK_MODE_ITEM) continue;//���� ������
  if (sDuckPtr->DuckMode==DUCK_MODE_NONE) continue;//���� �� �����������
  if (sDuckPtr->DuckMode==DUCK_MODE_FAIL) continue;//���� �������
  float speed=Level;
  speed*=0.1;
  speed+=1;
  float dx=sDuckPtr->dX*sDuckPtr->Speed*speed;
  float dy=sDuckPtr->dY*sDuckPtr->Speed*speed;
  float x=sDuckPtr->X+dx;//����� ���������� ������ ����
  float y=sDuckPtr->Y+dy;
  if (sDuckPtr->DuckMode==DUCK_MODE_FALL)//���� ������
  {
   if (y>=WorkingAreaHeight-(DuckFrameSizeY>>1))//���� ��������� � ������ �������
   {
    sDuckPtr->DuckMode=DUCK_MODE_ITEM;//������ ���� �������� �������
   }
  }
  if (sDuckPtr->DuckMode==DUCK_MODE_FLY)//���� ������ ������
  {
   if (x<=(DuckFrameSizeX>>1))//���� ��������� � ����� �������
   {
    if (sDuckPtr->dX<0 && y<=WorkingAreaHeight-GrassHeight) sDuckPtr->DirectCounter--;
    sDuckPtr->dX=fabs(sDuckPtr->dX);
    sDuckPtr->SpriteCounter=0;
    sDuckPtr->SpriteDirectCounter=1;
    sDuckPtr->SpriteAnimateCounter=0;
    if (sDuckPtr->DirectCounter<=0)
    {
     sDuckPtr->FlyCounter=1000;//����� ���� ������������� �������
     sDuckPtr->dX=0;
     sDuckPtr->dY=-1;
    }
   }
   if (x>=WorkingAreaWidth-(DuckFrameSizeX>>1))//���� ��������� � ������ �������
   {
    if (sDuckPtr->dX>0 && y<=WorkingAreaHeight-GrassHeight) sDuckPtr->DirectCounter--;
    sDuckPtr->dX=-fabs(sDuckPtr->dX);
    sDuckPtr->SpriteCounter=0;
    sDuckPtr->SpriteDirectCounter=1;
    sDuckPtr->SpriteAnimateCounter=0;
    if (sDuckPtr->DirectCounter<=0)
    {
     sDuckPtr->FlyCounter=1000;//����� ���� ������������� �������
     sDuckPtr->dX=0;
     sDuckPtr->dY=-1;
    }
   }
   if (y<=(DuckFrameSizeY>>1))//���� ��������� � ������� �������
   {
    if (sDuckPtr->DirectCounter<=0)//���� �������
    {
     sDuckPtr->FlyCounter=1000;//����� ���� ������������� �������
     if (y<-(DuckFrameSizeY>>1))//���� �������
     {
      sDuckPtr->DuckMode=DUCK_MODE_FAIL;//��� ������
     }
    }
    else//���� ����� � ������ �������
    {
     if (sDuckPtr->dY<0) sDuckPtr->DirectCounter--;
     sDuckPtr->dY=fabs(sDuckPtr->dY);
     sDuckPtr->SpriteCounter=0;
     sDuckPtr->SpriteDirectCounter=1;
     sDuckPtr->SpriteAnimateCounter=0;
    }
   }
   if (y>=WorkingAreaHeight-(DuckFrameSizeY>>1)-GrassHeight)//���� ��������� � ������ �������
   {
    sDuckPtr->dY=-fabs(sDuckPtr->dY);
    sDuckPtr->SpriteCounter=0;
    sDuckPtr->SpriteDirectCounter=1;
    sDuckPtr->SpriteAnimateCounter=0;
    if (sDuckPtr->DirectCounter<=0)
    {
     sDuckPtr->FlyCounter=1000;//����� ���� ������������� �������
     sDuckPtr->dX=0;
     sDuckPtr->dY=-1;
    }
   }
   //��������� ������� ����� � �������� �����������
   if (sDuckPtr->FlyCounter>0) sDuckPtr->FlyCounter--;
   else//�������� ����� ����������� ����� ����
   {
    sDuckPtr->FlyCounter=RND(100)+10;
    float angle=RND(360);
    sDuckPtr->dX=sin(M_PI/180.0*angle);
    sDuckPtr->dY=cos(M_PI/180.0*angle);
    sDuckPtr->SpriteCounter=0;
    sDuckPtr->SpriteDirectCounter=1;
    sDuckPtr->SpriteAnimateCounter=0;
   }
  }
  sDuckPtr->X=x;
  sDuckPtr->Y=y;
  //�������� ������ �� ����������� � ���������� ��������
  int max_sprite_counter=0;
  if (dx<-0.1 && dy>0)//���� ����� �����-�����
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_UP_LEFT_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_UP_LEFT_2;
   max_sprite_counter=1;
  }
  if (dx>0.1 && dy>0)//���� ����� ������-�����
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_UP_RIGHT_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_UP_RIGHT_2;
   max_sprite_counter=1;
  }
  if (dx>=-0.1 && dx<=0.1)//���� ����� ����� ��� ����
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_UP_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_UP_2;
   if (sDuckPtr->SpriteCounter==2) sDuckPtr->Frame=DUCK_UP_3;
   max_sprite_counter=2;
  }
  if (dx<-0.1 && dy<=0)//���� ����� �����-����
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_DOWN_LEFT_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_DOWN_LEFT_2;
   if (sDuckPtr->SpriteCounter==2) sDuckPtr->Frame=DUCK_DOWN_LEFT_3;
   max_sprite_counter=2;
  }
  if (dx>0.1 && dy<=0)//���� ����� ������-����
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_DOWN_RIGHT_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_DOWN_RIGHT_2;
   if (sDuckPtr->SpriteCounter==2) sDuckPtr->Frame=DUCK_DOWN_RIGHT_3;
   max_sprite_counter=2;
  }
  if (sDuckPtr->DuckMode==DUCK_MODE_HIT) sDuckPtr->Frame=DUCK_HIT;//� ���� ������
  if (sDuckPtr->DuckMode==DUCK_MODE_FALL)//���� ������
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_FALL_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_FALL_2;
   max_sprite_counter=1;
  }
  //���������� ��������
  if (sDuckPtr->SpriteAnimateCounter<10)
  {
   sDuckPtr->SpriteAnimateCounter++;
  }
  else
  {
   sDuckPtr->SpriteAnimateCounter=0;
   //�������� �����
   sDuckPtr->SpriteCounter+=sDuckPtr->SpriteDirectCounter;
   if (sDuckPtr->SpriteCounter==max_sprite_counter) sDuckPtr->SpriteDirectCounter=-1;
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->SpriteDirectCounter=1;
   if (sDuckPtr->DuckMode==DUCK_MODE_HIT)//� ���� ������
   {
    sDuckPtr->DuckMode=DUCK_MODE_FALL;//������ ���� ������
    sDuckPtr->SpriteCounter=0;
    sDuckPtr->SpriteDirectCounter=1;
    sDuckPtr->SpriteAnimateCounter=5;
    sDuckPtr->dX=0;
    sDuckPtr->dY=1;
    sDuckPtr->Speed=3;
   }
  }
 }
}
//----------------------------------------------------------------------------------------------------
//������� ����
//----------------------------------------------------------------------------------------------------
void CDuckMap::PutDuck(void)
{
 for(int n=0;n<2;n++)
 {
  SDuck *sDuckPtr=&sDuck[n];
  if (sDuckPtr->Enabled==false) continue;//���� �� �������������
  if (sDuckPtr->DuckMode==DUCK_MODE_ITEM) continue;//���� ������
  if (sDuckPtr->DuckMode==DUCK_MODE_FAIL) continue;//���� �������
  if (sDuckPtr->DuckMode==DUCK_MODE_NONE) continue;//���� �� �����������
  int x=(int)(sDuckPtr->X-(DuckFrameSizeX>>1));
  int y=(int)(sDuckPtr->Y-(DuckFrameSizeY>>1));
  cSprite_DuckPtr->PutSpriteItem(x,y,sDuckPtr->Frame*DuckFrameSizeX,0,DuckFrameSizeX,DuckFrameSizeY,true);
 }
}
//----------------------------------------------------------------------------------------------------
//������ ����, ���� �����
//----------------------------------------------------------------------------------------------------
bool CDuckMap::LaunchDuck(void)
{
 bool ret=false;
 for(int n=0;n<2;n++)
 {
  SDuck *sDuckPtr=&sDuck[n];
  if (sDuckPtr->Enabled==false) continue;//���� �� �����������
  if (sDuckPtr->DuckMode!=DUCK_MODE_NONE) continue;//���� ��� ��������
  //��������� ����
  ret=true;
  sDuckPtr->X=RND(WorkingAreaWidth-4*DuckFrameSizeX)+2*DuckFrameSizeX;
  sDuckPtr->Y=WorkingAreaHeight;
  sDuckPtr->FlyCounter=0;
  sDuckPtr->SpriteCounter=0;
  sDuckPtr->SpriteDirectCounter=0;
  sDuckPtr->Speed=2;
  int sp=RND(100);
  sDuckPtr->Speed*=(1+sp/1000.0);
  sDuckPtr->Score=10+sp/10;
  int dc=(3-(int)((Level-1)*0.2));//� ���������� ������ ����� ������� ���� �����������
  if (dc<0) dc=0;
  sDuckPtr->DirectCounter=3+dc;
  sDuckPtr->DuckMode=DUCK_MODE_FLY;
 }
 if (ret==true) cSoundControl.Play(SOUND_DUCK);//���� �������
 return(ret);
}
//----------------------------------------------------------------------------------------------------
//���������, ��� ��� �����
//----------------------------------------------------------------------------------------------------
int CDuckMap::CheckEndDuckHunt(void)
{
 int n;
 int duck_end=0;
 int duck_enabled=0;
 int duck_item=0;
 int duck_fail=0;
 for(n=0;n<2;n++)
 {
  SDuck *sDuckPtr=&sDuck[n];
  if (sDuckPtr->Enabled==false) continue;//���� �� �����������
  duck_enabled++;
  if (sDuckPtr->DuckMode==DUCK_MODE_FAIL || sDuckPtr->DuckMode==DUCK_MODE_ITEM) duck_end++;//���� ������� ��� ���� �����
  if (sDuckPtr->DuckMode==DUCK_MODE_FAIL) duck_fail++;
  if (sDuckPtr->DuckMode==DUCK_MODE_ITEM) duck_item++;
 }
 if (duck_enabled==duck_end)//��� ���� ��������� ����
 {
  return(duck_item);//���������� ����� ������ ����
 }
 return(-1);//����� �� ��������
}
//----------------------------------------------------------------------------------------------------
//���������, ��� ��� �����
//----------------------------------------------------------------------------------------------------
int CDuckMap::Fire(int cX,int cY,int r)
{
 int score=0;
 for(int n=0;n<2;n++)
 {
  SDuck *sDuckPtr=&sDuck[n];
  if (sDuckPtr->Enabled==false) continue;//���� �� �����������
  if (sDuckPtr->DuckMode!=DUCK_MODE_FLY) continue;//���� �� ������
  //��������� ���������
  float dx=(cX-sDuckPtr->X);
  float dy=(cY-sDuckPtr->Y);
  float d=sqrt(dx*dx+dy*dy);
  float dr=r*sqrt(DuckFrameSizeX*DuckFrameSizeX+DuckFrameSizeY*DuckFrameSizeY)/2;
  if (d<=dr)//���������
  {
   sDuckPtr->DuckMode=DUCK_MODE_HIT;
   sDuckPtr->SpriteDirectCounter=1;
   sDuckPtr->SpriteCounter=0;
   sDuckPtr->SpriteAnimateCounter=0;
   score+=sDuckPtr->Score;
  }
 }
 return(score);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������
//----------------------------------------------------------------------------------------------------
void CDuckMap::SaveState(SceUID SceUID_File)
{
 if (SceUID_File<0) return;//������
 sceIoWrite(SceUID_File,&sDuck[0],sizeof(SDuck));//���������� ��������� ����
 sceIoWrite(SceUID_File,&sDuck[1],sizeof(SDuck));//���������� ��������� ����
 sceIoWrite(SceUID_File,&Level,sizeof(int));//���������� �������
}
//----------------------------------------------------------------------------------------------------
//��������� ���������
//----------------------------------------------------------------------------------------------------
void CDuckMap::LoadState(SceUID SceUID_File)
{
 if (SceUID_File<0) return;//������
 sceIoRead(SceUID_File,&sDuck[0],sizeof(SDuck));//������ ��������� ����
 sceIoRead(SceUID_File,&sDuck[1],sizeof(SDuck));//������ ��������� ����
 sceIoRead(SceUID_File,&Level,sizeof(int));//������ �������
}

