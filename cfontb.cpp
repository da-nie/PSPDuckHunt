#include "cfontb.h"

CFontB cFontB;

CFontB::CFontB(void)
{
}
CFontB::~CFontB()
{
 Release();
}
bool CFontB::Load(char *FileName,unsigned char alpha_r,unsigned char alpha_g,unsigned char alpha_b)
{
 bool res=cSprite_Font.Load(FileName);
 cSprite_Font.SetAlpha(0,alpha_r,alpha_g,alpha_b);
 return(res);
}
void CFontB::Release(void)
{
 cSprite_Font.Release();
}
void CFontB::PrintAt(int x,int y,char *string,bool alpha)
{
 int n;
 if (string==NULL) return;
 int length=strlen(string);
 for(n=0;n<length;n++,x+=13)
 {
  int code=-1;
  int b=(unsigned char)string[n];
  if (b<=(unsigned char)'~') code=b-32;
  if (b>=(unsigned char)'À') code=b-(unsigned char)'À'+(unsigned char)'~'-30;
  if (code<0) continue;
  cSprite_Font.PutSpriteItem(x,y,code*13,0,13,22,alpha);
 }
}
