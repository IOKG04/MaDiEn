CC = gcc

BIN_DIR = bin
OBJ_DIR = obj

# MaDiEn directories and files
MSD = src
MOD = $(OBJ_DIR)/MaDiEn
MLD = $(BIN_DIR)/MaDiEn
MLD_HEADERS = $(MLD)/madien
MDE_SRC_FILES = $(wildcard $(MSD)/*.c)
MDE_OBJ_FILES = $(patsubst $(MSD)/%.c,$(MOD)/%.o,$(MDE_SRC_FILES))
MDE_HFILES = $(wildcard $(MSD)/*.h)
MDE_LIB_HFILES = $(patsubst $(MSD)/%.h,$(MLD_HEADERS)/%.h,$(MDE_HFILES))
MDE_TARGET = $(MLD)/madien.a
# MaDiEn compiler flags
MDE_CFLAGS = -Wall -Os

# tests directories
TSD = tests
TBD = $(BIN_DIR)/tests
TESTS_NAMES = lines bold_unbold tictactoe acouplestrings
# tests compiler flags
T_CFLAGS = -Wall -Oz

.PHONY: all
all: madien tests_all

# MaDiEn related targets
.PHONY: madien
madien: $(MDE_TARGET) $(MDE_LIB_HFILES)

$(MDE_TARGET): $(MDE_OBJ_FILES)
	@mkdir -p $(MLD)
	ar rcs $(MDE_TARGET) $(MDE_OBJ_FILES)

$(MOD)/%.o: $(MSD)/%.c $(MDE_HFILES)
	@mkdir -p $(MOD)
	$(CC) -o $@ $< -c $(MDE_CFLAGS)

$(MLD_HEADERS)/%.h: $(MSD)/%.h
	@mkdir -p $(MLD_HEADERS)
	cp $< $@

# tests related targets
.PHONY: tests_all
tests_all: $(TESTS_NAMES)

.PHONY: $(TESTS_NAMES)
$(TESTS_NAMES): %: $(TBD)/%

$(TBD)/%: $(TSD)/%/main.c $(MDE_TARGET) $(MDE_LIB_HFILES)
	@mkdir -p $(TBD)
	@rm -rf $(TSD)/$*/madien
	cp -r $(MLD_HEADERS) $(TSD)/$*/madien
	gcc -o $@ $< $(MDE_TARGET) $(T_CFLAGS)

# cleaning related targets
.PHONY: clean
clean: clean_tests
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean_tests
clean_tests:
	rm -rf $(foreach tst,$(TESTS_NAMES),$(TSD)/$(tst)/madien)
