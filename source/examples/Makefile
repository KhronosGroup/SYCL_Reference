SYCL = dpcpp
RUN_EXAMPLES = vector-add get-platforms

all: vector-add.bin

vector-add.bin: vector-add.cpp
	dpcpp -o vector-add.bin vector-add.cpp
