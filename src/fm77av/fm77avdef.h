#ifndef FM77AVDEF_IS_INCLUDED
#define FM77AVDEF_IS_INCLUDED
/* { */



#include <string>



enum
{
	SCALE_NANO=1000000000,

	FM77AVTIME_NANOSEC=1,
	FM77AVTIME_MICROSEC=1000,
	FM77AVTIME_MILLISEC=1000000,

	FM77AVTIME_ONE_SECOND=1000000000,  // Unit: Nano Seconds
	FM77AV_RENDERING_FREQUENCY=FM77AVTIME_ONE_SECOND/60,

	FM7_BIOS_ENTRY_ADDR=0xF17D,

	FM77AV_NUM_GAMEPORTS=2,
	FM77AV_VRAM_BANK_SIZE=0xC000,
	FM77AV40_VRAM_SIZE=0xC000*3,

	FM77AV_MAX_RAM_SIZE=256*1024,
	FM77AV40_NUM_VRAM_BANKS=3,

	FM7_MAX_NUM_COMPORTS=4,
};
enum
{
	SCRNMODE_640X200,
	SCRNMODE_320X200_4096COL,
	SCRNMODE_320X200_260KCOL,
	SCRNMODE_640X400,
};
std::string ScrnModeToStr(int scrnMode);

enum
{
	MACHINETYPE_UNKNOWN,
	MACHINETYPE_FM7,
	MACHINETYPE_FM77,
	MACHINETYPE_FM77AV,
	MACHINETYPE_FM77AV40
};
#define MACHINETYPE_AUTO MACHINETYPE_UNKNOWN
std::string MachineTypeToStr(unsigned int machineType);
unsigned int StrToMachineType(std::string str);


enum
{
	CPU_MAIN,     // Keep CPU_MAIN=0
	CPU_SUB,      // Keep CPU_SUB=1
	CPU_UNKNOWN=0xFF,  // Keep it same as FM77AV::ADDR_NONE never make it collide with other ADDR_s.
};
std::string CPUToStr(unsigned int cpuMainOrSub);
unsigned int StrToCPU(std::string str);


enum
{
	// Main CPU
	FM77AVIO_KEYCODE_PRINTER_CASSETTE=0xFD00,
	FM77AVIO_KEYCODE_PRINTER=         0xFD01,

	FM77AVIO_CASSETTE_IRQMASK=        0xFD02,
	FM77AVIO_IRQ_BEEP=                0xFD03,

	FM77AVIO_FIRQ_SUBSYS_INTERFACE=   0xFD04,
	FM77AVIO_SUBSYS_BUSY_HALT=        0xFD05,

	FM77AVIO_RS232C_DATA=             0xFD06,
	FM77AVIO_RS232C_COMMAND_STATUS=   0xFD07,

	FM77AVIO_SHADOW_RAM_FM7ONLY=      0xFD0B,
	FM77AVIO_BOOT_SELECT=             0xFD0B, // ?
	FM77AVIO_RS232C_ENABLE_AV40=      0xFD0B,
	FM77AVIO_RS232C_SPEED_AV40=       0xFD0B,

	FM77AVIO_PSG_CONTROL=             0xFD0D,
	FM77AVIO_PSG_DATA=                0xFD0E,

	FM77AVIO_SHADOW_RAM=              0xFD0F,

	FM77AVIO_INITIATOR_ROM=           0xFD10,

	FM77AVIO_SUBSYS_MODE=             0xFD12,
	FM77AVIO_SUBSYS_BANK=             0xFD13,

	FM77AVIO_YM2203C_CONTROL=         0xFD15,
	FM77AVIO_YM2203C_DATA=            0xFD16,

	FM77AVIO_INT_YM2203C_MOUSE=       0xFD17,

