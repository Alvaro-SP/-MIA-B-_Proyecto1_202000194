#include <iostream>
#include <fstream>
#include <string.h>
#include "mkdisk.cpp"
#include "removedisk.cpp"
#include "rep.cpp"
#include "login.cpp"
#include "Fdisk.cpp"
#include "mkdir.cpp"
#include "mkfs.cpp"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <dirent.h>
#include "mount.cpp"
#include <cctype>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#include <stdio.h>
// #include "mount.h"
using namespace std;

// "/Downloads/OneDrive_1_2-4-2022/[MIA]HT1_202000194_Codigo/src" g++ -o src main.cpp

//! █████████████████████████████████████████████     BIENVENIDOS.    ██████████████████████████████████████████
//! BIENVENIDO A MI PROYECTO No 1. LECTOR DE COMANDOS Y ADMINISTRADOR DE ARCHIVOS
//*  La aplicación será totalmente en consola, a excepción de los reportes en Graphviz.
//*  Esta no tendrá menús, sino que se utilizarán comandos. No distinguirá entre
//*  mayúsculas y minúsculas. Hay parámetros obligatorios y opcionales. Solo se puede
//*  colocar un comando por línea.
//*  Si se utiliza un parámetro que no está especificado en este documento, debe
//*  mostrar un mensaje de error. Se utilizarán espacios en blanco para separar cada
//*  parámetro. Si se necesita que algún valor lleve espacios en blanco se encerrará
//*  entre comillas " ". Los parámetros pueden venir en cualquier orden

//! ███████████████████████████████████████████  FUNCIONES DEL ANALIZADOR.  ██████████████████████████████████████████
string extract(string cad){
	int pos =cad.find(" ");
	string cadnew = cad.substr(0, pos);
    return cadnew;
}

string quitarcomilla(string cad){
	
	string cadnew = "";
	for (size_t i = 0; i < cad.size(); i++)
	{
		if (cad[i]=='\"')
		{
			
		}else{
			cadnew+=cad[i];
		}
	}
    return cadnew;
}

string extractpath(string cad){
	// cout<<"iniciando a extraer ruta."<<endl<<endl;
	// int pos =cad.find(" ");
	
	string cadnew = "";
	try
	{
		for (size_t i = 0; i < cad.size(); i++)
		{
			if (cad[i]=='\"')
			{
				break;
			}else if(cad[i]==' '){
				cadnew=cad.substr(i);
			}else{
				cadnew=cad;
			}
		}
	}
	catch(...)
	{
		
	}
	
	
	return cadnew;
}

string wordmin(string myargument) //todo solo convertir a minusculas
{
    string mincase = "";
    for (size_t i = 0; i < myargument.size(); i++)
    {
        mincase += tolower(myargument[i]);
    }
    return mincase;
}

vector<string> splitSimulated5(string myargument, char quitar) //todo solo simulo un split
{
    int positioninitial = 0;
    // int positionfound = 0;
    string palabra;
    vector<string> mycommand;

    // while (positioznfound >= 0)
    // {
    //     positionfound = myargument.find(quitar, positioninitial);
    //     palabra = myargument.substr(positioninitial, positionfound - positioninitial);
    //     positioninitial = positionfound + 1;
    //     mycommand.push_back(palabra);
	// 	cout<<palabra<<endl;
    // }
    // return mycommand;


	string cadnew = "";
	string acum="";
	string lodemas="";
	string temp="";
	bool entro=false;
	int temporalint=myargument.size();
	// cout<<"tamano del argumento: "<< myargument.size() << endl;
	for (size_t i = 0; i < myargument.size(); i++)
	{
	   // cout<<"-"<<myargument[i]<<entro<<endl;
		if (myargument[i]==quitar && entro==false)
		{
			temp=myargument;
			mycommand.push_back(quitarcomilla(temp.substr(positioninitial, i - positioninitial)));
			// cout<<"-->"<<temp.substr(positioninitial, i - positioninitial)<<endl;
			positioninitial=i+1;
			
		}else if (myargument[i]=='\"' && entro==false)
		{
		  //  cout<<"entro true"<<endl;
			entro=true;
		}else if(entro==true){
			if(myargument[i]=='\"'){
				
				temp=myargument;
				mycommand.push_back(quitarcomilla(temp.substr(positioninitial, i - positioninitial)));
				// cout<<"-->"<<temp.substr(positioninitial, i - positioninitial)<<endl;
				positioninitial=i+2;
				entro=false;
				i++;
				i++;
			}
			
			
		}else{
		  //  cout<<"else"<<endl;
			// lodemas+=cad.substr(i,1);
		}
	}
	// cout<<"sale del problema"<<endl;
	
	try{
		mycommand.push_back(quitarcomilla(myargument.substr(positioninitial,temporalint - positioninitial)));
		// cout<<"-->"<<myargument.substr(positioninitial,temporalint - positioninitial)<<endl;
	}catch(...){}
	
	return mycommand;



}

