#include <stdio.h>

int main(void){
	printf("\n\nTamaño de un entero (int) en este sistema medido en bytes: %lu\n\n", sizeof(int));	
	int a_int_caso_1=2147483647;
	int b_int_caso_1=1;
	int c_int_caso_1_suma= a_int_caso_1 + b_int_caso_1;
	printf("No obtenemos el resultado esperado: %d + %d= %d\n\n", a_int_caso_1,b_int_caso_1,c_int_caso_1_suma);	

	printf("Pero si utilizamos números dobles...\n\n"); 
	printf("Tamaño de un número de punto flotante de doble precisión (double) en este sistema medido en bytes: %lu\n\n", sizeof(double));
	double a_float_caso_1=2147483647;
	double b_float_caso_1=1;
	double c_float_caso_1_suma= a_float_caso_1 + b_float_caso_1;
	printf("Si obtenemos el resultado esperado: %lf + %lf= %lf\n\n", a_float_caso_1,b_float_caso_1,c_float_caso_1_suma);	
	return 0;	
}
	
