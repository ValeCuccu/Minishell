# **************************************************************************** #
#                                   Minishell                                  #
# **************************************************************************** #

NAME        = minishell

# === Compilatore & Flag ===
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I./header -I./src/libft

# === Librerie ===
LIBFT_DIR   = ./src/libft
LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBS        = -lreadline -lncurses

# === Directory principali ===
SRC_DIR     = src
OBJ_DIR     = obj

# === Sorgenti (solo sotto src/) ===
SRC         = \
	$(SRC_DIR)/cmd/cmd_set.c \
	$(SRC_DIR)/lexer/lexer_set.c \
	$(SRC_DIR)/lexer/lexer_build_tokens.c \
	$(SRC_DIR)/redir/redir_set.c \
	$(SRC_DIR)/token/token_set.c \
	$(SRC_DIR)/utils/check_char_type.c \
	$(SRC_DIR)/utils/extract_cmd.c \
	$(SRC_DIR)/utils/track_quotes.c \
	$(SRC_DIR)/utils/track_redir.c \
	$(SRC_DIR)/utils/utils_lexer.c \
	$(SRC_DIR)/utils/expand_utils.c \
	$(SRC_DIR)/utils/global_status.c \
	$(SRC_DIR)/expand/expand_dollar.c \
	$(SRC_DIR)/expand/expand_quotes.c \
	$(SRC_DIR)/expand/expand_core.c \
	$(SRC_DIR)/expand/expand_tokens.c \
	$(SRC_DIR)/utils/expand_utils2.c \
	$(SRC_DIR)/utils/parsing_utils.c \
	$(SRC_DIR)/utils/parsing_utils2.c \
	$(SRC_DIR)/utils/check_syntax.c \
	$(SRC_DIR)/utils/build_cmd_list.c \
	$(SRC_DIR)/parsing/parse_pipeline.c \
	$(SRC_DIR)/utils/helper_quotes.c \
	$(SRC_DIR)/utils/env_utils.c \
	$(SRC_DIR)/utils/env_mod.c \
	$(SRC_DIR)/utils/env_utils2.c \
	$(SRC_DIR)/env_vale/env_init.c \
	$(SRC_DIR)/signal/signals.c \
	$(SRC_DIR)/signal/signal_helper.c \
	$(SRC_DIR)/builtin/bi_cd.c \
	$(SRC_DIR)/builtin/bi_cd_utils.c \
	$(SRC_DIR)/builtin/bi_echo.c \
	$(SRC_DIR)/builtin/bi_env.c \
	$(SRC_DIR)/builtin/bi_exit.c \
	$(SRC_DIR)/builtin/bi_exit_child.c \
	$(SRC_DIR)/builtin/bi_export.c \
	$(SRC_DIR)/builtin/bi_export_print.c \
	$(SRC_DIR)/builtin/bi_pwd.c \
	$(SRC_DIR)/builtin/bi_unset.c \
	$(SRC_DIR)/env/env_free_array.c \
	$(SRC_DIR)/env/env_init_utils.c \
	$(SRC_DIR)/env/env_init.c \
	$(SRC_DIR)/env/env_list.c \
	$(SRC_DIR)/env/env_ops.c \
	$(SRC_DIR)/env/env_to_array.c \
	$(SRC_DIR)/exec/adapt_child.c \
	$(SRC_DIR)/exec/adapt_entry.c \
	$(SRC_DIR)/exec/adapt_pipeline_utils.c \
	$(SRC_DIR)/exec/adapt_pipeline.c \
	$(SRC_DIR)/exec/adapt_redirs.c \
	$(SRC_DIR)/exec/adapt_redir_utils.c \
	$(SRC_DIR)/exec/adapt_single.c \
	$(SRC_DIR)/exec/builtin_child.c \
	$(SRC_DIR)/exec/builtin_dispatch.c \
	$(SRC_DIR)/exec/builtin_parent.c \
	$(SRC_DIR)/exec/external_exec.c \
	$(SRC_DIR)/exec/external_path.c \
	$(SRC_DIR)/exec/fds.c \
	$(SRC_DIR)/exec/heredoc.c \
	$(SRC_DIR)/exec/heredoc_child.c \
	$(SRC_DIR)/exec/heredoc_child_helpers.c \
	$(SRC_DIR)/exec/heredoc_expand.c \
	$(SRC_DIR)/exec/heredoc_expand2.c \
	$(SRC_DIR)/exec/status_wait.c \
	$(SRC_DIR)/utils/arr_utils.c \
	$(SRC_DIR)/utils/str_utils.c \
	$(SRC_DIR)/utils/err_utils.c \
	$(SRC_DIR)/utils/exit_utils.c \
	$(SRC_DIR)/utils/exit_utils_2.c \
	$(SRC_DIR)/utils/dequote_all.c \
	$(SRC_DIR)/utils/ms_close_extra_fds.c \
	$(SRC_DIR)/utils/fd_utils.c \
	$(SRC_DIR)/utils/utils_main.c \
	$(SRC_DIR)/utils/global_status2.c \
	$(SRC_DIR)/utils/external_exec_utils.c \
	$(SRC_DIR)/utils/utils_signals.c

# === Sorgente main (root) ===
MAIN        = main.c

# === Oggetti (mantenendo la struttura in obj/) ===
OBJ_SRC     = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_MAIN    = $(OBJ_DIR)/main.o
OBJ         = $(OBJ_SRC) $(OBJ_MAIN)

# === Colori ===
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
RED     = \033[1;31m
RESET   = \033[0m

# === Comandi ===
RM          = rm -rf

# === Regole ===
all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)🔧 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(LIBS) -o $(NAME) && \
	 echo "$(GREEN)✅ Build completata con successo!$(RESET)" || \
	 echo "$(RED)❌ Errore nel linking di $(NAME)!$(RESET)"

# === Compilazione sorgenti ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🛠 Compilazione:$(RESET) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ && \
	 echo "$(GREEN)   ✔ Creato: $@$(RESET)" || \
	 echo "$(RED)   ✘ Errore nella compilazione di: $<$(RESET)"

$(OBJ_DIR)/main.o: $(MAIN) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🛠 Compilazione:$(RESET) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ && \
	 echo "$(GREEN)   ✔ Creato: $@$(RESET)" || \
	 echo "$(RED)   ✘ Errore nella compilazione di: $<$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# === Libft ===
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

# === Pulizia ===
clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)🧹 Pulizia oggetti...$(RESET)"
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)✅ Cartella '$(OBJ_DIR)' rimossa.$(RESET)"

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)🧹 Pulizia completa...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✅ Binario '$(NAME)' rimosso.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
