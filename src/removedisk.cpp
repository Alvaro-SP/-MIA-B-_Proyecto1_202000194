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
    Consolecmd="rm \'";
    Consolecmd +=  pathnew +"\'"; 
    bool isfile;
    FILE *archivo;
    cout<<"pathnew: "<<pathnew<<endl;
    archivo = fopen(pathnew.c_str(), "r");
    

    
    try{
        cout<<"Eliminando con cmd: "<<Consolecmd<<endl;
        system(Consolecmd.c_str());
        cout<<"                     ------>      Ok Sr. the Disk went deleted."<<endl;
        cout << "                    ------>    El disco se ha borrado con Exito" << endl;
    }
    catch(...)
    {
        cout << "Verifique la ruta: \'" << pathnew << "\'... Porque no se encontro :/"<< endl;
    }
    
}