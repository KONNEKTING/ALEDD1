#ifdef FAKE_EEPROM
byte virtualEEPROM[256];

byte readMemory(int index){
    return virtualEEPROM[index];
}

void writeMemory(int index, byte val) {
    virtualEEPROM[index] = val;
}

void updateMemory(int index, byte val) {
    if (readMemory(index) != val) {
        writeMemory(index, val);
    }
}

void commitMemory() {

}

void initFakeEeprom(){
writeMemory(0,0x7F);
writeMemory(1,0x11);
writeMemory(2,0xE0);
writeMemory(3,0xFF);
writeMemory(4,0xFF);
writeMemory(5,0xFF);
writeMemory(6,0xFF);
writeMemory(7,0xFF);
writeMemory(8,0xFF);
writeMemory(9,0xFF);
writeMemory(10,0x3E);
writeMemory(11,0x00);
writeMemory(12,0x80);
writeMemory(13,0x3E);
writeMemory(14,0x01);
writeMemory(15,0x80);
writeMemory(16,0x3E);
writeMemory(17,0x02);
writeMemory(18,0x80);
writeMemory(19,0x3E);
writeMemory(20,0x04);
writeMemory(21,0x80);
writeMemory(22,0x3E);
writeMemory(23,0x05);
writeMemory(24,0x80);
writeMemory(25,0x3E);
writeMemory(26,0x03);
writeMemory(27,0x80);
writeMemory(28,0x3E);
writeMemory(29,0x0A);
writeMemory(30,0x80);
writeMemory(31,0x3E);
writeMemory(32,0x0B);
writeMemory(33,0x80);
writeMemory(34,0x3E);
writeMemory(35,0x0C);
writeMemory(36,0x80);
writeMemory(37,0x3E);
writeMemory(38,0x0D);
writeMemory(39,0x80);
writeMemory(40,0x3E);
writeMemory(41,0x14);
writeMemory(42,0x80);
writeMemory(43,0x3E);
writeMemory(44,0x15);
writeMemory(45,0x80);
writeMemory(46,0x3E);
writeMemory(47,0x0E);
writeMemory(48,0x80);
writeMemory(49,0x3E);
writeMemory(50,0x0F);
writeMemory(51,0x80);
writeMemory(52,0x3E);
writeMemory(53,0x10);
writeMemory(54,0x80);
writeMemory(55,0x3E);
writeMemory(56,0x16);
writeMemory(57,0x80);
writeMemory(58,0x3E);
writeMemory(59,0x17);
writeMemory(60,0x80);
writeMemory(61,0xD2);
writeMemory(62,0x00);
writeMemory(63,0x1E);
writeMemory(64,0xFF);
writeMemory(65,0xFF);
writeMemory(66,0xFF);
writeMemory(67,0xFF);
writeMemory(68,0x1C);
writeMemory(69,0xFF);
writeMemory(70,0xFA);
writeMemory(71,0xE0);
writeMemory(72,0x02);
writeMemory(73,0x03);
writeMemory(74,0x00);
writeMemory(75,0xFF);
writeMemory(76,0x00);
writeMemory(77,0xFF);
writeMemory(78,0x00);
writeMemory(79,0x00);
writeMemory(80,0x00);
writeMemory(81,0x00);
writeMemory(82,0x00);
writeMemory(83,0x00);
writeMemory(84,0x00);
writeMemory(85,0x00);
writeMemory(86,0x00);
writeMemory(87,0x00);
writeMemory(88,0x00);
writeMemory(89,0x00);
writeMemory(90,0x00);
writeMemory(91,0x00);
writeMemory(92,0x00);
writeMemory(93,0x00);
writeMemory(94,0x00);
writeMemory(95,0x00);
writeMemory(96,0x00);
writeMemory(97,0x00);

}
#endif
