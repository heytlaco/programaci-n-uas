//REVISIÓ DE AVANCE 1 DE 6 PROGRAMACIÓN II
//PRIMERA VERSIÓN DE CAJERO EN C++
//LUNES 3 DE OCTUBRE DE 20222
//CALIFICACIÓN 10
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Variable sesion que vamos a usar de referencia en cualquier movimiento
int sesion;

// todos los vectores que utilizaremos
vector<string> cuentas = {"fulano", "perengano"};
vector<int> nips = {1234, 4321};
vector<int> balances = {1200, 20};
vector<string> movs;

// metodos implementados
void menu();
void logIn();
void deposito();
void transferencia();
void retirar();
void cambiarNip();
void balance();
void movimientos();
void salir();

int main() { logIn(); }

void menu() {
  int option;
  cout << "Que desea realizar" << endl;
  cout << "1. Deposito" << endl;
  cout << "2. Transferencia" << endl;
  cout << "3. Retirar" << endl;
  cout << "4. Cambio de NIP" << endl;
  cout << "5. Balance" << endl;
  cout << "6. Movimientos Realizados" << endl;
  cout << "7. Salir" << endl;

  cin >> option;

  if (option == 1) {
    deposito();
  } else if (option == 2) {
    transferencia();
  } else if (option == 3) {
    retirar();
  } else if (option == 4) {
    cambiarNip();
  } else if (option == 5) {
    balance();
  } else if (option == 6) {
    movimientos();
  }

  else if (option == 7) {
    salir();
  }
}

void logIn() {
  bool inicio_correcto = false;
  string cuenta;
  int nip;
  cout << "Cuenta: ";
  cin >> cuenta;
  cout << "NIP: ";
  cin >> nip;
  for (int i = 0; i < cuentas.size(); i++) { // buscamos entre todas las cuentas
    if (cuenta == cuentas[i]) {
      if (nip == nips[i]) { // si encontramos la cuenta confirmamos que el nip
                            // corresponda
        sesion = i;         // le asignamos valor a sesion
        cout << "Bienvenido" << endl;
        movs.push_back("Acceso a la cuenta"); // enviamos el primer movimiento
                                              // al vector movimientos
        inicio_correcto = true; // confirmamos que se inicio sesion
        menu();                 // inicializamos el menu
      }
    }
  }
  if (inicio_correcto == false) { // en caso de que no se encuentre la cuenta o
                                  // el nip sea incorrecto
    cout << "Datos Incorrectos" << endl;
    logIn();
  }
}
void deposito() {
  int cantidad;
  cout << "Cantidad a Depositar: ";
  cin >> cantidad;
  balances[sesion] += cantidad;

  movs.push_back("deposito de: $" + to_string(cantidad));
  menu();
}

void transferencia() {
  bool cuenta_encontrada = false;
  string cuenta;
  int cantidad;
  cout << "Cuenta: ";
  cin >> cuenta;
  cout << "Cantidad: ";
  cin >> cantidad;
  if (balances[sesion] >=
      cantidad) { // comprobamos que el saldo de la cuenta es suficiente
    for (int i = 0; i < cuentas.size();
         i++) { // buscamos la cuenta dentro del vector cuentas
      if (cuenta == cuentas[i]) {
        balances[sesion] -= cantidad;
        balances[i] += cantidad;
        cuenta_encontrada = true; // verificamos que la encontro
        movs.push_back("transferencia de: $" + to_string(cantidad) + " a " +
                       cuenta);
        menu();
      }
    }
    if (cuenta_encontrada == false) {
      cout << "cuenta no encontrada" << endl;
      transferencia();
    }
  } else {
    cout << "saldo insuficiente" << endl;
    transferencia();
  }
}

void retirar() {
  int cantidad;
  cout << "Cantidad a retirar:";
  cin >> cantidad;
  if (balances[sesion] >=
      cantidad) { // comprobamos que el saldo de la cuenta es suficiente
    balances[sesion] -= cantidad;
    movs.push_back("retiro de: $" + to_string(cantidad));
    menu();
  } else {
    cout << "saldo insuficiente" << endl;
    retirar();
  }
}

void cambiarNip() {
  int nuevoNip;
  cout << "Introduzca nuevo NIP: ";
  cin >> nuevoNip;
  if (nuevoNip > 1000 && nuevoNip < 9999) {
    nips[sesion] = nuevoNip;
    movs.push_back("cambio de nip a: " + to_string(nuevoNip));
    menu();
  } else {
    cout << "NIP nuevo invalido" << endl;
    cambiarNip();
  }
}

void balance() {
  cout << cuentas[sesion] << endl;
  cout << balances[sesion] << endl;
  movs.push_back("balance: $" + to_string(balances[sesion]));
  menu();
}

void movimientos() {
  for (int i = 0; i < movs.size(); i++) {
    cout << movs[i] << endl;
  }
  menu();
}

void salir() {
  sesion = -1;
  movs.clear();
  logIn();
}
