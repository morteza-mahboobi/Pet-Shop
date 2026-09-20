# 🐾 Pet Shop Backend (Terminal-Based)

## 📌 About the Project

A **Terminal-Based Pet Shop Backend** developed as a university project.

This project combines a backend implementation with a responsive **Terminal User Interface (TUI)**. While its primary focus is backend development, it also includes a custom terminal-based frontend featuring interactive menus, animations, keyboard navigation, and responsive layouts that adapt to the current console size.

The application simulates a complete pet shop management system with user management, products, wallets, transactions, and an interactive terminal interface.

---

## 🚀 Installation and Running

### Easy Version (Pre-built)

1. Download the complete project folder.
2. Run `program.exe` to start the application.
3. To view all transactions, run `Show All Trans.exe` located in the `some tools` folder.

### Advanced Version (Build from Source)

1. Download the complete project folder.
2. Build `program.cpp` to compile the application with these command.
```shell   
g++ -c main.cpp
g++ -c headers\graphic_utilities.cpp -o headers\graphic_utilities.o
g++ -c headers\myClass.cpp -o headers\myClass.o
g++ main.o headers\graphic_utilities.o headers\myClass.o -o program.exe
```
3. Run the generated `program.exe` file.
4. To view all transactions:
   - Build `Show All Trans.cpp` located in the `some tools` folder.
   - Run the generated `Show All Trans.exe` file.

---

## Project Structure

```text
project/
├── main.cpp
│   └── Program entry point
│
├── some tools/
│   ├── get Width & height.cpp
│   │   └── A utility program to get console width and height,
│   │       used for responsive console UI design
│   │
│   └── Show All Trans.cpp
│       └── A testing tool to display all transactions
│           for debugging and verification
│
├── headers/
│   ├── graphic_utilities.hpp
│   │   └── Declaration of console graphic utilities
│   │
│   ├── graphic_utilities.cpp
│   │   └── Implementation of console graphic utilities
│   │
│   ├── myClass.hpp
│   │   └── Declaration of main project classes
│   │
│   ├── myClass.cpp
│   │   └── Implementation of main project classes
│   │
│   ├── myException.hpp
│   │   └── Custom exception definitions
│   │
│   └── printEnum.hpp
│       └── Utilities for printing and handling enum values
│
└── file/
    └── Stores program data
    │
    ├── ids.dat
    │   └── Stores the latest generated ID
    │
    ├── Pet.dat
    │   └── Stores registered pet information
    │
    ├── User.dat
    │   └── Stores registered user information
    │
    ├── Transaction.dat
    │   └── Stores transaction records
    │
    └── SavedAccount.dat
        └── Stores the last logged-in account information
```

---

## ✨ Features

- Interactive terminal interface
- Professional terminal graphics & animations
- Responsive layout based on the current console size (recommended in **Fullscreen** mode)
- Full keyboard navigation
  - ↑ ↓ ← →
  - Enter
  - Tab
  - Esc
- Comprehensive input validation
- Handles most common runtime and user input errors
- Permanent storage of:
  - Users
  - Products
  - Wallets
  - Transactions
  - Shopping history
  - Product ratings

---

## 👥 User Roles

- **Administrator (Admin)**
- **Seller**
- **Buyer**

---

## 🔧 Common Features

The following features are available for **Administrator**, **Seller**, and **Buyer**.

### Profile

- View profile
- Edit profile information

### Wallet

- Deposit
- Withdraw
- Transfer
- Transaction history

### Session

- **Logout**
  - Sign out without closing the application
- **Exit**
  - Close the application without logging out

---

## 👑 Administrator

### Products

- Show all products
- Approve pending products
- Delete products
- Apply discounts:
  - All products
  - Single product
  - Multiple selected products
  - Entire category

### Sales

- View complete sales history
- View sold product details

### Users

- View all users
- Edit user information
- Delete users
- Send gifts

### Account

- Delete account
  - User information
  - Wallet balance
  - Transactions

---

## 🛍 Seller

### Products

- View personal products
- Add products
  - The product is initially set to **Pending** status
- Edit products
  - Edited products become **Pending**
- Delete products

### Sales

- View sales history
- View sold product details

### Account

- Delete account
  - User information
  - Products
  - Wallet balance
  - Transactions

---

## 🛒 Buyer

### Products

