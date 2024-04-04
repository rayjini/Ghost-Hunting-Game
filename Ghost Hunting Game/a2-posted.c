#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 5000

int take_photo(unsigned char out[], int* rows, int* cols);
unsigned char get_bit(unsigned char byte, int bit);
unsigned char set_bit(unsigned char byte, int bit);
unsigned char clear_bit(unsigned char byte, int bit);
void print_raw(unsigned char raw_string[], int rows, int cols);
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]);
void print_packed(unsigned char packed[], int rows, int cols);
int encode_bits(unsigned char packed_bytes[], int packed_size, unsigned char encoded_result[]);
void print_encoded(unsigned char encoded_bytes[], int encoded_size, int rows, int cols);


//CHATGPT
int encode_bits(unsigned char packed_bytes[], int packed_size, unsigned char encoded_bytes[]) {
    int encoded_size = 0;
    int count = 0;  

    for (int i = 0; i < packed_size * 8; i++) {
        unsigned char current_byte = packed_bytes[i / 8];
        unsigned char current_bit = (current_byte >> (7 - (i % 8))) & 1;

        encoded_bytes[encoded_size++] = current_bit;

        count++;

        if (count == 8) {
            encoded_bytes[encoded_size++] = count;
            count = 0;
        }
    }

    if (count > 0) {
        encoded_bytes[encoded_size++] = count;
    }

    return encoded_size;
}



void print_encoded(unsigned char encoded_bytes[], int encoded_size, int rows, int cols) {
    int index = 0;

    
    for (int i = 0; i < encoded_size; i++) {
        int run_length = encoded_bytes[i];

      
        for (int j = 0; j < run_length; j++) {
            if (index < rows * cols) {
                if (encoded_bytes[i + 1]) {
                    printf("*");
                } else {
                    printf(".");
                }
                index++;
            }
        }

        
        i++;
    }

    printf("\n");
}


//CHATGPT
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]) {
    int packed_index = 0; // Index for the packed string
    unsigned char current_byte = 0; // The byte to hold packed bits
    int current_bit = 0; // Index for the current bit in the current byte
    int total_packed_bytes = 0; // Total number of packed bytes

    for (int i = 0; i < num_chars; i++) {
        if (unpacked_string[i] == '1') {
            current_byte = set_bit(current_byte, current_bit);
        } else if (unpacked_string[i] == '0') {
            current_byte = clear_bit(current_byte, current_bit);
        }

        current_bit--;

        if (current_bit < 0) {
            packed_result[packed_index] = current_byte;
            packed_index++;
            total_packed_bytes++;
            current_byte = 0;
            current_bit = 7;
        }
    }

    if (current_bit != 7) {
        packed_result[packed_index] = current_byte;
        packed_index++;
        total_packed_bytes++;
    }

    return total_packed_bytes;
}



void print_packed(unsigned char packed[], int rows, int cols) {
    int packed_index = 0;
    int bit_count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (bit_count < rows * cols) {
                if (get_bit(packed[packed_index], 7 - (j % 8))) {
                    printf("*");
                } else {
                    printf(".");
                }

                if ((j + 1) % 8 == 0) {
                    packed_index++;
                }

                bit_count++;
            }
        }
        printf("\n");
    }
}



void print_raw(unsigned char raw_string[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (raw_string[i * cols + j] == '1')
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}


int main() {
    int image_count = 0;
    int total_packed_bytes = 0;
    int encoded_size = 0;
//Chat ln 153-158
    while (1) {
        unsigned char raw_photo[MAX_ARR];
        int rows, cols;
        int image_size;

        image_size = take_photo(raw_photo, &rows, &cols);

        if (image_size == 0)
            break;

        printf("Raw photo (%d bytes):\n", image_size);
        print_raw(raw_photo, rows, cols);

               unsigned char packed_result[MAX_ARR];
        total_packed_bytes = pack_bits(raw_photo, image_size, packed_result);

        printf("Packed photo (%d bytes):\n", total_packed_bytes);
        print_packed(packed_result, rows, cols);

        unsigned char encoded_result[MAX_ARR];
        encoded_size = encode_bits(packed_result, total_packed_bytes, encoded_result);

        printf("Encoded photo (%d bytes):\n", encoded_size);
        print_encoded(encoded_result, encoded_size, rows, cols);

        printf("\nSizes: raw = %d bytes, packed = %d bytes, encoded = %d bytes\n\n", image_size, total_packed_bytes, encoded_size);

    } 

    return 0;
}



unsigned char get_bit(unsigned char byte, int bit) {
    return (byte >> bit) & 1;
}

unsigned char set_bit(unsigned char byte, int bit) {
    return byte | (1 << bit);
}

unsigned char clear_bit(unsigned char byte, int bit) {
    return byte & ~(1 << bit);
}




/*  Function: take_photo()
    Description: Simulates taking a photo as a black-and-white image represented by
                 an array of characters '1' and '0'. The photo is stored in the out[] array.

    Output: out[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Output: rows    - an address to an integer to store the number of rows in the photo
    Output: cols    - an address to an integer to store the number of columns in the photo

    Returns: the total number of characters in the photo data OR 0 if no photo was taken
    
*/

/* 
    Function: encode_bits()
    Description: Transforms the packed bits into a run-length encoded format.
    Input: packed_bytes[] - an array of packed bits (0s and 1s compacted into bytes)
    Input: packed_size    - the size of the packed_bytes array
    Output: encoded_bytes[] - an array to hold the run-length encoded bits
    Returns: the size of the encoded bits array
*/


/* 
    Function: print_encoded()
    Description: Displays the run-length encoded portrayal of the image.
    Input: encoded_bytes[] - an array of run-length encoded bits
    Input: encoded_size    - the size of the encoded_bytes array
    Input: rows            - the number of rows in the image
    Input: cols            - the number of columns in the image
*/


/* 
    Function: pack_bits()
    Description: Condenses individual bits (0s and 1s) into bytes.
    Input: unpacked_string[] - an array of unpacked bits (as characters '0' and '1')
    Input: num_chars         - the count of characters in the unpacked_string
    Output: packed_result[]  - an array to store the condensed bits
    Returns: the total number of packed bytes
*/


/* 
    Function: print_packed()
    Description: Exhibits the condensed representation of the image.
    Input: packed[] - an array of packed bits
    Input: rows     - the number of rows in the image
    Input: cols     - the number of columns in the image
*/


/* 
    Function: print_raw()
    Description: Presents the raw representation of the image.
    Input: raw_string[] - an array of raw bits (as characters '0' and '1')
    Input: rows         - the number of rows in the image
    Input: cols         - the number of columns in the image
*/


/* 
    Function: get_bit()
    Description: Retrieves the value of a specific bit within a byte.
    Input: byte - the byte from which to retrieve the bit
    Input: bit  - the index of the bit to retrieve (0 to 7)
    Returns: the value of the specified bit (0 or 1)
*/


/* 
    Function: set_bit()
    Description: Sets a specific bit within a byte to 1.
    Input: byte - the byte in which to set the bit
    Input: bit  - the index of the bit to set (0 to 7)
    Returns: the byte with the specified bit set to 1
*/


/* 
    Function: clear_bit()
    Description: Unsets a specific bit within a byte (sets it to 0).
    Input: byte - the byte in which to unset the bit
    Input: bit  - the index of the bit to unset (0 to 7)
    Returns: the byte with the specified bit unset (set to 0)
*/

