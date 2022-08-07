NAME_ZIP = compacta.out
NAME_UNZIP = descompacta.out
COMPILER = gcc
FLAGS = -lm -pedantic -Wall

EXEC_DIR = ./bin
OBJ_DIR = ./objects

C_FILES = *.c
O_FILES = *.o
ZIP_FILE = compress.c
UNZIP_FILE = unzip.c
ZIP_OBJ = compress.o
UNZIP_OBJ = unzip.o

YELLOW = "\033[1;33m"
RED = "\033[1;31m" 
CYAN = "\033[1;36m"
PURPLE = "\033[1;35m"
RESET_COLOR = "\033[0m"


all: create_directories $(O_FILES) compress uncompress create_binary

%.o: ./src/%.c ./include/%.h
	@echo $(YELLOW)
	@echo Compilling ./src/$(C_FILES) files...
	@$(COMPILER) -c ./src/$(C_FILES) 
	@mv $(O_FILES) $(OBJ_DIR)
	@echo $(RESET_COLOR)

compress: compress.c
	@echo $(YELLOW)
	@echo Compiling $(ZIP_FILE) file...
	@$(COMPILER) -c $(ZIP_FILE)
	@echo $(RESET_COLOR)

uncompress: unzip.c
	@echo $(YELLOW)
	@echo Compiling $(UNZIP_FILE) file...
	@$(COMPILER) -c $(UNZIP_FILE)
	@echo $(RESET_COLOR)

create_directories:
	@echo $(PURPLE)
	@echo Creating and organizing directories...
	@mkdir $(OBJ_DIR)
	@echo $(RESET_COLOR)

create_binary:
	@echo $(YELLOW)
	@echo Creating executable files...
	@$(COMPILER) -o $(NAME_ZIP) $(OBJ_DIR)/$(O_FILES) $(ZIP_OBJ) $(FLAGS)
	@$(COMPILER) -o $(NAME_UNZIP) $(OBJ_DIR)/$(O_FILES) $(UNZIP_OBJ) $(FLAGS)
	@mv $(O_FILES) $(OBJ_DIR)
	@echo $(RESET_COLOR)

clean:
	@echo $(RED)
	@echo Cleaning directory...
	@rm -rf $(OBJ_DIR) *.o *.out *.comp
	@echo $(RESET_COLOR)

zip:
	@echo $(CYAN)
	@echo Compressing file...
	@echo $(RESET_COLOR)
	@./$(NAME_ZIP) $(f)

unzip:
	@echo $(CYAN)
	@echo Unziping file...
	@echo $(RESET_COLOR)
	@./$(NAME_UNZIP) $(f)

valgrindz:
	@echo $(CYAN)
	@echo Running valgrind on $(NAME_UNZIP)
	@echo $(RESET_COLOR)
	@valgrind ./$(NAME_ZIP) $(r)

valgrindu:
	@echo $(CYAN)
	@echo Running valgrind on $(NAME_UNZIP)
	@echo $(RESET_COLOR)
	@valgrind ./$(NAME_UNZIP) $(r)

again: clean all zip