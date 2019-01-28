#include "structure.h"

structure planeur()

{
#define a true
#define d false
	structure ret(std::vector<std::vector<bool>>({ { d,a,d },{ a,d,d },{ a,a,a } }));
#undef a
#undef d
	return ret;
}
