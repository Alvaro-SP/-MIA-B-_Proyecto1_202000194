#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>
#include <string.h>
#include "mkdisk.h"
#include <vector>
using namespace std;


//todo ████████████ CLASS DE MI SESION ACTIVA  ████████████ 
class Sesion
    {
    public:

        string user;
        string pass;
        string path;
        string namePartition;
        string id;
        string idUser;
        string idGrp;
        Sesion();
        void cerrar();
    };
Sesion::Sesion()
{
    user= "";
    pass="";
    path = "";
    namePartition = "";
    id = "";
    idGrp = "";
    idUser = "";
}

void Sesion::cerrar()
{
    user = "";
    path = "";
    namePartition = "";
    id = "";

    this->idGrp = "";
    this->idUser = "";
}
//todo ████████████ CLASS DE USUARIOS Y GRUPOS DE MI SISTEMA  ████████████ 
class User{
public:
    std::string id;
    char type;
    std::string name;
    std::string password;
    std::string group;
};

class Group{
public:
    std::string id;
    std::string name;
};

class login
{

public:
    // string id; //Indicará el id que se generó con el comando mount.
    // string type;//Indicará que tipo de formateo se realizará.
    // string fs; //Indica el sistema de archivos a formatear.
    login();
    bool existeunaActiva();
    void cerrarsesion();
    MountedPart* obtainMountedPart(string idi);
    void addUser(string usuario , string password ,string grp);
    DISKMOUNT* obtainMountedDisk(string idi);
    void iniciarsesion(string usuario,string password,string id);
    User* searchUsuario(char usr[],char path[],char namePartition[]);
    vector<string> buscarUser(char usr[]);
    // void formato(mkfs *disco);
    // void EXT2format(mkfs *disco);
    // void EXT3format(mkfs *disco);
    
};

#endif // LOGIN_H