vector<string> splitSimulated5viejo(string myargument, char quitar) //todo solo simulo un split
{
    int positioninitial = 0;
    // int positionfound = 0;
    string palabra;
    vector<string> mycommand;

    // while (positionfound >= 0)
    // {
    //     positionfound = myargument.find(quitar, positioninitial);
    //     palabra = myargument.substr(positioninitial, positionfound - positioninitial);
    //     positioninitial = positionfound + 1;
    //     mycommand.push_back(palabra);
	// 	cout<<palabra<<endl;
    // }
    // return mycommand;


	string cadnew = "";
	string acum="";
	string lodemas="";
	bool entro=false;
	for (size_t i = 0; i < myargument.size(); i++)
	{
		if (myargument[i]==quitar && entro==false)
		{
			
			mycommand.push_back(myargument.substr(positioninitial, i - positioninitial));
			positioninitial=i+1;
		}else if (myargument[i]=='\"' && entro==false)
		{
			entro=true;
		}else if(entro==true){
			if(myargument[i]=='\"'){
				entro=false;
				positioninitial=i+1;
			}else{
				cadnew+=myargument.substr(i,1);
			}
			
			
		}else{
			// lodemas+=cad.substr(i,1);
		}
	}
	return mycommand;



}

vector<string> splitene(string myargument, char quitar) //todo solo simulo un split
{
    int posInit = 0;
    int posFound = 0;
    string splitted;
    vector<string> comandos;

	cout<<"\n\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"<<endl;
				
    while (posFound >= 0)
    {
        posFound = myargument.find(quitar, posInit);
        splitted = myargument.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        // cout<<splitted<<endl;
        comandos.push_back(splitted);
    }
	
	cout<<"\n\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\n"<<endl;
	
    return comandos;


}

string extractpath2(string cad){
	// cout<<"iniciando a extraer ruta."<<endl<<endl;
	// int pos =cad.find(" ");
	string cadnew = "";
	string acum="";
	string lodemas="";
	bool entro=false;
	for (size_t i = 0; i < cad.size(); i++)
	{
		if (cad[i]=='\"' && entro==false)
		{
			entro=true;
		}else if(entro==true){
			if(cad[i]=='\"'){
				entro=false;
			}else{
				cadnew+=cad.substr(i,1);
			}
			
			
		}else{
			lodemas+=cad.substr(i,1);
		}
	}
	return cadnew;
}

string abrir(string mypath) //todo: solo abro el archivo
{
	// cout<<"esta es mi ruta "<<mypath<<endl;

    string mislineas;
    string mytext;
    ifstream file;
    file.open(mypath, ios::in);
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
    return mislineas;
}

vector<string> cleantext(vector<string> cad){
    bool comment = false;
    vector<string> newtext;
    for (size_t i = 0; i < cad.size(); i++)
    {
		// cad[i].erase(std::remove(cad[i].begin(), cad[i].end(), ' '), cad[i].end());
		cad[i].erase(std::remove(cad[i].begin(), cad[i].end(), '\n'),cad[i].end());
		cad[i].erase(std::remove(cad[i].begin(), cad[i].end(), '\r'),cad[i].end());
        if (cad[i][0] != (char)00)
        {
            if (cad[i][0] != '#')
            {
                if (comment == false)
                {
					// cout<<cad[i];
                    newtext.push_back(cad[i]);
                }
            }
            else
            {
                comment = true;
            }
        }
    }
    return newtext;
}

