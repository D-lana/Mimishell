/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlana <dlana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:28:43 by dlana             #+#    #+#             */
/*   Updated: 2022/02/19 14:28:44 by dlana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_how_many(const char *str, char c);
static int	ft_word(int i, const char *s, char c);
static int	ft_words_killer(char **result, int j);
static int	ft_array(int words_j, char **result, const char *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		how_many_words;

	if (!s)
		return (NULL);
	how_many_words = ft_how_many(s, c);
	result = (char **)malloc(sizeof(char *) * (how_many_words + 1));
	if (!result)
		return (NULL);
	result[how_many_words] = ((void *)0);
	if (ft_array(how_many_words, result, s, c) == 0)
		return (NULL);
	else
		return (result);
}

static int	ft_how_many(const char *str, char c)
{
	int	i;
	int	how_many_words;
	int	note;

	i = 0;
	how_many_words = 0;
	note = 0;
	while (str[i])
	{
		if (str[i] == c)
			note = 0;
		if (note == 0 && str[i] != c)
		{
			note = 1;
			how_many_words++;
		}
		i++;
	}
	return (how_many_words);
}

static int	ft_word(int i, const char *s, char c)
{
	int	j;

	j = 0;
	while (s[i + j] && s[i + j] != c)
		j++;
	return (j);
}

static int	ft_words_killer(char **result, int j)
{
	while (j)
	{	
		j--;
		free(result[j]);
		result[j] = NULL;
	}
	free(result);
	result = NULL;
	return (0);
}

static int	ft_array(int words_j, char **result, const char *s, char c)
{
	int	i;
	int	j;
	int	word_i;

	i = 0;
	j = 0;
	while (j < words_j)
	{
		while (s[i] == c)
			i++;
		word_i = ft_word(i, s, c);
		result[j] = (char *)malloc(sizeof(char) * (word_i + 1));
		if (!result[j])
			return (ft_words_killer((char **) result, j));
		word_i = 0;
		while (s[i] && s[i] != c)
		{
			result[j][word_i] = s[i];
			word_i++;
			i++;
		}
		result[j][word_i] = '\0';
		j++;
	}
	return (1);
}
