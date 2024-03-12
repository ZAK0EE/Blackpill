/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "MCAL/NVIC/NVIC.h"
#include "assertparam.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

/************************************/
/***************Registers************/
/************************************/
#define NVIC_BASE (0xE000E100UL)


#define NVIC ((NVIC_t volatile* const)(NVIC_BASE))

/************************************/
/***************Validators***********/
/************************************/
/**
 * @brief Validate the NVIC interrupt.
 * 
 * This macro checks if the provided NVIC interrupt is within the valid range.
 * 
 * @param IRQ NVIC interrupt to be validated.
 */
#define IS_VALID_NVIC_IRQ(IRQ) (((IRQ) >= NVIC_IRQ_WWDG) && ((IRQ) <= NVIC_IRQ_SPI4))


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

/**
 * @brief Nested Vectored Interrupt Controller (NVIC) structure.
 * 
 * This structure represents the memory-mapped registers of the Nested Vectored Interrupt Controller (NVIC)
 * in a typical ARM Cortex-M microcontroller.
 * It includes registers for enabling, disabling, setting, and clearing interrupts, as well as registers for
 * interrupt pending, active status, and priority levels.
 * 
 * Note: The layout of this structure corresponds to the memory-mapped register arrangement of NVIC in ARM Cortex-M.
 * 
 * @see Cortex-M Technical Reference Manual for detailed information.
 */
typedef struct
{
    uint32_t ISER[8];           /**< Interrupt Set-Enable Registers (0-7) */
    uint32_t RESERVED0[24];     /**< Reserved space */
    uint32_t ICER[8];           /**< Interrupt Clear-Enable Registers (0-7) */
    uint32_t RESERVED1[24];     /**< Reserved space */
    uint32_t ISPR[8];           /**< Interrupt Set-Pending Registers (0-7) */
    uint32_t RESERVED2[24];     /**< Reserved space */
    uint32_t ICPR[8];           /**< Interrupt Clear-Pending Registers (0-7) */
    uint32_t RESERVED3[24];     /**< Reserved space */
    uint32_t IABR[8];           /**< Interrupt Active Bit Registers (0-7) */
    uint32_t RESERVED4[56];     /**< Reserved space */
    uint8_t  IPR[240];          /**< Interrupt Priority Registers (0-59) - Byte Accessible */
    uint32_t RESERVED5[580];    /**< Reserved space */
    uint32_t STIR;              /**< Software Trigger Interrupt Register */
} NVIC_t;


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

/**
 * @brief Clear pending interrupt for the specified NVIC_IRQ.
 * 
 * This function clears the pending status of the specified Nested Vectored Interrupt Controller (NVIC) interrupt.
 * 
 * @param NVIC_IRQ The NVIC_IRQ_t representing the interrupt for which the pending status should be cleared.
 */
static void clearPendingIRQ(NVIC_IRQ_t NVIC_IRQ)
{
    NVIC->ICPR[NVIC_IRQ / 32] = (1UL << (NVIC_IRQ % 32));
}

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/




MCAL_StatusTypeDef NVIC_enableIRQ(NVIC_IRQ_t NVIC_IRQ)
{
    assert_param(IS_VALID_NVIC_IRQ(NVIC_IRQ));

    /* Clear any previous pending*/
    clearPendingIRQ(NVIC_IRQ);

    /*Enable IRQ*/
    NVIC->ISER[NVIC_IRQ / 32] = (1UL << (NVIC_IRQ % 32));

    return MCAL_OK;
}

MCAL_StatusTypeDef NVIC_disableIRQ(NVIC_IRQ_t NVIC_IRQ)
{
    assert_param(IS_VALID_NVIC_IRQ(NVIC_IRQ));

    /*Disable IRQ*/
    NVIC->ICER[NVIC_IRQ / 32] = (1UL << (NVIC_IRQ % 32));

    return MCAL_OK;

}

MCAL_StatusTypeDef NVIC_setPendingIRQ(NVIC_IRQ_t NVIC_IRQ)
{
    assert_param(IS_VALID_NVIC_IRQ(NVIC_IRQ));

    NVIC->ISPR[NVIC_IRQ / 32] = (1UL << (NVIC_IRQ % 32));

    return MCAL_OK;
}

MCAL_StatusTypeDef NVIC_clearPendingIRQ(NVIC_IRQ_t NVIC_IRQ)
{
    assert_param(IS_VALID_NVIC_IRQ(NVIC_IRQ));

    clearPendingIRQ(NVIC_IRQ);
    return MCAL_OK;
}

NVIC_IsPending_t NVIC_getPendingIRQ(NVIC_IRQ_t NVIC_IRQ)
{
    assert_param(IS_VALID_NVIC_IRQ(NVIC_IRQ));

    NVIC_IsPending_t IRQPendingState = (NVIC->ISPR[NVIC_IRQ / 32] >> (NVIC_IRQ % 32)) & 1UL;
    return IRQPendingState;
 
}

NVIC_IsActive_t NVIC_getActiveStatus(NVIC_IRQ_t NVIC_IRQ)
{
    assert_param(IS_VALID_NVIC_IRQ(NVIC_IRQ));

    NVIC_IsActive_t IRQActiveState = (NVIC->IABR[NVIC_IRQ / 32] >> (NVIC_IRQ % 32)) & 1UL;
    return IRQActiveState;

}

