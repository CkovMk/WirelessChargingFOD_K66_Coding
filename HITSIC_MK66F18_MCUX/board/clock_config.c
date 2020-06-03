/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/
/*
 * How to setup clock using clock driver functions:
 *
 * 1. CLOCK_SetSimSafeDivs, to make sure core clock, bus clock, flexbus clock
 *    and flash clock are in allowed range during clock mode switch.
 *
 * 2. Call CLOCK_Osc0Init to setup OSC clock, if it is used in target mode.
 *
 * 3. Set MCG configuration, MCG includes three parts: FLL clock, PLL clock and
 *    internal reference clock(MCGIRCLK). Follow the steps to setup:
 *
 *    1). Call CLOCK_BootToXxxMode to set MCG to target mode.
 *
 *    2). If target mode is FBI/BLPI/PBI mode, the MCGIRCLK has been configured
 *        correctly. For other modes, need to call CLOCK_SetInternalRefClkConfig
 *        explicitly to setup MCGIRCLK.
 *
 *    3). Don't need to configure FLL explicitly, because if target mode is FLL
 *        mode, then FLL has been configured by the function CLOCK_BootToXxxMode,
 *        if the target mode is not FLL mode, the FLL is disabled.
 *
 *    4). If target mode is PEE/PBE/PEI/PBI mode, then the related PLL has been
 *        setup by CLOCK_BootToXxxMode. In FBE/FBI/FEE/FBE mode, the PLL could
 *        be enabled independently, call CLOCK_EnablePll0 explicitly in this case.
 *
 * 4. Call CLOCK_SetSimConfig to set the clock configuration in SIM.
 */

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v6.0
processor: MK66FX1M0xxx18
package_id: MK66FX1M0VLQ18
mcu_data: ksdk2_0
processor_version: 6.0.1
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

#include "fsl_smc.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MCG_IRCLK_DISABLE                                 0U  /*!< MCGIRCLK disabled */
#define MCG_PLL_DISABLE                                   0U  /*!< MCGPLLCLK disabled */
#define OSC_CAP0P                                         0U  /*!< Oscillator 0pF capacitor load */
#define OSC_ER_CLK_DISABLE                                0U  /*!< Disable external reference clock */
#define SIM_OSC32KSEL_OSC32KCLK_CLK                       0U  /*!< OSC32KSEL select: OSC32KCLK clock */
#define SIM_PLLFLLSEL_MCGFLLCLK_CLK                       0U  /*!< PLLFLL select: MCGFLLCLK clock */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_SetFllExtRefDiv
 * Description   : Configure FLL external reference divider (FRDIV).
 * Param frdiv   : The value to set FRDIV.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_SetFllExtRefDiv(uint8_t frdiv)
{
    MCG->C1 = ((MCG->C1 & ~MCG_C1_FRDIV_MASK) | MCG_C1_FRDIV(frdiv));
}

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
}

/*******************************************************************************
 ********************* Configuration RTECLK_HsRun_180MHz ***********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: RTECLK_HsRun_180MHz
outputs:
- {id: Bus_clock.outFreq, value: 60 MHz}
- {id: Core_clock.outFreq, value: 180 MHz}
- {id: Flash_clock.outFreq, value: 22.5 MHz}
- {id: FlexBus_clock.outFreq, value: 60 MHz}
- {id: LPO_clock.outFreq, value: 1 kHz}
- {id: MCGFFCLK.outFreq, value: 12.5 MHz}
- {id: System_clock.outFreq, value: 180 MHz}
settings:
- {id: MCGMode, value: PEE}
- {id: powerMode, value: HSRUN}
- {id: MCG.FRDIV.scale, value: '4', locked: true}
- {id: MCG.IREFS.sel, value: MCG.FRDIV}
- {id: MCG.PLLS.sel, value: MCG.PLLCS}
- {id: MCG.PRDIV.scale, value: '5', locked: true}
- {id: MCG.VDIV.scale, value: '36', locked: true}
- {id: SIM.OUTDIV1.scale, value: '1', locked: true}
- {id: SIM.OUTDIV2.scale, value: '3'}
- {id: SIM.OUTDIV3.scale, value: '3', locked: true}
- {id: SIM.OUTDIV4.scale, value: '8', locked: true}
sources:
- {id: OSC.OSC.outFreq, value: 50 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for RTECLK_HsRun_180MHz configuration
 ******************************************************************************/
