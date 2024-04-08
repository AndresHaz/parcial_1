#include <iostream>
#include <vector>
#include <algorithm> // Para la función next_permutation

using namespace std;

// Función para imprimir la matriz
void imprimirMatriz(const vector<int> &matriz, int dimension) {
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            cout << matriz[i * dimension + j] << " ";
        }
        cout << endl; // Nueva línea al final de cada fila
    }
    cout << endl; // Nueva línea adicional entre matrices
}

// Función para generar una matriz cuadrada con dimensiones impares, con centro 0
vector<int> generarMatriz(int dimension) {
    vector<int> matriz(dimension * dimension, 0);
    int valorActual = 1;

    // Calcular el centro de la matriz
    int centro = dimension / 2;

    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            // Dejamos el centro de la matriz vacío
            if (i == centro && j == centro) {
                matriz[i * dimension + j] = 0;
            } else {
                matriz[i * dimension + j] = valorActual++;
            }
        }
    }
    return matriz;
}

bool validarReglaK(const vector<int> &estructuraActual, const vector<int> &estructuraSiguiente, int dimensionActual, int dimensionSiguiente, const vector<int> &reglaK) {
    int fila = reglaK[0];
    int columna = reglaK[1];

    if (fila < 0 || fila >= dimensionActual || columna < 0 || columna >= dimensionActual)
        return false; // La posición especificada en la regla K está fuera de los límites de la estructura actual

    int valorK = reglaK[2];

    bool reglaCumplida = false;
    int rotaciones = 0; // Contador de rotaciones

    vector<int> estructuraSiguienteCopy = estructuraSiguiente; // Hacer una copia de estructuraSiguiente

    while (rotaciones < 4) { // Realizar rotaciones hasta alcanzar un total de 360 grados
        switch (valorK) {
        case 1: // La posición de la matriz actual debe ser mayor que la posición de la matriz siguiente
            reglaCumplida = (estructuraActual[fila * dimensionActual + columna] > estructuraSiguienteCopy[fila * dimensionSiguiente + columna]);
            break;
        case -1: // La posición de la matriz actual debe ser menor que la posición de la matriz siguiente
            reglaCumplida = (estructuraActual[fila * dimensionActual + columna] < estructuraSiguienteCopy[fila * dimensionSiguiente + columna]);
            break;
        case 0: // La posición de la matriz actual debe ser igual a la posición de la matriz siguiente
            reglaCumplida = (estructuraActual[fila * dimensionActual + columna] == estructuraSiguienteCopy[fila * dimensionSiguiente + columna]);
            break;
        default:
            return false; // Valor de regla K no reconocido
        }

        if (reglaCumplida)
            break;

        // Rotar la matriz siguiente 90 grados en sentido antihorario
        vector<int> temp = estructuraSiguienteCopy;
        for (int i = 0; i < dimensionSiguiente; ++i) {
            for (int j = 0; j < dimensionSiguiente; ++j) {
                estructuraSiguienteCopy[i * dimensionSiguiente + j] = temp[j * dimensionSiguiente + (dimensionSiguiente - 1 - i)];
            }
        }

        rotaciones++; // Incrementar el contador de rotaciones
    }

    return reglaCumplida;
}


