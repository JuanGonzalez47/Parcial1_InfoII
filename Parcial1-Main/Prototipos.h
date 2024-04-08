#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#endif // PROTOTIPOS_H

int*** generar_matrices(int n_matrix,int tamInicial);
bool compareFunction(int ***ptrPrincipal, int *ptrCond, int Pos1, int Pos2, int dimensionMatrixToRotate, int AmountConditions, int *ptrStates, int *ptrorden,bool bajar_dimension,int InitialSizeIteration1);
void rotations(int ***arrSup, int dim, int NumberMatrix);
void cambiar_dimension_matriz(int ***arreglo,int dimen,int numberMatrix,int tam_inicial);
void imprimir_cerradura(int *dimension_final,int *rotacion_final,int n_matrix);
void imprimir_clave(int *ptrToKey,int m,int n,int z);
void liberar_memoria(int ***ptrPrincipal,int *rotacion_final,int *dimension_final,int *ptrToKey,int AmountConditions,bool confir);
void imprimir_matrices(int ***ptrPrincipal, int n_matrix, int *dimension_final);
void principal_menu(int *ptrToKey,int * ptrStates,int * ptrorden,int *** arreglo,int z,int m, int n, int cond, int dimMatrix, bool end);
bool validar_regla(int ***ptrPrincipal, int *ptrCond, int Pos1, int Pos2,int AmountConditions, int *ptrStates, int *ptrorden);
int*** matrices_validar_regla(int n_matrix,int *dimen);
