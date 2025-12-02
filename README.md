                                                 🔐 TimeGuard Access Shield

                                 ⏳ Password-Controlled • Time-Restricted Machine Operation System

🧠 Project Overview

    TimeGuard Access Shield is an intelligent access-controlled machine operation system that only allows device usage during authorized working hours and by authenticated users.
    By integrating RTC time tracking, password authentication, and interrupt-based configuration,   this project enhances security, prevents misuse, and ensures safe automation in 
    controlled environments.

🎯 AIM

    To design a secure embedded system that grants machine access only to authorized users and only within pre-defined valid time intervals.

⭐ Key Objectives

    🔸 Display real-time clock (Date + Time) on LCD
    
    🔸 User authentication through secure password input
    
    🔸 Store configurable working hours in variables
    
    🔸 Allow password and timing modification through external interrupt
    
    🔸 Automatically enable/disable device based on authorized time window


![image alt](https://github.com/ThummaRahul/Vector_Mini_Project_V25He2T5/blob/main/main/1.png?raw=true)


🔥 Features at a Glance

🚀 Feature	

    📝 Description
    
    ⏱ Real-time RTC Display	Continuously shows updated time & date
          
    🔐 Password Authentication	Prevents unauthorized access
          
    🕒 Time-Restricted Operation	Machine runs only inside allowed window
          
    🎛 Interrupt-Based Menu	Allows live modifications anytime
          
    🔄 Editable RTC + Password + Time	Fully configurable through keypad
          
    ⚡ Device Control Output	Relay/LED toggles based on access status

📌 Working Flow

        
    1️⃣ Power ON → Modules initialize (LCD, Keypad, RTC, I/O)
            
    2️⃣ LCD shows real-time clock continuously 🕒
            
    3️⃣ User requests entry → Enters password via keypad ⌨
            
    4️⃣ System checks validity ✔
            
            ◾ If Valid + Within Time → Device ON ⚡
              
            ◾ Else → Access DENIED ❌
              
     5️⃣ External interrupt 🔘 opens configuration menu
            
            ➤ Edit RTC Time
            
            ➤ Change Device Operational Hours
            
            ➤ Change Password
            
            ➤ Exit


🧾 Configuration Menu (on interrupt)

    1. E.RTCINFO      3. PWD CHG
    2. E.DEV.A.TIME   4. EXIT


![image alt](https://github.com/ThummaRahul/Vector_Mini_Project_V25He2T5/blob/main/main/2.png?raw=true)



⏳ RTC Edit Options

    1. Hour   2. Minute  3. Second  4. Day
    5. Date   6. Month   7. Year    8. Exit


🛠 Hardware Requirements


      🔹 LPC2148 ARM7 MCU
      
      🔹 16x2 LCD Display
      
      🔹 4x4 Matrix Keypad
      
      🔹 RTC + Backup Cell
      
      🔹 LED
      
      🔹 Interrupt Push Switch
      


💻 Software Requirements


    🛠 Embedded-C
    
    🛠 Keil µVision
    
    🛠 Flash Magic


📌 Conclusion


       The TimeGuard Access Shield provides a secure and reliable solution for controlling machine operation using password authentication and RTC-based time restrictions. By integrating real-time monitoring, programmable working-hour limits, and    an interrupt-driven configuration menu, the system ensures that only authorized users can operate the device and only during permitted hours. This enhances safety, prevents unauthorized usage, and supports disciplined machine management in     laboratories, workshops, and industrial environments. With flexible editing options for RTC, password, and device timing, the system offers both usability and strong access control, making it a practical and efficient embedded application.


👨‍💻 Developed & Implemented By

🏆 Thumma Rahul

🆔 Vector ID: V25he2T5


