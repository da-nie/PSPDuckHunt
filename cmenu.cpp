#include "cmenu.h"

extern CFontB cFontB;
extern CSoundControl cSoundControl;
extern SVideo_DisplaySetting sVideo_DisplaySetting;
extern bool done;
//--------------------------------------------------------------------------
CMenu::CMenu(void)
{
}
CMenu::~CMenu()
{
 Release();
}
void CMenu::Create(char *Path)
{
 char *FileName=new char[strlen(Path)+255];
 sprintf(FileName,"%ssprites\\menu.tga",Path);
 cSprite_MenuBack.Load(FileName);
 sprintf(FileName,"%ssprites\\hiscore.tga",Path);
 cSprite_HiScoreBack.Load(FileName);
 delete(FileName);
 if (LoadHiScore(Path)==false) CreateHiScore();
 Text=new char[16384];
 strcpy(Text,"                                            ");
 strcat(Text,"УТИНАЯ ОХОТА. Управление в игре - аналоговый джойстик; крестик - стрелять; правая и левая триггерная кнопка - выбор оружия;");
 strcat(Text,"select - сохранить скриншот; start - выйти в меню; одновременное нажатие 'вправо' и 'вниз' - сохранить игру, 'вправо' и 'вверх' - загрузить игру;");
 strcat(Text,"треугольник - пауза. Ну вот, с официальной частью закончили, теперь неофициальная пойдет. Итак...          ");
 strcat(Text,"Приветствую всех любителей приставки PSP! Поиграл я тут в Doom Duck Deluxe и захотелось сделать нечто подобное на PSP.");
 strcat(Text,"Ну а что из этого вышло, вы сейчас и увидите. Кому-то эта игра может и понравиться, а кто-то скажет (как это уже было), что 'как нагло уперта графика и звуки из...'.");
 strcat(Text,"Но поймите, я же не художник. Рисовать я не умею совершенно. Поэтому вся графика и звуки взяты из интернета. Если кто узнает свое авторство и хочет чтобы я его упомянул,");
 strcat(Text,"я, конечно же, с радостью это сделаю. Ну а если кто будет против использования своих картинок или звуков, ну что ж, я их заменю, если вы того захотите.");
 strcat(Text,"Но все же, надеюсь, обиженных не будет, и эта игра всем понравится. Ведь, собственно, для того оно и делалось, как вы понимаете. :) ");
 strcat(Text,"Далее, пользуясь случаем, хочу передать привет своей замечательной жене Леночке и всем тем, кто меня знает, пусть даже, бывает, увы, не с лучшей стороны. ");
 strcat(Text,"Так же передаю привет основному конкуренту сайта Миката - сайту Animekazan.net и его админу - Шкитову Александру, который, между прочим, и нарисовал мне этот желтый шрифт, который вы сейчас читаете. :) ");
 strcat(Text,"К сожалению, форум этого сайта вот уже который год влачит жалкое существование и никак не желает оживать, несмотря на обилие самых разнообразных тем, часто ");
 strcat(Text,"не имеющих вообще никакой связи с аниме. Такая же участь постигла и форум noir.ru, которому я тоже передам привет, поскольку это был первый форум ");
 strcat(Text,"на котором я зарегистрировался и у меня с этим форумом связан мой первый опыт общения в сети. Ну, вот, пожалуй, и все. УДАЧНОЙ ИГРЫ!");
 strcat(Text,"     P.S. Не надо играть в игру сохраняясь после каждого выстрела. ;) Это не спортивно. :)         (с) Дмитрий Трунов (Da-nie), 01.08.2012. www.animekazan.net/forum2   ");
 TextOffset=0;
 TextLength=strlen(Text);
}
void CMenu::Release(void)
{
 cSprite_MenuBack.Release();
 cSprite_HiScoreBack.Release();
 delete(Text);
}
//--------------------------------------------------------------------------
void CMenu::SaveHiScore(char *Path)
{
 char *FileName=new char[strlen(Path)+256];
 sprintf(FileName,"%ssave\\hiscore.bin",Path);
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_WRONLY|PSP_O_CREAT,0777);//открываем файл
 if (SceUID_File<=0)//ошибка создания файла
 {
  delete(FileName);
  return;
 }
 //кодовое слово
 unsigned char codeword[256];
 strcpy((char*)codeword,"Codename from Duck Hunt HiScore.");
 int codewordlength=strlen((char*)codeword);
 int codepos=0;
 int n,m;
 int size=sizeof(struct SHiScore);
 unsigned char *line=new unsigned char[size+2];
 unsigned short *crc=(unsigned short*)(line+size);
 *crc=0;
 for(n=0;n<10;n++)
 {
  //переносим строчку таблицы рекордов в буфер
  memcpy(line,(unsigned char *)&sHiScore[n],size);
  //кодируем её
  for(m=0;m<size;m++)
  {
   unsigned char byte=line[m];
   *crc+=byte;
   byte=byte^codeword[codepos];
   *crc+=byte;
   codepos+=m-n;
   codepos++;
   while(codepos<0) codepos+=codewordlength;
   while(codepos>=codewordlength) codepos-=codewordlength;
   byte=byte^codeword[codepos];
   *crc+=byte;
   line[m]=byte;
  }
  //сохраняем строку
  if (sceIoWrite(SceUID_File,line,size+2)<size+2) break;//ошибка записи
 }
 delete(line);
 sceIoClose(SceUID_File);
 delete(FileName);
}
bool CMenu::LoadHiScore(char *Path)
{
 char *FileName=new char[strlen(Path)+256];
 sprintf(FileName,"%ssave\\hiscore.bin",Path);
 SceUID SceUID_File;
 SceUID_File=sceIoOpen(FileName,PSP_O_RDONLY,0777);//открываем файл
 if (SceUID_File<=0)//ошибка открытия файла
 {
  delete(FileName);
  return(false);
 }
 unsigned char codeword[256];
 strcpy((char*)codeword,"Codename from Duck Hunt HiScore.");
 int codewordlength=strlen((char*)codeword);
 int codepos=0;
 int n,m;
 int size=sizeof(struct SHiScore);
 unsigned char *line=new unsigned char[size+2];
 unsigned short *crc=(unsigned short*)(line+size);
 unsigned short crc_l=0;
 bool ok=true;
 for(n=0;n<10;n++)
 {
  //считываем строчку
  if (sceIoRead(SceUID_File,line,size+2)<size+2)//ошибка чтения
  {
   ok=false;
   break;
  }
  //расшифровываем строчку
  for(m=0;m<size;m++)
  {
   char code1=codeword[codepos];
   codepos+=m-n;
   codepos++;
   while(codepos<0) codepos+=codewordlength;
   while(codepos>=codewordlength) codepos-=codewordlength;
   char code2=codeword[codepos];
   unsigned char byte=line[m];
   crc_l+=byte;
   byte=byte^code2;
   crc_l+=byte;
   byte=byte^code1;
   crc_l+=byte;
   line[m]=byte;
  }
  //сравниваем crc
  if ((*crc)!=crc_l)//ошибка контрольной суммы
  {
   ok=false;
   break;
  }
  //переносим строчку из буфера в таблицу рекордов
  memcpy((unsigned char *)&sHiScore[n],line,size);
 }
 delete(line);
 sceIoClose(SceUID_File);
 delete(FileName);
 return(ok);
}
void CMenu::CreateHiScore(void)
{
 strcpy(sHiScore[0].Name,"By Da-nie 01.08.2012");sHiScore[0].Score=10000;
 strcpy(sHiScore[1].Name,"Трунова Елена.......");sHiScore[1].Score=9000;
 strcpy(sHiScore[2].Name,"Трунов Дмитрий......");sHiScore[2].Score=8000;
 strcpy(sHiScore[3].Name,"Дроздов Максим......");sHiScore[3].Score=7000;
 strcpy(sHiScore[4].Name,"Макаев Евгений......");sHiScore[4].Score=6000;
 strcpy(sHiScore[5].Name,"Давыдочкина Светлана");sHiScore[5].Score=5000;
 strcpy(sHiScore[6].Name,"Карпова Ольга.......");sHiScore[6].Score=4000;
 strcpy(sHiScore[7].Name,"Жуков Константин....");sHiScore[7].Score=3000;
 strcpy(sHiScore[8].Name,"Одинцов Борис.......");sHiScore[8].Score=2000;
 strcpy(sHiScore[9].Name,"Поводырев Юрий......");sHiScore[9].Score=1000;
}
void CMenu::DrawHiScore(void)
{
 char string[255];
 int n;
 SceCtrlData pad;
 u64 tick_frequency=sceRtcGetTickResolution();//текущее значение частоты
 u64 begin_tick;
 u64 current_tick;
 sceRtcGetCurrentTick(&begin_tick);
 bool enable_control=false;
 while(!done)
 {
  if (enable_control==false)
  {
   sceRtcGetCurrentTick(&current_tick);//текущее значение частоты
   double time_span=((double)(current_tick-begin_tick))/(double)tick_frequency;//прошедшее время
   if (time_span>0.5) enable_control=true;
  }
  sceCtrlReadBufferPositive(&pad,1);
  if (pad.Buttons && enable_control==true) break;//нажали любую клавишу и прошло больше пол-секунды
  //выводим фоновую картинку
  cSprite_HiScoreBack.Put(0,0,false);
  //выводим таблицу рекордов
  cFontB.PrintAt(136,10,(char*)"Таблица рекордов",true);
  for(n=0;n<10;n++)
  {
   sprintf(string,"%s %i",sHiScore[n].Name,sHiScore[n].Score);
   cFontB.PrintAt(70,40+n*20,string,true);
  }
  //делаем вывод на экран
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
 }
}
bool CMenu::InputHiScore(int score,char *Path)
{
 int n;
 int posy=-1;
 for(n=0;n<10;n++)
 {
  if (sHiScore[n].Score<score)
  {
   posy=n;
   break;
  }
 }
 if (posy<0) return(true);//очков не хватило
 //сдвигаем таблицу рекордов вниз
 for(n=9;n>posy;n--) sHiScore[n]=sHiScore[n-1];
 sHiScore[posy].Score=score;
 strcpy(sHiScore[posy].Name,"                    ");
 //вводим имя
 SceCtrlData pad;
 bool on_exit=false;
 unsigned char symbol=32;
 int posx=0;
 while(done==false && on_exit==false)
 {
  //заносим символ в таблицу рекордов
  sHiScore[posy].Name[posx]=symbol;
  //выводим фоновую картинку
  cSprite_HiScoreBack.Put(0,0,false);
  cFontB.PrintAt(136,10,(char*)"Таблица рекордов",true);
  cFontB.PrintAt(32,250,(char*)"Select-выход. Курсор-ввод имени.",true);
  char string[255];
  for(n=0;n<10;n++)
  {
   sprintf(string,"%s %i",sHiScore[n].Name,sHiScore[n].Score);
   cFontB.PrintAt(70,40+n*20,string,true);
  }
  Video_ViewDisplayPage();
  //ждём нажатия на клавиши влево, вверх и вниз, а так же крестик
  while(done==false)
  {
   sceCtrlReadBufferPositive(&pad,1);
   if (pad.Buttons&PSP_CTRL_UP)//нажата клавиша "вверх"
   {
    symbol++;
    if (symbol>(unsigned char)'~') symbol=32;
    break;
   }
   if (pad.Buttons&PSP_CTRL_DOWN)//нажата клавиша "вверх"
   {
    symbol--;
    if (symbol<32) symbol=(unsigned char)'~';
    break;
   }
   if (pad.Buttons&PSP_CTRL_LEFT)//нажата клавиша "влево"
   {
    sHiScore[posy].Name[posx]=32;
    posx--;
    if (posx<0) posx=0;
    break;
   }
   if (pad.Buttons&PSP_CTRL_RIGHT)//нажата клавиша "вправо"
   {
    posx++;
    if (posx>19) posx=19;
    break;
   }
   if (pad.Buttons&PSP_CTRL_SELECT)//нажата клавиша select
   {
    on_exit=true;
    break;
   }
  }
  //делаем вывод на экран
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  //делаем задержку
  sceKernelDelayThread(100000);
 }
 //дополняем точками строку
 for(n=posx+1;n<20;n++) sHiScore[posy].Name[n]='.';
 SaveHiScore(Path);
 if (done==true) return(false);
 return(true);
}
bool CMenu::Activate(char *Path,bool &two_duck,int &sensitivity_x,int &sensitivity_y)
{
 SceCtrlData pad;
 int key_delay=0;
 u64 tick_frequency=sceRtcGetTickResolution();
 u64 begin_tick;
 u64 current_tick;
 int index=0;
 while(done==false)
 {
  sceRtcGetCurrentTick(&begin_tick);//текущее значение частоты
  //производим упрравление от клавиатуры
  sceCtrlReadBufferPositive(&pad,1);
  if (key_delay==0)//производим управление
  {
   if (pad.Buttons&PSP_CTRL_UP)
   {
    key_delay=10;
    if (index>0) index--;
   }
   if (pad.Buttons&PSP_CTRL_DOWN)
   {
    key_delay=10;
    if (index<5) index++;
   }
   if (pad.Buttons&PSP_CTRL_LEFT)
   {
    key_delay=10;
    if (index==2) two_duck=false;//меняем количество уток
    if (index==3 && sensitivity_x<99) sensitivity_x++;//уменьшаем чувствительность (sensitivity- коэффициент деления)
    if (index==4 && sensitivity_y<99) sensitivity_y++;//уменьшаем чувствительность (sensitivity- коэффициент деления)
   }
   if (pad.Buttons&PSP_CTRL_RIGHT)
   {
    key_delay=10;
    if (index==2) two_duck=true;//меняем количество уток
    if (index==3 && sensitivity_x>1) sensitivity_x--;//увеличиваем чувствительность (sensitivity- коэффициент деления)
    if (index==4 && sensitivity_y>1) sensitivity_y--;//увеличиваем чувствительность (sensitivity- коэффициент деления)
   }
   if (pad.Buttons&PSP_CTRL_CROSS)//выбран пункт меню
   {
    key_delay=10;
    if (index==0) return(true);//старт игры
    if (index==1) DrawHiScore();//рисуем таблицу рекордов
    if (index==2)//меняем количество уток
    {
     if (two_duck==true) two_duck=false;
                    else two_duck=true;
    }
    if (index==5) return(false);//выход
   }
  }
  else key_delay--;
  //рисуем меню
  cSprite_MenuBack.Put(0,0,false);
  int y=110;
  int x_o[6]={5,5,5,5,5,5};
  x_o[index]=15;
  cFontB.PrintAt(x_o[0],y,(char*)"Начать игру",true);y+=20;
  cFontB.PrintAt(x_o[1],y,(char*)"Таблица рекордов",true);y+=20;
  if (two_duck==false) cFontB.PrintAt(x_o[2],y,"Игра с одной уткой",true);
                  else cFontB.PrintAt(x_o[2],y,"Игра с двумя утками",true);
  y+=20;
  char string[255];
  sprintf(string,"Чувствительность джойстика по X:%02i",100-sensitivity_x);
  cFontB.PrintAt(x_o[3],y,string,true);y+=20;
  sprintf(string,"Чувствительность джойстика по Y:%02i",100-sensitivity_y);
  cFontB.PrintAt(x_o[4],y,string,true);y+=20;
  cFontB.PrintAt(x_o[5],y,(char*)"Выйти из игры",true);y+=20;
  //выводим бегущую строку
  for(int n=0;n<40;n++)
  {
   int offset=((int)(TextOffset/13)+n)%TextLength;
   char string[2];
   string[1]=0;
   string[0]=Text[offset];
   cFontB.PrintAt(-13-(TextOffset%13)+n*13,240,string,true);
  }
  TextOffset+=2;
  TextOffset%=TextLength*13;
  //делаем вывод на экран
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
 return(true);
}
