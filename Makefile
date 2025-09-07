# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablo <pablo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 14:04:17 by fgalvez-          #+#    #+#              #
#    Updated: 2025/09/06 19:04:01 by pablo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================= VARIABLES GLOBALES =============================== #

ASAN_CFLAGS  = -g -O0 -fsanitize=address -fno-omit-frame-pointer
ASAN_LDFLAGS = -fsanitize=address
ASAN_ENV     = ASAN_OPTIONS=detect_leaks=1:halt_on_error=1

NAME         = minishell
CC           = cc
CFLAGS       = -Wall -Wextra -Werror -g3 -O0 -fsanitize=address

LIBS_FLAGS   = -L$(DIR_LIBFT) -lft \
               -L$(DIR_UTILS) -lutils \
               -lreadline -lncurses

RM           = rm -f
NORMINETTE   = norminette
VALGRING     = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
           --suppressions=readline.supp

# ========================= DIRECTORIOS Y ARCHIVOS =========================== #

DIR_HEADERS = Inc/Inc/libft
DIR_LIBFT   = Inc/libft/
DIR_MINI    = Inc/
DIR_UTILS   = Inc/utils/

HEADERS = $(DIR_UTILS)errors.h \
			$(DIR_MINI)minishell.h \
			$(DIR_LIBFT)libft.h \

DIRSOURCE   = src/
DIR_LEXER   = src/lexer/
DIR_PARSER   = src/parser/
DIR_EXPANDS   = src/expands/
DIR_UTILSMINI   = src/utils/
DIR_BUILTIN     = src/builtin/
DIR_VARS     = src/vars/
DIR_EXECUTE  = src/execute/
DIR_SIGNAL  = src/signal/
DIR_EXPANDS  = src/expands/

IGNORED_SRC = src/debugs.c
NORM_SRCS   = $(filter-out $(IGNORED_SRC),$(SRCS))

SOURCES = $(DIRSOURCE)main.c \
			$(DIR_LEXER)lexer.c \
			$(DIR_LEXER)types.c \
			$(DIR_LEXER)tokenice.c \
			$(DIR_LEXER)quotes.c \
			$(DIR_LEXER)one_ops.c \
			$(DIR_LEXER)lexer_utils.c \
			$(DIR_LEXER)free_lexer.c \
			$(DIR_PARSER)checks_preparser.c \
			$(DIR_PARSER)checks_utils.c \
			$(DIR_PARSER)handler_redir_utils.c \
			$(DIR_PARSER)handler_utils.c \
			$(DIR_PARSER)handler_word_utils.c \
			$(DIR_PARSER)more_checks_utils.c \
			$(DIR_PARSER)more_redir_utils.c \
			$(DIR_PARSER)parser_utils.c \
			$(DIR_PARSER)parser.c \
			$(DIR_PARSER)process_token.c \
			$(DIR_PARSER)process_token_utils.c \
			$(DIR_VARS)vars.c \
			$(DIR_VARS)remove_vars.c \
			$(DIR_VARS)update_envs.c \
			$(DIR_VARS)key_and_entrys.c \
			$(DIR_VARS)vars_utils.c \
			$(DIR_VARS)last_status.c \
			$(DIR_VARS)more_vars.c \
			$(DIR_EXPANDS)command_expands.c \
			$(DIR_EXPANDS)expands_utils.c \
			$(DIR_EXPANDS)more_expands_utils.c \
			$(DIR_EXPANDS)expands.c \
			$(DIR_EXPANDS)handlers.c \
			$(DIR_EXPANDS)more_utils.c \
			$(DIR_UTILSMINI)frees.c \
			$(DIR_UTILSMINI)env.c \
			$(DIR_UTILSMINI)status.c \
			$(DIR_UTILSMINI)main_utils.c \
			$(DIR_BUILTIN)builtin.c \
			$(DIR_BUILTIN)fix_shlvl.c \
			$(DIR_BUILTIN)utils.c \
			$(DIR_BUILTIN)ft_echo.c \
			$(DIR_BUILTIN)ft_pwd.c \
			$(DIR_BUILTIN)ft_cd.c \
			$(DIR_BUILTIN)cd_utils.c \
			$(DIR_BUILTIN)ft_exit.c \
			$(DIR_BUILTIN)ft_env.c \
			$(DIR_BUILTIN)ft_unset.c \
			$(DIR_BUILTIN)ft_export.c \
			$(DIR_BUILTIN)ft_export_utils.c \
			$(DIR_BUILTIN)print_export.c \
			$(DIR_EXECUTE)heredoc.c \
			$(DIR_EXECUTE)heredoc_utils.c \
			$(DIR_EXECUTE)run_cmds.c \
			$(DIR_EXECUTE)keys.c \
			$(DIR_EXECUTE)more_utils_exec.c \
			$(DIR_EXECUTE)redirections.c \
			$(DIR_EXECUTE)handle_redirections.c \
			$(DIR_EXECUTE)execute_commands.c \
			$(DIR_EXECUTE)path_process.c \
			$(DIR_EXECUTE)execute_utils.c \
			$(DIR_SIGNAL)signal.c

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
.PHONY: all clean fclean re n val ex err test nor

all: libft utils $(NAME)

$(NAME): $(OBJS)
	@echo "\n${MAGENTA}Compilando el ejecutable $(NAME)...${RESET}\n"
	$(CC) $(OBJS) $(CFLAGS) $(LIBS_FLAGS) $(LDFLAGS) -o $(NAME)
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
	@echo "${CYAN}Compilando objetos de los includes: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_LEXER)%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objetos del lexer: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_PARSER)%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objetos del parser: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_EXPANDS)%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objetos de las expansiones: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_UTILSMINI)%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objetos de minishell utils: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_BUILTIN)%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objetos de los builtins: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_VARS)%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objetos de las variables: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_EXECUTE)%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objetos del execute: $<${RESET}"
	$(CC) $(CFLAGS) $(addprefix -I, $(DIR_HEADERS)) -c $< -o $@

$(OBJSDIR)%.o: $(DIR_SIGNAL)%.c
	@mkdir -p $(dir $@)
	@echo "${CYAN}Compilando objetos del signal: $<${RESET}"
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
	@rm -rf logs
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT) clean
	@$(MAKE) --no-print-directory -C $(DIR_UTILS) clean

fclean: clean
	@echo "${RED}Eliminando la biblioteca $(NAME)...${RESET}"
	$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT) fclean
	@$(MAKE) --no-print-directory -C $(DIR_UTILS) fclean

re: fclean all

# ========================= OTRAS REGLAS ===================================== #

val: all
	@echo "\n${MAGENTA}Ejecutando Valgrind en ./$(NAME)...${RESET}\n"
	$(VALGRING) ./$(NAME)

asan: fclean
	@echo "$(MAGENTA)Compilando con AddressSanitizer...$(RESET)"
	$(MAKE) --no-print-directory \
		CFLAGS="$(CFLAGS) $(ASAN_CFLAGS)" \
		LDFLAGS="$(LDFLAGS) $(ASAN_LDFLAGS)" \
		all

sani: asan
	@echo "$(MAGENTA)Ejecutando con AddressSanitizer...$(RESET)"
	$(ASAN_ENV) ./$(NAME)
