#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

using namespace std;

const int MAX_USUARIOS = 5;
const int MAX_BIBLIOTECARIOS = 5;
const int MAX_LIBROS = 10;

struct S_Tiempo {
	int nDia;
	int nMes;
	int nAnio;
};
class Persona {
protected:
	string nIDPersona;
	string nombre;
	string apellido;
	string correo;
	
public:
	Persona() {}
	
	Persona(int id, const string &nombre, const string &apellido)
		: nIDPersona(to_string(id)), nombre(nombre), apellido(apellido)
	{
		correo = nombre + apellido + "@gmail.com";
	}
	
	void mostrarDatos() const
	{
		cout <<""<< endl;
		cout << "ID:  " << nIDPersona << endl;
		cout << "Nombre: " << nombre << endl;
		cout << "Apellido: " << apellido << endl;
		cout << "Correo: " << correo << endl;
		
	}
	
	virtual void mostrarDatos(string t) const
	{
		cout <<setw(5)<< nIDPersona << setw(8) << nombre << setw(10)<< apellido <<setw(30) << correo << setw(20)<<"\t\t";
		cout << endl;
	}
	
	virtual bool buscar(const string &letras, int &contador) const = 0;
};


class Usuario : public Persona {
private:
	string direccion;
	
public:
	Usuario() {}
	
	Usuario(int id, const string &nombre, const string &apellido, const string &arrDireccion)
		: Persona(id, nombre, apellido), direccion(arrDireccion) {}
	
	string get_direccion() { return direccion; }
	void set_direccion(string d) { direccion = d; }
	
	void mostrarDato() const
	{
		cout << "--usuarios--" << endl;
		Persona::mostrarDatos();
		cout << "Dirección: " << direccion << endl;
		cout << endl;
	}
	
	void mostrarDatos(string titulo) const
	{
		Persona::mostrarDatos(titulo);
		cout  << setw(70)<<direccion << endl;
		cout << endl;
	}
	
	bool buscar(const string &letras, int &contador) const override
	{
		string letrasUpper = letras;
		for (char &c : letrasUpper)
		{
			c = toupper(c);
		}
		
		string nombreUpper = nombre;
		string apellidoUpper = apellido;
		string correoUpper = correo;
		string direccionUpper = direccion;
		
		for (char &c : nombreUpper)
		{
			c = toupper(c);
		}
		for (char &c : apellidoUpper)
		{
			c = toupper(c);
		}
		
		for (char &c : correoUpper)
		{
			c = toupper(c);
		}
		for (char &c : direccionUpper)
		{
			c = toupper(c);
		}
		
		bool encontrado = (nombreUpper.find(letrasUpper) != string::npos) 
			 || (apellidoUpper.find(letrasUpper) != string::npos)
			 || (correoUpper.find(letrasUpper) != string::npos)
			 || (direccionUpper.find(letrasUpper) != string::npos);
		if (encontrado)
		{
			contador++;
			mostrarDatos("COINCIDENCIA");
		}
		
		return encontrado;
	}
};
class GestionUsuarios {
private:
	Persona *usuarios[MAX_USUARIOS];
	int numUsuarios;
	
public:
	GestionUsuarios() : numUsuarios(0) {}
	
	void llenarUsuarios(int nCad, string arrNombres[], string arrApellidos[], string arrDirecciones[])
	{
		srand(time(NULL));
		for (int i = 0; i < nCad; i++)
		{
			int id = 201 + i;
			string nombre = arrNombres[i+rand() % 1];
			string apellido = arrApellidos[i+rand() % 10];
			string direccion = arrDirecciones[rand() % 10];
			usuarios[i] = new Usuario(id, nombre, apellido, direccion);
		}
		numUsuarios = nCad;
	}
	
