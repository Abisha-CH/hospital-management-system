#define _CRT_SECURE_NO_WARNINGS
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define YELLOW "\x1b[33m"
#define CYAN "\x1b[36m"
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Function declarations
// ROLES
void admin();
void doctor();
void patient();
// CREDITS
void showCredits();
// @ ADMIN
void addPatient();
void viewAllPatients(); 
void editPatient();     
void deletePatient();
void addDoctor();
void viewAllDoctors();  
void editDoctor();      
void deleteDoctor();
// GENERAL
void changePassword();
void registerUser();
// @ DOCTOR
void patientEnquiry();
void makePatReport();
void viewDocDetails(int index);
void modifyDocDetails();
// FILE HANDLING
void saveData();
void loadData();
// Global variables
char n[50];
int attempt, choiceA, ageP[200], patientCount = 0, doctorCount = 0, ageD[200], docExp[200], maxP = 200, currIndex, id;
// Authentication Data
char authUsername[100][50];
char authPassword[100][50];
int authRole[100]; // 1=Admin, 2=Doctor, 3=Patient
int authCount = 0;
int currentUserIndex = -1;

char nameP[200][50], diseaseP[200][50], genderP[200][50], more, specialization[200][50], nameD[200][50], genderD[200][50];
// Report Data per Patient
char diag[200][100], pres[200][100], note[200][200], followUp[200][50];

