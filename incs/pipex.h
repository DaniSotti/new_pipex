/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-sott <dde-sott@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:29:56 by dde-sott          #+#    #+#             */
/*   Updated: 2023/05/24 20:29:56 by dde-sott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/incs/libft.h"
# include <errno.h>

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	char	*file1;
	char	*file2;
	int		pipefd[2];
	int		dup_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd1;
	char	*cmd2;
	char	*tmp;
	char	**cmd_args;
	char	**cmd_paths;
	char	*final_cmd;
	char	*cmd;
}	t_pipex;

void	close_error(t_pipex *data, const char *message);
void	handle_error(const char *message);
int		empty_str(char *str);
void	free_paths(t_pipex *data);
char	*find_path(char **envp, t_pipex *data);
void	first_child_process(t_pipex *data, char **envp);
void	second_child_process(t_pipex *data, char **envp);
void	pipe_process(t_pipex *data, char **envp);

void	ft_free_array(char **arr);

#endif