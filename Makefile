all: md5crack md5sum

md5crack: md5crack.o md5.o
	$(CXX) $(LDFLAGS) -o $@ $^

md5sum: md5sum.o md5.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	$(RM) md5crack md5sum md5crack.o md5sum.o md5.o
