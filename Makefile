#This sample makefile has been setup for a project which contains the following files: main.h, ap-main.c, ap-main.h, ap-gen.c, ap-gen.h   Edit as necessary for your project

#Change output_file_name.a below to your desired executible filename

#Set all your object files (the object files of all the .c files in your project, e.g. main.o my_sub_functions.o )
#OBJ = main.o Repositorio.o var_func_globales.o var_func_vent_programa.o
OBJ = main.o var_func_globales.o var_func_vent_programa.o

#OBJ_BG = control_riego_bg.o	Repositorio.o
OBJ_BG = control_riego_bg.o

PRUEBA_CMD_SH = prueba_comandos_shm.o

IHM_CONF_RIEGO = interfaz_conf_riego.o var_globales_ihm.o var_ventana_cfg_prog.o

#Set any dependant header files so that if they are edited they cause a complete re-compile (e.g. main.h some_subfunctions.h some_definitions_file.h ), or leave blank
DEPS = Repositorio.h var_func_globales.h

DEPS_IHM = var_globales_ihm.h 

DEPS_REP = Repositorio.h

#Any special libraries you are using in your project (e.g. -lbcm2835 -lrt `pkg-config --libs gtk+-3.0` ), or leave blank
LIBS = -lbcm2835 -lpthread -lComms -lRepositorio `pkg-config --libs gtk+-3.0`

LIBS_IHM = `pkg-config --libs gtk+-3.0`

#Set any compiler flags you want to use (e.g. -I/usr/include/somefolder `pkg-config --cflags gtk+-3.0` ), or leave blank
CFLAGS = `pkg-config --cflags gtk+-3.0` -lrt -L./libcomms -L.

#Set the compiler you are using ( gcc for C or g++ for C++ )
CC = g++

#Set the filename extensiton of your C files (e.g. .c or .cpp )
EXTENSION = .cxx

#define a rule that applies to all files ending in the .o suffix, which says that the .o file depends upon the .c version of the file and all the .h files included in the DEPS macro.  Compile each object file
%.o: %$(EXTENSION) $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

#Combine them into the output file
#Set your desired exe output file name here
libRepositorio:
	$(CC)	-c	-g	-fPIC	Repositorio.cxx	-o	Repositorio.o
	$(CC)	Repositorio.o -shared	-o	libRepositorio.so

control_riego_rpi: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
control_riego_bg: $(OBJ_BG)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
prueba_comandos_shm: $(PRUEBA_CMD_SH)	
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
interfaz_conf_riego: $(IHM_CONF_RIEGO)	
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS_IHM)
		
all:	libRepositorio	control_riego_bg	control_riego_rpi	prueba_comandos_shm	

#Cleanup
.PHONY: clean

clean:
	rm -f *.so	*.o *~ core *~ control_riego_bg control_riego_rpi interfaz_conf_riego prueba_comandos_shm
