#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

// Estructura para manejar tiempo (fecha de publicación)
struct S_Tiempo {
	int nDia;
	int nMes;
	int nAnio;
};

// Clase base abstracta Persona
class Persona {
protected:
	string nIDPersona;
	string nombre;
	string apellido;
	string correo;
	
public:
	// Constructor
	Persona() {}
	
	// Constructor con parámetros
	Persona(int id, const string &nombre, const string &apellido)
		: nIDPersona(to_string(id)), nombre(nombre), apellido(apellido)
	{
		correo = nombre + "." + apellido + "@gmail.com"; // Generar correo
	}
	
	void mostrarDatos() const
	{
		cout << "ID:  " << nIDPersona << endl;
		cout << "Nombre: " << nombre << endl;
		cout << "Apellido: " << apellido << endl;
		cout << "Correo: " << correo << endl;
		cout << endl;
	}
	
	// Método virtual puro
	virtual bool buscar(const string &letras) const = 0;
};

// Clase Usuario que hereda de Persona
class Usuario : public Persona
{
private:
	string direccion;
	
public:
	// Constructor
	Usuario() {}
	
	// Constructor con parámetros
	Usuario(int id, const string &nombre, const string &apellido, const string &arrDireccion)
		: Persona(id, nombre, apellido), direccion(arrDireccion) {}
	
	string get_direccion() { return direccion; }
	void set_direccion(string d) { direccion = d; }
	
	// Implementación del método buscar
	bool buscar(const string &letras) const override
	{
		string letrasUpper = letras;
		for (char &c : letrasUpper)
		{
			c = toupper(c);
		}
		
		string nombreUpper = nombre;
		string apellidoUpper = apellido;
		for (char &c : nombreUpper)
		{
			c = toupper(c);
		}
		for (char &c : apellidoUpper)
		{
			c = toupper(c);
		}
		
		return nombreUpper.find(letrasUpper) != string::npos || apellidoUpper.find(letrasUpper) != string::npos;
	}
	
	// Implementación del método mostrarDatos para Usuario
	void mostrarDatos() const
	{
		cout << "--USUARIO--" << endl;
		Persona::mostrarDatos();
		cout << "Dirección: " << direccion << endl;
		cout << endl;
	}
};

// Clase Bibliotecario que hereda de Persona
class Bibliotecario : public Persona
{
private:
	string fechaNacimiento;
	
public:
	// Constructor
	Bibliotecario() {}
	
	// Constructor con parámetros
	Bibliotecario(int id, const string &nombre, const string &apellido, const string &fechaNacimiento)
		: Persona(id, nombre, apellido), fechaNacimiento(fechaNacimiento) {}
	
	// Implementación del método buscar
	bool buscar(const string &letras) const override
	{
		string letrasUpper = letras;
		for (char &c : letrasUpper)
		{
			c = toupper(c);
		}
		
		string nombreUpper = nombre;
		string apellidoUpper = apellido;
		for (char &c : nombreUpper)
		{
			c = toupper(c);
		}
		for (char &c : apellidoUpper)
		{
			c = toupper(c);
		}
		
		return nombreUpper.find(letrasUpper) != string::npos || apellidoUpper.find(letrasUpper) != string::npos;
	}
	
	// Implementación del método mostrarDatos para Bibliotecario
	void mostrarDatos() const
	{
		cout << "--BIBLIOTECARIO--" << endl;
		Persona::mostrarDatos();
		cout << "Fecha de Nacimiento: " << fechaNacimiento << endl;
		cout << endl;
	}
};

// Clase Libro
class Libro
{
private:
	int nSNBI;
	string sTituloLibro;
	string sAutorLibro;
	S_Tiempo tFechaPublicacion;
	string sEditorial;
	int nNumEstante;
	string arrEstado;
	
public:
	// Constructor
	Libro() {}
	
	// Constructor con parámetros
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
	// Implementación del método buscar
	bool buscar(const string &letras) const 
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
		
		return tituloUpper.find(letrasUpper) != string::npos || autorUpper.find(letrasUpper) != string::npos;
	}
};

// Clase GestionUsuarios para manejar Usuarios, Bibliotecarios y Libros
class GestionUsuarios
{
private:
	vector<Persona *> usuarios;
	vector<Persona *> bibliotecarios;
	vector<Libro> libros;
	
public:
	// Constructor
	GestionUsuarios() {}
	
