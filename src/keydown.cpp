#include "stdafx.h"
#include "keydown.h"

key:: key(){}
key::~key(){}

void key::keydown()
{
	if(turntag==1 && !cur.heromoving)
	{
		if( keyChar== 0x6B || keyChar== 0x4B ) //按键K “选择”
			key_K();
		if( keyChar== 0x6A || keyChar== 0x4A ) //按键J “取消”
			key_J();
		if( keyChar== 0x77 || keyChar== 0x57) // W 上
			key_W();
		if( keyChar== 0x73 || keyChar== 0x53 ) //s 下
			key_S();
		if( keyChar== 0x64 || keyChar== 0x44 )  //D 右
			key_D();
		if( keyChar== 0x61 || keyChar== 0x41 ) //左 A
			key_A();
	}
}

void key::key_K()
{
	if(cur.heroselect)
	{
		if(masshero[cur.y][cur.x]==100 || masshero[cur.y][cur.x]==p->ID)
		{
			oldpoint.x=p->x;
			oldpoint.y=p->y;
			if(masshero[cur.y][cur.x]!=p->ID)
			{
				masshero[cur.y][cur.x]=p->ID;
				masshero[p->y][p->x]=100;
			}
			cur.heroselect=false;
			howtogo(cur.x,cur.y);

			p->x=cur.x;
			p->y=cur.y;
			domenu();
			cur.heromoving=true;
		}
	}
	else if(cur.voidmenu)
		switch(systemmenu)
		{
			case 0:break;
			case 1:break;
			case 2:break;
			case 3:break;
			case 4:break;
			case 5:break;
			case 6:endheroturn2();cur.voidmenu=false;break;
		}
	else if(cur.heromenu)
		dohmenu();
	else if(cur.selectmon)
	{
		q=&m[massmon[cur.y][cur.x]];
		cur.x=p->x;cur.y=p->y;
		cur.selectmon=false;
		p->selected=false;
		p->action=false;
		war();	
		p=0;
		q=0;
	}
	else if(cur.selectfriend)
	{
				int tempitem;
				tempitem=p->item;
				p->item=h[masshero[cur.y][cur.x]].item;
				h[masshero[cur.y][cur.x]].item=tempitem;
				cur.x=p->x;cur.y=p->y;
				cur.selectfriend=false;
				p->selected=false;
				p->action=false;
				exchange();
	}
	else if(cur.status)
	{
			cur.status1=true;
			cur.status=false;
			if(q)
			if(q->selected)
				q->selected=false;
	}
	else if(cur.status1)
	{
			cur.status1=false;
			if(q)q=0;
			if(p)
			if(p->action)
			{
				cur.heroselect=true;
				tomove();
			}
			else p=0;
	}
	else
	{
			if(masshero[cur.y][cur.x]!=100)
				if(h[masshero[cur.y][cur.x]].action)
				{
					p=&h[masshero[cur.y][cur.x]];
					p->selected=true;
					cur.status=true;
				}
				else
				{
					p=&h[masshero[cur.y][cur.x]];
					cur.status=true;
				}
			else if(massmon[cur.y][cur.x]!=100)
			{
				q=&m[massmon[cur.y][cur.x]];
				q->selected=true;
				cur.status=true;
			}
			else
			{
				cur.voidmenu=true;
				systemmenu=0;
			}
	}
}

