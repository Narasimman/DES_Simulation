#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

#include "event.h"
#include "processor.h"
#include "scheduler.h"
#include "FIFO.h"

using namespace std;

FILE* instFile;
Scheduler *iosched;

bool getNextInstruction(int &timestep, int &track) {
	char buf[1000];
    fgets(buf, 1000, instFile);

	timestep = track = -1;
    if (!feof(instFile) && buf[0] != '#') {
        sscanf(buf, "%d%d", &timestep, &track);
		return true;
    }
	return false;
}

void getPRAlgorithm(int algo) {
	switch(algo) { 
		case 'i':
			iosched = new FIFOScheduler();
			break;
	}
}

int main(int argc, char *argv[]) {
    
    int c;
	int timestep, track, reqId = 0;
	while ((c = getopt (argc, argv, "s:")) != -1) {
        switch(c) {
            case 's':
				getPRAlgorithm(optarg[0]);
                break;
            default:
                break;
        }
    }
	
	
    if(argc - optind != 1){
        cout << "inputfile is required.\nInput the required inputs in the format specified. -sScheduler inputfile\n";
        exit(99);
    }

    instFile = fopen(argv[optind], "r");
	
	Processor *ioproc = new Processor(iosched);

	/* Read instruction set one line at a time */
	while(!feof(instFile)) {
		if(getNextInstruction(timestep, track)) {			
			Event e(timestep, reqId, track);
			ioproc->putEvent(e);
			reqId++;
		}
	}
	// ioHandler
	ioproc->handler();
	
	fclose(instFile);
    return 0;
}
