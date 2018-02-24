#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct SAnimate
{
 int Mode;//�����
 int Frame;//����
 int dX;//��������� ��������� ����� ��������� �����
 int dY;
};

int RND(int max);//��������� �����
void SetAnimate(SAnimate *sAnimatePtr,int Mode,int Frame,int dX,int dY);//������ ��������� ��������

#endif //COMMON_H_INCLUDED
