#include "cduckmap.h"

extern CSoundControl cSoundControl;

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CDuckMap::CDuckMap(void)
{
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CDuckMap::~CDuckMap()
{

}
//----------------------------------------------------------------------------------------------------
//инициализация
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
//установить разрешение на полёт уток
//----------------------------------------------------------------------------------------------------
void CDuckMap::SetEnabledDuck(bool duck1_enabled,bool duck2_enabled)
{
 sDuck[0].Enabled=duck1_enabled;
 sDuck[1].Enabled=duck2_enabled;
}
//----------------------------------------------------------------------------------------------------
//получить разрешение на полёт уток
//----------------------------------------------------------------------------------------------------
void CDuckMap::GetEnabledDuck(bool &duck1_enabled,bool &duck2_enabled)
{
 duck1_enabled=sDuck[0].Enabled;
 duck2_enabled=sDuck[1].Enabled;
}
//----------------------------------------------------------------------------------------------------
//настроить уток на начало уровня
//----------------------------------------------------------------------------------------------------
void CDuckMap::InitLevel(int level)
{
 sDuck[0].DuckMode=DUCK_MODE_NONE;//утка не запускалась
 sDuck[1].DuckMode=DUCK_MODE_NONE;
 Level=level;
}
//----------------------------------------------------------------------------------------------------
//управление утками
//----------------------------------------------------------------------------------------------------
void CDuckMap::DuckControl(void)
{
 for(int n=0;n<2;n++)
 {
  SDuck *sDuckPtr=&sDuck[n];
  if (sDuckPtr->Enabled==false) continue;//утка не задействована
  if (sDuckPtr->DuckMode==DUCK_MODE_ITEM) continue;//утка добыта
  if (sDuckPtr->DuckMode==DUCK_MODE_NONE) continue;//утка не запускалась
  if (sDuckPtr->DuckMode==DUCK_MODE_FAIL) continue;//утка улетела
  float speed=Level;
  speed*=0.1;
  speed+=1;
  float dx=sDuckPtr->dX*sDuckPtr->Speed*speed;
  float dy=sDuckPtr->dY*sDuckPtr->Speed*speed;
  float x=sDuckPtr->X+dx;//новые координаты центра утки
  float y=sDuckPtr->Y+dy;
  if (sDuckPtr->DuckMode==DUCK_MODE_FALL)//утка падает
  {
   if (y>=WorkingAreaHeight-(DuckFrameSizeY>>1))//утка врезалась в нижнюю границу
   {
    sDuckPtr->DuckMode=DUCK_MODE_ITEM;//теперь утка является трофеем
   }
  }
  if (sDuckPtr->DuckMode==DUCK_MODE_FLY)//утка просто летает
  {
   if (x<=(DuckFrameSizeX>>1))//утка врезалась в левую границу
   {
    if (sDuckPtr->dX<0 && y<=WorkingAreaHeight-GrassHeight) sDuckPtr->DirectCounter--;
    sDuckPtr->dX=fabs(sDuckPtr->dX);
    sDuckPtr->SpriteCounter=0;
    sDuckPtr->SpriteDirectCounter=1;
    sDuckPtr->SpriteAnimateCounter=0;
    if (sDuckPtr->DirectCounter<=0)
    {
     sDuckPtr->FlyCounter=1000;//чтобы утка гарантировано улетела
     sDuckPtr->dX=0;
     sDuckPtr->dY=-1;
    }
   }
   if (x>=WorkingAreaWidth-(DuckFrameSizeX>>1))//утка врезалась в правую границу
   {
    if (sDuckPtr->dX>0 && y<=WorkingAreaHeight-GrassHeight) sDuckPtr->DirectCounter--;
    sDuckPtr->dX=-fabs(sDuckPtr->dX);
    sDuckPtr->SpriteCounter=0;
    sDuckPtr->SpriteDirectCounter=1;
    sDuckPtr->SpriteAnimateCounter=0;
    if (sDuckPtr->DirectCounter<=0)
    {
     sDuckPtr->FlyCounter=1000;//чтобы утка гарантировано улетела
     sDuckPtr->dX=0;
     sDuckPtr->dY=-1;
    }
   }
   if (y<=(DuckFrameSizeY>>1))//утка врезалась в верхнюю границу
   {
    if (sDuckPtr->DirectCounter<=0)//утка улетает
    {
     sDuckPtr->FlyCounter=1000;//чтобы утка гарантировано улетела
     if (y<-(DuckFrameSizeY>>1))//утка улетела
     {
      sDuckPtr->DuckMode=DUCK_MODE_FAIL;//это промах
     }
    }
    else//утка летит в другую сторону
    {
     if (sDuckPtr->dY<0) sDuckPtr->DirectCounter--;
     sDuckPtr->dY=fabs(sDuckPtr->dY);
     sDuckPtr->SpriteCounter=0;
     sDuckPtr->SpriteDirectCounter=1;
     sDuckPtr->SpriteAnimateCounter=0;
    }
   }
   if (y>=WorkingAreaHeight-(DuckFrameSizeY>>1)-GrassHeight)//утка врезалась в нижнюю границу
   {
    sDuckPtr->dY=-fabs(sDuckPtr->dY);
    sDuckPtr->SpriteCounter=0;
    sDuckPtr->SpriteDirectCounter=1;
    sDuckPtr->SpriteAnimateCounter=0;
    if (sDuckPtr->DirectCounter<=0)
    {
     sDuckPtr->FlyCounter=1000;//чтобы утка гарантировано улетела
     sDuckPtr->dX=0;
     sDuckPtr->dY=-1;
    }
   }
   //уменьшаем счётчик полёта в заданном направлении
   if (sDuckPtr->FlyCounter>0) sDuckPtr->FlyCounter--;
   else//выбираем новое направление полёта утки
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
  //выбираем спрайт по направлению и производим анимацию
  int max_sprite_counter=0;
  if (dx<-0.1 && dy>0)//утка летит влево-вверх
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_UP_LEFT_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_UP_LEFT_2;
   max_sprite_counter=1;
  }
  if (dx>0.1 && dy>0)//утка летит вправо-вверх
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_UP_RIGHT_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_UP_RIGHT_2;
   max_sprite_counter=1;
  }
  if (dx>=-0.1 && dx<=0.1)//утка летит вверх или вниз
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_UP_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_UP_2;
   if (sDuckPtr->SpriteCounter==2) sDuckPtr->Frame=DUCK_UP_3;
   max_sprite_counter=2;
  }
  if (dx<-0.1 && dy<=0)//утка летит влево-вниз
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_DOWN_LEFT_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_DOWN_LEFT_2;
   if (sDuckPtr->SpriteCounter==2) sDuckPtr->Frame=DUCK_DOWN_LEFT_3;
   max_sprite_counter=2;
  }
  if (dx>0.1 && dy<=0)//утка летит вправо-вниз
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_DOWN_RIGHT_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_DOWN_RIGHT_2;
   if (sDuckPtr->SpriteCounter==2) sDuckPtr->Frame=DUCK_DOWN_RIGHT_3;
   max_sprite_counter=2;
  }
  if (sDuckPtr->DuckMode==DUCK_MODE_HIT) sDuckPtr->Frame=DUCK_HIT;//в утку попали
  if (sDuckPtr->DuckMode==DUCK_MODE_FALL)//утка падает
  {
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->Frame=DUCK_FALL_1;
   if (sDuckPtr->SpriteCounter==1) sDuckPtr->Frame=DUCK_FALL_2;
   max_sprite_counter=1;
  }
  //производим анимацию
  if (sDuckPtr->SpriteAnimateCounter<10)
  {
   sDuckPtr->SpriteAnimateCounter++;
  }
  else
  {
   sDuckPtr->SpriteAnimateCounter=0;
   //изменяем кадры
   sDuckPtr->SpriteCounter+=sDuckPtr->SpriteDirectCounter;
   if (sDuckPtr->SpriteCounter==max_sprite_counter) sDuckPtr->SpriteDirectCounter=-1;
   if (sDuckPtr->SpriteCounter==0) sDuckPtr->SpriteDirectCounter=1;
   if (sDuckPtr->DuckMode==DUCK_MODE_HIT)//в утку попали
   {
    sDuckPtr->DuckMode=DUCK_MODE_FALL;//теперь утка падает
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
//вывести уток
//----------------------------------------------------------------------------------------------------
void CDuckMap::PutDuck(void)
{
 for(int n=0;n<2;n++)
 {
  SDuck *sDuckPtr=&sDuck[n];
  if (sDuckPtr->Enabled==false) continue;//утка не задействована
  if (sDuckPtr->DuckMode==DUCK_MODE_ITEM) continue;//утка добыта
  if (sDuckPtr->DuckMode==DUCK_MODE_FAIL) continue;//утка улетела
  if (sDuckPtr->DuckMode==DUCK_MODE_NONE) continue;//утка не запускалась
  int x=(int)(sDuckPtr->X-(DuckFrameSizeX>>1));
  int y=(int)(sDuckPtr->Y-(DuckFrameSizeY>>1));
  cSprite_DuckPtr->PutSpriteItem(x,y,sDuckPtr->Frame*DuckFrameSizeX,0,DuckFrameSizeX,DuckFrameSizeY,true);
 }
}
//----------------------------------------------------------------------------------------------------
//запуск уток, если нужно
//----------------------------------------------------------------------------------------------------
bool CDuckMap::LaunchDuck(void)
{
 bool ret=false;
 for(int n=0;n<2;n++)
 {
  SDuck *sDuckPtr=&sDuck[n];
  if (sDuckPtr->Enabled==false) continue;//утка не запускалась
  if (sDuckPtr->DuckMode!=DUCK_MODE_NONE) continue;//утка уже запущена
  //запускаем утку
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
  int dc=(3-(int)((Level-1)*0.2));//с повышением уровня число метаний уток сокращается
  if (dc<0) dc=0;
  sDuckPtr->DirectCounter=3+dc;
  sDuckPtr->DuckMode=DUCK_MODE_FLY;
 }
 if (ret==true) cSoundControl.Play(SOUND_DUCK);//утка крякает
 return(ret);
}
//----------------------------------------------------------------------------------------------------
//проверить, как идёт охота
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
  if (sDuckPtr->Enabled==false) continue;//утка не запускалась
  duck_enabled++;
  if (sDuckPtr->DuckMode==DUCK_MODE_FAIL || sDuckPtr->DuckMode==DUCK_MODE_ITEM) duck_end++;//утка улетела или была сбита
  if (sDuckPtr->DuckMode==DUCK_MODE_FAIL) duck_fail++;
  if (sDuckPtr->DuckMode==DUCK_MODE_ITEM) duck_item++;
 }
 if (duck_enabled==duck_end)//все утки завершили полёт
 {
  return(duck_item);//возвращаем число сбитых уток
 }
 return(-1);//охота не окончена
}
//----------------------------------------------------------------------------------------------------
//проверить, как идёт охота
//----------------------------------------------------------------------------------------------------
int CDuckMap::Fire(int cX,int cY,int r)
{
 int score=0;
 for(int n=0;n<2;n++)
 {
  SDuck *sDuckPtr=&sDuck[n];
  if (sDuckPtr->Enabled==false) continue;//утка не запускалась
  if (sDuckPtr->DuckMode!=DUCK_MODE_FLY) continue;//утка не летает
  //проверяем попадание
  float dx=(cX-sDuckPtr->X);
  float dy=(cY-sDuckPtr->Y);
  float d=sqrt(dx*dx+dy*dy);
  float dr=r*sqrt(DuckFrameSizeX*DuckFrameSizeX+DuckFrameSizeY*DuckFrameSizeY)/2;
  if (d<=dr)//пападание
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
//записать состояние
//----------------------------------------------------------------------------------------------------
void CDuckMap::SaveState(SceUID SceUID_File)
{
 if (SceUID_File<0) return;//ошибка
 sceIoWrite(SceUID_File,&sDuck[0],sizeof(SDuck));//записываем состояние уток
 sceIoWrite(SceUID_File,&sDuck[1],sizeof(SDuck));//записываем состояние уток
 sceIoWrite(SceUID_File,&Level,sizeof(int));//записываем уровень
}
//----------------------------------------------------------------------------------------------------
//загрузить состояние
//----------------------------------------------------------------------------------------------------
void CDuckMap::LoadState(SceUID SceUID_File)
{
 if (SceUID_File<0) return;//ошибка
 sceIoRead(SceUID_File,&sDuck[0],sizeof(SDuck));//читаем состояние уток
 sceIoRead(SceUID_File,&sDuck[1],sizeof(SDuck));//читаем состояние уток
 sceIoRead(SceUID_File,&Level,sizeof(int));//читаем уровень
}

