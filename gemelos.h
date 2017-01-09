#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LONG 100		//caracteres máximos que creo que puede tener una línea
#define COMIENZOCOORD 8		//posición del primer carácter de la coordenada x de la huella
#define COMIENZOREF 23		//posición del primer carácter de la referencia en el fichero.kicad_pcb
#define COMIENZOPOSX 28		//posición del primer carácter de la coordenada x de la referencia
#define COMIENZOSCH 9		//posición del primer carácter de la referencia en el fichero.sch
#define NUEVE 9			//final de la palabra "module" en la línea que define el comienzo del módulo
#define VEINTIDOS 22		//final de la palabra "(fp_text reference" que define la línea de referencia
#define COL 4			//número de columnas del fichero de bloques: ref posx posy angle
#define MAXCHAR 256		//máximo número de caracteres que puede tener el nombre de un fichero en linux
#define CINCO 5			//caracteres máximos de las tiras up y down
#define COMIENZOMODULOS 13	//posición del primer carácter para leer el número de módulos en fichero.kicad_pcb
