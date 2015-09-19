#include "game.h"

class gamemap : public game	
{public: gamemap();
 virtual~gamemap();

public:
	int flag,flag1,flag2,menutag;
	int attmenu,itemmenu,lmmenu,dmmenu,up,down,right,left;
	int dx,dy;
	int systemmenu,heromenu,count;
	int hatt,matt,hattr,mattr,hdam,mdam,damall;
	CPoint oldpoint;
	CPoint screen;
	UINT timeIDEvent,keyChar;

	void initmap();
	void dmap();
	void dman();
	void herostatus();
	void herostatus1();
	void heromnu();
	void win();
	void loss();
	void toheromenu();
	void endheroturn();
	void monturn();
	void doheromenu();
	void doattack();
	void dochange();
	void warstart();
	void warhero();
	void warmon();
	void expup();
	void levelup();
	void exchange();
	void war();
	void fin();
};