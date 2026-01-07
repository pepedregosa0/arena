#------------------------------------------------
# Compile options
CC=g++
CFLAGS= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Directories
SRC_DIR=src
INCLUDE=include
OBJ_DIR=obj

# Srcs
SRC_FILES=input.cpp simulation.cpp utils.cpp main.cpp

SRCS=$(addprefix $(SRC_DIR)/,$(SRC_FILES))

# Objs
OBJS=$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))

# Project name
NAME=arena

#------------------------------------------------

#------------------------------------------------
# ALL rule
all: $(NAME)
#------------------------------------------------

#------------------------------------------------
# Project compilation
$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "Compilando simulador"
	@echo "	                              "
	@echo "    /\\                         "
	@echo "   /  \\   _ __ ___ _ __   __ _ "
	@echo "  / /\\ \\ | '__/ _ \\ '_ \\ / _\` |"
	@echo " / ____ \\| | |  __/ | | | (_| |"
	@echo "/_/    \\_\\_|  \\___|_| |_|\\__,_|"
	@echo "                               "
	@$(CC) $(CFLAGS) -I$(INCLUDE) -o $(NAME) $(OBJS)
	@echo "Compilado"
#------------------------------------------------

#------------------------------------------------
# Dependencies
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CFLAGS) -I$(INCLUDE) $< -o $@
#------------------------------------------------

#------------------------------------------------
# Cleaning
clean:
	@rm -rf $(OBJ_DIR)
	@echo "  /\\                          "
	@echo "  ||                          "
	@echo "  ||                          "
	@echo "  ||                          "
	@echo "  ||                          "
	@echo "  ||                          "
	@echo "  ||                          "
	@echo "  ||                          "
	@echo "  ||                          "
	@echo " /||\\                         "
	@echo "/||||\\                        "
	@echo "======         __|__          "
	@echo "||||||        / ~#~ \\         "
	@echo "||||||       |-------|        "
	@echo "||||||       |_______|        "
	@echo "                              "

fclean: clean
	@rm -f $(NAME)
#------------------------------------------------

#------------------------------------------------
# RE
re: fclean all
#------------------------------------------------

#------------------------------------------------
# PHONY
.PHONY: all $(NAME) clean fclean re
#------------------------------------------------