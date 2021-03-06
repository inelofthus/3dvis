// assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <stdio.h>
using namespace std;

const int NUMSAMPLES = 1750;
const int NUMTRACES = 13483;
char matrix[NUMTRACES][NUMSAMPLES];
const char* fileName = "NVGT-88-06.sgy";

void ReadSEGYTrace(const char* sFileName) {
	FILE *pFile = fopen(sFileName, "rb");
	fseek(pFile, 3600, SEEK_SET); //Skip file header

	for (int i = 0; i < NUMTRACES; i++) {
		fseek(pFile, 240, SEEK_CUR); //Skip trace header

		for (int j = 0; j < NUMSAMPLES; j++) {
			fread(&matrix[i][j], 1, 1, pFile);
		}
	}
	fclose(pFile);
}

int main()
{
	try {
		ReadSEGYTrace(fileName);
		cout << "Hello world" << endl;
		for (int j = 40; j <= 54; j++) {
			cout << (int) matrix[50][j] << ' ';
		}
	}
	catch (int e){
		cout << "Exception " << e << endl;
	}
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
