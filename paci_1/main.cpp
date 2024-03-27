#include <iostream>

using namespace std;

const int N = 3;

// Declaración de funciones
void imprimirMatriz(int matriz[N][N]);
void rotarMatrizCuatroVeces(int* matriz, int dimension);
int* generarMatriz(int dimension);
void imprimirMatriz(int* matriz, int dimension);

int main() {
    int dimension;
    cout << "Ingrese la dimensión de la matriz: ";
    cin >> dimension;

    int* matriz = generarMatriz(dimension);

    cout << "Matriz original:" << endl;
    imprimirMatriz(matriz, dimension);

    rotarMatrizCuatroVeces(matriz, dimension);

    // Liberar memoria después de usarla
    delete [] matriz;

    return 0;
}

// Función para generar la matriz
int* generarMatriz(int dimension) {
    int* matriz = new int[dimension * dimension];
    int valorActual = 1;

    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            // Dejamos el centro de la matriz vacío
            if(i == dimension / 2 && j == dimension / 2) {
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
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            if(matriz[i * dimension + j] == 0) {
                cout << "  ";
            } else {
                cout << matriz[i * dimension + j] << " ";
            }
        }
        cout << endl;
    }
}

// Función para rotar la matriz cuatro veces
void rotarMatrizCuatroVeces(int* matriz, int dimension) {
    int temp;

    for (int k = 0; k < 4; ++k) {
        cout << "Matriz después de rotación " << k + 1 << ":" << endl;

        for (int i = 0; i < dimension / 2; ++i) {
            for (int j = i; j < dimension - i - 1; ++j) {
                temp = matriz[i * dimension + j];
                matriz[i * dimension + j] = matriz[(dimension - 1 - j) * dimension + i];
                matriz[(dimension - 1 - j) * dimension + i] = matriz[(dimension - 1 - i) * dimension + (dimension - 1 - j)];
                matriz[(dimension - 1 - i) * dimension + (dimension - 1 - j)] = matriz[j * dimension + (dimension - 1 - i)];
                matriz[j * dimension + (dimension - 1 - i)] = temp;
            }
        }

        imprimirMatriz(matriz, dimension);
    }
}