	void imprimirUsuarios(bool imprimirEnTabla) const
	{
		if (imprimirEnTabla)
		{
			cout << "---------" << "Usuarios" << "-------------" << endl;
			cout << setw(5) << "ID" << setw(8) << "Nombre" << setw(10) << "Apellido" << setw(20) << "Correo" << setw(25)<<"Direccion"<<endl;
			for (int i = 0; i < numUsuarios; i++)
			{
				usuarios[i]->mostrarDatos("usuario");
			}
		}
		else{
			cout << "\nLISTADO DE USUARIOS:" << endl;
			for (int i = 0; i < numUsuarios; i++)
			{
				// Llamar al método mostrarDato de Usuario en lugar de Persona
				Usuario *user = dynamic_cast<Usuario *>(usuarios[i]); // Convertir a Usuario
				if (user != nullptr)
				{
					user->mostrarDato();
				}
			}
		}
	}
	
	void buscarUsuarios(const string &letras_a_buscar) const
	{
		int contador = 0;
		cout << "\nBUSCAR USUARIO:" << endl;
		for (int i = 0; i < numUsuarios; i++)
		{
			usuarios[i]->buscar(letras_a_buscar, contador);
		}
		cout << "Número total de coincidencias: " << contador << endl;
	}
	
};


class Bibliotecario : public Persona {
private:
	string fechaNacimiento;
	
public:
	Bibliotecario() {}
	
	Bibliotecario(int id, const string &nombre, const string &apellido, const string &fechaNacimiento)
		: Persona(id, nombre, apellido), fechaNacimiento(fechaNacimiento) {}
	
	void mostrarDatos() const
	{
		cout << "--BIBLIOTECARIO--" << endl;
		Persona::mostrarDatos();
		cout << "Fecha de Nacimiento: " << fechaNacimiento << endl;
		cout << endl;
	}
	void mostrarDatos(string t) const
	{
		Persona::mostrarDatos(t);
		cout << setw(70)<< fechaNacimiento << endl;
		cout << endl;
	}
	
	bool buscar(const string &letras, int &contador) const override
	{
		string letrasUpper = letras;
		for (char &c : letrasUpper)
		{
			c = toupper(c);
		}
		
		string nombreUpper = nombre;
		string apellidoUpper = apellido;
		string correoUpper = correo;
		for (char &c : nombreUpper)
		{
			c = toupper(c);
		}
		for (char &c : apellidoUpper)
		{
			c = toupper(c);
		}
		for (char &c : correoUpper)
		{
			c = toupper(c);
		}
		
		bool encontrado = (nombreUpper.find(letrasUpper) != string::npos) || (apellidoUpper.find(letrasUpper) != string::npos)|| (correoUpper.find(letrasUpper) != string::npos);
		if (encontrado)
		{
			contador++;
			mostrarDatos("");
		}
		
		return encontrado;
	}
};
class GestionBibliotecarios {
private:
	Persona *bibliotecarios[MAX_BIBLIOTECARIOS];
	int numBibliotecarios;
	
public:
	GestionBibliotecarios() :numBibliotecarios(0) {}
	
	void llenarBibliotecarios(int nCad, string arrNombres[], string arrApellidos[], string arrFechas[])
	{
		srand(time(NULL));
		for (int i = 0; i < nCad; i++)
		{
			int id = 1110 + i;
			string nombre = arrNombres[rand() % 10];
			string apellido = arrApellidos[rand() % 10];
			string fechaNacimiento = arrFechas[rand() % 10];
			bibliotecarios[i] = new Bibliotecario(id, nombre, apellido, fechaNacimiento);
		}
		numBibliotecarios = nCad;
	}
	
	void imprimirBibliotecarios(bool imprimirEnTabla) const
	{
		if (imprimirEnTabla)
		{
			cout << "--BIBLIOTECARIO--" << endl;
			
			cout << setw(5) << "ID" << setw(8) << "Nombre" << setw(10) << "Apellido" << setw(20)<< "Correo: " <<setw(30) << "Fecha Nacimiento" << endl;
			for (int i = 0; i < numBibliotecarios; i++)
			{
				bibliotecarios[i]->mostrarDatos("BIBLIOTECARIO");
			}
		}
		else{
			cout << "\nLISTADO DE BIBLIOTECARIOS:" << endl;
			for (int i = 0; i < numBibliotecarios; i++)
			{
				// Llamar al método mostrarDatos de Bibliotecario en lugar de Persona
				Bibliotecario *biblio = dynamic_cast<Bibliotecario *>(bibliotecarios[i]); // Convertir a Bibliotecario
				if (biblio != nullptr)
				{
					biblio->mostrarDatos();
				}
			}
		}
	}
	
