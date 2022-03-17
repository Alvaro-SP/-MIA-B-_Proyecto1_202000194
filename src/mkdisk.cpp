#include "mkdisk.h"
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <vector>

mkdisk::mkdisk() {}
bool mkdisk::isvalidDirectory(const char *path)
{
    // cout<<path<<endl;
    if (path == NULL)
    {
        return false;
    }

    DIR *directorio;
    bool existeono = false;
    
    directorio = opendir(path);

    if (directorio != NULL)
    {
        existeono = true;
        (void)closedir(directorio);
    }
    return existeono;
}

void mkdisk::createDisk(mkdisk *disco)
{
    //! ████████████  VERIFICACION DE LA RUTA  ████████████
    // Primero validamos de que exista la carpeta donde creare el disco.
    vector<string> ccarpetold = (splitSimulated(disco->path, '/'));
    vector<string> ccarpet ;

    string espacio = " ";
    bool com = false;    
    for (size_t i = 0; i < ccarpetold.size(); i++){//recorro mi vector de la ruta para ver si no hay espacios
        if (ccarpetold[i][0] != (char)00)//!si no es un (char)00
        {
            if (ccarpetold[i][0] != '#')//!si no es un comentario
            {
                if (com == false)//! y si com no ha sido modificado.
                {
                    ccarpet.push_back(ccarpetold[i]);//* meto la posicion de mi vector en el nuevo vector.
                }
            }
            else
            {
                com = true;
            }
        }
    }
    

    string tempath = "";
    string tempath2 = "";
    // cout<<ccarpet.size()<<endl;
    MBR mbr;
    if(ccarpet.size()>0){
        for (size_t  i = 0; i < ccarpet.size()-1; i++)
        {
            tempath += "/" + ccarpet[i];
            // cout<<ccarpet[i]<<"  -----------------------"<<endl;
            // Si las carpetas de la ruta no existen deberán crearse.
            // cout<<"tempath; "<<tempath<<endl;
            if (!isvalidDirectory(tempath.c_str()))
            {
                string comando = "mkdir " + tempath2 + "/\"" + ccarpet[i] + "\"";
                // cout<<"comando; "<<comando<<endl;
                system(comando.c_str());
            }
            tempath2 += "/" + ccarpet[i];
        }

    }
    
    //! EN ESTE MOMENTO YA SE TIENEN CREADAS TODAS LAS CARPETAS DONDE GUARDAR EL DISCO
    /*
    Este parámetro recibirá un número que indicará el tamaño
        del disco a crear. Debe ser positivo y mayor que cero, si no
        se mostrará un error*/
    if(disco->size < 0){
        cout << "FFFFFFFFF      EL TAMANO DEL DISCO ES MENOR QUE 0      FFFFFFFFF" << endl;
        return;
    }
    
    FILE *archivo;
    archivo = fopen(disco->path.c_str(), "wb");
    if (archivo == NULL)
    {
        cout << "El archivo no existe." << endl;
        return;
    }
    //! ████████████  VALIDACION DE FIT  ████████████
    //!Indicará el ajuste que utilizará el disco para crear las
    //!particiones dentro del disco Podrá tener los siguientes valores:
    if (disco->fit == "b" ||disco->fit == "bf" || disco->unit.empty() ) //Indicará el mejor ajuste (Best Fit)
    {
        strcpy(mbr.disk_fit, "bf");
        cout<<"Indicará el mejor ajuste (Best Fit)"<<endl;
    }else if(disco->fit == "ff"||disco->fit == "f")
    {
        cout<<"Utilizará el primer ajuste (First Fit)"<<endl;
        strcpy(mbr.disk_fit, "ff");
    }else if(disco->fit == "wf"||disco->fit == "w")
    {
        strcpy(mbr.disk_fit, "wf");
        cout<<"Utilizará el peor ajuste (Worst Fit)"<<endl;
    }else
    {
        strcpy(mbr.disk_fit, "bf");
        cout << "  EL AJUSTE FIT ES INCORRECTO PERO SE ASIGNO BF   " << endl;
    }


    char buffer[1024];
    //! ████████████  VALIDACION DE SIZE  ████████████
    if (disco->unit == "k") //k que indicará que se utilizarán Kilobytes (1024 bytes)
    {
        mbr.mbr_tamano = disco->size * 1024; //todo Tamaño total del disco en bytes
        for (int i = 0; i < 1024; i++)//* Se llena de 0's 
        {
            buffer[i] = '\0';
        }

        for (int i = 0; i < disco->size; i++)
        {
            fwrite(&buffer, 1024, 1, archivo);
        }

        fclose(archivo);
    }else if (disco->unit == "m" || disco->unit.empty() == 1)//m en el que se utilizarán Megabytes (1024 * 1024 bytes)
    {//Este parámetro es opcional, si no se encuentra se creará
        //un disco con tamaño en Megabytes
        mbr.mbr_tamano = disco->size * 1024 * 1024;
        for (int i = 0; i < 1024; i++)
        {
            buffer[i] = '\0';
        }
        for (int i = 0; i < (disco->size * 1024); i++)
        {
            fwrite(&buffer, 1024, 1, archivo);
        }
        fclose(archivo);
    }else{
        // Si se utiliza otro valor debe mostrarse un mensaje de error
        cout << "FFFFFFFFF      LAS UNIDADES SON INCORRECTAS      FFFFFFFFF" << endl;
        return;
    }
    cout<<"Tendra un tamano de : "<<disco->size<<disco->unit<<endl;

    //! ████████████  CREACION DEL MBR AL INICIO DEL DISCO  ████████████
    time_t tiempo = time(0);
    struct tm *loc = localtime(&tiempo);
    char fechacreado[16];
    strftime(fechacreado, 16, "%d/%m/%y %H:%M:%S", loc);

    disco->date_created = fechacreado;

    mbr.mbr_disk_signature = rand(); //todo Número random, que identifica de forma única a cada disco
    strcpy(mbr.mbr_fecha_creacion, fechacreado);//todo Fecha y hora de creación del disco
    
    PARTITION partitions;
    //*Estructuras con información de la partición 1,2,3 y 4
    partitions.part_status = '0';
    partitions.part_type = '-';
    partitions.part_fit = '-';
    partitions.part_start = -1;
    partitions.part_size = -1;
    partitions.part_name[0] = '\0';
    //Agrego las particiones vacias a mi MBR (master boot record.)
    mbr.mbr_p[0]=partitions;
    mbr.mbr_p[1]=partitions;
    mbr.mbr_p[2]=partitions;
    mbr.mbr_p[3]=partitions;
    
    // crearbin(prueba_mbr);

    archivo = fopen(disco->path.c_str(), "rb+");

    if (archivo != NULL)
    {
        fseek(archivo, 0, SEEK_SET);// me posiciono al inicio del archivo
        fwrite(&mbr, sizeof(MBR), 1, archivo); // e inserto el MBR.
        fclose(archivo);
        printf("\nSe inserto el MBR en el archivo!! :)");
        cout << "\n\nEl disco se creo en la ruta: \"" << disco->path << "\"" << endl;
    }
    else
    {
        cout << "FFFFFFFFF  MBR NO fue creado. FFFFFFFFFF" << endl;
    }
}

