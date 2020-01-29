
#define ENCODER_MAX_POSITIONS 4096 

/* SPI commands */
#define AMT22_NOP       0x00
#define AMT22_RESET     0x60
#define AMT22_ZERO      0x70

/* Define special ascii characters */
#define NEWLINE         0x0A
#define TAB             0x09

/* We will use these define macros so we can write code once compatible with 12 or 14 bit encoders */
#define RES12           12
#define RES14           14

/* SPI pins */
#define ENC_PIN         ROTATION_PIN
#define SPI_MOSI        23
#define SPI_MISO        22
#define SPI_SCLK        24
