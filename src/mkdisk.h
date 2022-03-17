#ifndef MKDISK_H
#define MKDISK_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
//! ████████████████████████████████████  INICIO FASE 1  ████████████████████████████████████ 
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

//! ████████████████████████████████████  INICIO FASE 2  ████████████████████████████████████ 
//todo ████████████  Struct SUPERBLOQUE  ████████████ 
struct SuperBlock{
    //  Contiene información sobre la configuración del sistema de archivos. Tendrá los
    //  siguientes valores:
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    char s_mtime[16]; //time
    char s_umtime[16];//time
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_firts_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
};
//todo ████████████  Struct INODO  ████████████ 
struct Inodo{
    int i_uid;
    int i_gid;    
    int i_size;
    char i_atime[16];
    char i_ctime[16];
    char i_mtime[16];    
    int i_block[15];
    char i_type;
    int i_perm;
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