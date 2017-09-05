#include<stdio.h> /* required for file operations */
//fopen, fclose, fgets, fputs, fscanf

#include <string.h>	//strncmp


float cpu_temp;

int read_thermal_file()
{
	FILE *fp;
	fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");	//read mode
	if(fp == NULL)
	{
		perror("Error while opening the file.\n");
		return -1;
	}
	fscanf(fp, "%f", &cpu_temp);
	fclose(fp);

	cpu_temp = cpu_temp / 1000;

	return 0;
}

void print_help_menu()
{
        printf("Usage: lstemp [OPTIONS]... \n");
        printf("Raspberry Pi 2, Temperature Display\n");
	printf("\n");
        printf("Options:\n");
        printf("  -h, --help                    Help Menu\n");
        printf("  -v, --version                 Display the curent version\n");
        printf("  -c				Display Temp in Celsius only\n");
        printf("  -f				Display Temp in Fehrenheit only\n");
        printf("\n");
        printf("\n");
        printf("Report bugs to <mubarak.qahtani@outlook.sa>\n");

        return;
}


void print_version()
{
        printf("lstemp 0.0.1\n");
        printf("Copyright (C) 2015.\n");
        printf("This is free software.  You may redistribute copies of it under the terms of\n");
        printf("the GNU General Public License <http://www.gnu.org/licenses/gpl.html>.\n");
        printf("There is NO WARRANTY, to the extent permitted by law.\n");
        printf("\n");
        printf("Mubarak AlQahtani <mubarak.qahtani@outlook.sa>.\n");

}



int main(int argc, char* argv[])
{

	read_thermal_file();

	if(argc > 1 && strncmp(argv[1], "-h", 2) == 0)
		print_help_menu();
	else if(argc > 1 && strncmp(argv[1], "-V", 2) == 0)
		print_version();
	else
	{
		if(argc < 2 || strncmp(argv[1], "-f", 2) != 0)
			printf("CPU temp = %4.2f 'C\n", cpu_temp);

		;
		if(argc < 2 || strncmp(argv[1], "-c", 2) != 0)
		{
			cpu_temp = 32.0 + 1.8 * cpu_temp;
			printf("CPU temp = %5.2f 'F\n", cpu_temp);
		}

	}

	return 0;
//echo GPU $(/opt/vc/bin/vcgencmd measure_temp)
//	printf("GPU temp = %d 'C\n", 0);
}
