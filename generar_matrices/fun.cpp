# include <iostream>
using namespace std;

int*** generar_matrices(int n_matrix,int tam_inicial);

int*** generar_matrices(int n_matrix,int tam_inicial){
    int elemento;

    // Reserva de memoria para la primera dimensión
    int ***arreglo = new int**[n_matrix];
    // Reserva de memoria para las otras dos dimensiones
    for (int i = 0; i < n_matrix; ++i) {
        arreglo[i] = new int*[tam_inicial];
        for (int j = 0; j < tam_inicial; ++j) {
            arreglo[i][j] = new int[tam_inicial];
        }
    }
    //Rellenar arreglo
    for (int i = 0; i < n_matrix; ++i) {
        elemento=1;
        for (int j = 0; j < tam_inicial; ++j) {
            for (int k = 0; k < tam_inicial; ++k) {
                *(*(*(arreglo+i)+j)+k)=elemento;
                if(k==(tam_inicial/2)&&(j==k)){
                    *(*(*(arreglo+i)+j)+k) = 0;
                }
                else{
                    elemento++;
                }
            }
        }
    }


    //Imprimir los elementos del arreglo
    for (int i = 0; i <n_matrix; ++i) {
        for (int j = 0; j < tam_inicial; ++j) {
            for (int k = 0; k < tam_inicial; ++k) {
                cout <<  *(*(*(arreglo+i)+j)+k) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return arreglo;
}