	FM77AVIO_FDC_STATUS_COMMAND=      0xFD18,
	FM77AVIO_FDC_TRACK=               0xFD19,
	FM77AVIO_FDC_SECTOR=              0xFD1A,
	FM77AVIO_FDC_DATA=                0xFD1B,
	FM77AVIO_FDC_SIDE=                0xFD1C,
	FM77AVIO_FDC_MOTOR_DRIVE=         0xFD1D,
	FM77AVIO_FDC_DRIVE_MODE=		  0xFD1E,
	FM77AVIO_FDC_DRQ_IRQ=             0xFD1F,

	FM77AVIO_KANJI_ADDR_HIGH=         0xFD20,
	FM77AVIO_KANJI_ADDR_LOW=          0xFD21,
	FM77AVIO_KANJI_DATA_L=            0xFD22,
	FM77AVIO_KANJI_DATA_R=            0xFD23,

	FM77AVIO_RS232C_COM1_DATA=        0xFD24,
	FM77AVIO_RS232C_COM1_COMMAND_STATUS=   0xFD25,
	FM77AVIO_RS232C_COM2_DATA=        0xFD26,
	FM77AVIO_RS232C_COM2_COMMAND_STATUS=   0xFD27,
	FM77AVIO_RS232C_COM3_DATA=        0xFD28,
	FM77AVIO_RS232C_COM3_COMMAND_STATUS=   0xFD29,
	FM77AVIO_RS232C_COM4_DATA=        0xFD2A,
	FM77AVIO_RS232C_COM4_COMMAND_STATUS=   0xFD2B,

	FM77AV40IO_KANJI2_ADDR_HIGH=      0xFD2C,
	FM77AV40IO_KANJI2_ADDR_LOW=       0xFD2D,
	FM77AV40IO_DICTIONARY_RAM_ROM=    0xFD2E,
	FM77AV40IO_KANJI2_DATA_R=         0xFD2F,

	FM77AVIO_ANALOG_PALETTE_NUM_HIGH= 0xFD30,
	FM77AVIO_ANALOG_PALETTE_NUM_LOW=  0xFD31,
	FM77AVIO_ANALOG_PALETTE_BLUE=     0xFD32,
	FM77AVIO_ANALOG_PALETTE_RED=      0xFD33,
	FM77AVIO_ANALOG_PALETTE_GREEN=    0xFD34,

	FM77AVIO_VOICE=                   0xFD35,

	FM77AVIO_DISPLAY_PAGE=            0xFD37,
	// See F-BASIC Analysys Manual Phase I, pp. 237 for details.

	FM77AVIO_DIGITAL_PALETTE_0=       0xFD38,
	FM77AVIO_DIGITAL_PALETTE_1=       0xFD39,
	FM77AVIO_DIGITAL_PALETTE_2=       0xFD3A,
	FM77AVIO_DIGITAL_PALETTE_3=       0xFD3B,
	FM77AVIO_DIGITAL_PALETTE_4=       0xFD3C,
	FM77AVIO_DIGITAL_PALETTE_5=       0xFD3D,
	FM77AVIO_DIGITAL_PALETTE_6=       0xFD3E,
	FM77AVIO_DIGITAL_PALETTE_7=       0xFD3F,

	FM77AVIO_MMR_0=                   0xFD80,
	FM77AVIO_MMR_1=                   0xFD81,
	FM77AVIO_MMR_2=                   0xFD82,
	FM77AVIO_MMR_3=                   0xFD83,
	FM77AVIO_MMR_4=                   0xFD84,
	FM77AVIO_MMR_5=                   0xFD85,
	FM77AVIO_MMR_6=                   0xFD86,
	FM77AVIO_MMR_7=                   0xFD87,
	FM77AVIO_MMR_8=                   0xFD88,
	FM77AVIO_MMR_9=                   0xFD89,
	FM77AVIO_MMR_A=                   0xFD8A,
	FM77AVIO_MMR_B=                   0xFD8B,
	FM77AVIO_MMR_C=                   0xFD8C,
	FM77AVIO_MMR_D=                   0xFD8D,
	FM77AVIO_MMR_E=                   0xFD8E,
	FM77AVIO_MMR_F=                   0xFD8F,
	FM77AVIO_MMR_SEG=                 0xFD90,
	FM77AVIO_WINDOW_OFFSET=           0xFD92,
	FM77AVIO_MEMORY_MODE=             0xFD93,

