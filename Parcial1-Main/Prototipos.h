#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#endif // PROTOTIPOS_H

int*** generar_matrices(int n_matrix,int tamInicial);
void rotations(int ***arrSup, int dim, int NumberMatrix);
void compareFunction(int ***ptrPrincipal, int *ptrCond, int Pos1, int Pos2, int dimensionMatrixToRotate, int AmountConditions, int *ptrStates, int *ptrorden);
void cambiar_dimension_matriz(int ***arreglo,int *dimen,int numberMatrix,int tam_inicial);
void imprimir_cerradura(int *dimension_final,int *rotacion_final,int n_matrix);
void imprimir_clave(int *ptrToKey,int m,int n,int z);
void liberar_memoria(int ***ptrPrincipal,int *rotacion_final,int *dimension_final,int *ptrToKey,int AmountConditions);
