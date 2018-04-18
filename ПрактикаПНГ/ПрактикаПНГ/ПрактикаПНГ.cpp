// ПрактикаПНГ.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>  

using namespace std;

bool tru (char * idat) {
	char TrueIDAT[4] = { 0x49, 0x44, 0x41, 0x54 };

	for (int i = 0; i < 8; i++) {
		if (idat[i] == TrueIDAT[i] && i == 7) {
			return 1;
		}
		else
			if (idat[i] != TrueIDAT[i]) {
				return 0;
				system("pause");
			}
	}
}

int main()
{
	if (__argc != 2) {
		cout << "Error!" << endl;
		return 0;
		system("pause");
	}

	ifstream MyFile;
	MyFile.open(__argv[1], ios::binary);

	if (!MyFile.is_open()) {
		cout << "Error! File not found" << endl;
		return 0;
		system("pause");
	}


	char CheckPNG[8];
	char TruePng[8] = { 0x89, 0x50, 0x4E, 0x47,0x0D, 0x0A, 0x1A, 0x0A };
	MyFile.read(CheckPNG, 8);

	for (int i = 0; i < 8; i++) {
		if (CheckPNG[i] == TruePng[i] && i == 7)
		cout << "This png format!" << endl;
			else
				if (CheckPNG[i] != TruePng[i]) {
				cout << "This is not a png format!" << endl;
				return 0;
				system("pause");
		}
	}

	char IHDRLength[4];
	MyFile.read(IHDRLength, 4);
	int Length=_byteswap_ulong(*((unsigned int*)IHDRLength));

	MyFile.seekg(12,ios::beg);
	char CHECK_CRC_HDR[4];
	MyFile.read(CHECK_CRC_HDR, 4);
	int CRC = _byteswap_ulong(*((unsigned int*)CHECK_CRC_HDR));

	MyFile.seekg(12, ios::beg);
	char CheckIHDR[4];
	char TrueIHDR[4] = {0x49,0x48,0x44,0x52};
	MyFile.read(CheckIHDR, 4);

	for (int i = 0; i < 8; i++) {
		if (CheckIHDR[i] == TrueIHDR[i] && i == 7)
			cout << "IHDR OK" << endl << "Length= " << Length << " CRC= 0x" << hex << CRC << endl<<endl;
		else
			if (CheckIHDR[i] != TrueIHDR[i]) {
				cout << "IHDR NO" << endl;
				return 0;
				system("pause");
			}
	}

	MyFile.seekg(24+Length, ios::beg);
	char CheckIDAT[4];
	MyFile.read(CheckIDAT, 4);

	if (tru(CheckIDAT) == 0) {
		cout << "IDAT NOT FOUND" << endl;
		return 0;
		system("pause");
	}
	
	while (tru(CheckIDAT)!=0) {
		MyFile.seekg(-8, ios::cur);
		cout << "Position IDAT = " << dec << MyFile.tellg() << endl;
		char IDATLength[4];
		MyFile.read(IDATLength, 4);
		int ILength = _byteswap_ulong(*((unsigned int*)IDATLength));
		MyFile.seekg(4 + ILength, ios::cur);
		char CRC_IDAT[4];
		MyFile.read(CRC_IDAT, 4);
		int CRC_IDAT1 = _byteswap_ulong(*((unsigned int*)CRC_IDAT));
		cout << "Length = " << ILength << " CRC = 0x" << hex << CRC_IDAT1 << endl << endl;

		MyFile.seekg(4, ios::cur);
		CheckIDAT[4];
		MyFile.read(CheckIDAT, 4);
	} 
	

	MyFile.seekg(-0xC, ios_base::end);
	char TrueIEND[12] = { 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44,0xAE, 0x42, 0x60, 0x82 };
	char CheckIEND[12];
	MyFile.read(CheckIEND, 12);

	for (int i = 0; i < 8; i++) {
		if (CheckIEND[i] == TrueIEND[i] && i == 7)
			cout << "IEND OK" << endl;
		else
			if (CheckIEND[i] != TrueIEND[i]) {
				cout << "IEND NO" << endl;
				return 0;
				system("pause");
			}
	}

	





	system("pause");
    return 0;
}

