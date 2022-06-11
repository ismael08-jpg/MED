#include <stdio.h>  /* print, scanf */
#include <string.h>
#include <stdlib.h> /* system */
#include <locale.h> /* setlocale */
#define MAX_LNGH 90
#define BANDERA_LOGICA -1 //Usado para eliminación lógica

struct Reo{
    int clave;
    char nombre[MAX_LNGH];
    int edad;//edad del Reo (costo)
    char escolaridad[MAX_LNGH];//Precio de venta
    int cod_delito;//Existencia
   	char nacionalidad[MAX_LNGH];
};
typedef struct Reo Reo;
char aux[MAX_LNGH];

//Definiendo prototipos
void menu();
void store();
void search();
void destroy();
void show();
void update();
void destroyPhysical();

//Obtiene un vector dinamico de Reos
Reo *obtenerReos(int *n);
char existeReo(int claveReo,Reo *Reo);
char insertarReo(Reo Reo);
char eliminarReo(int claveReo);
char eliminacionFisica();
char modificarReo(Reo Reo);
char guardarReporte();
int readc(char *cad,int n);
void mainTitle();


//Funciones y metodos
void main(){
    setlocale(LC_ALL,"Spanish");
    menu();
}

void menu(){
    char repite = 1;
    int opcion =-1;
    
    do{
        system("cls");
        mainTitle();
        
        printf("\n\t\t\t\tMENU PRINCIPAL\n");
        printf("\n\t\t[1]. Insertar nuevo Reo\n");
        printf("\t\t[2]. Mostrar listado de Reos\n");
        printf("\t\t[3]. Eliminar un Reo\n");
        printf("\t\t[4]. Buscar Reo por clave\n");
        printf("\t\t[5]. Modificar un Reo\n");
        printf("\t\t[6]. Eliminación física de registros\n");
        printf("\t\t[7]. Salir\n");
        
        printf("\n\t\tIngrese su opción: | |\b\b");
        readc(aux,MAX_LNGH);
        sscanf(aux,"%d",&opcion);
            
            switch(opcion){
                case 1:
                    store();
                    break;
                case 2:
                    show();
                    break;
                case 3:
                    destroy();
                    break;
                case 4:
                    search();
                    break;
                case 5:
                    update();
                    break;
                case 6:
                    destroyPhysical();
                    break;
                case 7:
                    repite = 0;
                    break;
            }
    }while(repite);
}

//Funcion para eliminar reo
void destroy(){
    Reo reo;
    int claveReo;
    char repite = 1;
    char respuesta[MAX_LNGH];
    
    do{
        system("cls");
        mainTitle();
        printf("\n\t\t\t==> ELIMINAR REGISTRO DE REOS <==\n");
        
        //Solicitar datos del Reo
        printf("\n\tCódigo de Reo: ");
        readc(aux, MAX_LNGH);
        sscanf(aux, "%d", &claveReo);
        
        //Verificar que el Reo EXISTE
        if(existeReo(claveReo,&reo)){
            //Proceder a mostrar datos del registro a eliminar
            printf("\n\tClave del reo: %d\n", reo.clave);
            printf("\tNombre del reo: %s\n", reo.nombre);
            printf("\tEdad: %d\n", reo.edad);
            printf("\tEscolaridad: %s\n", reo.escolaridad);  
            printf("\tCódigo del delito comitido por el reo: %d\n", reo.cod_delito);
            printf("\tNacionalidad: %s\n", reo.nacionalidad);
            
            printf("\n\t¿Esta seguro de eliminar? [S/N]: ");
            readc(respuesta,MAX_LNGH);
            
            if((strcmp(respuesta,"S")==0 || strcmp(respuesta,"s")==0))
                if(eliminarReo(claveReo))
                    printf("\n\tReo eliminado\n");
                else
                    printf("\n\tEl Reo no pudo ser eliminado\n");
        }else{
            printf("\n\tEl Reo buscado no existe\n");
        }
        
        printf("\n\t¿Desea continuar eliminando Reos? [S/N]: ");
        readc(respuesta,MAX_LNGH);
        
        if(!(strcmp(respuesta,"S")==0 || strcmp(respuesta,"s")==0))
            repite = 0;
    }while(repite);
}//Fin de destroy

