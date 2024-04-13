// Name: Marco Yglesia
// Date: April 12th, 2024
// Assignment: Lab 9
// Programming Language: C

#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType {
    struct RecordType **my_Table;
    int size;

};

void displayRecordsInHash(struct HashType *pHashArray, int hashSz);
int hash(int x);
int parseData(char* inputFileName, struct RecordType** ppData);
void printRecords(struct RecordType pData[], int dataSz);

// START OF DRIVER CODE
int main(void) {
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
} // END OF DRIVER CODE


// Compute the hash function
int hash(int x) {
    return x%23;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    printf("\n%d:\n",dataSz);

    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;

    for (i=0;i<hashSz;++i)
    {
        // if index is occupied with any records, print all
    }
}

void initTable(struct HashType *Table, int size) {
   Table->my_Table = malloc(size * sizeof(struct RecordType));
    // Initialize all pointers to NULL
    for (int i = 0; i < size; i++) {
        Table->my_Table[i] = NULL;
    }
    Table->size = size;
}