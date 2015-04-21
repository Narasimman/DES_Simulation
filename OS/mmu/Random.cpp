#include "Random.h"
#include "memory_manager.h"

using namespace std;

Random::Random() {}

int Random::getFrame(vector<PTE> &pte, vector<unsigned int> &frames, vector<unsigned int> &ftop) {
	int frameNumber = rnd.getRandomNumber();
	return frames[frameNumber % frames.size()];
}
