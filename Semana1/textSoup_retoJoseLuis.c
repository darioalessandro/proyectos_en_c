#import <stdio.h>
#import <string.h>
#import <math.h>
#import <stdlib.h>
#include <time.h>

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
	char * decrypt(char * encrypted_text,int * key, int key_length);
	
	const clock_t initial_clock = clock();
		
	int key[]={3,9,12,0,11,1,4,13,5,7,14,8,10,2,6};
	int key_length=sizeof(key)/sizeof(key[0]);	

	//3) Encryption
	char * encrypted_text= "  yAunsih'nsbde w gy sttioraaaa    hv e    en";//encrypt(normalized_plain_text,key,key_length);
	printf("Encrypted text: %s\n\n", encrypted_text);

	//4) Decryption
	char * decrypted_text= decrypt(encrypted_text,key,key_length);
	printf("Decrypted text: %s\n\n", decrypted_text);

	free(decrypted_text);	
	float clocks_diff= (float) clock() - initial_clock;	
	printf("Processing time %e seconds\n", clocks_diff/CLOCKS_PER_SEC);
	return 0;
} 