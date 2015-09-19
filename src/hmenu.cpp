#include "stdafx.h"
#include "hmenu.h"

menu:: menu(){}
menu::~menu()
{
	if(mn!=0)delmenutype(mn);
	if(it!=0)delmanpoint(it);
	if(v!=0)delmanpoint(v);
}

CString cs[5]={"攻击","黑魔法","白魔法","物品","待机"};
short cd1[8]={-1,0,1,0,0,1,0,-1};
short bd1[4]={4,2,6,0};

void menu::initmenu()
{
	mn=0;
	v=0;
	it=0;
}

void menu::domenu()
{
	if(mn!=0)delmenutype(mn);
	mn=0;
	if(att(p))		insertmenu(0);
	if(bmagic(p))	insertmenu(1);
	if(wmagic(p))	insertmenu(2);
	if(exitem(p))	insertmenu(3);
					insertmenu(4);
	mc=mn;
}

void menu::insertmenu(short i)
{
	if(mn==0)
	{
		if((mn=(menutype *)malloc(sizeof(menutype)))==0)return;
		mn->menu=i;
		mn->i=0;
		mn->n=mn;
		mn->p=mn;
	}
	else
	{
		menutype *s;
		if((s=(menutype *)malloc(sizeof(menutype)))==0)return;
		s->menu=i;
		s->i=mn->p->i+1;
		s->n=mn;
		s->p=mn->p;
		mn->p->n=s;
		mn->p=s;
	}
}

void menu::insertman(short x,short y,manpoint **v)
{
	if((*v)==0)
	{
		if(((*v)=(manpoint *)malloc(sizeof(manpoint)))==0)return;
		(*v)->x=x;
		(*v)->y=y;
		(*v)->n=(*v);
		(*v)->p=(*v);
	}
	else
	{
		manpoint *s;
		if((s=(manpoint *)malloc(sizeof(manpoint)))==0)return;
		s->x=x;
		s->y=y;
		s->n=(*v);
		s->p=(*v)->p;
		(*v)->p->n=s;
		(*v)->p=s;
	}
}

int menu::att(HERO *p)
{
	if(v!=0)delmanpoint(v);
	v=0;
	short r=p->range;
	short i,j,x,y;
	for(i=-r;i<=r;i++)
		for(j=-(r-abs(i));j<=r-abs(i);j++)
			if((x=p->x+j)<mapwidth-1 && x>0 &&
			   (y=p->y+i)<mapheight-1 && y>0 &&
						   massmon[y][x]!=100)
			   insertman(x,y,&v);
	if(v==0)return 0;
	else return 1;
}

int menu::wmagic(HERO *p)
{
	return 0;
}

int menu::bmagic(HERO *p)
{
	return 0;
}

int menu::exitem(HERO *p)
{
	if(it!=0)delmanpoint(it);
	it=0;
	short x,y,i,j;
	for(j=0;j<4;j++)
		if(p->item!=0)
		{
			if((x=p->x+cd1[j])<mapwidth-1 && x>0 &&
			   (y=p->y+cd1[4+j])<mapheight-1 && y>0 &&
				(i=masshero[y][x])!=100				)
				insertman(x,y,&it);
		}
		else
		{
			if((x=p->x+cd1[j])<mapwidth-1 && x>0 &&
			   (y=p->y+cd1[4+j])<mapheight-1 && y>0 &&
				(i=masshero[y][x])!=100 && h[i].item!=0)
				insertman(x,y,&it);
		}
	if(it==0)return 0;
	else return 1;
}

void menu::bitmenu()
{
	short t=1,tag=1;
	SetBkMode(*mdc,TRANSPARENT);	
	SetTextColor(*mdc,RGB(255,255,255));
	mdc1->SelectObject(herobmp);
	if(p->x<=7){t=9;}
	mdc->BitBlt(t*32,32,160,32,mdc1,0,0,SRCCOPY);

	menutype *s;
	s=mn;
	while(s->menu!=4)
	{
		mdc->BitBlt(t*32,32+32*tag,160,32,mdc1,0,16,SRCCOPY);
		mdc->TextOut(t*32+40,32+32*tag-4,cs[s->menu]);
		tag++;
		s=s->n;
	}
	mdc->BitBlt(t*32,32+32*tag,160,32,mdc1,0,32,SRCCOPY);
	mdc->TextOut(t*32+40,32+32*tag-4,cs[s->menu]);
	mdc1->SelectObject(triangle);
	mdc->BitBlt(t*32+16,32*(mc->i+2),14,14,mdc1,0,0,SRCCOPY);
}

void menu::dohmenu()
{
	switch(mc->menu)
	{
		case 0: cur.selectmon=true;cur.heromenu=false;doattack();break;
		case 1: break;
		case 2: break;
		case 3: cur.selectfriend=true;cur.heromenu=false;dochange();break;
		case 4: p->action=false;p->selected=false;cur.heromenu=false;break;
	}
}

void menu::delmenutype(menutype *h)
{
	menutype *s;
	while(h->p!=h)
	{
		s=h->p;
		h->p=s->p;
		free(s);
	}
	free(h);
}

void menu::delmanpoint(manpoint *h)
{
	manpoint *s;
	while(h->p!=h)
	{
		s=h->p;
		h->p=s->p;
		free(s);
	}
	free(h);
}

void menu::selectmenu()
{
	if(p->selected && flag1)
	{
		mdc1->SelectObject(hero[p->ID]);
		TransparentBlt2(*mdc,-32*screen.x+p->x*32,-32*screen.y+p->y*32,32,32,*mdc1,(6+flag2%2+bd1[pt[mi].D])*16,0,16,16,RGB(72,168,16));
	}
	dman();
	if(flag1)
	{
		if(cur.selectfriend){cur.x=it->x;cur.y=it->y;}
		if(cur.selectmon){cur.x=v->x;cur.y=v->y;}
		mdc1->SelectObject(curp);
		TransparentBlt2(*mdc,-32*screen.x+cur.x*32,-32*screen.y+cur.y*32,32,32,*mdc1,32,0,16,16,RGB(0,0,0));
	}
}
