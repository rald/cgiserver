#include "random.h"

double drand() {
	return rand()/(RAND_MAX+1.0);
}
