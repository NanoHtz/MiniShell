# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 14:04:17 by fgalvez-          #+#    #+#              #
#    Updated: 2025/05/19 12:04:27 by fgalvez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================= VARIABLES GLOBALES =============================== #

NAME         = minishell
CC           = cc
CFLAGS       = -Wall -Wextra -Werror

LIBS_FLAGS   = -L$(DIR_LIBFT) -lft \
               -L$(DIR_UTILS) -lutils \
               -lreadline -lncurses

RM           = rm -f
NORMINETTE   = norminette
VALGRING     = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
VALGRING_OUT = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_output

# ========================= DIRECTORIOS Y ARCHIVOS =========================== #

DIR_HEADERS = Inc/Inc/libft
DIR_LIBFT   = Inc/libft/
DIR_MINI    = Inc/
DIR_UTILS   = Inc/utils/

HEADERS = $(DIR_UTILS)errors.h \
			$(DIR_MINI)minishell.h \
			$(DIR_LIBFT)libft.h \

DIRSOURCE   = src/

SOURCES = $(DIRSOURCE)main.c \
			$(DIRSOURCE)lexer.c \
			$(DIRSOURCE)lexer_utils.c

# ========================= OBJETOS =========================== #

SRCS        = $(sort $(SOURCES))

OBJSDIR     = ./obj/
OBJS        = $(addprefix $(OBJSDIR), $(notdir $(SRCS:.c=.o)))

# ========================= COLORES PARA EL OUTPUT =========================== #

GREEN			= \033[0;32m
YELLOW			= \033[0;33m
CYAN			= \033[0;36m
MAGENTA			= \033[0;35m
RESET			= \033[0m
RED             = \033[0;31m

# ========================= REGLAS PRINCIPALES =============================== #
.PHONY: all clean fclean re n val ex err

all: libft utils $(NAME)

$(NAME): $(OBJS)
	@echo "\n${MAGENTA}Compilando el ejecutable $(NAME)...${RESET}\n"
	$(CC) $(OBJS) $(CFLAGS) $(LIBS_FLAGS) -o $(NAME)
	@echo "${CYAN}=================================================================================================================${RESET}"
	@echo "${GREEN}                                       [✔] $(NAME) successfully compiled.${RESET}                               "
	@echo "${CYAN}=================================================================================================================${RESET}"
	@echo "${MAGENTA}You should use: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_output ./$(NAME) ${RESET}"

# ========================= REGLAS PARA LOS OBJETOS ========================== #
$(OBJSDIR)%.o: $(DIRSOURCE)%.c
	@echo "${MAGENTA}Generando objetos de $(NAME)...${RESET}"
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objeto: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_MINI)/%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objeto: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

# ========================= LIMPIEZA DE ARCHIVOS ============================= #

libft:
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT)

utils:
	@$(MAKE) --no-print-directory -C $(DIR_UTILS)

clean:
	@echo "${YELLOW}Limpiando archivos objeto de la minishell...${RESET}"
	$(RM) -r $(OBJSDIR)
	@$(RM) valgrind_output
	@$(RM) errors.log
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT) clean
	@$(MAKE) --no-print-directory -C $(DIR_UTILS) clean

fclean: clean
	@echo "${RED}Eliminando la biblioteca $(NAME)...${RESET}"
	$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT) fclean
	@$(MAKE) --no-print-directory -C $(DIR_UTILS) fclean

re: fclean all

# ========================= OTRAS REGLAS ===================================== #
n:  libft utils all
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT) n
	@$(MAKE) --no-print-directory -C $(DIR_UTILS) n
	@echo "\n${CYAN}=================================${RESET}"
	@echo "${GREEN}    Norminette de Minishell    ${RESET}"
	@echo "${CYAN}=================================${RESET}"
	-$(NORMINETTE) $(HEADERS) $(SRCS)
	@echo "${GREEN}[✔] Norminette completa.${RESET}\n"

val: all
	@echo "\n${MAGENTA}Ejecutando Valgrind en ./$(NAME)...${RESET}\n"
	$(VALGRING) ./$(NAME)

valo: all
	@echo "\n${MAGENTA}Ejecutando Valgrind en ./$(NAME)...${RESET}\n"
	$(VALGRING_OUT) ./$(NAME)

ex: all
	@echo "\n${MAGENTA}Ejecutando.../$(NAME)...${RESET}\n"
	./$(NAME)

err: all
	@echo "\n${MAGENTA}Ejecutando.../$(NAME)...${RESET}\n"
	-./$(NAME) 2> errors.log ; \
	echo "exit code: $$?"
	@echo "\n${MAGENTA}log de errores de ./$(NAME):${RESET}\n"
	@cat errors.log;
