#include "mkfs.h"
#include "math.h"
#include "v.h"
#include "mkdisk.h"
#include <cstdio>
#include <cctype>
#include <iostream>
mkfs::mkfs()
{
}
MountedPart* mkfs::obtainMountedPart(string idi){
    char* id=&idi[0];
    string str(id);

    cout<<" Id a Desmontar: " << str << endl;
    //* SI la longitud del ID es menor a 4 eso significa de que no es correcto            
    if(strlen(id)<4){
        cout<<"FFFFFFFF No se ha encontrado el Disco a desmontar: ID incorrecto  FFFFFFF";
        return NULL;
    }
    // 94   +   Numero  +   Letra
    char num = str.at(2);

    string s(1, num);
    int contDisks = 0;
    bool existeDisco= false;
    while(partsMounted[contDisks]!=NULL){
        cout<<partsMounted[contDisks]->num <<" con "<< num<<endl;
        if(partsMounted[contDisks]->num == stoi(s)){
            existeDisco = true;
            break;
        }
        contDisks++;
    }
    if(!existeDisco){
        cout<<"FFFFF Error debido a que el disco no existe. FFFFFF";
        return NULL;
    }

    int tampart= 0;
    bool existePart = true;
    int contadorPart = 0;
    
    //! mientras las particiones montadas no sean vacias se aumenta el tamano de la particiones
    while((partsMounted[contDisks])->parts[tampart]!=NULL){
        tampart++;
    }
    //* recorro las particiones montadas y si encuentro una particion que coincida con el id entonces si existe.
    while((partsMounted[contDisks])->parts[contadorPart]!=NULL){
        if(strcmp((partsMounted[contDisks])->parts[contadorPart]->id,id)==0){
            existePart = false;// si existe
            break;
        }
        contadorPart++;
    }
    //! si existe entonces se va a eliminar esa montacion"""
    if(!existePart){
        return partsMounted[contDisks]->parts[contadorPart];
        
        
    }else{
        cout<<"FFFFFFF La particion se encuentra en estado DESMONTADA (No Montada) FFFFFFF";
        return NULL;
    }
}

DISKMOUNT* mkfs::obtainMountedDisk(string idi){
    char* id=&idi[0];
    if(id==NULL) return NULL;
    string str(id);
    if(strlen(id)<4){
        cout<<"FFFFFFFF No se ha encontrado el Disco a desmontar: ID incorrecto  FFFFFFF";
        return NULL;
    }

    // 94   +   Numero  +   Letra
    char num = str.at(2);
    string s(1, num);
    int contDisks = 0;
    bool existeDisco= true;
    while(partsMounted[contDisks]!=NULL){
        cout<<partsMounted[contDisks]->num <<" con "<< num<<endl;
        if(partsMounted[contDisks]->num == stoi(s)){
            existeDisco = false;
            break;
        }
        contDisks++;
    }
    if(existeDisco){
        cout<<"FFFFF Error debido a que el disco no existe. FFFFFF";
        return NULL;
    }

    return partsMounted[contDisks];
}

void mkfs::EXT2format(mkfs *disco)
{
    cout<<"\n       Se ha realizado un formateo para el sistema de archivos EXT2\n";

}
void mkfs::EXT3format(mkfs *disco)
{
    cout<<"\n       Se ha realizado un formateo para el sistema de archivos EXT3\n";

}
void mkfs::formato(mkfs *disco)
{
    if(disco->id.empty() || disco->id=="" || disco->id==" "|| disco->id=="\n"|| disco->id=="\r"){
        cout<<"\nFFFFFFFFF EL ID NO PUEDE ESTAR VACIO.. ERROR    FFFFFFFFFFF"<<endl;
        return;
    }
    string id = disco->id;
    //! INICIANDO EL FORMATEO DE LA PARTICION
    //* validar que la particion sea correcta.
    DISKMOUNT *disk =  obtainMountedDisk(id);
    if(disk==NULL){
        cout<<"El disco no ha sido montado.\n";
        return;
    }
    MountedPart *part = obtainMountedPart(id);
    if(part==NULL){
        cout<<"la partición no fue encontrada.\n";
         return;
    }
    MOUNT mont;
    bool ismount = false;
    bool mountFlag2 = false;


    

    //*2fs: Para el sistema EXT2
    //*Por defecto será ext2.
    if(disco->fs == "2fs" || disco->fs.empty()==1){
        cout<<"\n   Formateando... (Para el sistema EXT2)\n";
        EXT2format(disco);

    }else{
        //*3fs: Para el sistema EXT3
        cout<<"\n   Formateando... (Para el sistema EXT3)\n";
        EXT3format(disco);

    }

    /*También creará un
        archivo en la raíz llamado users.txt que tendrá los usuarios y contraseñas del
        sistema de archivos. La estructura de este archivo se explicará más adelante.*/
}