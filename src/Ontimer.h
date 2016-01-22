#include "AI.h"

class time : public monster	
{public: time();
 virtual~time();

public:
	void timer(UINT n);
	void cur_normal();
	void cur_heromenu();
	void cur_voidmenu();
	void cur_status();
	void cur_status1();
	void cur_else();
};