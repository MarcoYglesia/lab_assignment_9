// Name: Marco Yglesia
// Date: April 12th, 2024
// Assignment: Lab 9, Hashing with Separate Chaining
// Programming Language: C

#include <stdio.h>
#include <stdlib.h>

// RecordType
// The info we are taking in.
struct RecordType {
	int		id;
	char	name;
	int		order;
};

// Fill out this structure
// This is a node.
struct HashType {
    struct RecordType **my_Table;
    int size;
};

// This is a node for the linked list. Needed for Separate Chaining.
struct Node {
    struct RecordType record;
    struct Node* next;
};

// Functions
void displayRecordsInHash(struct HashType *pHashArray, int hashSz);
int hash(int x);

int parseData(char* inputFileName, struct RecordType** ppData);
void printRecords(struct RecordType pData[], int dataSz);
void initTable(struct HashType *hashTable,int size);
void insertTable(struct HashType *hashTable, struct RecordType *record);

// START OF DRIVER CODE ----------------------------------------------------------------------
int main(void)
{
    // CREATE A VARIABLE FOR PERSONAL RECORDS
    struct RecordType *pRecords;
    int recordSz;
    struct HashType hashTable;

    // This assign the values into our array pRecords & gives us the number of records.
    recordSz = parseData("/Users/marcoyglesia/Desktop/C Code/COP 3502 CS1/lab_assignment_9/input_lab_9.txt", &pRecords);

    printRecords(pRecords, recordSz);


    // Your hash implementation

    // Initiate the hash table...
    initTable(&hashTable,recordSz);

    // Add values from array into the Hash Table
    for (int i = 0; i < recordSz; i++) {
        insertTable(&hashTable, &pRecords[i]);
    }

    // Print out the Hash Table
    displayRecordsInHash(&hashTable,hashTable.size);


}
// END OF DRIVER CODE ----------------------------------------------------------------------

// Compute the hash function
int hash(int x) {
    return x%23;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData) {
    // READS THE FILE IN
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;

    // ppData IS AN ARRAY OF POINTERS THAT WILL HOUSE OUR INFO
    *ppData = NULL;

    if (inFile) {
        // READS FIRST INTEGER WHICH ASSIGNS THE SIZE OF "dataSz"
        // "dataSz" is used read in the given number of entries
        fscanf(inFile, "%d\n", &dataSz);

        // ALLOCATE MEM FOR "ppDATA" FOR THE GIVEN AMOUNT OF ENTRIES
        *ppData = (struct RecordType *) malloc(sizeof(struct RecordType) * dataSz);

        // Implement parse data block
        // IF DMA FAILS...
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        } else {
            // IF DMA IS SUCCESSFUL
            for (i = 0; i < dataSz; ++i) {
                // READS IN AND ASSIGNS THE INFO INTO OUR "ppData" ARRAY
                pRecord = *ppData + i;
                fscanf(inFile, "%d ", &n);
                pRecord->id = n;
                fscanf(inFile, "%c ", &c);
                pRecord->name = c;
                fscanf(inFile, "%d ", &n);
                pRecord->order = n;
            }
            fclose(inFile);

            return dataSz;
        }
    }
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n");
}

// FUNCTION: Displays info being held in the Hash Table
void displayRecordsInHash(struct HashType *pHashArray, int hashSz) {
    for (int i=0;i<hashSz;++i) {
        // Temp node to aid in printing out info being held at different indexes of Hash Table
        struct Node* temp = pHashArray->my_Table[i];

        if (temp == NULL){
            // Does nothing, no print .3.
        }
        else{
            printf("\n");
            printf("Index %d ",i);
            while(temp != NULL) {
                printf("-> %d %c %d ", temp->record.id, temp->record.name, temp->record.order);
                temp=temp->next; // Moves along the chain
            }
        }
    }
}

// FUNCTION: Initiates the Hash Table
void initTable(struct HashType *hashTable,int size) {
    // Allocate memory for our hash table.
    // Keep in mind that our Hash Table is kind of like an array of linked list, so we must allocate memory accordingly.
    hashTable->my_Table = (struct Node **) malloc(sizeof(struct Node *) * size);
    // Set the size of the table.
    hashTable->size = size;

    // Set all of these to NULL to be filled later.
    for (int i=0; i<size; i++) {
        hashTable->my_Table[i] = NULL;
    }
}


// FUNCTION: Takes in the hashTable and the pRecord's and adds value.
void insertTable(struct HashType *hashTable, struct RecordType *record) {
    // Calculate hash value.
    int hashval = hash(record->id);
    // Find the index we will insert info base on hash value and given table size.
    int index = hashval % hashTable->size;

    // Create a new node for the record that will later be inserted.
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    // Assign passed record info to temp node.
    temp->record = *record;
    // Assign node's next to NULL, this may change in the future depending on collisions.
    temp->next = NULL;

    // Insert node into the linked list at the calculated index...
    // If this is the first node at the index set as head
    if (hashTable->my_Table[index] == NULL){
        hashTable->my_Table[index] = temp;
    } else
        // If another value is located at the index, have it be pointed to by the previous value.
    {
        // Create another temp variable to keep track of current value being stored.
        struct Node *occupied = hashTable->my_Table[index];
        while (occupied->next != NULL) { // Find the next available spot.
            occupied = occupied->next;
        }
        occupied->next = temp;
    }
}