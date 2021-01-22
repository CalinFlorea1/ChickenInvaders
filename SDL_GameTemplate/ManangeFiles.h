#pragma once
#pragma warning(disable:4996)

struct FileStuff {
	char *nume;
	int score;
	int Level;
	int L1, L2, L3, L4;
};

class ManangeFiles {
	FileStuff Files[200];
	int NumbersOfFilesEntries;
public:
	ManangeFiles();
	void ExportFromFile();
	void ImportToFile(char* _nume, int _scor, int _level, int _L1, int _L2, int _L3, int _L4, int poz);

	char* ExportNume(int poz);
	int ExportScore(int poz);
	int ExportLevel(int poz);
	int ExportL1(int poz);
	int ExportL2(int poz);
	int ExportL3(int poz);
	int ExportL4(int poz);
	int OutNumbersOfEntries();
};
