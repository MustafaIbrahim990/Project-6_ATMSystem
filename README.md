"# Project-6 _ ATMSystem" 

# 🏧 Project-6: ATM System

## 👤 Author: Mustafa A. Ibrahim

This repository contains a **console-based Automated Teller Machine (ATM)** system developed in **C++**, designed to simulate essential banking operations such as withdrawals, deposits, and balance inquiries. The system stores and manages client data in a text file for persistent access across sessions.

---

## 📋 Overview

The ATM system allows users to:
- Log in using account credentials (Account Number & PIN)
- Perform transactions (quick withdraw, custom withdraw, deposit)
- Check account balances
- Log out securely

All client data — including **account numbers, PINs, names, phone numbers, and balances** — is saved in a plain text file (`ClientsData.txt`).

---

## 🧰 Technologies Used

- **Language:** C++
- **Libraries:**
  - `<iostream>` – Input/output
  - `<fstream>` – File operations
  - `<vector>` – Dynamic arrays
  - `<string>` – String handling

---

## 🚀 Features

- 💻 **Console Interface:** Simple, intuitive CLI experience
- 💾 **Data Persistence:** All client data is stored in `ClientsData.txt`
- 🔐 **User Authentication:** Secure login via Account Number and PIN
- 💸 **Quick Withdraw:** Predefined options ($20, $50, $100, etc.)
- 🏦 **Normal Withdraw:** Custom amounts (validated as multiples of 5, and within balance limits)
- ➕ **Deposit:** Add funds to account with validation
- 📊 **Check Balance:** View current balance
- ❌ **Logout:** Exit session and return to login
- ✅ **Input Validation:** Robust checks for inputs, balances, and format
- 🧩 **Modular Design:** Functions are well-structured and separated for clarity and maintenance

---

## 🛠️ Installation & Setup

### 1. Clone the Repository
```bash
git clone https://github.com/MustafaIbrahim990/Project-6_ATMSystem.git