const mcg_config_t mcgConfig_RTECLK_HsRun_180MHz =
    {
        .mcgMode = kMCG_ModePEE,                  /* PEE - PLL Engaged External */
        .irclkEnableMode = MCG_IRCLK_DISABLE,     /* MCGIRCLK disabled */
        .ircs = kMCG_IrcSlow,                     /* Slow internal reference clock selected */
        .fcrdiv = 0x1U,                           /* Fast IRC divider: divided by 2 */
        .frdiv = 0x2U,                            /* FLL reference clock divider: divided by 4 */
        .drs = kMCG_DrsLow,                       /* Low frequency range */
        .dmx32 = kMCG_Dmx32Default,               /* DCO has a default range of 25% */
        .oscsel = kMCG_OscselOsc,                 /* Selects System Oscillator (OSCCLK) */
        .pll0Config =
            {
                .enableMode = MCG_PLL_DISABLE,    /* MCGPLLCLK disabled */
                .prdiv = 0x4U,                    /* PLL Reference divider: divided by 5 */
                .vdiv = 0x14U,                    /* VCO divider: multiplied by 36 */
            },
        .pllcs = kMCG_PllClkSelPll0,              /* PLL0 output clock is selected */
    };
const sim_clock_config_t simConfig_RTECLK_HsRun_180MHz =
    {
        .pllFllSel = SIM_PLLFLLSEL_MCGFLLCLK_CLK, /* PLLFLL select: MCGFLLCLK clock */
        .pllFllDiv = 0,                           /* PLLFLLSEL clock divider divisor: divided by 1 */
        .pllFllFrac = 0,                          /* PLLFLLSEL clock divider fraction: multiplied by 1 */
        .er32kSrc = SIM_OSC32KSEL_OSC32KCLK_CLK,  /* OSC32KSEL select: OSC32KCLK clock */
        .clkdiv1 = 0x2270000U,                    /* SIM_CLKDIV1 - OUTDIV1: /1, OUTDIV2: /3, OUTDIV3: /3, OUTDIV4: /8 */
    };
const osc_config_t oscConfig_RTECLK_HsRun_180MHz =
    {
        .freq = 50000000U,                        /* Oscillator frequency: 50000000Hz */
        .capLoad = (OSC_CAP0P),                   /* Oscillator capacity load: 0pF */
        .workMode = kOSC_ModeExt,                 /* Use external clock */
        .oscerConfig =
            {
                .enableMode = OSC_ER_CLK_DISABLE, /* Disable external reference clock */
                .erclkDiv = 0,                    /* Divider for OSCERCLK: divided by 1 */
            }
    };

/*******************************************************************************
 * Code for RTECLK_HsRun_180MHz configuration
 ******************************************************************************/
void RTECLK_HsRun_180MHz(void)
{
    /* Set HSRUN power mode */
//    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
//    SMC_SetPowerModeHsrun(SMC);
//    while (SMC_GetPowerModeState(SMC) != kSMC_PowerStateHsrun)
//    {
//    }
//    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_SetSimSafeDivs();
    /* Initializes OSC0 according to board configuration. */
    CLOCK_InitOsc0(&oscConfig_RTECLK_HsRun_180MHz);
    CLOCK_SetXtal0Freq(oscConfig_RTECLK_HsRun_180MHz.freq);
    /* Configure FLL external reference divider (FRDIV). */
    CLOCK_CONFIG_SetFllExtRefDiv(mcgConfig_RTECLK_HsRun_180MHz.frdiv);
    /* Set MCG to PEE mode. */
    CLOCK_BootToPeeMode(mcgConfig_RTECLK_HsRun_180MHz.oscsel,
                        mcgConfig_RTECLK_HsRun_180MHz.pllcs,
                        &mcgConfig_RTECLK_HsRun_180MHz.pll0Config);
    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_RTECLK_HsRun_180MHz);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = RTECLK_HSRUN_180MHZ_CORE_CLOCK;
}

/*******************************************************************************
 ********************* Configuration RTECLK_MsRun_120MHz ***********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: RTECLK_MsRun_120MHz
outputs:
- {id: Bus_clock.outFreq, value: 60 MHz}
- {id: Core_clock.outFreq, value: 120 MHz}
- {id: Flash_clock.outFreq, value: 24 MHz}
- {id: FlexBus_clock.outFreq, value: 60 MHz}
- {id: LPO_clock.outFreq, value: 1 kHz}
- {id: MCGFFCLK.outFreq, value: 12.5 MHz}
- {id: System_clock.outFreq, value: 120 MHz}
settings:
- {id: MCGMode, value: PEE}
- {id: MCG.FRDIV.scale, value: '4', locked: true}
- {id: MCG.IREFS.sel, value: MCG.FRDIV}
- {id: MCG.PLLS.sel, value: MCG.PLLCS}
- {id: MCG.PRDIV.scale, value: '5', locked: true}
- {id: MCG.VDIV.scale, value: '24', locked: true}
- {id: SIM.OUTDIV2.scale, value: '2'}
- {id: SIM.OUTDIV4.scale, value: '5', locked: true}
sources:
- {id: OSC.OSC.outFreq, value: 50 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for RTECLK_MsRun_120MHz configuration
 ******************************************************************************/
