#ifndef WRAPPER_INPPAR
#define WRAPPER_INPPAR
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int inppar_scmp(char* longer, char* shorter)
{
	int i = 0;

	while (1)
	{
		if (shorter[i] == '\0')
		{
			return 1;
		}

		if (longer[i] == '\0')
		{
			return 0;
		}

		if (shorter[i] != longer[i])
		{
			return 0;
		}

		i++;
	}
}

int inppar_fetchs(int argc, char** argv, char* target, char* src)
{
	int i, j;

	for (i = 1; i < argc; i++)
	{
		if (inppar_scmp(argv[i], target))
		{
			int l = strlen(target);

			int sum = 0;
			for (j = l; argv[i][j] != '\0'; j++)
			{
				src[j - l] = argv[i][j];
			}
			src[j - l] = '\0';

			return i;
		}
	}

	src[0] = '\0';
	return 0;
}

int inppar_fetchi(int argc, char** argv, char* target, int* src)
{
	int i, j;

	for (i = 1; i < argc; i++)
	{
		if (inppar_scmp(argv[i], target))
		{
			int l = strlen(target);

			int sum = 0;
			for (j = l; argv[i][j] != '\0'; j++)
			{
#ifdef INPPAR_STRICT
				if (argv[i][j] < '0' || argv[i][j] > '9')
				{
#ifdef INPPAR_EXIT_ON_WARNING
					printf("error: '%s' is an illegal parameter becuase '%s' is a number flag.\n", argv[i], target);
					exit(33);
#else
					printf("warning: '%s' is an illegal parameter becuase '%s' is a number flag.\n", argv[i], target);
					return 0;
#endif
				}
#endif
				sum = (sum << 1) + (sum << 3) + argv[i][j] - '0';
			}

			*src = sum;

			return i;
		}
	}

	return 0;
}

int inppar_fetchb(int argc, char** argv, char* target, int* src)
{
	int i, j;

	for (i = 1; i < argc; i++)
	{
		if (inppar_scmp(argv[i], target))
		{
#ifdef INPPAR_STRICT
			if (strlen(argv[i]) != strlen(target))
			{
#ifdef INPPAR_EXIT_ON_WARNING
				printf("error: '%s' is an illegal parameter becuase '%s' is a binary flag.\n", argv[i], target);
				exit(33);
#else
				printf("warning: '%s' is an illegal parameter becuase '%s' is a binary flag.\n", argv[i], target);
				return 0;
#endif
			}
#endif
			*src = 1;

			return i;
		}
	}

	return 0;
}

















#endif
