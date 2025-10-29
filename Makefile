INCLUDE_DIR = include
BUILD_DIR = build
SRC_DIR = src

CFLAGS =	-Wall -Wextra -Werror -g
INCLUDE = -I$(INCLUDE_DIR)

NAME =		interpreter

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@printf "Object files cleaned.\n"

fclean: clean
	@rm -f $(NAME)
	@printf "Binaries cleaned.\n"

phony: all clean fclean
