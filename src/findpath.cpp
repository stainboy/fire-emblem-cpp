#include "stdafx.h"
#include "findpath.h"

find:: find(){}	
find::~find()
{
	if(t!=0)deltree(t);
}	

short cd[8]={-1,0,1,0,0,1,0,-1};
short bd[4]={4,2,6,0};
short eff[36]={	1,	1,	1,	1,
				10,	10,	10,	10,
				2,	2,	2,	2,
				1,	1,	1,	1,
				1,	1,	1,	1,
				10,	10,	10,	10,
				1,	1,	1,	1,
				1,	1,	1,	1,
				1,	1,	1,	1};//9*4

void find::initfind()
{
	t=0;
	Maxnode=0;
}

void find::findpath(HERO *p)
{
	Maxnode=0;
	if(t!=0)deltree(t);
	pass[p->y][p->x]=1;
	if((t=(tree *)malloc(sizeof(tree)))==0)return;
	t->x=p->x;
	t->y=p->y;
	t->J=p->job;
	t->R=p->movement;
	t->D=i;
	t->f=0;
	for(int j=0;j<4;j++)
		t->c[j]=0;
	finds(t);
//	CString cc;
//	cc.Format("%d",Maxnode);
//	AfxMessageBox(cc);
}

void find::finds(tree *t)
{
	short tx,ty,dr,D;
	for(int i=0;i<4;i++)
	if((tx=t->x+cd[D=(t->D+i)%4])<mapwidth-1 && tx>0 &&
	   (ty=t->y+cd[4+D])<mapheight-1 && ty>0 &&
	   massmon[ty][tx]==100 && isgeneration(tx,ty,t,D) &&
	   (dr=t->R-eff[maze[ty][tx]*4+t->J])>=0)
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
		pass[ty][tx]=1;
		Maxnode++;
		finds(t->c[i]);
	}
}

void find::howtogo(int x,int y)
{
	s=0;
	howtogo2(x,y,t);
	moves=parentcount(s)>10?10:parentcount(s);
	for(int i=moves;s!=0;s=s->f,i--)
	{
		pt[i].x=s->x;
		pt[i].y=s->y;
		pt[i].D=s->D;
	}
	pt[0].x=t->x;
	pt[0].y=t->y;
//------------------------------------------------
	mi=0;
	mj=0;
//------------------------------------------------
}

void find::howtogo2(int x,int y,tree *t)
{
	if(t==0)return;
	if(t->x==x && t->y==y)
	{
		if(s==0)s=t;
		s=parentcount(s)>parentcount(t)?t:s;
		return;
	}
	for(int i=0;i<4;i++)
		if(t->c[i]!=0)howtogo2(x,y,t->c[i]);
}

short find::parentcount(tree *t)
{
	short i=0;
	for(i=0;t!=0;t=t->f,i++);
	return i-1;
}

void find::movesto()
{
	if(moves==0)
	{
		cur.heromoving=false;
		cur.heromenu=true;
		return;	
	}
	if(mj==0)
	{
		detx=(float)(pt[mi+1].x-pt[mi].x);
		dety=(float)(pt[mi+1].y-pt[mi].y);
		detx/=3;
		dety/=3;
	}
	mdc1->SelectObject(hero[p->ID]);
	TransparentBlt2(*mdc,-32*screen.x+(int)(32*(pt[mi].x+mj*detx)),-32*screen.y+(int)(32*(pt[mi].y+mj*dety)),32,32,
		*mdc1,(6+mj%2+bd[pt[mi+1].D])*16,0,16,16,RGB(72,168,16));
	mj++;
	if(mj==3)
	{
		mj=0;
		mi++;
		if(mi==moves)
		{
			cur.heromoving=false;
			cur.heromenu=true;
		}
	}
}

void find::tomove()
{
	dx=0;dy=0;
	for(int i=0;i<mapheight;i++)
		for(int j=0;j<mapwidth;j++)
			pass[i][j]=0;
	findpath(p);
}

void find::deltree(tree *t)
{
	if(t==0) return;
	for(int i=0;i<4;i++)
		if(t->c[i]!=0)deltree(t->c[i]);
	free(t);
}

int find::isgeneration(int x,int y,tree *t,short D)
{
	tree *s;
	s=t->f;
	while(s!=0)
	{
		if(s->x==x && s->y==y)return 0;
		s=s->f;
	}
	for(int i=-1;i<=1;i++)
	{
		s=t->f;
		while(s!=0)
		{
			if(s->x==x+cd[(D+i+4)%4] && s->y==y+cd[4+(D+i+4)%4])return 0;
			s=s->f;
		}
	}
	return 1;
}

