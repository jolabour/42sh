/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:16:04 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/20 02:47:05 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEBUG_H

# define FT_DEBUG_H

# include "sh.h"

char					*g_tokstr[] =
{
	"NONE",
	"WORD",
	"ASSIGNMENT_WORD",
	"NAME",
	"NEWLINE",
	"IO_NUMBER",
	"OP",
	"PIPE",
	"AND",
	"SEMI",
	"GREAT",
	"LESS",
	"LPAR",
	"RPAR",
	"AND_IF",
	"OR_IF",
	"DLESS",
	"DGREAT",
	"LESSAND",
	"LESSANDDASH",
	"GREATAND",
	"GREATANDDASH",
	"LESSGREAT",
	"DLESSDASH",
	"CLOBBER",
	"LBRACE",
	"RBRACE",
	"COMMAND"
};

char					*g_txtstr[] =
{
	"TXT_NONE",
	"TEXT",
	"TILDE",
	"VAR",
	"BRACE_VAR",
	"CMD_SUB",
	"CMD_SUB_BQUOTE",
	"ARTH_EXPR"
};

char					*g_matchstr[] =
{
	"MATCH_NONE",
	"MATCH_TEXT",
	"MATCH_WCARD",
	"MATCH_QMARK",
	"MATCH_HOOK",
	"MATCH_RHOOK"
};

#endif
