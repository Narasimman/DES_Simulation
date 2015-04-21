#include <vector>

#include "memory_manager.h"
#include "PR_algorithm_base.h"

using namespace std;

void PR_Algorithm::initializeRandom(RandomNumber& r) {
	rnd = r;
	bitop = new BitOP();
}

int PR_Algorithm::getFrame(vector<PTE> &pte, vector<unsigned int> &frame, vector<unsigned int> &ftop) {
	return -1;
}
