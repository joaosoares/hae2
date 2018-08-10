CPP := $(wildcard *.cpp)
CPP := $(notdir $(CPP))
OBJ := $(patsubst %.cpp,%.o,$(CPP)) 
OBJ := $(notdir $(OBJ))
HEA := $(wildcard *.h) 
HEA := $(notdir $(HEA))
DLL := $(CEK5_PATH)/cekeikon/bin/libcekeikon.so

CXXFLAGS := -fmax-errors=2 -c -O3 -std=gnu++14 -I. -fPIC -Wno-unused-result `pkg-config opencv --cflags`
LDFLAGS := -s -shared `pkg-config opencv --libs`
#Nao sei se tem que ter -fPIC

all: $(DLL)

$(DLL): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) 

$(OBJ): %.o: %.cpp %.h
	$(CXX) $< -o $@ $(CXXFLAGS) 

.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(DLL)

.PHONY: debug
debug:
	@echo $(CPP)
	@echo $(OBJ)
	@echo $(HEA)
	@echo $(DLL)
	@echo $(CXXFLAGS)
	@echo $(LDFLAGS)

