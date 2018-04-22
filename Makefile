SOURCE_DIR = ./src
TESTS_DIR = ./test

all:
	${MAKE} -C ${SOURCE_DIR} all
ifneq ($(wildcard ${TESTS_DIR}),)
	${MAKE} -C ${TESTS_DIR} run
endif

run:
	${MAKE} -C ${SOURCE_DIR} run

clean:
	${MAKE} -C ${SOURCE_DIR} clean
ifneq ($(wildcard ${TESTS_DIR}),)
	${MAKE} -C ${TESTS_DIR} clean
endif
