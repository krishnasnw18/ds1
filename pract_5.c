#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for an appointment node
struct Appointment {
    int id;
    int startTime; // e.g., 9 for 9:00 AM
    int endTime;   // e.g., 10 for 10:00 AM
    char patientName[50];
    int isBooked; // 0 for free, 1 for booked
    struct Appointment *prev;
    struct Appointment *next;
};

struct Appointment *head = NULL; // Head of the doubly linked list

// Function to create a new appointment node
struct Appointment* createAppointment(int id, int startTime, int endTime) {
    struct Appointment* newAppointment = (struct Appointment*)malloc(sizeof(struct Appointment));
    if (newAppointment == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newAppointment->id = id;
    newAppointment->startTime = startTime;
    newAppointment->endTime = endTime;
    strcpy(newAppointment->patientName, "N/A");
    newAppointment->isBooked = 0; // Initially free
    newAppointment->prev = NULL;
    newAppointment->next = NULL;
    return newAppointment;
}

// Function to add an appointment slot to the list (sorted by time)
void addAppointmentSlot(int id, int startTime, int endTime) {
    struct Appointment* newSlot = createAppointment(id, startTime, endTime);
    if (head == NULL || startTime < head->startTime) {
        newSlot->next = head;
        if (head != NULL) {
            head->prev = newSlot;
        }
        head = newSlot;
    } else {
        struct Appointment* current = head;
        while (current->next != NULL && current->next->startTime < startTime) {
            current = current->next;
        }
        newSlot->next = current->next;
        newSlot->prev = current;
        if (current->next != NULL) {
            current->next->prev = newSlot;
        }
        current->next = newSlot;
    }
    printf("Appointment slot added: ID %d, Time %d-%d\n", id, startTime, endTime);
}

// a) Display free slots
void displayFreeSlots() {
    struct Appointment* current = head;
    if (current == NULL) {
        printf("No appointment slots available.\n");
        return;
    }
    printf("\n--- Free Appointment Slots ---\n");
    while (current != NULL) {
        if (current->isBooked == 0) {
            printf("ID: %d, Time: %d:00 - %d:00\n", current->id, current->startTime, current->endTime);
        }
        current = current->next;
    }
    printf("----------------------------\n");
}

// b) Book appointment
void bookAppointment(int desiredTime, const char* patientName) {
    struct Appointment* current = head;
    while (current != NULL) {
        if (current->isBooked == 0 && desiredTime >= current->startTime && desiredTime < current->endTime) {
            current->isBooked = 1;
            strcpy(current->patientName, patientName);
            printf("Appointment booked for %s at %d:00 (Slot ID: %d).\n", patientName, desiredTime, current->id);
            return;
        }
        current = current->next;
    }
    printf("No free slot available at %d:00 or invalid time specified.\n", desiredTime);
}

// c) Sort list based on time (already handled in addAppointmentSlot for simplicity)
// If a separate sort function is required, a bubble sort or insertion sort can be implemented.
// For example:
void sortAppointmentsByTime() {
    // This function assumes 'addAppointmentSlot' already keeps the list sorted.
    // If not, a sorting algorithm like bubble sort or insertion sort on the linked list
    // would be implemented here by swapping node data or re-linking pointers.
    printf("List is already sorted by time during insertion.\n");
}

// d) Cancel appointment (check validity, time bounds, availability)
void cancelAppointment(int slotId) {
    struct Appointment* current = head;
    while (current != NULL) {
        if (current->id == slotId) {
            if (current->isBooked == 1) {
                current->isBooked = 0;
                strcpy(current->patientName, "N/A");
                printf("Appointment for Slot ID %d cancelled successfully.\n", slotId);
            } else {
                printf("Slot ID %d is already free.\n", slotId);
            }
            return;
        }
        current = current->next;
    }
    printf("Slot ID %d not found.\n", slotId);
}

// e) Sort list based on time using pointer manipulation (Example: Bubble Sort)
void sortListByPointerManipulation() {
    struct Appointment *i, *j;
    int swapped;

    if (head == NULL) {
        return;
    }

    do {
        swapped = 0;
        i = head;
        while (i->next != NULL) {
            if (i->startTime > i->next->startTime) {
                // Swap nodes by manipulating pointers
                struct Appointment* node1 = i;
                struct Appointment* node2 = i->next;

                // Adjust next/prev pointers
                if (node1->prev != NULL) {
                    node1->prev->next = node2;
                } else {
                    head = node2; // New head
                }
                if (node2->next != NULL) {
                    node2->next->prev = node1;
                }

                node1->next = node2->next;
                node2->prev = node1->prev;
                node2->next = node1;
                node1->prev = node2;

                swapped = 1;
            } else {
                i = i->next;
            }
        }
    } while (swapped);
    printf("List sorted by time using pointer manipulation.\n");
}


void displayAllAppointments() {
    struct Appointment* current = head;
    if (current == NULL) {
        printf("No appointment slots to display.\n");
        return;
    }
    printf("\n--- All Appointment Slots ---\n");
    while (current != NULL) {
        printf("ID: %d, Time: %d:00 - %d:00, Status: %s, Patient: %s\n",
               current->id, current->startTime, current->endTime,
               current->isBooked ? "Booked" : "Free", current->patientName);
        current = current->next;
    }
    printf("----------------------------\n");
}

int main() {
    // Add some initial appointment slots
    addAppointmentSlot(1, 10, 11);
    addAppointmentSlot(2, 9, 10);
    addAppointmentSlot(3, 11, 12);
    addAppointmentSlot(4, 14, 15);

    displayAllAppointments();
    displayFreeSlots();

    bookAppointment(9, "Alice");
    bookAppointment(10, "Bob");
    bookAppointment(13, "Charlie"); // Invalid time

    displayAllAppointments();
    displayFreeSlots();

    cancelAppointment(2); // Cancel Alice's appointment
    cancelAppointment(5); // Non-existent slot

    displayAllAppointments();

    printf("\nAttempting to sort by pointer manipulation (already sorted by insertion):\n");
    sortListByPointerManipulation(); // Demonstrates the sorting function
    displayAllAppointments();

    // Free allocated memory (important for preventing memory leaks)
    struct Appointment* current = head;
    while (current != NULL) {
        struct Appointment* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;

    return 0;
}