#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
//проверка на ввод числа 



using namespace std;

int P1; // 09 08 06
int P2; // 09 07 os
int N; // 2510

int M; // 48 16

bool to_print = false;
bool short_print = false;
int seq_proc_count = 0;

float min_relat = 100;
float max_relat = 0;
float mid_relat = 0;



bool is_digit(const char* S) {		//проверка на число
	const char* temp = "0123456789-+";
	unsigned point_count = 0;

	for (int i = 0; i < strlen(S); i++) {
		if ((i > 0) && (S[i] == '+' || S[i] == '-')) return false;
		if (S[i] == '.') {
			point_count++;
			if (point_count > 1) return false;
		}
		if (!strchr(temp, S[i])) return false;
	}
	return true;
}
int return_int()
{
	const int N = 256;
	char S[N];

	cin >> S;
	while (!is_digit(S)) {	//сделать проверку на ввод числа
		cout << "введите число  = ";
		cin >> S;
	}
	cout << "ok\n";
	return atof(S);
}



int max(int _t1, int _t2, int _t3)
{
	int a = (_t1 > _t2) ? _t1 : _t2;

	int b = (_t2 > _t3) ? _t2 : _t3;

	return (a > b) ? a : b;

}

void setP1_menu()
{

	int c = 0;
	while (c <= 0 || c > 3)
	{

		printf("set P1 - probability of first type command, options: \n\t1 -- 0.9\n\t2 -- 0.8\n\t3 -- 0.6\n");
		//mscanf(&c);
		c = return_int();
		
	}
	switch (c)
	{

	case 1:
		P1 = 9;
		break;
	case 2:
		P1 = 8;
		break;
	case 3:
		P1 = 6;
		break;
	default:
		throw(char*)"P1 error";
	}
}


void setP2_menu()
{

	int c = 0;
	while (c <= 0 || c > 3)
	{

		printf("set P2 - probability of first type command, options: \n\t1 -- 0.9\n\t2 -- 0.7\n\t3 -- 0.5\n");
		//mscanf(&c);
		c = return_int();
	}
	switch (c)
	{

	case 1:
		P2 = 9;
		break;
	case 2:
		P2 = 7;
		break;
	case 3:
		P2 = 5;
		break;
	default: throw(char*)"P2 error";
	}
}

void setN_menu()
{
	int c = 0;
	while (c <= 0 || c > 3)
	{
		printf("set N - clocks to access memory, options: \n\t1 -- 2\n\t2 -- 5\n\t3 -- 10\n");
		//mscanf(&c);
		c = return_int();

	}
	switch (c)
	{

	case 1:
		N = 2;
		break;
	case 2:
		N = 5;
		break;
	case 3:
		N = 10;
		break;
	default: throw(char*)"N error";
	}
}

void setM_menu()
{
	int c = 0;
	while (c <= 0 || c > 3)
	{
		printf("set M - clocks it takes to calculate second type command, options: \n\t1 -- 4\n\t2 -- 8\n\t3 -- 16\n");
		//mscanf(&c);
		c = return_int();
	}

	switch (c)
	{

	case 1:
		M = 4;

		break;
	case 2:
		M = 8;

		break;
	case 3:
		M = 16;
		break;
	default: throw (char*)"P1 error";

	}
}

int settings()//ввод параметров конвеера
{
	printf("\tconveir settings:\n");
	try {
		setP1_menu();
		setP2_menu();
		setN_menu();

		setM_menu();
	}
	catch (char* m)
	{
		printf(m);
		return 1;
	}
	if (P1 != 0)
		printf("conveir settings\n\tP1 0.%d\tP2 O.%d\tN %d\tM %d\t\n", P1, P2, N, M);

	
	system("pause");
	return 0;

}

bool coin(int _prob)
{
	srand(time(NULL));
	if (rand() % 10 < _prob) return true;
	else return false;
}

int command()	//счет тактов
{
	int step1 = 1, step2 = 1, step3 = 1, step4 = 1, step5 = step3;

	if (!coin(P1))
		step2 = N;

	if (!coin(P1))
		step3 = N;

	if (!coin(P2))
		step4 = M;

	step5 = step3;
	seq_proc_count += step1 + step2 + step3 + step4 + step5;

	int step123 = max(step1, step2, step3);
	int sum = step123 + step4 + step5;

	if (to_print)
		printf("%d %d %d %d %d\n\t\tclocks: %d\n", step1, step2, step3, step4, step5, sum);
	return sum;
}


