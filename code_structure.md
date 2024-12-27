# Català
## **1. Programa Principal (`main.c`)**  
**Propòsit:** Controla la inicialització i execució del sistema.  
- Mostra una pantalla de benvinguda i missatges introductoris al GLCD.  
- Gestiona els estats del sistema (p. ex., **Selecció**, **Progrés**, **Finalitzat**) mitjançant una màquina d’estats.  
- Llegeix sensors de temperatura i pressió.  
- Gestiona la interacció de l’usuari i alerta sobre possibles punxades.  
- **Detecció de Rodes Punxades:**  
  - Mesura la **pressió cada 100 ms**.  
  - Si la pressió **disminueix**, imprimeix una **alerta** per avisar sobre una **possible roda punxada**.  

---

## **2. Mòduls Perifèrics**  

### **ADC (`ADC.c`)**  
- **Propòsit:** Inicialitza i llegeix dades analògiques dels sensors.  
- **Funcions Clau:**  
  - `initADC()` – Inicialitza la configuració de l’ADC.  
  - `getAN6()` i `getAN7()` – Llegeix valors analògics.  

### **CCP (`CCP.c`)**  
- **Propòsit:** Configura la sortida PWM per controlar dispositius externs.  
- **Funcions Clau:**  
  - `initPWM()` – Inicialitza el PWM.  
  - `setDutyCycleFromPSI()` – Ajusta el cicle de treball segons la pressió.  

### **EUSART (`EUSART.c`)**  
- **Propòsit:** Gestiona la comunicació sèrie.  
- **Funcions Clau:**  
  - `initEUSART()` – Inicialitza la comunicació.  
  - `transmitAsyncEUSART()` – Envia dades.  
  - `receptionErrorRecovery()` – Gestiona errors.  
- **Notes:**  
  - Durant les proves, vaig trobar l'**error de sobrecàrrega**, però **no l'error de sincronització de trama**.  
  - El mètode de recuperació resol els errors descartant **totes les dades de la FIFO** i **esborrant els indicadors d'error**, assegurant així que la comunicació reprengui sense dades invàlides.
  - Durant les proves amb la transmissió USART, vaig trobar un problema amb el format de final de línia. Estava utilitzant el caràcter *'\n'* per indicar el final de línia, però el terminal virtual esperava el format de Windows, que utilitza *'\r\n'*. Això causava que els salts de línia no es mostressin correctament. Per solucionar-ho, vaig modificar el codi per enviar *'\r\n'* en lloc de només *'\n'*, assegurant així la compatibilitat amb el terminal virtual utilitzat.  

### **Timers (`timers.c`)**  
- **Propòsit:** Gestiona les operacions de temporització i PWM.  
- **Funcions Clau:**  
  - `initTMR0()` – Configura el Temporitzador 0 per a interrupcions.  
  - `initTMR2()` – Configura el Temporitzador 2 per al PWM.  

---

## **3. Mòduls de Visualització**  

### **GLCD (`GLCD.c`)**  
- **Propòsit:** Proporciona un control de baix nivell per al GLCD.  
- **Característiques Clau:**  
  - Inicialitza i neteja el GLCD.  
  - Dibuixa text, números i elements gràfics com línies i píxels.  

### **Llibreria Gràfica (`libIndividual.c`)**  
- **Propòsit:** Proporciona funcions d’alt nivell per a elements gràfics.  
- **Característiques Clau:**  
  - Dibuixa botons amb estats commutables.  
  - Gestiona barres de progrés i animacions.  
  - Vaig **modificar algunes funcions anteriors** per treballar amb **estructures** per millorar la **encapsulació** i **abstracció**.  
  - Abans, les funcions requerien **arguments repetits com literals**, fet que **no era ergonòmic** ni **mantenible**. Ara, les estructures simplifiquen la gestió dels paràmetres i milloren la **lectura del codi**.  

---

