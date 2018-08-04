#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

double gcd(double a, double b);

void print_loc();

double f();
double l();
double t();
double num();
char getch();
void dump_line();

char should_end = 0;
char** inp;
char* line;
int line_i;
int error;

int main(int argc, char** argv)
{
	inp = argv;
	double ret = 0;

	line = malloc(sizeof(char)*1024);

	while (!should_end)
	{
		error = 0;
		printf("~ ");
		char c = getchar();

		if (c == EOF)
		{
			break;
		}

		line_i = 0;
		while (c != 10)
		{
			while (c == ' ' || c == '\t')
			{
				c = getchar();
			}

			line[line_i++] = c;
			c = getchar();
		}
		line[line_i] = '\0';
		line_i = 0;

		if (line[0] == '!')
		{
			if (strcmp(line, "!help") == 0 || strcmp(line, "!h") == 0)
			{
				printf("---- Some helpful information:\n");
				printf("---- !help, !h     - Some helpful information.\n");
				printf("---- !funcions, !f - Supported functions.\n");

			}
			else if (strcmp(line, "!quit") == 0 || strcmp(line, "!q") == 0)
			{
				break;
			}
			if (strcmp(line, "!functions") == 0 || strcmp(line, "!f") == 0)
			{
				printf("---- exp(a)      - Same as exp in math.h.\n");
				printf("---- sin(a)      - Same as sin in math.h, so a is a radian.\n");
				printf("---- cos(a)      - Same as cos in math.h, so a is a radian.\n");
				printf("---- tan(a)      - To be written (look up 'math.h')\n");
				printf("---- sinh(a)     - To be written (look up 'math.h')\n");
				printf("---- cosh(a)     - To be written (look up 'math.h')\n");
				printf("---- tanh(a)     - To be written (look up 'math.h')\n");
				printf("---- asin(a)     - To be written (look up 'math.h')\n");
				printf("---- acos(a)     - To be written (look up 'math.h')\n");
				printf("---- log(a)      - To be written (look up 'math.h')\n");
				printf("---- floor(a)    - To be written (look up 'math.h')\n");
				printf("---- abs(a)      - To be written (look up 'math.h')\n");
				printf("---- fabs(a)     - To be written (look up 'math.h')\n");
				printf("---- ceil(a)     - To be written (look up 'math.h')\n");
				printf("---- sqrt(a)     - To be written (look up 'math.h')\n");
				printf("---- log10(a)    - To be written (look up 'math.h')\n");
				printf("---- atan(a)     - To be written (look up 'math.h')\n");
				printf("---- atan2(a, b) - To be written (look up 'math.h')\n");
				printf("---- ldexp(a, b) - To be written (look up 'math.h')\n");
				printf("---- pow(a, b)   - To be written (look up 'math.h')\n");
				printf("---- mod(a, b)   - To be written (look up 'math.h')\n");
				printf("---- fmod(a, b)  - To be written (look up 'math.h')\n");
				printf("---- gcd(a, b)   - a and b are rounded to the nearest integer. Look up 'gcd' if you are unsure what it does.\n");

			}
			else
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Unknown subcall '%s'\n", line);
			}
		}
		else
		{
			double val = f();
			if (error == 0)
			{
				printf("= %f\n", val);
			}
		}
	}

	free(line);

	return 0;
}

double f()
{
	double ret = l();

	while (1)
	{
		char c = line[line_i];
		//printf("---Line %d: %c was read\n", __LINE__, c);

		if (c == '+')
		{
			line_i++;
			ret += l();
		}
		else if (c == '-')
		{
			line_i++;
			ret -= l();
		}
		else
		{
			break;
		}
	}

	return ret;
}

double l()
{
	double ret = t();

	while (1)
	{
		char c = line[line_i];

		if (c == '*')
		{
			line_i++;
			ret *= t();
		}
		else if (c == '/')
		{
			line_i++;
			ret /= t();
		}
		else
		{
			break;
		}
	}

	return ret;
}

