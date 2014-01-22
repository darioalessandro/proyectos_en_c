#include <stdio.h>

int main(void){
	int variable_int = 69; 
	float variable_flotante = 3.1416; 
	double variable_doble = 9.81e+11; 
	char variable_char = 'c';
	_Bool variable_boolean = 1;

	printf ("variable_int = %i\n", variable_int); 
	printf ("variable_flotante = %f\n", variable_flotante); 
	printf ("variable_doble = %lf\n", variable_doble); 
	printf ("variable_doble en notación científica= %e\n", variable_doble); 
	printf ("variable_char = %c\n", variable_char);
	printf ("variable_boolean = %i\n", variable_boolean);
	return 0;	
}

