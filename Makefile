ARCH := $(shell getconf LONG_BIT)

LIBS :=  lib/x$(ARCH)/libvmf.a
INCLUDES := -Iinclude/vmf -Iinclude
CFLAGS += $(INCLUDES) -std=gnu++11
LDFLAGS += -ldl

vmftool: vmftool.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) $^ $(LIBS) $(LDFLAGS) -o $@

clean:
	rm -f vmftool *.o