vector<string> mkdisk::splitSimulated(string myargument, char quitar) // solo simulo un split
{
    int positioninitial = 0;
    int positionfound = 0;
    string palabra;
    vector<string> mycommand;
    while (positionfound >= 0)
    {
        
        positionfound = myargument.find(quitar, positioninitial);
        palabra = myargument.substr(positioninitial, positionfound - positioninitial);
        positioninitial = positionfound + 1;
        mycommand.push_back(palabra);
		// cout<<palabra<<endl;
    }
    return mycommand;
}

void mkdisk::crearbin(MBR prueba_mbr) // solo simulo un split
{
    FILE *myarchivo = fopen("MBR.bin", "ab");

	if (myarchivo)
	{
		
		// fseek(myarchivo,linea,SEEK_END);
		// fwrite( el apuntador,sizeof(tamanoDeVariable), ElementosAInsertar,myarchivo);
		fwrite(&prueba_mbr, sizeof(struct MBR), 1, myarchivo);
		fclose(myarchivo);
		printf("\nSe inserto la estructura en el archivo!! :)");
	}
	else
	{
		printf("\nno se pudo crear hay algun dato malo.");
	};
     
}

void mkdisk::abrirbin() // solo simulo un split
{
    FILE *myarchivo = fopen("MBR.bin", "rb");
	struct MBR prueba_mbr2;
	if (myarchivo)
	{
		fread(&prueba_mbr2, sizeof(struct MBR), 1, myarchivo);
		while (!feof(myarchivo))
		{
			printf("\n --------------------------");
			printf("\n --------------------------");
			printf("\n mbr_tamano:         %i", prueba_mbr2.mbr_tamano);
			printf("\n mbr_fecha_creacion :%s", prueba_mbr2.mbr_fecha_creacion);
			printf("\n mbr_disk_signature :%i", prueba_mbr2.mbr_disk_signature);
			printf("\n --------------------------");
			fread(&prueba_mbr2, sizeof(struct MBR), 1, myarchivo);
		}
	}
	else
	{
		printf("El archivo de MBR no existe.");
	};
	fclose(myarchivo);
    
}



