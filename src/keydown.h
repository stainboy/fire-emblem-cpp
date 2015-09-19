#include "Ontimer.h"

class key : public time	
{public: key();
 virtual~key();

public:
	void keydown();
	void key_K();//ok
	void key_J();//cancel
	void key_W();//up
	void key_S();//down
	void key_A();//left
	void key_D();//right

};