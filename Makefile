CC=clang
CFLAGS=-I. -Wall
OUTDIR=bin
HELPER_SRCS:=$(shell find C_Helper -name '*.c')
CLIENT_SRCS:=$(shell find C_Client -name '*.c')
SERVER_SRCS:=$(shell find C_Server -name '*.c')
HELPER_OBJECTS:=$(patsubst %.c,$(OUTDIR)/%.o,$(HELPER_SRCS))
CLIENT_OBJECTS:=$(patsubst %.c,$(OUTDIR)/%.o,$(CLIENT_SRCS))
SERVER_OBJECTS:=$(patsubst %.c,$(OUTDIR)/%.o,$(SERVER_SRCS))
all: mkdir C_Client/c_client C_Server/c_server

mkdir:
	mkdir -p ./$(OUTDIR) ./$(OUTDIR)/C_Helper ./$(OUTDIR)/C_Server ./$(OUTDIR)/C_Client
$(OUTDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $<  -o $@
C_Client/c_client: $(CLIENT_OBJECTS) $(HELPER_OBJECTS)
	$(CC) $^ -o $(OUTDIR)/$@ $(CFLAGS)
C_Server/c_server: $(CLIENT_OBJECTS) $(HELPER_OBJECTS)
	$(CC) $^ -o $(OUTDIR)/$@ $(CFLAGS)

clean:
	cd bin && rm -rf *
