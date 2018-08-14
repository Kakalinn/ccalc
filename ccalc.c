#define INPPAR_STRICT
#define INPPAR_EXIT_ON_WARNING
#include "inppar.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

double gcd(double a, double b);
double torad(double a);
double todeg(double a);

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

int arg_s = 0;
int arg_h = 0;
int arg_x = 0;
int arg_r = 0;
int arg_l = 1024;
char arg_f[128];

FILE* fp_out;
FILE* fp_in;

int main(int argc, char** argv)
{
	fp_out = stdout;
	fp_in = stdin;
	inp = argv;
	double ret = 0;

	inppar_fetchb(argc, argv, "-s", &arg_s);

	inppar_fetchb(argc, argv, "-h", &arg_h);

	inppar_fetchi(argc, argv, "-l", &arg_l);

	inppar_fetchb(argc, argv, "-r", &arg_r);

	inppar_fetchs(argc, argv, "-if", &(arg_f[0]));
	if (arg_f[0] != '\0')
	{
		printf("~~~in: %s\n", arg_f);
		fp_in = fopen(arg_f, "r");
		if (fp_in == NULL)
		{
			// ERROR
			printf(">>>> ");
			printf("Error!\n");
			printf(">>>> ");
			printf("Could not open input file '%s'\n", arg_f);
		}
	}

	inppar_fetchs(argc, argv, "-of", &(arg_f[0]));
	if (arg_f[0] != '\0')
	{
		printf("~~~out: %s\n", arg_f);
		fp_out = fopen(arg_f, "w");
		if (fp_out == NULL)
		{
			// ERROR
			printf(">>>> ");
			printf("Error!\n");
			printf(">>>> ");
			printf("Could not open output file '%s'\n", arg_f);
		}
	}

	if (arg_h == 1)
	{
		printf("Options:\n");
		printf("  -h        - Brings up this prompt and exits.\n");
		printf("  -s        - Use simple mode. In simple mode only the evaluation of the expression is put on the output.\n");
		printf("  -r        - Round the output. This means the output will always be an integer.\n");
		printf("              default = 0.\n");
		printf("  -l<num>   - Sets the maximum line length to <num>.\n");
		printf("              Inputting a line longer than the maximum is undefined (read 'not recommended').\n");
		printf("              default = 1024\n");
		printf("  -if<str>  - Sets <str> as the output file.\n");
		printf("              default = stdin\n");
		printf("  -of<str>  - Sets <str> as the input file.\n");
		printf("              default = stdout\n");
		exit(23);
	}

	line = malloc(sizeof(char)*arg_l);

	while (!should_end)
	{
		error = 0;
		if (arg_s == 0 && fp_in == stdin)
		{
			fprintf(fp_out, "~ ");
		}
		char c = fgetc(fp_in);

		if (c == EOF)
		{
			break;
		}

		line_i = 0;
		while (c != 10)
		{
			while (c == ' ' || c == '\t')
			{
				c = fgetc(fp_in);
			}

			line[line_i++] = c;
			c = fgetc(fp_in);
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
				printf("---- !quit, !q     - Quit.\n");

			}
			else if (strcmp(line, "!quit") == 0 || strcmp(line, "!q") == 0)
			{
				break;
			}
			else if (strcmp(line, "!functions") == 0 || strcmp(line, "!f") == 0)
			{
				printf("---- abs(a)      - To be written (look up 'math.h')\n");
				printf("---- acos(a)     - To be written (look up 'math.h')\n");
				printf("---- asin(a)     - To be written (look up 'math.h')\n");
				printf("---- atan(a)     - To be written (look up 'math.h')\n");
				printf("---- atan2(a, b) - To be written (look up 'math.h')\n");
				printf("---- ceil(a)     - To be written (look up 'math.h')\n");
				printf("---- cos(a)      - Same as cos in math.h, so a is a radian.\n");
				printf("---- cosh(a)     - To be written (look up 'math.h')\n");
				printf("---- fabs(a)     - To be written (look up 'math.h')\n");
				printf("---- floor(a)    - To be written (look up 'math.h')\n");
				printf("---- fmod(a, b)  - To be written (look up 'math.h')\n");
				printf("---- gcd(a, b)   - a and b are rounded to the nearest integer. Look up 'gcd' if you are unsure what it does.\n");
				printf("---- ldexp(a, b) - To be written (look up 'math.h')\n");
				printf("---- log(a)      - To be written (look up 'math.h')\n");
				printf("---- log10(a)    - To be written (look up 'math.h')\n");
				printf("---- mod(a, b)   - To be written (look up 'math.h')\n");
				printf("---- pow(a, b)   - To be written (look up 'math.h')\n");
				printf("---- sin(a)      - Same as sin in math.h, so a is a radian.\n");
				printf("---- sinh(a)     - To be written (look up 'math.h')\n");
				printf("---- sqrt(a)     - To be written (look up 'math.h')\n");
				printf("---- tan(a)      - To be written (look up 'math.h')\n");
				printf("---- tanh(a)     - To be written (look up 'math.h')\n");
				printf("---- todeg(a)    - Converts degrees to radians.\n");
				printf("---- torad(a)    - Converts degrees to radians.\n");
				printf("---- exp(a)      - Same as exp in math.h.\n");
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
				if (arg_s == 0)
				{
					fprintf(fp_out, "= ");
				}

				if (arg_r == 0)
				{
					fprintf(fp_out, "%f\n", val);
				}
				else
				{
					fprintf(fp_out, "%d\n", (int)(val + 0.5));
				}
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
		//fprintf(fp_out, "---Line %d: %c was read\n", __LINE__, c);

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
	else if (line[line_i] == '\0')
	{
		return 0.0;
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "todeg") == 0)
		{
			double ret = todeg(f());
			if (line[line_i] != ')')
			{
				// ERROR
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
				print_loc();
				error = 23;
				return 0.0;
			}
			line_i++;
			return ret;
		}
		else if (strcmp(name, "torad") == 0)
		{
			double ret = torad(f());
			if (line[line_i] != ')')
			{
				// ERROR
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ',' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Error!\n");
				fprintf(fp_out, ">>>> ");
				fprintf(fp_out, "Expected ')' but got '%c' (%d)\n", inp[0], line[line_i], line[line_i]);
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
			fprintf(fp_out, ">>>> ");
			fprintf(fp_out, "Error!\n");
			fprintf(fp_out, ">>>> ");
			fprintf(fp_out, "Unknown function %s\n", inp[0], name);
			print_loc();
			error = 33;
			return 0.0;
		}
	}
	else
	{
		// ERROR
		fprintf(fp_out, ">>>> ");
		fprintf(fp_out, "Error!\n");
		fprintf(fp_out, ">>>> ");
		fprintf(fp_out, "Expected a number or parenthesis\n", inp[0], line[line_i]);
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
	fprintf(fp_out, ">>>> ");
	fprintf(fp_out, "%s\n", line);
	fprintf(fp_out, ">>>> ");
	for (i = 0; i < line_i; i++)
	{
		fputc(' ', fp_out);
	}
	fputc('^', fp_out);
	fputc(10, fp_out);
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

double todeg(double a)
{
	return a/(2*M_PI)*360;
}

double torad(double a)
{
	return a/360.0*2*M_PI;
}

