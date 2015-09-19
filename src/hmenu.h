#include "findpath.h"

typedef struct link1
{
	short menu;	//0~4
	short i;	//计数
	link1 *p;	//前结点
	link1 *n;	//后结点
}menutype;

typedef struct link2
{
	short x,y;	//坐标
	link2 *p;	//前结点
	link2 *n;	//后结点
}manpoint;

class menu : public find	
{public: menu();
 virtual~menu();

public:
	menutype *mn,*mc;
	manpoint *v,*it;

	void initmenu();
	void domenu();
	void insertmenu(short i);
	void insertman(short x,short y,manpoint **v);
	void bitmenu();
	void dohmenu();
	void selectmenu();
	void delmenutype(menutype *h);
	void delmanpoint(manpoint *h);
	int att(HERO *p);
	int wmagic(HERO *p);
	int bmagic(HERO *p);
	int exitem(HERO *p);
};