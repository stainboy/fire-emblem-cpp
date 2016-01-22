#include "stdafx.h"
#include "game.h"

game:: game(){}	
game::~game(){exit();}	

void game::init()
{
	CClientDC dc(hwnd);
	mdc = new CDC;
	mdc1 = new CDC;
	map = new CDC;
	mdc->CreateCompatibleDC(&dc);
	mdc1->CreateCompatibleDC(&dc);
	map->CreateCompatibleDC(&dc);
	temp = new CBitmap;
	temp->CreateCompatibleBitmap(&dc,WIDTH,HEIGHT);
	bmpmap = new CBitmap;
	bmpmap->CreateCompatibleBitmap(&dc,1600,1600);
	mdc->SelectObject(temp);
	map->SelectObject(bmpmap);
	for(i=0;i<=9-1;i++)
	{
		char cc[20];
		sprintf(cc,"res/b%d.bmp",i);
		b[i] = new CBitmap;
		b[i]->m_hObject=(HBITMAP)LoadImage(NULL,cc,IMAGE_BITMAP,32,32,LR_LOADFROMFILE);
	}
	for(i=0;i<=5-1;i++)
	{
		char cc[20];
		sprintf(cc,"res/hero%d.bmp",i);
		hero[i] = new CBitmap;
		hero[i]->m_hObject=(HBITMAP)LoadImage(NULL,cc,IMAGE_BITMAP,224,16,LR_LOADFROMFILE);
	}
	for(i=0;i<=11-1;i++)
	{
		char cc[20];
		sprintf(cc,"res/job%d.bmp",i);
		job[i] = new CBitmap;
		job[i]->m_hObject = (HBITMAP)LoadImage(NULL, cc ,IMAGE_BITMAP,38*2,32*2,LR_LOADFROMFILE); 
	}
	mon = new CBitmap;
	mon->m_hObject=(HBITMAP)LoadImage(NULL,"res/mon.bmp",IMAGE_BITMAP,48,32,LR_LOADFROMFILE);
	curp = new CBitmap;
	curp->m_hObject=(HBITMAP)LoadImage(NULL,"res/cur.bmp",IMAGE_BITMAP,48,16,LR_LOADFROMFILE);
	systembmp = new CBitmap;
	systembmp->m_hObject=(HBITMAP)LoadImage(NULL,"res/systemmenu.bmp",IMAGE_BITMAP,192,256,LR_LOADFROMFILE);
	triangle = new CBitmap;
	triangle->m_hObject=(HBITMAP)LoadImage(NULL,"res/triangle.bmp",IMAGE_BITMAP,14,14,LR_LOADFROMFILE);
	herobmp = new CBitmap;
	herobmp->m_hObject = (HBITMAP)LoadImage(NULL,"res/heromenu.bmp",IMAGE_BITMAP,160,64,LR_LOADFROMFILE);
	turn = new CBitmap;
	turn->m_hObject = (HBITMAP)LoadImage(NULL,"res/turn.bmp",IMAGE_BITMAP,192,64,LR_LOADFROMFILE);
	heropic = new CBitmap;
	heropic->m_hObject = (HBITMAP)LoadImage(NULL,"res/heropic.bmp",IMAGE_BITMAP,96*5,96,LR_LOADFROMFILE);
	warbground = new CBitmap;
	warbground->m_hObject = (HBITMAP)LoadImage(NULL,"res/warbground.bmp",IMAGE_BITMAP,256*2,256*2,LR_LOADFROMFILE); 
	warstatus = new CBitmap;
	warstatus->m_hObject = (HBITMAP)LoadImage(NULL,"res/warstatus~.bmp",IMAGE_BITMAP,238*2,96*2,LR_LOADFROMFILE); 
	blood = new CBitmap;
	blood->m_hObject = (HBITMAP)LoadImage(NULL,"res/blood.bmp",IMAGE_BITMAP,14*2,7*2,LR_LOADFROMFILE); 
	warmessage = new CBitmap;
	warmessage->m_hObject = (HBITMAP)LoadImage(NULL,"res/message.bmp",IMAGE_BITMAP,223*2,30*2,LR_LOADFROMFILE); 
	lvup = new CBitmap;
	lvup->m_hObject = (HBITMAP)LoadImage(NULL,"res/lvup.bmp",IMAGE_BITMAP,150*2,94*2,LR_LOADFROMFILE); 

	font.CreateFont(
	   25,                        // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_BOLD,                   // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   ANSI_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	   "Arial Bold");                  // lpszFacename
	mdc->SelectObject(&font);
}
void game::exit()
{
	MCIWndClose(hMCI);
	delete hMCI;
	delete mdc,mdc1,map;
	delete temp,bmpmap,curp,systembmp,triangle,herobmp,warbground,
		heropic,turn,warstatus,blood,warmessage,lvup;
	for(i=0;i<=9-1;i++)delete b[i];
	for(i=0;i<=5-1;i++)delete hero[i];
	for(i=0;i<=11-1;i++)delete job[i];
}
void game::TransparentBlt2( HDC hdc0,	
					int nX0,int nY0,
					int nW0,int nH0,
				      HDC hdc1,
					int nX1,int nY1,
					int nW1,int nH1,
				      UINT Tcol)
{	
	HBITMAP hBMP  =CreateCompatibleBitmap(hdc0,nW0, nH0);
	HBITMAP mBMP  =CreateBitmap(nW0,nH0,1,1,NULL);	
	HDC	hDC   =CreateCompatibleDC(hdc0);
	HDC	mDC   =CreateCompatibleDC(hdc0);
	HBITMAP oldBMP =(HBITMAP)SelectObject(hDC, hBMP);
	HBITMAP oldmBMP=(HBITMAP)SelectObject(mDC, mBMP);
	if (nW0==nW1&&nH0==nH1)
		BitBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,SRCCOPY);
	else
		StretchBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,nW1,nH1,SRCCOPY);

	SetBkColor(hDC, Tcol);
	BitBlt(mDC,0,0,nW0,nH0,hDC,0,0,SRCCOPY);
	SetBkColor(hDC, RGB(0,0,0));
	SetTextColor(hDC, RGB(255,255,255));
	BitBlt(hDC,0,0,nW0,nH0,mDC,0,0,SRCAND);
	SetBkColor(hdc0,RGB(255,255,255));
	SetTextColor(hdc0,RGB(0,0,0));

	BitBlt(hdc0,nX0,nY0,nW0,nH0,mDC,0,0,SRCAND);
	BitBlt(hdc0,nX0,nY0,nW0,nH0,hDC,0,0,SRCPAINT);

	SelectObject(hDC, oldBMP);				
	DeleteDC(hDC);
	SelectObject(mDC, oldmBMP);
	DeleteDC(mDC);
	DeleteObject(hBMP);
	DeleteObject(mBMP);
}
void game::del(HERO **head,HERO *p)//指向head的指针,用于改变head的地址
{
	HERO *s;
	if(*head==p)
	{
		if((*head)->next!=0)
			{*head=(*head)->next;return;}
		else
			{*head=0;return;}
	}
	else
	{
	for(s=*head;s!=0;s=s->next)
		if(s->next==p)break;
	s->next=s->next->next;
	return;
	}
}
CString game::JOB(int i)
{
	switch(i)
	{
		case 0:return "村人";break;
		case 1:return "海盗";break;
		case 2:return "枪兵";break;
		case 3:return "战士";break;
		default : return "";
	}
}
void game::toHERO(HERO *h,HERO *_h,int num)
{
	for(i=0;i<=num-1;i++)
	{
		h[i].x			=_h[i].x;
		h[i].y			=_h[i].y;
		h[i].ID			=_h[i].ID;
		h[i].job		=_h[i].job;
		strcpy(h[i].name,_h[i].name);
		h[i].movement	=_h[i].movement;
		h[i].range		=_h[i].range;
		h[i].item		=_h[i].item;
		h[i].action		=_h[i].action;
		h[i].selected	=_h[i].selected;
		h[i].P.level	=_h[i].P.level;
		h[i].P.exp		=_h[i].P.exp;
		h[i].P.hp		=_h[i].P.hp;
		h[i].P.hpmax	=_h[i].P.hpmax;
		h[i].P.str		=_h[i].P.str;
		h[i].P.dex		=_h[i].P.dex;
		h[i].P.speed	=_h[i].P.speed;
		h[i].P.luck		=_h[i].P.luck;
		h[i].P.def		=_h[i].P.def;
		h[i].P.mdef		=_h[i].P.mdef;
		h[i].P.hpup		=_h[i].P.hpup;
		h[i].P.strup	=_h[i].P.strup;
		h[i].P.dexup	=_h[i].P.dexup;
		h[i].P.speedup	=_h[i].P.speedup;
		h[i].P.luckup	=_h[i].P.luckup;
		h[i].P.defup	=_h[i].P.defup;
		h[i].P.mdefup	=_h[i].P.mdefup;
		h[i].P.magic0	=_h[i].P.magic0;
		h[i].P.magic1	=_h[i].P.magic1;
		h[i].P.magic2	=_h[i].P.magic2;
		h[i].P.magic3	=_h[i].P.magic3;
		h[i].P.magic4	=_h[i].P.magic4;
		h[i].P.magic5	=_h[i].P.magic5;
	}
}
void game::toCUR(CUR _cur)
{
	cur.x			=_cur.x;
	cur.y			=_cur.y;
	cur.voidmenu	=_cur.voidmenu;
	cur.heromenu	=_cur.heromenu;
	cur.heroselect	=_cur.heroselect;
	cur.heromoving	=_cur.heromoving;
	cur.selectmon	=_cur.selectmon;
	cur.selectfriend=_cur.selectfriend;
	cur.status		=_cur.status;
	cur.status1		=_cur.status1;
}
void game::link(HERO **head,HERO *p,int n)
{
	*head=p;
	for(int i=0;i<n;i++)
		(p+i)->next=(p+i+1);
	(p+n-1)->next=0;
}
void game::zone()
{
	for(i=0;i<=mapheight-1;i++)
		for(j=0;j<=mapwidth-1;j++)
		{
			masshero[i][j]=100;
			massmon[i][j]=100;
			switch(maze[i][j])
			{
				case 0: ground[i][j]=0;break;
				case 1: ground[i][j]=0;break;
				case 2: ground[i][j]=40;break;
				case 3: ground[i][j]=40;break;
				case 4: ground[i][j]=0;break;
				case 5: ground[i][j]=0;break;
				case 6: ground[i][j]=0;break;
				case 7: ground[i][j]=0;break;
				case 8: ground[i][j]=0;break;
			}
		}
}
void game::upHERO(int num)
{
	for(i=0;i<=num-1;i++)
	{
		h[i].P.hp=h[i].P.hpmax;
		h[i].action=true;
		h[i].selected=false;
		h[i].P.exp+=25;
		if(h[i].P.exp>99)h[i].P.exp=99;
	}
}
