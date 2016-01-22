#include "stdafx.h"
#include "AI.h"

monster:: monster(){}
monster::~monster(){}
short bd2[4]={4,2,6,0};
short cd2[8]={-1,0,1,0,0,1,0,-1};
short eff2[36]={1,	1,	1,	1,
				10,	10,	10,	10,
				2,	2,	2,	2,
				1,	1,	1,	1,
				1,	1,	1,	1,
				10,	10,	10,	10,
				1,	1,	1,	1,
				1,	1,	1,	1,
				1,	1,	1,	1};//9*4

void monster::initAI()
{
	mtime.attack=0;
	mtime.move=1;
	mtime.time=0;
	mtime.canatt=0;
}

void monster::cur_backpress(HERO *p)
{
	ori_p.x=(float)screen.x;
	ori_p.y=(float)screen.y;
	cur.x=p->x;
	cur.y=p->y;

	tar_p.x=(float)(cur.x-8);
	if(tar_p.x<0.00001)tar_p.x=0;
	if(tar_p.x+16>mapwidth)tar_p.x=(float)mapwidth-16;

	tar_p.y=(float)(cur.y-7);
	if(tar_p.y<0.00001)tar_p.y=0;
	if(tar_p.y+15>mapheight)tar_p.y=(float)mapheight-15;

	if(tar_p.x!=ori_p.x || tar_p.y!=ori_p.y)
	{
		turn1=turntag;
		turntag=3;
	}
}

void monster::cur_backbit()
{
	CClientDC dc(hwnd);
	if		(tar_p.x-ori_p.x>0)ori_p.x+=0.125;
	else if	(tar_p.x-ori_p.x<0)ori_p.x-=0.125;
	else if	(tar_p.y-ori_p.y>0)ori_p.y+=0.125;
	else if	(tar_p.y-ori_p.y<0)ori_p.y-=0.125;
	else 
	{
		screen.x=(int)tar_p.x;
		screen.y=(int)tar_p.y;
		turntag=turn1;
	}
	mdc->BitBlt(0,0,WIDTH,HEIGHT,map,(int)(32*ori_p.x),(int)(32*ori_p.y),SRCCOPY);
	for(p1=hhead;p1!=0;p1=p1->next)
	{
		mdc1->SelectObject(hero[p1->ID]);
		if(!p1->selected)
			if(p1->action)
				TransparentBlt2(*mdc,(int)(-32*ori_p.x)+p1->x*32,(int)(-32*ori_p.y)+p1->y*32,32,32,*mdc1,flag*16,0,16,16,RGB(72,168,16));
			else
				TransparentBlt2(*mdc,(int)(-32*ori_p.x)+p1->x*32,(int)(-32*ori_p.y)+p1->y*32,32,32,*mdc1,(3+flag)*16,0,16,16,RGB(72,168,16));
	}
	for(q1=mhead;q1!=0;q1=q1->next)
	{
		mdc1->SelectObject(mon);
		if(!q1->selected)
			if(q1->action)
				TransparentBlt2(*mdc,(int)(-32*ori_p.x)+q1->x*32,(int)(-32*ori_p.y)+q1->y*32,32,32,*mdc1,flag*16,0,16,16,RGB(72,168,16));
			else
				TransparentBlt2(*mdc,(int)(-32*ori_p.x)+q1->x*32,(int)(-32*ori_p.y)+q1->y*32,32,32,*mdc1,flag*16,16,16,16,RGB(72,168,16));
	}
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
}

void monster::AItime()
{
	CClientDC dc(hwnd);
	flag++;	if(flag==3)flag=0;
	flag2++;if(flag2==2)flag2=0;
	flag1++;if(flag1==3)flag1=0;
	dmap();
	dman();
	if		(mtime.move)	{gogogo();}
	//{AImoving();}
//	else if	(mtime.attack)	{}
//	else	{think();}
	dc.BitBlt(0,0,WIDTH,HEIGHT,mdc,0,0,SRCCOPY);
}

void monster::think()
{
	q->selected=true;
	short r=q->movement;
/*	while(1)
	{
		if(AIfindpath(q,r))break;
		else r++;
	}
	if(r==m->movement)mtime.canatt=1;
	else mtime.canatt=0;*/
	mtime.move=1;
	AfxMessageBox("think over");
}