	FM77AVIO_AV40_EXTMMR=             0xFD94,

	FM77AVIO_AV40_DMAC_REG=           0xFD98,
	FM77AVIO_AV40_DMAC_DATA=          0xFD99,

	FM77AVIO_MOUSE_CONTROL_3_1=       0xFDE0,
	FM77AVIO_MOUSE_CONTROL_2=         0xFDE1,
	FM77AVIO_MOUSE_TIMER1_HIGH=       0xFDE2,
	FM77AVIO_MOUSE_TIMER1_LOW=        0xFDE3,
	FM77AVIO_MOUSE_TIMER2_HIGH=       0xFDE4,
	FM77AVIO_MOUSE_TIMER2_LOW=        0xFDE5,
	FM77AVIO_MOUSE_TIMER3_HIGH=       0xFDE6,
	FM77AVIO_MOUSE_TIMER3_LOW=        0xFDE7,
	FM77AVIO_MOUSE_STATUS_CONTROL=    0xFDE8,

	FM77AVIO_MIDI_PIT_USART_ENABLE=   0xFDE9,
	FM77AVIO_MIDI_DATA=               0xFDEA,
	FM77AVIO_MIDI_USART=              0xFDEB,
	FM77AVIO_MIDI_COUNTER_1=          0xFDEC,
	FM77AVIO_MIDI_COUNTER_2=          0xFDED,
	FM77AVIO_MIDI_COUNTER_3=          0xFDEE,
	FM77AVIO_MIDI_COUNTER_4=          0xFDEF,

	// Sub CPU
	FM77AVIO_KEY_HIGH=                0xD400,
	FM77AVIO_KEY_LOW=                 0xD401,

	FM77AVIO_ACK_CANCEL_IRQ=          0xD402,
	FM77AVIO_BEEP=                    0xD403,
	FM77AVIO_IRQ_TO_MAINCPU=          0xD404,
	FM77AVIO_SUB_KANJI_HIGH=          0xD406,
	FM77AVIO_SUB_KANJI_LOW=           0xD407,
	FM77AVIO_CRT_ON_OFF=              0xD408,
	FM77AVIO_VRAM_ACCESS=             0xD409,
	FM77AVIO_SUBCPU_BUSY=             0xD40A,
	FM77AVIO_INSERT_LED=              0xD40D,
	FM77AVIO_VRAM_OFFSET_HIGH=        0xD40E,
	FM77AVIO_VRAM_OFFSET_LOW=         0xD40F,

	FM77AVIO_LOGICAL_OP_MODE=         0xD410,
	FM77AVIO_LOGICAL_OP_COLOR=        0xD411,
	FM77AVIO_LOGICAL_OP_MASK=         0xD412,
	FM77AVIO_LOGICAL_OP_COMPARE_0=    0xD413,
	FM77AVIO_LOGICAL_OP_COMPARE_1=    0xD414,
	FM77AVIO_LOGICAL_OP_COMPARE_2=    0xD415,
	FM77AVIO_LOGICAL_OP_COMPARE_3=    0xD416,
	FM77AVIO_LOGICAL_OP_COMPARE_4=    0xD417,
	FM77AVIO_LOGICAL_OP_COMPARE_5=    0xD418,
	FM77AVIO_LOGICAL_OP_COMPARE_6=    0xD419,
	FM77AVIO_LOGICAL_OP_COMPARE_7=    0xD41A,
	FM77AVIO_LOGICAL_OP_BANK_DISABLE= 0xD41B,
	FM77AVIO_LOGICAL_OP_TILING_BLUE=  0xD41C,
	FM77AVIO_LOGICAL_OP_TILING_RED=   0xD41D,
	FM77AVIO_LOGICAL_OP_TILING_GREEN= 0xD41E,

