#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include <vector>
#include <map>
using namespace std;

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
	Persona(int id, const string& nombre, const string& apellido)
		: nIDPersona(to_string(id)), nombre(nombre), apellido(apellido) {
		correo = nombre + "." + apellido + "@gmail.com"; // Generar correo
	}
	
	void mostrarDatos() const {
		cout << "ID:  " << nIDPersona << endl;
		cout << "Nombre: " << nombre << endl;
		cout << "Apellido: " << apellido << endl;
		cout << "Correo: " << correo << endl;
		cout << endl;
	}
	
	// Método virtual puro
	virtual bool buscar(const string& letras) const = 0;
};

// Clase Usuario que hereda de Persona
class Usuario : public Persona {
private:
	string direccion;
	
public:
	// Constructor
	Usuario() {}
	
	// Constructor con parámetros
	Usuario(int id, const string& nombre, const string& apellido, const string& arrDireccion)
		: Persona(id, nombre, apellido), direccion(arrDireccion) {}
	
	string get_direccion() { return direccion; }
	void set_direccion(string d) { direccion = d; }
	
	// Implementación del método buscar
	bool buscar(const string& letras) const override {
		string letrasUpper = letras;
		for (char& c : letrasUpper) {
			c = toupper(c);
		}
		
		string nombreUpper = nombre;
		string apellidoUpper = apellido;
		for (char& c : nombreUpper) {
			c = toupper(c);
		}
		for (char& c : apellidoUpper) {
			c = toupper(c);
		}
		
		return nombreUpper.find(letrasUpper) != string::npos || apellidoUpper.find(letrasUpper) != string::npos;
	}
	
	// Implementación del método mostrarDatos para Usuario
	void mostrarDatos() const  {
		cout << "--USUARIO--" << endl;
		Persona::mostrarDatos();
		cout << "Dirección: " << direccion << endl;
		cout << endl;
	}
};

// Clase Bibliotecario que hereda de Persona
class Bibliotecario : public Persona {
private:
	string fechaNacimiento;
	
public:
	// Constructor
	Bibliotecario() {}
	
	// Constructor con parámetros
	Bibliotecario(int id, const string& nombre, const string& apellido, const string& fechaNacimiento)
		: Persona(id, nombre, apellido), fechaNacimiento(fechaNacimiento) {}
	
	// Implementación del método buscar
	bool buscar(const string& letras) const override {
		string letrasUpper = letras;
		for (char& c : letrasUpper) {
			c = toupper(c);
		}
		
		string nombreUpper = nombre;
		string apellidoUpper = apellido;
		for (char& c : nombreUpper) {
			c = toupper(c);
		}
		for (char& c : apellidoUpper) {
			c = toupper(c);
		}
		
		return nombreUpper.find(letrasUpper) != string::npos || apellidoUpper.find(letrasUpper) != string::npos;
	}
	
	// Implementación del método mostrarDatos para Bibliotecario
	void mostrarDatos(const string& fechaNacimiento) const  {
		cout << "--BIBLIOTECARIO--" << endl;
		Persona::mostrarDatos();
		cout << "Fecha de Nacimiento: " << fechaNacimiento << endl;
		cout << endl;
	}
};

// Clase GestionUsuarios para manejar Usuarios y Bibliotecarios
class GestionUsuarios {
private:
	vector<Persona*> usuarios;
	vector<Persona*> bibliotecarios;
	
public:
	// Constructor
	GestionUsuarios() {}
	
	
	
	// Método para llenar la lista de Usuarios
	void llenarUsuarios(int nCad, string arrNombres[], string arrApellidos[], string arrDirecciones[]) {
		srand(time(NULL));
		for (int i = 0; i < nCad; i++) {
			int id = 201 + i;
			string nombre = arrNombres[rand() % 10];
			string apellido = arrApellidos[rand() % 10];
			string direccion = arrDirecciones[rand() % 10];
			usuarios.push_back(new Usuario(id, nombre, apellido, direccion));
		}
	}
	
	// Método para llenar la lista de Bibliotecarios
	void llenarBibliotecarios(int nCad, string arrNombres[], string arrApellidos[], string arrFechas[]) {
		srand(time(NULL));
		for (int i = 0; i < nCad; i++) {
			int id = 301 + i;
			string nombre = arrNombres[rand() % 10];
			string apellido = arrApellidos[rand() % 10];
			string fechaNacimiento = arrFechas[rand() % 10];
			bibliotecarios.push_back(new Bibliotecario(id, nombre, apellido, fechaNacimiento));
		}
	}
	
	// Método para imprimir la lista de Usuarios
	void imprimirUsuarios() const {
		cout << "\nLISTADO DE USUARIOS:" << endl;
		for (const auto& usuario : usuarios) {
			usuario->mostrarDatos();
		}
	}
	
	// Método para imprimir la lista de Bibliotecarios
	void imprimirBibliotecarios() const {
		cout << "\nLISTADO DE BIBLIOTECARIOS:" << endl;
		for (const auto& bibliotecario : bibliotecarios) {
			bibliotecario->mostrarDatos();
		}
	}
	