int main() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  char name[50], password[50];
  int role, attempts = 0, mainChoice;
  loadData(); // Load data at startup
  // printf(BLUE);
  SetConsoleTextAttribute(hConsole, 3);
  printf("                                   _________                         "
         "           \n");
  printf("                                  |  _   _  |                        "
         "           \n");
  printf("                                  | | | | | |                        "
         "           \n");
  printf("                                  | |_| |_| |                        "
         "           \n");
  printf("                                  |  _   _  |                        "
         "           \n");
  printf("                                  | | | | | |                        "
         "           \n");
  printf("                                  | |_| |_| |                        "
         "           \n");
  printf("                                  |    +    |                        "
         "           \n");
  printf("                                  |    +    |                        "
         "           \n");
  printf("                                  |  +++++  |                        "
         "           \n");
  printf("                                  |    +    |                        "
         "           \n");
  printf("                              ____|____+____|___                     "
         "           \n");
  printf("                             |                  |                    "
         "           \n");
  printf("                             |   @ HOSPITAL @   |                    "
         "           \n");
  printf("                             |__________________|                    "
         "           \n");
  printf(RESET);

  printf("*********************************************************************"
         "**************\n\n");
  printf("| " CYAN BOLD "                       HOSPITAL MANAGEMENT SYSTEM     "
         "                          " RESET "|\n\n");
  printf("---------------------------------------------------------------------"
         "--------------\n\n");
  printf(BOLD "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN MENU "
              "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" RESET);
  printf("*********************************************************************"
         "**************\n\n");

  do {
    printf(BOLD "\tENTER YOUR CHOICE:\n" RESET);
    printf(GREEN "\t1. LOGIN\n" RESET);
    printf(BLUE "\t2. REGISTER\n" RESET);
    printf(RED "\t3. EXIT\n" RESET);
    printf("\n\tENTER HERE :");

    if (scanf("%d", &mainChoice) != 1) {
      while (getchar() != '\n');
      mainChoice = -1;
    }

    if (mainChoice == 1) {
      // --- SUB MENU: LOGIN AS ---
      printf(BOLD "\n\t--- LOGIN AS ---\n" RESET);
      printf(GREEN "\t1. RECEPTIONIST\n" RESET);
      printf(YELLOW "\t2. DOCTOR\n" RESET);
      printf("\t3. PATIENT\n");
      printf(RED "\t4. BACK\n" RESET);
      printf("\n\tENTER ROLE :");

      if (scanf("%d", &role) != 1) {
        while (getchar() != '\n');
        role = -1;
      }

      if (role == 4)
        continue; // Go back to main menu

      // AUTHENTICATION LOGIC
      if (role == 1 || role == 2 || role == 3) {
        char username[50], password[50];
        int loginSuccess = 0;
        for (int i = 0; i < 3; i++) {
          printf("\tEnter username: ");
          scanf("%49s", username);
          printf("\tEnter password: ");
          scanf("%49s", password);

          // CHECK CREDENTIALS
          for (int j = 0; j < authCount; j++) {
            if (strcmp(authUsername[j], username) == 0 &&
                strcmp(authPassword[j], password) == 0 && authRole[j] == role) {
              currentUserIndex = j;
              loginSuccess = 1;
              break;
            }
          }

          if (loginSuccess) {
            printf(GREEN BOLD "\n\t\tLOGIN SUCCESSFUL  \n" RESET);
            if (role == 1)
              admin();
            else if (role == 2)
              doctor();
            else if (role == 3)
              patient();
            break;
          } else {
            printf(YELLOW "\n\t\tINCORRECT USERNAME, PASSWORD, OR ROLE   TRY "
                          "AGAIN  : \n" RESET);
          }
        }
        if (!loginSuccess) {
          printf(RED BOLD "\n\t\t   TRIED MANY TIMES \n" RESET);
          showCredits();
          return 0;
        }
      } else {
        printf(YELLOW "\n\t\tINVALID ROLE  \n" RESET);
      }

    } else if (mainChoice == 2) {
      registerUser();
    } else if (mainChoice == 3) {
      printf(RED BOLD "\n\t\t........................EXITING FROM THE SYSTEM "
                      "..........................\n" RESET);
      showCredits();
      return 0;
    } else {
      printf(YELLOW "\n\t\tINVALID CHOICE   TRY AGAIN\n" RESET);
      attempts++; // Count main menu failures?
    }
  } while (attempts < 3);

  if (attempts >= 3) {
    printf(RED BOLD "\n\t\t        TRIED MANY TIMES      \n" RESET);
  }
  showCredits();
  return 0;
}
void admin() {
  int exitAdmin = 0;
  while (!exitAdmin) {
    printf(BLUE BOLD "\n\tChoose (1-10):\n" RESET);
    printf("\t1. Add Patient Record\n");
    printf("\t2. View All Patients\n");
    printf("\t3. Edit Patient Record\n");
    printf("\t4. Delete Patient Record\n");
    printf("\t------------------------\n");
    printf("\t5. Add Doctor Record\n");
    printf("\t6. View All Doctors\n");
    printf("\t7. Edit Doctor Record\n");
    printf("\t8. Delete Doctor Record\n");
    printf("\t------------------------\n");
    printf("\t9. Change Password\n");
    printf("\t10. Exit\n");
    printf("\n\tEnter your choice:");
    if (scanf("%d", &choiceA) != 1) {
      while (getchar() != '\n');
      choiceA = -1;
    }
    switch (choiceA) {
    case 1:
      addPatient();
      break;
    case 2:
      viewAllPatients();
      break;
    case 3:
      editPatient();
      break;
    case 4:
      deletePatient();
      break;
    case 5:
      addDoctor();
      break;
    case 6:
      viewAllDoctors();
      break;
    case 7:
      editDoctor();
      break;
    case 8:
      deleteDoctor();
      break;
    case 9:
      changePassword();
      break;
    case 10:
      printf(CYAN BOLD
             "\n\t\t............EXITING ADMIN PANEL..........\n" RESET);
      saveData();
      return;
    default:
      printf(YELLOW "\n\t\tInvalid Choice   ..... Enter Again :  \n" RESET);
      break;
    }
  }
}
void doctor() {
  int exitDoctor = 0;
  while (!exitDoctor) {
    printf(BOLD "\n\tChoose (1-6):\n" RESET);
    printf("\t1. View All Patients\n");
    printf("\t2. Patient Enquiry\n");
    printf("\t3. Make Patient Report\n");
    printf("\t4. View Doctor Details\n");
    printf("\t5. Password change\n");
    printf("\t6. Exit\n");
    printf("\n\tEnter your choice:");
    if (scanf("%d", &choiceA) != 1) {
      while (getchar() != '\n');
      choiceA = -1;
    }
    switch (choiceA) {
    case 1:
      viewAllPatients();
      break;
    case 2:
      patientEnquiry();
      break;
    case 3:
      makePatReport();
      break;
    case 4:
      viewDocDetails(currIndex);
      break;
    case 5:
      changePassword();
      break;
    case 6:
      printf(CYAN BOLD "\n\t\t........................EXITING DOCTOR "
                       "PANEL..........................\n" RESET);
      return;
    default:
      printf(YELLOW "\n\t\tInvalid Choice   ..... Enter Again :  \n" RESET);
      break;
    }
  }
}

void patient() {
  printf("\n\tYou can see your report here");
  printf("\n\tEnter your ID:");
  scanf("%d", &id);
  if (id <= 0 || id > maxP) {
    printf(YELLOW BOLD " \n\t......... Invalid Patient ID   ..... \n" RESET);
    return;
  }
  currIndex = id - 1;
  printf("\n\tPatient ID : %d", id);
  printf("\n\tPatient Name : %s", nameP[currIndex]);
  printf("\n\tPatient Age : %d", ageP[currIndex]);
  printf("\n\tPatient Gender : %s",genderP[currIndex]);  
  printf("\n\tDiagnosis : %s", diag[currIndex]);
  printf("\n\tPrescription  : %s", pres[currIndex]);
  printf("\n\tDoctor's Notes  : %s", note[currIndex]);
  printf("\n\tFollow Up Date : %s\n", followUp[currIndex]);
  return;
}

