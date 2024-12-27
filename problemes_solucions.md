## *Problema amb la Transmissió USART (Català)*  
Durant les proves amb la transmissió USART, vaig trobar un problema amb el format de final de línia. Estava utilitzant el caràcter *'\n'* per indicar el final de línia, però el terminal virtual esperava el format de Windows, que utilitza *'\r\n'*. Això causava que els salts de línia no es mostressin correctament.  

Per solucionar-ho, vaig modificar el codi per enviar *'\r\n'* en lloc de només *'\n'*, assegurant així la compatibilitat amb el terminal virtual utilitzat.  

---

## *USART Transmission Issue (English)*  
While testing USART transmission, I encountered an issue with the end-of-line format. I was using the *'\n'* character to indicate the end of a line, but the virtual terminal expected the Windows format, which uses *'\r\n'*. This caused the line breaks to display incorrectly.  

To resolve this, I updated the code to transmit *'\r\n'* instead of just *'\n'*, ensuring compatibility with the virtual terminal in use.