	FM77AVIO_LINE_DRAW_OFFSET_HIGH=   0xD420,
	FM77AVIO_LINE_DRAW_OFFSET_LOW=    0xD421,
	FM77AVIO_LINE_DRAW_PATTERN_HIGH=  0xD422,
	FM77AVIO_LINE_DRAW_PATTERN_LOW=   0xD423,
	FM77AVIO_LINE_DRAW_X0_HIGH=       0xD424,
	FM77AVIO_LINE_DRAW_X0_LOW=        0xD425,
	FM77AVIO_LINE_DRAW_Y0_HIGH=       0xD426,
	FM77AVIO_LINE_DRAW_Y0_LOW=        0xD427,
	FM77AVIO_LINE_DRAW_X1_HIGH=       0xD428,
	FM77AVIO_LINE_DRAW_X1_LOW=        0xD429,
	FM77AVIO_LINE_DRAW_Y1_HIGH=       0xD42A,
	FM77AVIO_LINE_DRAW_Y1_LOW=        0xD42B,

	FM77AVIO_AV40_SUB_RAM_BANK=       0xD42E,
	FM77AVIO_AV40_400LINE_VRAMBANK=   0xD42F,

	FM77AVIO_LINE_DRAW_STATUS=        0xD430,

	FM77AVIO_ENCODER_DATA=            0xD431,
	FM77AVIO_ENCODER_STATUS=          0xD432,
};

enum
{
	FM7_SUBCMD_INKEY=                 0x29,
	FM7_SUBCMD_DEFINE_PFKEY=          0x2A,
	FM7_SUBCMD_GET_PFKEY_STR=         0x2B,
	FM7_SUBCMD_INT_CTRL=              0x2C,
	FM7_SUBCMD_SET_TIMER=             0x3D,
	FM7_SUBCMD_READ_TIMER=            0x3E,
	FM7_SUBCMD_TEST=                  0x3F,
	FM7_SUBCMD_INIT=                  0x01,
	FM7_SUBCMD_ERASE=                 0x02,
	FM7_SUBCMD_PUT=                   0x03,
	FM7_SUBCMD_GET=                   0x04,
	FM7_SUBCMD_GETC=                  0x05,
	FM7_SUBCMD_GET_CHAR_BLOCK1=       0x06,
	FM7_SUBCMD_PUT_CHAR_BLOCK1=       0x07,
	FM7_SUBCMD_GET_CHAR_BLOCK2=       0x08,
	FM7_SUBCMD_PUT_CHAR_BLOCK2=       0x09,
	FM7_SUBCMD_GET_BUFFER_ADDR=       0x0A,
	FM7_SUBCMD_TABSET=                0x0B,
	FM7_SUBCMD_CONSOLE_CONTROL=       0x0C,
	FM7_SUBCMD_ERASE2=                0x0D,
	FM7_SUBCMD_LINE=                  0x15,
	FM7_SUBCMD_CHAIN=                 0x16,
	FM7_SUBCMD_POINT=                 0x17,
	FM7_SUBCMD_PAINT=                 0x18,
	FM7_SUBCMD_SYMBOL=                0x19,
	FM7_SUBCMD_CHANGE_COLOR=          0x1A,
	FM7_SUBCMD_GET_BLOCK1=            0x1B,
	FM7_SUBCMD_PUT_BLOCK1=            0x1C,
	FM7_SUBCMD_GET_BLOCK2=            0x1D,
	FM7_SUBCMD_PUT_BLOCK2=            0x1E,
	FM7_SUBCMD_GCURSOR=               0x1F,
	FM7_SUBCMD_CHAR_LINE=             0x20,
FM7_MAX_SUB_CMD=0x40,
};