- View approved products
- Purchase products
- Rate products after purchase
- Advanced product search

### Shopping

- View shopping history
- View purchased product details

### Account

- Delete account
  - User information
  - Wallet balance
  - Transactions

---

## 🧪 Multiple accounts for testing the project

| Type | Username | Password | Name |
|------|----------|----------|------|
| Admin | amir.hosseini | Amir@2026 | Amir Hosseini |
| Seller | ali.moradi | Ali@2026 | Ali Moradi |
| Seller | sina.rahimi | Sina@2026 | Sina Rahimi |
| Buyer | Buyer | Buyer | Main Buyer |

> Additional user accounts can be viewed from the **Admin Panel**.

---

## 📌 معرفی پروژه

این پروژه یک **بک‌اند فروشگاه حیوانات خانگی** با **رابط کاربری مبتنی بر ترمینال (TUI)** است که به عنوان یک پروژه دانشگاهی توسعه داده شده است.

اگرچه تمرکز اصلی پروژه بر توسعه بک‌اند بوده، اما علاوه بر پیاده‌سازی کامل منطق برنامه، یک رابط کاربری مبتنی بر ترمینال نیز برای آن طراحی و پیاده‌سازی شده است. این رابط کاربری شامل منوهای تعاملی، انیمیشن، کنترل کامل با صفحه‌کلید و نمایش واکنش‌گرا نسبت به اندازه پنجره کنسول است و تجربه‌ای شبیه به یک فرانت‌اند را در محیط ترمینال ارائه می‌دهد.

این پروژه یک سیستم کامل مدیریت فروشگاه حیوانات را با امکاناتی مانند مدیریت کاربران، محصولات، کیف پول، تراکنش‌ها و سایر قابلیت‌های موردنیاز شبیه‌سازی می‌کند.

---

## 🚀 نصب و اجرای پروژه

### نسخه آسان (نسخه آماده اجرا)

1. کل پوشه پروژه را دانلود کنید.
2. فایل `program.exe` را برای اجرای برنامه اجرا کنید.
3. برای مشاهده تمام تراکنش‌ها، فایل `Show All Trans.exe` موجود در پوشه `some tools` را اجرا کنید.

### نسخه حرفه‌ای‌تر (بیلد از سورس)

1. کل پوشه پروژه را دانلود کنید.
2. فایل `program.cpp` را به کمک این دستورات بسازید.
```shell   
g++ -c main.cpp
g++ -c headers\graphic_utilities.cpp -o headers\graphic_utilities.o
g++ -c headers\myClass.cpp -o headers\myClass.o
g++ main.o headers\graphic_utilities.o headers\myClass.o -o program.exe
```
3. فایل ساخته‌شده `program.exe` را اجرا کنید.
4. برای مشاهده تمام تراکنش‌ها:
   - فایل `Show All Trans.cpp` موجود در پوشه `some tools` را بیلد کنید.
   - فایل ساخته‌شده `Show All Trans.exe` را اجرا کنید.

---

## ساختار پروژه

```text
project/
├── main.cpp
│   └── نقطه شروع اجرای برنامه
│
├── some tools/
│   ├── get Width & height.cpp
│   │   └── یک ابزار کمکی برای دریافت طول و عرض کنسول،
│   │       جهت طراحی رابط کاربری واکنش‌گرا (Responsive)
│   │
│   └── Show All Trans.cpp
│       └── یک ابزار تست برای نمایش تمام تراکنش‌ها
│           جهت بررسی و دیباگ برنامه
│
├── headers/
│   ├── graphic_utilities.hpp
│   │   └── دکلریشن قابلیت‌ها و توابع گرافیکی کنسول
│   │
│   ├── graphic_utilities.cpp
│   │   └── پیاده‌سازی قابلیت‌ها و توابع گرافیکی کنسول
│   │
│   ├── myClass.hpp
│   │   └── دکلریشن کلاس‌های اصلی پروژه
│   │
│   ├── myClass.cpp
│   │   └── پیاده‌سازی کلاس‌های اصلی پروژه
│   │
│   ├── myException.hpp
│   │   └── تعریف Exception های اختصاصی پروژه
│   │
│   └── printEnum.hpp
│       └── ایجاد قابلیت چاپ و مدیریت مقادیر Enum
│
└── file/
    └── شامل اطلاعات ذخیره‌شده برنامه
    │
    ├── ids.dat
    │   └── ذخیره آخرین ID استفاده‌شده
    │
    ├── Pet.dat
    │   └── اطلاعات پت‌های ثبت‌شده
    │
    ├── User.dat
    │   └── اطلاعات کاربران ثبت‌نام‌شده
    │
    ├── Transaction.dat
    │   └── اطلاعات تراکنش‌ها
    │
    └── SavedAccount.dat
        └── ذخیره آخرین اکانت واردشده به برنامه
```

