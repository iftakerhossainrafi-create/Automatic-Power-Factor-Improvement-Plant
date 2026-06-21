# Automatic-Power-Factor-Improvement-Plant

Objective :

The aimofthis project is to design a system that automatically measures and improves the powerfactor of an electrical load. Inductive loads reduce power factor and efficiency. This system monitors powerfactor in real time and corrects it using a capacitor bank.

____________________________________________________________________________________________________________________________


Components :

   1. Arduino Uno

   2. Voltage Sensor (ZMPT101B)
      
   3. Current Sensor (SCT-013-000)

   4. Relay Module

   5. Capacitor Bank (3.5µF, 16µF, 20µF, 30µF)

   6. 16×2LCD(I2C)

   7. Inductive Loads

 ________________________________________________________________________________________________________________________

 
Arduino Pin Connections :

   1. A0–Voltage SensorInput

   2. A1–CurrentSensorInput

   3. 4–Relay 1

   4. 5–Relay 2

   5. 6–Relay 3

   6. 7–Relay 4

   7. A4–LCDSDA

   8. A5–LCDSCL

   9. 5V–Powersupplytosensors,LCD, and relays

   10. GND–Commonground

________________________________________________________________________________________________________________________


Circuit Diagram :

<img width="1185" height="850" alt="Circuit Diagram" src="https://github.com/user-attachments/assets/56977705-42e5-4f6d-9eaa-b87a5379ba12" />

Circuit Diagram :

<img width="1166" height="689" alt="Circuit Setup" src="https://github.com/user-attachments/assets/e5e8bd4d-c788-48f3-8a92-7dd348885b3d" />

_______________________________________________________________________________________________________________________


Working Principle :

The Automatic Power Factor Improvement Plant operates by continuously monitoring the electrical parameters of a load and automatically compensating for poor power factor using a capacitor bank. Initially, the system measures voltage and current using sensors such as the ZMPT101B voltage sensor and SCT-013-000 current sensor. These analog signals are fed into the Arduino microcontroller, where signal processing is performed. Using the EmonLib library, the Arduino calculates RMS voltage, RMS current, and the power factor (PF) by determining the phase difference between voltage and current waveforms. 

Once the power factor is computed, the controller compares it with a predefined threshold (typically 0.95). If the power factor falls below this limit, it indicates the presence of inductive loads (such as motors or ballasts), which cause lagging current. To compensate, the Arduino activates relay switches step-by-step, connecting capacitor banks in parallel with the load. These capacitors provide leading reactive power, which counteracts the lagging reactive power of the inductive load, thereby improving the overall power factor. As the power factor approaches the desired value, the system stops adding capacitors.


To prevent instability and frequent switching (relay chatter), a hysteresis control mechanism is implemented. This ensures that capacitors are only disconnected when the  power factor rises above a slightly higher threshold, avoiding overcompensation and maintaining system stability.Finally, the system displays real-time values of voltage, current, power factor and capacitor status on an LCD for monitoring purposes.

__________________________________________________________________________________________________________________________


Discussion

The developed system demonstrates an effective and automated solution to improve power factor in electrical systems with inductive loads. Experimental results show that the power factor can be significantly improved (e.g., from around 0.6 to approximately 0.9) through proper capacitor switching. One of the key advantages of this system is its automation. Unlike manual capacitor switching, which is slow and inefficient, this system responds instantly to load variations, ensuring continuous optimization of power factor. This leads to improved energy efficiency, reduced power losses, and lower electricity costs. However, several challenges were observed during implementation. Sensor noise and calibration inaccuracies can affect the precision of power factor measurement. Proper calibration using known loads is essential to ensure accurate readings. Additionally, selecting appropriate capacitor values is critical; incorrect sizing may lead to undercompensation or overcompensation. Another issue is the fluctuation of power factor due to rapidly changing loads. Although smoothing and averaging techniques help stabilize readings, some variations are unavoidable in real-time systems. For future improvements, the system can be enhanced by implementing automatic capacitor sizing, integrating IoT-based monitoring for remote data analysis, and using more precise industrial-grade sensors and meters. These upgrades would make the system more reliable and suitable for large-scale industrial applications.

Overall, the project successfully demonstrates a practical and scalable approach to automatic power factor correction, highlighting its importance in modern electrical systems.

_______________________________________________________________________________________________________________________