std::string SubCmdToStr(unsigned int subCmd);

enum
{
	FM7_BIOSCMD_ANALOGP=0x00,
	FM7_BIOSCMD_MOTOR=0x01,
	FM7_BIOSCMD_CTBWRT=0x02,
	FM7_BIOSCMD_CTBRED=0x03,
	FM7_BIOSCMD_INTBBL=0x04,
	FM7_BIOSCMD_SCREEN=0x05,
	FM7_BIOSCMD_WRTBBL=0x06,
	FM7_BIOSCMD_REDBBL=0x07,
	FM7_BIOSCMD_RESTOR=0x08,
	FM7_BIOSCMD_DWRITE=0x09,
	FM7_BIOSCMD_DREAD=0x0A,
	FM7_BIOSCMD_UNUSED1=0x0B,
	FM7_BIOSCMD_BEEPON=0x0C,
	FM7_BIOSCMD_BEEPOF=0x0D,
	FM7_BIOSCMD_LPOUT=0x0E,
	FM7_BIOSCMD_HDCOPY=0x0F,
	FM7_BIOSCMD_SUBOUT=0x10,
	FM7_BIOSCMD_SUBIN=0x11,
	FM7_BIOSCMD_INPUT=0x12,
	FM7_BIOSCMD_INPUTC=0x13,
	FM7_BIOSCMD_OUTPUT=0x14,
	FM7_BIOSCMD_KEYIN=0x15,
	FM7_BIOSCMD_KANJIR=0x16,
	FM7_BIOSCMD_LPCHK=0x17,
	FM7_BIOSCMD_BIINIT=0x18,
	FM7_BIOSCMD_UNUSED2=0x19,
	FM7_BIOSCMD_UNUSED3=0x1A,
	FM7_BIOSCMD_UNUSED4=0x1B,
};

std::string BIOSCmdToStr(unsigned int biosCmd);



// I don't know how likely I need analog-stick support,
// but I took it from Tsugaru anyway.

