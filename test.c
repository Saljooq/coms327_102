#include <stdio.h>
#include <stdlib.h>
#include <endian.h>
#include <string.h>
#include <time.h>

#define xlenMax 10
#define ylenMax 5

int main(int argc, char* argv[])
{
	srand(time(0));
	printf("Hello World!!\n");

	int i,j,k;

	FILE *f;

	for (i = 1; i < argc; i++)
	{
			if (!(strcmp(argv[i], "--save")))
			{
				j = 1;
				break;
			}

	}

	if (j==1)
	{
		printf("save found\n");
	}
	else
	{
		printf("save not found\n");
	}

	int hardness[xlenMax][ylenMax];

	//populating the hardness randomly
	for (i = 0; i < ylenMax; i++)
	{
		for (j = 0; j < xlenMax; j++)
		{
			hardness[j][i] = 1 + (rand() % 254);
			printf("%d ", hardness[j][i]);
		}
		printf("\n");
	}

	fopen("binary_file", "w");

	if( !( f = fopen( "binary_file", "w"))) {fprintf(stderr, "Failed to open file"); return 1;}

	char* marker = "RLG327-S2021";
	fwrite(marker, sizeof(char), 12, f);

	u_int32_t version = 1;
	version = htobe32(version);
	fwrite(&version, sizeof(u_int32_t), 1, f);

	

	u_int8_t xPCpos = 0;
	u_int8_t yPCpos = 0;
	for (i = 0; i < ylenMax; i++)
	{
		k = 0;
		for (j = 0; j < xlenMax; j++)
		{
			if (hardness[j][i] < 10)//if (grid[j][i] == '.')
			{
				xPCpos = j+1;
				yPCpos = i+1;
				k=1;
				break;
			}

		}
		if (k) break;
	}

	fwrite(&xPCpos, sizeof(u_int8_t), 1, f);
	fwrite(&yPCpos, sizeof(u_int8_t), 1, f);

	for (i = 0; i < ylenMax; i++)
	{
		for (j = 0; j < xlenMax; j++)
		{
			int8_t write_value = (hardness[i][j]);
			fwrite(&write_value,sizeof(int8_t),1,f);
		}
	}

	fclose(f);

	return 0;

}