void key::key_J()
{
	if(cur.selectmon)
	{
				cur.selectmon=false;
				cur.heromenu=true;
				cur.x=p->x;cur.y=p->y;
	}
	else if(cur.selectfriend)
	{
				cur.selectfriend=false;
				cur.heromenu=true;
				cur.x=p->x;cur.y=p->y;
	}
	else if(cur.heromenu)
	{
				cur.heromenu=false;
				masshero[cur.y][cur.x]=100;
				p->x=oldpoint.x;p->y=oldpoint.y;
				cur.x=oldpoint.x;cur.y=oldpoint.y;
				masshero[p->y][p->x]=p->ID;
				dx=0;dy=0;
				cur.heroselect=true;
	}
	else if(cur.voidmenu)
				cur.voidmenu=false;
	else if(cur.heroselect)
	{
				p->selected=false;
				cur.heroselect =false;
				cur.x=p->x;cur.y=p->y;
				p=0;
//				deltree();
	}
	else if(cur.status)
	{
				cur.status=false;
				if(p)
				if(p->selected)
					{p->selected=false;p=0;}
				else p=0;
				if(q)
				if(q->selected)
					{q->selected=false;q=0;}
	}
	else if(cur.status1)
	{
				cur.status1=false;
				if(q)q=0;
				if(p)
				if(p->action)
				{
					cur.heroselect=true;
					tomove();
				}
				else p=0;
	}
	else
	{
		if(masshero[cur.y][cur.x]==100)
		{
			for(p1=hhead;p1!=0;p1=p1->next)
				if(p1->action)
				{cur_backpress(p1);break;}
		}
		else
		{
			p1=h+masshero[cur.y][cur.x];
			p1=p1->next;
			for(;p1!=0;p1=p1->next)
			{
				if(p1->action)
				{cur_backpress(p1);return;}
			}
			if(p1==0)
			for(p1=hhead;p1!=0;p1=p1->next)
				if(p1->action)
				{cur_backpress(p1);break;}
		}
	}
}
void key::key_W()
{
	if(cur.heroselect)
	{
		if(pass[cur.y-1][cur.x] && cur.y-1>=0)
			{cur.y--;dy--;}
		if(cur.y-2 == screen.y && screen.y != 0)
			screen.y--;
	}
	else if(cur.voidmenu)
	{
		if(systemmenu!=0)systemmenu--;
		else systemmenu=6;
	}
	else if(cur.heromenu)
	{
		mc=mc->p;
	}
	else if(cur.selectmon)
	{
		v=v->p;
	}
	else if(cur.selectfriend)
	{
		it=it->p;
	}
	else if(cur.status)
	{
				cur.status=false;
				if(q)
				if(q->selected)
					{q->selected=false;q=0;}
				if(p)
				if(p->action)
				{
					cur.heroselect=true;
					tomove();
				}
				else
					p=0;
	}
	else if(cur.status1)
	{
				cur.status1=false;
				if(q)q=0;
				if(p)
				if(p->action)
				{
					cur.heroselect=true;
					tomove();
				}
				else
					p=0;
	}
	else
	{
		if(cur.y>=1)cur.y--;
		if(cur.y-2 == screen.y && screen.y != 0)
			screen.y--;
	}
}
void key::key_S()
{
	if(cur.heroselect)
	{
		if(pass[cur.y+1][cur.x] && cur.y+1<=mapheight-1)
			{cur.y++;dy++;}
		if(cur.y+2 == screen.y+14 && screen.y != mapheight-15)
			screen.y++;
	}
	else if(cur.voidmenu)
	{
		if(systemmenu!=0)systemmenu--;
		else systemmenu=6;
	}
	else if(cur.heromenu)
	{
		mc=mc->n;
	}
	else if(cur.selectmon)
	{
		v=v->n;
	}
	else if(cur.selectfriend)
	{
		it=it->n;
	}
	else if(cur.status)
	{
				cur.status=false;
				if(q)
				if(q->selected)
					{q->selected=false;q=0;}
				if(p)
				if(p->action)
				{
					cur.heroselect=true;
					tomove();
				}
				else
					p=0;
	}
	else if(cur.status1)
	{
				cur.status1=false;
				if(q)q=0;
				if(p)
				if(p->action)
				{
					cur.heroselect=true;
					tomove();
				}
				else
					p=0;
	}
	else
	{
		if(cur.y<mapheight-1)cur.y++;
		if(cur.y+2 == screen.y+14 && screen.y != mapheight-15)
			screen.y++;
	}
}
void key::key_A()
{
	if(cur.heroselect)
	{
		if(pass[cur.y][cur.x-1] && cur.x-1>=0)
			{cur.x--;dx--;}
		if(cur.x-2 == screen.x && screen.x != 0)
			screen.x--;
	}
	else if(cur.selectmon)
	{
		v=v->p;
	}
	else if(cur.selectfriend)
	{
		it=it->p;
	}
	else if(cur.voidmenu){}
	else if(cur.heromenu){}
	else if(cur.status)
	{
				cur.status=false;
				if(q)
				if(q->selected)
					{q->selected=false;q=0;}
				if(p)
				if(p->action)
				{
					cur.heroselect=true;
					tomove();
				}
				else
					p=0;
	}
	else if(cur.status1)
	{
				cur.status1=false;
				if(q)
				if(q->selected)
					{q->selected=false;q=0;}
				if(p)
				if(p->action)
				{
					cur.heroselect=true;
					tomove();
				}
				else
					p=0;
	}
	else
	{
		if(cur.x>0)cur.x--;
		if(cur.x-2 == screen.x && screen.x != 0)
			screen.x--;
	}
}
void key::key_D()
{
	if(cur.heroselect)
	{
		if(pass[cur.y][cur.x+1] && cur.x+1<=mapwidth-1)
			{cur.x++;dx++;}
		if(cur.x+2 == screen.x+15 && screen.x != mapwidth-16)
			screen.x++;
	}
	else if(cur.voidmenu){}
	else if(cur.heromenu){}
	else if(cur.selectmon)
	{
		v=v->n;
	}
	else if(cur.selectfriend)
	{
	//	if(right){cur.x=p->x+1;cur.y=p->y;}
		it=it->n;
	}
	else if(cur.status)
	{
				cur.status=false;
				if(q)
				if(q->selected)
					{q->selected=false;q=0;}
				if(p)
				if(p->action)
				{
					cur.heroselect=true;
					tomove();
				}
				else
					p=0;
	}
	else if(cur.status1)
	{
				cur.status1=false;
				if(q)q=0;
				if(p)
				if(p->action)
				{
					cur.heroselect=true;
					tomove();
				}
				else
					p=0;
	}
	else
	{
		if(cur.x<mapwidth-1)cur.x++;
		if(cur.x+2 == screen.x+15 && screen.x != mapwidth-16)
			screen.x++;
	}
}