	// Método para llenar la lista de Usuarios
	void llenarUsuarios(int nCad, string arrNombres[], string arrApellidos[], string arrDirecciones[])
	{
		srand(time(NULL));
		for (int i = 0; i < nCad; i++)
		{
			int id = 201 + i;
			string nombre = arrNombres[rand() % 10];
			string apellido = arrApellidos[rand() % 10];
			string direccion = arrDirecciones[rand() % 10];
			usuarios.push_back(new Usuario(id, nombre, apellido, direccion));
		}
	}
	
	// Método para llenar la lista de Bibliotecarios
	void llenarBibliotecarios(int nCad, string arrNombres[], string arrApellidos[], string arrFechas[])
	{
		srand(time(NULL));
		for (int i = 0; i < nCad; i++)
		{
			int id = 301 + i;
			string nombre = arrNombres[rand() % 10];
			string apellido = arrApellidos[rand() % 10];
			string fechaNacimiento = arrFechas[rand() % 10];
			bibliotecarios.push_back(new Bibliotecario(id, nombre, apellido, fechaNacimiento));
		}
	}
	
	// Método para llenar la lista de Libros
	void llenarLibros(int nLibros, string arrTitulos[], string arrAutores[],string arrEditorial[],string arrEstado[])
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
			libros.push_back(Libro(snbi, titulo, autor, fecha, editorial, estante, estado));
		}
	}
	
	// Método para imprimir la lista de Usuarios
	void imprimirUsuarios() const
	{
		cout << "\nLISTADO DE USUARIOS:" << endl;
		for (const auto &usuario : usuarios)
		{
			usuario->mostrarDatos();
		}
	}
	
	// Método para imprimir la lista de Bibliotecarios
	void imprimirBibliotecarios() const
	{
		cout << "\nLISTADO DE BIBLIOTECARIOS:" << endl;
		for (const auto &bibliotecario : bibliotecarios)
		{
			bibliotecario->mostrarDatos();
		}
	}
	
	// Método para imprimir la lista de Libros
	void imprimirLibros() const
	{
		cout << "\nLISTADO DE LIBROS:" << endl;
		for (const auto &libro : libros)
		{
			libro.mostrarDatos();
		}
	}
	
	// Método para buscar Usuarios por nombre o apellido
	void buscarUsuarios(const string &letras) const
	{
		cout << "\nBUSCAR USUARIO:" << endl;
		vector<Persona *> encontrados;
		for (const auto &usuario : usuarios)
		{
			if (usuario->buscar(letras))
			{
				encontrados.push_back(usuario);
			}
		}
		
		cout << "Número de coincidencias encontradas: " << encontrados.size() << endl;
		cout << "Usuarios encontrados:" << endl;
		for (const auto &encontrado : encontrados)
		{
			encontrado->mostrarDatos();
		}
	}
	
	// Método para buscar Bibliotecarios por nombre o apellido
	void buscarBibliotecarios(const string &letras) const
	{
		cout << "\nBUSCAR BIBLIOTECARIO:" << endl;
		vector<Persona *> encontrados;
		for (const auto &bibliotecario : bibliotecarios)
		{
			if (bibliotecario->buscar(letras))
			{
				encontrados.push_back(bibliotecario);
			}
		}
		
		cout << "Número de coincidencias encontradas: " << encontrados.size() << endl;
		cout << "Bibliotecarios encontrados:" << endl;
		for (const auto &encontrado : encontrados)
		{
			encontrado->mostrarDatos();
		}
	}
	// Método para buscar Libros por título, autor, etc.
	void buscarLibros(const string &letras) const
	{
		cout << "\nBUSCAR LIBROS:" << endl;
		vector<Libro> encontrados;
		for (const auto &libro : libros)
		{
			if (libro.buscar(letras))
			{
				encontrados.push_back(libro);
			}
		}
		
		cout << "Número de coincidencias encontradas: " << encontrados.size() << endl;
		cout << "Libros encontrados:" << endl;
		for (const auto &encontrado : encontrados)
		{
			encontrado.mostrarDatos();
		}
	}
};

