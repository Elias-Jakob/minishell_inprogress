#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "enums.h"
# include "structs.h"

// // ejakob: didnt compile without it... :)
// # include "includes.h"

// variable_parser.c
size_t		find_variable_end(char *input, size_t dollar_pos, int *is_bracket);
char		*extract_variable_name(char *input, size_t dollar_pos, size_t var_end,
								int	is_bracket);

//variable_resolver.c
char		*resolve_variable_value(char *var_name, char **env, int exit_status);
void		cleanup_variable_memory(char *var_name, char *var_value);
int			needs_special_cleanup(char *var_name);

//string_builder.c
char		*build_expanded_string(char *input, size_t dollar_pos, size_t var_end,
									char *var_value, int is_bracket);

//expansion_env_var.c
char		*expand_env_var(char *input, size_t dollar_pos, char **env, int last_exit_status);

//word_processor.c
int			process_word_token(t_token *token, t_cmd **current_cmd, t_cmd **cmd_head, char **env, int last_exit_status);

//pipe_processor.c
int			process_pipe_token(t_cmd **current_cmd);

//redirection_processor.c
int			process_redirection_token(t_list **token_node, t_cmd **current_cmd, t_cmd **cmd_head);

//heredoc
void		cleanup_heredoc(t_redirs *redir);
char		*create_heredoc_temp_file(void);
int			read_heredoc_input(int fd, char *delimiter);
int			create_heredoc_file(char *delimiter, char **tmp_file_path);

int			ensure_redirection_exists(t_cmd *cmd);
int			validate_redirection_sequence(t_list *token_node);
int			validate_pipe_sequence(t_list *token_node);
int			validate_token_sequence(t_list *token_list);
int			add_argument_to_command(t_cmd *cmd, t_token *token, char **env, int exit_status);
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


int			handle_input_redirection(t_cmd *cmd, t_token *file_token);
int			handle_output_redirection(t_cmd *cmd, t_token *file_token);
int			handle_append_redirection(t_cmd *cmd, t_token *file_token);
int			handle_heredoc_redirection(t_cmd *cmd, t_token *delimiter_token);

int			create_heredoc_file(char *delimiter, char **tmp_file_path);

int			parser(t_list *token_list, t_cmd **cmd_head, char **env, int exit_status);

char		*expand_variables_in_token(char *token_value, char **env, int last_exit_status);
char		*process_token_expansion(t_token *token, char **env, int last_exit_status);

#endif