int find_avarage(int _num)	//среднее время такта
{
	srand(time(0));

	int count = 0;

	seq_proc_count = 0;	//?

	for (int i = 0; i < _num; i++)
	{
		if (to_print) printf("N_%d\t", i + 1);
		int add = command();

		count += add;
	}
	return count;
}


void conveir(FILE* fp)	//счет времени выполнения команд. чтение и дешифрация как просто команда выполняются тут
{
	int iteration = 200;
	if (short_print)
		iteration = 400;
	int total_clocks = find_avarage(iteration);
	float average = (float)total_clocks / (float)iteration;
	float seq_proc_average = (float)seq_proc_count / (float)iteration;
	if (short_print)
	{
		printf("\t%d\t%.3f\t%.2F\n", total_clocks, average, seq_proc_average);
		if (fp != nullptr)
			fprintf(fp, "\t%d\t%.3F\t%.3F\n", total_clocks, average, seq_proc_average);

		float relation = seq_proc_average / average;
		if (relation > max_relat)
			max_relat = relation;
		else
			if (relation < min_relat)
				min_relat = relation;
		mid_relat += relation;

	}
	else
	{
		printf("\n\tRESULTS\n\ttotal clocks for 200 operations = %d\n\taverage =	%.3f\n", total_clocks, average);
		printf("\taverage with sequence proc = %.3f\n", seq_proc_average);
	}
}

void all_conveir_stats()	//вывод статистики
{

	FILE* fpout;
	int m1 = 0;
	fpout = fopen("conveir_stats.txt", "w");
	if (fpout == NULL)
	{
		printf("ATTENTION: could not open File conveir_stats.txt\n");
		return;

	}

	printf("P1\tP2\tN\tM\ttotal clocks\tavegare\taverage seq\n");
	fprintf(fpout, "P1\tP2\tN\tM\ttotal clocks\tavegare\taverage seq\n");
	int save_P1 = P1;

	P1 = 9;

	mid_relat = 0;

	min_relat = 10;

	max_relat = 0;
	for (int p1 = 0; p1 < 3; p1++)
	{

		P2 = 9;
		for (int p2 = 0; p2 < 3; p2++)
		{
			N = 10;
			for (int n = 0; n < 3; n++)
			{
				M = 16;
				for (m1 = 0; m1 < 3; m1++)
				{

					printf("0.%d\t0.%d\t%d\t%d\t", P1, P2, N, M);
					fprintf(fpout, "O.%d\t0.%d\t%d\t%d\t", P1, P2, N, M);
					conveir(fpout);

					M /= 2;
				}
				N /= 2;
			}
			P2 -= 2;
		}
		P1 -= 1;
	}

	P1 = save_P1;
	printf("\n");

	printf("mininum relation: %F\n", min_relat);
	printf("maximun relation: %f\n", max_relat);
	printf("average relatior: %f\n", mid_relat / 81.0);

	fclose(fpout);

}

int main()
{
	int c = 0;
	P1 = 0;

	while (true)
	{

		if (P1 != 0)
			printf("convein settings\n\tP1 0.%d\tP2 0.%d\tN %d\tM %d\t\n", P1, P2, N, M);
		printf("\tmain menu\n");
		printf("0 exit\n");
		printf("1 conveir settings\n");
		printf("2 count with print\n");
		printf("3 count without print\n");
		printf("4 count all conveir stats\n");
		
		//c=mscanf(&c);
		c = return_int();

		switch (c)
		{
		case 0:
			return 0;
		case 2:

			system("cls");

			if (P1 == 0)
			{
				printf("conveir paraneters are not set\n");
				break;

			}

			to_print = true;

			short_print = false;

			conveir(nullptr);

			break;

		case 3:
			system("cls");

			if (P1 == 0)
			{
				printf("conveir parameters are not set\n");
				break;

			}

			to_print = false;

			short_print = false;

			conveir(nullptr);

			break;

		case 4:
			system("cls");

			to_print = false;
			short_print = true;
			all_conveir_stats();
			break;
		case 1:
			system("cls");
			while (settings() != 0)
			{
			};
			system("cls");
			break;
		default:
			printf("unknwon comtand\n");
		}

	}
	return 0;
}
