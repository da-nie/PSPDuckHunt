#include "cfonta.h"

CFontA cFontA;

//----------------------------------------------------------------------------------------------------
//�����������
//----------------------------------------------------------------------------------------------------
CFontA::CFontA(void)
{
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CFontA::~CFontA()
{
 cSprite_Font.Release();
}
//----------------------------------------------------------------------------------------------------
//��������� �����
//----------------------------------------------------------------------------------------------------
void CFontA::Load(char *FileName,unsigned char alpha_r,unsigned char alpha_g,unsigned char alpha_b)
{
 cSprite_Font.Load(FileName);
 cSprite_Font.SetAlpha(0,alpha_r,alpha_g,alpha_b);
}
//----------------------------------------------------------------------------------------------------
//������� ������
//----------------------------------------------------------------------------------------------------
void CFontA::PrintAt(int x,int y,char *string,bool alpha)
{
 if (string==NULL) return;
 int length=strlen(string);
 for(int n=0;n<length;n++,x+=9)
 {
  int code=-1;
  int b=(unsigned char)string[n];
  if (b==(unsigned char)'`') code=0;
  if (b==(unsigned char)';') code=1;
  if (b==(unsigned char)',') code=2;
  if (b==(unsigned char)'.') code=3;
  if (b==(unsigned char)'=') code=4;
  if (b==(unsigned char)'(') code=5;
  if (b==(unsigned char)')') code=6;
  if (b==(unsigned char)'-') code=7;
  if (b==(unsigned char)'+') code=8;
  if (b==(unsigned char)'�') code=77;
  if (b>=(unsigned char)'0' && b<=(unsigned char)'9') code=9+b-((unsigned char)'0');
  if (b>=(unsigned char)'A' && b<=(unsigned char)'Z') code=19+b-((unsigned char)'A');
  if (b>=(unsigned char)'�' && b<=(unsigned char)'�') code=45+b-((unsigned char)'�');
  if (code<0) continue;
  cSprite_Font.PutSpriteItem(x,y,code*9,0,9,7,alpha);
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ����� ������ � ��������
//----------------------------------------------------------------------------------------------------
int CFontA::GetStringWidth(char *string)
{
 return(strlen(string)*9);
}
//----------------------------------------------------------------------------------------------------
//�������� ������ ������ � ��������
//----------------------------------------------------------------------------------------------------
int CFontA::GetStringHeight(char *string)
{
 return(7);
}