void makePatReport() {
  int age;
  printf(BLUE BOLD
         " \n\t @@@@@@@@@------ CREATE PATIENT REPORT ------@@@@@@@@@ " RESET);
  printf("\n\tEnter Patient ID : ");
  scanf("%d", &id);
  if (id <= 0 || id > maxP) {
    printf(YELLOW BOLD " \n\t......... Invalid Patient ID   ..... \n" RESET);
    return;
  }
  getchar();
  currIndex = id - 1;
  printf(CYAN BOLD
         "\n\t @@@@@@@@@-------- PATIENT DETAILS --------@@@@@@@@@\n\n" RESET);
  printf("\tName   : %s\n", nameP[currIndex]);
  printf("\tAge    : %d\n", ageP[currIndex]);
  printf("\tGender : %s\n", genderP[currIndex]);
  printf("\tDisease: %s\n", diseaseP[currIndex]);
  printf("\n\tEnter Diagnosis: ");
  fgets(diag[currIndex], sizeof(diag[0]), stdin);
  diag[currIndex][strcspn(diag[currIndex], "\n")] = '\0';
  printf("\tEnter Prescription : ");
  fgets(pres[currIndex], sizeof(pres[0]), stdin);
  pres[currIndex][strcspn(pres[currIndex], "\n")] = '\0';
  printf("\tEnter Doctor's Notes : ");
  fgets(note[currIndex], sizeof(note[0]), stdin);
  note[currIndex][strcspn(note[currIndex], "\n")] = '\0';
  printf("\tEnter Follow Up Date (DD/MM/YYYY): ");
  fgets(followUp[currIndex], sizeof(followUp[0]), stdin);
  followUp[currIndex][strcspn(followUp[currIndex], "\n")] = '\0';
  printf("\t-------------------------------------------------------------------"
         "---------------");
  printf("\n\t-----------------------------------------------------------------"
         "-----------------");
  printf("\n\tPatient ID : %d", id);
  printf("\n\tPatient Name : %s", nameP[currIndex]);
  printf("\n\tPatient Age : %d", ageP[currIndex]);
  printf("\n\tPatient Gender : %s", genderP[currIndex]);  
  printf("\n\tDiagnosis : %s", diag[currIndex]);
  printf("\n\tPrescription  : %s", pres[currIndex]);
  printf("\n\tDoctor's Notes  : %s", note[currIndex]);
  printf("\n\tFollow Up Date : %s", followUp[currIndex]);
  printf("\n\t-----------------------------------------------------------------"
         "-----------------");
  printf("\n\t-----------------------------------------------------------------"
         "-----------------");
  printf(GREEN BOLD "\n\tPATIENT REPORT MADE SUCCESSFULLY  \n" RESET);
  saveData(); // Save report
}
void viewDocDetails(int unused_index) {
  printf("---------------------------------------------------------------------"
         "---------------------\n");
  printf("\n-------------------------------------------------------------------"
         "-----------------------\n");
  printf(BLUE BOLD
         "\t @@@@@@@@@@@@@@ DOCTOR'S DETAILS @@@@@@@@@@@@@@@  \n" RESET);
  if (doctorCount == 0) {
    printf(RED "\n\t........No doctor records found..........\n" RESET);
    return;
  }
  for (int i = 0; i < doctorCount; i++) {
    printf(RED "-----------------------------------------\n" RESET);
    printf("\n\tDoctor's ID : %d\n", i + 1);
    printf("Doctor Name  : %s\n", nameD[i]);
    printf("Doctor Age   : %d\n", ageD[i]);
    printf("Doctor Gender  : %s\n", genderD[i]);
    printf("Doctor Specialization  : %s\n", specialization[i]);
    printf("Years of Experience : %d  years\n", docExp[i]);
    printf(RED "-----------------------------------------\n" RESET);
  }
  printf("---------------------------------------------------------------------"
         "---------------------\n");
  printf("---------------------------------------------------------------------"
         "---------------------\n");
}

