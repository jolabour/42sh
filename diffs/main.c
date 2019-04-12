[1mdiff --git a/src/core/main.c b/src/core/main.c[m
[1mindex ed211a1..6926d37 100644[m
[1m--- a/src/core/main.c[m
[1m+++ b/src/core/main.c[m
[36m@@ -6,13 +6,40 @@[m
 /*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */[m
 /*                                                +#+#+#+#+#+   +#+           */[m
 /*   Created: 2018/07/29 04:21:23 by jolabour          #+#    #+#             */[m
[31m-/*   Updated: 2019/04/12 02:49:12 by jolabour         ###   ########.fr       */[m
[32m+[m[32m/*   Updated: 2019/04/12 11:37:25 by geargenc         ###   ########.fr       */[m
 /*                                                                            */[m
 /* ************************************************************************** */[m
 [m
 #include "sh.h"[m
 #include "ft_global.h"[m
 [m
[32m+[m[32mvoid		ft_init(t_42sh *shell)[m
[32m+[m[32m{[m
[32m+[m	[32mshell->pid = getpid();[m
[32m+[m	[32mshell->pgid = getpgrp();[m
[32m+[m	[32mshell->foreground = 0;[m
[32m+[m	[32msignal(SIGINT, &ft_handler);[m
[32m+[m	[32mif (isatty(STDIN_FILENO))[m
[32m+[m	[32m{[m
[32m+[m		[32mwhile (tcgetpgrp(STDIN_FILENO) != shell->pgid)[m
[32m+[m			[32mkill(-shell->pgid, SIGTTIN);[m
[32m+[m		[32mshell->pgid = 0;[m
[32m+[m		[32mft_init_signals();[m
[32m+[m		[32msetpgid(shell->pid, shell->pid);[m
[32m+[m		[32mtcsetpgrp(STDIN_FILENO, shell->pid);[m
[32m+[m		[32mtcgetattr(STDIN_FILENO, &(shell->term));[m
[32m+[m		[32mshell->foreground = 1;[m
[32m+[m	[32m}[m
[32m+[m	[32mshell->forked = 0;[m
[32m+[m	[32mshell->jobs = NULL;[m
[32m+[m	[32mshell->current = NULL;[m
[32m+[m	[32mshell->retval = 0;[m
[32m+[m	[32mshell->tmp_fds = NULL;[m
[32m+[m	[32mshell->last_bg = 0;[m
[32m+[m	[32mshell->exit_lock = 0;[m
[32m+[m	[32mshell->buffer_mode = false;[m
[32m+[m[32m}[m
[32m+[m
 int			main(int argc, char **argv, char **env)[m
 {[m
 	t_42sh	sh;[m
