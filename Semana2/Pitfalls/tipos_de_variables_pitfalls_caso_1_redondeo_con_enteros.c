#include <stdio.h>

int main(void){
	printf("\n\nCaso 1 Errores de redondeo al trabajar con enteros (int).\n\n");
	int a_int_caso_1=10;
	int b_int_caso_1=15;
	int c_int_caso_1_multiplicacion= a_int_caso_1 * b_int_caso_1;
	int c_int_caso_1_suma= a_int_caso_1 + b_int_caso_1;
	int c_int_caso_1_resta= a_int_caso_1 - b_int_caso_1;

	printf("Si obtenemos el resultado esperado: %d * %d= %d\n", a_int_caso_1,b_int_caso_1,c_int_caso_1_multiplicacion);
	printf("Si obtenemos el resultado esperado: %d + %d= %d\n", a_int_caso_1,b_int_caso_1,c_int_caso_1_suma);	
	printf("Si obtenemos el resultado esperado: %d - %d= %d\n", a_int_caso_1,b_int_caso_1,c_int_caso_1_resta);

	int c_int_caso_1_division= a_int_caso_1 / b_int_caso_1;
	printf("\n¡Cuidado!\n\n");
	printf("No obtenemos el resultado esperado: %d / %d= %d\n\n", a_int_caso_1,b_int_caso_1,c_int_caso_1_division);
	printf("Pero si utilizamos variables de tipo float, \n\n");

	float a_float_caso_1=10;
	float b_float_caso_1=15;
	
	float c_float_caso_1_division= a_float_caso_1 / b_float_caso_1;
	printf("Si obtenemos el resultado esperado: %f / %f= %f\n\n", a_float_caso_1,b_float_caso_1,c_float_caso_1_division);
	return 0;	
}