void patientEnquiry() {
  int pID;
  printf("\tEnter patient ID: ");
  scanf("%d", &pID);

  if (pID <= 0 || pID > maxP) {
    printf(YELLOW BOLD " \n\t......... Invalid Patient ID   ..... \n" RESET);
    return;
  }

  int index = pID - 1;
  printf(BLUE BOLD
         "\n\t @@@@@@@@@-------- PATIENT DETAILS --------@@@@@@@@@\n\n" RESET);
  printf("\tName  : %s\n", nameP[index]);
  printf("\tAge   : %d\n", ageP[index]);
  printf("\tGender: %s\n", genderP[index]);
  printf("\tHistory: %s\n", diseaseP[index]);

  char symptoms[100], diagnosis[100];
  int medCount = 0, testCount = 0;
  char test[10][50], med[10][50];

  getchar();
  printf("\tEnter Symptoms: ");
  fgets(symptoms, sizeof(symptoms), stdin);
  symptoms[strcspn(symptoms, "\n")] = '\0';

  printf("\tEnter Diagnosis: ");
  fgets(diagnosis, sizeof(diagnosis), stdin);
  diagnosis[strcspn(diagnosis, "\n")] = '\0';

  printf("\tEnter No. of Medicines to prescribe: ");
  if (scanf("%d", &medCount) != 1) {
    medCount = 0;
    while (getchar() != '\n')
      ;
  } else {
    getchar();  
  }

  for (int i = 0; i < medCount; i++) {
    printf("\tEnter Medicine %d Name: ", i + 1);
    fgets(med[i], sizeof(med[i]), stdin);
    med[i][strcspn(med[i], "\n")] = '\0';
  }

  printf("\tEnter No. of Medical Tests to prescribe: ");
  if (scanf("%d", &testCount) != 1) {
    testCount = 0;
    while (getchar() != '\n')
      ;
  } else {
    getchar();  
  }
  for (int i = 0; i < testCount; i++) {
    printf("\tEnter Medical Test %d Name: ", i + 1);
    fgets(test[i], sizeof(test[i]), stdin);
    test[i][strcspn(test[i], "\n")] = '\0';
  }

  printf(BLUE BOLD "\n\t----- Consultation Summary -----\n" RESET);
  printf("\tSymptoms: %s\n", symptoms);
  printf("\tDiagnosis: %s\n", diagnosis);
  printf("\tMedicines Prescribed: ");
  for (int i = 0; i < medCount; i++) {
    printf("%s%s", med[i], i < medCount - 1 ? ", " : "\n");
  }
  printf("\tMedical Tests Prescribed: ");
  for (int i = 0; i < testCount; i++) {
    printf("%s%s", test[i], i < testCount - 1 ? ", " : "\n");
  }
  printf(GREEN BOLD "\n\t@@@@@@ - CONSULTATION COMPLETED - @@@@@@\n" RESET);
}

void addPatient() {
  // NAME
  do {
    getchar();
    printf("\n\tEnter Patient's Name:");
    do {
      fgets(nameP[patientCount], sizeof(nameP[0]), stdin);
      nameP[patientCount][strcspn(nameP[patientCount], "\n")] = '\0';
      if (strcmp(nameP[patientCount], "") == 0) {
        printf(
            YELLOW
            " \n\t............. Invalid Patient Name   ......... \n" RESET);
        return;
      }

    } while (strcmp(nameP[patientCount], "") == 0 ||
             strcmp(nameP[patientCount], " ") == 0);

    // AGE
    printf("\tEnter Patient's age:");
    do {
      scanf("%d", &ageP[patientCount]);
      if (ageP[patientCount] <= 0) {
        printf(YELLOW " \n\t............. Invalid Patient Age    Try Again "
                      " ......... \n" RESET);
        return;
      }
    } while (getchar() != '\n');

    // DISEASE
    printf("\tEnter Patients disease:");
    do {
      fgets(diseaseP[patientCount], sizeof(diseaseP[0]), stdin);
      diseaseP[patientCount][strcspn(diseaseP[patientCount], "\n")] = '\0';
      if (strcmp(diseaseP[patientCount], "") == 0) {
        printf(YELLOW " \n\t............. Invalid Disease    Try Again "
                      " ......... \n" RESET);
      }
    } while (strcmp(diseaseP[patientCount], "") == 0 ||
             strcmp(diseaseP[patientCount], " ") == 0);

    // GENDER
    printf("\tEnter Your Gender  (Male/ Female / Other): ");
    do {
      fgets(genderP[patientCount], sizeof(genderP[0]), stdin);
      genderP[patientCount][strcspn(genderP[patientCount], "\n")] = '\0';

      if (!(strcmp(genderP[patientCount], "Female") == 0 ||
            strcmp(genderP[patientCount], "Male") == 0 ||
            strcmp(genderP[patientCount], "Other") == 0))

      {
        printf(YELLOW " \n\t............. Invalid Gender    Try Again "
                      " ......... \n" RESET);
      }
    } while (strcmp(genderP[patientCount], "") == 0 ||
             strcmp(genderP[patientCount], " ") == 0);

    printf(BLUE "\n\t [Added] ,Patient ID : %d , Name : %s , Age : %d  "
                "Disease: %s, Gender : %s" GREEN,
           patientCount + 1, nameP[patientCount], ageP[patientCount],
           diseaseP[patientCount], genderP[patientCount]);

    patientCount++;
    getchar();
    printf(BLUE "\n\t ..................Do you want to add more Patient?  [Y / "
                "N]........... " RESET);
    scanf(" %c", &more);
  } while (more == 'y' || more == 'Y');
  if (more == 'n' || more == 'N') {
    admin();
  }
  saveData(); // Save new patient
}

