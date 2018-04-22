TARGET = RandBmp
BUILD_DIR = ../build
OBJ_DIR = ../build/obj
BIN_DIR = ../build/bin
LIB_DIR = ../build/lib
INCLUDE_DIR = ../include
# Список подкаталогов с исходными файлами
SRC_DIRS = .
OBJ_DIRS = $(addprefix ${OBJ_DIR}/,${SRC_DIRS})

CC = clang
INCLUDES = -I${INCLUDE_DIR}
DEFINES = -D_UNICODE -DUNICODE
LIBS = -lcomctl32
ifeq (${CC},clang)
  LIBS += -lkernel32 -luser32 -lgdi32
  TARGET = RandBmp2.exe
endif
CFLAGS = -std=c++14 -Wall
CLFLAGS =
ifdef DEBUG
  CFLAGS += -g
else
  CFLAGS += -O
  ifneq (${CC},clang)
    CLFLAGS += -s -Wl,--gc-sections
  endif
endif

SRCS = $(wildcard $(addsuffix /*.cpp, ${SRC_DIRS}))
OBJS = $(addprefix ${OBJ_DIR}/, $(subst .cpp,.o,$(SRCS)))
HDRS = $(wildcard $(addsuffix /*.h, $(addprefix ${INCLUDE_DIR}/,${SRC_DIRS})))

RES = $(wildcard *.rc)
RESC = $(addprefix ${OBJ_DIR}/, $(subst .rc,.res,$(RES)))

all: ${BIN_DIR}/${TARGET}

${BIN_DIR}/${TARGET}: ${OBJS} ${RESC}
	${CC} ${CLFLAGS} -mwindows -o $@ $^ ${LIBS}

${OBJ_DIR}/%.o: %.cpp ${HDRS}
	${CC} ${DEFINES} ${CFLAGS} ${INCLUDES} -c -o $@ $<

${OBJ_DIR}/%.res: %.rc resource.h
	windres $< $@ -O coff

run: ${BIN_DIR}/${TARGET}
	${BIN_DIR}/${TARGET}

${OBJS} ${RESC}: | ${OBJ_DIRS}

${OBJ_DIRS}:
	swiss mkdir -p $@

clean:
	swiss rm -f ${OBJS} ${RESC}
