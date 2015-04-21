#include "RandomNumber.h"

using namespace std;

RandomNumber::RandomNumber() {}

RandomNumber::RandomNumber(FILE* f) {
    file = f;
    char buf[80];
    fgets(buf, 80, file);
}

int RandomNumber::getRandomNumber() {
    char buf[80];
    int ret;

    fgets(buf, 80, file);

    // wrap around
    if (feof(file)) {
        fseek(file, 0, SEEK_SET);
        fgets(buf, 80, file);
        fgets(buf, 80, file);
    }
    sscanf(buf, "%d", &ret);
    return ret;
}