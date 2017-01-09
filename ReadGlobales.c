/*
Programa para guardar las posiciones relativas de las referencias de todos los módulos de un layout
Ficheros de origen: el del propio layout: proyecto.kicad_pcb 
*/

#include "gemelos.h"
#include "extrae.h"
#include "cambia.h"


void main(int argc, char *argv[])
{
// argv[1] fichero original .kicad_pcb
FILE *pcb;			//fichero proyecto.kicad_pcb
FILE *nuevo;		//fichero con las posiciones de las referencias de todos los módulos
char ficherosalida[MAXCHAR];		//tomará el nombre proyecto-ReferenciasGlobales.csv
char linea[LONG];
char modulo[LONG];
char referencia[LONG]="";
int i=0,j=0;
int k,l;
int huellastotales=0;
char ch;
int encontrado = 0;

if (argc < 2)
	{
	printf("\n\tSe necesitan el fichero de entrada en línea de ejecución\n");
	printf("\tFichero: fichero original .kicad_pcb\n");
	exit(0);
	}
	
	
quitaextension(argv[1],ficherosalida);
strcat(ficherosalida,"-RelativasGlobales.csv");

/*Obtengo del fichero .kicad_pcb el número de huellas*/
if ((pcb=fopen(argv[1],"r"))==NULL)
	{
	printf("\nNo se puede abrir el fichero %s\n",argv[1]);
	exit(0);
	}
	
	
while ((fgets(linea,LONG,pcb) != NULL) && (encontrado==0))
	{
	strcpy(modulo, linea);
	modulo[12]='\0';
	if (!strcmp(modulo,"    (modules"))
	    {
		encontrado = 1;
	    huellastotales = extraenumodulos(linea);
	    }
	}
fclose(pcb);

printf("\n\tNúmero de huellas:%i\n",huellastotales);



char listaref[huellastotales][COL][LONG];	//Array de las coordenadas relativas de posicionado de las referencias

for (i=0; i<huellastotales ; i++)	//inicializo listaref por si acaso
	for(l=0; l<COL ; l++)
		{
		strcpy(listaref[i][l],"0");
		}

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
/*Meto en el array listaref las referencias y sus posiciones relativas de todos los bloques*/
i=0;	//por si acaso
while (fgets(linea,LONG,pcb) != NULL)
	{
	strcpy(modulo, linea);
	modulo[VEINTIDOS]='\0';
	if (!strcmp(modulo,"    (fp_text reference"))
	    {
	    extraeref(linea,referencia);
		strcpy(listaref[i][0],referencia);
			
		k=COMIENZOPOSX+strlen(referencia);		//pongo el cursor de lectura del fichero en la coordenda x de l referencia
		j=1; l=0;
		while((ch=linea[k++])!=')')		//copio posx
			{
			if (isspace(ch))
				{
				j++; l=0;
				}
			else
				{
				listaref[i][j][l++]=ch;
				listaref[i][j][l]='\0';
				}
			}
		i++;
		}
	}

fprintf(nuevo, "%d\n",huellastotales);			//la primera línea del archivo de salida contiene el número de módulos
for(i=0; i<huellastotales ; i++)
	{
	for(j=0; j<COL ; j++)
		{
		fputs(listaref[i][j],nuevo);
		fputs("\t",nuevo);
		}
	fputs("\n",nuevo);	
	}

fclose(pcb);
fclose(nuevo);

printf("\n\tFichero de posiciones relativas de referencias:  %s\n\n",ficherosalida);

} //main()