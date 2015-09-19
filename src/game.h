#define WIDTH 512
#define HEIGHT 480

struct Property
{
	int level,exp;
	int hp,hpmax,str,dex,speed,luck,def,mdef;
	int hpup,strup,dexup,speedup,luckup,defup,mdefup;
	int magic0,magic1,magic2,magic3,magic4,magic5;
};
struct HERO
{
	int x,y;
	int ID;
	int job;
	char name[15];
	int movement;
	int range;
	int item;
	BOOL action;
	BOOL selected;
//	HERO *next,*nextunit,*preunit;
	HERO *next;
	Property P;
};
struct CUR
{
	int x;
	int y;
	BOOL voidmenu,heromenu,heroselect,heromoving,selectmon,selectfriend;
	BOOL status,status1;
};

class game
{public: game();
 virtual~game();
public:
	CWnd *hwnd;
	HWND hMCI;
	CDC *mdc,*mdc1,*map;
	CBitmap *temp,*bmpmap;
	CBitmap *b[9];
	CBitmap *hero[5],*job[11],*mon,*herobmp;
	CBitmap *curp,*systembmp,*triangle;
	CBitmap *turn,*heropic,*warbground,*warstatus,*blood,
		*warmessage,*lvup;
	CFont font;

	CString cc;
	int i,j,n,n1;
	int maze[50][50],masshero[50][50],massmon[50][50],pass[50][50],ground[50][50];
	int mapheight,mapwidth;
	HERO h[20],m[20];
	HERO *p,*p1,*q,*q1,*hhead,*mhead;
	CUR cur;

	void init();
	void exit();
	void zone();
	void upHERO(int num);
	void toHERO(HERO *h,HERO *_h,int num);
	void toCUR(CUR _cur);
	void link(HERO **head,HERO *p,int n);
	CString JOB(int i);
	void del(HERO **head,HERO *p);
	void TransparentBlt2( HDC hdc0,	
						int nX0,int nY0,
						int nW0,int nH0,
						  HDC hdc1,
						int nX1,int nY1,
						int nW1,int nH1,
						  UINT Tcol);
};