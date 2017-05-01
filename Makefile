include cpp/files.mk

#change to your MATLAB directory
MATLABHOME = /home/osboxes/Downloads/MATLAB

MEXSUFFIX  = mexa64
EXECUTABLE = CXX_caller

#change for different comilers
MEX        = $(MATLABHOME)/mex
CXX        = g++

CFLAGS     = -fPIC -pthread -DMATLAB_MEX_FILE -ansi -D_GNU_SOURCE -fno-omit-frame-pointer -pthread -O3 -DNDEBUG
INCLUDE   = -I/usr/include/eigen3 -I$(MATLABHOME)
LIBS      = -lm -lCGAL
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE).$(MEXSUFFIX) $(SOURCES)

$(EXECUTABLE).$(MEXSUFFIX): $(OBJECTS)
	$(MEX) $(LIBS) -output $(EXECUTABLE) $^

.cpp.o: $(SOURCES)
	$(CXX) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean: 
	rm $(OBJECTS) $(EXECUTABLE).$(MEXSUFFIX)

