[1mdiff --git a/Makefile b/Makefile[m
[1mindex 66e3056..ff1cd95 100644[m
[1m--- a/Makefile[m
[1m+++ b/Makefile[m
[36m@@ -32,7 +32,20 @@[m [mSRCS		= core/main.c edit_line/list.c core/process.c utils/getenv.c \[m
 			  ft_ast/ft_ast_is.c ft_ast/ft_ast_push_one_back.c \[m
 			  ft_ast/ft_ast_redir.c ft_ast/ft_ast_separators.c \[m
 			  ft_ast/ft_ast_tools.c \[m
[31m-			  geff/main.c geff/ft_expanse.c \[m
[32m+[m			[32m  ft_exe/ft_exe_assigns.c ft_exe/ft_exe_builtin.c \[m
[32m+[m			[32m  ft_exe/ft_exe_command.c ft_exe/ft_exe_compound.c \[m
[32m+[m			[32m  ft_exe/ft_exe_exit.c ft_exe/ft_exe_file.c \[m
[32m+[m			[32m  ft_exe/ft_exe_redir.c ft_exe/ft_exe_redirand.c \[m
[32m+[m			[32m  ft_exe/ft_exe_redirerror.c ft_exe/ft_exe_separators.c \[m
[32m+[m			[32m  ft_exe/ft_exe_tmpfd.c \[m
[32m+[m			[32m  ft_jobs/ft_jobs_any.c ft_jobs/ft_jobs_check.c \[m
[32m+[m			[32m  ft_jobs/ft_jobs_cmdline1.c ft_jobs/ft_jobs_cmdline2.c \[m
[32m+[m			[32m  ft_jobs/ft_jobs_error.c ft_jobs/ft_jobs_get.c \[m
[32m+[m			[32m  ft_jobs/ft_jobs_launch.c ft_jobs/ft_jobs_manage.c \[m
[32m+[m			[32m  ft_jobs/ft_jobs_remove.c ft_jobs/ft_jobs_report.c \[m
[32m+[m			[32m  ft_jobs/ft_jobs_signals.c ft_jobs/ft_jobs_status.c \[m
[32m+[m			[32m  ft_jobs/ft_jobs_tools.c \[m
[32m+[m			[32m  geff/ft_expanse.c \[m
 			  histo/init_file_history.c histo/parser_history.c \[m
 			  edit_line/move_histo.c histo/substitute_history.c \[m
 			  builtin/test/test.c builtin/test/test_bcdef.c builtin/test/test_glprs.c \[m
[36m@@ -46,7 +59,8 @@[m [mSRCS		= core/main.c edit_line/list.c core/process.c utils/getenv.c \[m
 			  histo/ctrlr_action/ctrlr_action.c builtin/set/set.c builtin/unset/unset.c builtin/export/export.c armand/ft_check_exp_ari.c armand/ft_erase_space.c builtin/export/print_export.c \[m
 			  armand/ft_logic_op.c armand/ft_true_op.c armand/ft_check_var.c armand/ft_itoa_exp_ari.c \[m
 			  armand/ft_math_op.c armand/exp_ari.c builtin/unset/list_unset.c \[m
[31m-			  builtin/jobs/jobs.c builtin/exit/exit.c utils/ft_continue_line.c \[m
[32m+[m			[32m  builtin/jobs/jobs.c builtin/jobs/fg.c builtin/jobs/bg.c \[m
[32m+[m			[32m  builtin/exit/exit.c utils/ft_continue_line.c utils/ft_get_opts.c \[m
 			  utils/tools.c utils/var.c utils/check.c histo/list_history.c histo/search_history.c \[m
 			  builtin/cd/builtin_cd.c builtin/cd/cd_exec.c builtin/cd/dot_cd.c builtin/cd/list_cd.c builtin/cd/opt_cd.c \[m
 			  builtin/cd/utils_cd.c[m
[36m@@ -87,8 +101,10 @@[m [m$(OBJS_DIR)/%.o: %.c[m
 	@mkdir -p $(OBJS_DIR)/core[m
 	@mkdir -p $(OBJS_DIR)/edit_line[m
 	@mkdir -p $(OBJS_DIR)/histo[m
[31m-	@mkdir -p $(OBJS_DIR)/ft_lexer[m
 	@mkdir -p $(OBJS_DIR)/ft_ast[m
[32m+[m	[32m@mkdir -p $(OBJS_DIR)/ft_exe[m
[32m+[m	[32m@mkdir -p $(OBJS_DIR)/ft_jobs[m
[32m+[m	[32m@mkdir -p $(OBJS_DIR)/ft_lexer[m
 	@mkdir -p $(OBJS_DIR)/hashtable[m
 	@mkdir -p $(OBJS_DIR)/utils[m
 	@mkdir -p $(OBJS_DIR)/parser[m