## **4. Característiques Clau**  
- **Gestió d'Interrupcions:**  
  - Controla els temporitzadors, les entrades de botons i la comunicació sèrie.  
- **Disseny amb Màquina d'Estats:**  
  - Gestiona el comportament del sistema mitjançant estats predefinits.  
- **Mecanismes de Seguretat:**  
  - Detecta i alerta sobre caigudes brusques de pressió (rodes punxades).  
- **Anti-rebots:**  
  - Assegura una entrada fiable dels botons amb comptadors.  

---

# English
## **1. Main Program (`main.c`)**  
**Purpose:** Controls system initialization and execution.  
- Displays a splash screen and intro messages on the GLCD.  
- Manages system states (e.g., **Select**, **Progress**, **Finished**) through a state machine.  
- Reads temperature and pressure sensors.  
- Handles user input and alerts for events like flat tires.  
- **Flat Tyre Detection:**  
  - Measures **pressure every 100 ms**.  
  - If pressure **decreases**, it **prints an alert** to notify about a **potential flat tyre**.  

---

## **2. Peripheral Modules**  

### **ADC (`ADC.c`)**  
- **Purpose:** Initializes and reads analog data from sensors.  
- **Key Functions:**  
  - `initADC()` – Initializes ADC settings.  
  - `getAN6()` and `getAN7()` – Read analog values.  

### **CCP (`CCP.c`)**  
- **Purpose:** Configures PWM output for external device control.  
- **Key Functions:**  
  - `initPWM()` – Initializes PWM.  
  - `setDutyCycleFromPSI()` – Sets duty cycle based on pressure.  

### **EUSART (`EUSART.c`)**  
- **Purpose:** Handles serial communication.  
- **Key Functions:**  
  - `initEUSART()` – Initializes communication.  
  - `transmitAsyncEUSART()` – Sends data.  
  - `receptionErrorRecovery()` – Handles errors.  
- **Notes:**  
  - I encountered the **overrun error**, but **not the framing error** during testing.  
  - The recovery method resolves errors by **discarding all data in the FIFO** and **clearing error flags** to ensure proper communication resumes without invalid data.
  - While testing USART transmission, I encountered an issue with the end-of-line format. I was using the *'\n'* character to indicate the end of a line, but the virtual terminal expected the Windows format, which uses *'\r\n'*. This caused the line breaks to display incorrectly. To resolve this, I updated the code to transmit *'\r\n'* instead of just *'\n'*, ensuring compatibility with the virtual terminal in use.

### **Timers (`timers.c`)**  
- **Purpose:** Manages timing and PWM operations.  
- **Key Functions:**  
  - `initTMR0()` – Configures Timer0 for interrupts.  
  - `initTMR2()` – Configures Timer2 for PWM.  

---

## **3. Display Modules**  

### **GLCD (`GLCD.c`)**  
- **Purpose:** Provides low-level control for the Graphic LCD.  
- **Key Features:**  
  - Initializes and clears the GLCD.  
  - Draws text, numbers, and graphical elements like lines and pixels.  

### **Graphics Library (`libIndividual.c`)**  
- **Purpose:** Offers high-level functions for graphical elements.  
- **Key Features:**  
  - Draws buttons with toggle states.  
  - Manages progress bars and animations.  
  - I had to **modify some of the previous functions** to work with **structs** for better **encapsulation** and **abstraction**.  
  - Previously, functions required the same **repeated arguments as literals**, which was **not ergonomic** or **maintainable**. Using structs simplified parameter management and improved **code readability**.  

---

## **4. Key Features**  
- **Interrupt Handling:**  
  - Manages timers, button inputs, and serial communication.  
- **State Machine Design:**  
  - Controls system behavior through predefined states.  
- **Safety Mechanisms:**  
  - Detects and alerts for sudden pressure drops (flat tires).  
- **Debouncing:**  
  - Ensures reliable button input with counters.  

---
