CC = gcc

BIN_DIR = bin
OBJ_DIR = obj

# MaDiEn directories and files
MSD = src
MOD = $(OBJ_DIR)
MLD = $(BIN_DIR)
MLD_HEADERS = $(MLD)
MDE_SRC_FILES = $(wildcard $(MSD)/*.c)
MDE_OBJ_FILES = $(patsubst $(MSD)/%.c,$(MOD)/%.o,$(MDE_SRC_FILES))
MDE_HFILES = $(wildcard $(MSD)/*.h)
MDE_LIB_HFILES = $(patsubst $(MSD)/%.h,$(MLD_HEADERS)/%.h,$(MDE_HFILES))
MDE_TARGET = $(MLD)/madien.a
# MaDiEn compiler flags
MDE_CFLAGS = -Wall -O2

.PHONY: all
all: madien

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

# cleaning related targets
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
