CC = gcc

madien: madien_setup madien_o madien_h
	@echo "Creating MaDiEn archive file"
	ar rcs bin/MaDiEn/madien.a obj/MaDiEn/*.o

madien_setup:
	@echo "Setting up MaDiEn directories"
	mkdir -p bin/MaDiEn/
	mkdir -p obj/MaDiEn/

madien_o:
	@echo "Compiling MaDiEn source to object files"
	$(CC) -o obj/MaDiEn/display.o src/display.c -c
	$(CC) -o obj/MaDiEn/buffer.o src/buffer.c -c

madien_h:
	@echo "Copying MaDiEn header files"
	cp src/display.h bin/MaDiEn/display.h
	cp src/buffer.h bin/MaDiEn/buffer.h

tests_all: tests_lines

tests_lines: madien
	@echo "Copying MaDiEn library to tests/lines/madien/"
	cp -r bin/MaDiEn/ tests/lines/madien/
	@echo "Setting up tests/lines directories"
	mkdir -p bin/tests/lines/
	@echo "Compiling tests/lines"
	$(CC) -o bin/tests/lines/lines tests/lines/main.c tests/lines/madien/madien.a

clean: clean_obj_bin clean_tests

clean_obj_bin:
	rm -rf bin/
	rm -rf obj/

clean_tests:
	rm -rf tests/lines/madien/

.PHONY: madien madien_setup madien_o madien_h tests_all tests_lines clean clean_obj_bin clean_tests