// Función para buscar una combinación óptima que cumpla con la regla K
bool buscarCombinacionOptima(vector<vector<int>> &matrices, const vector<int> &dimensiones, const vector<int> &reglaK) {
    int numMatrices = matrices.size();

    // Vector para almacenar las permutaciones de las matrices
    vector<int> perm(numMatrices);
    for (int i = 0; i < numMatrices; ++i) {
        perm[i] = i;
    }

    // Inicializar un vector para almacenar las rotaciones actuales de cada matriz
    vector<int> rotacionesActuales(numMatrices, 0);

    // Inicializar un vector para almacenar el mejor estado de rotación de cada matriz
    vector<int> mejorEstadoRotacion(numMatrices, 0);

    bool combinacionEncontrada = false;

    // Bucle principal para probar todas las combinaciones posibles
    do {
        bool reglaKValida = true;

        // Bucle para probar todas las matrices
        for (int i = numMatrices - 1; i >= 0; --i) {
            int idx = perm[i]; // Índice de la matriz actual en la permutación actual
            vector<int> &estructuraActual = matrices[idx]; // Matriz actual
            int dimensionActual = dimensiones[idx]; // Dimensiones de la matriz actual

            // Realizar la cantidad de rotaciones actuales en la matriz actual
            for (int j = 0; j < rotacionesActuales[i]; ++j) {
                vector<int> temp = estructuraActual;
                for (int k = 0; k < dimensionActual; ++k) {
                    for (int l = 0; l < dimensionActual; ++l) {
                        estructuraActual[k * dimensionActual + l] = temp[l * dimensionActual + (dimensionActual - 1 - k)];
                    }
                }
            }

            // Verificar si la regla K se cumple entre la matriz actual y la siguiente
            if (i < numMatrices - 1) {
                vector<int> &estructuraSiguiente = matrices[perm[i + 1]]; // Matriz siguiente
                int dimensionSiguiente = dimensiones[perm[i + 1]]; // Dimensiones de la matriz siguiente
                reglaKValida = validarReglaK(estructuraActual, estructuraSiguiente, dimensionActual, dimensionSiguiente, reglaK);
                if (!reglaKValida) {
                    break; // Si la regla K no se cumple, salir del bucle
                }
            }
        }

        // Si la regla K se cumple para todas las matrices, se ha encontrado una combinación válida
        if (reglaKValida) {
            combinacionEncontrada = true;
            break; // Salir del bucle principal
        }

        // Incrementar el estado de rotación de la última matriz
        rotacionesActuales[numMatrices - 1]++;

        // Actualizar el estado de rotación de cada matriz y retroceder según sea necesario
        for (int i = numMatrices - 1; i > 0; --i) {
            if (rotacionesActuales[i] == 4) {
                rotacionesActuales[i] = 0; // Restablecer la rotación a cero si alcanza 4 rotaciones completas
                rotacionesActuales[i - 1]++; // Incrementar la rotación de la matriz anterior
            }
        }
    } while (next_permutation(perm.begin(), perm.end()) && !combinacionEncontrada);

    // Si se encontró una combinación válida, imprimir las matrices
    if (combinacionEncontrada) {
        cout << "Combinación óptima encontrada:" << endl;
        for (int i = 0; i < numMatrices; ++i) {
            int idx = perm[i];
            cout << "Matriz " << idx + 1 << ":" << endl;
            imprimirMatriz(matrices[idx], dimensiones[idx]);
        }
    } else {
        cout << "No se encontró ninguna combinación que cumpla con la regla K." << endl;
    }

    return combinacionEncontrada;
}

int main() {
    int longitudReglaK;
    cout << "Ingrese la longitud de la regla K: ";
    cin >> longitudReglaK;

    // Crear las matrices con base en la longitud de la regla K
    int numMatrices = longitudReglaK - 1;
    vector<vector<int>> matrices;
    vector<int> dimensiones;

    for (int i = 0; i < numMatrices; ++i) {
        int dimension = 2 * (i + 2) - 1; // Dimensiones impares creciendo de 3 en 3
        vector<int> matriz = generarMatriz(dimension);
        matrices.push_back(matriz);
        dimensiones.push_back(dimension);
    }

    // Vector para almacenar la regla K
    vector<int> reglaK(longitudReglaK);

    // Ingresar la regla K
    cout << "\nIngrese los elementos de la regla K (fila, columna, tipo): ";
    for (int i = 0; i < longitudReglaK; ++i) {
        cin >> reglaK[i];
    }

    // Buscar combinación óptima entre las estructuras
    buscarCombinacionOptima(matrices, dimensiones, reglaK);

    return 0;
}