	// Método para buscar Usuarios por nombre o apellido
	void buscarUsuarios(const string& letras) const {
		cout << "\nBUSCAR USUARIO:" << endl;
		vector<Persona*> encontrados;
		for (const auto& usuario : usuarios) {
			if (usuario->buscar(letras)) {
				encontrados.push_back(usuario);
			}
		}
		
		cout << "Número de coincidencias encontradas: " << encontrados.size() << endl;
		cout << "Usuarios encontrados:" << endl;
		for (const auto& encontrado : encontrados) {
			encontrado->mostrarDatos();
		}
	}
	
	// Método para buscar Bibliotecarios por nombre o apellido
	void buscarBibliotecarios(const string& letras) const {
		cout << "\nBUSCAR BIBLIOTECARIO:" << endl;
		vector<Persona*> encontrados;
		for (const auto& bibliotecario : bibliotecarios) {
			if (bibliotecario->buscar(letras)) {
				encontrados.push_back(bibliotecario);
			}
		}
		
		cout << "Número de coincidencias encontradas: " << encontrados.size() << endl;
		cout << "Bibliotecarios encontrados:" << endl;
		for (const auto& encontrado : encontrados) {
			encontrado->mostrarDatos();
		}
	}
};

int main() {
	int opcion;
	const int CAD = 5;
	GestionUsuarios gestionUsuarios;
	string arrNombres[] = { "Juan", "Pedro", "Roberto", "Silvia", "Karen", "Rafaela", "Sofia", "Alicia", "Jaime", "Iver" };
	string arrApellidos[] = { "Peralta", "Lazarte", "Cuba", "Torre", "Saucedo", "Ruiz", "Flores", "Herrera", "Fernandez", "Aguilera" };
	string arrDirecciones[] = { "Direccion 1", "Direccion 2", "Direccion 3", "Direccion 4", "Direccion 5", "Direccion 6", "Direccion 7", "Direccion 8", "Direccion 9", "Direccion 10" };
	string arrFechas[] = { "10/01/1980", "15/03/1975", "20/05/1990", "05/11/1988", "30/09/1979", "12/07/1985", "22/04/1995", "18/08/1982", "08/12/1970", "25/06/1992" };
	
	do {
		cout << "\nMENU" << endl;
		cout << "1. Llenar datos" << endl;
		cout << "2. Listar" << endl;
		cout << "3. Buscar" << endl;
		cout << "4. Salir" << endl;
		cout << "" << endl;
		
		cout << "Seleccione una opción: ";
		cin >> opcion;
		cout << "--------------------" << endl;
		switch (opcion) {
		case 1:
			cout << "" << endl;
			gestionUsuarios.llenarUsuarios(CAD, arrNombres, arrApellidos, arrDirecciones);
			cout << "Datos de Usuarios llenados" << endl;
			cout << "" << endl;
			gestionUsuarios.llenarBibliotecarios(CAD, arrNombres, arrApellidos, arrFechas);
			cout << "Datos de Bibliotecarios llenados" << endl;
			cout << "" << endl;
			break;
		case 2:
			int subopcion_listar;
			cout << "LISTAR:" << endl;
			cout << "1. Listar usuarios" << endl;
			cout << "2. Listar bibliotecarios" << endl;
			cout << "0. Regresar al menu principal " << endl;
			cout << "Seleccione una opción: ";
			cin >> subopcion_listar;
			cout << "--------------------" << endl;
			if (subopcion_listar == 1) {
				gestionUsuarios.imprimirUsuarios();
			} else if (subopcion_listar == 2) {
				gestionUsuarios.imprimirBibliotecarios();
			}
			else if (subopcion_listar == 0) {
				break; // Salir del caso 3 y volver al menú principal
			}
			else {
				cout << "Opción no válida. Intente de nuevo." << endl;
			}
			break;
		case 3:
			int subopcion_buscar;
			cout << "BUSCAR:" << endl;
			cout << "1. Buscar usuarios" << endl;
			cout << "2. Buscar bibliotecarios" << endl;
			cout << "0. Regresar al menu principal " << endl;
			cout << "Seleccione una opción: ";
			cin >> subopcion_buscar;
			cout << "--------------------" << endl;
			if (subopcion_buscar == 1) {
				string letras_a_buscar;
				cout << "Ingrese las letras para buscar en el nombre o apellido del usuario: ";
				cin.ignore(); // Ignorar el buffer del enter anterior
				getline(cin, letras_a_buscar);
				gestionUsuarios.buscarUsuarios(letras_a_buscar);
			} else if (subopcion_buscar == 2) {
				string letras_a_buscar;
				cout << "Ingrese las letras para buscar en el nombre o apellido del bibliotecario: ";
				cin.ignore(); // Ignorar el buffer del enter anterior
				getline(cin, letras_a_buscar);
				gestionUsuarios.buscarBibliotecarios(letras_a_buscar);
			} 
			else if (subopcion_buscar == 0) {
				break; // Salir del caso 3 y volver al menú principal
			}else {
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