//Funcion de eliminado fisico
void destroyPhysical(){
    char respuesta[MAX_LNGH];
    
    system("cls");
    mainTitle();
    printf("\n\t\t\t==> ELIMINADO FISICO DE REGISTRO DE REOS <==\n");
    
    printf("\n\tEsta seguro de continuar?[S/N]: ");
    readc(respuesta,MAX_LNGH);
    
    if((strcmp(respuesta,"S")==0 || strcmp(respuesta,"s")==0))
        if(eliminacionFisica()){
            printf("\n\tEliminación terminada correctamente\n");
        }else
            printf("\n\tOcurrio un error en la eliminación fisica\n");
    
    system("pause");
}//Fin de destroyPhysical

//Funcion para buscar
void search(){
    Reo reo;
    int claveReo;
    char repite = 1;
    char respuesta[MAX_LNGH];
    
    do{
        system("cls");
        mainTitle();
        printf("\n\t\t\t==> BUSCAR REGISTRO DE REOS <==\n");
        
        //Solicitar datos del Reo
        printf("\n\tCódigo de Reo: ");
        readc(aux, MAX_LNGH);
        sscanf(aux, "%d", &claveReo);
        
        //Verificar que el Reo EXISTE
        if(existeReo(claveReo,&reo)){
            //Proceder a mostrar datos
            printf("\n\tClave del reo: %d\n", reo.clave);
            printf("\tNombre del reo: %s\n", reo.nombre);
            printf("\tEdad: %d\n", reo.edad);
            printf("\tEscolaridad: %s\n", reo.escolaridad);  
            printf("\tCódigo del delito comitido por el reo: %d\n", reo.cod_delito);
            printf("\tNacionalidad: %s\n", reo.nacionalidad);
        }else{
            printf("\n\tEl Reo buscado no existe\n");
        }
        
        printf("\n\t¿Desea continuar buscando Reos? [S/N]: ");
        readc(respuesta,MAX_LNGH);
        
        if(!(strcmp(respuesta,"S")==0 || strcmp(respuesta,"s")==0))
            repite = 0;
        
    }while(repite);
}//Fin de search

