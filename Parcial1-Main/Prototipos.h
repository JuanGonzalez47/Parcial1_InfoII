#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#endif // PROTOTIPOS_H

int*** generar_matrices(int n_matrix,int tam_inicial);
int* dimensio_variables(int n_matrix,int tam_inicial);
void rotations(int ***arrSup, int dim, int NumberMatrix, int state);
void compareFunction(int ***ptrPrincipal, int cont1, int cont2, int *ptrCond, int WichCond, int Pos1, int Pos2, int dimensionMatrixToRotate);
void cambiar_dimension_matriz(int ***arreglo,int *dimen,int numberMatrix,int tam_inicial);
void impresion(int *dimension_final,int *rotacion_final,int n_matrix);