int main()
{
	int opcion;
	const int CAD = 5;
	const int LIBROS = 10;
	GestionUsuarios gestionUsuarios;
	string arrNombres[] = { "Juan", "Pedro", "Roberto", "Silvia", "Karen", "Rafaela", "Sofia", "Alicia", "Jaime", "Iver" };
	string arrApellidos[] = { "Peralta", "Lazarte", "Cuba", "Torre", "Saucedo", "Ruiz", "Flores", "Herrera", "Fernandez", "Aguilera" };
	string arrDirecciones[] = { "Direccion 1", "Direccion 2", "Direccion 3", "Direccion 4", "Direccion 5", "Direccion 6", "Direccion 7", "Direccion 8", "Direccion 9", "Direccion 10" };
	string arrFechas[] = { "10/01/1980", "15/03/1975", "20/05/1990", "05/11/1988", "30/09/1979", "12/07/1985", "22/04/1995", "18/08/1982", "08/12/1970", "25/06/1992" };
	string arrTitulos[] = { "Aprenda C", "Calculo 1", "Problemas y Soluciones", "Tecnología Moderna", "Los Animales" };
	string arrAutores[] = { "Erich Segal", "William P. Blatty", "Richard Bach", "Erica Jong", "Gabriel Garciía Márquez" };
	string arrEditorial[] = { "Comunity", "Santa Cruz", "La Hogera" , "Editorial C", "AyR" };
	string arrEstado[] = { "Bueno", "Aceptable", "Malo"};
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
		switch (opcion)
		{
		case 1:
			cout << "" << endl;
			gestionUsuarios.llenarUsuarios(CAD, arrNombres, arrApellidos, arrDirecciones);
			cout << "Datos de Usuarios llenados" << endl;
			cout << "" << endl;
			gestionUsuarios.llenarBibliotecarios(CAD, arrNombres, arrApellidos, arrFechas);
			cout << "Datos de Bibliotecarios llenados" << endl;
			gestionUsuarios.llenarLibros(LIBROS,arrTitulos,arrAutores,arrEditorial,arrEstado);
			cout << "Datos de Libros llenados" << endl;
			cout << "" << endl;
			break;
		case 2:
			int subopcion_listar;
			cout << "LISTAR:" << endl;
			cout << "1. Listar usuarios" << endl;
			cout << "2. Listar bibliotecarios" << endl;
			cout << "3. Listar libros" << endl;
			cout << "0. Regresar al menu principal " << endl;
			cout << "Seleccione una opción: ";
			cin >> subopcion_listar;
			cout << "--------------------" << endl;
			if (subopcion_listar == 1)
			{
				gestionUsuarios.imprimirUsuarios();
			}
			else if (subopcion_listar == 2)
			{
				gestionUsuarios.imprimirBibliotecarios();
			}
			else if (subopcion_listar == 3)
			{
				gestionUsuarios.imprimirLibros();
			}
			else if (subopcion_listar == 0)
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
			cout << "1. Buscar usuarios" << endl;
			cout << "2. Buscar bibliotecarios" << endl;
			cout << "3. Buscar libros" << endl;
			cout << "0. Regresar al menu principal " << endl;
			cout << "Seleccione una opción: ";
			cin >> subopcion_buscar;
			cout << "--------------------" << endl;
			if (subopcion_buscar == 1)
			{
				string letras_a_buscar;
				cout << "Ingrese las letras para buscar en el nombre o apellido del usuario: ";
				cin.ignore(); // Ignorar el buffer del enter anterior
				getline(cin, letras_a_buscar);
				gestionUsuarios.buscarUsuarios(letras_a_buscar);
			}
			else if (subopcion_buscar == 2)
			{
				string letras_a_buscar;
				cout << "Ingrese las letras para buscar en el nombre o apellido del bibliotecario: ";
				cin.ignore(); // Ignorar el buffer del enter anterior
				getline(cin, letras_a_buscar);
				gestionUsuarios.buscarBibliotecarios(letras_a_buscar);
			}
			else if (subopcion_buscar == 3)
			{
				string letras_a_buscar;
				cout << "Ingrese las letras para buscar en el titulo o autor de un libro: ";
				cin.ignore(); // Ignorar el buffer del enter anterior
				getline(cin, letras_a_buscar);
				gestionUsuarios.buscarLibros(letras_a_buscar);
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
	} while (opcion != 0);
	
	return 0;
}
