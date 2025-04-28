# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 11:57:46 by caonguye          #+#    #+#              #
#    Updated: 2025/04/26 19:10:51 by tripham          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= gcc
FLAG	:= -Wall -Wextra -Werror -g -O3
LFLAG	:=	-lreadline


# Additional libft paths
LIBFT_DIR		:= ./Library/libft
LIBFT			:= $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR	:= ./Library/ft_printf_fd
PRINTF			:= $(FT_PRINTF_DIR)/libftprintf.a

HEADER			:= ./Include/Main

INCLUDE			:= -I $(LIBFT_DIR) -I $(FT_PRINTF_DIR) -I $(HEADER)

#MAIN
MAIN_SRC		:=	./Srcs/Main

MAIN_C			:=	main.c					\
					shell_implement.c		\
					shell_input.c			\
					shell_init.c			\
					bad_allocation.c		\
					shell_clean.c			\
					shell_clean_utils.c

# PARSING
PARSING_SRC		:=	./Srcs/Parsing

# Lexer
LEXER_DIR		:=	$(PARSING_SRC)/Lexer

LEXER_C			:=	shell_token_gen.c		\
					lx_group_split.c		\
					lx_group_utils.c		\
					lx_token_split.c		\
					lx_split_utils.c		\
					lx_qmarks_elimination.c	\
					lx_cmd_group.c			\
					lx_classify_utils.c

#Parser
PARSER_DIR		:= $(PARSING_SRC)/Parser

PARSER_C		:=  prs_cmd_check.c			\
					prs_extension.c			\
					prs_list_check.c		\
					prs_utils.c				\
					prs_final.c				\
					prs_split_allspace.c	\
					prs_split_utils.c
#	Env
ENVIR_DIR		:= $(PARSING_SRC)/Environment

ENVIR_C			:= 	env_gen.c				\
					env_sorting.c			\
					env_shlvl.c

#Expansion
EXPANSION_DIR	:= $(PARSING_SRC)/Expansion

EXPANSION_C		:=  exp_generate.c			\
					exp_utils.c				\
					exp_expand.c			\
					exp_type.c

#Heredoc Expansion
HD_EXP_DIR		:= $(PARSING_SRC)/Hdexpansion

HD_EXP_C		:=	hd_expansion_gen.c		\
					hd_expansion_utils.c

# Execution
EXECUTION_SRC	:=	./Srcs/Execution

# AST
AST_DIR			:=	$(EXECUTION_SRC)/Ast

AST_C			:=	ast_init.c				\
					ast_utils.c

# Signals
SIGNAL_DIR		:=	$(EXECUTION_SRC)/Signals

SIGNAL_C		:=	handle_signals_default.c	\
					signals_initialize.c		\
					hd_signal.c

# Execute
EXECUTE_DIR		:=	$(EXECUTION_SRC)/Execute

EXECUTE_C		:=	exec_ast.c			\
					exec_utils.c		\
					exec_cmd_check.c	\
					found_cmd_path.c	\
					exec_handle_error.c	\
					exec_cmd.c			\
					exec_cmd_2.c		\
					exec_rd.c			\
					exec_check_error.c 	\
					exec_heredoc.c		\
					exec_heredoc_utils.c\
					exec_hd_clean_all.c	\
					exec_print_heredoc.c

# Built In Functions
BUILT_IN_DIR	:= $(EXECUTION_SRC)/Built-In_Functions

#Cd
CD_DIR			:= 	$(BUILT_IN_DIR)/Cd

CD_C			:=	cd_call.c

#Echo
ECHO_DIR		:= 	$(BUILT_IN_DIR)/Echo

ECHO_C			:=	echo_call.c

#Env
ENV_DIR			:= 	$(BUILT_IN_DIR)/Env

ENV_C			:=	env_call.c		\
					env_standalone.c

#Exit
EXIT_DIR		:= 	$(BUILT_IN_DIR)/Exit

EXIT_C			:=	exit_call.c

#Export
EXPORT_DIR		:= 	$(BUILT_IN_DIR)/Export

