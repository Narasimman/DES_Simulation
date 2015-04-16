#ifndef __BIT_OP__
#define __BIT_OP__

#include "PTE.h"

using namespace std;

class BitOP {
	public:
		void SET_REFERENCED(PTE&);
		void UNSET_REFERENCED(PTE&);
		unsigned int GET_REFERENCED(PTE&);
		
		void SET_MODIFIED(PTE&);
		void UNSET_MODIFIED(PTE&);
		unsigned int GET_MODIFIED(PTE&);
		
		void SET_PRESENT(PTE&);
		void UNSET_PRESENT(PTE&);
		unsigned int GET_PRESENT(PTE&);
		
		void SET_PAGEDOUT(PTE&);
		void UNSET_PAGEDOUT(PTE&);
		unsigned int GET_PAGEDOUT(PTE&);
		
};

#endif