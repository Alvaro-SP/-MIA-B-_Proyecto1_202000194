#include <iostream>
#include <fstream>
#include <string.h>
#include "mkdisk.cpp"
#include "removedisk.cpp"
#include "Fdisk.cpp"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <dirent.h>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
// #include <stdio.h>
// using namespace std;
// "/Downloads/OneDrive_1_2-4-2022/[MIA]HT1_202000194_Codigo/src" g++ -o src main.cpp
using namespace std;
struct Teacher
{
	int Id_teacher;
	char cui[13];
	char nombre[25];
	char curso[25];
};
// typedef struct
struct Student
{
	int Id_student;
	char cui[13];
	char nombre[25];
	char carnet[25];
};
void crearbin5()
{
	FILE *myarchivo = fopen("estudiantes.bin", "w+b");
	FILE *myarchivo2 = fopen("profesores.bin", "w+b");

	// printf("Nombre del file:");
	// gets(nombrestring);
	// para concatenar un string se puede usar     strcat(str1,str2);
	if (myarchivo && myarchivo2)
	{
		printf("si se crearon los archivos");
	}
	else
	{
		printf("ERROR NO SE CREARON LOS ARCHIVOS");
	}
	// printf(myarchivo);
}
void addteach()
{
	FILE *myarchivo = fopen("profesores.bin", "ab");

	if (myarchivo)
	{
		struct Teacher t1;
		// Ingreso de datos:
		printf("\nArchivo estudiante abierto\n\n --ESTRUCTURA DE MAESTRO--\n");

		printf("\nIngrese el ID del maestro: ");
		scanf("%i", &t1.Id_teacher);

		printf("\nIngrese el CUI del maestro: ");
		scanf("%s", t1.cui);

		printf("\nIngrese el NOMBRE del maestro: ");
		scanf("%s", t1.nombre);

		printf("\nIngrese el CURSO del maestro: ");
		scanf("%s", t1.curso);

		// fseek(myarchivo,linea,SEEK_END);
		// fwrite( el apuntador,sizeof(tamanoDeVariable), ElementosAInsertar,myarchivo);
		fwrite(&t1, sizeof(struct Teacher), 1, myarchivo);
		fclose(myarchivo);
		printf("\nSe inserto la estructura en el archivo!! :)");
	}
	else
	{
		printf("\nno se pudo crear hay algun dato malo.");
	};
}
void addstudent()
{
	FILE *myarchivo = fopen("estudiantes.bin", "ab");

	if (myarchivo)
	{
		struct Student t1;
		// Ingreso de datos:
		printf("\nArchivo estudiante abierto\n\n --ESTRUCTURA DE ESTUDIANTE--\n");

		printf("\nIngrese el ID del estudiante: ");
		scanf("%i", &t1.Id_student);

		printf("\nIngrese el CUI del estudiante: ");
		scanf("%s", t1.cui);

		printf("\nIngrese el NOMBRE del estudiante: ");
		scanf("%s", t1.nombre);

		printf("\nIngrese el CARNE del estudiante: ");
		scanf("%s", t1.carnet);

		// fseek(myarchivo,linea,SEEK_END);
		// fwrite( el apuntador,sizeof(tamanoDeVariable), ElementosAInsertar,myarchivo);
		fwrite(&t1, sizeof(struct Student), 1, myarchivo);
		fclose(myarchivo);
		printf("\nSe inserto la estructura en el archivo!! :)");
	}
	else
	{
		printf("\nno se pudo crear hay algun dato malo.");
	};
}
void adds()
{
	FILE *myarchivo = fopen("profesores.bin", "rb");
	struct Teacher t1;
	printf("\n PROFESORES: ");
	if (myarchivo)
	{
		fread(&t1, sizeof(struct Teacher), 1, myarchivo);
		while (!feof(myarchivo))
		{
			printf("\n --------------------------");
			printf("\n --------------------------");
			printf("\n Id_teacher :  %i", t1.Id_teacher);
			printf("\n cui :   %s", t1.cui);
			printf("\n nombre :   %s", t1.nombre);
			printf("\n curso :   %s", t1.curso);
			printf("\n --------------------------");
			fread(&t1, sizeof(struct Teacher), 1, myarchivo);
		}
	}
	else
	{
		printf("El archivo de profesores no existe.");
	};
	fclose(myarchivo);
}
void adds2()
{
	FILE *myarchivo = fopen("estudiantes.bin", "rb");
	struct Student t1;
	printf("\n ESTUDIANTES-: ");
	if (myarchivo)
	{
		fread(&t1, sizeof(struct Student), 1, myarchivo);
		while (!feof(myarchivo))
		{
			printf("\n --------------------------");
			printf("\n --------------------------");
			printf("\n Id_teacher :  %i", t1.Id_student);
			printf("\n cui :   %s", t1.cui);
			printf("\n nombre :   %s", t1.nombre);
			printf("\n curso :   %s", t1.carnet);
			printf("\n --------------------------");
			fread(&t1, sizeof(struct Student), 1, myarchivo);
		}
	}
	else
	{
		printf("El archivo de profesores no existe.");
	};
	fclose(myarchivo);
}

