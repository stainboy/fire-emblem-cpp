#include "stdafx.h"
#include "Ontimer.h"

time:: time(){}
time::~time(){}
short bd3[4]={4,2,6,0};

void time::timer(UINT n)
{
	if(MCIWndGetPosition(hMCI) >=MCIWndGetLength(hMCI)) 
		MCIWndPlay(hMCI);
	if(n==1)//我方
	{
		if(turntag!=1)return;
		flag++;	if(flag==3)flag=0;
		flag2++;if(flag2==2)flag2=0;
		flag1++;if(flag1==3)flag1=0;
		CClientDC dc(hwnd);
		dmap();
		if(cur.heromoving)
			{dman();movesto();}
		else if(cur.heroselect)
			{cur_normal();}
		else if(cur.selectfriend || cur.selectmon)
			{selectmenu();}
		else if(cur.heromenu)
			{cur_heromenu();}
		else if(cur.voidmenu)
			{cur_voidmenu();}
		else if(cur.status)
			{cur_status();}
		else if(cur.status1)
			{cur_status1();}
		else
			{cur_else();}
		dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	}
	if(n==2)//敌方
	{
		if(turntag!=2)return;
		AItime();
	}
	if(n==3)//光标回归
	{
		if(turntag!=3)return;	
		cur_backbit();
	}
	
}
	
void time::cur_normal()
{
	if(p->selected && flag1)
			{
				mdc1->SelectObject(hero[p->ID]);
				TransparentBlt2(*mdc,-32*screen.x+p->x*32,-32*screen.y+p->y*32,32,32,*mdc1,(8+flag2)*16,0,16,16,RGB(72,168,16));
			}
			dman();
			if(cur.heroselect)
			{
				mdc1->SelectObject(curp);
				for(i=0;i<=mapheight-1;i++)
					for(j=0;j<=mapwidth-1;j++)
						if(pass[i][j])
							TransparentBlt2(*mdc,-32*screen.x+j*32,-32*screen.y+i*32,32,32,*mdc1,16,0,16,16,RGB(255,255,255));
			}
			if(flag1)
			{
				mdc1->SelectObject(curp);
				TransparentBlt2(*mdc,-32*screen.x+cur.x*32,-32*screen.y+cur.y*32,32,32,*mdc1,32,0,16,16,RGB(0,0,0));
			}
}
void time::cur_heromenu()
{
		if(p->selected && flag1 )
		{
			mdc1->SelectObject(hero[p->ID]);
			TransparentBlt2(*mdc,-32*screen.x+p->x*32,-32*screen.y+p->y*32,32,32,*mdc1,(6+flag2%2+bd3[pt[mi].D])*16,0,16,16,RGB(72,168,16));
		}
		dman();
		bitmenu();
}
void time::cur_voidmenu()
{
	dman();
	int t=1;
	if(cur.x<=7){t=9;}
	mdc1->SelectObject(systembmp);
	mdc->BitBlt(t*32,32,512,512-32,mdc1,0,0,SRCCOPY);
	mdc1->SelectObject(triangle);
	mdc->BitBlt(t*32+16,32+32+32*systemmenu,512,512-32,mdc1,0,0,SRCCOPY);
}
void time::cur_status()
{
			if(p)
			if(p->selected && flag1)
			{
				mdc1->SelectObject(hero[p->ID]);
				TransparentBlt2(*mdc,-32*screen.x+p->x*32,-32*screen.y+p->y*32,32,32,*mdc1,(8+flag2)*16,0,16,16,RGB(72,168,16));
			}
			if(q)
			if(q->selected && flag1)
			{
				mdc1->SelectObject(mon);
				TransparentBlt2(*mdc,-32*screen.x+q->x*32,-32*screen.y+q->y*32,32,32,*mdc1,flag*16,0,16,16,RGB(72,168,16));
			}
			flag=0;
			dman();
			herostatus();		
}
void time::cur_status1()
{
			if(p)
			if(p->selected && flag1)
			{
				mdc1->SelectObject(hero[p->ID]);
				TransparentBlt2(*mdc,-32*screen.x+p->x*32,-32*screen.y+p->y*32,32,32,*mdc1,(8+flag2)*16,0,16,16,RGB(72,168,16));
			}
			flag=0;
			dman();
			herostatus1();
}
void time::cur_else()
{	
	dman();
	mdc1->SelectObject(curp);
	if(flag1)
		TransparentBlt2(*mdc,-32*screen.x+cur.x*32,-32*screen.y+cur.y*32,32,32,*mdc1,0,0,16,16,RGB(0,0,0));
}