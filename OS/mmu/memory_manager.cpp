#include "memory_manager.h"
#include "bit_operations.h"

using namespace std;

VMM::VMM() {}

VMM::VMM(int n) {
	if(n < 1)
		n =32;
	num_frames = n;	

	/* Initialize virtual page table of size 64*/
	pages = vector<PTE>(64);
	frames = vector<unsigned int>(num_frames, -1);
	ftop = vector<unsigned int>(num_frames);
	
	bool O = P = F = S = false;
	bitop = new BitOP();
}

void VMM::setOptions(char* optarg) {
	int len = strlen(optarg);
	for(int i =0; i < len; i++) {
		if(optarg[i] == 'O') O = true;
		if(optarg[i] == 'P') P = true;
		if(optarg[i] == 'F') F = true;
		if(optarg[i] == 'S') S = true;
	}
}

void VMM::mapPagesToFrames(int &operation, int &page) {
	if (O) {
        cout << "==> inst: " << operation << " " << page << endl;
    }

	cout << bitop->GET_REFERENCED(pages[0]);
	bitop->SET_REFERENCED(pages[0]);
	cout << bitop->GET_REFERENCED(pages[0]);

}