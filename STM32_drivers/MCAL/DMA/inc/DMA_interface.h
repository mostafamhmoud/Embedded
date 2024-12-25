#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H



typedef enum
{
	CHANNEL0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL5,
	CHANNEL6,
	CHANNEL7,

}EN_DMA_Channel_t;

typedef enum
{
	STREAM0,
	STREAM1,
	STREAM2,
	STREAM3,
	STREAM4,
	STREAM5,
	STREAM6,
	STREAM7,

}EN_DMA_Stream_t;

typedef enum
{
	P2M,
	M2P,
	M2M,

}EN_DMA_Direction_t;

typedef enum
{
	LOW_PRIORITY,
	MEDIUM_PRIORITY,
	HIGH_PRIORITY,
	VERY_HIGH_PRIORITY,
}EN_DMA_Stream_Priority_t;

typedef enum
{
	BYTE,
	HALF_WORD,
	WORD,

}EN_DMA_Memmory_Peripheral_Data_Alignment_t;



typedef enum
{
	MINC_DISABLE,
	MINC_ENABLE,

}EN_DMA_Memmory_Increment_t;

typedef enum
{
	PINC_DISABLE,
	PINC_ENABLE,

}EN_DMA_Peripheral_Increment_t;


typedef enum
{
	DIRECT_MODE,
	FIFO_MODE,
}EN_DMA_Mode_t;

typedef enum
{
	CIRCULAR_MODE_DISABLE,
	CIRCULAR_MODE_ENABLE,
}EN_DMA_Circular_Mode_t;

typedef enum
{
	QUARTER_FULL_FIFO,
	HALF_FULL_FIFO,
	THREE_QUARTER_FULL_FIFO,
	FULL_FIFO,
}EN_DMA_FIFO_Threshold_Select_t;

typedef enum
{
	DMA1,
	DMA2,

}EN_DMA_Controller_t;

typedef enum
{
	Transfer_Complete_ID,
	Half_Transfer_ID,
	Transfer_Error_ID,
	FIFO_Error_ID,
	Direct_Mode_Error_ID,
}EN_DMA_IT_Type_t;

typedef struct
{
	uint8_t Transfer_Complete_Flag : 1;
	uint8_t Half_Transfer_Flag : 1;
	uint8_t Transfer_Error_Flag : 1;
	uint8_t FIFO_Error_Flag : 1;
	uint8_t Direct_Mode_Error_Flag : 1;
}ST_DMA_IT_FLAGS_State_t;


typedef enum
{
	DMA_IT_DISABLE,
	DMA_IT_ENABLE,
}EN_DMA_IT_State_t;

typedef struct
{
	EN_DMA_IT_State_t Transfer_Complete_IT;
	EN_DMA_IT_State_t Half_Transfer_IT;
	EN_DMA_IT_State_t Transfer_Error_IT;
	EN_DMA_IT_State_t FIFO_Error_IT;
	EN_DMA_IT_State_t Direct_Mode_Error_IT;

}ST_DMA_IT_Enable_t;


typedef struct
{
	EN_DMA_Controller_t DMA_controller;
	EN_DMA_Channel_t DMA_ch_num;
	EN_DMA_Stream_t DMA_str_num;
	EN_DMA_Direction_t DMA_dir;
	EN_DMA_Memmory_Peripheral_Data_Alignment_t DMA_mem_allign;
	EN_DMA_Memmory_Peripheral_Data_Alignment_t DMA_p_allign;
	EN_DMA_Memmory_Increment_t DMA_mem_inc;
	EN_DMA_Peripheral_Increment_t DMA_p_inc;
	EN_DMA_Stream_Priority_t DMA_str_priority;
	EN_DMA_Mode_t DMA_mode;
	EN_DMA_Circular_Mode_t DMA_Circular_mode;
	EN_DMA_FIFO_Threshold_Select_t DMA_fifo_select;

	ST_DMA_IT_Enable_t DMA_IT_State;

	void(*DMA_CallBackFun[5])(void);

}ST_DMA_config_t;


/* DMA_LISR register bits */

enum
{
	FEIF0,
	DMEIF0 = 2,
	TEIF0,
	HTIF0,
	TCIF0,
};

/* DMA_LIFCR register bits */

enum
{
	CFEIF0,
	CDMEIF0 = 2,
	CTEIF0,
	CHTIF0,
	CTCIF0,
};


/* DMA_SCR register bits */

enum
{
	EN,
	DMEIE,
	TEIE,
	HTIE,
	TCIE,
	PFCTRL,
	DIR,
	CIRC = 8,
	PINC,
	MINC,
	PSIZE,
	MSIZE = 13,
	PINCOS = 15,
	PL,
	DBM = 18,
	CT,
	PBURST = 21,
	MBURST = 23,
	CHSEL = 25,
};

/* DMA_SFCR register bits */

enum
{
	FTH,
	DMDIS = 2,
	FS,
	FEIE,

};


uint8_t DMA_Init(ST_DMA_config_t* Ptr_DMA_config);


uint8_t DMA_Start_IT(ST_DMA_config_t* Ptr_DMA_config, uint32_t* Src_Addr, uint32_t* Dest_Addr, uint16_t data_items);

uint8_t DMA_Set_Callback(ST_DMA_config_t* DMA_config, EN_DMA_IT_Type_t DMA_IT_type);

uint8_t DMA_Clear_IT_Flag(EN_DMA_Controller_t DMA_type, EN_DMA_Stream_t DMA_Str_num, EN_DMA_IT_Type_t IT_type);

static uint8_t DMA_Get_Flags_State(EN_DMA_Controller_t DMA_type, EN_DMA_Stream_t stram_num, ST_DMA_IT_FLAGS_State_t* Flags_state);





#endif