const mcg_config_t mcgConfig_RTECLK_MsRun_120MHz =
    {
        .mcgMode = kMCG_ModePEE,                  /* PEE - PLL Engaged External */
        .irclkEnableMode = MCG_IRCLK_DISABLE,     /* MCGIRCLK disabled */
        .ircs = kMCG_IrcSlow,                     /* Slow internal reference clock selected */
        .fcrdiv = 0x1U,                           /* Fast IRC divider: divided by 2 */
        .frdiv = 0x2U,                            /* FLL reference clock divider: divided by 4 */
        .drs = kMCG_DrsLow,                       /* Low frequency range */
        .dmx32 = kMCG_Dmx32Default,               /* DCO has a default range of 25% */
        .oscsel = kMCG_OscselOsc,                 /* Selects System Oscillator (OSCCLK) */
        .pll0Config =
            {
                .enableMode = MCG_PLL_DISABLE,    /* MCGPLLCLK disabled */
                .prdiv = 0x4U,                    /* PLL Reference divider: divided by 5 */
                .vdiv = 0x8U,                     /* VCO divider: multiplied by 24 */
            },
        .pllcs = kMCG_PllClkSelPll0,              /* PLL0 output clock is selected */
    };
const sim_clock_config_t simConfig_RTECLK_MsRun_120MHz =
    {
        .pllFllSel = SIM_PLLFLLSEL_MCGFLLCLK_CLK, /* PLLFLL select: MCGFLLCLK clock */
        .pllFllDiv = 0,                           /* PLLFLLSEL clock divider divisor: divided by 1 */
        .pllFllFrac = 0,                          /* PLLFLLSEL clock divider fraction: multiplied by 1 */
        .er32kSrc = SIM_OSC32KSEL_OSC32KCLK_CLK,  /* OSC32KSEL select: OSC32KCLK clock */
        .clkdiv1 = 0x1140000U,                    /* SIM_CLKDIV1 - OUTDIV1: /1, OUTDIV2: /2, OUTDIV3: /2, OUTDIV4: /5 */
    };
const osc_config_t oscConfig_RTECLK_MsRun_120MHz =
    {
        .freq = 50000000U,                        /* Oscillator frequency: 50000000Hz */
        .capLoad = (OSC_CAP0P),                   /* Oscillator capacity load: 0pF */
        .workMode = kOSC_ModeExt,                 /* Use external clock */
        .oscerConfig =
            {
                .enableMode = OSC_ER_CLK_DISABLE, /* Disable external reference clock */
                .erclkDiv = 0,                    /* Divider for OSCERCLK: divided by 1 */
            }
    };

/*******************************************************************************
 * Code for RTECLK_MsRun_120MHz configuration
 ******************************************************************************/
void RTECLK_MsRun_120MHz(void)
{
    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_SetSimSafeDivs();
    /* Initializes OSC0 according to board configuration. */
    CLOCK_InitOsc0(&oscConfig_RTECLK_MsRun_120MHz);
    CLOCK_SetXtal0Freq(oscConfig_RTECLK_MsRun_120MHz.freq);
    /* Configure FLL external reference divider (FRDIV). */
    CLOCK_CONFIG_SetFllExtRefDiv(mcgConfig_RTECLK_MsRun_120MHz.frdiv);
    /* Set MCG to PEE mode. */
    CLOCK_BootToPeeMode(mcgConfig_RTECLK_MsRun_120MHz.oscsel,
                        mcgConfig_RTECLK_MsRun_120MHz.pllcs,
                        &mcgConfig_RTECLK_MsRun_120MHz.pll0Config);
    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_RTECLK_MsRun_120MHz);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = RTECLK_MSRUN_120MHZ_CORE_CLOCK;
}

