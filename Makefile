TARGET=s21_matrix.a
DFLAGS=-o 0 -g3
CFLAGS=-Wall -Wextra -std=c11 -g# -Werror
OS=$(shell uname)
TEST_TARGET=test
EXECUTABLE=s21_matrix

ifeq ($(OS), Darwin)
	LDLIBS = -lcheck -lm -lpthread
else
	LDLIBS = -lcheck -lm -lsubunit -lpthread  -lrt 
endif

TEST_DIR=test
SRC_DIR=lib_matrix
BUILD_DIR=obj
BIN_DIR=bin

MODULES=$(shell find "$(SRC_DIR)" -name "*.c" ! -name "main.c")

OBJECTS=$(MODULES:%.c=%.o)
MODULES_TEST=$(wildcard $(TEST_DIR)/*.c)
OBJECTS_TEST=$(MODULES_TEST:%.c=%.o)
MODULES_RUN = $(wildcard $(SRC_DIR)/*.c)
OBJECTS_RUN = $(MODULES_RUN:%.c=%.o)

.PHONY: all run build rebuild clean test gcov_report style_check valgrind_check $(TARGET)

all: clean $(TARGET) test gcov_report

debug: create_dir
	$(CC)  $(DFLAGS) $(MODULES_RUN) -lm -o $(BIN_DIR)/$@

debug_test: create_dir
	$(CC)  $(DFLAGS) $(MODULES) $(MODULES_TEST) $(LDLIBS) -L. -lm -o $(BIN_DIR)/$@

build: $(TARGET)

rebuild: clean $(TARGET)

$(TARGET): create_dir $(OBJECTS)
	@ar rcs $(BUILD_DIR)/$(TARGET) $(shell find "$(BUILD_DIR)/$(SRC_DIR)" -name "*.o" -not -name "main.o")
	@ar rcs $(TARGET) $(shell find "$(BUILD_DIR)/$(SRC_DIR)" -name "*.o" -not -name "main.o")

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $^

run: create_dir_run $(OBJECTS_RUN)
	@$(CC) $(CFLAGS) $(shell find "$(BUILD_DIR)/$(SRC_DIR)" -name "*.o") -o $(BIN_DIR)/$(EXECUTABLE) -lm
	@./$(BIN_DIR)/$(EXECUTABLE)

test: $(TARGET) $(OBJECTS_TEST)
	@$(CC) $(CFLAGS) $(wildcard $(BUILD_DIR)/$(TEST_DIR)/*.o) $(BUILD_DIR)/$(TARGET) $(LDLIBS) -L. -o $(BIN_DIR)/$(TEST_TARGET)
	@./$(BIN_DIR)/$(TEST_TARGET)
	
gcov_report: $(TARGET)
	@$(CC) --coverage $(CFLAGS) $(wildcard $(TEST_DIR)/*.c) $(LDLIBS) $(MODULES) -o $(BIN_DIR)/$(TEST_TARGET)_gcov
	@./$(BIN_DIR)/$(TEST_TARGET)_gcov
	@lcov -t "test_coverage" -o test_coverage.info -c -d .
	@genhtml -o report test_coverage.info
	@open report/index.html
	@rm -rf */*.gcda */*.gcno report/test_coverage.info *.info

format_style:
	@cp ../materials/linters/.clang-format .
	@clang-format -n */*.c */*.h *.h
	@clang-format -i */*.c */*.h *.h

valgrind_check: test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log-file="valgrind.log" -v --verbose -q --quiet -s ./$(BIN_DIR)/$(TEST_TARGET)

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem */*.c */*.h *.h

run_and_valgrind: run
	valgrind --track-origins=yes --leak-check=full ./$(BIN_DIR)/$(EXECUTABLE)

clean:
	@echo "Deleting unnecessary files..."
	@rm -rf **/*.dSYM **/*.dSYM **/*.log **/*.log test_coverage.info obj bin report *.a *.log

create_dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	@mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	@mkdir -p $(BIN_DIR)

create_dir_run:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(SRC_DIR)
	@mkdir -p $(BIN_DIR)