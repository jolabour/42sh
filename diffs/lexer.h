[1mdiff --git a/includes/lexer.h b/includes/lexer.h[m
[1mindex 736139e..e645ec0 100644[m
[1m--- a/includes/lexer.h[m
[1m+++ b/includes/lexer.h[m
[36m@@ -6,7 +6,7 @@[m
 /*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */[m
 /*                                                +#+#+#+#+#+   +#+           */[m
 /*   Created: 2019/04/12 07:17:54 by geargenc          #+#    #+#             */[m
[31m-/*   Updated: 2019/04/12 08:50:23 by geargenc         ###   ########.fr       */[m
[32m+[m[32m/*   Updated: 2019/04/12 10:43:19 by geargenc         ###   ########.fr       */[m
 /*                                                                            */[m
 /* ************************************************************************** */[m
 [m
[36m@@ -18,6 +18,8 @@[m
 [m
 typedef struct s_42sh		t_42sh;[m
 [m
[32m+[m[32m# define EOFWHILELOOK "42sh: unexpected EOF while looking for matching `"[m
[32m+[m
 /*[m
 **							enum[m
 */[m
