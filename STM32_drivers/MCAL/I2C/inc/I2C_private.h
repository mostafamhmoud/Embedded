#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

#define SLAVE_ADD_7_BIT_MASK         0xFFFFFF01
#define SLAVE_ADD_10_BIT_MASK        0xFC00


#define MASTER_WRITE_ADDRESS_MASK    0xFFFFFFFE

#define NUMBERS_OF_I2C                3U
#define I2C_IT_SOURCES                  2U



/* flags state names */

#define START_SEND                  1
#define ADDRESS_SEND                2
#define ADDRESS_10_SEND             3
#define STOP_SEND                   4
#define BYTE_FINISHED               5
#define DATA_REGISTER_EMPTY         6  // for transmitters
#define DATA_REGISTER_NOT_EMPTY     7  // for receivers


#define BUS_ERROR                    8
#define ARBITRATION_LOST             9
#define ACKNOWLEDGE_FAILURE          10
#define OVERRUN_UNDERRUN             11
#define PEC_ERROR_IN_RECEPTION       12
#define TIMEOUT_ERROR                13
#define SMBUS_ALERT                  14


/* I2C_CR1 Register bits */

enum
{
	PE,
	SMBUS,
	SMBTYPE = 3,
	ENARP,
	ENPEC,
	ENGC,
	NOSTRETCH,
	START,
	STOP,
	ACK,
	POS,
	PEC,
	ALERT,
	SWRST = 15,
};

/* I2C_CR2 Register bits */

enum
{
	FREQ,
	ITERREN = 8,
	ITEVTEN,
	ITBUFEN,
	DMAEN,
	LAST,
};

/* I2C_SR1 Register bits */

enum
{
	SB,
	ADDR,
	BTF,
	ADD10,
	STOPF,
	RxNE = 6,
	TxE,
	BERR,
	ARLO,
	AF,
	OVR,
	PECERR,
	TIMEOUT = 14,
	SMBALERT,

};

/* I2C_SR2 Register bits */

enum
{
	MSL,
	BUSY,
	TRA,
	GENCALL = 4,
	SMBDEFAULT,
	SMBHOST,
	DUALF,

};



/* I2C_CCR Register bits */

enum
{
	CCR,
	DUTY = 14,
	F_S,
};


/* I2C_OAR1 Register bits */

enum
{
	ADD0,
	ADDMODE = 15,
};



#endif // !I2C_PRIVATE_H

