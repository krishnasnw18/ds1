#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 


typedef struct Client 
{
    char name[50];
    long long phoneNumber;
    int status; 
} Client;


Client hashTable[TABLE_SIZE];


void initHashTable() 
{
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        hashTable[i].status = 0; 
    }
}

int hashFunction(char *name) 
{
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) 
    {
        sum += name[i];
    }
    return sum % TABLE_SIZE;
}

// Second hash function for double hashing
int hashFunction2(char *name) 
{
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++)
     {
        sum += name[i];
    }
    // A common choice for the second hash function: prime - (key % prime)
    // where prime is a prime number smaller than TABLE_SIZE
    return 7 - (sum % 7); // Using 7 as a prime less than 10
}

// Linear Probing
void insertLinearProbing(char *name, long long phoneNumber) 
{
    int index = hashFunction(name);
    int i = 0;
    while (i < TABLE_SIZE) {
        int current_index = (index + i) % TABLE_SIZE;
        if (hashTable[current_index].status == 0 || hashTable[current_index].status == 2) 
        {
            strcpy(hashTable[current_index].name, name);
            hashTable[current_index].phoneNumber = phoneNumber;
            hashTable[current_index].status = 1;
            printf("Client %s inserted at index %d (Linear Probing).\n", name, current_index);
            return;
        }
        i++;
    }
    printf("Hash table is full! Cannot insert %s (Linear Probing).\n", name);
}

//  Quadratic Probing
void insertQuadraticProbing(char *name, long long phoneNumber) {
    int index = hashFunction(name);
    int i = 0;
    while (i < TABLE_SIZE) {
        int current_index = (index + i * i) % TABLE_SIZE;
        if (hashTable[current_index].status == 0 || hashTable[current_index].status == 2) 
        {
            strcpy(hashTable[current_index].name, name);
            hashTable[current_index].phoneNumber = phoneNumber;
            hashTable[current_index].status = 1;
            printf("Client %s inserted at index %d (Quadratic Probing).\n", name, current_index);
            return;
        }
        i++;
    }
    printf("Hash table is full! Cannot insert %s (Quadratic Probing).\n", name);
}

// Double Hashing
void insertDoubleHashing(char *name, long long phoneNumber) 
{
    int index = hashFunction(name);
    int step = hashFunction2(name);
    int i = 0;
    while (i < TABLE_SIZE) 
    {
        int current_index = (index + i * step) % TABLE_SIZE;
        if (hashTable[current_index].status == 0 || hashTable[current_index].status == 2) 
        {
            strcpy(hashTable[current_index].name, name);
            hashTable[current_index].phoneNumber = phoneNumber;
            hashTable[current_index].status = 1;
            printf("Client %s inserted at index %d (Double Hashing).\n", name, current_index);
            return;
        }
        i++;
    }
    printf("Hash table is full! Cannot insert %s (Double Hashing).\n", name);
}


long long searchClient(char *name) 
{
    int index = hashFunction(name);
    int i = 0;
    while (i < TABLE_SIZE) 
    {
        int current_index = (index + i) % TABLE_SIZE;
        if (hashTable[current_index].status == 0) { // Empty slot, client not found
            return -1;
        }
        if (hashTable[current_index].status == 1 && strcmp(hashTable[current_index].name, name) == 0) 
        {
            return hashTable[current_index].phoneNumber;
        }
        i++;
    }
    return -1; 
}

// Display hash table
void displayHashTable() 
{
    printf("\n--- Hash Table Contents ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        if (hashTable[i].status == 1) {
            printf("Index %d: Name: %s, Phone: %lld\n", i, hashTable[i].name, hashTable[i].phoneNumber);
        } else if (hashTable[i].status == 0) {
            printf("Index %d: Empty\n", i);
        } else { // status == 2 (Deleted)
            printf("Index %d: Deleted\n", i);
        }
    }
    printf("---------------------------\n");
}

int main()
 {
    initHashTable();

    // Example insertions using different collision handling techniques
    insertLinearProbing("Ajay", 1234567890);
    insertQuadraticProbing("Bharat", 9876543210);
    insertDoubleHashing("Chetan", 1122334455);
    insertLinearProbing("Devendra", 5566778899); // May cause collision and linear probe
    insertQuadraticProbing("Emran", 9988776655); // May cause collision and quadratic probe
    insertDoubleHashing("Fiza", 4433221100); // May cause collision and double hash

    displayHashTable();

    // Example search
    long long phone = searchClient("Bharat");
    if (phone != -1) {
        printf("\nPhone number for Bharat: %lld\n", phone);
    } else {
        printf("\nBharat not found in the directory.\n");
    }

    phone = searchClient("Zakir");
    if (phone != -1) {
        printf("Phone number for Zakir: %lld\n", phone);
    } else {
        printf("Zakir not found in the directory.\n");
    }

    return 0;
}