int monster::AIfindpath(HERO *p,short r)
{
	mtime.week=-1;
	mtime.range=p->range;
	if(t!=0)
		deltree(t);
	if((t=(tree *)malloc(sizeof(tree)))==0)return 0;
	t->x=p->x;
	t->y=p->y;
	t->J=p->job;
	t->R=p->movement;
	t->D=i;
	t->f=0;
	for(int j=0;j<4;j++)
		t->c[j]=0;
	find2(t);

	if(mtime.week==-1)return 0;
	else
	{
		howtogo(mtime.x,mtime.y);
		short i=1,dr=mtime.range;
		while(1)
		{
		   if((dr-=eff2[maze[pt[i].y][pt[i].x]*4+p->job])<0)break;
		   i++;
		}
		moves=i;
		return 1;
	}
}

void monster::find2(tree *t)
{
	short tx,ty,dr,D;
	for(int i=0;i<4;i++)
	if((tx=t->x+cd2[D=(t->D+i)%4])<mapwidth-1 && tx>0 &&
	   (ty=t->y+cd2[4+D])<mapheight-1 && ty>0 &&
	   massmon[ty][tx]==100 && isgeneration(tx,ty,t,D) &&
	   (dr=t->R-eff2[maze[ty][tx]*4+t->J])>=0)
	{
		if((t->c[i]=(tree *)malloc(sizeof(tree)))==0)return;
		t->c[i]->x=tx;
		t->c[i]->y=ty;
		t->c[i]->J=t->J;
		t->c[i]->R=dr;
		t->c[i]->D=D;
		t->c[i]->f=t;
		for(int j=0;j<4;j++)
			t->c[i]->c[j]=0;
		att2(t->c[i]);
		find2(t->c[i]);
	}
}

void monster::att2(tree *t)
{
	if(v!=0)delmanpoint(v);
	v=0;
	short r=mtime.range;
	short i,j,x,y;
	for(i=-r;i<=r;i++)
		for(j=-(r-abs(i));j<=r-abs(i);j++)
			if((x=p->x+j)<mapwidth-1 && x>0 &&
			   (y=p->y+i)<mapheight-1 && y>0 &&
						   masshero[y][x]!=100)
			   insertman(x,y,&v);
	if(v==0)return ;
	manpoint *v0;
	short s;
	for(v0=v;v0->n!=v;v0=v0->n)
	{
		s=masshero[v0->y][v0->x];
		if(mtime.week==-1)
		{
			mtime.week=s;
			mtime.x=t->x;
			mtime.y=t->y;
		}
		if(justice(mtime.week)>justice(s))
		{
			mtime.week=s;
			mtime.x=t->x;
			mtime.y=t->y;
		}
	}
}

int monster::justice(int i)
{
	return h[i].P.hp;
}

void monster::AImoving()
{
	if(moves==0)
	{
		q->selected=false;
		q->action=false;
		AfxMessageBox("待机");
		q=q->next;
		if(q=0)endmonturn();
		return;	
	}
	if(mj==0)
	{
		detx=(float)(pt[mi+1].x-pt[mi].x);
		dety=(float)(pt[mi+1].y-pt[mi].y);
		detx/=2;
		dety/=2;
	}
//	mdc1->SelectObject(hero[p->ID]);
	mdc1->SelectObject(mon);
	TransparentBlt2(*mdc,-32*screen.x+(int)(32*(pt[mi].x+mj*detx)),-32*screen.y+(int)(32*(pt[mi].y+mj*dety)),32,32,
		*mdc1,(6+mj+bd2[pt[mi+1].D])*16,0,16,16,RGB(72,168,16));
	mj++;
	if(mj==2)
	{
		mj=0;
		mi++;
		if(mi==moves)
		{
			q->selected=false;
			q->action=false;
			AfxMessageBox("待机");
			q=q->next;
			if(q=0)endmonturn();
		}
	}
}

void monster::endheroturn2()
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
//		monturn();
		q=mhead;
		turntag=2;
}

void monster::endmonturn()
{
	CClientDC dc(hwnd);
	for(q1=mhead;q1!=0;q1=q1->next)
		q1->action=true;
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
	turntag=1;
	p1=hhead;
	cur_backpress(p1);
}

void monster::gogogo()
{
	cur_backpress(q);
	q->action=false;
	q=q->next;
	if(q==0)endmonturn();
}