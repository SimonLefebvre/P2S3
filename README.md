# P2S3
Le projet de la S3 est un projet de générateur d'électricité.
Le projet que nous dévelopons est un vélo électrique qui va recharger un batterie.
## Contenue
### Microcontroler Code
### Qt code

## BTInfo
### JsonInfo

| JSON Objects | Type | Name |
| --- | --- | --- |
| Between 0-2, Changes the screen view on the ESP32 | Number | "Mode Ecran" |
| Gives the status of the ESP32, can be changed, see status list | Number | "Status" |

#### Mode Ecran
Mode 0 is the mode that will show Voltages and Temperatures.
Mode 1 is the mode that will show the Motor Speed, Voltage, PWM and  Frequency
Mode 2 is the mode that will show the Generator Speed,  Voltage,  PWM and  Frequency

#### Status list

- #0: OK
- #1: Not OK

### JsonADC

| JSON Objects | Type | Name |
| --- | --- | --- |
| Gives the temperature of the motor in degree Celsius | Number | "Temp Moteur" |
| Gives the temperature of the generator in degree Celsius | Number | "Temp Generateur" |
| Gives the speed of the motor in RPM | Number | "Vitesse Moteur" |
| Gives the speed of the generator in RPM | Number | "Vitesse Generateur" |
| Gives the voltage that outputs the motor | Number | "Tension Moteur" |
| Gives the voltage that outputs the generator | Number | "Tension Generateur" |

### JsonPWM

| JSON Objects | Type | Name |
| --- | --- | --- |
| Gives the frequency that controls the motor | Number | "Freq Moteur" |
| Gives the frequency that controls the Generator | Number | "Freq Generateur" |
| Gives the PWM that controls the motor | Number | "PWM Moteur" |
| Gives the PWM that controls the Generator | Number | "PWM Generateur" |