EXPORT_C		:=	export_call.c	\
					ep_export.c		\
					ep_validation.c	\
					ep_split.c

#Pwd
PWD_DIR			:= 	$(BUILT_IN_DIR)/Pwd

PWD_C			:=	pwd_call.c

#Unset
UNSET_DIR		:= 	$(BUILT_IN_DIR)/Unset

UNSET_C			:=	unset_call.c
#utils
UTILS_DIR		:= 	Srcs/Execution/Env_utils

UTILS_C			:=	cd_utils.c
SRCS			:= 	$(addprefix ${MAIN_SRC}/,		${MAIN_C})				\
					$(addprefix ${LEXER_DIR}/, 		${LEXER_C})				\
					$(addprefix ${PARSER_DIR}/,		${PARSER_C})			\
					$(addprefix ${ENVIR_DIR}/,		${ENVIR_C})				\
					$(addprefix ${EXPANSION_DIR}/,	${EXPANSION_C})			\
					$(addprefix ${HD_EXP_DIR}/,		${HD_EXP_C})			\
					$(addprefix ${AST_DIR}/,		${AST_C})				\
					$(addprefix ${EXECUTE_DIR}/,	${EXECUTE_C})			\
					$(addprefix ${SIGNAL_DIR}/,		${SIGNAL_C})			\
					$(addprefix ${CD_DIR}/,			${CD_C})				\
					$(addprefix ${ECHO_DIR}/,		${ECHO_C})				\
					$(addprefix ${ENV_DIR}/,		${ENV_C})				\
					$(addprefix ${EXPORT_DIR}/,		${EXPORT_C})			\
					$(addprefix ${EXIT_DIR}/,		${EXIT_C})				\
					$(addprefix ${UNSET_DIR}/,		${UNSET_C})				\
					$(addprefix ${PWD_DIR}/,		${PWD_C})				\
					$(addprefix ${UTILS_DIR}/,		${UTILS_C})	  			

OBJS           :=	${SRCS:.c=.o}

all:    ${LIBFT} ${PRINTF} ${NAME}

%.o:%.c
		@${CC} ${FLAG} ${INCLUDE} -o $@ -c $<

${NAME}	:	${OBJS} ${LIBFT} ${PRINTF}
		@printf "\033[1;32m💻Launching"
		@for i in 1 2 3; do \
			printf "\033[0;32m."; sleep 0.3; \
		done; \
		for i in 1 2 3; do \
			printf "\b \b"; sleep 0.3; \
		done; \
		for i in 1 2 3; do \
			printf "\033[0;32m."; sleep 0.3; \
		done; \
		for i in 1 2 3; do \
			printf "\b \b"; sleep 0.3; \
		done; \
		printf "\033[0m\n"
		@${CC} ${OBJS} ${LIBFT} ${PRINTF} ${FLAG} ${LFLAG} -o ${NAME}

${LIBFT}	:
		@$(MAKE) -s -C ${LIBFT_DIR}

${PRINTF}	:
		@$(MAKE) -s -C ${FT_PRINTF_DIR}

clean    :
		@rm -f ${OBJS}
		@$(MAKE) -s -C ${LIBFT_DIR} clean
		@$(MAKE) -s -C ${FT_PRINTF_DIR} clean

fclean   : clean
		@printf "\033[1;32m🧹️Cleaning"
		@for i in 1 2 3; do \
			printf "\033[0;32m."; sleep 0.3; \
		done; \
		for i in 1 2 3; do \
			printf "\b \b"; sleep 0.3; \
		done; \
		for i in 1 2 3; do \
			printf "\033[0;32m."; sleep 0.3; \
		done; \
		for i in 1 2 3; do \
			printf "\b \b"; sleep 0.3; \
		done; \
		printf "\033[0m\n"
		@echo "\033[1;32mDone🎉"
		@rm -rf ${NAME}
		@$(MAKE) -s -C ${LIBFT_DIR} fclean
		@$(MAKE) -s -C ${FT_PRINTF_DIR} fclean

re    : fclean all

.PHONY: all clean fclean re
