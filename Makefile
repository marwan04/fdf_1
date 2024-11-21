NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCDIR = srcs
OBJDIR = obj
LIBPATH	= libft/

LIB = -L./libft -lft -lmlx -lX11  -lXext

RM = rm -rf

SRC_FILES = draw.c

SRC = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

${NAME}: ${OBJ}
	 make -C ${LIBPATH}
	 ${CC} ${CFLAGS} $^ ${LIB} -o $@
	 
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
	 
clean:
	make clean -C ${LIBPATH}
	${RM} $(OBJDIR)

fclean: clean
	make fclean -C ${LIBPATH}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