/*******************************************************************************
 ********************* Configuration RTECLK_LpRun_060MHz ***********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: RTECLK_LpRun_060MHz
outputs:
- {id: Bus_clock.outFreq, value: 60 MHz, locked: true, accuracy: '0.001'}
- {id: Core_clock.outFreq, value: 60 MHz, locked: true, accuracy: '0.001'}
- {id: Flash_clock.outFreq, value: 20 MHz}
- {id: FlexBus_clock.outFreq, value: 60 MHz}
- {id: LPO_clock.outFreq, value: 1 kHz}
- {id: MCGFFCLK.outFreq, value: 12.5 MHz}
- {id: System_clock.outFreq, value: 60 MHz}
settings:
- {id: MCGMode, value: PEE}
- {id: MCG.FRDIV.scale, value: '4', locked: true}
- {id: MCG.IRCS.sel, value: MCG.FCRDIV}
- {id: MCG.IREFS.sel, value: MCG.FRDIV}
- {id: MCG.PLLS.sel, value: MCG.PLLCS}
- {id: MCG.PRDIV.scale, value: '5'}
- {id: MCG.VDIV.scale, value: '24'}
- {id: MCG_C5_PLLCLKEN0_CFG, value: Enabled}
- {id: MCG_C5_PLLSTEN0_CFG, value: Enabled}
- {id: SIM.OUTDIV1.scale, value: '2'}
- {id: SIM.OUTDIV2.scale, value: '2'}
- {id: SIM.OUTDIV4.scale, value: '6', locked: true}
sources:
- {id: OSC.OSC.outFreq, value: 50 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for RTECLK_LpRun_060MHz configuration
 ******************************************************************************/
const mcg_config_t mcgConfig_RTECLK_LpRun_060MHz =
    {
        .mcgMode = kMCG_ModePEE,                  /* PEE - PLL Engaged External */
        .irclkEnableMode = MCG_IRCLK_DISABLE,     /* MCGIRCLK disabled */
        .ircs = kMCG_IrcFast,                     /* Fast internal reference clock selected */
        .fcrdiv = 0x1U,                           /* Fast IRC divider: divided by 2 */
        .frdiv = 0x2U,                            /* FLL reference clock divider: divided by 4 */
        .drs = kMCG_DrsLow,                       /* Low frequency range */
        .dmx32 = kMCG_Dmx32Default,               /* DCO has a default range of 25% */
        .oscsel = kMCG_OscselOsc,                 /* Selects System Oscillator (OSCCLK) */
        .pll0Config =
            {
                .enableMode = kMCG_PllEnableIndependent | kMCG_PllEnableInStop,/* MCGPLLCLK enabled independently of MCG clock mode as well as in STOP mode */
                .prdiv = 0x4U,                    /* PLL Reference divider: divided by 5 */
                .vdiv = 0x8U,                     /* VCO divider: multiplied by 24 */
            },
        .pllcs = kMCG_PllClkSelPll0,              /* PLL0 output clock is selected */
    };
const sim_clock_config_t simConfig_RTECLK_LpRun_060MHz =
    {
        .pllFllSel = SIM_PLLFLLSEL_MCGFLLCLK_CLK, /* PLLFLL select: MCGFLLCLK clock */
        .pllFllDiv = 0,                           /* PLLFLLSEL clock divider divisor: divided by 1 */
        .pllFllFrac = 0,                          /* PLLFLLSEL clock divider fraction: multiplied by 1 */
        .er32kSrc = SIM_OSC32KSEL_OSC32KCLK_CLK,  /* OSC32KSEL select: OSC32KCLK clock */
        .clkdiv1 = 0x11150000U,                   /* SIM_CLKDIV1 - OUTDIV1: /2, OUTDIV2: /2, OUTDIV3: /2, OUTDIV4: /6 */
    };
const osc_config_t oscConfig_RTECLK_LpRun_060MHz =
    {
        .freq = 50000000U,                        /* Oscillator frequency: 50000000Hz */
        .capLoad = (OSC_CAP0P),                   /* Oscillator capacity load: 0pF */
        .workMode = kOSC_ModeExt,                 /* Use external clock */
        .oscerConfig =
            {
                .enableMode = OSC_ER_CLK_DISABLE, /* Disable external reference clock */
                .erclkDiv = 0,                    /* Divider for OSCERCLK: divided by 1 */
            }
    };

/*******************************************************************************
 * Code for RTECLK_LpRun_060MHz configuration
 ******************************************************************************/
void RTECLK_LpRun_060MHz(void)
{
    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_SetSimSafeDivs();
    /* Initializes OSC0 according to board configuration. */
    CLOCK_InitOsc0(&oscConfig_RTECLK_LpRun_060MHz);
    CLOCK_SetXtal0Freq(oscConfig_RTECLK_LpRun_060MHz.freq);
    /* Configure FLL external reference divider (FRDIV). */
    CLOCK_CONFIG_SetFllExtRefDiv(mcgConfig_RTECLK_LpRun_060MHz.frdiv);
    /* Set MCG to PEE mode. */
    CLOCK_BootToPeeMode(mcgConfig_RTECLK_LpRun_060MHz.oscsel,
                        mcgConfig_RTECLK_LpRun_060MHz.pllcs,
                        &mcgConfig_RTECLK_LpRun_060MHz.pll0Config);
    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_RTECLK_LpRun_060MHz);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = RTECLK_LPRUN_060MHZ_CORE_CLOCK;
}

