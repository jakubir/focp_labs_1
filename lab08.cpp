#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <time.h>

#include <fstream>

//1. Write a function that takes a file name and returns its size on disk.If the file cannot be opened, the function should return zero.Suggested function prototype :
unsigned long long GetFileSize(char* file_name)
{
	FILE* file = fopen(file_name, "r");

	if (!file)
		return 0;

	unsigned long long res;

	fseek(file, 0, SEEK_END);
	res = ftell(file);
	fclose(file);

	return res;
}

#define BUFFER_SIZE 1024

bool copyFile(const char* source, const char* dest)
{
	size_t count;
	char buffer[BUFFER_SIZE];

	FILE* src_file = fopen(source, "rb");

	if (!src_file)
	{
		printf("Error");

		return 0;
	}

	FILE* out_file = fopen(dest, "wb");

	if (!out_file)
	{
		printf("Error");

		return 0;
	}

	while ((count = fread(buffer, 1, BUFFER_SIZE, src_file)) > 0)
		fwrite(buffer, 1, count, out_file);

	fclose(src_file);
	fclose(out_file);

	return 1;
}

//2. Write a program that truncates a given file to 2048 bytes.Use a buffer
//in memory to store the initial 2KB of the file.Read data using fread,
//close the file and recreate it using the same name and writing only 2048
//bytes or less, if the original file was shorter.Do not enlarge short
//files.

bool truncate_file(const char* filename)
{
	FILE* file = fopen(filename, "rb");

	if (!file)
		return false;

	char buffer[2048];
	size_t count;

	count = fread(buffer, 1, 2048, file);

	fclose(file);
	
	file = fopen(filename, "wb");

	fwrite(buffer, 1, count, file);

	fclose(file);

	return true;
}

//3. Write a program that encrypts binary files by performing an XOR
//operation with a "key." The "key" is a string of characters.Subsequent
//characters of the key are used for subsequent bytes of the encrypted file.
//When the key reaches the end, it is reused.Decryption requires repeating
//these operations with the same key.Verify the program's operation.

bool encrypt_file(const char* filename, const char* key)
{
	FILE* file = fopen(filename, "rb");

	if (!file)
		return false;

	FILE* tmp_file = tmpfile();
	unsigned char buffer[1024];
	size_t count;
	int key_length = strlen(key);

	while ((count = fread(buffer, 1, 1024, file)) > 0)
	{
		for (int i = 0; i < count; i++)
			buffer[i] ^= key[i % key_length];

		fwrite(buffer, 1, count, tmp_file);
	}

	fclose(file);

	file = fopen(filename, "wb");

	if (!file)
		return false;

	fseek(tmp_file, 0, SEEK_SET);

	while ((count = fread(buffer, 1, 1024, tmp_file)) > 0)
		fwrite(buffer, 1, count, file);

	fclose(file);
	fclose(tmp_file);

	return true;
}

//	6. Use C++ ifstream / ofstream(the fstream library) :
//	This program should be run with the following command - line arguments :
//numbers.txt result.txt result.bin
//Open an existing text file with numbers(its name : first command - line argument) and :
//	a) print all numbers to the screen,
//	b) calculate mean and minimum of all read numbers,
//	c) calculated values(mean and minimum) should be stored :
//-as a text in a new file(its name : second command - line argument),
//-as a memory block in a new file(its name : third command - line argument),
//d) calculate and display the sizes of files created in c), hint: use ftell,
//e) close all files.

//7. Use C++ ifstream / ofstream(the fstream library) :
	//Write a definition of a function copyFile that creates an exact copy of a source file.The names of the source and destination files are function parameters.The function should return true if the operation was successful, and false otherwise.Example function prototype :

//bool copyFile(const char* source, const char* dest);

//Call this function for some existing file(e.g.a JPG image) with the name of the destination file different, but with the same extension.Check the copied file e.g.by opening it in a browser.

int main()
{
	char tmp[] = "test.txt";
	char tmp2[] = "test2.txt";

	copyFile("focp-Lab08-tasks.txt", tmp);

	printf("%lld\n", GetFileSize(tmp));

	truncate_file(tmp);

	printf("%lld\n", GetFileSize(tmp));

	encrypt_file(tmp, "abcdef");

	copyFile(tmp, tmp2);

	encrypt_file(tmp, "abcdef");


	//5. Use C++ ifstream / ofstream(the fstream library) :
	//	Open(create) a text file called “numbers.txt”.Write 100 random integers to that file.Close the file.

	srand(time(NULL));

	return 0;
}