double t()
{
	char c = line[line_i];

	if (line[line_i] == '(')
	{
		// ( <F> )
		line_i++;
		double ret = f();

		if (line[line_i] == ')')
		{
			line_i++;
			return ret;
		}
		else
		{
			// ERROR
			printf(">>>> ");
			printf("Error!\n");
			printf(">>>> ");
			printf("Expected ')' but got '%c'\n", inp[0], line[line_i]);
			print_loc();
			error = 77;
			return 0.0;
		}
	}
	else if (line[line_i] >= '0' && line[line_i] <= '9')
	{
		// NUM
		return num();
	}
	else if (line[line_i] >= 'a' && line[line_i] <= 'z')
	{
		char name[512];
		char name_i = 0;

		while (line[line_i] >= 'a' && line[line_i] <= 'z' || line[line_i] >= '0' && line[line_i] <= '9')
		{
			name[name_i] = line[line_i];
			name_i++;
			line_i++;
		}
		name[name_i] = '\0';

		if (line[line_i] != '(')
		{
			// ERROR
			printf(">>>> ");
			printf("Error!\n");
			printf(">>>> ");
			printf("Expected '(' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
			print_loc();
			error = 23;
			return 0.0;
		}
		line_i++;

		if (strcmp(name, "exp") == 0)
		{
			double ret = exp(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "sin") == 0)
		{
			double ret = sin(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "cos") == 0)
		{
			double ret = cos(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "tan") == 0)
		{
			double ret = tan(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "sinh") == 0)
		{
			double ret = sin(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "cosh") == 0)
		{
			double ret = cos(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "tanh") == 0)
		{
			double ret = tan(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "asin") == 0)
		{
			double ret = asin(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "acos") == 0)
		{
			double ret = acos(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "log") == 0)
		{
			double ret = log(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "floor") == 0)
		{
			double ret = floor(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "abs") == 0)
		{
			double ret = fabs(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "fabs") == 0)
		{
			double ret = fabs(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "ceil") == 0)
		{
			double ret = ceil(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "sqrt") == 0)
		{
			double ret = sqrt(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "log10") == 0)
		{
			double ret = log10(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "atan") == 0)
		{
			double ret = atan(f());
			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "atan2") == 0)
		{
			double x = f();
			if (line[line_i] != ',')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;

			double y = f();
			double ret = atan2(x, y);

			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "ldexp") == 0)
		{
			double x = f();
			if (line[line_i] != ',')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;

			double y = f();
			double ret = ldexp(x, y);

			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "pow") == 0)
		{
			double x = f();
			if (line[line_i] != ',')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;

			double y = f();
			double ret = pow(x, y);

			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "mod") == 0)
		{
			double x = f();
			if (line[line_i] != ',')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;

			double y = f();
			double ret = fmod(x, y);

			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "fmod") == 0)
		{
			double x = f();
			if (line[line_i] != ',')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;

			double y = f();
			double ret = fmod(x, y);

			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "gcd") == 0)
		{
			double x = f();
			if (line[line_i] != ',')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;

			double y = f();
			double ret = gcd(x, y);

			if (line[line_i] != ')')
			{
				// ERROR
				printf(">>>> ");
				printf("Error!\n");
				printf(">>>> ");
				printf("Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else
		{
			// ERROR
			printf(">>>> ");
			printf("Error!\n");
			printf(">>>> ");
			printf("Unknown function %s\n", inp[0], name);
			print_loc();
			error = 33;
			return 0.0;
		}
	}
	else
	{
		// ERROR
		printf(">>>> ");
		printf("Error!\n");
		printf(">>>> ");
		printf("Expected a number or parenthesis\n", inp[0], line[line_i]);
		print_loc();
		error = 11;
		return 0.0;
	}
}

double num()
{
	double sum = 0.0;
	double rest = 0.0;
	double ex = 0.1;

	char c = line[line_i++];
	while (c >= '0' && c <= '9')
	{
		sum = sum*10 + c - '0';
		c = line[line_i++];
	}

	if (c == '.')
	{
		c = line[line_i++];
		while (c >= '0' && c <= '9')
		{
			rest += (c - '0')*ex;
			ex /= 10;
			c = line[line_i++];
		}
	}

	line_i--;

	return sum + rest;

}

void print_loc()
{
	int i;
	printf(">>>> ");
	printf("%s\n", line);
	printf(">>>> ");
	for (i = 0; i < line_i; i++)
	{
		putchar(' ');
	}
	putchar('^');
	putchar(10);
}

int gcd_i(int a, int b)
{
	int r;
	while (b > 0)
	{
		r = a%b;
		a = b;
		b = r;
	}
	return a;
}

double gcd(double a, double b)
{
	return (double)(gcd_i((int)(a + 0.5), (int)(b + 0.5)));
}

