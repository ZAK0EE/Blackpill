/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "MCAL/NVIC/NVIC.h"
#include "assertparam.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define SCB_PRIGROUP_OFFSET (8UL)
#define SCB_PRIGROUP_MASK (0x7UL << SCB_PRIGROUP_OFFSET)
/************************************/
/***************Registers************/
/************************************/
#define NVIC_BASE (0xE000E100UL)
#define SCB_BASE     (0xE000ED00UL)


#define NVIC    ((NVIC_t volatile* const)(NVIC_BASE))
#define SCB     ((SCB_t volatile* const)(SCB_BASE))
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

/**
 * @brief Macro to validate NVIC priority grouping options.
 *
 * This macro checks if the provided NVIC priority grouping option is valid.
 * It verifies if the option matches one of the defined options in the NVIC_PG_t enumeration.
 *
 * @param pg The NVIC priority grouping option to validate.
 *
 */
#define IS_VALID_NVIC_PG(pg) \
    (((pg) == NVIC_PG_16GROUPS_0SUBGROUPS) || \
     ((pg) == NVIC_PG_8GROUPS_2SUBGROUPS) || \
     ((pg) == NVIC_PG_4GROUPS_4SUBGROUPS) || \
     ((pg) == NVIC_PG_2GROUPS_8SUBGROUPS) || \
     ((pg) == NVIC_PG_0GROUPS_16SUBGROUPS))



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
    uint32_t RESERVED5[644];    /**< Reserved space */
    uint32_t STIR;              /**< Software Trigger Interrupt Register */
} NVIC_t;

/**
 * @brief Structure representing System Control Block (SCB) registers.
 *
 * This structure defines the layout of the System Control Block (SCB) registers,
 * which include various control and status registers related to the Cortex-M processor.
 */
typedef struct 
{
    uint32_t ACTLR;           /**< Auxiliary Control Register. */
    uint32_t Reserved1[829];  /**< Reserved space. */
    uint32_t CPUID;           /**< CPUID Base Register. */
    uint32_t ICSR;            /**< Interrupt Control and State Register. */
    uint32_t VTOR;            /**< Vector Table Offset Register. */
    uint32_t AIRCR;           /**< Application Interrupt and Reset Control Register. */
    uint32_t SCR;             /**< System Control Register. */
    uint32_t CCR;             /**< Configuration and Control Register. */
    uint8_t SHPR[12];         /**< System Handler Priority Registers (0-11). */
    uint32_t SHCSR;           /**< System Handler Control and State Register. */
    uint32_t CFSR;            /**< Configurable Fault Status Register. */
    uint32_t HFSR;            /**< Hard Fault Status Register. */
    uint32_t Reserved2;       /**< Reserved space. */
    uint32_t MMAR;            /**< MemManage Fault Address Register. */
    uint32_t BFAR;            /**< BusFault Address Register. */
    uint32_t AFSR;            /**< Auxiliary Fault Status Register. */
} SCB_t;


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

MCAL_StatusTypeDef NVIC_generateSWInterrupt(NVIC_IRQ_t NVIC_IRQ)
{
    assert_param(IS_VALID_NVIC_IRQ(NVIC_IRQ));

    NVIC->STIR = NVIC_IRQ;

    return MCAL_OK;
  
}

MCAL_StatusTypeDef NVIC_setPriorityGrouping(NVIC_PG_t PriorityGrouping)
{
    assert_param(IS_VALID_NVIC_PG(PriorityGrouping));

    /* Clearing the VECTKEYSTAT/VECTKEY bits as the read value is different than the write*/
    SCB->AIRCR = (SCB->AIRCR & ~(0xFFFFUL << 16)) | PriorityGrouping;

    return MCAL_OK;
}

MCAL_StatusTypeDef NVIC_SetPriority(NVIC_IRQ_t IRQ, NVIC_PG_t PriorityGrouping, uint8_t Preemption, uint8_t SubGroup)
{
    assert_param(IS_VALID_NVIC_IRQ(IRQ));
    assert_param(IS_VALID_NVIC_PG(PriorityGrouping));

    uint8_t SubGroupEndBit = ((PriorityGrouping & SCB_PRIGROUP_MASK) >> SCB_PRIGROUP_OFFSET);

    /* Create a mask covers bits from 0 to SubGroupEndBit*/
    //uint8_t SubGroupMask = 0xFF >> (8U - SubGroupEndBit - 1U);
    uint8_t SubGroupMask = (1 << (SubGroupEndBit + 1)) - 1;
    uint8_t SubGroupMasked = (SubGroup << 4) & SubGroupMask;

    uint8_t PreemptionMasked = (Preemption<< 4) & (uint8_t)~SubGroupMask;

    uint8_t Priority = PreemptionMasked | SubGroupMasked;

    NVIC->IPR[IRQ]=Priority;


    return MCAL_OK;
}
