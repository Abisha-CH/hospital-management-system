# Hospital Management System 🏥

A robust, console-based Hospital Management System written in C. This project demonstrates core programming concepts including file handling, array manipulation, user authentication, and CRUD operations.

## 🚀 Features

### 🔐 User Authentication
- **Secure Login**: Role-based login for Admin, Doctor, and Patient.
- **Registration**: New users can sign up with a unique username and password.
- **Multi-User Support**: distinct accounts for multiple admins or doctors.
- **Password Management**: Users can securely change their own passwords.

### 👨‍💼 Admin Panel
- **Manage Patients**: Add, View All, Edit, and Delete patient records.
- **Manage Doctors**: Add, View All, Edit, and Delete doctor records.
- **full CRUD**: Complete Create, Read, Update, and Delete capabilities.

### 🩺 Doctor Panel
- **Patient Enquiry**: Search for patients by ID.
- **Medical Reports**: Create detailed reports including Diagnosis, Prescription, and Notes.
- **View All Patients**: Access a list of all registered patients.
- **My Profile**: View personal details and experience.

### 👤 Patient Panel
- **View Details**: Patients can view their own profile.
- **Medical History**: Access reports, prescriptions, and doctor's notes.

### 💾 Data Persistence
All data is automatically saved to text files, ensuring records remain safe even after the program closes.
- `patients.txt`: Stores patient demographics and medical reports.
- `doctors.txt`: Stores doctor profiles and specialization.
- `users.txt`: Stores login credentials and roles.

## 🛠️ Tech Stack
- **Language**: C
- **Compiler**: GCC
- **Platform**: Windows (uses `windows.h` for console styling)

## 🏃‍♂️ How to Run

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/Hospital-Management-System.git
    cd Hospital-Management-System
    ```

2.  **Compile the code**:
    You need a C compiler (like MinGW/GCC).
    ```bash
    gcc PF_PROJECT_SYSTEM.C -o hospital.exe
    ```

3.  **Run the application**:
    ```bash
    ./hospital.exe
    ```

## 📂 File Structure
- `PF_PROJECT_SYSTEM.C`: The main source code file.
- `users.txt`: Authenticated user credentials.
- `patients.txt`: Database of patient records.
- `doctors.txt`: Database of doctor records.

## 👥 Credits
**Developed by:**
- ABISHA CH (BSEF24M007)
- KHANSA ZAEEM (BSEF24M013)
 
**Class**: B.S Software Engineering
**Special Thanks**: Sir Anzar and TAs.
