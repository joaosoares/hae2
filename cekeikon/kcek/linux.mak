CPP := $(wildcard *.cpp)
CPP := $(notdir $(CPP))
OBJ := $(patsubst %.cpp,%.olx,$(CPP)) 
OBJ := $(notdir $(OBJ))
EXE := $(CEK5_PATH)/cekeikon/bin/kcek

CXXFLAGS := -fmax-errors=2 -c -O3 -Wall -std=gnu++14 -fPIC -Wno-unused-result `pkg-config opencv --cflags` -I. -I$(CEK5_PATH)/cekeikon/src
LDFLAGS := -s `pkg-config opencv --libs` -lcekeikon -L$(CEK5_PATH)/cekeikon/bin 

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ): %.olx: %.cpp 
	$(CXX) $< -o $@ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(EXE)

.PHONY: debug
debug:
	@echo $(CPP)
	@echo $(OBJ)
	@echo $(EXE)
	@echo $(CXXFLAGS)
	@echo $(LDFLAGS)
