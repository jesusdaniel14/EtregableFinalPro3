#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include <vector>
#include <map>
using namespace std;

class Usuario {
public:
	int nIDUsuario;
	string sNombre;
	string sApellido;
	string sContrasena;
	int nTelf;
	
	Usuario() {}
	
	Usuario(int id, const string& nombre, const string& apellido, int telf)
		: nIDUsuario(id), sNombre(nombre), sApellido(apellido), nTelf(telf) {
		sContrasena = sNombre + sApellido; // Generar contraseña
	}
	
	void imprimir() const {
		cout << "ID Usuario:  " << nIDUsuario << endl;
		cout << "Nombre: " << sNombre << endl;
		cout << "Apellido: " << sApellido << endl;
		cout << "Contraseña: " << sContrasena << endl;
		cout << "Telefono: " << nTelf << endl;
		cout << endl;
	}
	
	bool buscar(const string& letras) const {
		string letrasUpper = letras;
		for (char& c : letrasUpper) {
			c = toupper(c);
		}
		
		string nombreUsuarioUpper = sNombre;
		string apellidoUsuarioUpper = sApellido;
		for (char& c : nombreUsuarioUpper) {
			c = toupper(c);
		}
		for (char& c : apellidoUsuarioUpper) {
			c = toupper(c);
		}
		
		return nombreUsuarioUpper.find(letrasUpper) != string::npos || apellidoUsuarioUpper.find(letrasUpper) != string::npos;
	}
};

class GestionUsuarios {
private:
	vector<Usuario> usuarios;
	
public:
	GestionUsuarios() {}
	
	void llenar(int nCad, string arrNombres[], string arrApellidos[]) {
		srand(time(NULL));
		usuarios.clear();
		for (int i = 0; i < nCad; i++) {
			int id = 201 + i;
			string nombre = arrNombres[rand() % 10];
			string apellido = arrApellidos[rand() % 10];
			int telf = 70000000 + rand() % 79999999;
			usuarios.push_back(Usuario(id, nombre, apellido, telf));
		}
	}
	
	void imprimir() const {
		for (const Usuario& usuario : usuarios) {
			usuario.imprimir();
		}
	}
	
	void buscar(const string& letras) const {
		vector<Usuario> usuariosEncontrados;
		for (const Usuario& usuario : usuarios) {
			if (usuario.buscar(letras)) {
				usuariosEncontrados.push_back(usuario);
			}
		}
		
		cout << "Número de coincidencias encontradas: " << usuariosEncontrados.size() << endl;
		cout << "Nombres de usuarios encontrados:" << endl;
		for (const Usuario& usuario : usuariosEncontrados) {
			usuario.imprimir();
		}
	}
};

int main() {
	int opcion;
	const int CAD = 5;
	GestionUsuarios gestionUsuarios;
	string arrNombres[] = { "Juan", "Pedro", "Roberto", "Silvia", "Karen", "Rafaela", "Sofia", "Alicia", "Jaime", "Iver" };
	string arrApellidos[] = { "Peralta", "Lazarte", "Cuba", "Torre", "Saucedo", "Ruiz", "Flores", "Herrera", "Fernandez", "Aguilera" };
	
	do {
		cout << "\nMENU" << endl;
		cout << "1. Llenar datos" << endl;
		cout << "2. Listado" << endl;
		cout << "3. Busqueda" << endl;
		cout << "4. Salir" << endl;
		cout << "" << endl;
		
		cout << "Seleccione una opción: ";
		cin >> opcion;
		cout << "--------------------" << endl;
		switch (opcion) {
		case 1:
			gestionUsuarios.llenar(CAD, arrNombres, arrApellidos);
			cout << "Datos llenados" << endl;
			break;
		case 2:
			cout << "\nLISTADO DE USUARIOS:" << endl;
			gestionUsuarios.imprimir();
			break;
		case 3:
			cout << "\nBUSCAR USUARIO:" << endl;
			{
				string letras_a_buscar;
				cout << "Ingrese las letras para buscar en el nombre o apellido del usuario: ";
				cin.ignore(); // Ignorar el buffer del enter anterior
				getline(cin, letras_a_buscar);
				gestionUsuarios.buscar(letras_a_buscar);
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
