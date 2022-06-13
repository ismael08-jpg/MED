#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_LNGH 90
#define BANDERA_LOGICA -1 // Usado para eliminación lógica

/*
    ** INTEGRANTES **
    Flamenco Galdámez, Luis Fernando
    Torrez Ramírez, Caleth Abimael
    Reyes Mejía, Nicole Alejandra
    Castillo Martínez, Ismael Alberto

    GRUPO DS19
*/

struct Reo
{
    int clave;             // Clave del reo
    char nombre[MAX_LNGH]; // Nombre del reo
    int edad;              // edad del Reo
    int escolaridad;       // Escolaridad
    int cod_delito;        // codigo del delito
    int nacionalidad;      // nacionalidad
};
typedef struct Reo Reo;
char aux[MAX_LNGH];

// Definiendo prototipos
void menu();
void store();
void search();
void destroy();
void show();
void update();
void generateReprote();

// Obtiene un vector dinamico de Reos
Reo *obtenerReos(int *n);
int validarFilterReo(int edad, int escolaridad, int delito, int nacionalidad, Reo reo);
char existeReo(int claveReo, Reo *Reo);
char insertarReo(Reo Reo);
char eliminarReo(int claveReo);
char modificarReo(Reo Reo);
char guardarReporte();
int readc(char *cad, int n);
char *getDelito(int codDelito);
char *getNacionalidad(int nacion);
char *getEscolaridad(int esco);
void datosReo(Reo reo);

void mainTitle();

// Funciones y metodos
void main()
{
    setlocale(LC_ALL, "Spanish");
    menu();
}

void menu()
{
    char repite = 1;
    int opcion = -1;

    do
    {
        system("cls");
        mainTitle();

        printf("\n\t\t\t\tMENU PRINCIPAL\n");
        printf("\n\t\t[1]. Agregar Reo\n");
        printf("\t\t[2]. Consulta de reos\n");
        printf("\t\t[3]. Modificar datos de un Reo\n");
        printf("\t\t[4]. Eliminar registro de reo\n");
        printf("\t\t[5]. Guardar los datos en el archivo\n");
        printf("\t\t[6]. Salir\n");

        printf("\n\t\tIngrese su opción: | |\b\b");
        readc(aux, MAX_LNGH);
        sscanf(aux, "%d", &opcion);

        switch (opcion)
        {
        case 1:
            store();
            break;
        case 2:
            show();
            break;
        case 3:
            update();
            break;
        case 4:
            destroy();
            break;
        case 5:
            generateReprote();
            break;
        case 6:
            repite = 0;
            break;
        }
    } while (repite);
}

