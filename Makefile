AutomatedMakefile = am
CC = g++
CXXFLAGS = -Wno-deprecated-declarations -g -O0

PROJECT_PATH = $(PROJECT_DIR)
GUI_PATH = $(PROJECT_PATH)/TDM-GCC-64/wxWidgets-3.1.0

INC_DIRS = -I$(PROJECT_PATH)/CSC2110 -I$(PROJECT_PATH)/GUI -I$(GUI_PATH)/include -I$(GUI_PATH)/lib/gcc510TDM_x64_dll/mswu
LIB_DIRS = -L$(PROJECT_PATH)/CSC2110 -L$(PROJECT_PATH)/GUI -L$(GUI_PATH)/lib/gcc510TDM_x64_dll
LDFLAGS = -Wl,-Bstatic
LIBS = $(LDFLAGS) -lCSC2110 -lrandom -lGUI -lwxmsw31u_core -lwxbase31u -lgdi32

COMPILE = $(CC) $(CXXFLAGS) $(INC_DIRS) -c 
LINK = $(CC) $(CXXFLAGS) $(LIB_DIRS)

FILES =Main.o
EXECUTABLE = AVL.exe

all: AVL

AVL: $(FILES)
	 $(LINK) $(FILES) $(LIBS) -o $(EXECUTABLE)

Main.o:	
	$(COMPILE) Main.cpp