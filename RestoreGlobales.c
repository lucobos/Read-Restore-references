/*
 * Programa que recupera las posiciones relativas de las referencias de todos los módulos de un layout que han sido guardadas
 * previamente en el fichero ficheroPCB-RelativasGlobales.csv con el programa ReadGlobales.c
 *
 */


#include "gemelos.h"
#include "extrae.h"
#include "cambia.h"

void main(int argc, char *argv[])
{
// argv[1] fichero original .kicad_pcb
// argv[2] fichero con las coordenadas de posicionamiento de las referencias
char ficherosalida[MAXCHAR]="Salida.kicad_pcb";	//fichero de salida que tomará el nombre original del fichero de entrada	
char old[MAXCHAR];				//nuevo nombre del fichero de entrada ,renombrado como .kicad_pcb.old
FILE *entrada;
FILE *pcb;
FILE *nuevo;
int i=0,j=0;
int huellastotales=0;
char linea[LONG];
char referencia[LONG]="";
char modulo[LONG];

if (argc < 3)
	{
	printf("\n\tSe necesitan 2 ficheros de entrada en línea de ejecución\n");
	printf("\tFichero1: fichero original ficheroPCB.kicad_pcb\n");
	printf("\tFichero2: fichero con las referencias : ficheroPCB-RelativasGlobales.csv\n\n");
	exit(0);
	}
	
	
if ((entrada=fopen(argv[2], "r"))==NULL)
	{
	printf("\nNo se puede abrir el fichero %s\n",argv[2]);
	exit(0);
	}

// Leo la tabla de referencias guardadas en ficheroPCB-RelativasGlobales.csv
fscanf(entrada,"%d", &huellastotales);
char listaref[huellastotales][COL][LONG];	//Array de las coordenadas relativas de posicionado de las referencias
for (i=0; i<huellastotales ; i++)
	for (j=0; j<COL ; j++)
		fscanf(entrada,"%s",listaref[i][j]);
fclose(entrada);


if ((pcb=fopen(argv[1],"r"))==NULL)
	{
	printf("\nNo se puede abrir el fichero %s\n",argv[1]);
	exit(0);
	}

if ((nuevo=fopen(ficherosalida, "w"))==NULL)
	{
	printf("\nNo se puede abrir el fichero %s\n",ficherosalida);
	exit(0);
	}

//Sustituyo cada línea con referencia por las referencias guardadas en listaref (ficheroPCB-RelativasGlobales.csv)
while (fgets(linea,LONG,pcb) != NULL)
	{
	strcpy(modulo, linea);
	modulo[VEINTIDOS]='\0';
	if (!strcmp(modulo,"    (fp_text reference"))
	    {
	    extraeref(linea,referencia);
	    cambiaposxposy(huellastotales,referencia,linea,listaref);
	    }
	fputs(linea,nuevo);
	}
fclose(pcb);
fclose(nuevo);

renombrafichero(argv[1],ficherosalida);		//nombro el nuevo como ficheroPCB.kicad_pcb y el original como ficheroPCB.kicad_pcbOld

printf("\nPrograma finalizado\n\n");

} //main()