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
#include "Random.h"
#include "SecondChance.h"
#include "ClockFrame.h"
#include "ClockVirtual.h"
#include "NRU.h"
#include "LRU.h"
#include "AgingFrame.h"
#include "AgingVirtual.h"
#include "RandomNumber.h"

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
		case 'r':
			pr_algo = new Random();
			break;
		case 's':
			pr_algo = new SecondChance();
			break;
		case 'c':
			pr_algo = new ClockFrame();
			break;
		case 'X':
			pr_algo = new ClockVirtual();
			break;
		case 'N':
			pr_algo = new NRU();
			break;
		case 'l':
			pr_algo = new LRU();
			break;
		case 'a':
			pr_algo = new AgingFrame();
			break;
		case 'Y':
			pr_algo = new AgingVirtual();
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
	
	RandomNumber *rnd = new RandomNumber(rFile);
	pr_algo->initializeRandom(*rnd);
	

	/* Read instruction set one line at a time */
	while(!feof(instFile)) {
		if(getNextInstruction(operation, page)) {
			// Process the virtual page
			mmu->mapPagesToFrames(operation, page);
		}
	}
	
	mmu->printOptions();
	
    fclose(rFile);
    fclose(instFile);
    return 0;
}
