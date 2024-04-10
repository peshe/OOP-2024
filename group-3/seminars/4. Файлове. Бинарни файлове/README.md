# Бинарни файлове

Кодът от първия час на семинара, в който показахме писане и четене в бинарни файлове:

```c++
#pragma once
#include <iostream>
#include <fstream>

using namespace std;

void writeBuiltInTypesToBinaryFile(const char* fileName)
{
	ofstream outBinaryStream = ofstream(fileName, std::ios::binary);

	if (!outBinaryStream) {
		cerr << "Couldn't open file " << fileName << endl;
		return;
	}

	int x = 42;
	bool isPositive = true;
	double pi = 3.14;
	char c = 'A';

	outBinaryStream.write((const char*)&x, sizeof(x));
	outBinaryStream.write((const char*)&isPositive, sizeof(isPositive));
	outBinaryStream.write((const char*)&pi, sizeof(pi));
	outBinaryStream.write((const char*)&c, sizeof(c));

	if (outBinaryStream.good()) {
		cout << "Built in types:" << endl;
		cout << x << endl;
		cout << isPositive << endl;
		cout << pi << endl;
		cout << c << endl;
	}
	else {
		cerr << "Failed writing to file" << endl;
	}

	cout << endl;
	outBinaryStream.close();
}
void readBuiltInTypesToBinaryFile(const char* fileName)
{
	ifstream inBinaryStream = ifstream(fileName, std::ios::binary);

	if (!inBinaryStream) {
		cerr << "Couldn't open file " << fileName << endl;
		return;
	}

	int x;
	bool isPositive;
	double pi;
	char c;

	inBinaryStream.read((char*)&x, sizeof(x));
	inBinaryStream.read((char*)&isPositive, sizeof(isPositive));
	inBinaryStream.read((char*)&pi, sizeof(pi));
	inBinaryStream.read((char*)&c, sizeof(c));

	if (inBinaryStream.good()) {
		cout << "Built in types read from file:" << endl;
		cout << x << endl;
		cout << isPositive << endl;
		cout << pi << endl;
		cout << c << endl;
	}
	else {
		cerr << "Coudln't read file." << endl;
	}

	inBinaryStream.close();
}


void writeStaticArrayToBinaryFile(const char* fileName)
{
	ofstream outBinaryStream = ofstream(fileName, std::ios::binary);

	if (!outBinaryStream) {
		cerr << "Couldn't open file " << fileName << endl;
		return;
	}

	int numbers[128] = { 1,2,3,4,5,6,7 };
	size_t size = sizeof(numbers);
	size_t numbersSize = 7;

	outBinaryStream.write((const char*)&numbersSize, sizeof(numbersSize));
	for (size_t i = 0; i < numbersSize; i++)
	{
		outBinaryStream.write((const char*)&numbers[i], sizeof(numbers[i]));
	}

	if (outBinaryStream.good()) {

		cout << numbersSize << endl;
		for (size_t i = 0; i < numbersSize; i++)
		{
			cout << numbers[i] << " ";
		}
		cout << endl;
	}
	else {
		cerr << "Couldn't write to file" << endl;
	}

	outBinaryStream.close();
}

void readStaticArrayToBinaryFile(const char* fileName)
{
	ifstream inBinaryStream = ifstream(fileName, std::ios::binary);

	if (!inBinaryStream) {
		cerr << "Couldn't open file " << fileName << endl;
		return;
	}

	int numbers[128];
	size_t numbersSize;

	inBinaryStream.read((char*)&numbersSize, sizeof(numbersSize));
	for (size_t i = 0; i < numbersSize; i++)
	{
		inBinaryStream.read((char*)&numbers[i], sizeof(numbers[i]));
	}

	if (inBinaryStream.good()) {

		cout << numbersSize << endl;
		for (size_t i = 0; i < numbersSize; i++)
		{
			cout << numbers[i] << " ";
		}
		cout << endl;
	}
	else {
		cerr << "Couldn't write to file" << endl;
	}

	inBinaryStream.close();
}



void writeDynamicArrayToBinaryFile(const char* fileName)
{
	ofstream outBinaryStream = ofstream(fileName, std::ios::binary);

	if (!outBinaryStream) {
		cerr << "Couldn't open file " << fileName << endl;
		return;
	}

	size_t numbersSize = 7;
	int* numbers = new int[numbersSize] { 11, 22, 33, 44, 55, 66, 77 };

	outBinaryStream.write((const char*)&numbersSize, sizeof(numbersSize));
	for (size_t i = 0; i < numbersSize; i++)
	{
		outBinaryStream.write((const char*)&numbers[i], sizeof(numbers[i]));
	}

	if (outBinaryStream.good()) {

		cout << numbersSize << endl;
		for (size_t i = 0; i < numbersSize; i++)
		{
			cout << numbers[i] << " ";
		}
		cout << endl;
	}
	else {
		cerr << "Couldn't write to file" << endl;
	}

	outBinaryStream.close();
	delete[] numbers;
}

void readDynamicArrayToBinaryFile(const char* fileName)
{
	ifstream inBinaryStream = ifstream(fileName, std::ios::binary);

	if (!inBinaryStream) {
		cerr << "Couldn't open file " << fileName << endl;
		return;
	}

	size_t numbersSize;

	inBinaryStream.read((char*)&numbersSize, sizeof(numbersSize));

	int* numbers = new int[numbersSize];

	for (size_t i = 0; i < numbersSize; i++)
	{
		inBinaryStream.read((char*)&numbers[i], sizeof(numbers[i]));
	}

	if (inBinaryStream.good()) {

		cout << numbersSize << endl;
		for (size_t i = 0; i < numbersSize; i++)
		{
			cout << numbers[i] << " ";
		}
		cout << endl;
	}
	else {
		cerr << "Couldn't write to file" << endl;
	}

	inBinaryStream.close();
	delete[] numbers;
}

```