---

## ✨ امکانات پروژه

- رابط کاربری تعاملی در ترمینال
- گرافیک و انیمیشن حرفه‌ای
- صفحه کاملاً **Responsive** نسبت به اندازه پنجره کنسول (پیشنهاد می‌شود در حالت **Fullscreen** اجرا شود)
- کنترل کامل با صفحه‌کلید
  - ↑ ↓ ← →
  - Enter
  - Tab
  - Esc
- اعتبارسنجی کامل ورودی‌ها
- مدیریت بیشتر خطاهای رایج برنامه و ورودی کاربران
- ذخیره دائمی:
  - کاربران
  - محصولات
  - کیف پول
  - تراکنش‌ها
  - تاریخچه خرید
  - امتیاز محصولات

---

## 👥 نقش‌های کاربری

- **مدیر (Admin)**
- **فروشنده (Seller)**
- **خریدار (Buyer)**

---

## 🔧 امکانات مشترک

امکانات زیر برای **مدیر**، **فروشنده** و **خریدار** مشترک هستند.

### پروفایل

- مشاهده پروفایل
- ویرایش اطلاعات

### کیف پول

- شارژ
- برداشت
- انتقال
- تاریخچه تراکنش‌ها

### نشست

- **لاگ اوت**
  - خروج از حساب بدون بستن برنامه
- **خروج**
  - بستن برنامه بدون خروج از حساب

---

## 👑 مدیر

### محصولات

- مشاهده همه محصولات
- تایید محصولات در انتظار بررسی
- حذف محصولات
- اعمال تخفیف:
  - روی همه محصولات
  - روی یک محصول
  - روی چند محصول
  - روی یک دسته‌بندی خاص

### فروش

- مشاهده تاریخچه همه فروش‌ها
- مشاهده اطلاعات محصولات فروخته‌شده

### کاربران

- مشاهده همه کاربران
- ویرایش اطلاعات
- حذف کاربران
- ارسال هدیه

### حساب کاربری

- حذف حساب همراه با:
  - اطلاعات کاربر
  - موجودی کیف پول
  - تراکنش‌ها

---

## 🛍 فروشنده

### محصولات

- مشاهده محصولات
- افزودن محصول
  - وضعیت محصول ابتدا به حالت **Pending** قرار می‌گیرد
- ویرایش محصول
  - وضعیت محصول به **Pending** تغییر می‌کند
- حذف محصول

### فروش

- مشاهده تاریخچه فروش
- مشاهده اطلاعات محصولات فروخته‌شده

### حساب کاربری

- حذف حساب همراه با:
  - اطلاعات کاربر
  - محصولات
  - موجودی کیف پول
  - تراکنش‌ها

---

## 🛒 خریدار

### محصولات

- مشاهده محصولات تاییدشده
- خرید محصول
- ثبت امتیاز پس از خرید
- جستجوی پیشرفته

### خریدها

- مشاهده تاریخچه خرید
- مشاهده اطلاعات محصولات خریداری‌شده

### حساب کاربری

- حذف حساب همراه با:
  - اطلاعات کاربر
  - موجودی کیف پول
  - تراکنش‌ها

---

## 🧪 چند اکانت برای تست پروژه

| نوع کاربری | نام کاربری | رمز عبور | نام |
|------------|------------|----------|-----|
| مدیر | amir.hosseini | Amir@2026 | Amir Hosseini |
| فروشنده | ali.moradi | Ali@2026 | Ali Moradi |
| فروشنده | sina.rahimi | Sina@2026 | Sina Rahimi |
| خریدار | Buyer | Buyer | Main Buyer |

> اطلاعات سایر کاربران را می‌توانید از طریق **پنل مدیر (Admin Panel)** مشاهده کرده و برای تست پروژه از آن‌ها استفاده کنید.