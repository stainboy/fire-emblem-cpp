#include "hmenu.h"

typedef struct
{
	float x,y;
}fpoint;

typedef struct
{
	short x,y;
	short move;
	short attack;
	short canatt;
	short week;
	short range;
	short time;
}monstertime;

class monster : public menu	
{public: monster();
 virtual~monster();

public:
	int turntag;			//控制第几个计时器的tag(1-人，2-AI，3-光标)
	int turn1;				//之前的turn
	fpoint tar_p,ori_p;		//目标点，原始点
	monstertime mtime;

	void initAI();
	void cur_backpress(HERO *p);
	void cur_backbit();
	void AItime();
	void think();
	int AIfindpath(HERO *m,short r);
	void find2(tree *t);
	void att2(tree *t);
	int justice(int i);
	void AImoving();
	void endheroturn2();
	void endmonturn();
	void gogogo();

};