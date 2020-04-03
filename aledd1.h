#ifndef DEVELOPMENT //ALEDD
//create a new Serial on Pins 1=TX and 3=RX
Uart SerialKNX (&sercom2, 3, 1, SERCOM_RX_PAD_1, UART_TX_PAD_2); //+pinPeripheral
//Interrupt handler for SerialKNX
void SERCOM2_Handler()
{
  SerialKNX.IrqHandler();
}

//Hardware settings 
#define PROG_BUTTON_PIN 2 //active low
#define PROG_LED_PIN 8
#define LED_STRIP_PIN 22
#define POWER_SUPPLY_PIN 38 //active low
#define EEPROM_EMULATION_SIZE 2048

#else //test board
//Hardware settings 
#define PROG_BUTTON_PIN 7 //active low
#define PROG_LED_PIN 13
#define LED_STRIP_PIN 6  //LED shield
#define POWER_SUPPLY_PIN 8 //active low
#define EEPROM_EMULATION_SIZE 2048
#define SerialKNX Serial
#endif



#ifndef FAKE_EEPROM
byte readMemory(int index) {
    Debug.println(F("FLASH read on index %d"),index);
    return EEPROM.read(index);
}

void writeMemory(int index, byte val) {
    Debug.println(F("FLASH write value %d on index %d"),val, index);
    EEPROM.write(index, val);
}

void updateMemory(int index, byte val) {
    Debug.println(F("FLASH update"));
    if (EEPROM.read(index) != val) {
        EEPROM.write(index, val);
    }
}

void commitMemory() {
    Debug.println(F("FLASH commit"));
    EEPROM.commit();
}
#endif
