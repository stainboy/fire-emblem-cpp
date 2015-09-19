#include "stdafx.h"
#include "gamepro.h"

gamemap:: gamemap(){}
gamemap::~gamemap(){}

void gamemap::initmap()
{
	flag=0;
	flag1=0;
	flag2=0;
	systemmenu=0;
	heromenu=0;
	zone();
	for(p1=hhead;p1!=0;p1=p1->next)
		masshero[p1->y][p1->x]=p1->ID;
	for(q1=mhead;q1!=0;q1=q1->next)
		massmon[q1->y][q1->x]=q1->ID;
	for(i=0;i<=mapheight-1;i++)
		for(j=0;j<=mapwidth-1;j++)
		{
			mdc1->SelectObject(b[maze[i][j]]);
			map->BitBlt(j*32,i*32,32,32,mdc1,0,0,SRCCOPY);
		}
	CString cc;
	MCIWndClose(hMCI);
	cc="res/1.mp3";
	hMCI = MCIWndCreate(NULL, NULL,WS_POPUP
					|MCIWNDF_NOPLAYBAR|MCIWNDF_NOMENU
					,cc);
	MCIWndPlay(hMCI);
}

void gamemap::dmap()
{
	mdc->BitBlt(0,0,WIDTH,HEIGHT,map,32*screen.x,32*screen.y,SRCCOPY);
}
void gamemap::dman()
{
	for(p1=hhead;p1!=0;p1=p1->next)
	{
		mdc1->SelectObject(hero[p1->ID]);
		if(!p1->selected)
			if(p1->action)
				TransparentBlt2(*mdc,-32*screen.x+p1->x*32,-32*screen.y+p1->y*32,32,32,*mdc1,flag*16,0,16,16,RGB(72,168,16));
			else
				TransparentBlt2(*mdc,-32*screen.x+p1->x*32,-32*screen.y+p1->y*32,32,32,*mdc1,(3+flag)*16,0,16,16,RGB(72,168,16));
	}
	for(q1=mhead;q1!=0;q1=q1->next)
	{
		mdc1->SelectObject(mon);
		if(!q1->selected)
			if(q1->action)
				TransparentBlt2(*mdc,-32*screen.x+q1->x*32,-32*screen.y+q1->y*32,32,32,*mdc1,flag*16,0,16,16,RGB(72,168,16));
			else
				TransparentBlt2(*mdc,-32*screen.x+q1->x*32,-32*screen.y+q1->y*32,32,32,*mdc1,flag*16,16,16,16,RGB(72,168,16));
	}
}

