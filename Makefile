CC = gcc

BIN_DIR = bin
OBJ_DIR = obj

# MaDiEn directories and files
MSD = src
MOD = $(OBJ_DIR)/MaDiEn
MLD = $(BIN_DIR)/MaDiEn
MDE_SRC_FILES = $(MSD)/display.c $(MSD)/buffer.c
MDE_OBJ_FILES = $(patsubst $(MSD)/%.c,$(MOD)/%.o,$(MDE_SRC_FILES))
MDE_HFILES = $(MSD)/display.h $(MSD)/buffer.h
MDE_LIB_HFILES = $(patsubst $(MSD)/%.h,$(MLD)/%.h,$(MDE_HFILES))
MDE_TARGET = $(MLD)/madien.a
# MaDiEn compiler flags
MDE_CFLAGS = -Wall

# tests directories
TSD = tests
TBD = $(BIN_DIR)/tests
TESTS_NAMES = lines bold_unbold
# tests compiler flags
T_CFLAGS = -Wall

.PHONY: all
all: madien tests_all

# MaDiEn related targets
.PHONY: madien
madien: $(MDE_TARGET) $(MDE_LIB_HFILES)

$(MDE_TARGET): $(MDE_OBJ_FILES)
	@mkdir -p $(MLD)
	ar rcs $(MDE_TARGET) $(MDE_OBJ_FILES)

$(MOD)/%.o: $(MSD)/%.c
	@mkdir -p $(MOD)
	$(CC) -o $@ $< -c $(MDE_CFLAGS)

$(MLD)/%.h: $(MSD)/%.h
	@mkdir -p $(MLD)
	cp $< $@

# tests related targets
.PHONY: tests_all
tests_all: $(TESTS_NAMES)

.PHONY: $(TESTS_NAMES)
$(TESTS_NAMES): %: $(TBD)/%

$(TBD)/%: $(TSD)/%/main.c $(MDE_TARGET) $(MDE_LIB_HFILES)
	@mkdir -p $(TBD)
	@rm -rf $(TSD)/$*/madien
	cp -r $(MLD) $(TSD)/$*/madien
	gcc -o $@ $< $(TSD)/$*/madien/madien.a $(T_CFLAGS)

# cleaning related targets
.PHONY: clean
clean: clean_tests
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean_tests
clean_tests:
	rm -rf $(foreach tst,$(TESTS_NAMES),$(TSD)/$(tst)/madien)
