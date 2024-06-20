#include "../include/csds/datatypes.h"
#include <assert.h>

int main() {
	assert(sizeof(int8) == 1);
	assert(sizeof(uint8) == 1);

	assert(sizeof(int16) == 2);
	assert(sizeof(uint16) == 2);

	assert(sizeof(int32) == 4);
	assert(sizeof(uint32) == 4);
	assert(sizeof(real32) == 4);

	assert(sizeof(int64) == 8);
	assert(sizeof(uint64) == 8);
	assert(sizeof(real64) == 8);

	return 0;
}