//Funcion para modificar registros
void update(){
    Reo reo;
    int claveReo;
    char repite = 1;
    char respuesta[MAX_LNGH];
    
    do{
        system("cls");
        mainTitle();
        printf("\n\t\t\t|**| MODIFICAR REGISTRO DE REOS |**|\n");
        
        //Solicitar datos del Reo
        printf("\n\tCódigo de Reo: ");
        readc(aux, MAX_LNGH);
        sscanf(aux, "%d", &claveReo);
        
        //Verificar que el Reo EXISTE
        if(existeReo(claveReo,&reo)){
            //Proceder a mostrar datos del registro a eliminar
            printf("\n\tClave del reo: %d\n", reo.clave);
            printf("\tNombre del reo: %s\n", reo.nombre);
            printf("\tEdad: %d\n", reo.edad);
            printf("\tEscolaridad: %s\n", reo.escolaridad);  
            printf("\tCódigo del delito comitido por el reo: %d\n", reo.cod_delito);
            printf("\tNacionalidad: %s\n", reo.nacionalidad);
            
            printf("\n\tElija los datos a modificar\n");
            
            //VALIDANDO CUALES DATOS SE VAN A MODIFICAR

            //Modificando nombre de reo
            printf("\n\tNombre del reo actual: %s\n", reo.nombre);
            printf("\tDesea modificar el nombre del reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);
            
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo nombre del reo: ");
                readc(reo.nombre, MAX_LNGH);
            }

             /* Modificación de la edad del reo */
            printf("\n\tEdad del reo actual: %d\n", reo.edad);
            printf("\t¿Desea modificar la edad del reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);
            
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNueva edad del reo: ");
                readc(aux, MAX_LNGH);
                sscanf(aux, "%d", &reo.edad);
            }

            //Modificando la escolaridad del reo
            printf("\n\tNombre del reo actual: %s\n", reo.escolaridad);
            printf("\t¿Desea modificar la escolaridad del reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);
            
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tLa nueva escolaridad del reo: ");
                readc(reo.escolaridad, MAX_LNGH);
            }

             /* Modificación del codigo del delito reo */
            printf("\n\tEl actual delito del reo: %d\n", reo.cod_delito);
            printf("\t¿Desea modificar el delito del reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);
            
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tEl nuevo delito del reo: ");
                readc(aux, MAX_LNGH);
                sscanf(aux, "%d", &reo.cod_delito);
            }

            //Modificando la nacionalidad del reo
            printf("\n\tNacionalidad actual del reo: %s\n", reo.nacionalidad);
            printf("\t¿Desea modificar la nacionalidad reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);
            
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tLa nueva nacionalidad del reo: ");
                readc(reo.nacionalidad, MAX_LNGH);
            }
            
            printf("\n\t¿Esta seguro de modificar el registro? [S/N]: ");
            readc(respuesta,MAX_LNGH);
            
            
            if((strcmp(respuesta,"S")==0 || strcmp(respuesta,"s")==0)){
                //SE PROCEDE CON LA MODIFICACION DEL reo EN EL ARCHIVO
                if(modificarReo(reo))
                    printf("\n\treo modificado correctamente\n");
                else
                    printf("\n\tEl reo no pudo ser modificado\n");
            }   
        }else{
            printf("\n\tEl reo buscado no existe\n");
        }
        
        printf("\n\t¿Desea continuar modificando reos? [S/N]: ");
        readc(respuesta,MAX_LNGH);
        
        if(!(strcmp(respuesta,"S")==0 || strcmp(respuesta,"s")==0))
            repite = 0;
    }while(repite);
}//Fin de update