void gamemap::herostatus()
{
	int t=1;
	SetBkMode(*mdc,TRANSPARENT);	
	SetTextColor(*mdc,RGB(255,255,255));
	CString cc="有物品",cc1="没物品";
	mdc1->SelectObject(turn);
	if(cur.x<=7){t=9;}
			mdc->BitBlt(t*32,32,6*32,32,mdc1,0,0,SRCCOPY);
			mdc->BitBlt(t*32,2*32,6*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt(t*32,3*32,6*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt(t*32,4*32,6*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt(t*32,5*32,6*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt(t*32,6*32,6*32,32,mdc1,0,32,SRCCOPY);
			mdc->BitBlt(t*32,7*32,6*32,2*32,mdc1,0,0,SRCCOPY);
	if(p)
	{
		if(p->item)
			mdc->TextOut(t*32+40,8*32-16,cc);
		else
			mdc->TextOut(t*32+40,8*32-16,cc1);
		mdc->TextOut(t*32+32,2*32-16,p->name);
		char chp[20];
		mdc->TextOut(t*32+32,3*32-16,JOB(p->job));
		sprintf(chp,"Lev:%d   Exp:%d",p->P.level,p->P.exp);
		mdc->TextOut(t*32+32,4*32-16,chp);
		cc="武器:剑";
		mdc->TextOut(t*32+32,5*32-16,cc);
		sprintf(chp,"HP:%d/%d",p->P.hp,p->P.hpmax);
		mdc->TextOut(t*32+32,6*32-16,chp);
	}
	if(q)
	{
		if(q->item)
			mdc->TextOut(t*32+40,8*32-16,cc);
		else
			mdc->TextOut(t*32+40,8*32-16,cc1);
		mdc->TextOut(t*32+32,2*32-16,q->name);
		char chp[20];
		mdc->TextOut(t*32+32,3*32-16,JOB(q->job));
		sprintf(chp,"Lev:%d   Exp:%d",q->P.level,q->P.exp);
		mdc->TextOut(t*32+32,4*32-16,chp);
		cc="武器:剑";
		mdc->TextOut(t*32+32,5*32-16,cc);
		sprintf(chp,"HP:%d/%d",q->P.hp,q->P.hpmax);
		mdc->TextOut(t*32+32,6*32-16,chp);
	}
}

void gamemap::herostatus1()
{
	int t=1,o=1;
	SetBkMode(*mdc,TRANSPARENT);	
	SetTextColor(*mdc,RGB(255,255,255));
	CString cc;
	mdc1->SelectObject(turn);
	if(cur.x<=7){t=9;o=0;}
			mdc->BitBlt(t*32,32,6*32,32,mdc1,0,0,SRCCOPY);
			mdc->BitBlt(t*32,2*32,6*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt(t*32,3*32,6*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt(t*32,4*32,6*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt(t*32,5*32,6*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt(t*32,6*32,6*32,32,mdc1,0,32,SRCCOPY);
			
			mdc->BitBlt(t*32,8*32,6*32,32,mdc1,0,0,SRCCOPY);
			mdc->BitBlt(t*32,9*32,6*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt(t*32,10*32,6*32,32,mdc1,0,32,SRCCOPY);

if(p)
{			mdc->BitBlt((10-t-o)*32,32,2*32,32,mdc1,0,0,SRCCOPY);
			mdc->BitBlt((12-t-o)*32,32,2*32,32,mdc1,4*32,0,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,2*32,2*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,3*32,2*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt((12-t-o)*32,2*32,2*32,32,mdc1,4*32,16,SRCCOPY);
			mdc->BitBlt((12-t-o)*32,3*32,2*32,32,mdc1,4*32,16,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,4*32,2*32,32,mdc1,0,32,SRCCOPY);
			mdc->BitBlt((12-t-o)*32,4*32,2*32,32,mdc1,4*32,32,SRCCOPY);
}
			mdc->BitBlt((10-t-o)*32,5*32,4*32,32,mdc1,0,0,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,6*32,4*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,7*32,4*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,8*32,4*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,9*32,4*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,10*32,4*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,11*32,4*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,12*32,4*32,32,mdc1,0,16,SRCCOPY);
			mdc->BitBlt((10-t-o)*32,13*32,4*32,32,mdc1,0,32,SRCCOPY);

			mdc->BitBlt((14-t-o)*32,5*32,3*32,32,mdc1,3*32,0,SRCCOPY);
			mdc->BitBlt((14-t-o)*32,6*32,3*32,32,mdc1,3*32,16,SRCCOPY);
			mdc->BitBlt((14-t-o)*32,7*32,3*32,32,mdc1,3*32,16,SRCCOPY);
			mdc->BitBlt((14-t-o)*32,8*32,3*32,32,mdc1,3*32,16,SRCCOPY);
			mdc->BitBlt((14-t-o)*32,9*32,3*32,32,mdc1,3*32,16,SRCCOPY);
			mdc->BitBlt((14-t-o)*32,10*32,3*32,32,mdc1,3*32,16,SRCCOPY);
			mdc->BitBlt((14-t-o)*32,11*32,3*32,32,mdc1,3*32,16,SRCCOPY);
			mdc->BitBlt((14-t-o)*32,12*32,3*32,32,mdc1,3*32,16,SRCCOPY);
			mdc->BitBlt((14-t-o)*32,13*32,3*32,32,mdc1,3*32,32,SRCCOPY);
	if(p)
	{
		mdc1->SelectObject(heropic);
		mdc->BitBlt((10-t-o)*32+16,32+16,96,96,mdc1,96*p->ID,0,SRCCOPY);
		mdc->TextOut(t*32+32,2*32-16,p->name);
		char chp[20];
		mdc->TextOut(t*32+32,3*32-16,JOB(p->job));
		sprintf(chp,"Lev:%d   Exp:%d",p->P.level,p->P.exp);
		mdc->TextOut(t*32+32,4*32-16,chp);
		cc="武器:剑";
		mdc->TextOut(t*32+32,5*32-16,cc);
		sprintf(chp,"HP:%d/%d",p->P.hp,p->P.hpmax);
		mdc->TextOut(t*32+32,6*32-16,chp);
		cc="不能";
		mdc->TextOut(t*32+32,9*32-8,cc);
		cc="习得魔法";
		mdc->TextOut(t*32+32,10*32-8,cc);
		sprintf(chp,"力量:       %d",p->P.str);
		mdc->TextOut((10-t-o)*32+40,6*32,chp);
		sprintf(chp,"技术:       %d",p->P.dex);
		mdc->TextOut((10-t-o)*32+40,7*32,chp);
		sprintf(chp,"速度:       %d",p->P.speed);
		mdc->TextOut((10-t-o)*32+40,8*32,chp);
		sprintf(chp,"运气:       %d",p->P.luck);
		mdc->TextOut((10-t-o)*32+40,9*32,chp);
		sprintf(chp,"防御:       %d",p->P.def);
		mdc->TextOut((10-t-o)*32+40,10*32,chp);
		sprintf(chp,"魔防:       %d",p->P.mdef);
		mdc->TextOut((10-t-o)*32+40,11*32,chp);
		sprintf(chp,"移动:       %d",p->movement);
		mdc->TextOut((10-t-o)*32+40,12*32,chp);
		sprintf(chp," EXP:       %d",p->P.exp);
		mdc->TextOut((10-t-o)*32+40,13*32,chp);
	}
	if(q)
	{
		mdc->TextOut(t*32+32,2*32-16,q->name);
		char chp[20];
		mdc->TextOut(t*32+32,3*32-16,JOB(q->job));
		sprintf(chp,"Lev:%d   Exp:%d",q->P.level,q->P.exp);
		mdc->TextOut(t*32+32,4*32-16,chp);
		cc="武器:剑";
		mdc->TextOut(t*32+32,5*32-16,cc);
		sprintf(chp,"HP:%d/%d",q->P.hp,q->P.hpmax);
		mdc->TextOut(t*32+32,6*32-16,chp);
		cc="不能";
		mdc->TextOut(t*32+32,9*32-8,cc);
		cc="习得魔法";
		mdc->TextOut(t*32+32,10*32-8,cc);
		sprintf(chp,"力量:       %d",q->P.str);
		mdc->TextOut((10-t-o)*32+40,6*32,chp);
		sprintf(chp,"技术:       %d",q->P.dex);
		mdc->TextOut((10-t-o)*32+40,7*32,chp);
		sprintf(chp,"速度:       %d",q->P.speed);
		mdc->TextOut((10-t-o)*32+40,8*32,chp);
		sprintf(chp,"运气:       %d",q->P.luck);
		mdc->TextOut((10-t-o)*32+40,9*32,chp);
		sprintf(chp,"防御:       %d",q->P.def);
		mdc->TextOut((10-t-o)*32+40,10*32,chp);
		sprintf(chp,"魔防:       %d",q->P.mdef);
		mdc->TextOut((10-t-o)*32+40,11*32,chp);
		sprintf(chp,"移动:       %d",q->movement);
		mdc->TextOut((10-t-o)*32+40,12*32,chp);
		sprintf(chp," EXP:       %d",q->P.exp);
		mdc->TextOut((10-t-o)*32+40,13*32,chp);
	}
}

void gamemap::win()
{
	CClientDC dc(hwnd);
			dmap();
			dman();
			mdc1->SelectObject(turn);
			mdc->BitBlt(5*32,6*32,512,512-32,mdc1,0,0,SRCCOPY);
			SetBkMode(*mdc,TRANSPARENT);	
			SetTextColor(*mdc,RGB(255,255,255));
			CString cc="VICTORY";
			mdc->TextOut(7*32-8,7*32-8,cc);
			dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
			Sleep(1000);
//胜利的代码
}
void gamemap::loss()
{
	CClientDC dc(hwnd);
	dmap();
	dman();
	mdc1->SelectObject(turn);
	mdc->BitBlt(5*32,6*32,512,512-32,mdc1,0,0,SRCCOPY);
	SetBkMode(*mdc,TRANSPARENT);	
	SetTextColor(*mdc,RGB(255,255,255));
	CString cc="LOSS";
	mdc->TextOut(7*32,7*32-8,cc);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(1000);
//失败的代码
}

void gamemap::endheroturn()
{
	CClientDC dc(hwnd);
	for(p1=hhead;p1!=0;p1=p1->next)
		p1->action=true;
			dmap();
			dman();
			mdc1->SelectObject(turn);
			mdc->BitBlt(5*32,6*32,WIDTH,HEIGHT,mdc1,0,0,SRCCOPY);
			SetBkMode(*mdc,TRANSPARENT);	
			SetTextColor(*mdc,RGB(255,255,255));
			CString cc="ENEMY";
			mdc->TextOut(7*32-4,7*32-8,cc);
			dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
			Sleep(500);
			monturn();
}
void gamemap::monturn()
{
	CClientDC dc(hwnd);
	dmap();
	dman();
	mdc1->SelectObject(turn);
	mdc->BitBlt(5*32,6*32,WIDTH,HEIGHT,mdc1,0,0,SRCCOPY);
	SetBkMode(*mdc,TRANSPARENT);	
	SetTextColor(*mdc,RGB(255,255,255));
	CString cc="HERO";
	mdc->TextOut(7*32,7*32-8,cc);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(500);
	cur.x=hhead->x;cur.y=hhead->y;
}

void gamemap::doattack()
{
	up=0;down=0;right=0;left=0;
	for(i=0;i<=p->range;i++)
		for(j=0;i+j<=p->range;j++)
		{
			if( massmon[p->y+i][p->x+j]!=100)
				{cur.x=p->x+j;cur.y=p->y+i;up=1;}
			if(massmon[cur.y-i][cur.x-j]!=100)
				{cur.x=p->x-j;cur.y=p->y-i;down=1;}
			if(massmon[cur.y-i][cur.x+j]!=100)
				{cur.x=p->x+j;cur.y=p->y-i;left=1;}
			if(massmon[cur.y+i][cur.x-j]!=100)
				{cur.x=p->x-j;cur.y=p->y+i;right=1;}
		}
}
void gamemap::dochange()
{
	up=0;down=0;right=0;left=0;
	if(masshero[p->y-1][p->x]!=100 &&
	(h[masshero[p->y-1][p->x]].item!=0||p->item!=0))
		{cur.x=p->x;cur.y=p->y-1;up=1;}
	if(masshero[p->y+1][p->x]!=100 &&
	(h[masshero[p->y+1][p->x]].item!=0||p->item!=0))
		{cur.x=p->x;cur.y=p->y+1;down=1;}
	if(masshero[p->y][p->x-1]!=100 &&
	(h[masshero[p->y][p->x-1]].item!=0||p->item!=0))
		{cur.x=p->x-1;cur.y=p->y;left=1;}
	if(masshero[p->y][p->x+1]!=100 &&
	(h[masshero[p->y][p->x+1]].item!=0||p->item!=0))
		{cur.x=p->x+1;cur.y=p->y;right=1;}
}
void gamemap::warstart()
{
	CClientDC dc(hwnd);
	mdc1->SelectObject(warbground);
	mdc->BitBlt(0,0,512,512-32,mdc1,0,0,BLACKNESS);
	mdc1->SelectObject(warstatus);
	mdc->BitBlt(18,272,238*2,96*2,mdc1,0,0,SRCCOPY);
	mdc1->SelectObject(job[q->job]);
	mdc->BitBlt(123,206,76,32*2,mdc1,0,0,SRCCOPY);
	mdc1->SelectObject(job[p->job]);
	mdc->BitBlt(333,206,76,32*2,mdc1,0,0,SRCCOPY);
//战斗状态on-----------------------------------------------------------
	mdc1->SelectObject(blood);
//HP-----------------------------------------------------------
	for(i=1;i<=q->P.hpmax;i++)
		if(i<=26)
			mdc->BitBlt(18+4+8*i,386,8,14,mdc1,8,0,SRCCOPY);
		else
			mdc->BitBlt(18+4+8*(i-26),370,8,14,mdc1,8,0,SRCCOPY);
	for(i=1;i<=q->P.hp;i++)
		if(i<=26)
			mdc->BitBlt(18+4+8*i,386,8,14,mdc1,0,0,SRCCOPY);
		else
			mdc->BitBlt(18+4+8*(i-26),370,8,14,mdc1,0,0,SRCCOPY);
	for(i=1;i<=p->P.hpmax;i++)
		if(i<=26)
			mdc->BitBlt(123+140+8*i,386,8,14,mdc1,16,0,SRCCOPY);
		else
			mdc->BitBlt(123+140+8*(i-26),370,8,14,mdc1,16,0,SRCCOPY);
	for(i=1;i<=p->P.hp;i++)
		if(i<=26)
			mdc->BitBlt(123+140+8*i,386,8,14,mdc1,0,0,SRCCOPY);
		else
			mdc->BitBlt(123+140+8*(i-26),370,8,14,mdc1,0,0,SRCCOPY);
//命中-----------------------------------------------------------
	for(i=1;i<=40;i++)
		mdc->BitBlt(18+58+4*i,386+22,2,8,mdc1,24,0,SRCCOPY);
	for(i=1;i<=(int)(mattr/2.5);i++)
		mdc->BitBlt(18+58+4*i,386+22,4,8,mdc1,0,0,WHITENESS);
	for(i=1;i<=40;i++)
		mdc->BitBlt(18+298+4*i,386+22,2,8,mdc1,26,0,SRCCOPY);
	for(i=1;i<=(int)(hattr/2.5);i++)
		mdc->BitBlt(18+298+4*i,386+22,4,8,mdc1,0,0,WHITENESS);
//攻击力-----------------------------------------------------------
	for(i=1;i<=40;i++)
		mdc->BitBlt(18+58+4*i,386+38,2,8,mdc1,24,0,SRCCOPY);
	for(i=1;i<=((q->P.str<40)?q->P.str:40);i++)
		mdc->BitBlt(18+58+4*i,386+38,4,8,mdc1,0,0,WHITENESS);
	for(i=1;i<=40;i++)
		mdc->BitBlt(18+298+4*i,386+38,2,8,mdc1,26,0,SRCCOPY);
	for(i=1;i<=((q->P.str<40)?q->P.str:40);i++)
		mdc->BitBlt(18+298+4*i,386+38,4,8,mdc1,0,0,WHITENESS);
//防御力-----------------------------------------------------------
	for(i=1;i<=40;i++)
		mdc->BitBlt(18+58+4*i,386+54,2,8,mdc1,24,0,SRCCOPY);
	for(i=1;i<=((q->P.def<40)?q->P.def:40);i++)
		mdc->BitBlt(18+58+4*i,386+54,4,8,mdc1,0,0,WHITENESS);
	for(i=1;i<=40;i++)
		mdc->BitBlt(18+298+4*i,386+54,2,8,mdc1,26,0,SRCCOPY);
	for(i=1;i<=((q->P.def<40)?q->P.def:40);i++)
		mdc->BitBlt(18+298+4*i,386+54,4,8,mdc1,0,0,WHITENESS);
//属性-----------------------------------------------------------
	SetBkMode(*mdc,TRANSPARENT);	
	SetTextColor(*mdc,RGB(255,255,255));
	char chp[20];CString cc;
	sprintf(chp,"%s",q->name);
	mdc->TextOut(40,300,chp);
	mdc->TextOut(40,330,JOB(q->job));
	sprintf(chp,"LV%d",q->P.level);
	mdc->TextOut(180,300,chp);
	sprintf(chp,"%s",p->name);
	mdc->TextOut(40+240,300,chp);
	mdc->TextOut(40+240,330,JOB(p->job));
	sprintf(chp,"LV%d",p->P.level);
	mdc->TextOut(180+240,300,chp);
//战斗状态off-----------------------------------------------------------
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(500);
}
void gamemap::warhero()
{
	CClientDC dc(hwnd);
	mdc->SetBkMode(TRANSPARENT);
	mdc->SetTextColor(RGB(255,255,255));
//攻击的循环on-----------------------------------------------------------
	mdc1->SelectObject(warmessage);
	mdc->BitBlt(32,300,223*2,30*2,mdc1,0,0,SRCCOPY);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(300);

	char chp[100];
	sprintf(chp,("%s发起了一次攻击..."),p->name);
	mdc->TextOut(50,305,chp);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(500);

	if(hattr>rand()%100)
	{
		if((int)(p->P.dex*1.5+p->P.luck*1)>=rand()%100)
		{
			sprintf(chp,("%s愤怒一击...%s损失了%dHP"),p->name,q->name,3*hdam);
			q->P.hp-=3*hdam;
			damall+=3*hdam;
			dc.BitBlt(-10,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
			Sleep(20);
			dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
			Sleep(20);
		}
		else
		{
			sprintf(chp,("命中了...%s损失了%dHP"),q->name,hdam);
			q->P.hp-=hdam;
			damall+=hdam;
			dc.BitBlt(-10,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
			Sleep(20);
			dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
			Sleep(20);
		}
		mdc1->SelectObject(blood);
		for(i=1;i<=q->P.hpmax;i++)
			if(i<=26)
				mdc->BitBlt(18+4+8*i,386,8,14,mdc1,8,0,SRCCOPY);
			else
				mdc->BitBlt(18+4+8*(i-26),370,8,14,mdc1,8,0,SRCCOPY);
		for(i=1;i<=q->P.hp;i++)
			if(i<=26)
				mdc->BitBlt(18+4+8*i,386,8,14,mdc1,0,0,SRCCOPY);
			else
				mdc->BitBlt(18+4+8*(i-26),370,8,14,mdc1,0,0,SRCCOPY);
	}
	else
		sprintf(chp,("%s巧妙的跺过了攻击"),q->name);
	
	mdc->TextOut(50,330,chp);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(500);
//攻击的循环off-----------------------------------------------------------
}

void gamemap::warmon()
{
{
	CClientDC dc(hwnd);
	mdc->SetBkMode(TRANSPARENT);
	mdc->SetTextColor(RGB(255,255,255));
//攻击的循环on-----------------------------------------------------------
	mdc1->SelectObject(warmessage);
	mdc->BitBlt(32,300,223*2,30*2,mdc1,0,0,SRCCOPY);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(300);

	char chp[100];
	sprintf(chp,("%s发起了攻击..."),q->name);
	mdc->TextOut(50,305,chp);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(500);

	if(mattr>rand()%100)
	{
		sprintf(chp,("命中了...%s损失了%dHP"),p->name,mdam);
		p->P.hp-=mdam;
			dc.BitBlt(10,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
			Sleep(20);
			dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
			Sleep(20);
		mdc1->SelectObject(blood);
		for(i=1;i<=p->P.hpmax;i++)
			if(i<=26)
				mdc->BitBlt(123+140+8*i,386,8,14,mdc1,16,0,SRCCOPY);
			else
				mdc->BitBlt(123+140+8*(i-26),370,8,14,mdc1,16,0,SRCCOPY);
		for(i=1;i<=p->P.hp;i++)
			if(i<=26)
				mdc->BitBlt(123+140+8*i,386,8,14,mdc1,0,0,SRCCOPY);
			else
				mdc->BitBlt(123+140+8*(i-26),370,8,14,mdc1,0,0,SRCCOPY);
	}
	else
		sprintf(chp,("%s巧妙的跺过了攻击"),p->name);
	
	mdc->TextOut(50,330,chp);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(500);
}
}
void gamemap::expup()
{
	CClientDC dc(hwnd);
	mdc->SetBkMode(TRANSPARENT);
	mdc->SetTextColor(RGB(255,255,255));

	mdc1->SelectObject(warmessage);
	mdc->BitBlt(32,300,223*2,30*2,mdc1,0,0,SRCCOPY);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(300);
	char chp[20];
	int x;
	if(q->P.hp<=0)
		x=(int)(52*(q->job+10)/(p->job+10)*(q->P.level+5)/(p->P.level+5))+1;
	else
		x=(int)(damall*(q->job+10)/(p->job+10)*(q->P.level+5)/(p->P.level+5))+1;
	p->P.exp+=x;
	sprintf(chp,("%s获得了%d经验值..."),p->name,x);
	mdc->TextOut(50,320,chp);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(500);
}
void gamemap::levelup()
{
	CClientDC dc(hwnd);
	mdc->SetBkMode(TRANSPARENT);
	mdc->SetTextColor(RGB(255,255,255));

	mdc1->SelectObject(lvup);
	mdc->BitBlt(120,272,150*2,94*2,mdc1,0,0,SRCCOPY);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(300);
	char chp[20];
	sprintf(chp,("%s升级了..."),p->name);
	p->P.level++;
	mdc->TextOut(140,300,chp);
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(500);
	int lvtag=0;
	if((p->P.strup>=rand()%100 && lvtag<=2) && p->P.str<40)
	{
		p->P.str++;lvtag++;
		mdc->TextOut(140,300+25*lvtag,"力量增加1...");
		dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
		Sleep(500);
	}
	if((p->P.dexup>=rand()%100 && lvtag<=2) && p->P.dex<40)
	{
		p->P.dex++;lvtag++;
		mdc->TextOut(140,300+25*lvtag,"技术增加1...");
		dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
		Sleep(500);
	}
	if((p->P.speedup>=rand()%100 && lvtag<=2) && p->P.speed<40)
	{
		p->P.speed++;lvtag++;
		mdc->TextOut(140,300+25*lvtag,"速度增加1...");
		dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
		Sleep(500);
	}
	if((p->P.luckup>=rand()%100 && lvtag<=1) && p->P.luck<40)
	{
		p->P.luck++;lvtag++;
		mdc->TextOut(140,300+25*lvtag,"运气增加1...");
		dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
		Sleep(500);
	}
	if((p->P.defup>=rand()%100 && lvtag<=2) && p->P.def<40)
	{
		p->P.def++;lvtag++;
		mdc->TextOut(140,300+25*lvtag,"防御增加1...");
		dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
		Sleep(500);
	}
	if((p->P.mdefup>=rand()%100 && lvtag<=0)&& p->P.mdef<=20)
	{
		p->P.mdef++;lvtag++;
		mdc->TextOut(140,300+25*lvtag,"魔防增加1...");
		dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
		Sleep(500);
	}
	if(((p->P.hpup>=rand()%100 && lvtag<=3)||lvtag==0)&& p->P.hpmax<52)
	{
		p->P.hpmax++;lvtag++;
		mdc->TextOut(140,300+25*lvtag,"HP增加1...");
		dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
		Sleep(500);
	}
	Sleep(500);
}

void gamemap::exchange()
{
	CClientDC dc(hwnd);
			mdc1->SelectObject(turn);
			mdc->BitBlt(5*32,6*32,WIDTH,HEIGHT,mdc1,0,0,SRCCOPY);
			SetBkMode(*mdc,TRANSPARENT);	
			SetTextColor(*mdc,RGB(255,255,255));
			CString cc="物品交换成功";
			mdc->TextOut(6*32-4,7*32-8,cc);
			dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
			Sleep(500);
}

void gamemap::war()
{
				damall=0;
				//哪方攻击2次
				if(p->P.speed>q->P.speed)
				{hatt=2;matt=1;}
				else if(p->P.speed==q->P.speed)
				{hatt=1;matt=1;}
				else
				{hatt=1;matt=2;}
				
				//命中率
				hattr=(int)((85+(p->P.dex-q->P.dex)*0.5)*(100-ground[q->y][q->x])/100)-q->P.luck;
				if(hattr>100)hattr=100;
				else if(hattr<=0)hattr=0;
				mattr=(int)((85+(q->P.dex-p->P.dex)*0.5)*(100-ground[p->y][p->x])/100)-p->P.luck;
				if(mattr>100)mattr=100;
				else if(mattr<=0)mattr=0;

				//伤害
				hdam=p->P.str-q->P.def;
				if(hdam<=0)hdam=1;
				mdam=q->P.str-p->P.def;
				if(mdam<=0)mdam=1;

				warstart();
				for(;hatt || matt;)
				{
					if(hatt){warhero();hatt--;if(q->P.hp<=0)break;}
					if(matt){warmon();matt--;if(p->P.hp<=0)break;}
				}

				if(p->P.hp<=0)
				{
					del(&hhead,p);
					masshero[p->y][p->x]=100;
				}
				else
				{
					expup();
					if(p->P.exp>=100)
						if(p->P.level!=20)
						{p->P.exp-=100;levelup();}
						else p->P.exp=100;
				}
				if(q->P.hp<=0)
				{
					del(&mhead,q);
					massmon[q->y][q->x]=100;
				}
}
void gamemap::fin()
{
	CClientDC dc(hwnd);
	mdc->SetBkMode(TRANSPARENT);
	mdc->SetTextColor(RGB(255,255,255));
	mdc1->SelectObject(warmessage);
	mdc->BitBlt(0,0,WIDTH,HEIGHT,mdc1,0,0,BLACKNESS);
	mdc->TextOut(230,230,"fin");
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
	Sleep(1000);
}