#include "removedisk.h"
#include <string.h>
#include <string>
#include <iostream>
#include <dirent.h>

removedisk::removedisk()
{
}

bool existthefile(string file)
{
    FILE *myfile;
    myfile = fopen(file.c_str(), "r");
    if(myfile!=NULL){
        fclose(myfile);
        return true;
    }
    else
    {
        return false;
    }
}

void removedisk::removeDisco(string pathnew)
{
    //!Este parámetro elimina un archivo que representa a un disco duro mostrando
    //! un mensaje de confirmación para eliminar


    string Consolecmd;
    Consolecmd = "rm \"" + pathnew + "\"";    
    bool isfile;
    FILE *archivo;
    archivo = fopen(pathnew.c_str(), "r");
    if (archivo!=NULL)
    {
        fclose(archivo);
        isfile = true;
    }
    else
    {
        isfile = false;
    }

    
    if (isfile){
        system(Consolecmd.c_str());
        cout<<"------>      Ok Sr. the Disk went deleted."<<endl;
        cout << "------>    El disco se ha borrado con Exito" << endl;
    }
    else
    {
        cout << "Verifique la ruta: \'" << pathnew << "\'... Porque no se encontro :/"<< endl;
    }
    
}