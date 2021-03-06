#include "OLED.h"

// 8x16 ASCII
const u8 ASCII8[96][5]={          
0x00, 0x00, 0x00, 0x00, 0x00,   // sp    1
0x00, 0x00, 0x2f, 0x00, 0x00,   // !     2
0x00, 0x07, 0x00, 0x07, 0x00,   // "     3
0x14, 0x7f, 0x14, 0x7f, 0x14,   // #     4
0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $     5
0x62, 0x64, 0x08, 0x13, 0x23,   // %     6
0x36, 0x49, 0x55, 0x22, 0x50,   // &     7
0x00, 0x05, 0x03, 0x00, 0x00,   // ��    8
0x00, 0x1c, 0x22, 0x41, 0x00,   // (     9
0x00, 0x41, 0x22, 0x1c, 0x00,   // )     10
0x14, 0x08, 0x3E, 0x08, 0x14,   // *     11
0x08, 0x08, 0x3E, 0x08, 0x08,   // +     12
0x00, 0x00, 0xA0, 0x60, 0x00,   // ,     13
0x08, 0x08, 0x08, 0x08, 0x08,   // -     14
0x00, 0x60, 0x60, 0x00, 0x00,   // .     15
0x20, 0x10, 0x08, 0x04, 0x02,   // /     16
0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0     17
0x00, 0x42, 0x7F, 0x40, 0x00,   // 1     18
0x42, 0x61, 0x51, 0x49, 0x46,   // 2     19
0x21, 0x41, 0x45, 0x4B, 0x31,   // 3     20
0x18, 0x14, 0x12, 0x7F, 0x10,   // 4     21
0x27, 0x45, 0x45, 0x45, 0x39,   // 5     22
0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6     23
0x01, 0x71, 0x09, 0x05, 0x03,   // 7     24
0x36, 0x49, 0x49, 0x49, 0x36,   // 8     25
0x06, 0x49, 0x49, 0x29, 0x1E,   // 9     26
0x00, 0x36, 0x36, 0x00, 0x00,   // :     27
0x00, 0x56, 0x36, 0x00, 0x00,   // ;     28
0x08, 0x14, 0x22, 0x41, 0x00,   // <     29
0x14, 0x14, 0x14, 0x14, 0x14,   // =     30
0x00, 0x41, 0x22, 0x14, 0x08,   // >     31
0x02, 0x01, 0x51, 0x09, 0x06,   // ?     32
0x32, 0x49, 0x59, 0x51, 0x3E,   // @     33
0x7C, 0x12, 0x11, 0x12, 0x7C,   // A     34
0x7F, 0x49, 0x49, 0x49, 0x36,   // B     35
0x3E, 0x41, 0x41, 0x41, 0x22,   // C     36
0x7F, 0x41, 0x41, 0x22, 0x1C,   // D     37
0x7F, 0x49, 0x49, 0x49, 0x41,   // E     38
0x7F, 0x09, 0x09, 0x09, 0x01,   // F     39
0x3E, 0x41, 0x49, 0x49, 0x7A,   // G     40
0x7F, 0x08, 0x08, 0x08, 0x7F,   // H     41
0x00, 0x41, 0x7F, 0x41, 0x00,   // I     42
0x20, 0x40, 0x41, 0x3F, 0x01,   // J     43
0x7F, 0x08, 0x14, 0x22, 0x41,   // K     44
0x7F, 0x40, 0x40, 0x40, 0x40,   // L     45
0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M     46
0x7F, 0x04, 0x08, 0x10, 0x7F,   // N     47
0x3E, 0x41, 0x41, 0x41, 0x3E,   // O     48
0x7F, 0x09, 0x09, 0x09, 0x06,   // P     49
0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q     50
0x7F, 0x09, 0x19, 0x29, 0x46,   // R     51
0x46, 0x49, 0x49, 0x49, 0x31,   // S     52
0x01, 0x01, 0x7F, 0x01, 0x01,   // T     53
0x3F, 0x40, 0x40, 0x40, 0x3F,   // U     54
0x1F, 0x20, 0x40, 0x20, 0x1F,   // V     55
0x3F, 0x40, 0x38, 0x40, 0x3F,   // W     56
0x63, 0x14, 0x08, 0x14, 0x63,   // X     57
0x07, 0x08, 0x70, 0x08, 0x07,   // Y     58
0x61, 0x51, 0x49, 0x45, 0x43,   // Z     59
0x00, 0x7F, 0x41, 0x41, 0x00,   // [     60
0x55, 0x2A, 0x55, 0x2A, 0x55,   // 55    61
0x00, 0x41, 0x41, 0x7F, 0x00,   // ]     62
0x04, 0x02, 0x01, 0x02, 0x04,   // ^     63
0x40, 0x40, 0x40, 0x40, 0x40,   // _     64
0x00, 0x01, 0x02, 0x04, 0x00,   // ��    65
0x20, 0x54, 0x54, 0x54, 0x78,   // a     66
0x7F, 0x48, 0x44, 0x44, 0x38,   // b     67
0x38, 0x44, 0x44, 0x44, 0x20,   // c     68
0x38, 0x44, 0x44, 0x48, 0x7F,   // d     69
0x38, 0x54, 0x54, 0x54, 0x18,   // e     70
0x08, 0x7E, 0x09, 0x01, 0x02,   // f     71
0x18, 0xA4, 0xA4, 0xA4, 0x7C,   // g     72
0x7F, 0x08, 0x04, 0x04, 0x78,   // h     73
0x00, 0x44, 0x7D, 0x40, 0x00,   // i     74
0x40, 0x80, 0x84, 0x7D, 0x00,   // j     75
0x7F, 0x10, 0x28, 0x44, 0x00,   // k     76
0x00, 0x41, 0x7F, 0x40, 0x00,   // l     77
0x7C, 0x04, 0x18, 0x04, 0x78,   // m     78
0x7C, 0x08, 0x04, 0x04, 0x78,   // n     79
0x38, 0x44, 0x44, 0x44, 0x38,   // o     80
0xFC, 0x24, 0x24, 0x24, 0x18,   // p     81
0x18, 0x24, 0x24, 0x18, 0xFC,   // q     82
0x7C, 0x08, 0x04, 0x04, 0x08,   // r     83
0x48, 0x54, 0x54, 0x54, 0x20,   // s     84
0x04, 0x3F, 0x44, 0x40, 0x20,   // t     85
0x3C, 0x40, 0x40, 0x20, 0x7C,   // u     86
0x1C, 0x20, 0x40, 0x20, 0x1C,   // v     87
0x3C, 0x40, 0x30, 0x40, 0x3C,   // w     88
0x44, 0x28, 0x10, 0x28, 0x44,   // x     89
0x1C, 0xA0, 0xA0, 0xA0, 0x7C,   // y     90
0x44, 0x64, 0x54, 0x4C, 0x44,   // z     91
0x00, 0x08, 0x36, 0x41, 0x00,   // {     92
0x00, 0x00, 0x7F, 0x00, 0x00,   // |     93
0x00, 0x41, 0x36, 0x08, 0x00,   // }     94
0x08, 0x10, 0x08, 0x04, 0x08    // ~     95
}; 
