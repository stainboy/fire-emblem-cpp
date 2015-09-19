#include "gamepro.h"

typedef struct link
{
	short x,y;		//坐标
	short J;		//职业
	short R;		//剩余步数
	short D;		//方向 0左 1下 2右 3上
	link *c[4];		//3个儿子
	link *f;		//父亲
}tree;

typedef struct
{
	short x,y;		//坐标
	short D;		//方向
}movept;

class find : public gamemap	
{public: find();
 virtual~find();

public:
	tree *t;		//寻路用的树
	tree *s;		//一棵树，返回最短路
	movept pt[10];	//保存最短路的数组
	short moves;	//保存一共走了几格
	short mi,mj;	//走路时需要用到的变量
	float detx,dety;//走路用临时变量
	int Maxnode;
	
	void initfind();
	void findpath(HERO *p);
	void finds(tree *t);
	int isgeneration(int x,int y,tree *t,short D);
	void howtogo(int x,int y);
	void howtogo2(int x,int y,tree *t);
	short parentcount(tree *t);
	void movesto();
	void tomove();
	void deltree(tree *t);
};