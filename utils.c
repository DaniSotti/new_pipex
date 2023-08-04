/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:30:26 by dde-sott          #+#    #+#             */
/*   Updated: 2023/06/20 19:30:26 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_error(t_pipex *data, const char *message)
{
	perror(message);
	ft_free_array(data->cmd_args);
	if (data->pipefd[0] != -1)
		close (data->pipefd[0]);
	if (data->pipefd[1] != -1)
		close (data->pipefd[0]);
	if (data->dup_fd[0] != -1)
		close(data->dup_fd[0]);
	if (data->dup_fd[1] != -1)
		close(data->dup_fd[1]);
	exit(EXIT_FAILURE);
}

void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}

int	empty_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (0);
		i++;
	}
	return (1);
}

void	free_paths(t_pipex *data)
{
	int	i;

	i = 0;
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
}
