# Magic Meal – Restaurant Management System (C)

**Magic Meal** is a console-based **Restaurant Management System** written in C for the **Programming Fundamentals** course project.  
It allows customers to register, log in, order meals, view their details, rate the restaurant, and even give suggestions — all from a terminal interface.

---

## Features
- **Customer Registration** – Stores customer details in a text file with validation (CNIC, phone, email, etc.)
- **Customer Login** – Reads customer data from file and loads profile.
- **Meal Ordering System**  
  - Breakfast, Lunch, and Dinner menus with special discounts.
  - Order multiple meals in one session.
  - Automatic bill calculation.
- **Billing & Payment**  
  - Cash on Delivery.
  - Online payment (opens in browser).
- **Rating & Suggestions** – Records ratings (1–10) and stores suggestions in a file.
- **View Customer Details** – Shows stored customer profile after login.
- **Social Media Link** – Opens restaurant's Facebook page.

---

## 🗂 Project Structure
magic_meal.c # Main source code
textfile.txt # Stores registered customers
ratings.txt # Stores ratings data
Suggestions.txt # Stores customer suggestions


---

## ⚙️ Requirements
- **Operating System**: Windows (due to `windows.h` and `system("color")`)
- **Compiler**: GCC (MinGW for Windows) or any C compiler supporting C99+
- **Files Needed**:  
  - `magic_meal.c` (source code)  
  - Empty `textfile.txt` (if not already created)  
  - Optional: `ratings.txt` and `Suggestions.txt` will be created automatically.

---

## 🚀 How to Run
1. **Compile**
   ```bash
   gcc magic_meal.c -o magic_meal.exe

0 → Exit Program
1 → Register as a new customer
2 → Login as a registered customer
3 → Order Meal
4 → View Customer Details

