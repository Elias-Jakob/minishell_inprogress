#include "../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t i;
	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;
	char *d;
	const char *s;
	if (!dst || !src)
		return (dst);
	d = dst;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup_min(const char *s)
{
	size_t len;
	char *res;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s, len);
	res[len] = '\0';
	return (res);
}

char	*ft_strjoin_min(const char *s1, const char *s2)
{
	size_t l1;
	size_t l2;
	char *res;
	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = malloc(l1 + l2 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, l1);
	ft_memcpy(res + l1, s2, l2);
	res[l1 + l2] = '\0';
	return (res);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t i;
	size_t j;
	if (!s || !reject)
		return (0);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	size_t l1;
	size_t l2;
	size_t l3;
	char *res;
	if (!s1 || !s2 || !s3)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	l3 = ft_strlen(s3);
	res = malloc(l1 + l2 + l3 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, l1);
	ft_memcpy(res + l1, s2, l2);
	ft_memcpy(res + l1 + l2, s3, l3);
	res[l1 + l2 + l3] = '\0';
	return (res);
}

char	*find_git_dir(const char *cwd)
{
	char *dup;
	char *slash;
	char *path;
	if (!cwd)
		return (NULL);
	dup = ft_strdup_min(cwd);
	if (!dup)
		return (NULL);
	while (1)
	{
		path = ft_strjoin_min(dup, "/.git");
		if (!path)
		{
			free(dup);
			return (NULL);
		}
		if (access(path, F_OK) == 0)
		{
			free(dup);
			return (path);
		}
		free(path);
		slash = strrchr(dup, '/');
		if (!slash)
			break ;
		*slash = '\0';
		if (dup[0] == '\0')
			break ;
	}
	free(dup);
	return (NULL);
}

char	*get_git_branch(const char *git_dir)
{
	char *head_path;
	int fd;
	ssize_t r;
	char buf[256];
	char *ref;
	if (!git_dir)
		return (NULL);
	head_path = ft_strjoin_min(git_dir, "/HEAD");
	if (!head_path)
		return (NULL);
	fd = open(head_path, O_RDONLY);
	free(head_path);
	if (fd < 0)
		return (NULL);
	r = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (r <= 0)
		return (NULL);
	buf[r] = '\0';
	if (strncmp(buf, "ref:", 4) == 0)
	{
		ref = strrchr(buf, '/');
		if (!ref)
			return (ft_strdup_min(buf));
		ref++;
		ref[ft_strcspn(ref, "\n")] = '\0';
		return (ft_strdup_min(ref));
	}
	buf[ft_strcspn(buf, "\n")] = '\0';
	return (ft_strdup_min(buf));
}

int	is_git_dirty(void)
{
	pid_t pid;
	int status;
	if (access("/usr/bin/git", X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execlp("git", "git", "diff", "--quiet", NULL);
			_exit(2);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status) != 0);
			return (1);
		}
		return (1);
	}
	return (1);
}

char	*git_prompt(const char *cwd)
{
	char *git;
	char *branch;
	int dirty;
	char *res;
	if (!cwd)
		return (ft_strdup_min(""));
	git = find_git_dir(cwd);
	if (!git)
		return (ft_strdup_min(""));
	branch = get_git_branch(git);
	free(git);
	if (!branch)
		return (ft_strdup_min(""));
	dirty = is_git_dirty();
	if (dirty)
		res = ft_strjoin3(" (", "\033[31m", "");
	else
		res = ft_strjoin3(" (", "\033[32m", "");
	if (!res)
	{
		free(branch);
		return (ft_strdup_min(""));
	}
	free(res);
	if (dirty)
		res = ft_strjoin3("(\033[31m", branch, "\033[0m)");
	else
		res = ft_strjoin3("(\033[32m", branch, "\033[0m)");
	free(branch);
	return (res);
}
