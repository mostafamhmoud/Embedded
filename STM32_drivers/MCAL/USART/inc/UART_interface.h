#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H




typedef enum
{
	SYNCHRONOUS,
	ASYNCHRONOUS,
}EN_Syn_Asyn_Mode_t;

typedef enum
{
	ONE_STOP_BIT,
	TWO_STOP_BIT,
	HALF_STOP_BIT,
	ONE_HALF_STOP_BIT
}EN_Stop_Bits_t;

typedef enum
{
	OVERSAMPLING_BY_16,
	OVERSAMPLING_BY_8,
}EN_OverSampling_Mode_t;

typedef enum
{
	DATA_BITS_8,
	DATA_BITS_9,
}EN_Data_Length_t;

typedef enum
{
	PARITY_CONTROL_DISABLE,
	PARITY_CONTROL_ENABLE,
}EN_Parity_Control_t;

typedef enum
{
	EVEN_PARITY,
	ODD_PARITY,
}EN_Parity_Select_t;

typedef enum
{
	TRANSMITTER,
	RECEIVER,
	TRANSMITTER_RECEIVER,
}EN_Tans_Rec_Mode_t;

typedef enum
{
	STD_LOW,
	STD_HIGH,
}EN_CLK_Polarity_t;

typedef enum
{
	FIRST_CLK_TRANS,
	SECOND_CLK_TRANS,
}EN_CLK_Phase_t;

typedef enum
{
	HALF_DUPLEX_NOT_SELECTED,
	HALF_DUPLEX_SELECTED,

}EN_Half_Duplex_Select_t;



typedef enum
{
	USART_NUM_2,
	USART_NUM_3,
	UART_NUM_4,

	UART_NUM_5,
	USART_NUM_1 = 51, // because usart2 start at 0x40004400  and usart1 start at 0x40011000
	USART_NUM_6,

}EN_USART_Num_t;


typedef enum
{
	DMA1_USED_USART,
	DMA2_USED_USART,
}EN_DMA_Used_t;

typedef enum
{
	STREAM0_USED_USART,
	STREAM1_USED_USART,
	STREAM2_USED_USART,
	STREAM3_USED_USART,
	STREAM4_USED_USART,
	STREAM5_USED_USART,
	STREAM6_USED_USART,
	STREAM7_USED_USART,

}EN_DMA_Stream_Used_t;

typedef struct
{
	EN_USART_Num_t usart_num;
	EN_Syn_Asyn_Mode_t sync_async;
	EN_Stop_Bits_t stop_bits;
	uint32_t baud_rate;
	EN_Parity_Control_t parity_en_dis;
	EN_Parity_Select_t parity_ev_odd;
	EN_Data_Length_t data_length;
	EN_Tans_Rec_Mode_t mode;
	EN_OverSampling_Mode_t ov_s_mode;
	EN_CLK_Polarity_t clk_pol;
	EN_CLK_Phase_t clk_phase;
	EN_Half_Duplex_Select_t half_duplex_select;
	EN_DMA_Stream_Used_t dma_stream_used;
	EN_DMA_Used_t dma_used;

}ST_USART_Config_t;




/* CR1 Register Bits */

enum
{
	SBK,
	RWU,
	RE,
	TE,
	IDLEIE,
	RXNEIE,
	UART_TCIE,
	TXEIE,
	PEIE,
	PS,
	PCE,
	WAKE,
	M,
	UE,
	OVER8 = 15,

};

/* CR2 Register Bits */

enum
{
	ADD,
	LBDL = 5,
	LBDIE,
	LBCL = 8,
	CPHA,
	CPOL,
	CLKEN,
	STOP,
	LINEN = 14,
};

/* CR3 Register Bits */

enum
{
	EIE,
	IREN,
	IRLP,
	HDSEL,
	NACK,
	SCEN,
	DMAR,
	DMAT,
	RTSE,
	CTSE,
	CTSIE,
	ONEBIT,
};


/* SR Register Bits */

enum
{
	UART_PE,
	FE,
	NF,
	ORE,
	IDLE,
	RXNE,
	TC,
	TXE,
	LBD,
	CTS,

};

uint8_t USART_init(ST_USART_Config_t* usart_config);

uint8_t USART_Transmit_Polling(ST_USART_Config_t* usart_config, uint8_t* trans_data, uint8_t data_len);

uint8_t USART_Receive_Polling(ST_USART_Config_t* usart_config, uint8_t* received_data);

uint8_t USART_Transmit_IT(EN_USART_Num_t usart_num, uint8_t trans_data);

uint8_t USART_Receive_IT(EN_USART_Num_t usart_num, uint8_t* received_data);

uint8_t USART_Transmit_DMA(ST_USART_Config_t* usart_config , uint32_t Src_Addr, uint32_t data_len);

uint8_t USART_Receive_DMA(ST_USART_Config_t* usart_config, uint32_t Dest_Addr, uint32_t data_len);


#endif // !UART_INTERFACE_H

