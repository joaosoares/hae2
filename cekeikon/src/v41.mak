OPENCVLIB := $(notdir $(wildcard $(CEK5_PATH)/OPENCV2410/BUILD/MINGW64/BIN/lib*.dll) )
OPENCVLIB := $(subst libopencv_,-lopencv_,$(OPENCVLIB))
OPENCVLIB := $(basename $(OPENCVLIB))

CPP := $(wildcard *.cpp)
CPP := $(notdir $(CPP))
OBJ := $(patsubst %.cpp,%.o41,$(CPP)) 
OBJ := $(notdir $(OBJ))
HEA := $(wildcard *.h) 
HEA := $(notdir $(HEA))
DLL := $(CEK5_PATH)/CEKEIKON/BIN/cekeikon41.dll

CXXFLAGS := -fmax-errors=2 -c -O3 -Wall -std=gnu++14 -I$(CEK5_PATH)/OPENCV2410/BUILD/INCLUDE -I$(CEK5_PATH)/CEKEIKON/SRC
LDFLAGS := -s -shared $(OPENCVLIB) -L$(CEK5_PATH)/OPENCV2410/BUILD/MINGW64/LIB -L$(CEK5_PATH)/CEKEIKON/BIN -L$(CEK5_PATH)/CEKEIKON/PROJS/BIN

#Nao sei se tem que ter -fPIC

all: $(DLL) 

$(DLL): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) 

$(OBJ): %.o41: %.cpp %.h
	$(CXX) $< -o $@ $(CXXFLAGS) 

.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(DLL)

.PHONY: debug
debug:
	@echo $(OPENCVLIB)
	@echo $(CPP)
	@echo $(OBJ)
	@echo $(HEA)
	@echo $(DLL)
	@echo $(CXXFLAGS)
	@echo $(LDFLAGS)
