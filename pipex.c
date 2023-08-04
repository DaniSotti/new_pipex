/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:39:42 by dde-sott          #+#    #+#             */
/*   Updated: 2023/05/24 22:39:42 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp, t_pipex *data, char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || empty_str(cmd))
		handle_error(data, "empty string or no command");
	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	data->cmd_paths = ft_split(*envp + 5, ':');
	while (data->cmd_paths[i] != NULL)
	{
		data->tmp = ft_strjoin(data->cmd_paths[i], "/");
		data->final_cmd = ft_strjoin(data->tmp, cmd);
		free(data->tmp);
		if (access(data->final_cmd, X_OK | F_OK) == 0)
			return (data->final_cmd);
		free(data->final_cmd);
		i++;
	}
	free_paths(data);
	return (NULL);
}

void	first_child_process(t_pipex *data, char **envp)
{
	int	i;

	i = 0;
	data->dup_fd[0] = dup2(data->pipefd[1], STDOUT_FILENO);
	if (data->dup_fd[0] == -1)
		handle_error(data, "Error dup2");
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	data->dup_fd[1] = dup2(data->fd1, STDIN_FILENO);
	if (data->dup_fd[1] == -1)
		handle_error(data, "Error dup2");
	close(data->fd1);
	close(data->fd2);
	data->cmd_args = ft_split(data->cmd1, ' ');
	data->cmd = find_path(envp, data, data->cmd_args[0]);
	if (!data->cmd)
		handle_error(data, "command 1 not valid");
	exit(execve(data->cmd, data->cmd_args, envp));
}

void	second_child_process(t_pipex *data, char **envp)
{
	int	i;

	i = 0;
	data->dup_fd[0] = dup2(data->pipefd[0], STDIN_FILENO);
	if (data->dup_fd[0] == -1)
		handle_error(data, "Error dup2");
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	data->dup_fd[1] = dup2(data->fd2, STDOUT_FILENO);
	if (data->dup_fd[1] == -1)
		handle_error(data, "Error dup2");
	close(data->fd1);
	close(data->fd2);
	data->cmd_args = ft_split(data->cmd2, ' ');
	data->cmd = find_path(envp, data, data->cmd_args[0]);
	if (!data->cmd)
		handle_error(data, "command 2 not valid");
	exit(execve(data->cmd, data->cmd_args, envp));
}

void	pipe_process(t_pipex *data, char **envp)
{
	data->fd1 = open(data->file1, O_RDONLY);
	if (data->fd1 < 0)
	{
		perror("Error open infile");
		exit(EXIT_FAILURE);
	}
	data->fd2 = open(data->file2, O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (data->fd2 < 0)
	{
		perror("Error open outfile");
		exit(EXIT_FAILURE);
	}
		// handle_error(data, "Error open outfile");
	if (pipe(data->pipefd) < 0)
		handle_error(data, "Error creating pipe");
	data->pid1 = fork();
	if (data->pid1 == 0)
		first_child_process(data, envp);
	data->pid2 = fork();
	if (data->pid2 == 0)
		second_child_process(data, envp);
	close(data->fd1);
	close(data->fd2);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		data;
	const char	*err;

	err = "Error number of arguments ./pipe_program file1 cmd1 cmd2 file2\n";
	if (argc != 5 || envp[0] == NULL)
	{
		write(1, err, ft_strlen(err));
		exit(EXIT_FAILURE);
	}
	data.file1 = argv[1];
	data.cmd1 = argv[2];
	data.cmd2 = argv[3];
	data.file2 = argv[4];
	pipe_process(&data, envp);
	return (0);
}
