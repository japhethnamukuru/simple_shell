#include "shell.h"

/**
  * get_full_path - creates the absolute path from a program name
  * @exe: the name of the executable
  * Description: looks for the program 'exe' in the directories stored
  * in the current environment's PATH variable
  * Return: pointer to the full path of the program if found, else exe
  */
char *get_full_path(char *exe)
{
	char *dir, *env_path, *save_ptr, *full_path;

	if (exe == NULL)
		return (NULL);
	else if (*exe == '/')
		return (str_dup(exe));

	save_ptr = NULL;
	env_path = str_dup(getenv("PATH"));
	dir = str_tok_r(env_path, ":", &save_ptr);

	full_path = find_path(dir, exe, &save_ptr);

	free(env_path);

	return (full_path);
}

/**
  * find_path - runs through the directories in PATH, looking for the exe
  * @dir: the first dir in PATH, gotten by first call to strtok_r()
  * @exe: the name of executable program
  * @save_ptr: pointer passed to strtok_r()
  * Return: the full path if it exist, exe otherwise
  */
char *find_path(char *dir, char *exe, char **save_ptr)
{
	char *dir_c, *full_path;
	int found, prev_errno;
	struct stat st;

	found = 0;
	prev_errno = errno;
	while (dir)
	{
		dir_c = str_dup(dir);
		full_path = malloc(sizeof(char) * (str_len(dir_c) + str_len(exe) + 2));
		if (full_path == NULL)
			return (NULL);

		mem_cpy(full_path, dir_c, str_len(dir_c));
		mem_cpy(full_path + str_len(dir_c), "/", 1);
		mem_cpy(full_path + str_len(dir_c) + 1, exe, str_len(exe));
		*(full_path + str_len(dir_c) + str_len(exe) + 1) = '\0';

		if (stat(full_path, &st) == 0)
		{
			found = 1;
			free(dir_c);
			break;
		}

		free(dir_c);
		free(full_path);
		dir = str_tok_r(NULL, ":", save_ptr);
	}
	errno = prev_errno;

	if (found)
		return (full_path);
	else
		return (str_dup(exe));
}
