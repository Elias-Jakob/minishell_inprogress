#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

int			ensure_redirection_exists(t_cmd *cmd);
int			validate_redirection_sequence(t_list *token_node);
int			add_argument_to_command(t_cmd *cmd, t_token *token);
int			count_argv_size(char **argv);
t_redirs	*init_redirection(void);

t_token		*get_current_token(t_list *token_list);
t_token		*get_next_token(t_list *token_list);
t_list		*advance_token_node(t_list *current_node);
int			is_redirection_token(t_token *token);
int			is_token_builtin(t_token *token);

t_cmd		*ensure_current_command_exists(t_cmd **current_cmd, t_cmd **cmd_head);
int			append_command_to_list(t_cmd *new_cmd, t_cmd **cmd_head);
t_cmd		*create_new_command(t_token *token);

int			process_word_token(t_token *token, t_cmd **current_cmd, t_cmd **cmd_head);
int			process_pipe_token(t_cmd **current_cmd);
int			process_redirection_token(t_list **token_node, t_cmd **current_cmd, t_cmd **cmd_head);

int			handle_input_redirection(t_cmd *cmd, t_token *file_token);
int			handle_output_redirection(t_cmd *cmd, t_token *file_token);
int			handle_append_redirection(t_cmd *cmd, t_token *file_token);
int			handle_heredoc_redirection(t_cmd *cmd, t_token *delimiter_token);

void		cleanup_heredoc(t_redirs *redir);
int			create_heredoc_file(char *delimiter, char **tmp_file_path);

int			parser(t_list *token_list, t_cmd **cmd_head);

#endif