void addDoctor() {
  char more;
  do {
    // Clear leftover input
    while (getchar() != '\n');

    // NAME
    do {
      printf("\tEnter Doctor's Name: ");
      fgets(nameD[doctorCount], sizeof(nameD[0]), stdin);
      nameD[doctorCount][strcspn(nameD[doctorCount], "\n")] = '\0';

      if (strlen(nameD[doctorCount]) == 0 ||
          strcmp(nameD[doctorCount], " ") == 0) {
        printf(YELLOW " \n\t............. Invalid Doctor Name     Try Again "
                      " ......... \n" RESET);
      }
    } while (strlen(nameD[doctorCount]) == 0 ||
             strcmp(nameD[doctorCount], " ") == 0);

    // AGE
    do {
      printf("\tEnter Doctor's Age: ");
      if (scanf("%d", &ageD[doctorCount]) != 1 || ageD[doctorCount] <= 0) {
        printf(YELLOW " \n\t............. Invalid Doctor Age     Try Again "
                      " ......... \n" RESET);
        while (getchar() != '\n');
        ageD[doctorCount] = 0;
      } else {
        while (getchar() != '\n');
        break;
      }
    } while (ageD[doctorCount] <= 0);

    // SPECIALIZATION
    do {
      printf("\tEnter Doctor's Specialization: ");
      fgets(specialization[doctorCount], sizeof(specialization[0]), stdin);
      specialization[doctorCount][strcspn(specialization[doctorCount], "\n")] =
          '\0';

      if (strlen(specialization[doctorCount]) == 0 ||
          strcmp(specialization[doctorCount], " ") == 0) {
        printf(YELLOW " \n\t............. Invalid Specialization     Try "
                      "Again  ......... \n" RESET);
      }
    } while (strlen(specialization[doctorCount]) == 0 ||
             strcmp(specialization[doctorCount], " ") == 0);

    // GENDER
    do {
      printf("\tEnter Gender (Male / Female / Other): ");
      fgets(genderD[doctorCount], sizeof(genderD[0]), stdin);
      genderD[doctorCount][strcspn(genderD[doctorCount], "\n")] = '\0';

      if (strcmp(genderD[doctorCount], "Male") != 0 &&
          strcmp(genderD[doctorCount], "Female") != 0 &&
          strcmp(genderD[doctorCount], "Other") != 0) {
        printf(YELLOW " \n\t............. Invalid Gender     Try Again "
                      " ......... \n" RESET);
      }
    } while (strcmp(genderD[doctorCount], "Male") != 0 &&
             strcmp(genderD[doctorCount], "Female") != 0 &&
             strcmp(genderD[doctorCount], "Other") != 0);

    // EXPERIENCE
    do {
      printf("\tEnter Years of Experience: ");
      if (scanf("%d", &docExp[doctorCount]) != 1 || docExp[doctorCount] <= 0) {
        printf(YELLOW " \n\t............. Invalid Years of Experience Added  "
                      "   Try Again  ......... \n" RESET);
        while (getchar() != '\n');
        docExp[doctorCount] = 0;
      } else {
        while (getchar() != '\n');
        break;
      }
    } while (docExp[doctorCount] <= 0);
    printf(GREEN "\n\t [Added] Doctor ID: %d, Name: %s, Age: %d, "
                 "Specialization: %s, Gender: %s, Experience: %d\n" RESET,
           doctorCount + 1, nameD[doctorCount], ageD[doctorCount],
           specialization[doctorCount], genderD[doctorCount],
           docExp[doctorCount]);

    doctorCount++;

    do {
      printf(BLUE "\n\t Do you want to add more doctors? [Y/N]: " RESET);
      scanf(" %c", &more);
      while (getchar() != '\n')
        ;
      if (more != 'Y' && more != 'y' && more != 'N' && more != 'n') {
        printf(YELLOW " \n\t............. Invalid Input     Try Again "
                      " ......... \n" RESET);
      }
    } while (more != 'Y' && more != 'y' && more != 'N' && more != 'n');

  } while (more == 'Y' || more == 'y');

  if (more == 'N' || more == 'n') {
    saveData(); // Save new doctor
    return;
  }
}

void deletePatient() {
  int id;
  printf("\tEnter patient ID:");
  scanf("%d", &id);

  if (id <= 0 || id > patientCount) {
    printf(YELLOW
           " \n\t............. Invalid Patient ID   ......... \n" RESET);
    return;
  }

  for (int i = id - 1; i < patientCount - 1; i++) {
    strcpy(nameP[i], nameP[i + 1]);
    ageP[i] = ageP[i + 1];
    strcpy(diseaseP[i], diseaseP[i + 1]);
    strcpy(genderP[i], genderP[i + 1]);
  }
  patientCount--;
  printf(GREEN BOLD "\t..................RECORD DELETED SUCCESSFULLY   "
                    " ..................\n" RESET);
  saveData(); // Save deletion
}

