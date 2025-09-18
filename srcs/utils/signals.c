#include "../../includes/minishell.h"

sig_atomic_t	g_sig_received = 0;

void	default_sigint_handler(int signal)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig_received = signal;
}

void	exec_sigint_handler(int signal)
{
	printf("\n");
	g_sig_received = signal;
}

void	heredoc_sigint_handler(int signal)
{
	g_sig_received = signal;
}

int	handle_pending_signals(t_exec_context *exec_context)
{
	if (g_sig_received)
	{
		exec_context->exit_status = 130;
		// printf("g_sig_received = %d\n", g_sig_received);
		g_sig_received = 0;
		return (1);
	}
	return (0);
}

void	change_signal_settings(void (*hander_func)(int),
	t_exec_context *exec_context)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = hander_func;
	if (sigemptyset(&sa_int.sa_mask) == -1)
		fatal_error(exec_context, "setting signals: sigemptyset failed");
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		fatal_error(exec_context, "setting signals: sigaction failed");
}

void	setup_signals(void)
{
	struct sigaction	sa_quit;

	change_signal_settings(default_sigint_handler, NULL);
	sa_quit.sa_handler = SIG_IGN;
	if (sigemptyset(&sa_quit.sa_mask) == -1)
	{
		perror("setup_signals: sigemptyset failed");
		exit(1);
	}
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("setup_signals: sigaction failed");
		exit(1);
	}
}
