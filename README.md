# 🚖 CLI-Based Taxi Booking System

A simple **command-line interface (CLI) application** built in **C** for taxi booking management as my **1st Semester Final Project In Programming Fundamentals Course**.  
The system allows **user registration, login, taxi booking, fare calculation, driver assignment, booking history**, and **phone number updates** using **file-based storage**.

---

## 📌 Project Overview
The Taxi Booking System provides a lightweight solution for booking taxis through the command line.  
It stores **user data, booking records, and driver details** in text files for persistent storage.

---

## ✨ Key Features
- **Signup & Login** – Users can create accounts and log in using their phone number and password.
- **Fare Calculation** – Fare is based on the selected vehicle type.
- **Pickup Points** – 16 different pickup points available.
- **Driver Assignment** – A driver is automatically assigned to each booking.
- **Booking Records** – Stores pickup, drop-off, distance, fare, and driver details.
- **Update Phone Number** – Updates across both user data and booking history.
- **Booking History** – Users can view all past bookings.

---

## 🏗️ System Design

### 1. User Management
- Signup with **name, phone number, and password**.  
- Login with **phone number & password validation**.  

### 2. Taxi Booking
- Choose **vehicle type, pickup, and drop-off points**.  
- Distance is calculated via a **distance matrix**.  
- A driver is auto-assigned.  

### 3. File Handling
- `users.txt` → stores user info.  
- `booking_records.txt` → stores booking details.  
- `drivers.txt` → stores driver list.  

### 4. Fare Calculation
- Each vehicle type has a **predefined fare rate**.  
- Fare = `distance × rate`.  

### 5. Distance Calculation
- Predefined **distance matrix** used for pickup & drop-off points.  

---

## ⚙️ Technical Specifications
- **Language:** C  
- **Libraries Used:**
  - `stdio.h` → input/output
  - `stdlib.h` → memory & system functions
  - `string.h` → string operations
  - `time.h` → timestamps (optional)  

- **Data Storage:**
  - `users.txt` → name, phone, password
  - `booking_records.txt` → booking history
  - `drivers.txt` → driver names  

---

## 🚦 User Flow

### 1. Signup
- Enter **name, phone number, and password**.  
- Duplicate phone numbers not allowed.  

### 2. Login
- Validate phone number and password.  
- On success → user accesses **main menu**.  

### 3. Book a Taxi
- Select **vehicle type, pickup point, drop-off point**.  
- System calculates **distance & fare**.  
- Assigns a driver and saves booking.  

### 4. View Booking History
- User can check **all past bookings**.  

### 5. Update Phone Number
- Updates across **user records & booking records**.  

---

## 🔧 Challenges Faced
- **File Handling** – Ensuring no corruption while updating files.  
- **Input Validation** – Phone number format, password security.  
- **User Experience** – Keeping CLI prompts clear and user-friendly.  

---

## 🚀 Future Enhancements
- Driver availability system (busy/free tracking).  
- Dynamic pricing (based on time & demand).  
- Better CLI interface (color coding for errors/success).  
- Password hashing for improved security.  

---

## ✅ Conclusion
This project demonstrates how a **CLI-based system** can manage a **taxi booking workflow** with:
- **User authentication**
- **Booking management**
- **File storage system**

It provides a solid foundation for real-world taxi booking scenarios, with room for **future enhancements**.