void menu(){
	int menu;
	// primero creo los archivos que usare:
	//  crearbin();
	printf("********Welcome to my Program********\n\n");
	do
	{

		printf("ALVARO EMMANUEL SOCOP PEREZ  --  202000194\n");

		printf("******************************************************\n");
		printf("********************MENU PRINCIPAL*********************\n");
		printf("1.	 Registro de Profesor\n");
		printf("2.	 Registro de Estudiante\n");
		printf("3.	 Ver Registros Profesores\n");
		printf("4.	 Ver Registros Estudiantes\n");
		printf("5.	 Salir\n");
		std::cin >> menu;
		/* code */
		switch (menu)
		{
		case 1:
			addteach();
			break;
		case 2:
			addstudent();
			break;
		case 3:
			adds();
			break;
		case 4:
			adds2();
			break;
		}
	} while (menu != 5);
	printf("Hasta luego.");
}



string wordmin(string myargument) // solo convertir a minusculas
{
    string mincase = "";
    for (int i = 0; i < myargument.size(); i++)
    {
        mincase += tolower(myargument[i]);
    }
    return mincase;
}
vector<string> splitSimulated5(string myargument, char quitar) // solo simulo un split
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
		cout<<palabra<<endl;
    }
    return mycommand;
}

string abrir(string mypath) // solo abro el archivo
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
string extract(string cad){
	int pos =cad.find(" ");
	string cadnew = cad.substr(0, pos);
    return cadnew;
}
string extractpath(string cad){
	// cout<<"iniciando a extraer ruta."<<endl<<endl;
	int pos =cad.find(" ");
	string cadnew = "";
	for (int i = 0; i < cad.size(); i++)
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
	return cadnew;
}
vector<string> cleantext(vector<string> cad){
    bool comment = false;
    vector<string> newtext;
    for (int i = 0; i < cad.size(); i++)
    {
        if (cad[i][0] != (char)00)
        {
            if (cad[i][0] != '#')
            {
                if (comment == false)
                {
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
void analizer(string mylines) //este seria el analizador
{
	//primero lo que necesito hacer teniendo ya el archivo es separar las lineas
	// si fuera el caso de que vengan muchas lineas, sino no.
	vector<string> line = splitSimulated5(mylines, '\n');
	//luego de tener mis lineas ya separacas procedo a analizarlas
	
	for (int i = 0; i < line.size()-2; i++)
	{

		/* code */
		if (line[i][0]=='#'){cout<<"     --"<<line[i]<<endl;}
		// cout<<line[i][0]<<endl;
		if (line[i][0] != ' ')
		{	//suponemos un comentario de # en nuestro archivo.
			if (line[i][0] != '#')
			{
				// /* code */
				// cout<<line[i]<77<endl;
				vector<string> comandos = cleantext(splitSimulated5(line[i], ' ')); //Separa por espacios cada linea
                //comandos = unir_rutas(comandos);
				
                string mycommand = (comandos[0]);
				if (mycommand == "mkdisk")
                {
					cout<<"███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.MKDISK. ░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████"<<endl;
                    mkdisk *disco = new mkdisk();

                    for (int j = 1; j < comandos.size(); j++)
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
                            disco->path = comando[1];
                        }
						
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }

                    disco->createDisk(disco);
                }else if(mycommand == "rmdisk"){
					cout<<"███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.RMDISK.░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████ "<<endl;
                    removedisk *disco = new removedisk();
					/*Este parámetro elimina un archivo que representa a un disco duro mostrando
						un mensaje de confirmación para eliminar. */
					string pathremove;
                    for (int j = 1; j < comandos.size(); j++)
                    {
                        vector<string> comando = splitSimulated5(comandos[j], '=');
						
						if (comando[0] == "-path")
                        {	/*Este parámetro será la ruta en el que se ELIMINARA el archivo
							que representará el disco duro*/
                            pathremove = comando[1];
                        }
                        else
                        {
                            cout << "El comando: " << comando[0] << " es un comando invalido, favor revisarlo." << endl;
                        }
                    }
					disco->removeDisco(pathremove);
				}else if(mycommand == "fdisk"){
					/*Este comando administra las particiones en el archivo que representa al disco duro.
						Deberá mostrar un error si no se pudo realizar la operación solicitada sobre la
						partición, especificando por qué razón no pudo crearse (Por espacio, por
						restricciones de particiones, etc.).*/
					cout<<"███████▓▓▓▓▒▒▒▒▒░░░░░░░░░░░.FDISK.░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓████████ "<<endl;
                    Fdisk *disco = new Fdisk();

                    for (int j = 1; j < comandos.size(); j++)
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
					
				
				}else if (mycommand == "pause"){
                    string ps;
					cout<<"Presione una tecla para continuar....";
							
                    cin >> ps;
                }else{
					cout<<"███▓▒░░.REP.░░▒▓███ "<<endl;
					Fdisk *disco = new Fdisk();
					disco->abrirbin();
				}
			/* code */
			// cout<<line[i]<<endl;
			}



		}

	}
}

int main()
{
	cout<<" ◣_◢ ◣_◢ ALVARO EMMANUEL SOCOP PEREZ - 202000194  ◣_◢ ◣_◢"<<endl;

	cout<<" ◣_◢ ◣_◢ ╔═════════════════════════╗  ◣_◢ ◣_◢"<<endl;
	cout<<" ◣_◢ ◣_◢ ║BIENVENIDO A MI PROYECTO!║  ◣_◢ ◣_◢"<<endl;
	cout<<" ◣_◢ ◣_◢ ╚═════════════════════════╝  ◣_◢ ◣_◢"<<endl;
	cout<<"       ıllıllı (Alvaro Socop) ıllıllı "<<endl;
	cout<<"..,ø¤º°`°º¤ø,¸( LAB. ARCHIVOS B )°º¤ø,¸¸,ø¤º°`"<<endl;
	cout<<""<<endl;
	cout<<"            [̲̅F̲̅][̲̅I̲̅][̲̅U][̲̅S][̲̅A][̲̅C̲̅]  "<<endl<<endl;

	string command;
    string tempcommand;
	while(true){
		command="";
		cout<<"◢◢Ingrese su comando Sr. : ";
		getline(cin,command);

		tempcommand=extract(command);
		if (wordmin(tempcommand) == "exec")
		{
			// cout<<command2<<endl<<endl;
			vector<string> myargument = splitSimulated5(command, '=');
			// cout<<myargument[0]<<endl;
			// cout<<myargument[1]<<endl;
			string tem2=myargument[1];
			string cadena = abrir(extractpath(tem2));
			// cout<<cadena<<endl<<endl;
			analizer(wordmin(cadena));
		}
		else if(wordmin(command) == "exit"){
			break;
		}
		else
		{
			analizer(command);
			cout<<"Ejecute el comando exec si desea cargar un archivo";
		}
		cout<<"end main."<<endl;
	}
	cout<<"Entendible, vuelva pronto."<<endl;
	return 0;
}
