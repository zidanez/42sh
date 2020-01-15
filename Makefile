# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgranule <hgranule@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/06 08:51:16 by hgranule          #+#    #+#              #
#    Updated: 2019/12/17 20:37:07 by hgranule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re, make_lft

# ************************************************************************** #
#                           colors                                           #
# ************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PINK = \033[35m
AQUA = \033[36m
GREY = \033[37m
UNDERLINE = \033[4m
ESCN = \033[0m

# ************************************************************************** #
#                           Configuration                                    #
# ************************************************************************** #
NAME = 42sh
FLAGS = -Wall -Wextra -Werror

WS_PATH = $(shell pwd)
SRC_PATH = $(WS_PATH)/sources/
OBJ_PATH = $(WS_PATH)/objects/
INC_PATH = $(WS_PATH)/includes/ $(WS_PATH)/includes/printf/

SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))
INC = $(addprefix -I, $(INC_PATH))

SRC_FILES = sh_main.c sh_launch.c sh_launch_srcs.c \
			ft_flagsparser.c exe_sys/exe_calls.c free_me/rms.c free_me/rms_2.c \
			ft_basename.c exe_sys/exe_binaries.c exe_sys/exe_builtns.c \
			exe_sys/exe_load_save_rdr.c exe_sys/exe_rdr_hered.c \
			exe_sys/exe_redirs.c parser/prs_arch.c parser/prs_args.c exe_sys/exe_subshell.c \
			parser/prs_instructions.c parser/prs_rdrs.c parser/prs_types.c \
			env/env_init.c env/env_get_variable.c env/env_set_variable.c env/env_unset_variable.c env/env_unset_func.c env/env_get_keys.c\
			bltns/bltn_init.c bltns/bltn_setenv.c bltns/bltn_env.c bltns/bltn_getenv.c bltns/bltn_unsetenv.c \
			bltns/bltn_exit.c bltns/bltn_pwd.c bltns/bltn_export.c bltns/bltn_unset.c \
			bltns/bltn_type/bltn_type.c bltns/bltn_type/bltn_type_free.c bltns/bltn_type/bltn_type_alias_check.c bltns/bltn_type/bltn_type_bins_check.c\
			bltns/bltn_type/bltn_type_help.c bltns/bltn_echo.c \
			exe_sys/exe_bckgr.c \
			bltns/bltn_cd/main_cd.c bltns/bltn_cd/parse_path.c bltns/bltn_cd/chdir_cd.c \
			exe_sys/exe_funcs.c parser/prs_and_or.c parser/prs_assigm.c \
			parser/prs_funcs.c parser/prs_if_while.c parser/prs_skipers.c \
			parser/prs_error.c parser/prs_core_setter.c parser/prs_background.c \
			parser/prs_get_deref.c parser/prs_for.c parser/prs_rdrs_support.c parser/prs_arch_support.c \
			\
			bltns/math/bltn_math.c bltns/math/math_bases_in.c bltns/math/math_tokenize.c \
			bltns/math/math_polish_reverse.c bltns/math/math_operations.c \
			bltns/math/math_hierarchy_in.c bltns/math/math_calculate.c \
			bltns/math/math_hierarchy_init.c bltns/math/math_tokenize_2.c \
			bltns/math/math_tokenize_3.c bltns/math/math_errors.c \
			bltns/math/math_environment.c bltns/math/math_memory.c \
			bltns/math/math_operands.c bltns/math/math_checkers.c \
			bltns/math/math_optable.c bltns/math/math_useful_func.c \
			bltns/math/math_obliczac.c \
			\
			bltns/bltn_test/bltn_test.c bltns/bltn_test/bltn_test_parser/bltn_test_fileflgs.c\
			bltns/bltn_test/bltn_test_expr/bltn_test_expr.c bltns/bltn_test/bltn_test_expr/test_expr.c bltns/bltn_test/bltn_test_expr/test_expr_action.c\
			bltns/bltn_test/bltn_test_file/bltn_test_file.c bltns/bltn_test/bltn_test_file/test_checkfile.c\
			\
			sys_tools/sys_init.c sys_tools/sys_pipes.c parser/prs_subsh.c \
			sys_tools/sys_proc_wait.c sys_tools/sys_errors.c sys_tools/sys_io.c \
			sys_tools/sys_touch.c sys_tools/sys_argc.c sys_tools/sys_token_string.c \
			sys_tools/sys_exprs_strings.c sys_tools/sys_sigs_dfl_init.c \
			sys_tools/sys_hot_proc.c sys_tools/sys_wait_ps.c \
			sys_tools/sys_exprs_strings_2.c sys_tools/sys_exprs_strings_3.c \
			sys_tools/sys_prompt.c \
			\
			bltns/bltn_jobs/bltn_jobs.c bltns/bltn_jobs/bltn_fg_bg.c bltns/bltn_set.c \
			bltns/bltn_jobs/bltn_fg_bg_helper.c bltns/bltn_jobs/bltn_jobs_entries.c \
			bltns/bltn_jobs/bltn_jobs_help.c bltns/bltn_source.c \
			\
			$(addprefix gui/, $(GUI_FILES)) \
			$(LIBFT_SRCS) \
			sys_tools/sys_config.c sys_tools/sys_files.c sys_tools/sys_proc_tables.c \
			env/env_get_bins/env_get_bins.c \
			\
			lexer/lx_backgr_offset.c lexer/lx_script_init.c \
			lexer/lx_script_parse.c lexer/lx_cleaners.c \
			lexer/lx_comm_parse.c lexer/lx_envar_parse.c \
			lexer/lx_func_parse.c \
			lexer/lx_hedoc_parse.c lexer/lx_lexer.c \
			lexer/lx_math_parse.c lexer/lx_metatree.c \
			lexer/lx_input_finished.c lexer/lx_proc_parse.c \
			lexer/lx_quots_parse.c lexer/lx_redir_init.c \
			lexer/lx_redir_parse.c lexer/lx_regulars.c \
			lexer/lx_sep_parse.c lexer/lx_subsh_parse.c \
			lexer/lx_tokenizer.c lexer/lx_usefull_func.c \
			lexer/lx_validators.c lexer/lx_input_codes.c \
			lexer/lx_parse_func.c lexer/lx_deref_parse.c \
			lexer/lx_syntax_err.c lexer/lx_skippers.c \
			lexer/lx_skippers_2.c lexer/lx_checkers.c \
			lexer/lx_checkers_2.c lexer/lx_checkers_3.c \
			lexer/lx_cutters.c lexer/lx_first_layer.c \
			lexer/lx_make_clear.c lexer/lx_second_layer.c \
			lexer/lx_mirror_parse.c lexer/lx_portal.c \
			lexer/lx_regulars_2.c lexer/lx_regulars_3.c \
			lexer/lx_substitutors.c lexer/lx_validators_2.c \
			lexer/lx_constructors.c lexer/lx_graph_func.c \
			lexer/lx_input_check.c lexer/lx_input_check_2.c \
			lexer/lx_input_check_3.c lexer/lx_input_check_4.c \
			lexer/lx_metabranches.c lexer/lx_metabranch.c \
			lexer/lx_redir_init_2.c lexer/lx_redir_parse_2.c \
			lexer/lx_redir_trace.c lexer/lx_script_trace.c \
			lexer/lx_script_in_2.c lexer/lx_script_in_3.c \
			lexer/lx_script_in_4.c lexer/lx_script_in_5.c \
			lexer/lx_args_check.c lexer/lx_redir_parse_3.c \
			lexer/lx_apof_parse.c \
			\
			printf/ft_insert_c.c printf/ft_insert_doubles.c \
			printf/ft_bf_ariphmetic.c printf/ft_bf_cmp.c \
			printf/ft_bf_io.c printf/ft_bf_shifts.c \
			printf/ft_bigint.c printf/ft_format_parser.c \
			printf/ft_help_insert_b.c printf/ft_insert_b.c \
			printf/ft_insert_p.c printf/ft_insert_percent.c \
			printf/ft_insert_r.c printf/ft_insert_s.c \
			printf/ft_insert_spec.c printf/ft_printf.c \
			printf/ft_putll_base_spec.c \
			\
			options/sh_options_conds.c options/sh_options_fsm.c \
			options/sh_options_handlers.c \
			ft_dlst_helper.c sys_tools/sys_core_set.c sh_history_rl.c \
			\
			env/env_cmd_hash.c sys_tools/sys_siglog.c \
			env/env_get_darr_from_tree.c \
			\
			bltns/hash/bltn_hash.c bltns/hash/bltn_setreset.c \
			exe_sys/exe_checkers.c bltns/hash/bltn_hash_actions.c \
			exe_sys/exe_heredoc_getline.c

ADD_OBJ = $(addprefix $(OBJ_PATH), exe_sys free_me parser env bltns aliases \
	bltns/math sys_tools gui env/env_get_bins bltns/bltn_type bltns/bltn_cd lexer \
	printf bltns/bltn_jobs options bltns/hash bltns/bltn_test \
	bltns/bltn_test/bltn_test_parser bltns/bltn_test/bltn_test_expr bltns/bltn_test/bltn_test_file \
	Libft)

LIBFT_SRCS = $(addprefix Libft/, $(LIBFT_FILES))
LIBFT_FILES = dbg_timer.c\
	dbg_timer_points.c\
	dstr_insert.c\
	dstr_mem.c\
	dstr_slice.c\
	dstr_srch.c\
	dstr_swpc.c\
	dstr_trim.c\
	ft_atoi.c\
	ft_atoi_base.c\
	ft_atoll_base.c\
	ft_avl_api_del.c\
	ft_avl_api_info.c\
	ft_avl_api_nodecr.c\
	ft_avl_balance_blt.c\
	ft_avl_edit_blt.c\
	ft_avl_srch_blt.c\
	ft_avl_utils_blt.c\
	ft_bzero.c\
	ft_countw_delim.c\
	ft_dlst_count.c\
	ft_dlst_gnsort.c\
	ft_dlst_maparr.c\
	ft_dlst_rgnsort.c\
	ft_dlstcut.c\
	ft_dlstdel.c\
	ft_dlstget.c\
	ft_dlstinsert.c\
	ft_dlstnew.c\
	ft_dlstpush.c\
	ft_dlstrget.c\
	ft_dlstrmelem.c\
	ft_dlstshift.c\
	ft_dlstswap.c\
	ft_dlstunshift.c\
	ft_hexdump.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_isspace.c\
	ft_itoa.c\
	ft_lbuffer_io.c\
	ft_lltoa_base.c\
	ft_lstadd.c\
	ft_lstdel.c\
	ft_lstdelone.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_lstnew.c\
	ft_mem_mem.c\
	ft_memalloc.c\
	ft_memccpy.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memdel.c\
	ft_memdup.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar.c\
	ft_putchar_fd.c\
	ft_putendl.c\
	ft_putendl_fd.c\
	ft_putll_base_fd.c\
	ft_putnbr.c\
	ft_putnbr_fd.c\
	ft_putstr.c\
	ft_putstr_fd.c\
	ft_realloc.c\
	ft_strcat.c\
	ft_strcate.c\
	ft_strccpy.c\
	ft_strchr.c\
	ft_strclr.c\
	ft_strcmp.c\
	ft_strcpy.c\
	ft_strdel.c\
	ft_strdup.c\
	ft_strequ.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlen.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strncat.c\
	ft_strncmp.c\
	ft_strncpy.c\
	ft_strnequ.c\
	ft_strnew.c\
	ft_strnlen.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strsplit.c\
	ft_strsplits.c\
	ft_strstr.c\
	ft_strsub.c\
	ft_strtrim.c\
	ft_tolower.c\
	ft_toupper.c\
	get_next_line.c\
	hs_hashfuncs.c\
	ht_add.c\
	ht_getdel.c\
	ht_info.c\
	ht_new.c\
	ht_resize.c

GUI_FILES = sh_control_term.c sh_dir_content.c \
			sh_rewrite.c sh_rewrite_help.c sh_rewrite_clip.c\
			dstr.c ft_concat.c sh_put_col.c sh_darr.c \
			match.c sh_reg_expr.c sh_reg_expr_help.c sh_reg_help.c sh_reg_expr_help2.c sh_type_input.c \
			sh_histr.c sh_histr_help.c sh_search_his.c sh_search_his_help.c \
			sh_readline.c sh_readline_help.c clip.c \
			sh_put_col_help.c sh_dir_content_help.c \
			sh_move_insertion_point.c \
			gui_errors.c \
			sh_tab.c sh_tab_help.c slicer_unite_buf.c sh_get_overlap.c sh_get_file_help.c sh_get_cmd_help.c sh_get_var_help.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

# ************************************************************************** #
#                                   Rules                                    #
# ************************************************************************** #

all: $(NAME)


$(NAME): $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(INC) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "$(RED)$(UNDERLINE)CREATING >> $@$(ESCN)"
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(ADD_OBJ)
	@gcc $(FLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all