//Funcion para insertar registros
void store(){
    Reo reo;
    int claveReo = 0;
    char repite = 1;
    char respuesta[MAX_LNGH];
    int auxEscolaridad, auxNacionalidad;
    
    do{
        system("cls");
        mainTitle();
        printf("\n\t\t\t   |##| INSERTAR REGISTRO DE REOS |##|\n");
        
        //Solicitar datos del Reo
        printf("\n\tClave del Reo: ");
        readc(aux, MAX_LNGH);
        sscanf(aux, "%d", &claveReo);
        
        //Verificar que el Reo no haya sido almacenado anteriormente
        if(!existeReo(claveReo,&reo)){
            //Asignar el valor del clave a la estructura
            reo.clave = claveReo;
            
            //Solicitar el resto de datos
            printf("\tNombre del Reo: ");
            readc(reo.nombre, MAX_LNGH);

            printf("\tEdad: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &reo.edad);

            printf("\n\t[1] Analfabeto\n\t[2] Primaria\n\t[3] Secundaria\n\t[4] Preparatoria\n\t[5] Universidad\n\t[6] Post Grado\n\tSeleccione la escolaridad del reo: ");
            scanf("%d",&auxEscolaridad);


            switch (auxEscolaridad)
            {
                case 1:
                    strcpy(reo.escolaridad,"Analfabeto");
                    break;
                case 2:
                    strcpy(reo.escolaridad,"Primaria");
                    break;
                case 3:
                    strcpy(reo.escolaridad,"Secundaria");
                    break;
                case 4:
                    strcpy(reo.escolaridad,"Preparatoria");
                    break;
                case 5:
                    strcpy(reo.escolaridad,"Universidad");
                    break;
                case 6:
                    strcpy(reo.escolaridad,"Post Grado");
                    break;
                default:
                    readc(reo.escolaridad, MAX_LNGH);
                    break;
            }
            

            printf("\tCódigo del delito cometido: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &reo.cod_delito);

            printf("\tNacionalidad del Reo: ");
            readc(reo.nacionalidad, MAX_LNGH);

            
            //Insertar el reo en el archivo
            if(insertarReo(reo))
                printf("\n\tEl reo se inserto correctamente\n");
            else
                printf("\n\tOcurrio un problema al insertar\n");
            
        }else
            printf("\n\tEl clave de reo ya EXISTE\n");
        
        printf("\n\tDesea continuar ingresando reos? [S/N]: ");
        readc(respuesta,MAX_LNGH);
        
        if(!(strcmp(respuesta,"S")==0 || strcmp(respuesta,"s")==0))
            repite = 0;
            
    }while(repite);
}//Fin de store

//Funcion para mostrar registros
void show(){
    Reo *reos;
    int numeroReos;
    int i;
    char respuesta[MAX_LNGH];
    
    system("cls");
    mainTitle();
    //Obtener un vector dinamico de reos
    reos = obtenerReos(&numeroReos);
    
    if(numeroReos==0){
        printf("\n\tEl archivo esta vacio\n");
        system("pause");
    }else{
        printf("\n\t\t    |]  LISTADO DE REOS REGISTRADOS  [|\n");
        printf(" ------------------------------------------------------------------------------\n");
        printf("%7s %20s %7s %15s %7s %15s\n", "CLAVE", "NOMBRE", "EDAD", "ESCOLARIDAD", "COD. DELITO", "NACIONALIDAD");
        printf(" ------------------------------------------------------------------------------\n");        
        
        //Recorrer el vector dinamico de reos
        
        for(i=0;i<numeroReos;i++){
            //Mostrar unicamente para reos no marcados
            if(reos[i].clave != BANDERA_LOGICA){
                printf("%7d %20.20s %7d %15.20s %7d %15.20s\n", reos[i].clave, reos[i].nombre, reos[i].edad, reos[i].escolaridad, reos[i].cod_delito, reos[i].nacionalidad);
                // costoTotal += reos[i].costo;
                // precioTotal += reos[i].precio;
                // cantidadTotal += reos[i].cantidad;
            }
        }//Fin de for
        //Mostrando totales de regitros
        printf(" ------------------------------------------------------------------------------\n");
       
        
        printf("\n\tDesea guardar el reporte en un archivo de texto? [S/N]: ");
        readc(respuesta,MAX_LNGH);
        
        // if((strcmp(respuesta,"S")==0 || strcmp(respuesta,"s")==0)){
        //     if(guardarReporte()){
        //         printf("\n\tEl reporte fue guardado correctamente\n");
        //         system("pause");
        //         system("reporte.txt");//Aperturar archivo de texto
        //     }
                
        //     else
        //         printf("\n\tOcurrio un error al guardar el reporte\n");
                
        // system("pause");    
        // }//Fin de if    
    }
}//Fin de show

//Funcion para vector dinamico de reos
Reo *obtenerReos(int *n){
    FILE *archivo;
    Reo reo;
    Reo *reos;//Vector dinamico de reos
    int i;
    
    //Apertura del archivo en modo lectura
    archivo = fopen("reos.dat","rb");
    if(archivo == NULL){
        *n = 0;//No se pudo aperturar el archivo
        reos = NULL;
    }else{
        fseek(archivo,0,SEEK_END);//Posiciona el cursor al final del archivo
        //Usada para obtener el numero de reos almacenados en el archivo
        *n = ftell(archivo)/sizeof(Reo);
        
        //Se reserva memoria para todos los reos almacenados en el archivo
        reos = (Reo *)malloc((*n)*sizeof(reo));
        
        //Se recorre el archivo en forma secuencial
        //Posicionar el cursor al inicio del archivo
        fseek(archivo,0,SEEK_SET);
        //Lectura de datos
        fread(&reo,sizeof(reo),1,archivo);
        i=0;
        while(!feof(archivo)){
            reos[i++]=reo;
            //Leer el siguiente registro
            fread(&reo,sizeof(reo),1,archivo);
        }//FIn del while
        
        //Cerrando el archivo
        fclose(archivo);
    }//Fin de else archivo
    
    return reos;
}//Fin de obtenerreos

//Subfuncion para reporte
char guardarReporte()
{
    FILE *archivo;
    char guardado;
    Reo *reos;
    int numeroReos;
    int i;
    float costoTotal;
    float precioTotal;
    int cantidadTotal;
 
    // reos = obtenerReos(&numeroReos); /* Retorna un vector dinámico de reos */
 
    // if (numeroReos == 0) {
    //     guardado = 0;//No hay registros que mostrar
 
    // } else {
    //     /* Abre el archivo en modo texto para escritura */
    //     archivo = fopen("reporte.txt", "w");
 
    //     if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
    //         guardado = 0;
 
    //     } else {
    //         fprintf(archivo, "\n\t\t    ==> LISTADO DE REOS REGISTRADOS <==\n");
    //         fprintf(archivo, " ------------------------------------------------------------------------------\n");
    //         fprintf(archivo, "%8s\t%-20s%15s%15s%10s\n", "CODIGO", "NOMBRE", "COSTO $", "PRECIO $", "CANTIDAD");
    //         fprintf(archivo, " ------------------------------------------------------------------------------\n");
 
    //         /* Se recorre el vector dinámico de reos */
    //         costoTotal = 0;
    //         precioTotal = 0;
    //         cantidadTotal = 0;
    //         for (i = 0; i < numeroReos; i++) {
    //             if (reos[i].clave != BANDERA_LOGICA) {
    //                 fprintf(archivo, "%7d \t%-20.20s%15.1f%15.1f%8d\n", reos[i].clave, reos[i].nombre, reos[i].costo, reos[i].precio, reos[i].cantidad);
    //                 costoTotal += reos[i].costo;
    //                 precioTotal += reos[i].precio;
    //                 cantidadTotal += reos[i].cantidad;
    //             }
    //         }
    //         fprintf(archivo, " ------------------------------------------------------------------------------\n");
    //         fprintf(archivo, "\t\t\t      TOTAL: %15.1f%15.1f%8d", costoTotal, precioTotal, cantidadTotal);
 
    //         guardado = 1;
 
    //         /* Cierra el archivo */
    //         fclose(archivo);
    //     }
    // }
 
    return guardado;
}//Fin de guardarReporte

//Subfuncion para eliminado fisico
char eliminacionFisica()
{
    FILE *archivo;//Original
    FILE *temporal;//Auxiliar (copia)
    Reo reo;
    char elimina = 0;
 
    //Aperturar en modo lectura
    archivo = fopen("reos.dat", "rb");
    //Aperturar el archivo auxiliar en modo escritura
    temporal = fopen("temporal.dat", "wb");
 
    if (archivo == NULL || temporal == NULL) {
        elimina = 0;
    } else {
        /* Se copia en el archivo temporal los registros válidos */
        fread(&reo, sizeof(reo), 1, archivo);
        while (!feof(archivo)) {
            if (reo.clave != BANDERA_LOGICA) {
                fwrite(&reo, sizeof(reo), 1, temporal);
            }
            //Leer el siguiente valor
            fread(&reo, sizeof(reo), 1, archivo);
        }
        /* Se cierran los archivos antes de borrar y renombrar */
        fclose(archivo);
        fclose(temporal);
        //Eliminar el archivo original
        remove("reos.dat");
        //Renombrar el archivo temporal por el original
        rename("temporal.dat", "reos.dat");
 
        elimina = 1;
    }
 
    return elimina;
}//Fin de eliminacionFisica

//Subfuncion para modificar
char modificarReo(Reo reo)
{
    FILE *archivo;
    char modifica;
    Reo reo2;
 
    /* Abre el archivo para lectura/escritura */
    archivo = fopen("reos.dat", "rb+");
 
    if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        modifica = 0;
 
    } else {
        modifica = 0;
        fread(&reo2, sizeof(reo2), 1, archivo);
        while (!feof(archivo)) {
            if (reo2.clave == reo.clave) {
                fseek(archivo, ftell(archivo) - sizeof(reo), SEEK_SET);
                fwrite(&reo, sizeof(reo), 1, archivo);
                modifica = 1;
                break;
            }
            fread(&reo2, sizeof(reo2), 1, archivo);
        }
 
        fclose(archivo);
    }
 
    /* Cierra el archivo */
    return modifica;
}//Fin de modificarReo

//Subfuncion para eliminacion logica
char eliminarReo(int clave_reo){
    FILE *archivo;
    FILE *auxiliar;
    Reo reo;
    char elimina;
    
    /* Abre el archivo para leer */
    archivo = fopen("reos.dat", "r+b");
    
    if(archivo == NULL)
        elimina = 0;
    else{
        elimina = 0;
        fread(&reo, sizeof(reo), 1, archivo);
        while (!feof(archivo)) {
            if (reo.clave == clave_reo) {
                fseek(archivo, ftell(archivo) - sizeof(reo), SEEK_SET);
                //Marcado para eliminacion
                reo.clave = BANDERA_LOGICA;
                fwrite(&reo, sizeof(reo), 1, archivo);
                elimina = 1;
                break;
            }
            fread(&reo, sizeof(reo), 1, archivo);
        }
        fclose(archivo);
    }
    return elimina;
}//Fin de eliminarReo

//Funcion para verificar si existe un reo
char existeReo(int clave_reo, Reo *reo){
    FILE *archivo;
    char existe;
    
    //Apertura del archivo en modo lectura
    archivo = fopen("reos.dat","rb");
    
    if(archivo==NULL)
        existe = 0;//Indica que no se pudo aperturar el archivo
    else{
        existe = 0;
        //Se busca el reo cuyo clave coincida con clave_reo
        fread(&(*reo),sizeof(*reo),1,archivo);
        
        while(!feof(archivo)){
            if((*reo).clave == clave_reo){
                existe = 1;//Indica que el clave existe
                break;
            }
            fread(&(*reo),sizeof(*reo),1,archivo);    
        }//FIn del while
        //Cierre del archivo
        fclose(archivo);
    }//Fin de else archivo
    return existe;
}//Fin de existeReo

//Subfuncion para insertar registros
char insertarReo(Reo reo){
    FILE *archivo;
    char insercion;
    
    //Apertura del archivo en modo append
    archivo = fopen("reos.dat","ab");
    
    if(archivo == NULL)
        insercion = 0;
    else{
        //Escribiendo en archivo
        fwrite(&reo,sizeof(reo),1,archivo);
        insercion = 1;
        fclose(archivo);
    }
    
    return insercion;
}//Fin de insertarreo

//Funcion auxiliar para lectura de caracteres
int readc(char *cad, int n)
{
    int i, c;
    c = getchar();
    if (c == EOF) {
        cad[0] = '\0';
        return 0;
    }
 
    if (c == '\n') {
        i = 0;
    } else {
        cad[0] = c;
        i = 1;
    }
    for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        cad[i] = c;
    }
    cad[i] = '\0';
 
    /*3. LIMPIEZA DEL BUFFER */
    /* Finalmente limpiamos el buffer si es necesario */
    if (c != '\n' && c != EOF) /* es un caracter */
        while ((c = getchar()) != '\n' && c != EOF);
    return 1;
}

//Función para mostrar titulo del programa
void mainTitle()
{
    int i;
    printf("\n     *****************************************************************************\n");
    printf("\t\t\t     Dirección General de Centro Penales\n");
    printf("\t             Gestión de datos de personas privadas de libertad\n");
    
    printf("     *****************************************************************************\n");
 
    i = 0;
    putchar('\n');
    for (; i < 80; i++) {
        putchar('_');
    }
}
