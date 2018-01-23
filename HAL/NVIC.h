#pragma once
#include "Common.h"

struct __reserved_SNVIC
{
public:
	__reserved_SNVIC();
	~__reserved_SNVIC(void);

	void enable(IRQn_Type IRQn);
	void disable(IRQn_Type IRQn);
	void configPriority(IRQn_Type IRQn,u8 PreemptionPriority,u8 SubPriority);
private:
	__IO uint32_t ISER[8];                      /*!< Offset: 0x000  Interrupt Set Enable Register           */
	uint32_t RESERVED0[24];                                   
	__IO uint32_t ICER[8];                      /*!< Offset: 0x080  Interrupt Clear Enable Register         */
	uint32_t RSERVED1[24];                                    
	__IO uint32_t ISPR[8];                      /*!< Offset: 0x100  Interrupt Set Pending Register          */
	uint32_t RESERVED2[24];                                   
	__IO uint32_t ICPR[8];                      /*!< Offset: 0x180  Interrupt Clear Pending Register        */
	uint32_t RESERVED3[24];                                   
	__IO uint32_t IABR[8];                      /*!< Offset: 0x200  Interrupt Active bit Register           */
	uint32_t RESERVED4[56];                                   
	__IO uint8_t  IP[240];                      /*!< Offset: 0x300  Interrupt Priority Register (8Bit wide) */
	uint32_t RESERVED5[644];                                  
	__O  uint32_t STIR;                         /*!< Offset: 0xE00  Software Trigger Interrupt Register     */
};

#define nvic	(*(__reserved_SNVIC*)NVIC)
