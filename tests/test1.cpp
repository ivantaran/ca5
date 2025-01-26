#include "myreader.h"

#include <cassert>

int main(int argc, char *argv[]) {
    assert(argc > 1);
    MyReader reader(argv[1]);
    size_t size = reader.dataSize();
    assert(size == 1520);
    return 0;
}
