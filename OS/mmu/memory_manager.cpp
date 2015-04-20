#include "memory_manager.h"
#include "bit_operations.h"

using namespace std;

VMM::VMM() {}

VMM::VMM(int n, PR_Algorithm *algo) {
	if(n < 1)
		n =32;
	num_frames = n;	
	pr_algo = algo;

	/* Initialize virtual page table of size 64*/
	pages = vector<PTE>(64);
	int counter = 0;
	
	frames = vector<unsigned int>();
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

void VMM::mapPagesToFrames(int &operation, int &pageid) {
	/* Get the virtual page */
	PTE& page = pages[pageid];

	int framenumber;
	if (O) {
        cout << "==> inst: " << operation << " " << pageid << endl;
    }

	if(bitop->GET_PRESENT(page)) {// page is already present
		if(operation == 0) {
			bitop->SET_REFERENCED(page);
		} else {
			bitop->SET_REFERENCED(page);
			bitop->SET_MODIFIED(page);
		}
	} else { // page is absent
		if(frames.size() < num_frames) { // free list
			framenumber = frames.size();
			
			page.framenumber = framenumber;
			frames.push_back(framenumber);
			ftop[framenumber] = pageid;
			
			if(O) {
				cout << counter << ": ZERO" << " " << pageid << endl;
				cout << counter << ": MAP"  << " " << pageid << " " << framenumber << endl;
			}
			
			
		} else { // nothing in the free list. Call the algorithm.
			framenumber = pr_algo->getFrame(pages, frames, ftop);
			
			int rev_pageid = ftop[framenumber];
			
			PTE& old_page = pages[rev_pageid];
			
			bitop->UNSET_PRESENT(old_page);

			ftop[framenumber] = pageid;
			//pages[rev_pageid] = old_page;
			
			if(O) {
				cout << counter << ": UNMAP"  << " " << rev_pageid << " " << framenumber << endl;
				cout << counter << ": ZERO" << " " << rev_pageid << endl;
				cout << counter << ": MAP"  << " " << pageid << " " << framenumber << endl;
			}
			
		
		}
		
		bitop->SET_PRESENT(page);
		bitop->SET_REFERENCED(page);
		//pages[pageid] = page;
	} // if present
	counter++;
		
}