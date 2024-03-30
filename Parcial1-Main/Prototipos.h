#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#endif // PROTOTIPOS_H

int*** generar_matrices(int n_matrix,int tamInicial);
int*** rotations(int ***arrSup, int dim, int NumberMatrix);
void compareFunction(int ***ptrPrincipal, int *ptrCond, int Pos1, int Pos2, int dimensionMatrixToRotate, int AmountConditions, int *ptrStates, int *ptrorden);
int*** cambiar_dimension_matriz(int ***arreglo,int *dimen,int numberMatrix,int tam_inicial);
