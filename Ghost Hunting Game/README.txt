Name: Rayan Ourdjini
Student #: 101266109



Program Purpose: 
The purpose of this is to create a pixled camera that is shrinked in size. 
Files Included:
•	a2-posted.c
•	camera.o
•	README.txt


Instructions for compiling the program: 
You have to compile the program with source code and the camera.o: to do this you have to: bash and then gcc -o a2 a2-posted.c camera.o


Instructions for running the program:
bash
./a

Instructions for how to use the program once its running:
It will print the image once it runs


I asked chat to Implement the encode_bits() function. and it gave me:
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




I asked chat to make the pack bits and it gave me:
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

I asked chat to make the loop in the main and it gave me:
while (1) {
        unsigned char raw_photo[MAX_ARR];
        int rows, cols;
        int image_size;

        image_size = take_photo(raw_photo, &rows, &cols);

