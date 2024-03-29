
#include <iostream>

using namespace std;

// Declaración de funciones
void imprimirMatriz(int* matriz, int dimension);
int* generarMatriz(int dimension);

int main() {
    int numMatrices;
    cout << "Ingrese la cantidad de matrices: ";
    cin >> numMatrices;

    for (int i = 0; i < numMatrices; ++i) {
        int dimension;
        cout << "Ingrese la dimensión de la matriz " << i + 1 << " (debe ser un número impar): ";
        cin >> dimension;

        if (dimension % 2 == 0) {
            cout << "El tamaño de la matriz debe ser un número impar." << endl;
            return 1; // Salir del programa con un código de error
        }

        int* matriz = generarMatriz(dimension);

        cout << "Matriz " << i + 1 << ":" << endl;
        imprimirMatriz(matriz, dimension);

        // Liberar memoria después de usarla
        delete[] matriz;
    }

    return 0;
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
                matriz[i * dimension + j] = valorActual;
                valorActual += 1; // Incrementamos en 1
            }
        }
    }

    return matriz;
}

// Función para imprimir la matriz
void imprimirMatriz(int* matriz, int dimension) {
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if (matriz[i * dimension + j] == 0) {
                cout << "  ";
            } else {
                cout << matriz[i * dimension + j] << " ";
            }
        }
        cout << endl;
    }
}
