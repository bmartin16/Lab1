#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1

/**
 * Parses the command line.
 *
 * argc: the number of items on the command line (and length of the
 *       argv array) including the executable
 * argv: the array of arguments as strings (char* array)
 * bits: the integer value is set to TRUE if bits output indicated
 *       outherwise FALSE for hex output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *bits) {
  if (argc > 2) {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }

  if (argc == 2 &&
      (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
    *bits = TRUE;
  } else {
    *bits = FALSE;
  }

  return stdin;
}

/**
 * Writes data to stdout in hexadecimal.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsHex(unsigned char *data, size_t size) {
	if(size == 16){
		for(unsigned int i = 0; i < size; i++){
          		if(i % 2 == 0){
				printf(" ");
			}
			printf("%02x", data[i]);
		}
	}
	if(size != 16){
		for(unsigned int i = 0; i < size; i++){
			if(i % 2 == 0){
				printf(" ");
			}
                	printf("%02x", data[i]);
		}
  		for(unsigned int i = 0; i < 16-size; i++){
			if(i % 2 == 0 && i != 16-size-1) {
			printf(" ");
			}
			printf("  ");
		}
	}
}

/**
 * Writes data to stdout as characters.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsChars(unsigned char *data, size_t size) {
	for(unsigned int i = 0; i < size; i++){
		if((unsigned int)data[i] < 32 || (unsigned int)data[i] > 126){
			printf(".");
		}
		else{
		printf("%c", data[i]);
		}
        	
  	}
}

void charToBits(unsigned char c) {
	unsigned char bits[8];
	for(unsigned int i = 0; i < 8; i++){
		if(c % 2 == 1) {
			bits[i] = 1;
		}
		else {
			bits[i] = 0;
		}
		c = c / 2;
	}
	printf(" ");
	for(int i = 7; i >= 0; i--) {
		printf("%u", bits[i]);
	}
}

void printDataAsBits(unsigned char *data, size_t size) {
	if(size == 6) {
		for(unsigned int i = 0; i < size; i++){
			charToBits(data[i]);
		}
	}
	else {
		for(unsigned int i = 0; i < size; i++){
		 	charToBits(data[i]);
		}
                for(unsigned int i = 0; i < 6-size; i++){
			printf("         ");
                }

	}
}

void readAndPrintInputAsHex(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 16, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsHex(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 16, input);
  }
}

/**
 * Bits output for xxd.
 *
 * See myxxd.md for details.
 *
 * input: input stream
 **/
void readAndPrintInputAsBits(FILE *input) {
  unsigned char data[6];
  int numBytesRead = fread(data, 1, 6, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsBits(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 6, input);
  }
}

int main(int argc, char **argv) {
  int bits = FALSE;
  FILE *input = parseCommandLine(argc, argv, &bits);

  if (bits == FALSE) {
    readAndPrintInputAsHex(input);
  } else {
    readAndPrintInputAsBits(input);
  }
  return 0;
}



