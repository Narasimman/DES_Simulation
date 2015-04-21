#include "memory_manager.h"
#include "bit_operations.h"
#include <iomanip>

using namespace std;

MMU::MMU() {}

MMU::MMU(int n, PR_Algorithm *algo) {
	if(n < 1)
		n =32;
	num_frames = n;	
	pr_algo = algo;

	/* Initialize virtual page table of size 64*/
	pages = vector<PTE>(64);
	counter = 0;
	
	frames = vector<unsigned int>();
	ftop = vector<unsigned int>(num_frames, -1);
	
	O = P = F = S = false;
	map_counter = unmap_counter = zero_counter = in_counter = out_counter = 0;
	bitop = new BitOP();
}

void MMU::setOptions(char* optarg) {
	int len = strlen(optarg);
	for(int i =0; i < len; i++) {
		if(optarg[i] == 'O') O = true;
		if(optarg[i] == 'P') P = true;
		if(optarg[i] == 'F') F = true;
		if(optarg[i] == 'S') S = true;
	}
}

void MMU::printOptions() {
	if (P) {
        for (int i = 0; i < pages.size(); i++) {
            if (bitop->GET_PRESENT(pages[i]) == 1) {
                cout << i << ": ";
                (bitop->GET_REFERENCED(pages[i]) == 1)? cout << "R" : cout << "-";
                (bitop->GET_MODIFIED(pages[i]) == 1)? cout << "M" :  cout << "-";
                (bitop->GET_PAGEDOUT(pages[i]) == 1)? cout << "S " : cout << "- ";
            } else {
                (bitop->GET_PAGEDOUT(pages[i]) == 1)? cout << "# " :  cout << "* ";                
            }
        }
        cout << endl;
    }
	
	if (F) {
        for (int i = 0; i < ftop.size(); i++) {
            (ftop[i] == -1)? cout << "* " : cout << ftop[i] << " ";            
        }
        cout << endl;
    }
	
	if(S) {
	    unsigned long long cost;

        cost =  counter + 400 * (map_counter + unmap_counter)
				+ 3000 * (in_counter + out_counter)
                + 150 * zero_counter;


        cout << "SUM " << counter << " U=" << unmap_counter << " M=" << map_counter;
		cout << " I=" << in_counter << " O=" << out_counter << " Z=" << zero_counter << " ===> " << cost << endl;
    
	}
	
}

void MMU::mapPagesToFrames(int &operation, int &pageid) {
	/* Get the virtual page */
	PTE& page = pages[pageid];

	int framenumber;
	if (O) {
        cout << "==> inst: " << operation << " " << pageid << endl;
    }

	if(!bitop->GET_PRESENT(page)) { // page is absent
		if(frames.size() < num_frames) { // free list
			framenumber = frames.size();
			
			page.framenumber = framenumber;
			frames.push_back(framenumber);
			ftop[framenumber] = pageid;
			
			if(O) {
				cout << counter << ": ZERO " << setfill(' ') << setw(8) << framenumber << endl;
				cout << counter << ": MAP  " << setfill(' ') << setw(4) << pageid << framenumber << endl;
			}
			zero_counter++;
			map_counter++;			
			
		} else { // nothing in the free list. Call the algorithm.
			framenumber = pr_algo->getFrame(pages, frames, ftop);
			
			int old_pageid = ftop[framenumber];
			
			PTE& old_page = pages[old_pageid];
			
			bitop->UNSET_PRESENT(old_page);
			bitop->UNSET_REFERENCED(old_page);
			
			if(O) {
				cout << counter << ": UNMAP"  << setfill(' ') << setw(4) << old_pageid << setw(4) << framenumber << endl;				
			}
			
			unmap_counter++;
			
			if(bitop->GET_MODIFIED(old_page) == 1) {
				bitop->SET_PAGEDOUT(old_page);
				bitop->UNSET_MODIFIED(old_page);
				
				if(O) {
					cout << counter << ": OUT  " << setfill(' ') << setw(4) << old_pageid << framenumber << endl;
				}
				out_counter++;
				
			}
	
			ftop[framenumber] = pageid;

			if(bitop->GET_PAGEDOUT(page) == 1) {
				if(O) {
					cout << counter << ": IN   " << setfill(' ') << setw(4) << pageid << framenumber << endl;
				}
				in_counter++;
			} else {
				if(O) {
					cout << counter << ": ZERO "  << setfill(' ') << setw(8) << framenumber << endl;
				}
				zero_counter++;
			}
			if(O) {
				cout << counter << ": MAP  "  << setfill(' ') << setw(4) << pageid << setw(4) << framenumber << endl;
			}
			map_counter++;		
		}
		
		bitop->SET_PRESENT(page);
		
	} // if absent
	
	if(operation == 0) {
		bitop->SET_REFERENCED(page);
	} else {
		bitop->SET_REFERENCED(page);
		bitop->SET_MODIFIED(page);
	}
		
	counter++;
		
}