vector<string> split(string cad)
{
	vector<string> mycommand;
    stringstream ss(cad);
    string word;
    while (ss >> word) {
		mycommand.push_back(word);
    }
	return mycommand;
}

vector<string> analizadorState(string myargument){
    vector<string> tokens;
    if (myargument.empty())
    {
        return tokens;
    }
    myargument.push_back(' ');
    string token = "";
    int estado = 0;
    for(char &c: myargument){
        if (estado ==0 && c=='-')
        {
            estado = 1;

        }else if(estado==0 && c=='#'){
            continue;
        }else if(estado!=0){
            if (estado == 1)
            {
                if(c=='='){
                    estado = 2;
                }else if(c == ' '){
                    continue;
                }
            }else if (estado ==4 && c==' ')
            {
                estado = 0;
                tokens.push_back(token);
                token = "";
                continue;
            }else if(estado == 3){
                if (c=='\"')
                {
                    estado = 4;
                }
            }else if(estado == 2){
                if (c=='\"')
                {
                    estado = 3;
                }else{
                    estado = 4;
                }
                
            }else if (estado==4 && c=='\"')
            {
                tokens.clear();
                continue;
            }
            token+=c;
        }
    }
    return tokens;
}


//! █████████████████████████████████████████████  ANALIZADOR SIMPLE.  ██████████████████████████████████████████
void analizer(string mylines) //todo este seria el analizador
{
	//primero lo que necesito hacer teniendo ya el archivo es separar las lineas
	// si fuera el caso de que vengan muchas lineas, sino no.
			
	vector<string> line = splitene(mylines, '\n'); //! estas serian mi array de lineas.
	
	//luego de tener mis lineas ya separacas procedo a analizarlas
	//! recorro mis lineas.
	
	// cout<<line.size()<<endl;
	for (size_t i = 0; i < line.size(); i++)
	{
		// line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		// line.erase(std::remove(line.begin(), line.end(), '\n'),line.end());
		// line.erase(std::remove(line.begin(), line.end(), '\r'),line.end());
		/* code */
		if (line[i][0]=='#'){//* comentarios
			cout<<"\n■■■ Comentario analizado:   "<<line[i]<<endl;
		}
		// cout<<line[i][0]<<endl;
		if (line[i][0] != ' ')
		{	//suponemos un comentario de # en nuestro archivo.
			if (line[i][0] != '#')
			{
				// cout<<"marquita"<<endl;
				// /* code */
				string rutafound = extractpath2(line[i]);
				// cout<<"marquita 2"<<endl;
				// cout<<line[i]<77<endl;
				vector<string> comandos = cleantext(splitSimulated5(line[i], ' ')); //!Separa por espacios cada linea
                //comandos = unir_rutas(comandos);
				// cout<<"marquita 3"<<endl;
				bool sino = true;
			
                
				
			if(comandos.size()>0){
				string mycommand = (comandos[0]);//!obtengo la primer instruccion.
				// mycommand.erase(std::remove(mycommand.begin(), mycommand.end(), ' '), mycommand.end());
				mycommand.erase(std::remove(mycommand.begin(), mycommand.end(), '\n'), mycommand.end());
				mycommand.erase(std::remove(mycommand.begin(), mycommand.end(), '\r'), mycommand.end());
				// cout<<"COMANDO RECONOCIDO: ("<<mycommand<<")"<<endl;
				// if(mycommand=="rep"){
				// 	cout<<"si se reconocio el REP"<<endl;
				// }
				if (mycommand == "mkdisk")
                {
					cout<<"\n\n\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.MKDISK. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;
                    mkdisk *disco = new mkdisk();
					// cout<<"comandos.size():  "<<comandos.size()<<endl;
                    for (size_t j = 1; j < comandos.size(); j++) //!Recorro por toda mi linea
                    {
                        vector<string> comando = splitSimulated5(comandos[j], '=');
						/*-size	Obligatorio	
						Este parámetro recibirá un número que indicará el tamaño
						del disco a crear. Debe ser positivo y mayor que cero, si no
						se mostrará un error.*/
						if (comando[0] == "-size")
                        {
							// stoi convierte a int
                            disco->size = stoi(comando[1]);
                        }//
                        else if (comando[0] == "-fit")
                        {/*Indicará el ajuste que utilizará el disco para crear las
							particiones dentro del disco Podrá tener los siguientes
							valores:*/
                            disco->fit = comando[1];
                        }
                        else if (comando[0] == "-unit")
                        {	/*Este parámetro recibirá una letra que indicará las unidades
							que utilizará el parámetro size. Podrá tener los siguientes
							valores:
							*/
                            disco->unit = comando[1];
                        }
                        else if (comando[0] == "-path")
                        {	/*Este parámetro será la ruta en el que se creará el archivo
							que representará el disco duro*/
							cout<<" pathremove: "<<rutafound<<endl;
							if(rutafound!=""){
								disco->path=rutafound;
							}else{
								disco->path = comando[1];
							}
                            
                        }
						
                        else
                        {
                            cout << "\nEl comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }

                    disco->createDisk(disco);
                }else if(mycommand == "rmdisk"){
					cout<<"\n\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.RMDISK.░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████ "<<endl;
                    removedisk *disco = new removedisk();
					/*Este parámetro elimina un archivo que representa a un disco duro mostrando
						un mensaje de confirmación para eliminar. */
					string pathremove;
					string confirma;
					string concateno="";
					sino=true;

					
                    for (size_t j = 1; j < comandos.size(); j++)
                    {
						vector<string> comando = splitSimulated5(comandos[j], '=');
                        // vector<string> comando = splitSimulated5(comandos[j], '=');
						
						if (comando[0] == "-path")
                        {	/*Este parámetro será la ruta en el que se ELIMINARA el archivo
							que representará el disco duro*/
							// cout<<" pathremove: "<<rutafound<<endl;
							// cout<<" comandoruta: "<<comando[1]<<endl;
							// if(rutafound!=""){
							// 	pathremove=rutafound;
							// }else{
							// 	pathremove = comando[1];
							// }
							concateno.pop_back();

							// Fuente: https://www.iteramos.com/pregunta/18755/eliminar-el-ultimo-caracter-de-la-cadena-de-c
							// concateno+=comando[1];
                            pathremove = concateno;
                        }
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
							sino=false;
                        }
                    }

					if(sino){
						cout << "Do you wish delete this hard Disk? [Y/n]..... \n";
						cout << "usted desea eliminar el disco realmente? [S/n]..... ";					
						cin >> confirma;

						if (confirma == "y" || confirma == "Y"|| confirma == "s"|| confirma == "S")
						{							
							disco->removeDisco(pathremove);
						}
						
					}
					
				}else if(mycommand == "fdisk"){
					/*Este comando administra las particiones en el archivo que representa al disco duro.
						Deberá mostrar un error si no se pudo realizar la operación solicitada sobre la
						partición, especificando por qué razón no pudo crearse (Por espacio, por
						restricciones de particiones, etc.).*/
					cout<<"\n\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.FDISK.░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████ "<<endl;
                    Fdisk *disco = new Fdisk();

                    for (size_t j = 1; j < comandos.size(); j++)
                    {
                        vector<string> comando = splitSimulated5(comandos[j], '=');
						/*-size	Obligatorio	
						Este parámetro recibirá un número que indicará el tamaño
						del disco a crear. Debe ser positivo y mayor que cero, si no
						se mostrará un error.*/
						if (comando[0] == "-size")
                        {   /*/*Este parámetro recibirá un número que indicará el tamañode la partición 
							a crear. */
                            disco->size = stoi(comando[1]);
                        }//
						else if (comando[0] == "-unit")
                        {	/*Este parámetro recibirá una letra que indicará las unidades
							que utilizará el parámetro size. */
                            disco->unit = comando[1];
                        }
						else if (comando[0] == "-path")
                        {	/*Este parámetro será la ruta en el que se creará el archivo
							que representará el disco duro*/
                            disco->path = comando[1];
                        }
						else if (comando[0] == "-name")
                        {/*Indicará el nombre de la partición. */
                            disco->name = comando[1];
                        }
						else if (comando[0] == "-type")
                        {// Indicará que tipo de partición se creará.*/
                            disco->type = comando[1];
                        }
                        else if (comando[0] == "-fit")
                        {/*Indicará el ajuste que utilizará la partición para asignar espacio*/
                            disco->fit = comando[1];
                        }
                        else if (comando[0] == "-delete")
                        {/*Este parámetro indica que se eliminará una partición. Este parámetro 
							se utiliza junto con -name y -path.*/
                            disco->deleted = comando[1];
                        }
                        else if (comando[0] == "-add")
                        {/*Este parámetro se utilizará para agregar o quitar espacio de la partición.*/
                            disco->add = comando[1];
                        }
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }

                    disco->adminPartition(disco);
					
				
				}else if(mycommand == "pause"){
					cout<<"\n\n██████████████████████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.PAUSE.░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓███████████████████████ "<<endl;
                    string ps;
					cout<<"Presione una tecla y enter para continuar....";
							
                    cin >> ps;
                
				}else if(mycommand == "mount"){
					cout<<"\n\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.MOUNT. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;
					// MOUNT montacion;
					mount *disco = new mount();
                    string ruta;
                    for (size_t k = 1; k < comandos.size(); k++)
                    {
                        vector<string> comando = splitSimulated5(comandos[k], '=');
                        if ((comando[0]) == "-path")
                        {
                            disco->path = comando[1];
                        }
                        else if ((comando[0]) == "-name")
                        {
                            disco->name = comando[1];
                        }
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }
                    disco->montar(disco);
                    

				}else if(mycommand == "unmount"){
					cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.UNMOUNT. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;
					mount *disco = new mount();
                    string idi="";
                    for (size_t k = 1; k < comandos.size(); k++)
                    {
                        vector<string> comando = splitSimulated5(comandos[k], '=');
                        if ((comando[0]) == "-id")
                        {
                            idi = comando[1];

                        }
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }
					idi.erase(std::remove(idi.begin(), idi.end(), ' '),  idi.end());
					idi.erase(std::remove(idi.begin(), idi.end(), '\n'), idi.end());
					idi.erase(std::remove(idi.begin(), idi.end(), '\r'), idi.end());
					// char myChars = idi.toCharArray();
					disco->desmontar(idi);
                    // disco->desmontar(idi);
				}else if(mycommand == "mkfs"){
					cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.MKFS. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;
					// Este comando realiza un formateo completo de la partición, se formateará como
					// ext2 por defecto si en caso el parámetro fs no está definido.
					// También creará un archivo en la raíz llamado users.txt que tendrá los usuarios y 
					// contraseñas del sistema de archivos.
					mkfs *disco = new mkfs();
                    for (size_t j = 1; j < comandos.size(); j++)
                    {
                        vector<string> comando = splitSimulated5(comandos[j], '=');
						/*-size	Obligatorio	
						Este parámetro recibirá un número que indicará el tamaño
						del disco a crear. Debe ser positivo y mayor que cero, si no
						se mostrará un error.*/
						if (comando[0] == "-id")
                        {   /*/*Este parámetro recibirá un número que indicará el tamañode la partición 
							a crear. */
                            disco->id = (comando[1]);
                        }//
						else if (comando[0] == "-fs")
                        {	/*Este parámetro recibirá una letra que indicará las unidades
							que utilizará el parámetro size. */
                            disco->fs = comando[1];
                        }
						else if (comando[0] == "-type")
                        {// Indicará que tipo de partición se creará.*/
                            disco->type = comando[1];
                        }
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }
					try
					{
						disco->formato(disco);
					}
					catch(...)
					{
						cout<<"no se pudo ejecutar el MKFS"<<endl;
					}
					

				}else if (mycommand == "login"){
					/*Este comando se utiliza para iniciar sesión en el sistema. No se puede iniciar
					otra sesión sin haber hecho un logout antes, si no, debe mostrar un mensaje
					de error indicando que debe cerrar sesión. Recibirá los Siguientes
					parámetros:*/
					cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.Login. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████\n"<<endl;
					cout<<" 		Iniciando sesion ";
					for (int w = 1; w < 5; w++)
                    {
						cout<<" * ";
						sleep(0.5);
					}
					cout<<"\n";
					login *disco = new login();
					string usuario ="";
					string password="";
					string id="";
					// mkfs *disco = new mkfs();
                    for (size_t j = 1; j < comandos.size(); j++)
                    {
                        vector<string> comando = splitSimulated5(comandos[j], '=');
						/*-size	Obligatorio	
						Este parámetro recibirá un número que indicará el tamaño
						del disco a crear. Debe ser positivo y mayor que cero, si no
						se mostrará un error.*/
						if (comando[0] == "-usuario")
                        {   /*/*Especifica el nombre del usuario que iniciarásesión. */
                            usuario = (comando[1]);
                        }//
						else if (comando[0] == "-password")
                        {	/*Indicará la contraseña del usuario que inicia sesión.*/
                            password = comando[1];
                        }
						else if (comando[0] == "-id")
                        {// Indicará el id de la partición montada de la cual van a iniciar sesión.*/
                            id = comando[1];
                        }
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }
					try
					{
						if(usuario!="" && password!="" && id!=""){

							disco->iniciarsesion(usuario,password,id);
						}else{
							cout<<"\nFFFFFFFFFFF El usuario , password o id no deben estar vacios.  FFFFFFFFFFF\n";
						}
						// disco->formato(disco);
						
					}
					catch(...)
					{
						cout<<"no se pudo ejecutar el MKFS"<<endl;
					}
				}else if (mycommand == "mkfile")
                {
					cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.MKFILE. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████\n"<<endl;
					// Este comando permitirá crear un archivo, el propietario será el usuario que
					// actualmente ha iniciado sesión. Tendrá los permisos 664. El usuario deberá tener
					// el permiso de escritura en la carpeta padre, si no debe mostrar un error. Tendrá los
					// siguientes parámetros
					string thispath;
					string thisid;
                    for (size_t j = 1; j < comandos.size(); j++)
                    {
                        vector<string> comando = splitSimulated5(comandos[j], '=');
						/*-size	Obligatorio	
						Este parámetro recibirá un número que indicará el tamaño
						del disco a crear. Debe ser positivo y mayor que cero, si no
						se mostrará un error.*/
						if (comando[0] == "-r")
                        {   /*/*Este parámetro recibirá un número que indicará el tamañode la partición 
							a crear. */
                            thisid= (comando[1]);
                        }//
						else if (comando[0] == "-path")
                        {	/*Este parámetro recibirá una letra que indicará las unidades
							que utilizará el parámetro size. */
                            thispath = comando[1];
                        } //! Si se ingresan los parámetros cont y size, tendrá mayor prioridad elparámetro cont *
						else if (comando[0] == "-size")
                        {// Indicará que tipo de partición se creará.*/
                            // disco->type = comando[1];
                        }
						else if (comando[0] == "-cont")
                        {// Indicará que tipo de partición se creará.*/
                            // disco->type = comando[1];
                        }
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }
				}
				else if (mycommand == "mkdir")
                {
					cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.MKDIR. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████\n"<<endl;
					//Este comando es similar a mkfile, pero no crea archivos, sino carpetas. El
					//propietario será el usuario que actualmente ha iniciado sesión. Tendrá los permisos
					//664. El usuario deberá tener el permiso de escritura en la carpeta padre, si no debe
					//mostrar un error.
					string thispath;
					string thisid;
                    for (size_t j = 1; j < comandos.size(); j++)
                    {
                        vector<string> comando = splitSimulated5(comandos[j], '=');
						/*-size	Obligatorio	
						Este parámetro recibirá un número que indicará el tamaño
						del disco a crear. Debe ser positivo y mayor que cero, si no
						se mostrará un error.*/
						if (comando[0] == "-id")
                        {   /*/*Este parámetro recibirá un número que indicará el tamañode la partición 
							a crear. */
                            thisid= (comando[1]);
                        }//
						else if (comando[0] == "-path")
                        {	/*Este parámetro recibirá una letra que indicará las unidades
							que utilizará el parámetro size. */
                            thispath = comando[1];
                        }
						else if (comando[0] == "-p")
                        {// Indicará que tipo de partición se creará.*/
                            // disco->type = comando[1];
                        }
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }
                    
                    
                }else if (mycommand == "cat")
                {
                   cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.CAT. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████\n"<<endl;
                }else if (mycommand == "find")
                {
                    cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.FIND. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████\n"<<endl;
                }else if (mycommand == "ren")
                {
                    cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REN. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████\n"<<endl;
                }else if (mycommand == "chmod")
                {
                    cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.CHMOD. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████\n"<<endl;
                }else if (mycommand == "touch")
                {
					cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.TOUCH. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████\n"<<endl;
                    
                } 

				else if(mycommand == "rep"){
					cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;
					// string pathremove;
					string nombre;
					string idi;
					string rutaReport;
					string path;
					sino=true;
                    rep *myreps = new rep();
					for (size_t j = 1; j < comandos.size(); j++) //!Recorro por toda mi linea
                    {
                        vector<string> comando = splitSimulated5(comandos[j], '=');
						/*-size	Obligatorio	
						Este parámetro recibirá un número que indicará el tamaño
						del disco a crear. Debe ser positivo y mayor que cero, si no
						se mostrará un error.*/
						if (comando[0] == "-name")
                        {
							// stoi convierte a int
                            nombre = (comando[1]);
                        }else if (comando[0] == "-id")
                        {/*Indicará el ajuste que utilizará el disco para crear las
							particiones dentro del disco Podrá tener los siguientes
							valores:*/
                            idi = comando[1];
                        }else if (comando[0] == "-ruta")
                        {	/*Este parámetro recibirá una letra que indicará las unidades
							que utilizará el parámetro size. Podrá tener los siguientes
							valores:
							*/
                            rutaReport = comando[1];
                        }else if (comando[0] == "-path")
                        {	/*Este parámetro será la ruta en el que se creará el archivo
							que representará el disco duro*/
                            path = comando[1];
                        }else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }
					//! Luego de obtener los datos ingresados se procede a buscar que reporte es el que desea crear el usuario.
					if(nombre=="mbr"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP MBR. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;
						myreps->mbr(nombre, idi, path, rutaReport);
					}else if(nombre=="disk"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP DISK. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;
						myreps->disk(nombre, idi, path, rutaReport);

					}else if(nombre=="journaling"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP JOURNALING. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;

					}else if(nombre=="block"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP BLOCK. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;

					}else if(nombre=="bm_inode"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP BM_INODE. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;

					}else if(nombre=="bm_block"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP BM_BLOCK. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;

					}else if(nombre=="tree"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP TREE. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;

					}else if(nombre=="sb"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP SB. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;

					}else if(nombre=="file"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP FILE. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;

					}else if(nombre=="ls"){
						cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.REP LS. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;

					}
					
					


				}else{
					if(mycommand=="" || mycommand==" "|| mycommand=="\n"|| mycommand=="\r"){

					}else{
						cout<<"FFFFFFFFF███▓▒░░.Eerror de comando, favor revisar el comando ingresado: "<<mycommand<<" ░░▒▓███FFFFFFFFF "<<endl;
						
					}
					
				}

			}
			
			/* code */
			// cout<<line[i]<<endl;
			}

		}

	}
}


//! █████████████████████████████████████████████    MAIN PRINCIPAL.   ██████████████████████████████████████████
int main()
{
	//! RUN IN PC : 
	//! 	1.	cd /home/alvaro/-MIA-B-_Proyecto1_202000194/src
	//! 	2.	g++ main.cpp -o main
	//! 	3.	./main
	//todo █████████████████████████████████████ MENU PRINCIPAL.  ███████████████████████████████████████
	cout<<"					 ◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_◣_◢_"<<endl;
	cout<<"					 ◣_◢ ◣_◢ ALVARO EMMANUEL SOCOP PEREZ - 202000194  ◣_◢ ◣_◢"<<endl;
	cout<<"					 ◣_◢ ◣_◢       ╔═════════════════════════╗        ◣_◢ ◣_◢"<<endl;
	cout<<"					 ◣_◢ ◣_◢       ║BIENVENIDO A MI PROYECTO!║        ◣_◢ ◣_◢"<<endl;
	cout<<"					 ◣_◢ ◣_◢       ╚═════════════════════════╝        ◣_◢ ◣_◢"<<endl;
	cout<<"					             ıllıllı (Alvaro Socop) ıllıllı 			 "<<endl;
	cout<<"					 ...,,ø¤º°`°º¤ø,¸( LAB. ARCHIVOS B )°º¤ø,¸¸,ø¤º°``''...  "<<endl;
	cout<<"																			 "<<endl;
	cout<<"					                [̲̅F̲̅][̲̅I̲̅][̲̅U][̲̅S][̲̅A][̲̅C̲̅]              "<<endl<<endl;
	cout<<"					---------------------------------------------------------"<<endl<<endl;
	   cout<<"\nDATO: No dejar espacios entre los parametros, de lo contrario puede que tenga errores, Gracias :D\n";
	// Ciclo que se repite por cada comando ingresado
	while(true){
		try
		{
			string command;
			string firstword;
			string tem2;
			
			cout<<"\n\n■■■■■◢◢  Ingrese su comando Sr. :  ";
			// cin>>command;
			getline(cin,command); //! el comando completo
			command=wordmin(command);
			// cout<<"falla"<<endl;
			firstword=extract(command);

			// si es el comando EXEC 
			if ((firstword) == "exec")
			{
				cout<<"\n███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.COMANDO EXEC EJECUTADO. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;
				// cout<<command2<<endl<<endl;
				try
				{
					vector<string> myargument = splitSimulated5(command, '=');
					if(myargument.size()>1){

					
					// cout<<myargument[0]<<endl;
					// cout<<myargument[1]<<endl;
					tem2=myargument[1]; //! tomar solo la ruta
					string cadena = abrir(extractpath(tem2));//! obtener texto del script
					// cout<<cadena<<endl<<endl;
					// analizer(wordmin(cadena));
					// cout<<"hola"<<endl;
					if(cadena!= " " || cadena!= "" || cadena!= "\n"||cadena!= "\r"){

						try {
						// Block of code to try
							
							analizer(wordmin(cadena)); //! obtengo el archivo SCRIPT en minusculas
							// cout<<"Ejecute el comando exec si desea cargar un archivo";
						// throw exception; // Throw an exception when a problem arise
						}
						catch (...) {
						// Block of code to handle errors
						}
					}
					}else{
						cout<<"\nFFFFFFFFFF  ERROR DE COMANDO, VERIFIQUE QUE TENGA TODOS LOS PARAMETROS... FFFFFFFFF\n"<<endl;
					}
				}
				catch(...)
				{
					
				}
				
				
				
			}
			else if((command) == "exit"){
				break;
				// cout<<"exit"<<endl;
			}
			else
			{
				//vector<string> myargument = splitSimulated5(command, '=');
				// cout<<myargument[0]<<endl;
				// cout<<myargument[1]<<endl;
				
				//! cualquier comando unitario que se envie desde la consola
				try {
				// Block of code to try
					analizer(wordmin(command));
					cout<<"\n------------>Ejecute el comando exec si desea cargar un archivo...";
				// throw exception; // Throw an exception when a problem arise
				}
				catch (...) {
				// Block of code to handle errors
				}
				
			}
			// cout<<"end main."<<endl;

		
	}
	catch(...)
	{
		
	}	
		
	}
	cout<<"\n■■▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓Entendible, vuelva pronto.▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓■■\n\n"<<endl;
	return 0;
}
