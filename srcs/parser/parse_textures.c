/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azorlutu <azorlutu@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:36:02 by azorlutu          #+#    #+#             */
/*   Updated: 2025/10/19 22:36:03 by azorlutu         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	clean_texture_token(t_game *game, char **token)
{
	char	*temp;

	temp = ft_strtrim(*token, " \t");
	if (!temp)
		exit_safe(game, "Malloc failed in parse_texture", 1);
	free(*token);
	*token = temp;
}

static void	validate_texture_file(t_game *game, char *path)
{
	int	len;
	int	fd;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 5) != 0)
		exit_safe(game, "Texture path must end with .xpm", 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_safe(game, "This file cannot be read", 1);
	close(fd);
	check_hidden_file(game, path, "The texture file cannot be hidden");
}

void	parse_texture(t_game *game, char **target_path, char **tokens)
{
	if (tokens[1] == NULL || tokens[2] != NULL)
		exit_safe(game, "Invalid texture format (Ex. 'NO ./path')", 1);
	if (*target_path != NULL)
		exit_safe(game, "Texture path duplicate detected", 1);
	clean_texture_token(game, &tokens[1]);
	validate_texture_file(game, tokens[1]);
	*target_path = ft_strdup(tokens[1]);
	if (*target_path == NULL)
		exit_safe(game, "fd: malloc error", 1);
}

void	check_hidden_file(t_game *game, char *path, char *error_msg)
{
	char	*arg;

	arg = ft_strrchr(path, '/');
	if (arg && arg[1] == '.')
	{
		if (ft_strlen(++arg) == 4)
			exit_safe(game, error_msg, 1);
		exit_safe(game, error_msg, 1);
	}
	if (!arg && path[0] == '.')
		exit_safe(game, error_msg, 1);
}
