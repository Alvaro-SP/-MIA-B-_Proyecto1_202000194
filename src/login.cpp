#include "login.h"
#include "mkfs.h"
#include "mkdisk.h"
#include "math.h"

#include "v.h"
#include "varsesion.h"//* mi variable global, montada en memoria.
#include <cstdio>
#include <cctype>
#include <iostream>
login::login()
{
}

bool login::existeunaActiva(){
    if(active_sesion->user!="" || active_sesion->path!="" || active_sesion->namePartition!="" || active_sesion->id!=""){
        cout<<"----------La sesion activa actualmente es:  (Datos encontrados)"<<endl;
        cout<<"      -Usuario: "<<active_sesion->user<<endl;
        cout<<"      -Ruta: "<<active_sesion->path<<endl;
        cout<<"      -En la Particion: "<<active_sesion->namePartition<<endl;
        cout<<"      -Id: "<<active_sesion->id<<endl;
        return true;
    }
    
    return false;
}

MountedPart* login::obtainMountedPart(string idi){
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
DISKMOUNT* login::obtainMountedDisk(string idi){
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


// string login::abrir(string mypath) //todo: solo abro el archivo
// {
// 	// cout<<"esta es mi ruta "<<mypath<<endl;

//     string mislineas;
//     string mytext;
//     ifstream file;
//     file.open(mypath, ios::in);
//     if (file.fail())
//     {
//         cout << "Error";
//     }
//     while (!file.eof())
//     {
//         getline(file, mytext);
//         mislineas += mytext + "\n";
//     }

//     file.close();
//     return mislineas;
// }


User* login::searchUsuario(char usr[],char path[],char namePartition[]){
    
    User* nameuser;
     
    // char *filePath="users.txt";
    //* Buscando en users.txt

    FILE *myarchivo = fopen("users.txt", "ab");
    
	
	fclose(myarchivo);

    return nameuser;
}

void login::iniciarsesion(string usuario,string password,string id){
    bool isac =existeunaActiva();
    if(isac){
        cout<<"\nEl usuario Tiene una Sesion iniciada.\n";
    }else{
        DISKMOUNT *disco = obtainMountedDisk(id);
        MountedPart *partition = obtainMountedPart(id);
        
        if(disco!=NULL && partition!=NULL){
            char* usuariochar=&usuario[0];
            User *user = searchUsuario(usuariochar,disco->path,partition->name);
            if(user==NULL){
                cout<<"\n   El usuario No existe dentro del sistema, verifique sus credenciales.\n";
                return;
            }
            if(user->password != password){
                cout<<"\n   La contrasena es incorrecta verifiquela.\n";
                return;
            }

            active_sesion->user = &user->name[0];
            active_sesion->pass = &user->password[0];
            active_sesion->path = disco->path;
            active_sesion->namePartition = partition->name;
            active_sesion->id = id;
            active_sesion->idUser = &user->id[0];
            active_sesion->idGrp = &user->group[0];
            cout<<"\n   Bienvenido usuario:"<<usuario<<"\n";
            
        }else{
            cout<<"\n No ha Montado el disco o la particion, Verifique eso por favor"<<endl;
            return;
        }
        
      
    }
}

void login::cerrarsesion(){
    active_sesion->cerrar();
    cout<<"     Esperamos que vuelva pronto...\nSesion cerrada.\n";
}

void login::addUser(string usuario , string password, string grp){
    /*Este comando crea un usuario en la partición. Solo lo puede ejecutar el
    usuario root, si lo utiliza otro usuario deberá mostrar un error.*/

    if(active_sesion->user == "root" && active_sesion->pass=="123"){
        //* SI LA SESION ES EL ADMIN ROOT SI PUEDO CREARLA

        string mislineas;
        string mytext;
        ifstream file;
        file.open("users.txt", ios::in);
        if (file.fail())
        {
            cout << "Error";
        }
        while (!file.eof())
        {
            getline(file, mytext);

            mislineas += mytext + "\n";
        }

        file.close();

        // FILE *myarchivo = fopen("users.txt", "a");
        
        // if (myarchivo)
        // {
        //     fread(&t1, sizeof(struct Student), 1, myarchivo);
        //     while (!feof(myarchivo))
        //     {
        //         printf("\n --------------------------");
        //         printf("\n --------------------------");
        //         printf("\n Id_teacher :  %i", t1.Id_student);
        //         printf("\n cui :   %s", t1.cui);
        //         printf("\n nombre :   %s", t1.nombre);
        //         printf("\n curso :   %s", t1.carnet);
        //         printf("\n --------------------------");
        //         fread(&t1, sizeof(struct Student), 1, myarchivo);
        //     }
        // }
        // else
        // {
        //     printf("El archivo de profesores no existe.");
        // };
        // fclose(myarchivo);

    }
}

