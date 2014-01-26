#include <stdio.h>

int main(void){
	printf("\n\nTamaño de un entero (int) en este sistema medido en bytes: %lu\n\n", sizeof(int));
	// En mi compu, esto da 4, utilizando matemática binaria, obtenemos que: 2^(4 * 8)= 4,294,967,296
	// Pero como esos 4 bytes son para números positivos y negativos, tenemos que dividir entre 2 menos 1 
	// (hablaremos mas de esto cuando toquemos el tema de matemática binaria)
	// Por lo que el número máximo en mi sistema es 2,147,483,647
	int a_int_caso_2=2147483647;
	int b_int_caso_2=1;
	int c_int_caso_2_suma= a_int_caso_2 + b_int_caso_2;
	printf("No obtenemos el resultado esperado: %d + %d= %d\n\n", a_int_caso_2,b_int_caso_2,c_int_caso_2_suma);	

	printf("Pero si utilizamos números dobles...\n\n"); 
	printf("Tamaño de un número de punto flotante de doble precisión (double) en este sistema medido en bytes: %lu\n\n", sizeof(double));
	double a_float_caso_2=2147483647;
	double b_float_caso_2=1;
	double c_float_caso_2_suma= a_float_caso_2 + b_float_caso_2;
	printf("Si obtenemos el resultado esperado: %lf + %lf= %lf\n\n", a_float_caso_2,b_float_caso_2,c_float_caso_2_suma);	
	return 0;	
}
