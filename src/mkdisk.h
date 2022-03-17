#ifndef MKDISK_H
#define MKDISK_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
//todo ████████████  Struct PARTICION  ████████████ 
struct PARTITION
{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
} ;
//todo ████████████  Struct MBR  ████████████ 
struct MBR
{
    int mbr_tamano;
    char mbr_fecha_creacion[16];
    int mbr_disk_signature;
    char disk_fit[1];
    PARTITION mbr_p[4];
} ;
//todo ████████████  Struct EBR  ████████████ 
struct EBR
{
    //! PARTICIONES EXTENDIDAS CON ESTRUCTURA DIFERENTE
    //! estructura llamada EBR (Extended Boot Record) en forma de lista enlazada
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
} ;

//todo ████████████  Struct del MOUNT  ████████████ 
struct MOUNT
{
    string id;
    string path;
    string name;
    int state;
    char tipo;
    PARTITION particion;
    EBR particionL;
} ;
class MountedPart{
public:
    char name[75];
    char id[10];
    int start;
};
//todo ████████████  Struct del DISKMOUNT  ████████████ 
// struct DISKMOUNT
// {
//     string letra;
//     string path; 
//     vector<MOUNT> particiones;
// } ;
struct DISKMOUNT
{
public:
    char path[200];
    int num;
    MountedPart *parts[60];

    DISKMOUNT(){
        int i;
        for(i=0;i<60;i++){
            parts[i]=NULL;
        }
            
    }
} ;

//todo ████████████  Struct PARTITIONS GENERALES  ████████████ 
struct GenPartition{
    // string ruta;
    // string id;
    char ruta[100];
	char id[6];
};

//todo ████████████  MKDISK CONSTRUCTOR  ████████████ 
class mkdisk
    {
    public:
        int size;
        string fit;
        string unit;
        string path;
        string date_created;
       
       
        mkdisk();
        void createDisk(mkdisk *disco);
        bool isvalidDirectory(const char *path);
        vector<string> splitSimulated(string str, char pattern);
        void printMBR();
        void crearbin(MBR prueba_mbr);
        void abrirbin();


    };


#endif // MKDISK_H