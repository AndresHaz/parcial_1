#include <iostream>
#include <vector>

using namespace std;

// Función para imprimir la matriz
void imprimirMatriz(int* matriz, int dimension) {
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            cout << matriz[i * dimension + j] << " ";
        }
        cout << endl; // Nueva línea al final de cada fila
    }
}



// Función para generar la matriz
int* generarMatriz(int dimension) {
    int* matriz = new int[dimension * dimension];
    int valorActual = 1;

    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            // Dejamos el centro de la matriz vacío
            if (i == dimension / 2 && j == dimension / 2) {
                matriz[i * dimension + j] = 0;
            } else {
                matriz[i * dimension + j] = valorActual++;
            }
        }
    }
    return matriz;
}

// Función para rotar una matriz cuadrada de tamaño 'dimension'
void rotarMatriz(int* matriz, int dimension) {
    int* temp = new int[dimension * dimension];

    // Copiar la matriz original en una temporal
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            temp[i * dimension + j] = matriz[i * dimension + j];
        }
    }

    // Rotar la matriz
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            matriz[j * dimension + (dimension - 1 - i)] = temp[i * dimension + j];
        }
    }

    delete[] temp;
}

// Función para validar la regla K
bool validarReglaK(const vector<int*>& estructuras, const vector<int>& dimensiones, const vector<int>& reglaK) {
    int numEstructuras = estructuras.size();
    int numReglas = reglaK.size();
    if (numEstructuras <= 1 || numReglas != numEstructuras - 1)
        return false; // No se pueden validar reglas K con menos de 2 estructuras o si el número de reglas no coincide

    for (int i = 0; i < numReglas; ++i) {
        int* estructuraActual = estructuras[i];
        int* estructuraSiguiente = estructuras[i + 1];
        int dimensionActual = dimensiones[i];
        int dimensionSiguiente = dimensiones[i + 1];

        int fila = reglaK[i];
        int columna = reglaK[i + numReglas];
        int valorA = reglaK[i + numReglas * 2];
        int valorB = reglaK[i + numReglas * 3];

        if (fila < 0 || fila >= dimensionActual || columna < 0 || columna >= dimensionActual)
            return false; // La posición especificada en la regla K está fuera de los límites de la estructura actual

        if (valorA < 0 || valorA >= dimensionSiguiente || valorB < 0 || valorB >= dimensionSiguiente)
            return false; // Las posiciones especificadas en la regla K están fuera de los límites de la estructura siguiente

        int valorC = estructuraSiguiente[valorA * dimensionSiguiente + valorB];
        int valorD = estructuraSiguiente[dimensionSiguiente / 2 * dimensionSiguiente + dimensionSiguiente / 2]; // Valor en el centro de la estructura siguiente

        if (!(estructuraActual[fila * dimensionActual + columna] > valorA && valorA < valorC && valorC > valorD))
            return false; // La regla K no se cumple
    }

    return true; // Todas las reglas K se cumplieron correctamente
}

int main() {
    int numMatrices;
    cout << "Ingrese la cantidad de matrices: ";
    cin >> numMatrices;

    // Vector para almacenar los punteros a las matrices
    vector<int*> listaMatrices;
    vector<int> dimensiones; // Para almacenar las dimensiones de las matrices

    for (int i = 0; i < numMatrices; ++i) {
        int dimension;
        cout << "Ingrese la dimensión de la matriz " << i + 1 << " (debe ser un número impar): ";
        cin >> dimension;

        if (dimension % 2 == 0) {
            cout << "El tamaño de la matriz debe ser un número impar." << endl;
            // Liberar la memoria de las matrices creadas antes de salir
            for (int* matriz : listaMatrices) {
                delete[] matriz;
            }
            return 1; // Salir del programa con un código de error
        }

        int* matriz = generarMatriz(dimension);
        listaMatrices.push_back(matriz); // Guardar el puntero de la matriz
        dimensiones.push_back(dimension); // Guardar la dimensión de la matriz

        cout << "Matriz " << i + 1 << ":" << endl;
        imprimirMatriz(matriz, dimension);
    }

    // Validar la regla K
    vector<int> reglaK;
    cout << "Ingrese la regla K (fila y columna de cada estructura seguidas de los valores A, B, C, D): ";
    int valor;
    for (int i = 0; i < numMatrices - 1; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> valor;
            reglaK.push_back(valor);
        }
    }

    bool reglaValida = validarReglaK(listaMatrices, dimensiones, reglaK);
    if (reglaValida) {
        cout << "La regla K se cumple." << endl;
    } else {
        cout << "La regla K no se cumple." << endl;
    }

    // Rotar las estructuras para abrir la cerradura
    cout << "\nAbriendo la cerradura..." << endl;
    for (int i = 0; i < numMatrices; ++i) {
        cout << "Estructura " << i + 1 << ":" << endl;
        rotarMatriz(listaMatrices[i], dimensiones[i]);
        imprimirMatriz(listaMatrices[i], dimensiones[i]);
    }

    // No olvides liberar la memoria después de usar las matrices
    for (int* matriz : listaMatrices) {
        delete[] matriz;
    }

    return 0;
}
