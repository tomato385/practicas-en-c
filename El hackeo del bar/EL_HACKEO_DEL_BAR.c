/*En la tranquila ciudad de JavaBeans, los Cafeteros se encontraban en un dilema. 
Una serie de eventos desafortunados había llevado a la pérdida de los registros de sobres de café más preciados. 
Los Vigilantes del Expreso, siempre atentos, fueron los primeros en notar que algo andaba mal.
Los Expertos Cafeteros confirmaron sus sospechas: los registros habían sido alterados. 
Ahora, dependía de los Maestros Tostadores y los Asociados del Café restaurar el orden, bajo la supervisión del Barista.
!PROBLEMA¡
Se te ha proporcionado un archivo llamado “registros_perdidos.txt” que contiene los registros de inventario de los sobres de café,
pero hay un problema: los datos están codificados y desordenados.
Cada línea del archivo representa un registro, pero la información está encriptada con una secuencia de números y letras */
#include <stdio.h>
#include <stdlib.h>
void darbuelta(char array1[],char array2[], int n);
int HexadecimalADecimal(char array1[], int n);
int potencia(int base,int exponencial);
int LetrasANumeros(char a);
int BinarioADecimal(char array[],int n);
void traducion_fecha(char array[] ,int n,char array2[]);
int main(){
FILE * archivo;//puntero del archivo
char caracter;
int pedidos=0,Ncantidad=0,Nfechas=0,Nnombres=0,i=1,Nreserva_cantidad=0,Nreserva_fechas=0,Nreserva_nombres=0;
archivo = fopen("registros_perdidos.txt","r");//puede precentar errores si no se intica donde se guarda
if (archivo==NULL)
{
    perror("no sepudo abrir el archivo \n");
    return 0;
}else
{
    printf("comprobando el archivo \n");
    while ((caracter = fgetc(archivo)) != EOF)//en este bucle se cuentan las cantidad necesaras guardar todos los caracteres
    {
        if (caracter=='\n')
        {
        if (Nreserva_cantidad<Ncantidad) { Nreserva_cantidad=Ncantidad;}
        if (Nreserva_fechas<Nfechas){Nreserva_fechas=Nfechas;}
        if (Nreserva_nombres<Nnombres){Nreserva_nombres=Nnombres;}
            i=0;Ncantidad=0;Nfechas=0;Nnombres=0;
            pedidos++;
        }else{
        if(caracter==','){i++;}else
        {
        if (i==0) {Ncantidad++;}
        if (i==1){Nfechas++;}
        if(i==2){Nnombres++;}
        }  
        }
    }
}
//se crean los arrays nesesarios para guardar
char cantidad[pedidos][Nreserva_cantidad],fecha[pedidos][Nreserva_fechas],nombre[pedidos][Nreserva_nombres];
char aux_cantidad[pedidos][Nreserva_cantidad];
pedidos=0;i=0;Ncantidad=0;Nfechas=0;Nnombres=0;
fseek(archivo,0,SEEK_SET);
printf("leyendo el archivo\n");
while (((caracter = fgetc(archivo)) != EOF))
{
    if (caracter=='\n')
    {
        nombre[pedidos][Nnombres]='\0';//señala el final del la cadena de caracteres de los nombres, tambien es el final de cada lina del pedido 
        i=0;Ncantidad=0;Nfechas=0;Nnombres=0;
        pedidos++;
    }
    else if(caracter==','){i++;
    }else
    {
    if (i==0) {//se guardan la cadena de caracteres de las cantidades de cada pedido
        cantidad[pedidos][Ncantidad]=caracter;
        Ncantidad++;
    }
    if (i==1){//se guardan la cadena de caracteres de las fechas en la que se realiso cada pedido
        fecha[pedidos][Nfechas]=caracter;
        Nfechas++;
    }
    if(i==2){//seguardan la cadena de caracteres de los nombreas de cada pedido
        nombre[pedidos][Nnombres]=caracter;
        Nnombres++;
    }
    }
}
fclose(archivo);//se cierra el archivo ya que no es nesesario tenerlo abierto
char Fechas_trducidas[pedidos][8];
int Cantidad_traducida[pedidos];
for (int i  = 0; i < pedidos; i++)
{
    traducion_fecha(fecha[i],Nreserva_fechas,Fechas_trducidas[i]);
    darbuelta(cantidad[i],aux_cantidad[i],Nreserva_cantidad);
   Cantidad_traducida[i]= HexadecimalADecimal(cantidad[i],Nreserva_cantidad);
}
FILE * guardar;//puntero del archivo deon de se guardara
guardar = fopen("registros_ordenados.txt","w");//puede precentar errores si no se intica donde se guarda
 if (guardar==NULL)
    {
        perror("el archivo no se pudo abrir");
        return 1;
    }else{
        printf("guardando los dato desifrados\n");
        for (int i = 0; i < pedidos; i++)
        {
            fprintf(guardar,"%i, ",Cantidad_traducida[i]);
            for (int j = 0; j < 8; j++)
            {
                fprintf(guardar,"%c",Fechas_trducidas[i][j]);
            }
            fprintf(guardar,", ");
            for (int j = 0; j < Nreserva_nombres; j++)
            {if (nombre[i][j]!='\0')
            {
              fprintf(guardar,"%c",nombre[i][j]);
            }else{fprintf(guardar,"%c",nombre[i][j]);j=Nreserva_nombres;} 
            }
            fprintf(guardar,"\n");
        }
    }//tiene que quedar asi 5684385, 20230315, Café Arábica
    fclose(guardar);
    printf("termino de guardar");
return 0;
}
void darbuelta(char array1[],char array2[],int n){
    
    for ( int i = 0; i < n; i++) {array2[i]=array1[n-1-i]; }
    for (int i = 0; i < n; i++){array1[i]=array2[i];}
}
int HexadecimalADecimal(char array1[], int n){
    int ret=0;
    for (int i = 0; i < n; i++)
    {
        ret +=LetrasANumeros(array1[i])*potencia(16,i);
    }
    return ret;
}
int potencia(int base,int exponencial){
    if (exponencial==0)
    {
        return 1;
    }else if  (exponencial==1)
    {
        return base;
    }else{
        base=base*potencia(base,exponencial-1);
        return base;
    }
    
}
int LetrasANumeros(char a){
    if (a >='0'&& a<='9')
    {
        return a-'0';
    }
    if (a >='a'&& a<='f')
    {
        return 10+ (a-'a');
    }
    if (a >='A'&& a<='F')
    {
        return 10 + (a-'A');
    }
    return 0;
}
int BinarioADecimal(char array1[],int n){
    int ret=0;
    for (int i = 0; i < n; i++)
    {
        
        ret +=LetrasANumeros(array1[i])*potencia(2,i);
        if (array1[i]==' ')
        {
            return ret;
        }
        
    }
    return ret;}
void traducion_fecha(char array[] ,int n,char array2[]){
char separar[8], auxiliar[8];
int a=0,b=0;   
    for (int i = 0; i < n; i++)
    {
     if (array[i]!=' ')
     {
       separar[a]=array[i];
       a++;
     }
     if (array[i]==' ')
     {
        darbuelta(separar,auxiliar,8);
        array2[b]= BinarioADecimal(separar,8);
        a=0;b++;
     }
    }
    darbuelta(separar,auxiliar,8);
     array2[b]=BinarioADecimal(separar,8);
}