void deleteDoctor() {
  int id;
  printf("\tEnter Doctor ID:");
  scanf("%d", &id);

  if (id <= 0 || id > doctorCount) {
    printf(YELLOW
           " \n\t............. INVALID DOCTOR ID   ......... \n" RESET);
    return;
  }

  for (int i = id - 1; i < doctorCount - 1; i++) {
    strcpy(nameD[i], nameD[i + 1]);
    ageD[i] = ageD[i + 1];
    strcpy(specialization[i], specialization[i + 1]);
    docExp[i] = docExp[i + 1];
    strcpy(genderD[i], genderD[i + 1]);  
  }
  doctorCount--;
  printf(GREEN BOLD "\t..................RECORD DELETED SUCCESSFULLY   "
                    " ..................\n" RESET);
  saveData(); // Save deletion
}

void changePassword() {
  char oldPassword[50], newPassword[50];
  int passCount = 0;

  do {
    printf("\tEnter previous password:");
    scanf("%49s", oldPassword);

    if (strcmp(oldPassword, authPassword[currentUserIndex]) == 0) {
      printf("\tEnter new password:");
      scanf("%49s", newPassword);

      strcpy(authPassword[currentUserIndex], newPassword);
      saveData();

      printf(CYAN BOLD
             "\tPassword updated   .......Your new password is %s" RESET,
             newPassword);
      return;
    } else {
      printf(YELLOW "\n\t\tInvalid Password   ..... Enter Again :  \n" RESET);
      passCount++;
    }

    if (passCount == 1) {
      printf(YELLOW "\t     You have 2 more chances to enter correct "
                    "password    \n\n" RESET);
    }
    if (passCount == 3) {
      printf(RED "\n\t\t        TRIED MANY TIMES      \n" RESET);
    }
  } while (passCount < 3);
}
void showCredits() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  printf(CYAN BOLD
         "\n\n\t\t================= CREDITS ==================\n" RESET);
  printf("\t\tHospital Management System\n");
  printf(GREEN "\t\tDeveloped by: ABISHA CH - KHANSA ZAEEM \n" RESET);
  SetConsoleTextAttribute(hConsole, 3);
  printf("\t\tRoll No: BSEF24M007 - BSEF24M013  \n");
  SetConsoleTextAttribute(hConsole, 5);
  printf("\t\tClass: B.S SOFTWARE ENGINEERING\n");
  printf(YELLOW "\t\tSpecial thanks to: SIR ANZAR, TA'S \n" RESET);
  printf("\t\t================================================\n\n");
  exit(0);
}

void saveData() {
  FILE *fp;

  // PATIENTS
  fp = fopen("patients.txt", "w");
  if (fp) {
    fprintf(fp, "Count: %d\n", patientCount);
    for (int i = 0; i < patientCount; i++) {
      fprintf(fp, "--------------------------------------------------\n");
      fprintf(fp, "Patient ID : %d\n", i + 1);
      fprintf(fp, "Name : %s\n", nameP[i]);
      fprintf(fp, "Age : %d\n", ageP[i]);
      fprintf(fp, "Gender : %s\n", genderP[i]);
      fprintf(fp, "Disease : %s\n", diseaseP[i]);
      fprintf(fp, "Diagnosis : %s\n", diag[i][0] ? diag[i] : "None");
      fprintf(fp, "Prescription : %s\n", pres[i][0] ? pres[i] : "None");
      fprintf(fp, "Notes : %s\n", note[i][0] ? note[i] : "None");
      fprintf(fp, "FollowUp : %s\n", followUp[i][0] ? followUp[i] : "None");
    }
    fclose(fp);
  }

  // DOCTORS
  fp = fopen("doctors.txt", "w");
  if (fp) {
    fprintf(fp, "Count: %d\n", doctorCount);
    for (int i = 0; i < doctorCount; i++) {
      fprintf(fp, "--------------------------------------------------\n");
      fprintf(fp, "Doctor ID : %d\n", i + 1);
      fprintf(fp, "Name : %s\n", nameD[i]);
      fprintf(fp, "Age : %d\n", ageD[i]);
      fprintf(fp, "Gender : %s\n", genderD[i]);
      fprintf(fp, "Specialization : %s\n", specialization[i]);
      fprintf(fp, "Experience : %d\n", docExp[i]);
    }
    fclose(fp);
  }
  fp = fopen("users.txt", "w");
  if (fp) {
    fprintf(fp, "Count: %d\n", authCount);
    for (int i = 0; i < authCount; i++) {
      fprintf(fp, "--------------------------------------------------\n");
      fprintf(fp, "Username : %s\n", authUsername[i]);
      fprintf(fp, "Password : %s\n", authPassword[i]);
      fprintf(fp, "Role : %d\n", authRole[i]);
    }
    fclose(fp);
  }
}