// Funcion para eliminar reo
void destroy()
{
    Reo reo;
    int claveReo;
    char repite = 1;
    char respuesta[MAX_LNGH];

    do
    {
        system("cls");
        mainTitle();
        printf("\n\t\t\t==> ELIMINAR REGISTRO DE REOS <==\n");

        // Solicitar datos del Reo
        printf("\n\tCódigo de Reo: ");
        readc(aux, MAX_LNGH);
        sscanf(aux, "%d", &claveReo);

        // Verificar que el Reo EXISTE
        if (existeReo(claveReo, &reo))
        {
            // Proceder a mostrar datos del registro a eliminar
            datosReo(reo);

            printf("\n\t¿Esta seguro de eliminar? [S/N]: ");
            readc(respuesta, MAX_LNGH);

            if ((strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
                if (eliminarReo(claveReo))
                    printf("\n\tReo eliminado\n");
                else
                    printf("\n\tEl Reo no pudo ser eliminado\n");
        }
        else
        {
            printf("\n\tEl Reo buscado no existe\n");
        }

        printf("\n\t¿Desea continuar eliminando Reos? [S/N]: ");
        readc(respuesta, MAX_LNGH);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
            repite = 0;
    } while (repite);
} // Fin de destroy

// Funcion para busqueda avanzada por diferentes parametros
void filterAdvance()
{
    Reo *reos;
    int escolary = 0;
    int age = 0;
    int delt = 0;
    int origen = 0;
    int numeroReosFilter;
    int i;
    int countFilter = 0;
    int coincideDatoFilter = 0;
    char repite = 1;
    char respuesta[MAX_LNGH];

    do
    {
        system("cls");
        mainTitle();
        printf("\n\t\t\t\t==> BUSCAR REGISTRO DE REOS <==\n");
        printf("\t------------------------------------------------------------------------\n");
        printf("\t|%18s|%30s|%20s|\n", "ESCOLARIDAD   ", "DELITO             ", "NACIONALIDAD    ");
        printf("\t------------------------------------------------------------------------\n");
        printf("\t|%18s|%30s|%20s|\n", "Analfabeto [1] ", "Delito contra la salud [1] ", "Salvadoreño [1] ");
        printf("\t|%18s|%30s|%20s|\n", "Primaria [2] ", "Robo con arma de fuego [2] ", "Estadounidense [2] ");
        printf("\t|%18s|%30s|%20s|\n", "Secundaria [3] ", "Acoso Sexual [3] ", "Guatemalteco [3] ");
        printf("\t|%18s|%30s|%20s|\n", "Preparatoria [4] ", "Agrupaciones ilícitas [4] ", "Hondureño [4] ");
        printf("\t|%18s|%30s|%20s|\n", "Universidad [5] ", "Otros [5] ", "Nicaraguense [5] ");
        printf("\t|%18s|%30s|%20s|\n", "Postgrado [6] ", "", "Mexicano [6] ");
        printf("\t|%18s|%30s|%20s|\n", "", "", "Otro [7] ");
        printf("\t------------------------------------------------------------------------\n");

        // Datos para filtrar
        printf("\t¿Desea filtrar por edad? [S/N]: ");
        readc(respuesta, MAX_LNGH);
        if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
        {
            printf("\n\tFiltro de edad: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &age);
        }
        printf("\t¿Desea filtrar por escolaridad? [S/N]: ");
        readc(respuesta, MAX_LNGH);
        if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
        {
            printf("\n\tFiltro de escolaridad: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &escolary);
        }
        printf("\t¿Desea filtrar por delito? [S/N]: ");
        readc(respuesta, MAX_LNGH);
        if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
        {
            printf("\n\tFiltro de delito: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &delt);
        }
        printf("\t¿Desea filtrar por nacionalidad? [S/N]: ");
        readc(respuesta, MAX_LNGH);
        if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
        {
            printf("\n\tFiltro de nacionalidad: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &origen);
        }

        // reos = advanceFilterList(&numeroReosFilter, age, escolary, delt, origen);
        reos = obtenerReos(&numeroReosFilter);
        if (numeroReosFilter == 0)
        {
            printf("\n\tEl archivo esta vacio\n");
            system("pause");
        }
        else
        {
            for (i = 0; i < numeroReosFilter; i++)
            {
                coincideDatoFilter = validarFilterReo(age, escolary, delt, origen, reos[i]);
                if (coincideDatoFilter)
                {
                    countFilter++;
                }
                coincideDatoFilter = 0;
            }

            if (countFilter > 0)
            {
                system("cls");
                mainTitle();
                printf("\n\t\t\t    ||  LISTADO DE REOS REGISTRADOS ENCONTRADOS ||\n");
                printf(" --------------------------------------------------------------------------------------------------------\n");
                printf("%7s %20s %7s %15s %25s %15s\n", "CLAVE", "NOMBRE", "EDAD", "ESCOLARIDAD", "DELITO", "NACIONALIDAD");
                printf(" --------------------------------------------------------------------------------------------------------\n");

                for (i = 0; i < numeroReosFilter; i++)
                {
                    if (validarFilterReo(age, escolary, delt, origen, reos[i]))
                    {
                        printf("%7d %20.20s %7d %15.20s %25s %15.20s\n", reos[i].clave, reos[i].nombre, reos[i].edad, getEscolaridad((int)reos[i].escolaridad), getDelito((int)reos[i].cod_delito), getNacionalidad((int)reos[i].nacionalidad));
                    }
                }
                printf(" --------------------------------------------------------------------------------------------------------\n");
            }
            else
            {
                printf("\n\t\t\t    ==> No se encontraron registros <== \n");
            }
        }

        printf("\n\t¿Desea continuar buscando Reos? [S/N]: ");
        readc(respuesta, MAX_LNGH);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
            repite = 0;

    } while (repite);
}

// Funcion para verificar si un registro cumple con los filtros
int validarFilterReo(int edad, int escolaridad, int delito, int nacionalidad, Reo reo)
{
    int coincideDatoFilter = 0;
    int count = 0;
    int countCumplen = 0;
    int isOk = 0;
    if (edad != 0)
        count++;

    if (escolaridad != 0)
        count++;

    if (delito != 0)
        count++;

    if (nacionalidad != 0)
        count++;

    if (edad != 0)
    {
        if (edad == reo.edad)
        {
            coincideDatoFilter = 1;
            countCumplen++;
        }
    }

    if (escolaridad != 0)
    {
        if (escolaridad == reo.escolaridad)
        {
            coincideDatoFilter = 1;
            countCumplen++;
        }
    }
    if (delito != 0)
    {
        if (delito == reo.cod_delito)
        {
            coincideDatoFilter = 1;
            countCumplen++;
        }
    }

    if (nacionalidad != 0)
    {
        if (nacionalidad == reo.nacionalidad)
        {
            coincideDatoFilter = 1;
            countCumplen++;
        }
    }

    if (coincideDatoFilter)
    {
        if (count == countCumplen)
        {
            isOk = 1;
        }
    }

    if (count == 0)
    {
        isOk = 1;
    }
    return isOk;
}

// Funcion para buscar
void search()
{
    Reo reo;
    int claveReo;
    char repite = 1;
    char respuesta[MAX_LNGH];

    do
    {
        system("cls");
        mainTitle();

        // Solicitar datos del Reo
        printf("\n\tCódigo de Reo: ");
        readc(aux, MAX_LNGH);
        sscanf(aux, "%d", &claveReo);

        // Verificar que el Reo EXISTE
        if (existeReo(claveReo, &reo))
        {
            // Proceder a mostrar datos
            datosReo(reo);
        }
        else
        {
            printf("\n\tEl Reo buscado no existe\n");
        }

        printf("\n\t¿Desea continuar buscando Reos? [S/N]: ");
        readc(respuesta, MAX_LNGH);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
            repite = 0;

    } while (repite);
} // Fin de search

// Funcion para modificar registros
void update()
{
    Reo reo;
    int claveReo;
    char repite = 1;
    char respuesta[MAX_LNGH];
    int auxEscolaridad = 0;
    int auxNacionalidad = 0;

    do
    {
        system("cls");
        mainTitle();
        printf("\n\t\t\t|**| MODIFICAR REGISTRO DE REOS |**|\n");

        // Solicitar datos del Reo
        printf("\n\tCódigo de Reo: ");
        readc(aux, MAX_LNGH);
        sscanf(aux, "%d", &claveReo);

        // Verificar que el Reo EXISTE
        if (existeReo(claveReo, &reo))
        {
            // Proceder a mostrar datos del registro a eliminar
            datosReo(reo);

            printf("\n\tElija los datos a modificar\n");

            // VALIDANDO CUALES DATOS SE VAN A MODIFICAR

            // Modificando nombre de reo
            printf("\n\tNombre del reo actual: %s\n", reo.nombre);
            printf("\t¿Desea modificar el nombre del reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);

            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tNuevo nombre del reo: ");
                readc(reo.nombre, MAX_LNGH);
            }

            /* Modificación de la edad del reo */
            printf("\n\tEdad del reo actual: %d\n", reo.edad);
            printf("\t¿Desea modificar la edad del reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);

            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\tNueva edad del reo: ");
                readc(aux, MAX_LNGH);
                sscanf(aux, "%d", &reo.edad);
            }

            // Modificando la escolaridad del reo
            printf("\n\tEscolaridad del reo actual: %s\n", getEscolaridad((int)reo.escolaridad));
            printf("\t¿Desea modificar la escolaridad del reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);

            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\n\n\t\t\t   |##| Escolaridad |##|\n");
                printf("\n\t[1] Analfabeto\n\t[2] Primaria\n\t[3] Secundaria\n\t[4] Preparatoria\n\t[5] Universidad\n\t[6] Post Grado\n\tSeleccione la escolaridad del reo: ");
                readc(aux, MAX_LNGH);
                sscanf(aux, "%d", &reo.escolaridad);
            }

            /* Modificación del codigo del delito reo */
            printf("\n\tEl actual delito del reo: %d (%s)\n", reo.cod_delito, getDelito((int)reo.cod_delito));
            printf("\t¿Desea modificar el delito del reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);

            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\n\n\t\t\t   |##| Delito |##|\n");
                printf("\n\t[1] Delito contra la salud\n\t[2] Robo con arma de fuego\n\t[3] Acoso Sexual\n\t[4] Agrupaciones ilícitas\n\t[5] Otros\n\tSeleccione Código del delito cometido por el reo: ");
                readc(aux, MAX_LNGH);
                sscanf(aux, "%d", &reo.cod_delito);
            }

            // Modificando la nacionalidad del reo
            printf("\n\tNacionalidad actual del reo: %s\n", getNacionalidad((int)reo.nacionalidad));
            printf("\t¿Desea modificar la nacionalidad reo? [S/N]: ");
            readc(respuesta, MAX_LNGH);

            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)
            {
                printf("\n\n\t\t\t   |##| Nacionalidad |##|\n");
                printf("\n\t[1] Salvadoreño\n\t[2] Estadounidense\n\t[3] Guatemalteco\n\t[4] Hondureño\n\t[5] Nicaraguense\n\t[6] Mexicano\n\t[7] Otro\n\tSeleccione la Nacionalidad del Reo: ");
                readc(aux, MAX_LNGH);
                sscanf(aux, "%d", &reo.nacionalidad);
            }

            printf("\n\t¿Esta seguro de modificar el registro? [S/N]: ");
            readc(respuesta, MAX_LNGH);

            if ((strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
            {
                // SE PROCEDE CON LA MODIFICACION DEL reo EN EL ARCHIVO
                if (modificarReo(reo))
                    printf("\n\tReo modificado correctamente\n");
                else
                    printf("\n\tEl reo no pudo ser modificado\n");
            }
        }
        else
        {
            printf("\n\tEl reo buscado no existe\n");
        }

        printf("\n\t¿Desea continuar modificando reos? [S/N]: ");
        readc(respuesta, MAX_LNGH);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
            repite = 0;
    } while (repite);
} // Fin de update

// Funcion para insertar registros
void store()
{
    Reo reo;
    int claveReo = 0;
    char repite = 1;
    char respuesta[MAX_LNGH];
    int auxEscolaridad, auxNacionalidad;

    do
    {
        system("cls");
        mainTitle();
        printf("\n\t\t\t   |##| INSERTAR REGISTRO DE REOS |##|\n");

        // Solicitar datos del Reo
        printf("\n\tClave del Reo: ");
        readc(aux, MAX_LNGH);
        sscanf(aux, "%d", &claveReo);

        // Verificar que el Reo no haya sido almacenado anteriormente
        if (!existeReo(claveReo, &reo))
        {
            // Asignar el valor del clave a la estructura
            reo.clave = claveReo;

            // Solicitar el resto de datos
            // Nombre
            printf("\tNombre del Reo: ");
            readc(reo.nombre, MAX_LNGH);

            // Edad
            printf("\tEdad: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &reo.edad);

            // Escolaridad
            printf("\n\n\t\t\t   |##| Escolaridad |##|\n");
            printf("\n\t[1] Analfabeto\n\t[2] Primaria\n\t[3] Secundaria\n\t[4] Preparatoria\n\t[5] Universidad\n\t[6] Post Grado\n\tSeleccione la escolaridad del reo: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &reo.escolaridad);

            // Codigo de delito
            printf("\n\n\t\t\t   |##| Delito |##|\n");
            printf("\n\t[1] Delito contra la salud\n\t[2] Robo con arma de fuego\n\t[3] Acoso Sexual\n\t[4] Agrupaciones ilícitas\n\t[5] Otros\n\tSeleccione Código del delito cometido por el reo: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &reo.cod_delito);

            // Nacionalidad del reo
            printf("\n\n\t\t\t   |##| Nacionalidad |##|\n");
            printf("\n\t[1] Salvadoreño\n\t[2] Estadounidense\n\t[3] Guatemalteco\n\t[4] Hondureño\n\t[5] Nicaraguense\n\t[6] Mexicano\n\t[7] Otro\n\tSeleccione la Nacionalidad del Reo: ");
            readc(aux, MAX_LNGH);
            sscanf(aux, "%d", &reo.nacionalidad);

            // Insertar el reo en el archivo
            if (insertarReo(reo))
                printf("\n\tEl reo se inserto correctamente\n");
            else
                printf("\n\tOcurrio un problema al insertar\n");
        }
        else
            printf("\n\tLa clave de reo ya EXISTE\n");

        printf("\n\t¿Desea continuar ingresando reos? [S/N]: ");
        readc(respuesta, MAX_LNGH);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
            repite = 0;

    } while (repite);
} // Fin de store

// Funcion para mostrar registros
void show()
{
    Reo *reos;
    int numeroReos;
    int i;
    char respuesta[MAX_LNGH];

    system("cls");
    mainTitle();
    // Obtener un vector dinamico de reos
    reos = obtenerReos(&numeroReos);

    if (numeroReos == 0)
    {
        printf("\n\tEl archivo esta vacio\n");
        system("pause");
    }
    else
    {
        printf("\n\t\t\t    ||  LISTADO DE REOS REGISTRADOS  ||\n");
        printf(" --------------------------------------------------------------------------------------------------------\n");
        printf("%7s %20s %7s %15s %25s %15s\n", "CLAVE", "NOMBRE", "EDAD", "ESCOLARIDAD", "DELITO", "NACIONALIDAD");
        printf(" --------------------------------------------------------------------------------------------------------\n");

        // Recorrer el vector dinamico de reos

        for (i = 0; i < numeroReos; i++)
        {
            // Mostrar unicamente para reos no marcados
            if (reos[i].clave != BANDERA_LOGICA)
            {
                printf("%7d %20.20s %7d %15.20s %25s %15.20s\n", reos[i].clave, reos[i].nombre, reos[i].edad, getEscolaridad((int)reos[i].escolaridad), getDelito((int)reos[i].cod_delito), getNacionalidad((int)reos[i].nacionalidad));
            }
        } // Fin de for
        // Mostrando totales de regitros
        printf(" --------------------------------------------------------------------------------------------------------\n");

        printf("\n\t¿Desea filtrar los datos? [S/N]: ");
        readc(respuesta, MAX_LNGH);
        if ((strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
        {
            filterAdvance();
        } // Fin de if */
        // system("pause");
    }
} // Fin de show

// Funcion para Generar el TXT del reporte de REOS
void generateReprote()
{
    if (guardarReporte())
    {
        printf("\n\tEl reporte fue guardado correctamente\n");
        // system("pause");
        system("reporte_reos.txt"); // Aperturar archivo de texto
    }
    else
        printf("\n\tOcurrio un error al guardar el reporte\n");

    system("pause");
}

// Funcion para vector dinamico de reos
Reo *obtenerReos(int *n)
{
    FILE *archivo;
    Reo reo;
    Reo *reos; // Vector dinamico de reos
    int i;

    // Apertura del archivo en modo lectura
    archivo = fopen("reos.dat", "rb");
    if (archivo == NULL)
    {
        *n = 0; // No se pudo aperturar el archivo
        reos = NULL;
    }
    else
    {
        fseek(archivo, 0, SEEK_END); // Posiciona el cursor al final del archivo
        // Usada para obtener el numero de reos almacenados en el archivo
        *n = ftell(archivo) / sizeof(Reo);

        // Se reserva memoria para todos los reos almacenados en el archivo
        reos = (Reo *)malloc((*n) * sizeof(reo));

        // Se recorre el archivo en forma secuencial
        // Posicionar el cursor al inicio del archivo
        fseek(archivo, 0, SEEK_SET);
        // Lectura de datos
        fread(&reo, sizeof(reo), 1, archivo);
        i = 0;
        while (!feof(archivo))
        {
            reos[i++] = reo;
            // Leer el siguiente registro
            fread(&reo, sizeof(reo), 1, archivo);
        } // FIn del while

        // Cerrando el archivo
        fclose(archivo);
    } // Fin de else archivo

    return reos;
} // Fin de obtenerreos

// Subfuncion para reporte
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

    reos = obtenerReos(&numeroReos);

    if (reos == 0)
    {
        guardado = 0; // No hay registros que mostrar
    }
    else
    {
        /* Abre el archivo en modo texto para escritura */
        archivo = fopen("reporte_reos.txt", "w");

        if (archivo == NULL)
        { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
            guardado = 0;
        }
        else
        {
            fprintf(archivo, "\n\t\t    |]  LISTADO DE REOS REGISTRADOS  [|\n");
            fprintf(archivo, " --------------------------------------------------------------------------------------------------------\n");
            fprintf(archivo, "%7s %20s %7s %15s %25s %15s\n", "CLAVE", "NOMBRE", "EDAD", "ESCOLARIDAD", "DELITO", "NACIONALIDAD");
            fprintf(archivo, " --------------------------------------------------------------------------------------------------------\n");
            for (i = 0; i < numeroReos; i++)
            {
                if (reos[i].clave != BANDERA_LOGICA)
                {
                    fprintf(archivo, "%7d %20.20s %7d %15.20s %25s %15.20s\n", reos[i].clave, reos[i].nombre, reos[i].edad, getEscolaridad((int)reos[i].escolaridad), getDelito((int)reos[i].cod_delito), getNacionalidad((int)reos[i].nacionalidad));
                }
            } // Fin de for
            fprintf(archivo, " --------------------------------------------------------------------------------------------------------\n");
            guardado = 1;

            /* Cierra el archivo */
            fclose(archivo);
        }
    }
    return guardado;
} // Fin de guardarReporte

// Subfuncion para modificar
char modificarReo(Reo reo)
{
    FILE *archivo;
    char modifica;
    Reo reo2;

    /* Abre el archivo para lectura/escritura */
    archivo = fopen("reos.dat", "rb+");

    if (archivo == NULL)
    { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        modifica = 0;
    }
    else
    {
        modifica = 0;
        fread(&reo2, sizeof(reo2), 1, archivo);
        while (!feof(archivo))
        {
            if (reo2.clave == reo.clave)
            {
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
} // Fin de modificarReo

// Subfuncion para eliminacion logica
char eliminarReo(int clave_reo)
{
    FILE *archivo;
    FILE *auxiliar;
    Reo reo;
    char elimina;

    /* Abre el archivo para leer */
    archivo = fopen("reos.dat", "r+b");

    if (archivo == NULL)
        elimina = 0;
    else
    {
        elimina = 0;
        fread(&reo, sizeof(reo), 1, archivo);
        while (!feof(archivo))
        {
            if (reo.clave == clave_reo)
            {
                fseek(archivo, ftell(archivo) - sizeof(reo), SEEK_SET);
                // Marcado para eliminacion
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
} // Fin de eliminarReo

// Funcion para verificar si existe un reo
char existeReo(int clave_reo, Reo *reo)
{
    FILE *archivo;
    char existe;

    // Apertura del archivo en modo lectura
    archivo = fopen("reos.dat", "rb");

    if (archivo == NULL)
        existe = 0; // Indica que no se pudo aperturar el archivo
    else
    {
        existe = 0;
        // Se busca el reo cuyo clave coincida con clave_reo
        fread(&(*reo), sizeof(*reo), 1, archivo);

        while (!feof(archivo))
        {
            if ((*reo).clave == clave_reo)
            {
                existe = 1; // Indica que el clave existe
                break;
            }
            fread(&(*reo), sizeof(*reo), 1, archivo);
        } // FIn del while
        // Cierre del archivo
        fclose(archivo);
    } // Fin de else archivo
    return existe;
} // Fin de existeReo

// Subfuncion para insertar registros
char insertarReo(Reo reo)
{
    FILE *archivo;
    char insercion;

    // Apertura del archivo en modo append
    archivo = fopen("reos.dat", "ab");

    if (archivo == NULL)
        insercion = 0;
    else
    {
        // Escribiendo en archivo
        fwrite(&reo, sizeof(reo), 1, archivo);
        insercion = 1;
        fclose(archivo);
    }

    return insercion;
} // Fin de insertarreo

// Funcion auxiliar para lectura de caracteres
int readc(char *cad, int n)
{
    int i, c;
    c = getchar();
    if (c == EOF)
    {
        cad[0] = '\0';
        return 0;
    }

    if (c == '\n')
    {
        i = 0;
    }
    else
    {
        cad[0] = c;
        i = 1;
    }
    for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        cad[i] = c;
    }
    cad[i] = '\0';

    /*3. LIMPIEZA DEL BUFFER */
    /* Finalmente limpiamos el buffer si es necesario */
    if (c != '\n' && c != EOF) /* es un caracter */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    return 1;
}

// Funcion para obtener texto de delito por el codigo
char *getDelito(int codDelito)
{
    char *b = NULL;
    switch (codDelito)
    {
    case 1:
        b = "Delito contra la salud";
        break;
    case 2:
        b = "Robo con arma de fuego";
        break;
    case 3:
        b = "Acoso Sexual";
        break;
    case 4:
        b = "Agrupaciones ilícitas";
        break;
    case 5:
        b = "Otros";
        break;
    default:
        b = "";
        break;
    }
    return b;
}

// Funcion para obtener texto de escolaridad por el codigo
char *getEscolaridad(int esco)
{
    char *b = NULL;
    switch (esco)
    {
    case 1:
        b = "Analfabeto";
        break;
    case 2:
        b = "Primaria";
        break;
    case 3:
        b = "Secundaria";
        break;
    case 4:
        b = "Preparatoria";
        break;
    case 5:
        b = "Universidad";
        break;
    case 6:
        b = "Postgrado";
        break;
    default:
        b = "";
        break;
    }
    return b;
}

// Funcion para obtener texto de nacionalidad por el codigo
char *getNacionalidad(int nacion)
{
    char *b = NULL;
    switch (nacion)
    {
    case 1:
        b = "Salvadoreño";
        break;
    case 2:
        b = "Estadounidense";
        break;
    case 3:
        b = "Guatemalteco";
        break;
    case 4:
        b = "Hondureño";
        break;
    case 5:
        b = "Nicaraguense";
        break;
    case 6:
        b = "Mexicano";
        break;
    case 7:
        b = "Otro";
        break;
    default:
        b = "";
        break;
    }
    return b;
}

void datosReo(Reo reo)
{
    printf("\n\tClave del reo: %d\n", reo.clave);
    printf("\tNombre del reo: %s\n", reo.nombre);
    printf("\tEdad: %d\n", reo.edad);
    printf("\tEscolaridad: %s\n", getEscolaridad((int)reo.escolaridad));
    printf("\tDelito comitido por el reo: %d (%s)\n", reo.cod_delito, getDelito((int)reo.cod_delito));
    printf("\tNacionalidad: %s\n", getNacionalidad((int)reo.nacionalidad));
}
// Función para mostrar titulo del programa
void mainTitle()
{
    int i;
    printf("\n     =================================================================================================================\n");
    printf("\t\t\t\t\t     ITCA-FEPADE | DIRECCION DE CENTROS PENALES \n");
    printf("\t\t\t\t\t\t   Gestión de privados de libertad\n");

    printf("     =================================================================================================================\n\n");
}
