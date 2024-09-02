/*En la tranquila cafetería de la esquina, donde los aromas del café recién molido se mezclan con las conversaciones de los asistentes, un misterio ha surgido.
 Los granos dorados, una edición limitada de café conocida por su sabor excepcional, han desaparecido.
 El Barista, creador y supervisor de la cafetería, ha convocado a los asociados y a los vigilantes para resolver el enigma.
Se ha descubierto que los granos dorados han sido escondidos en uno de los muchos frascos de la cafetería, pero están codificados con un sistema numérico complejo. 
Cada frasco tiene un número único y solo aquellos que descifren el código podrán encontrar los granos dorados.
Tu tarea es crear un programa que descifre el código. Se te proporcionará un archivo llamado “codigos_secretos.txt” que contiene una lista de números. 
Cada número representa un frasco y está codificado de la siguiente manera: 
si el número es primo, el frasco contiene granos comunes; si el número es compuesto y divisible por un número primo 7, contiene granos dorados.*/

#include<stdio.h>
#include<stdlib.h>
int EsPrimo(int num);
int main()
{
    FILE * archivo;//puntero de un archivo
    char caracter;
    int n=0;//numeros dentro el arreglo 
    int columnas=0,d=0;

    archivo= fopen("codigos_secretos.txt","r");/*se abre el archivo*/
    if (archivo==NULL)
    {
        perror("el archivo no se pudo abrir");
        return 1;
    }
    else
    {
        printf("comprovando espacios\n");
        while (!feof(archivo))
        {
            caracter=fgetc(archivo);
            if (caracter == ',')
            {
                n++; 
            }
            if (caracter!=' '&&caracter!= ',')
            {
                d++;
                if (columnas<d)
                {
                    columnas=d;
                }
            }else{
                d=0;
            }
        }
    }
    if(n<0){
        perror("no ahi elementos ");
        return 1;
    }
    int numeros[n];
    char numeros_txt[n][columnas+1];  
    fseek(archivo,0,SEEK_SET);
    int filaActual = 0;
    int columnaActual = 0;
    while ((caracter = fgetc(archivo)) != EOF) {
        if (caracter == ',') {
            numeros_txt[filaActual][columnaActual] = '\0'; // Terminar la cadena actual
            filaActual++;
            columnaActual = 0;
        } else if (caracter != ' ') {
            numeros_txt[filaActual][columnaActual] = caracter;
            columnaActual++;
        }
    }
    for (int i = 0; i < n; i++) {
        numeros[i]= atoi( numeros_txt[i]);
            if (EsPrimo(numeros[i])==1)
            {   
            }
    }
    int c=0;
    for (int i = 0; i < n; i++)
    {
            if (numeros[i]%7==0&&numeros[i]>7)
            {
                c++;
            }

    } 
    int ganador[c],j=0;
    for (int i = 0; i < n; i++)
    {
            if (numeros[i]%7==0&&numeros[i]>7)
            {
                ganador[j]=numeros[i];j++;
            }
    }

    fclose(archivo);
    FILE * guardar;
    guardar = fopen("registros_ordenados.txt", "w");
    if (guardar==NULL)
    {
        perror("el archivo no se pudo abrir");
        return 1;
    }else{
    printf("los ganadores son \n");
    for (int  i = 0; i < c; i++)
    {
        printf("%i, ",ganador[i]);
        fprintf(guardar,"%i, ",ganador[i]);
        
    }
    }
    fclose(guardar);
 return 0;}
int EsPrimo(int num){
    if (num <=1)
    {
        return 0;
    }else if (num==2)
    {
        return 1;
    
    }
    else
    {
        for (int j = 3; j <=(num)/2 ; j++)
        {
            if (num%j==0)
            {return 0;
            }
        }
        return 1;//si es primo 
    }
    
    }

  