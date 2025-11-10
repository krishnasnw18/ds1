#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
struct Node {
    int rollNumber;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int roll) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->rollNumber = roll;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertNode(struct Node** head_ref, int roll) {
    struct Node* newNode = createNode(roll);
    if (*head_ref == NULL) {
        *head_ref = newNode;
    } else {
        struct Node* temp = *head_ref;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->rollNumber);
        temp = temp->next;
    }
    printf("\n");
}

// Function to check if a roll number exists in a linked list
int contains(struct Node* head, int roll) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->rollNumber == roll) {
            return 1; // Found
        }
        temp = temp->next;
    }
    return 0; // Not found
}

// a) Set of students who like both vanilla and butterscotch (Intersection)
void findIntersection(struct Node* vanillaSet, struct Node* butterscotchSet) {
    printf("Students who like both vanilla and butterscotch: ");
    struct Node* temp = vanillaSet;
    while (temp != NULL) {
        if (contains(butterscotchSet, temp->rollNumber)) {
            printf("%d ", temp->rollNumber);
        }
        temp = temp->next;
    }
    printf("\n");
}

// b) Set of students who like either vanilla or butterscotch or not both (Symmetric Difference)
void findSymmetricDifference(struct Node* vanillaSet, struct Node* butterscotchSet) {
    printf("Students who like either vanilla or butterscotch or not both: ");
    struct Node* temp;

    // Add elements from vanillaSet not in butterscotchSet
    temp = vanillaSet;
    while (temp != NULL) {
        if (!contains(butterscotchSet, temp->rollNumber)) {
            printf("%d ", temp->rollNumber);
        }
        temp = temp->next;
    }

    // Add elements from butterscotchSet not in vanillaSet
    temp = butterscotchSet;
    while (temp != NULL) {
        if (!contains(vanillaSet, temp->rollNumber)) {
            printf("%d ", temp->rollNumber);
        }
        temp = temp->next;
    }
    printf("\n");
}

// c) Number of students who like neither vanilla nor butterscotch
void countNeither(struct Node* allStudents, struct Node* vanillaSet, struct Node* butterscotchSet) {
    int count = 0;
    struct Node* temp = allStudents;
    while (temp != NULL) {
        if (!contains(vanillaSet, temp->rollNumber) && !contains(butterscotchSet, temp->rollNumber)) {
            count++;
        }
        temp = temp->next;
    }
    printf("Number of students who like neither vanilla nor butterscotch: %d\n", count);
}

int main() {
    struct Node* vanillaSet = NULL;
    struct Node* butterscotchSet = NULL;
    struct Node* allStudents = NULL; // Represents the universal set of all students

    // Populate sets (example data)
    // All students
    insertNode(&allStudents, 101);
    insertNode(&allStudents, 102);
    insertNode(&allStudents, 103);
    insertNode(&allStudents, 104);
    insertNode(&allStudents, 105);

    // Students who like vanilla
    insertNode(&vanillaSet, 101);
    insertNode(&vanillaSet, 103);
    insertNode(&vanillaSet, 104);

    // Students who like butterscotch
    insertNode(&butterscotchSet, 102);
    insertNode(&butterscotchSet, 103);
    insertNode(&butterscotchSet, 105);

    printf("Vanilla Ice-cream Lovers: ");
    displayList(vanillaSet);
    printf("Butterscotch Ice-cream Lovers: ");
    displayList(butterscotchSet);
    printf("All Students: ");
    displayList(allStudents);

    // Perform operations
    findIntersection(vanillaSet, butterscotchSet);
    findSymmetricDifference(vanillaSet, butterscotchSet);
    countNeither(allStudents, vanillaSet, butterscotchSet);

    // Free allocated memory (important to prevent memory leaks)
    struct Node* current;
    struct Node* next;

    current = vanillaSet;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    current = butterscotchSet;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    current = allStudents;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;

}
