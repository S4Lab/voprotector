OPTIONS := -g
BINARIES := test0.out test0.voprotected.out test1.out test1.voprotected.out test2.out test2.voprotected.out test3.out test3.voprotected.out test4.out test4.voprotected.out test5.out test5.voprotected.out test6.out test6.voprotected.out input0.out input0.voprotected.out input1.out input1.voprotected.out input2.out input2.voprotected.out input3.out input3.voprotected.out

all: $(BINARIES)

%.voprotected.out: %.voprotected.o vo-interpreter.o
	$(CXX) $(OPTIONS) $^ -o $@

%.out: %.o
	$(CXX) $(OPTIONS) $^ -o $@

%.o: %.c
	$(CXX) $(OPTIONS) $< -c -o $@

clean:
	rm -f $(BINARIES) *.o

.PHONY: all clean
.PRECIOUS: %.o
