/*
Función para obtener la referencia del componente a partir de la línea que la contiene en .kicad_pcb
Ejemplo:
De la línea (fp_text reference Y5 (at 0 2.9972) (layer F.SilkS), obtener Y5
*/

void extraeref(char linea[LONG], char referencia[LONG])
{
int i=COMIENZOREF;
int j=0;
char ch;
while(!isspace(ch=linea[i++]))
	{
	referencia[j++]=ch;
	referencia[j]='\0';
	}
} /*extraeref() */


/*
Función para obetener la referencia y el número de "part" del componente a parir de la línea que lo contiene en .sch
Ejemplo:
De la línea AR Path="/4F1C9A8B/50F712C4/50853F39" Ref="C110"  Part="1" , obetener C110 y 1
*/
void extraeschparte(char linea[LONG], char referencia[LONG], char parte[LONG])
{
int i=COMIENZOSCH;
int j=0;
char ch;
while ((ch=linea[i++])!='=');
while((ch=linea[++i])!='\"')
	{
	referencia[j++]=ch;
	referencia[j]='\0';
	}
j=0;
while ((ch=linea[i++])!='=');
while((ch=linea[++i])!='\"')
	{
	parte[j++]=ch;
	parte[j]='\0';
	}
} /*extraesch() */

void extraesch(char linea[LONG], char referencia[LONG])
{
int i=COMIENZOSCH;
int j=0;
char ch;
while ((ch=linea[i++])!='=');
while((ch=linea[++i])!='\"')
	{
	referencia[j++]=ch;
	referencia[j]='\0';
	}
} /*extraesch() */

/*Función que cambia lee las coordenadas de los módulos del primer bloque*/
//Referencias y coordenadas: ref posx posy angle en posiciones[i][j]
void extraeposxposy(int numhuellas,int huellastotales,char referencia[LONG],char linea[LONG],char listaref[huellastotales][COL][LONG])
{
int k=COMIENZOPOSX;
int j=1 ;
int i,l=0;
char ch;

for (i=0; i<numhuellas; i++)
	{
	if (!strcmp(referencia,listaref[i][0]))
		{
		k+=strlen(listaref[i][0]);
		
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
		}
	}
} /*extraeposxposy() */



/*Obtengo las coordenadas de las huellas del primer bloque*/
void extraecoordenadas(int numhuellas, int huellastotales,char referencia[LONG],char linea[LONG],char listaref[numhuellas][COL][LONG])
{
int k=COMIENZOCOORD;
int j=1 ;
int i,l=0;
char ch;

for (i=0; i<numhuellas; i++)
	{
	if (!strcmp(referencia,listaref[i][0]))
		{
		while((ch=linea[k++])!=')')		//copio coordenada x, coordenada y, ángulo
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
		}
	}
} /*extraecoordenadas() */



/*
Función para obtener el número de módulos en .kicad_pcb
De la línea  (modules 239), obtener 239
*/
int extraenumodulos(char linea[LONG])
{
int i=COMIENZOMODULOS;
int j=0;
char referencia[LONG];
char ch;
while((ch=linea[i++])!= ')')
	{
	referencia[j++]=ch;
	referencia[j]='\0';
	}
return (atoi(referencia));
} /*extraenumodulos() */