void loadData() {
  FILE *fp;
  char buffer[256];
  int tempID;
  fp = fopen("users.txt", "r");
  if (fp) {
    if (fscanf(fp, "Count: %d\n", &authCount) == 1) {
      for (int i = 0; i < authCount; i++) {
        fgets(buffer, sizeof(buffer), fp);  
        fscanf(fp, "Username : ");
        fgets(authUsername[i], sizeof(authUsername[i]), fp);
        authUsername[i][strcspn(authUsername[i], "\n")] = 0;

        fscanf(fp, "Password : ");
        fgets(authPassword[i], sizeof(authPassword[i]), fp);
        authPassword[i][strcspn(authPassword[i], "\n")] = 0;

        fscanf(fp, "Role : %d\n", &authRole[i]);
      }
    }
    fclose(fp);
  } else {
    // Defaults if no file exists
    authCount = 3;
    strcpy(authUsername[0], "admin");
    strcpy(authPassword[0], "1234");
    authRole[0] = 1;
    strcpy(authUsername[1], "doctor");
    strcpy(authPassword[1], "1234");
    authRole[1] = 2;
    strcpy(authUsername[2], "patient");
    strcpy(authPassword[2], "1234");
    authRole[2] = 3;
    saveData();
  }

  // Load Patients
  fp = fopen("patients.txt", "r");
  if (fp) {
    if (fscanf(fp, "Count: %d\n", &patientCount) == 1) {
      for (int i = 0; i < patientCount; i++) {
        fgets(buffer, sizeof(buffer), fp);  
        fscanf(fp, "Patient ID : %d\n", &tempID);

        fscanf(fp, "Name : ");
        fgets(nameP[i], sizeof(nameP[i]), fp);
        nameP[i][strcspn(nameP[i], "\n")] = 0;

        fscanf(fp, "Age : %d\n", &ageP[i]);

        fscanf(fp, "Gender : ");
        fgets(genderP[i], sizeof(genderP[i]), fp);
        genderP[i][strcspn(genderP[i], "\n")] = 0;

        fscanf(fp, "Disease : ");
        fgets(diseaseP[i], sizeof(diseaseP[i]), fp);
        diseaseP[i][strcspn(diseaseP[i], "\n")] = 0;

        fscanf(fp, "Diagnosis : ");
        fgets(diag[i], sizeof(diag[i]), fp);
        diag[i][strcspn(diag[i], "\n")] = 0;

        fscanf(fp, "Prescription : ");
        fgets(pres[i], sizeof(pres[i]), fp);
        pres[i][strcspn(pres[i], "\n")] = 0;

        fscanf(fp, "Notes : ");
        fgets(note[i], sizeof(note[i]), fp);
        note[i][strcspn(note[i], "\n")] = 0;

        fscanf(fp, "FollowUp : ");
        fgets(followUp[i], sizeof(followUp[i]), fp);
        followUp[i][strcspn(followUp[i], "\n")] = 0;
      }
    }
    fclose(fp);
  }

  // Load Doctors
  fp = fopen("doctors.txt", "r");
  if (fp) {
    if (fscanf(fp, "Count: %d\n", &doctorCount) == 1) {
      for (int i = 0; i < doctorCount; i++) {
        fgets(buffer, sizeof(buffer), fp);  
        fscanf(fp, "Doctor ID : %d\n", &tempID);

        fscanf(fp, "Name : ");
        fgets(nameD[i], sizeof(nameD[i]), fp);
        nameD[i][strcspn(nameD[i], "\n")] = 0;

        fscanf(fp, "Age : %d\n", &ageD[i]);

        fscanf(fp, "Gender : ");
        fgets(genderD[i], sizeof(genderD[i]), fp);
        genderD[i][strcspn(genderD[i], "\n")] = 0;

        fscanf(fp, "Specialization : ");
        fgets(specialization[i], sizeof(specialization[i]), fp);
        specialization[i][strcspn(specialization[i], "\n")] = 0;

        fscanf(fp, "Experience : %d\n", &docExp[i]);
      }
    }
    fclose(fp);
  }
}

void registerUser() {
  char username[50], password[50];
  int role;

  printf("\n\t---------------- REGISTER ----------------\n");
  printf("\tEnter Username: ");
  scanf("%49s", username);

  // Check if user exists
  for (int i = 0; i < authCount; i++) {
    if (strcmp(authUsername[i], username) == 0) {
      printf(YELLOW "\n\tUsername already exists! Try again.\n" RESET);
      return;
    }
  }

  printf("\tEnter Password: ");
  scanf("%49s", password);

  printf("\tSelect Role (1.Admin, 2.Doctor, 3.Patient): ");
  if (scanf("%d", &role) != 1 || role < 1 || role > 3) {
    printf(YELLOW "\n\tInvalid role! Registration failed.\n" RESET);
    while (getchar() != '\n')
      ;
    return;
  }

  strcpy(authUsername[authCount], username);
  strcpy(authPassword[authCount], password);
  authRole[authCount] = role;
  authCount++;

  saveData();
  printf(GREEN BOLD "\n\tRegistration Successful! You can now login.\n" RESET);
}

