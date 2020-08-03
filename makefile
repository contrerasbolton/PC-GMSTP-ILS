$(shell mkdir -p obj/)
CPP      = g++
#DEFINES  = -DIL_STD -DNDEBUG -std=c++14 -g -ggdb
DEFINES  = -DIL_STD -std=c++14
CXXFLAGS = -O2 -Wall -fPIC -fno-strict-aliasing -Wno-ignored-attributes $(DEFINES)
INCPATH  = -I$(CPLEX)/cplex/include -I$(CPLEX)/concert/include
OBJDIR   = obj
LFLAGS   = -Wl,-O2
OBJ      = $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))
TARGET   = pc_gmstp

.PHONY: all clean

all: $(OBJDIR) $(TARGET)


$(OBJDIR):
	@cd $(OBJLIB) && $(MAKE)

$(OBJDIR)/%.o: %.cpp
	$(CPP) $(MCCFLAGS) $(CXXFLAGS) $(INCPATH)  -c $< -o $@

$(TARGET): $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJMINC) $(OBJGA) -o $@ $^ $(LFLAGS)

clean:
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -f  $(OBJDIR)/*
all: $(SUBDIRS)



.PHONY: $(SUBDIRS)
