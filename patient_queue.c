#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Patient {
int patient_id;
char name[50];
int age;
char disease[100];
int priority;
struct Patient *next;
} Patient;
typedef struct TreatedPatient {
int patient_id;
char name[50];
char disease[100];
char status[20];
struct TreatedPatient *next;
} TreatedPatient;
// Global head pointers for waiting and treated lists
Patient *waitingHead = NULL;
TreatedPatient *treatedHead = NULL;
// Patient ID generator
int next_id = 101;
// Function Prototypes
void registerPatient();
void displayWaitingQueue();
void treatNextPatient();
void displayTreatedPatients();
void searchPatient();
Patient* createPatientNode(char*, int, char*, int);
void insertByPriority(Patient*);
void moveToTreatedList(Patient*);
void clearInput();

int main() {
int choice;
while (1) {
printf("\n===== HOSPITAL PATIENT QUEUE MANAGEMENT =====\n");
printf("1. Register New Patient\n");
printf("2. Display Waiting Queue\n");
printf("3. Treat Next Patient\n");
printf("4. Display Treated Patients\n");
printf("5. Search Patient\n");
printf("6. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
clearInput();
switch(choice) {
case 1: registerPatient(); break;
case 2: displayWaitingQueue(); break;
case 3: treatNextPatient(); break;
case 4: displayTreatedPatients(); break;
case 5: searchPatient(); break;
case 6: exit(0);
default: printf("Invalid choice.\n");
}
}
return 0;
}
// Clears input buffer to avoid scanf issues
void clearInput() {
int c;
while((c = getchar()) != '\n' && c != EOF);
}
// Memory allocation and initialization for new patient node
Patient* createPatientNode(char* name, int age, char* disease, int priority) {
Patient *newNode = (Patient*)malloc(sizeof(Patient));
newNode->patient_id = next_id++;
strcpy(newNode->name, name);
newNode->age = age;
strcpy(newNode->disease, disease);
newNode->priority = priority;
newNode->next = NULL;
return newNode;
}

// Inserts patient in priority order (1 < 2 < 3)
void insertByPriority(Patient *newNode) {
if (!waitingHead || newNode->priority < waitingHead->priority) {
newNode->next = waitingHead;
waitingHead = newNode;
} else {
Patient *temp = waitingHead;
while(temp->next && temp->next->priority <= newNode->priority)
temp = temp->next;
newNode->next = temp->next;
temp->next = newNode;
}
}
// Register a patient (inserts in queue by priority)
void registerPatient() {
char name[50], disease[100];
int age, priority;
printf("Enter patient name: ");
fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;
printf("Enter age: "); scanf("%d", &age); clearInput();
printf("Enter disease: ");
fgets(disease, sizeof(disease), stdin); disease[strcspn(disease, "\n")] = 0;
printf("Enter priority (1=Critical, 2=Serious, 3=Normal): ");
scanf("%d", &priority); clearInput();
Patient *newPatient = createPatientNode(name, age, disease, priority);
insertByPriority(newPatient);
printf("Patient added successfully! Assigned ID: %d\n", newPatient->patient_id);
}
// Display all waiting patients in order
void displayWaitingQueue() {
Patient *temp = waitingHead;
if (!temp) {
printf("No patients in queue.\n");
return;
}
printf("Waiting Queue:\n");
printf("[ID | Name | Age | Disease | Priority]\n");
while(temp) {
printf("[%d | %s | %d | %s | %s]\n", temp->patient_id, temp->name, temp->age, temp->disease, temp->priority==1?"Critical":(temp->priority==2?"Serious":"Normal"));
temp = temp->next;
}
}
// Remove next patient and move to treated list
void treatNextPatient() {
if (!waitingHead) {
printf("No patient to treat!\n");
return;
}
Patient *toTreat = waitingHead;
waitingHead = waitingHead->next;
printf("Next patient: [ID: %d | Name: %s | Priority: %s]\n",
toTreat->patient_id, toTreat->name,
toTreat->priority==1?"Critical":toTreat->priority==2?"Serious":"Normal");
printf("Treatment complete. Record moved to Treated List.\n");
moveToTreatedList(toTreat);
free(toTreat);
}
// Transfers a patient record to treated list
void moveToTreatedList(Patient *p) {
TreatedPatient *treated = (TreatedPatient*)malloc(sizeof(TreatedPatient));
treated->patient_id = p->patient_id;
strcpy(treated->name, p->name);
strcpy(treated->disease, p->disease);
strcpy(treated->status, "Treated");
treated->next = treatedHead;
treatedHead = treated;
}
// Display all treated patients
void displayTreatedPatients() {
TreatedPatient *temp = treatedHead;
if (!temp) {
printf("No treated patients yet.\n");
return;
}
printf("Treated Patients List:\n");
printf("[ID | Name | Disease | Status]\n");
while(temp) {
printf("[%d | %s | %s | %s]\n", temp->patient_id, temp->name, temp->disease, temp->status);
temp = temp->next;
}
}
// Search by ID or name in both active and treated lists
void searchPatient() {
int id, found = 0;
char name[50];
printf("Search by: 1) Patient ID 2) Name : ");
int option;
scanf("%d", &option); clearInput();
if (option == 1) {
printf("Enter patient ID: ");
scanf("%d", &id); clearInput();
} else if (option == 2) {
printf("Enter patient name: ");
fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;
} else {
printf("Invalid search option.\n");
return;
}
// Search in waiting queue
Patient *temp = waitingHead;
while (temp) {
if ((option == 1 && temp->patient_id == id) || (option == 2 && strcmp(temp->name, name) == 0)) {
printf("Found in waiting queue: [ID: %d | Name: %s | Disease: %s | Priority: %s]\n", temp->patient_id, temp->name, temp->disease, temp->priority==1?"Critical":temp->priority==2?"Serious":"Normal");
found = 1;
}
temp = temp->next;
}
// Search in treated list
TreatedPatient *tptr = treatedHead;
while (tptr) {
if ((option == 1 && tptr->patient_id == id) || (option == 2 && strcmp(tptr->name, name) == 0)) {
printf("Found in treated list: [ID: %d | Name: %s | Disease: %s | Status: %s]\n", tptr->patient_id, tptr->name, tptr->disease, tptr->status);
found = 1;
}
tptr = tptr->next;
}
if (!found) {
printf("Patient not found.\n");
}
}
