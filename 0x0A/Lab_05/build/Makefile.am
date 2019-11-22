AUTOMAKE_OPTIONS = subdir-objects

noinst_LIBRARIES = libLab_05_Lib.a libLab_05_MatrixLib.a 
bin_PROGRAMS = Lab_05_Client Lab_05_Server

CFLAGS = -std=gnu99

libLab_05_MatrixLib_a_SOURCES = \
    ../Lab_05_MatrixLib/Matrix.c

libLab_05_Lib_a_SOURCES = \
    ../Lab_05_Lib/Input.c \
    ../Lab_05_Lib/ParseInt.c \
    ../Lab_05_Lib/ReturnCodes.c \
    ../Lab_05_Lib/LastErrorMessage.c \
    ../Lab_05_Lib/Request.c \
    ../Lab_05_Lib/Socket.c
libLab_05_Lib_a_CFLAGS = -I../Lab_05_MatrixLib 
libLab_05_Lib_a_LIBADD = libLab_05_MatrixLib.a

Lab_05_Client_SOURCES = \
    ../Lab_05_Client/Args.c \
    ../Lab_05_Client/Client.c \
    ../Lab_05_Client/main.c
Lab_05_Client_CFLAGS = -I../Lab_05_MatrixLib -I../Lab_05_Lib
Lab_05_Client_LDADD = libLab_05_MatrixLib.a libLab_05_Lib.a

Lab_05_Server_SOURCES = \
    ../Lab_05_Server/Args.c \
    ../Lab_05_Server/Server.c \
    ../Lab_05_Server/main.c
Lab_05_Server_CFLAGS = -I../Lab_05_MatrixLib -I../Lab_05_Lib
Lab_05_Server_LDADD = libLab_05_MatrixLib.a libLab_05_Lib.a

