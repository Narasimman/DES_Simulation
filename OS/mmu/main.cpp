#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

#include "memory_manager.h"
#include "bit_operations.h"
#include "FIFO.h"

using namespace std;

FILE* rFile;
FILE* instFile;
PR_Algorithm *pr_algo;


bool getNextInstruction(int &op, int &pg) {
	char buf[1000];
    fgets(buf, 1000, instFile);

	op = pg = -1;
    if (!feof(instFile) && buf[0] != '#') {
        sscanf(buf, "%d%d", &op, &pg);
		return true;
    }
	return false;
}

void getPRAlgorithm(int algo) {
	switch(algo) { 
		case 'f':
			pr_algo = new FIFO();
			break;
	}
}

int main(int argc, char *argv[]) {
    
    int c, num_frames = 0;
	int operation, page;
	char *options;
    while ((c = getopt (argc, argv, "a:o:f:")) != -1) {
        switch(c) {
            case 'a':
				getPRAlgorithm(optarg[0]);
                break;
            case 'o':
				options = optarg;
                break;
            case 'f':
				sscanf(optarg, "%d", &num_frames);				
                break;
            default:
                break;
        }
    }
	
	/* Initialize MMU*/
	MMU *mmu = new MMU(num_frames, pr_algo);
	mmu->setOptions(options);

    if(argc - optind != 2){
        cout << "inputfile and randfile are required.\nInput the required inputs in the format specified. [-aAlgo] [-oOptions] [-fFrameNumber] inputfile randfile\n";
        exit(99);
    }

    instFile = fopen(argv[optind], "r");
    rFile = fopen(argv[optind + 1], "r");
	

	/* Read instruction set one line at a time */
	while(!feof(instFile)) {
		if(getNextInstruction(operation, page)) {
			// Process the virtual page
			mmu->mapPagesToFrames(operation, page);
		}
	}
	
	
    fclose(rFile);
    fclose(instFile);
    return 0;
}
