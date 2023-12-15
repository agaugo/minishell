/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/12/15 15:39:03 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[31m\033[1m[ MINISHELL ]\033[0m\033[96m$\033[0m "

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# include "../libft/libft.h"
# include "tokenizer.h"

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <ctype.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_print_new_prompt;

typedef struct data {
	char			**envp;
	char			*user_input;
	int				last_exit_code;
	t_token_t		*tokens;
	int				redirect;
	int				pipe[2];
	char			*heredoc_tmp_file;
	char			*last_path;
	struct termios	*original_termios;
	int				std_out;
	int				std_in;
}					t_data;

typedef struct s_quote_vars
{
	size_t	*i;
	size_t	*j;
	int		*in_single_quote;
	int		*in_double_quote;
	char	*cleaned_str;
}			t_quote_vars;

typedef struct s_pid_node
{
	pid_t				pid;
	struct s_pid_node	*next;
}						t_pid_node;

typedef struct exec_data {
	pid_t		pid;
	t_token_t	*current;
	t_token_t	*next_command;
	char		**args;
	int			fds[2];
	int			in_fd;
	int			is_pipe;
	int			is_redirect;
	t_token_t	*first_command_token;
	int			num_pids;
	t_pid_node	*pid_list;
	int			builtin_exit_status;
	int			has_builtin;
	int			last_is_builtin;
}			t_exec_t_data;

typedef struct exp_data {
	int		i;
	int		j;
	int		k;
	int		do_free;
}			t_exp_t_data;

typedef struct echo_data {
	int		flag_n;
	int		first_word;
	int		stdout_backup;
	int		should_print_space;
	int		fd;
}			t_echo_data;

struct termios	enable_noncanonical_mode(void);
void			ms_make_data_struct(t_data *data, char **envp);
void			ms_check_redirect(t_data *data);
t_token_t		*ms_tokenizer(t_data data);
void			parse_special_tokens(char **current, t_token_t **head,
					t_token_t **current_token);
void			parse_regular_tokens(char **current, t_token_t **head,
					t_token_t **current_token);
t_tokentype_t	parse_pipe_token(char **current);
t_tokentype_t	parse_redirect_token(char **current);
t_tokentype_t	parse_redirect_token2(char **current);
t_tokentype_t	parse_quote_token(char **current);
t_tokentype_t	parse_word_token(char **current);
int				ms_is_whitespace(char c);
t_token_t		*init_new_token(char *start, char *current, t_tokentype_t type);
char			*ms_clean_quotes(t_quote_vars *vars, const char *str);
int				ms_run_builtin(t_data *data, char **args, t_token_t *current);
int				ms_is_builtin_command(char *command);
void			ms_resolve_command_paths(t_data *data);
int				ms_is_directory(const char *path);
int				ms_set_command_path(char **allpath, t_token_t *current);
char			**ms_get_full_args(t_token_t *start_token,
					t_token_t *end_token);
t_token_t		*ms_handle_heredoc(t_data *data, t_token_t *temp,
					t_token_t *first_command_token);
t_token_t		*ms_check_redirects(t_exec_t_data *cmd_data, t_token_t *cmd);
int				ms_setup_redirection(t_token_t *tokens);
void			ms_throw_error(t_data *data, t_token_t *current);
char			*ms_expand_tilde(t_data *data, char *token_value);
char			*ms_expand_dollarsign(t_data *data, char *token_value);
void			ms_expand_variable(t_data *data, t_token_t *current_token);
void			ms_expand_tokens(t_data *data, t_token_t *current_token);
void			update_token_type(t_token_t *current_token);
void			remove_token(t_token_t **head, t_token_t *prev_token,
					t_token_t *current_token);
void			remove_empty_token(t_data *data, t_token_t **prev_token,
					t_token_t **current_token);
void			remove_next_token(t_token_t *current);
char			*merge_token_values(t_token_t *current, t_token_t *next);
void			merge_connected_tokens(t_data *data, t_quote_vars *vars);
char			*ms_call_expand(t_data *data, char *token_value);
char			*ms_expand_exit_code(t_data *data, char *token_value,
					int *do_free, int i);
void			print_env(t_data *data);
void			update_env(t_data *data, char *key, char *new_assignment);
void			*allocate_memory(size_t buffer_size);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strchr(const char *str, int character);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strndup(const char *str, size_t n);
void			*memory_realloc(void *ptr, size_t new_size);
int				ms_get_env_size(char **envp);
void			ms_add_to_env(t_data *data, char *key);
void			executeBuiltin(struct termios *_oldTermios, t_token_t *_token);
int				main(int argc, char *argv[], char *envp[]);
void			ms_handle_error(int exit_code, char *message);
int				restoreTerminal(struct termios *_oldTermios);
void			ms_print_env_variables(t_data *data);
void			ms_cd_command(t_data *data, t_token_t *token);
void			ms_echo_command(t_data *data, t_token_t *token);
void			ms_exit_shell(t_data *data, t_token_t *token);
void			ms_export_command(t_data *data, t_token_t *token);
void			ms_pwd_command(t_data *data);
void			ms_unset_command(t_data *data, t_token_t *token);
int				ms_set_terminal_settings(t_data *data);
char			**ms_clone_envp(char **envp);
void			ms_handle_ctrl_c(int _signalNumber);
void			ms_handle_ctrl_d(t_data *data);
void			ms_handle_ctrl_backspace(int _signalNumber);
int				ms_init_signals(void);
int				ms_find_env_index(char **envp, const char *key);
char			*read_file_content(const char *filename);
void			remove_intermediate_input_redirections(t_data *data);
t_token_t		*ms_tokenizer(t_data data);
void			ms_expander(t_data *data);
void			ms_redirect(t_data *data);
void			ms_redirect_out_append(t_data *data);
void			ms_identify_command(t_data *data);
void			ms_execute_command(t_data *data, char **_array);
void			ms_heredoc(t_data *data, t_token_t *token);
char			*ms_get_current_working_dir(void);
int				ms_load_fd(t_token_t *_token, t_tokentype_t _direction);
void			ms_handle_redirect(t_token_t *_token, t_tokentype_t _direction);
void			ms_free_2d_array(char **_array);
char			*ft_getenv(char **envp, char *key);
void			ms_check_pipe(t_data *data);
void			ms_execute_commands(t_data *data);
int				setup_redirection(t_token_t *tokens);
void			free_token_list(t_token_t *head);
void			wipe_data_struct(t_data *data);
void			free_memory(void *buffer);
char			*ft_strjoin_free(char *s1, char *s2);
char			*create_assignment(char *key, char *value);
void			process_quotes(t_quote_vars *vars, t_token_t *current_token);
int				ms_exe_check_syntax(t_data *data);
void			ms_wait_and_receive(t_data *data, t_exec_t_data *cmd_data);
void			free_pid_list(t_pid_node *head);
void			add_pid(t_exec_t_data *cmd_data, pid_t new_pid);
void			ms_builtin_exitcode(t_data *data, t_exec_t_data *cmd_data);

#endif
