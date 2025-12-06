#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

//-------------------- Calcular determinante (Gauss) --------------------
double determinante(vector<vector<double>> A) {
    int n = A.size();
    double det = 1.0;

    for (int i = 0; i < n; i++) {
        // Si el pivote es 0, buscar otro en filas siguientes
        if (A[i][i] == 0) {
            for (int k = i + 1; k < n; k++) {
                if (A[k][i] != 0) {
                    swap(A[i], A[k]);
                    det *= -1; // Cambia signo por intercambio
                    break;
                }
            }
        }

        if (A[i][i] == 0) return 0; // No se puede triangular → det = 0

        det *= A[i][i];

        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++)
                A[k][j] -= factor * A[i][j];
        }
    }

    return det;
}

//-------------------- Calcular inversa (Gauss-Jordan) --------------------
bool inversa(vector<vector<double>> A, vector<vector<double>> &Inv) {
    int n = A.size();
    Inv.assign(n, vector<double>(n, 0));

    // Matriz identidad para formar la aumentada
    for (int i = 0; i < n; i++)
        Inv[i][i] = 1;

    for (int i = 0; i < n; i++) {
        double pivote = A[i][i];

        if (pivote == 0) {
            // Buscar otra fila para intercambiar
            bool cambiado = false;
            for (int k = i + 1; k < n; k++) {
                if (A[k][i] != 0) {
                    swap(A[i], A[k]);
                    swap(Inv[i], Inv[k]);
                    pivote = A[i][i];
                    cambiado = true;
                    break;
                }
            }
            if (!cambiado) return false; // No tiene inversa
        }

        // Normalizar fila
        for (int j = 0; j < n; j++) {
            A[i][j] /= pivote;
            Inv[i][j] /= pivote;
        }

        // Hacer ceros en las demás filas
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            double factor = A[k][i];
            for (int j = 0; j < n; j++) {
                A[k][j] -= factor * A[i][j];
                Inv[k][j] -= factor * Inv[i][j];
            }
        }
    }

    return true;
}

//------------------------- Programa principal -------------------------
int main() {
    int n;
    cout << "Ingrese el orden de la matriz (n): ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n));

    cout << "Ingrese la matriz A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    // Determinante
    double det = determinante(A);
    cout << "\nDeterminante: " << det << endl;

    // Inversa
    if (det == 0) {
        cout << "La matriz NO tiene inversa.\n";
    } else {
        vector<vector<double>> Inv;
        if (inversa(A, Inv)) {
            cout << "\nMatriz Inversa:\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    cout << fixed << setprecision(4) << Inv[i][j] << " ";
                cout << endl;
            }
        } else {
            cout << "La matriz NO tiene inversa.\n";
        }
    }

    return 0;
}