void viewAllPatients() {
  printf(BLUE BOLD "\n\t=========================== ALL PATIENTS "
                   "===========================\n" RESET);
  printf("\t%-5s %-20s %-5s %-10s %-15s\n", "ID", "Name", "Age", "Gender",
         "Disease");
  printf("\t-------------------------------------------------------------------"
         "-\n");
  for (int i = 0; i < patientCount; i++) {
    printf("\t%-5d %-20s %-5d %-10s %-15s\n", i + 1, nameP[i], ageP[i],
           genderP[i], diseaseP[i]);
  }
  printf(BLUE BOLD "\t========================================================="
                   "===========\n" RESET);
  printf("\n\tPress Enter to continue...");
  getchar();
  getchar();
}

void viewAllDoctors() {
  printf(BLUE BOLD "\n\t=========================== ALL DOCTORS "
                   "============================\n" RESET);
  printf("\t%-5s %-20s %-15s %-10s\n", "ID", "Name", "Specialization",
         "Experience");
  printf("\t-------------------------------------------------------------------"
         "-\n");
  for (int i = 0; i < doctorCount; i++) {
    printf("\t%-5d %-20s %-15s %d Years\n", i + 1, nameD[i], specialization[i],
           docExp[i]);
  }
  printf(BLUE BOLD "\t========================================================="
                   "===========\n" RESET);
  printf("\n\tPress Enter to continue...");
  getchar();
  getchar();
}

void editPatient() {
  int id;
  char buffer[100];

  printf("\n\tEnter Patient ID to edit: ");
  if (scanf("%d", &id) != 1) {
    while (getchar() != '\n')
      ;
    return;
  }

  if (id <= 0 || id > patientCount) {
    printf(YELLOW "\n\tInvalid Patient ID!\n" RESET);
    return;
  }

  int i = id - 1;
  getchar();  

  printf(BLUE BOLD "\n\t--- EDITING PATIENT: %s ---\n" RESET, nameP[i]);
  printf("\t(Press Enter to keep current value)\n");

  printf("\tName [%s]: ", nameP[i]);
  fgets(buffer, sizeof(buffer), stdin);
  if (strcmp(buffer, "\n") != 0) {
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(nameP[i], buffer);
  }

  printf("\tAge [%d]: ", ageP[i]);
  fgets(buffer, sizeof(buffer), stdin);
  if (strcmp(buffer, "\n") != 0) {
    ageP[i] = atoi(buffer);
  }

  printf("\tGender [%s]: ", genderP[i]);
  fgets(buffer, sizeof(buffer), stdin);
  if (strcmp(buffer, "\n") != 0) {
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(genderP[i], buffer);
  }

  printf("\tDisease [%s]: ", diseaseP[i]);
  fgets(buffer, sizeof(buffer), stdin);
  if (strcmp(buffer, "\n") != 0) {
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(diseaseP[i], buffer);
  }

  saveData();
  printf(GREEN BOLD "\n\tPatient details updated successfully!  \n" RESET);
}

void editDoctor() {
  int id;
  char buffer[100];

  printf("\n\tEnter Doctor ID to edit: ");
  if (scanf("%d", &id) != 1) {
    while (getchar() != '\n')
      ;
    return;
  }

  if (id <= 0 || id > doctorCount) {
    printf(YELLOW "\n\tInvalid Doctor ID!\n" RESET);
    return;
  }

  int i = id - 1;
  getchar();  

  printf(BLUE BOLD "\n\t--- EDITING DOCTOR: %s ---\n" RESET, nameD[i]);
  printf("\t(Press Enter to keep current value)\n");

  printf("\tName [%s]: ", nameD[i]);
  fgets(buffer, sizeof(buffer), stdin);
  if (strcmp(buffer, "\n") != 0) {
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(nameD[i], buffer);
  }

  printf("\tAge [%d]: ", ageD[i]);
  fgets(buffer, sizeof(buffer), stdin);
  if (strcmp(buffer, "\n") != 0) {
    ageD[i] = atoi(buffer);
  }

  printf("\tGender [%s]: ", genderD[i]);
  fgets(buffer, sizeof(buffer), stdin);
  if (strcmp(buffer, "\n") != 0) {
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(genderD[i], buffer);
  }

  printf("\tSpecialization [%s]: ", specialization[i]);
  fgets(buffer, sizeof(buffer), stdin);
  if (strcmp(buffer, "\n") != 0) {
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(specialization[i], buffer);
  }

  printf("\tExperience [%d]: ", docExp[i]);
  fgets(buffer, sizeof(buffer), stdin);
  if (strcmp(buffer, "\n") != 0) {
    docExp[i] = atoi(buffer);
  }

  saveData();
  printf(GREEN BOLD "\n\tDoctor details updated successfully!  \n" RESET);
}