enum
{
	FM77AV_GAMEPORTEMU_NONE,
	FM77AV_GAMEPORTEMU_MOUSE,
	FM77AV_GAMEPORTEMU_KEYBOARD,
	FM77AV_GAMEPORTEMU_PHYSICAL0,
	FM77AV_GAMEPORTEMU_PHYSICAL1,
	FM77AV_GAMEPORTEMU_PHYSICAL2,
	FM77AV_GAMEPORTEMU_PHYSICAL3,
	FM77AV_GAMEPORTEMU_PHYSICAL4,
	FM77AV_GAMEPORTEMU_PHYSICAL5,
	FM77AV_GAMEPORTEMU_PHYSICAL6,
	FM77AV_GAMEPORTEMU_PHYSICAL7,
	FM77AV_GAMEPORTEMU_ANALOG0,
	FM77AV_GAMEPORTEMU_ANALOG1,
	FM77AV_GAMEPORTEMU_ANALOG2,
	FM77AV_GAMEPORTEMU_ANALOG3,
	FM77AV_GAMEPORTEMU_ANALOG4,
	FM77AV_GAMEPORTEMU_ANALOG5,
	FM77AV_GAMEPORTEMU_ANALOG6,
	FM77AV_GAMEPORTEMU_ANALOG7,
	FM77AV_GAMEPORTEMU_PHYSICAL0_AS_CYBERSTICK,
	FM77AV_GAMEPORTEMU_PHYSICAL1_AS_CYBERSTICK,
	FM77AV_GAMEPORTEMU_PHYSICAL2_AS_CYBERSTICK,
	FM77AV_GAMEPORTEMU_PHYSICAL3_AS_CYBERSTICK,
	FM77AV_GAMEPORTEMU_PHYSICAL4_AS_CYBERSTICK,
	FM77AV_GAMEPORTEMU_PHYSICAL5_AS_CYBERSTICK,
	FM77AV_GAMEPORTEMU_PHYSICAL6_AS_CYBERSTICK,
	FM77AV_GAMEPORTEMU_PHYSICAL7_AS_CYBERSTICK,
	FM77AV_GAMEPORTEMU_MOUSE_BY_KEY,
	FM77AV_GAMEPORTEMU_MOUSE_BY_NUMPAD,
	FM77AV_GAMEPORTEMU_MOUSE_BY_PHYSICAL0,
	FM77AV_GAMEPORTEMU_MOUSE_BY_PHYSICAL1,
	FM77AV_GAMEPORTEMU_MOUSE_BY_PHYSICAL2,
	FM77AV_GAMEPORTEMU_MOUSE_BY_PHYSICAL3,
	FM77AV_GAMEPORTEMU_MOUSE_BY_PHYSICAL4,
	FM77AV_GAMEPORTEMU_MOUSE_BY_PHYSICAL5,
	FM77AV_GAMEPORTEMU_MOUSE_BY_PHYSICAL6,
	FM77AV_GAMEPORTEMU_MOUSE_BY_PHYSICAL7,
	FM77AV_GAMEPORTEMU_MOUSE_BY_ANALOG0,
	FM77AV_GAMEPORTEMU_MOUSE_BY_ANALOG1,
	FM77AV_GAMEPORTEMU_MOUSE_BY_ANALOG2,
	FM77AV_GAMEPORTEMU_MOUSE_BY_ANALOG3,
	FM77AV_GAMEPORTEMU_MOUSE_BY_ANALOG4,
	FM77AV_GAMEPORTEMU_MOUSE_BY_ANALOG5,
	FM77AV_GAMEPORTEMU_MOUSE_BY_ANALOG6,
	FM77AV_GAMEPORTEMU_MOUSE_BY_ANALOG7,
	FM77AV_GAMEPORTEMU_CYBERSTICK,
	FM77AV_GAMEPORTEMU_CAPCOM_BY_PHYSICAL0,
	FM77AV_GAMEPORTEMU_CAPCOM_BY_PHYSICAL1,
	FM77AV_GAMEPORTEMU_CAPCOM_BY_PHYSICAL2,
	FM77AV_GAMEPORTEMU_CAPCOM_BY_PHYSICAL3,
	FM77AV_GAMEPORTEMU_CAPCOM_BY_PHYSICAL4,
	FM77AV_GAMEPORTEMU_CAPCOM_BY_PHYSICAL5,
	FM77AV_GAMEPORTEMU_CAPCOM_BY_PHYSICAL6,
	FM77AV_GAMEPORTEMU_CAPCOM_BY_PHYSICAL7,
FM77AV_GAMEPORTEMU_NUM_DEVICES,
};

#ifdef __cplusplus
	unsigned int StrToGamePortEmu(std::string str);
	std::string GamePortEmuToStr(unsigned int emu);
#endif


enum
{
	FM77AV_KEYBOARD_MODE_DEFAULT,
	FM77AV_KEYBOARD_MODE_DIRECT,
	FM77AV_KEYBOARD_MODE_TRANSLATION1, // ESC -> BREAK+ESC
	FM77AV_KEYBOARD_MODE_TRANSLATION2, // ESC -> ESC
	FM77AV_KEYBOARD_MODE_TRANSLATION3, // ESC -> BREAK

FM77AV_KEYBOARD_MODE_NUM_MODES
};

#ifdef __cplusplus
	std::string KeyboardModeToStr(unsigned int keyboardMode);
	unsigned int StrToKeyboardMode(std::string str);
#endif


enum
{
	FM77AV_APPSPECIFIC_NONE,
FM77AV_NUM_APPSPECIFIC
};

#ifdef __cplusplus
std::string FM77AVAppToStr(unsigned int app);
unsigned int FM77AVStrToApp(std::string str);
#endif


/* } */
#endif
