#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_error
{
    ERR_NONE,
    ERR_CMD_NOT_FOUND,      // 127
    ERR_PERMISSION_DENIED,  // 126
    ERR_PIPE_FAIL,
    ERR_FORK_FAIL,
    ERR_FILE_NOT_FOUND
}   t_error;

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_REDIRECT_IN,
	TK_REDIRECT_OUT,
	TK_APPEND_OUT,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
	TK_HEREDOC,
	TK_ENV,
	TK_ERROR
}	t_token_type;

typedef enum e_builtin
{
    BUILTIN_NONE,
    BUILTIN_CD,
    BUILTIN_ECHO,
    BUILTIN_PWD,
    BUILTIN_EXPORT,
    BUILTIN_UNSET,
    BUILTIN_ENV,
    BUILTIN_EXIT
}   t_builtin;

typedef enum e_redir_type
{
	RD_STD,
	RD_FILE,
	RD_APPEND_OUT,
	RD_FD,
	RD_PIPE,
	RD_HEREDOC
}	t_redirs_type;

#endif
