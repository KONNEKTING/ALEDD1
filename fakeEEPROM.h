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
    writeMemory(0,0xFF);
    writeMemory(1,0xFF);
    writeMemory(2,0xFF);
    writeMemory(3,0xFF);
    writeMemory(4,0xFF);
    writeMemory(5,0xFF);
    writeMemory(6,0xFF);
    writeMemory(7,0xFF);
    writeMemory(8,0xFF);
    writeMemory(9,0xFF);
    writeMemory(10,0xFF);
    writeMemory(11,0xFF);
    writeMemory(12,0xFF);
    writeMemory(13,0xFF);
    writeMemory(14,0xFF);
    writeMemory(15,0xFF);
    writeMemory(16,0xFF);
    writeMemory(17,0xFF);
    writeMemory(18,0xFF);
    writeMemory(19,0xFF);
    writeMemory(20,0xFF);
    writeMemory(21,0xFF);
    writeMemory(22,0xFF);
    writeMemory(23,0xFF);
    writeMemory(24,0xFF);
    writeMemory(25,0xFF);
    writeMemory(26,0xFF);
    writeMemory(27,0xFF);
    writeMemory(28,0xFF);
    writeMemory(29,0xFF);
    writeMemory(30,0xFF);
    writeMemory(31,0xFF);
    writeMemory(32,0xFF);
    writeMemory(33,0xFF);
    writeMemory(34,0xFF);
    writeMemory(35,0xFF);
    writeMemory(36,0xFF);
    writeMemory(37,0xFF);
    writeMemory(38,0xFF);
    writeMemory(39,0xFF);
    writeMemory(40,0xFF);
    writeMemory(41,0xFF);
    writeMemory(42,0xFF);
    writeMemory(43,0xFF);
    writeMemory(44,0xFF);
    writeMemory(45,0xFF);
    writeMemory(46,0xFF);
    writeMemory(47,0xFF);
    writeMemory(48,0xFF);
    writeMemory(49,0xFF);
    writeMemory(50,0xFF);
    writeMemory(51,0xFF);
    writeMemory(52,0xFF);
    writeMemory(53,0xFF);
    writeMemory(54,0xFF);
    writeMemory(55,0xFF);
    writeMemory(56,0xFF);
    writeMemory(57,0xFF);
    writeMemory(58,0xFF);
    writeMemory(59,0xFF);
    writeMemory(60,0xFF);
    writeMemory(61,0xFF);
    writeMemory(62,0xFF);
    writeMemory(63,0xFF);
    writeMemory(64,0xFF);
    writeMemory(65,0xFF);
    writeMemory(66,0xFF);
    writeMemory(67,0xFF);
    writeMemory(68,0xFF);
    writeMemory(69,0xFF);
    writeMemory(70,0xFF);
    writeMemory(71,0xFF);
    writeMemory(72,0xFF);
    writeMemory(73,0xFF);
    writeMemory(74,0xFF);
    writeMemory(75,0xFF);
    writeMemory(76,0xFF);
    writeMemory(77,0xFF);
    writeMemory(78,0xFF);
    writeMemory(79,0xFF);
    writeMemory(80,0xFF);
    writeMemory(81,0xFF);
    writeMemory(82,0xFF);
    writeMemory(83,0xFF);
    writeMemory(84,0xFF);
    writeMemory(85,0xFF);
    writeMemory(86,0xFF);
    writeMemory(87,0xFF);
    writeMemory(88,0xFF);
    writeMemory(89,0xFF);
    writeMemory(90,0xFF);
    writeMemory(91,0xFF);
    writeMemory(92,0xFF);
    writeMemory(93,0xFF);
    writeMemory(94,0xFF);
    writeMemory(95,0xFF);
    writeMemory(96,0xFF);
    writeMemory(97,0xFF);
    writeMemory(98,0xFF);
    writeMemory(99,0xFF);
    writeMemory(100,0xFF);
    writeMemory(101,0xFF);
    writeMemory(102,0xFF);
    writeMemory(103,0xFF);
    writeMemory(104,0xFF);
    writeMemory(105,0xFF);
    writeMemory(106,0xFF);
    writeMemory(107,0xFF);
    writeMemory(108,0xFF);
    writeMemory(109,0xFF);
    writeMemory(110,0xFF);
    writeMemory(111,0xFF);
    writeMemory(112,0xFF);
    writeMemory(113,0xFF);
    writeMemory(114,0xFF);
    writeMemory(115,0xFF);
    writeMemory(116,0xFF);
    writeMemory(117,0xFF);
    writeMemory(118,0xFF);
    writeMemory(119,0xFF);
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
    writeMemory(159,0xFF);
    writeMemory(160,0xFF);
    writeMemory(161,0xFF);
    writeMemory(162,0xFF);
    writeMemory(163,0xFF);
    writeMemory(164,0xFF);
    writeMemory(165,0xFF);
    writeMemory(166,0xFF);
    writeMemory(167,0xFF);
    writeMemory(168,0xFF);
    writeMemory(169,0xFF);
    writeMemory(170,0xFF);
    writeMemory(171,0xFF);
    writeMemory(172,0xFF);
    writeMemory(173,0xFF);
    writeMemory(174,0xFF);
    writeMemory(175,0xFF);
    writeMemory(176,0xFF);
    writeMemory(177,0xFF);
    writeMemory(178,0xFF);
    writeMemory(179,0xFF);
    writeMemory(180,0xFF);
    writeMemory(181,0xFF);
    writeMemory(182,0xFF);
    writeMemory(183,0xFF);
}
#endif
