#ifndef SYSCFG_INTERFACE_H
#define SYSCFG_INTERFACE_H

typedef enum
{
	LINE0,
	LINE1,
	LINE2,
	LINE3,
	LINE4,
	LINE5,
	LINE6,
	LINE7,
	LINE8,
	LINE9,
	LINE10,
	LINE11,
	LINE12,
	LINE13,
	LINE14,
	LINE15

}EN_SYSCFG_Line_t;

typedef enum
{
	PA,
	PB,
	PC,
	PD,
	PE,
	PF,
	PG,
	PH

}EN_SYSCFG_Port_t;

uint8_t SYSCFG_Set_Line(EN_SYSCFG_Line_t copy_port, EN_SYSCFG_Line_t copy_line);


#endif
