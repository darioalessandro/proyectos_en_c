#import <stdio.h>
#import <string.h>
#import <math.h>
#import <stdlib.h>
#include <time.h>

char * normalize_plain_text_to_be_key_length_multiple(char * plain_text, int * key, int key_length){
	char * normalized_plain_text=NULL;
	int plain_text_length=strlen(plain_text);		
	int plain_text_mod_key_length=plain_text_length%key_length;	
	if(plain_text_mod_key_length!=0){		
		int number_of_chars_to_add=key_length- plain_text_mod_key_length;
		char bunch_of_spaces[number_of_chars_to_add];				
		memset(bunch_of_spaces,' ', number_of_chars_to_add);
		char * pointer_to_last_element_of_bunch_of_spaces=&bunch_of_spaces[number_of_chars_to_add];
		memset(pointer_to_last_element_of_bunch_of_spaces,0, 1); //Added NULL character to mark the end of the string.		
		normalized_plain_text= calloc(plain_text_length+number_of_chars_to_add, sizeof(char));
		sprintf(normalized_plain_text, "%s%s", plain_text, bunch_of_spaces);		
	}else{
		normalized_plain_text=strdup(plain_text);
	}
	return normalized_plain_text;
}

int index_of(int j,int * key, int key_length){
	int index_of=0;
	for(int i=0;i<key_length;i++){
		if(key[i]==j){
			index_of=i;
			break;	
		}		
	}
	return index_of;
}

char * encrypt(char * plain_text,int * key, int key_length){	
	int plain_text_length=strlen(plain_text);	
	int number_of_blocks= (int) ceil(((float)plain_text_length/(float)key_length));
	char * encrypted_text= calloc(plain_text_length, sizeof(char));
	for(int i=0; i<number_of_blocks;i++){		
		for(int j=0;j<key_length;j++){	
			int encrypted_text_index= i * key_length + j;				
			int plain_text_index= i * key_length + key[j];			
			encrypted_text[encrypted_text_index]= plain_text[plain_text_index];
		}
	}
	return encrypted_text;
}

char * decrypt(char * encrypted_text,int * key, int key_length){
	int encrypted_text_length=strlen(encrypted_text);	
	int number_of_blocks= (int) ceil(((float)encrypted_text_length/(float)key_length));	
	char * decrypted_text= calloc(encrypted_text_length, sizeof(char));
	for(int i=0; i<number_of_blocks;i++){		
		for(int j=0;j<key_length;j++){	
			int decrypted_text_index= i * key_length + j;							
			int encrypted_text_index= i * key_length + index_of(j,key,key_length);			
			decrypted_text[decrypted_text_index]= encrypted_text[encrypted_text_index];			
		}
	}
	return decrypted_text;
}



int main(){	
	char * normalize_plain_text_to_be_key_length_multiple(char * plain_text, int * key, int key_length);	
	int index_of(int j,int * key, int key_length);
	char * encrypt(char * plain_text,int * key, int key_length);
	char * decrypt(char * encrypted_text,int * key, int key_length);
	
	const clock_t initial_time = clock();
	
	//1) Plain Text	
	char * plain_text= "Metallica es una banda de thrash metal originaria de Los Ángeles, pero con base en San Francisco desde febrero de 1983. Fue fundada en 1981 en Los Ángeles por el danés Lars Ulrich y James Hetfield, a los que se les unirían Lloyd Grant y Ron McGovney. Estos dos músicos fueron después sustituidos por el guitarrista Dave Mustaine y el bajista Cliff Burton, Mustaine fue despedido un año después de ingresar en la banda debido a su excesiva adicción al alcohol y su actitud violenta, y fundó la banda Megadeth, siendo sustituido por Kirk Hammett ex guitarrista de Exodus. Por otra parte, en 1986, la muerte de Cliff Burton en un accidente de autobús en Suecia provocó la entrada al grupo de Jason Newsted,2 quien, tras su abandono quince años más tarde, sería sustituido por el bajista actual, Robert Trujillo.";
	printf("Plain text: %s\n\n", plain_text);	
	
	//2) Define key
	int key[]={3,9,12,0,11,1,4,13,5,7,14,8,10,2,6};
	int key_length=sizeof(key)/sizeof(key[0]);	

	char * normalized_plain_text= normalize_plain_text_to_be_key_length_multiple(plain_text, key, key_length);

	//3) Encryption
	char * encrypted_text= encrypt(normalized_plain_text,key,key_length);
	printf("Encrypted text: %s\n\n", encrypted_text);

	//4) Decryption
	char * decrypted_text= decrypt(encrypted_text,key,key_length);
	printf("Decrypted text: %s\n\n", decrypted_text);

	//5) Verification
	int success= strcmp(normalized_plain_text, decrypted_text);
	if(success==0){
		printf("It works.\n\n");
	}else{
		printf("#fail\n\n");
	}

	//Clean up everything that you own, (memory reserved with calloc, strdup & malloc)	
	free(encrypted_text);
	free(decrypted_text);
	free(normalized_plain_text);
	float clocks_diff= (float) clock() - initial_time;	
	printf("Processing time %f seconds\n", clocks_diff/CLOCKS_PER_SEC);
	return success;
} 