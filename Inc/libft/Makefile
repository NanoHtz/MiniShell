# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgalvez- <fgalvez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 19:54:07 by fgalvez-          #+#    #+#              #
#    Updated: 2025/05/13 22:49:28 by fgalvez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================= VARIABLES GLOBALES =============================== #

NAME         = libft.a
CC           = cc
CFLAGS       = -Wall -Wextra -Werror
AR           = ar rcs
RM           = rm -f
NORMINETTE   = norminette

# ========================= DIRECTORIOS Y ARCHIVOS =========================== #

DIR_INC      = .
DIR_SRC      = .
DIR_OBJ      = ./obj/

HEADERS      = $(DIR_INC)/libft.h

SRCS         = ft_strlen.c \
				ft_lstadd_back.c \
				ft_lstlast.c \
				ft_lstnew.c \
				ft_strdup.c \
				ft_calloc.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_strchr.c \
				ft_isspace.c \
				ft_strnlen.c \
				ft_strndup.c \
				ft_isalpha.c \
				ft_isalnum.c \
				ft_strcspn.c \
				ft_itoa.c \
				ft_intlen.c \
				ft_strjoin.c \
				ft_strncmp.c \
				ft_realloc.c \
				ft_free_split.c \
				ft_strcmp.c \
				ft_putstr.c \
				ft_putstrendl.c \
				ft_atoi.c \
				ft_isnum.c \
				ft_isdigit.c \
				ft_putendl_fd.c \
				ft_putstr_fd.c \
				ft_substr.c

SRCS         := $(addprefix $(DIR_SRC)/,$(SRCS))

OBJS         = $(addprefix $(DIR_OBJ),$(notdir $(SRCS:.c=.o)))

# ========================= COLORES PARA EL OUTPUT =========================== #

GREEN        = \033[0;32m
YELLOW       = \033[0;33m
CYAN         = \033[0;36m
MAGENTA      = \033[0;35m
RED          = \033[0;31m
RESET        = \033[0m

# ========================= REGLAS PRINCIPALES =============================== #

.PHONY: all clean fclean re n nor

all: $(NAME)

$(NAME): $(OBJS)
	@echo "${MAGENTA}Generando biblioteca $(NAME)...${RESET}"
	@$(AR) $(NAME) $(OBJS)
	@echo "${GREEN}✔ $(NAME) creado.${RESET}\n"

# ========================= REGLAS PARA OBJETOS ============================== #

$(DIR_OBJ)%.o: $(DIR_SRC)/%.c $(HEADERS)
	@echo "\n${MAGENTA}Generando objetos de la $(NAME)...${RESET}"
	@mkdir -p $(DIR_OBJ)
	@echo "${CYAN}Compilando: $< → $@${RESET}"
	$(CC) $(CFLAGS) -I$(DIR_INC) -c $< -o $@

# ========================= LIMPIEZA DE ARCHIVOS ============================= #

clean:
	@echo "${YELLOW}Limpiando objetos de libft...${RESET}"
	$(RM) -r $(DIR_OBJ)

fclean:
	@echo "${RED}Eliminando biblioteca $(NAME)...${RESET}"
	$(RM) $(NAME)

re: all

# ========================= NORMINETTE ======================================= #

n:
	@echo "${CYAN}=================================${RESET}"
	@echo "${GREEN} Norminette de la libft${RESET}"
	@echo "${CYAN}=================================${RESET}"
	-$(NORMINETTE) $(HEADERS) $(SRCS)
	@echo "${GREEN}[✔] Norminette pasada.${RESET}\n"

nor:
	@$(NORMINETTE) $(HEADERS) $(SRCS)
