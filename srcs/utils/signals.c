#include "../../includes/minishell.h"

sig_atomic_t	g_sig_received = 0;

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_sig_received = signal;
}

static void	signal_handler_heredoc(int signal)
{
	g_sig_received = signal;
}

int	handle_pending_signals(t_exec_context *exec_context)
{
	(void)exec_context;
	if (g_sig_received)
	{
		exec_context->exit_status = 130;
		printf("g_sig_received = %d\n", g_sig_received);
		g_sig_received = 0;
		return (1);
	}
	return (0);
}

void	setup_signals(int is_heredoc)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	if (is_heredoc)
		sa.sa_handler = &signal_handler_heredoc;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		perror("setup_signals: sigemptyset failed");
		exit(1);
	}
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("setup_signals: sigaction failed");
		exit(1);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("setup_signals: sigaction failed");
		exit(1);
	}
}