	void buscarBibliotecarios(const string &letras_a_buscar) const
	{
		int contador = 0;
		cout << "\nBUSCAR BIBLIOTECARIO:" << endl;
		for (int i = 0; i < numBibliotecarios; i++)
		{
			bibliotecarios[i]->buscar(letras_a_buscar, contador);
		}
		cout << "Número total de coincidencias: " << contador << endl;
	}
	
};


class Libro {
private:
	int nSNBI;
	string sTituloLibro;
	string sAutorLibro;
	S_Tiempo tFechaPublicacion;
	string sEditorial;
	int nNumEstante;
	string arrEstado;
	
public:
	Libro() {}
	
	Libro(int snbi, const string &titulo, const string &autor, S_Tiempo fecha, const string &editorial, int estante, const string &estado)
		: nSNBI(snbi), sTituloLibro(titulo), sAutorLibro(autor), tFechaPublicacion(fecha), sEditorial(editorial), nNumEstante(estante), arrEstado(estado) {}
	
	void mostrarDatos() const
	{
		cout << "--LIBRO--" << endl;
		cout << "SNBI: " << nSNBI << endl;
		cout << "Título: " << sTituloLibro << endl;
		cout << "Autor: " << sAutorLibro << endl;
		cout << "Fecha de Publicación: " << tFechaPublicacion.nDia << "/" << tFechaPublicacion.nMes << "/" << tFechaPublicacion.nAnio << endl;
		cout << "Editorial: " << sEditorial << endl;
		cout << "Número de Estante: " << nNumEstante << endl;
		cout << "Estado: " << arrEstado << endl;
		cout << endl;
	}
	void mostrarDatos(string Titulo) const
	{
		cout<<setw(1)<<nSNBI<<setw(17)<<sTituloLibro<<setw(16)<<sAutorLibro<<setw(8)
			<<tFechaPublicacion.nDia<<"/"<<tFechaPublicacion.nMes<<"/"<<tFechaPublicacion.nAnio <<
			setw(12)<< sEditorial<<setw(6) << nNumEstante<<setw(9)<< arrEstado<<endl;
		cout << endl;
	}
	
	
	bool buscarLibros(const string &letras, int &contador) const 
	{
		string letrasUpper = letras;
		for (char &c : letrasUpper)
		{
			c = toupper(c);
		}
		
		string tituloUpper = sTituloLibro;
		string autorUpper = sAutorLibro;
		
		
		for (char &c : tituloUpper)
		{
			c = toupper(c);
		}
		for (char &c : autorUpper)
		{
			c = toupper(c);
		}
		
		bool encontrado = (tituloUpper.find(letrasUpper) != string::npos) 
			 || (autorUpper.find(letrasUpper) != string::npos);
		if (encontrado)
		{
			contador++;
			mostrarDatos("COINCIDENCIA");
		}
		
		return encontrado;}
};

class GestionLibros {
private:
	Libro libros[MAX_LIBROS];
	int numLibros;
	
public:
	GestionLibros() : numLibros(0){}
	
	void llenarLibros(int nLibros, string arrTitulos[], string arrAutores[], string arrEditorial[], string arrEstado[])
	{
		srand(time(NULL));
		for (int i = 0; i < nLibros; i++)
		{
			int snbi = 1001 + i;
			string titulo = arrTitulos[rand() % 5];
			string autor = arrAutores[rand() % 5];
			S_Tiempo fecha;
			fecha.nDia = rand() % 30 + 1;
			fecha.nMes = rand() % 12 + 1;
			fecha.nAnio = rand() % 30 + 1990;
			string editorial = arrEditorial[rand() % 5];
			int estante = rand() % 10 + 1;
			string estado = arrEstado[rand() % 3];
			libros[i] = Libro(snbi, titulo, autor, fecha, editorial, estante, estado);
		}
		numLibros = nLibros;
	}
	
