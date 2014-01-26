#include <stdio.h>

int main(void){
	printf("\n\nCaso 1 Errores de redondeo al trabajar con enteros (int).\n\n");
	int a_int_caso_2=10;
	int b_int_caso_2=15;
	int c_int_caso_2_multiplicacion= a_int_caso_2 * b_int_caso_2;
	int c_int_caso_2_suma= a_int_caso_2 + b_int_caso_2;
	int c_int_caso_2_resta= a_int_caso_2 - b_int_caso_2;

	printf("Si obtenemos el resultado esperado: %d * %d= %d\n", a_int_caso_2,b_int_caso_2,c_int_caso_2_multiplicacion);
	printf("Si obtenemos el resultado esperado: %d + %d= %d\n", a_int_caso_2,b_int_caso_2,c_int_caso_2_suma);	
	printf("Si obtenemos el resultado esperado: %d - %d= %d\n", a_int_caso_2,b_int_caso_2,c_int_caso_2_resta);

	int c_int_caso_2_division= a_int_caso_2 / b_int_caso_2;
	printf("\n¡Cuidado!\n\n");
	printf("No obtenemos el resultado esperado: %d / %d= %d\n\n", a_int_caso_2,b_int_caso_2,c_int_caso_2_division);
	printf("Pero si utilizamos variables de tipo float, \n\n");

	float a_float_caso_2=10;
	float b_float_caso_2=15;
	
	float c_float_caso_2_division= a_float_caso_2 / b_float_caso_2;
	printf("Si obtenemos el resultado esperado: %f / %f= %f\n\n", a_float_caso_2,b_float_caso_2,c_float_caso_2_division);
	return 0;	
}

