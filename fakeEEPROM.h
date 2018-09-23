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
writeMemory(58,0x06);//type
writeMemory(59,0x00);
writeMemory(60,0x64);//ledNumber
writeMemory(61,0xFF);
writeMemory(62,0xFF);
writeMemory(63,0xFF);
writeMemory(64,0xFF);
writeMemory(65,0x00);
writeMemory(66,0xFF);
writeMemory(67,0xFA);
writeMemory(68,0xE0);
writeMemory(69,0x02);
writeMemory(70,0x03);
writeMemory(71,0x00);
writeMemory(72,0xFF);
writeMemory(73,0x00);
writeMemory(74,0xFF);
writeMemory(75,0xFF);
writeMemory(76,0x93);
writeMemory(77,0x29);
writeMemory(78,0x00);
writeMemory(79,0xFF);
writeMemory(80,0xC5);
writeMemory(81,0x8F);
writeMemory(82,0x00);
writeMemory(83,0xFF);
writeMemory(84,0xF1);
writeMemory(85,0xE0);
writeMemory(86,0x00);
writeMemory(87,0xFF);
writeMemory(88,0xFA);
writeMemory(89,0xF4);
writeMemory(90,0x00);
writeMemory(91,0xC9);
writeMemory(92,0xE2);
writeMemory(93,0xFF);
writeMemory(94,0x00);
writeMemory(95,0xFF);
writeMemory(96,0x00);
writeMemory(97,0x01);
writeMemory(98,0x02);
writeMemory(99,0x03);
writeMemory(100,0x04);
writeMemory(101,0x05);
writeMemory(102,0x06);
writeMemory(103,0x07);
writeMemory(104,0x08);
writeMemory(105,0x1F);
writeMemory(106,0x20);
writeMemory(107,0x21);
writeMemory(108,0x22);
writeMemory(109,0x23);
writeMemory(110,0x32);
writeMemory(111,0x33);
writeMemory(112,0x34);
writeMemory(113,0x35);
writeMemory(114,0x36);
writeMemory(115,0x37);
writeMemory(116,0x38);
writeMemory(117,0x39);
writeMemory(118,0x3C);
writeMemory(119,0x3D);
writeMemory(120,0xFF);
writeMemory(121,0xFF);
writeMemory(122,0xFF);
writeMemory(123,0xFF);
writeMemory(124,0xFF);
writeMemory(125,0xFF);
writeMemory(126,0xFF);
writeMemory(127,0xFF);
writeMemory(128,0xFF);
writeMemory(129,0xFF);
writeMemory(130,0xFF);
writeMemory(131,0xFF);
writeMemory(132,0xFF);
writeMemory(133,0xFF);
writeMemory(134,0xFF);
writeMemory(135,0xFF);
writeMemory(136,0xFF);
writeMemory(137,0xFF);
writeMemory(138,0xFF);
writeMemory(139,0xFF);
writeMemory(140,0xFF);
writeMemory(141,0xFF);
writeMemory(142,0xFF);
writeMemory(143,0xFF);
writeMemory(144,0xFF);
writeMemory(145,0xFF);
writeMemory(146,0xFF);
writeMemory(147,0xFF);
writeMemory(148,0xFF);
writeMemory(149,0xFF);
writeMemory(150,0xFF);
writeMemory(151,0xFF);
writeMemory(152,0xFF);
writeMemory(153,0xFF);
writeMemory(154,0xFF);
writeMemory(155,0xFF);
writeMemory(156,0xFF);
writeMemory(157,0xFF);
writeMemory(158,0xFF);
writeMemory(159,0x00);
writeMemory(160,0x1E);

}
#endif
