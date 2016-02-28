/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:01:09 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/27 18:42:55 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		ft_get_file_type(struct stat *file_stat)
{
	char c;

	if (S_ISBLK(file_stat->st_mode))
		c = 'b';
	else if (S_ISCHR(file_stat->st_mode))
		c = 'c';
	else if (S_ISDIR(file_stat->st_mode))
		c = 'd';
	else if (S_ISLNK(file_stat->st_mode))
		c = 'l';
	else if (S_ISFIFO(file_stat->st_mode))
		c = 'p';
	else if (S_ISSOCK(file_stat->st_mode))
		c = 's';
	else
		c = '-';
	return (c);
}

static	void	ft_perm_acc(t_lst *elem, struct stat *file_stat)
{
	ft_bzero(elem->file_data->get_perm, 11);
	elem->file_data->get_perm[0] = ft_get_file_type(file_stat);
	elem->file_data->get_perm[1] = (file_stat->st_mode & S_IRUSR) ? 'r' : '-';
	elem->file_data->get_perm[2] = (file_stat->st_mode & S_IWUSR) ? 'w' : '-';
	elem->file_data->get_perm[3] = (file_stat->st_mode & S_IXUSR) ? 'x' : '-';
	elem->file_data->get_perm[4] = (file_stat->st_mode & S_IRGRP) ? 'r' : '-';
	elem->file_data->get_perm[5] = (file_stat->st_mode & S_IWGRP) ? 'w' : '-';
	elem->file_data->get_perm[6] = (file_stat->st_mode & S_IXGRP) ? 'x' : '-';
	elem->file_data->get_perm[7] = (file_stat->st_mode & S_IROTH) ? 'r' : '-';
	elem->file_data->get_perm[8] = (file_stat->st_mode & S_IWOTH) ? 'w' : '-';
	elem->file_data->get_perm[9] = (file_stat->st_mode & S_IXOTH) ? 'x' : '-';
}
/* new function for ft_get_time */
static char    *ft_lastword(char *s)
{
	char    *ptr;
	int     is_word;

	ptr = NULL;
	is_word = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && !is_word)
		{
			ptr = s;
			is_word = 1;
		}
		else if (ft_isspace(*s))
			is_word = 0;
		++s;
	}
	return (ptr);
}
/* new function for time managing */
static char			*ft_get_time(const long *f_time)
{
	char 	*tmp;
	char 	*prev;
	char 	*new;
	time_t	today;

	time(&today);
	tmp = ctime(f_time);
	if (today - 15724800 > *f_time || today < *f_time)
	{
		prev = ft_strsub(tmp, 4, 7); // month + day
		new = ft_strjoin(prev, ft_lastword(tmp) - 1); // lastword = year
		new[ft_strlen(new)] = '\0';
		ft_strdel(&prev);
	}
	else
		new = ft_strsub(tmp, 4, 12); // date + heure
	if (ft_strchr(new, '\n')) //ctime ajoute un '\n' apres l'annee
		(ft_strchr(new, '\n'))[0] = '\0';
	return (new);
}

void			ft_add_data(struct stat file_stat, t_lst *node, char *file)
{
	struct passwd	*user_name;
	struct group	*group_name;

	node->file_data->blocks = file_stat.st_blocks;
	ft_perm_acc(node, &file_stat);
	node->file_data->links = ft_itoa(file_stat.st_nlink);
	if ((user_name = getpwuid(file_stat.st_uid)))
		node->file_data->uid = ft_strdup(user_name->pw_name);
	else
		node->file_data->uid = ft_itoa(file_stat.st_uid);
	if ((group_name = getgrgid(file_stat.st_gid)))
		node->file_data->gid = ft_strdup(group_name->gr_name);
	else
		node->file_data->gid = ft_itoa(file_stat.st_gid);
	node->file_data->size = ft_itoa(file_stat.st_size);
	//node->date = ft_strsub(ctime(&file_stat.st_mtime), 4, 12);
	node->date = ft_get_time(&file_stat.st_mtime); // new function
	node->last_edit = (int)(file_stat.st_mtime);
	node->name = ft_strdup(file);
	node->file_data->min = ft_itoa(minor(file_stat.st_rdev));
	node->file_data->maj = ft_strjoin(ft_itoa(major(file_stat.st_rdev)), ",");
	node->is_dir = (node->file_data->get_perm[0] == 'd'
			&& ft_strcmp(node->name, ".") && ft_strcmp(node->name, ".."));
	node->next = NULL;
}

t_lst			*ft_get_data(t_lst *head, char *file, char *path)
{
	struct stat file_st;
	t_lst		*tmp;
	t_lst		*current;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	tmp->file_data = (t_data *)malloc(sizeof(t_data));
	current = head;
	if (lstat(path, &file_st) <= 0)
		ft_add_data(file_st, tmp, file);
	if (head == NULL)
		return (tmp);
	while (current->next != NULL)
		current = current->next;
	current->next = tmp;
	return (head);
}
