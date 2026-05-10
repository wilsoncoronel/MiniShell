// Mini_shell_procesos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
/*
6. (Experto) Diseña e implementa en C++ un 'mini-shell' que:    
a) Muestre un prompt 'miniSO> '  
b) Acepte los comandos: 'ps' (lista procesos), 'kill PID', 'new NOMBRE MEM', 'mem' (estadísticas), 'exit' 
c) Mantenga una lista de procesos en memoria  
d) Rechace crear procesos si no hay memoria suficiente (máx 8192 KB)  
e) Muestre un historial de los últimos 5 comandos ejecutados
*/
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
struct Proceso {
    int pid;
    string nombre;
    int memoria;
    double cpu_pct;
    string estado;
};


class MiniShell {
private:
    vector<Proceso> tabla_procesos;
    int memoria_total_kb;
    int siguiente_pid;
    vector<string> opciones = { "PS", "Kill PID", "New Process", "MEM", "Exit" };

public:
    MiniShell(int ram_kb) {
        memoria_total_kb = ram_kb;
        siguiente_pid = 1000;
        cout << "[MiniSO] Sistema inicializado con " << ram_kb << " KB de RAM" << endl;
        cout << "<-------------------- Minishell ---------------------------->" << endl;
    }

    int crearProceso(string nombre, int memoria_kb, double cpu_pct) {
        int memoria_usada = memoriaUsada();

        if (memoria_usada + memoria_kb > memoria_total_kb) {
            cout << "[Error] No hay suficiente memoria libre!"
                << (memoria_total_kb - memoria_kb) << "KB" << endl;
            return -1;
        }
        Proceso nuevo_proceso = { siguiente_pid++, nombre, memoria_kb, cpu_pct,"Ejecutando" };
        tabla_procesos.push_back(nuevo_proceso);
        cout << "[MiniShell] Proceso creado pid: " << nuevo_proceso.pid
            << "\nNombre: " << nombre << endl;
        return nuevo_proceso.pid;
    }

    void listarProcesos() {
        for (auto& proce : tabla_procesos) {
            cout << "PID: " << proce.pid << ", " << proce.nombre << ", " << proce.memoria << ", " << proce.estado << endl;
        }
    }

    int eliminarProcesos(int pid) {
        for (int i = 0; i < tabla_procesos.size(); i++) {
            if (tabla_procesos[i].pid == pid) {
                cout << "Proceso eliminado PID = " << tabla_procesos[i].pid << endl;
                tabla_procesos.erase(tabla_procesos.begin() + i);
                return 1;
            }
        }
        return 0;
    }

    void listarOpciones() {
        cout << "Opciones Shell: " << endl;
        for (size_t i = 0; i < opciones.size(); i++) {
            cout << (i + 1) << " " << opciones[i] << endl;
        }
    }

    int memoriaUsada() {
        int total = 0;
        for (auto& proc : tabla_procesos) {
            total += proc.memoria;
        }
        return total;
    }

    void MostrarEstadoSO() {
        cout << "\n====================================================================" << endl;
        cout << "                          PROCESOS EN MEMORIA" << endl;
        cout << "\n====================================================================" << endl;
        cout << left << setw(6) << "PID"
            << left << setw(15) << "NOMBRE"
            << right << setw(10) << "MEM(KB)"
            << right << setw(8) << "CPU%"
            << left << setw(8) << " ESTADO" << endl;
        cout << "----------------------------------------------------------------------" << endl;

        for (auto& proc : tabla_procesos) {
            cout << left << setw(6) << proc.pid
                << left << setw(15) << proc.nombre
                << right << setw(10) << proc.memoria
                << right << setw(8) << fixed << setprecision(1) << proc.cpu_pct << "%"
                << left << setw(8) << (" " + proc.estado) << endl;
        }

        int usada = memoriaUsada();
        int libre = memoria_total_kb - usada;
        double pct_uso = (double)usada / memoria_total_kb * 100.0;
        cout << "Memoria Total: " << memoria_total_kb << " KB" << endl;
        cout << "Memoria Usada: " << usada << "KB ("
            << fixed << setprecision(1) << pct_uso << "%)" << endl;
        cout << "Memoria libre: " << libre << " KB" << endl;
        cout << "Procesos activos: " << tabla_procesos.size() << endl;
        cout << "====================================================================\n" << endl;

    }

    void ingresoOpciones() {
        cout << "\n====================================================================" << endl;
        cout << "                          MINISHELL OPCIONES:" << endl;
        cout << "\n====================================================================" << endl;
        listarOpciones();
        string opc;
        cout << "Ingrese una opcion para continuar: " << endl;
        cin >> opc;
        while (opc.size() > 0) {
            if (opc == "PS") {
                    listarProcesos();
                    break;
                }
                else if (opc == "Kill") {
                    int pid = 0;
                    cout << "Ingrese el pid a eliminar: " << endl;
                    cin >> pid;
                    if (pid > 0) {
                        eliminarProcesos(pid);
                    }
                    else {
                        cout << "No permitido" << endl;
                        listarOpciones();
                        cout << "Ingrese una opcion para continuar: " << endl;
                        cin >> opc;
                    }
                    break;
                }
                else if (opc == "New") {
                    string nombre;
                    int memoria_kb;
                    cout << "Ingrese el nombre del nuevo proceso: " << endl;
                    cin >> nombre;
                    cout << "Ingrese el tamano en memoria a usar: " << endl;
                    cin >> memoria_kb;
                    crearProceso(nombre, memoria_kb, 0.0);
                    break;
                }
                else if (opc == "MEM") {
                    MostrarEstadoSO();
                    break;
                }
                else if (opc == "Exit") {
                    cout << "Terminando la shell......" << endl;
                    opc = "";
                }
                else {
                    cout << "Opcion invalida" << endl;
                    listarOpciones();
                    cout << "Ingrese una opcion para continuar: " << endl;
                    cin >> opc;
                }
        }
    }
};

int main()
{
    cout << "============================================================" << endl;
    cout << "   TERMINAL DE PROCESOS DEL SISTEMA OPERATIVO   " << endl;
    cout << "============================================================\n" << endl;
    MiniShell shell(4096);
    shell.ingresoOpciones();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