	void imprimirLibros(bool imprimirEnTabla) const
	{
		if (imprimirEnTabla)
		{
			cout << setw(1) << "SNBI" << setw(15) << "Título" << setw(13)<< "Autor" << setw(20) << "Publicado"
				<< setw(12) << "Editorial" << setw(9) << "Estante" << setw(8) << "Estado" << endl;
			for (int i = 0; i < numLibros; i++)
			{
				libros[i].mostrarDatos("LIBRO");
			}
		}
		else
		{
			cout << "\nLISTADO DE LIBROS:" << endl;
			for (int i = 0; i < numLibros; i++)
			{
				libros[i].mostrarDatos();
			}
		}
	}
	
	void buscarLibros(const string &letras_a_buscar) const
	{
		int contador = 0;
		cout << "\nBUSCAR LIBROS:" << endl;
		for (int i = 0; i < numLibros; i++)
		{
			libros[i].buscarLibros(letras_a_buscar, contador);
		}
		cout << "Número total de coincidencias: " << contador << endl;
	}
};

int main()
{
	int opcion;
	const int CAD = 5;
	const int LIBROS = 10;
	GestionLibros gestionLibros;
	GestionUsuarios gestionUsuarios;
	GestionBibliotecarios gestionBibliotecarios;
	string arrNombres[] = {"Juan", "Pedro", "Roberto", "Silvia", "Karen", "Rafaela", "Sofia", "Alicia", "Jaime", "Iver"};
	string arrApellidos[] = {"Peralta", "Lazarte", "Cuba", "Torre", "Saucedo", "Ruiz", "Flores", "Herrera", "Fernandez", "Aguilera"};
	string arrDirecciones[] = {"Direccion 1", "Direccion 2", "Direccion 3", "Direccion 4", "Direccion 5", "Direccion 6", "Direccion 7", "Direccion 8", "Direccion 9", "Direccion 10"};
	string arrFechas[] = {"10/01/1980", "15/03/1975", "20/05/1990", "05/11/1988", "30/09/1979", "12/07/1985", "22/04/1995", "18/08/1982", "08/12/1970", "25/06/1992"};
	string arrTitulos[] = {"Aprenda C", "Calculo 1", "Problemas y Soluciones", "Tecnología Moderna", "Los Animales"};
	string arrAutores[] = {"Erich Segal", "William P. Blatty", "Richard Bach", "Erica Jong", "Gabriel G.M."};
	string arrEditorial[] = {"Comunity", "Santa Cruz", "La Hogera", "Editorial C", "AyR"};
	string arrEstado[] = {"Bueno", "Aceptable", "Malo"};
	do
	{
		cout << "\nMENU" << endl;
		cout << "1. Llenar datos" << endl;
		cout << "2. Listar" << endl;
		cout << "3. Buscar" << endl;
		cout << "4. Salir" << endl;
		cout << "" << endl;
		
		cout << "Seleccione una opción: ";
		cin >> opcion;
		cout << "--------------------" << endl;
		// Validar entrada del usuario
		while (cin.fail() || opcion < 1 || opcion > 4)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Respuesta inválida, intente otra vez." << endl;
			cout << "Seleccione una opción: ";
			cin >> opcion;
			cout << "--------------------" << endl;
		}
		switch (opcion)
		{
		case 1:
			cout << "" << endl;
			gestionLibros.llenarLibros(LIBROS, arrTitulos, arrAutores, arrEditorial, arrEstado);
			cout << "Datos de Libros llenados" << endl;
			gestionUsuarios.llenarUsuarios(CAD, arrNombres, arrApellidos, arrDirecciones);
			cout << "Datos de Usuarios llenados" << endl;
			cout << "" << endl;
			gestionBibliotecarios.llenarBibliotecarios(CAD, arrNombres, arrApellidos, arrFechas);
			cout << "Datos de Bibliotecarios llenados" << endl;
			cout << "" << endl;
			break;
		case 2:
			int subopcion_listar;
			bool imprimirEnTabla;
			cout << "LISTAR:" << endl;
			cout << "1. Listar libros" << endl;
			cout << "2. Listar usuarios" << endl;
			cout << "3. Listar bibliotecarios" << endl;
			cout << "4. Regresar al menu principal " << endl;
			cout << "Seleccione una opción: ";
			cin >> subopcion_listar;
			cout << "--------------------" << endl;
//			cout << "¿Quiere imprimir en forma de tabla? ( 1: Si, 0:No): ";
	//		cin >> imprimirEnTabla;
			// Validar entrada del submenu de listado
			while (cin.fail() || subopcion_listar < 1 || subopcion_listar > 4)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Respuesta inválida, intente otra vez." << endl;
				cout << "Seleccione una opción: ";
				cin >> subopcion_listar;
				cout << "--------------------" << endl;
			}			
			cout << "¿Quiere imprimir en forma de tabla? ( 1: Si, 0:No): ";
			cin >> imprimirEnTabla;
			while (cin.fail() || imprimirEnTabla <0 || imprimirEnTabla > 1)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Respuesta inválida, intente otra vez." << endl;
				cout << "Seleccione una opción: ";
				cin >> imprimirEnTabla;
				cout << "--------------------" << endl;
			}			
			if (subopcion_listar == 1)
			{				
				gestionLibros.imprimirLibros(imprimirEnTabla);
			}
			else if (subopcion_listar == 2)
			{
				gestionUsuarios.imprimirUsuarios(imprimirEnTabla);
			}
			else if (subopcion_listar == 3)
			{
				gestionBibliotecarios.imprimirBibliotecarios(imprimirEnTabla);
			}
			else if (subopcion_listar == 4)
			{
				break; // Salir del caso 2 y volver al menú principal
			}
			else
			{
				cout << "Opción no válida. Intente de nuevo." << endl;
			}
			break;
		case 3:
			int subopcion_buscar;
			cout << "BUSCAR:" << endl;
			cout << "1. Buscar libros" << endl;
			cout << "2. Buscar Usuario" << endl;
			cout << "3. Buscar bibliotecarios" << endl;
			cout << "0. Regresar al menu principal " << endl;
			cout << "Seleccione una opción: ";
			cin >> subopcion_buscar;
			cout << "--------------------" << endl;
			// Validar entrada del submenu de listado
			while (cin.fail() || subopcion_listar < 0 || subopcion_listar > 3)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Respuesta inválida, intente otra vez." << endl;
				cout << "Seleccione una opción: ";
				cin >> subopcion_listar;
				cout << "--------------------" << endl;
			}
			if (subopcion_buscar == 1)
			{
				string letras_a_buscar;
				cout << "Ingrese las letras para buscar en el titulo o autor de un libro: ";
				cin.ignore(); // Ignorar el buffer del enter anterior
				getline(cin, letras_a_buscar);
				gestionLibros.buscarLibros(letras_a_buscar);
			}
			else if (subopcion_buscar == 2)
			{
				string letras_a_buscar;
				cout << "Ingrese las letras para buscar en el nombre o apellido del usuario: ";
				cin.ignore(); // Ignorar el buffer del enter anterior
				getline(cin, letras_a_buscar);
				gestionUsuarios.buscarUsuarios(letras_a_buscar);
			}
			else if (subopcion_buscar == 3)
			{
				string letras_a_buscar;
				cout << "Ingrese las letras para buscar en el nombre o apellido del bibliotecario: ";
				cin.ignore(); // Ignorar el buffer del enter anterior
				getline(cin, letras_a_buscar);
				gestionBibliotecarios.buscarBibliotecarios(letras_a_buscar);
			}
			else if (subopcion_buscar == 0)
			{
				break; // Salir del caso 3 y volver al menú principal
			}
			else
			{
				cout << "Opción no válida. Intente de nuevo." << endl;
			}
			break;
		case 4:
			return 0;
		default:
			cout << "Opción no válida. Intente de nuevo." << endl;
			break;
		}
	} while (opcion != 4);
	
	return 0;
}
