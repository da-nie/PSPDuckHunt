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
 strcat(Text,"������ �����. ���������� � ���� - ���������� ��������; ������� - ��������; ������ � ����� ���������� ������ - ����� ������;");
 strcat(Text,"select - ��������� ��������; start - ����� � ����; ������������� ������� '������' � '����' - ��������� ����, '������' � '�����' - ��������� ����;");
 strcat(Text,"����������� - �����. �� ���, � ����������� ������ ���������, ������ ������������� ������. ����...          ");
 strcat(Text,"����������� ���� ��������� ��������� PSP! ������� � ��� � Doom Duck Deluxe � ���������� ������� ����� �������� �� PSP.");
 strcat(Text,"�� � ��� �� ����� �����, �� ������ � �������. ����-�� ��� ���� ����� � �����������, � ���-�� ������ (��� ��� ��� ����), ��� '��� ����� ������ ������� � ����� ��...'.");
 strcat(Text,"�� �������, � �� �� ��������. �������� � �� ���� ����������. ������� ��� ������� � ����� ����� �� ���������. ���� ��� ������ ���� ��������� � ����� ����� � ��� ��������,");
 strcat(Text,"�, ������� ��, � �������� ��� ������. �� � ���� ��� ����� ������ ������������� ����� �������� ��� ������, �� ��� �, � �� ������, ���� �� ���� ��������.");
 strcat(Text,"�� ��� ��, �������, ��������� �� �����, � ��� ���� ���� ����������. ����, ����������, ��� ���� ��� � ��������, ��� �� ���������. :) ");
 strcat(Text,"�����, ��������� �������, ���� �������� ������ ����� ������������� ���� ������� � ���� ���, ��� ���� �����, ����� ����, ������, ���, �� � ������ �������. ");
 strcat(Text,"��� �� ������� ������ ��������� ���������� ����� ������ - ����� Animekazan.net � ��� ������ - ������� ����������, �������, ����� ������, � ��������� ��� ���� ������ �����, ������� �� ������ �������. :) ");
 strcat(Text,"� ���������, ����� ����� ����� ��� ��� ������� ��� ������ ������ ������������� � ����� �� ������ �������, �������� �� ������ ����� ������������� ���, ����� ");
 strcat(Text,"�� ������� ������ ������� ����� � �����. ����� �� ������ �������� � ����� noir.ru, �������� � ���� ������� ������, ��������� ��� ��� ������ ����� ");
 strcat(Text,"�� ������� � ����������������� � � ���� � ���� ������� ������ ��� ������ ���� ������� � ����. ��, ���, �������, � ���. ������� ����!");
 strcat(Text,"     P.S. �� ���� ������ � ���� ���������� ����� ������� ��������. ;) ��� �� ���������. :)         (�) ������� ������ (Da-nie), 01.08.2012. www.animekazan.net/forum2   ");
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
 SceUID_File=sceIoOpen(FileName,PSP_O_WRONLY|PSP_O_CREAT,0777);//��������� ����
 if (SceUID_File<=0)//������ �������� �����
 {
  delete(FileName);
  return;
 }
 //������� �����
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
  //��������� ������� ������� �������� � �����
  memcpy(line,(unsigned char *)&sHiScore[n],size);
  //�������� �
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
  //��������� ������
  if (sceIoWrite(SceUID_File,line,size+2)<size+2) break;//������ ������
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
 SceUID_File=sceIoOpen(FileName,PSP_O_RDONLY,0777);//��������� ����
 if (SceUID_File<=0)//������ �������� �����
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
  //��������� �������
  if (sceIoRead(SceUID_File,line,size+2)<size+2)//������ ������
  {
   ok=false;
   break;
  }
  //�������������� �������
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
  //���������� crc
  if ((*crc)!=crc_l)//������ ����������� �����
  {
   ok=false;
   break;
  }
  //��������� ������� �� ������ � ������� ��������
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
 strcpy(sHiScore[1].Name,"������� �����.......");sHiScore[1].Score=9000;
 strcpy(sHiScore[2].Name,"������ �������......");sHiScore[2].Score=8000;
 strcpy(sHiScore[3].Name,"������� ������......");sHiScore[3].Score=7000;
 strcpy(sHiScore[4].Name,"������ �������......");sHiScore[4].Score=6000;
 strcpy(sHiScore[5].Name,"����������� ��������");sHiScore[5].Score=5000;
 strcpy(sHiScore[6].Name,"������� �����.......");sHiScore[6].Score=4000;
 strcpy(sHiScore[7].Name,"����� ����������....");sHiScore[7].Score=3000;
 strcpy(sHiScore[8].Name,"������� �����.......");sHiScore[8].Score=2000;
 strcpy(sHiScore[9].Name,"��������� ����......");sHiScore[9].Score=1000;
}
void CMenu::DrawHiScore(void)
{
 char string[255];
 int n;
 SceCtrlData pad;
 u64 tick_frequency=sceRtcGetTickResolution();//������� �������� �������
 u64 begin_tick;
 u64 current_tick;
 sceRtcGetCurrentTick(&begin_tick);
 bool enable_control=false;
 while(!done)
 {
  if (enable_control==false)
  {
   sceRtcGetCurrentTick(&current_tick);//������� �������� �������
   double time_span=((double)(current_tick-begin_tick))/(double)tick_frequency;//��������� �����
   if (time_span>0.5) enable_control=true;
  }
  sceCtrlReadBufferPositive(&pad,1);
  if (pad.Buttons && enable_control==true) break;//������ ����� ������� � ������ ������ ���-�������
  //������� ������� ��������
  cSprite_HiScoreBack.Put(0,0,false);
  //������� ������� ��������
  cFontB.PrintAt(136,10,(char*)"������� ��������",true);
  for(n=0;n<10;n++)
  {
   sprintf(string,"%s %i",sHiScore[n].Name,sHiScore[n].Score);
   cFontB.PrintAt(70,40+n*20,string,true);
  }
  //������ ����� �� �����
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
 if (posy<0) return(true);//����� �� �������
 //�������� ������� �������� ����
 for(n=9;n>posy;n--) sHiScore[n]=sHiScore[n-1];
 sHiScore[posy].Score=score;
 strcpy(sHiScore[posy].Name,"                    ");
 //������ ���
 SceCtrlData pad;
 bool on_exit=false;
 unsigned char symbol=32;
 int posx=0;
 while(done==false && on_exit==false)
 {
  //������� ������ � ������� ��������
  sHiScore[posy].Name[posx]=symbol;
  //������� ������� ��������
  cSprite_HiScoreBack.Put(0,0,false);
  cFontB.PrintAt(136,10,(char*)"������� ��������",true);
  cFontB.PrintAt(32,250,(char*)"Select-�����. ������-���� �����.",true);
  char string[255];
  for(n=0;n<10;n++)
  {
   sprintf(string,"%s %i",sHiScore[n].Name,sHiScore[n].Score);
   cFontB.PrintAt(70,40+n*20,string,true);
  }
  Video_ViewDisplayPage();
  //��� ������� �� ������� �����, ����� � ����, � ��� �� �������
  while(done==false)
  {
   sceCtrlReadBufferPositive(&pad,1);
   if (pad.Buttons&PSP_CTRL_UP)//������ ������� "�����"
   {
    symbol++;
    if (symbol>(unsigned char)'~') symbol=32;
    break;
   }
   if (pad.Buttons&PSP_CTRL_DOWN)//������ ������� "�����"
   {
    symbol--;
    if (symbol<32) symbol=(unsigned char)'~';
    break;
   }
   if (pad.Buttons&PSP_CTRL_LEFT)//������ ������� "�����"
   {
    sHiScore[posy].Name[posx]=32;
    posx--;
    if (posx<0) posx=0;
    break;
   }
   if (pad.Buttons&PSP_CTRL_RIGHT)//������ ������� "������"
   {
    posx++;
    if (posx>19) posx=19;
    break;
   }
   if (pad.Buttons&PSP_CTRL_SELECT)//������ ������� select
   {
    on_exit=true;
    break;
   }
  }
  //������ ����� �� �����
  Video_ViewDisplayPage();
  Video_ChangeDisplayPage();
  //������ ��������
  sceKernelDelayThread(100000);
 }
 //��������� ������� ������
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
  sceRtcGetCurrentTick(&begin_tick);//������� �������� �������
  //���������� ����������� �� ����������
  sceCtrlReadBufferPositive(&pad,1);
  if (key_delay==0)//���������� ����������
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
    if (index==2) two_duck=false;//������ ���������� ����
    if (index==3 && sensitivity_x<99) sensitivity_x++;//��������� ���������������� (sensitivity- ����������� �������)
    if (index==4 && sensitivity_y<99) sensitivity_y++;//��������� ���������������� (sensitivity- ����������� �������)
   }
   if (pad.Buttons&PSP_CTRL_RIGHT)
   {
    key_delay=10;
    if (index==2) two_duck=true;//������ ���������� ����
    if (index==3 && sensitivity_x>1) sensitivity_x--;//����������� ���������������� (sensitivity- ����������� �������)
    if (index==4 && sensitivity_y>1) sensitivity_y--;//����������� ���������������� (sensitivity- ����������� �������)
   }
   if (pad.Buttons&PSP_CTRL_CROSS)//������ ����� ����
   {
    key_delay=10;
    if (index==0) return(true);//����� ����
    if (index==1) DrawHiScore();//������ ������� ��������
    if (index==2)//������ ���������� ����
    {
     if (two_duck==true) two_duck=false;
                    else two_duck=true;
    }
    if (index==5) return(false);//�����
   }
  }
  else key_delay--;
  //������ ����
  cSprite_MenuBack.Put(0,0,false);
  int y=110;
  int x_o[6]={5,5,5,5,5,5};
  x_o[index]=15;
  cFontB.PrintAt(x_o[0],y,(char*)"������ ����",true);y+=20;
  cFontB.PrintAt(x_o[1],y,(char*)"������� ��������",true);y+=20;
  if (two_duck==false) cFontB.PrintAt(x_o[2],y,"���� � ����� �����",true);
                  else cFontB.PrintAt(x_o[2],y,"���� � ����� ������",true);
  y+=20;
  char string[255];
  sprintf(string,"���������������� ��������� �� X:%02i",100-sensitivity_x);
  cFontB.PrintAt(x_o[3],y,string,true);y+=20;
  sprintf(string,"���������������� ��������� �� Y:%02i",100-sensitivity_y);
  cFontB.PrintAt(x_o[4],y,string,true);y+=20;
  cFontB.PrintAt(x_o[5],y,(char*)"����� �� ����",true);y+=20;
  //������� ������� ������
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
  //������ ����� �� �����
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
 return(true);
}
