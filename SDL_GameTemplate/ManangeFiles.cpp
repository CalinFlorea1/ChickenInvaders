#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "ManangeFiles.h"

ManangeFiles::ManangeFiles() {
	NumbersOfFilesEntries = 0;

	for (int i = 0; i < 200; i++)
		Files[i] = { 0, 0, 0 };
}

void ManangeFiles::ExportFromFile() {
	char string[300];
	char* temp;
	int n;
	std::ifstream fin("PlayerScore.txt");

	while (fin.getline (string, 299)) {
		temp = strtok(string, " ");

		n = strlen(temp) + 1;
		Files[NumbersOfFilesEntries].nume = new char[n];
		strcpy_s(Files[NumbersOfFilesEntries].nume, n, temp);
		Files[NumbersOfFilesEntries].nume[n - 1] = 0;
		
		Files[NumbersOfFilesEntries].score = atoi (strtok (NULL, " "));
		Files[NumbersOfFilesEntries].Level = atoi (strtok (NULL, " "));
		Files[NumbersOfFilesEntries].L1 = atoi(strtok(NULL, " "));
		Files[NumbersOfFilesEntries].L2 = atoi(strtok(NULL, " "));
		Files[NumbersOfFilesEntries].L3 = atoi(strtok(NULL, " "));
		Files[NumbersOfFilesEntries].L4 = atoi(strtok(NULL, " "));
		NumbersOfFilesEntries++;
	}
	fin.close();
}

inline bool Compar(const FileStuff A, const FileStuff B) {
	if (A.Level == B.Level)
		return A.score > B.score;
	return A.Level > B.Level;
}

void ManangeFiles::ImportToFile(char* _nume, int _scor, int _level, int _L1, int _L2, int _L3, int _L4, int poz) {
	std::ofstream fout("PlayerScore.txt");
	if (poz == -1) {

		int n = strlen(_nume) + 1;
		Files[NumbersOfFilesEntries].nume = new char[n];
		strcpy_s(Files[NumbersOfFilesEntries].nume, n, _nume);
		Files[NumbersOfFilesEntries].nume[n - 1] = 0;
		Files[NumbersOfFilesEntries].Level = _level;
		Files[NumbersOfFilesEntries].score = _scor;
		Files[NumbersOfFilesEntries].L1 = _L1;
		Files[NumbersOfFilesEntries].L2 = _L2;
		Files[NumbersOfFilesEntries].L3 = _L3;
		Files[NumbersOfFilesEntries++].L4 = _L4;

		std::sort(Files, Files + NumbersOfFilesEntries, Compar);

		for (int i = 0; i < NumbersOfFilesEntries; i++) {
			fout << Files[i].nume << " " << Files[i].score << " " << Files[i].Level << " " << Files[i].L1 << " "
				<< Files[i].L2 << " " << Files[i].L3 << " " << Files[i].L4 << "\n";
		}
	}
	else {
		int n = strlen(_nume) + 1;
		Files[poz].nume = new char[n];
		strcpy_s(Files[poz].nume, n, _nume);
		Files[poz].nume[n - 1] = 0;
		Files[poz].Level = _level;
		Files[poz].score = _scor;
		Files[poz].L1 = _L1;
		Files[poz].L2 = _L2;
		Files[poz].L3 = _L3;
		Files[poz].L4 = _L4;

		std::sort(Files, Files + NumbersOfFilesEntries, Compar);

		for (int i = 0; i < NumbersOfFilesEntries; i++) {
			fout << Files[i].nume << " " << Files[i].score << " " << Files[i].Level << " " << Files[i].L1 << " "
				<< Files[i].L2 << " " << Files[i].L3 << " " << Files[i].L4 << "\n";
		}
	}
	fout.close();
}

char* ManangeFiles::ExportNume(int poz) {
	if (poz <= NumbersOfFilesEntries)
		return Files[poz].nume;
}

int ManangeFiles::ExportLevel(int poz) {
	if (poz <= NumbersOfFilesEntries)
		return Files[poz].Level;
}

int ManangeFiles::ExportScore(int poz) {
	if (poz <= NumbersOfFilesEntries)
		return Files[poz].score;
}

int ManangeFiles::ExportL1(int poz) {
	if (poz <= NumbersOfFilesEntries)
		return Files[poz].L1;
}

int ManangeFiles::ExportL2(int poz) {
	if (poz <= NumbersOfFilesEntries)
		return Files[poz].L2;
}

int ManangeFiles::ExportL3(int poz) {
	if (poz <= NumbersOfFilesEntries)
		return Files[poz].L3;
}

int ManangeFiles::ExportL4(int poz) {
	if (poz <= NumbersOfFilesEntries)
		return Files[poz].L4;
}
int ManangeFiles::OutNumbersOfEntries() {
	return NumbersOfFilesEntries;
}