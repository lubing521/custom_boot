/*GPIO ADDRESS for OK6410*/
#define GPACON  	(*((volatile unsigned long *)0x7f008000))
#define GPADAT          (*((volatile unsigned long *)0x7f008004))
#define GPMCON  	(*((volatile unsigned long *)0x7F008820))
#define GPMDAT 		(*((volatile unsigned long *)0x7F008824))

/*CLOCK*/
#define APLL_LOCK       (*((volatile unsigned long *)0x7e00f000))
#define MPLL_LOCK       (*((volatile unsigned long *)0x7e00f004))
#define EPLL_LOCK       (*((volatile unsigned long *)0x7e00f008))

#define OTHERS          (*((volatile unsigned long *)0x7e00f900))

#define CLK_DIV0        (*((volatile unsigned long *)0x7e00f020))

#define APLL_CON        (*((volatile unsigned long *)0x7e00f00c))
#define MPLL_CON        (*((volatile unsigned long *)0x7e00f010))

#define APLL_VAL        ((1 << 31) | (266<< 16) | (3 << 8) | 1)
#define MPLL_VAL        ((1 << 31) | (266<< 16) | (3 << 8) | 1)
#define CLK_SRC         (*((volatile unsigned long *)0x7e00f01c))

#define ARM_RATIO       0 //532
#define MPLL_RATIO      0 //532 
#define PCLK_RATIO      3 //66M
#define HCLK_RATIO      1 //133
#define HCLKX2_RATIO    1 //266

/*DDR*/
#define P1MEMSTAT       (*((volatile unsigned long *)0x7e001000))
#define P1MEMCCMD       (*((volatile unsigned long *)0x7e001004))
#define P1DIRECTCMD     (*((volatile unsigned long *)0x7e001008))
#define P1MEMCFG        (*((volatile unsigned long *)0x7e00100c))

#define P1REFRESH       (*((volatile unsigned long *)0x7e001010))
#define P1CASLAT        (*((volatile unsigned long *)0x7e001014))
#define P1T_DQSS        (*((volatile unsigned long *)0x7e001018))
#define P1T_MRD         (*((volatile unsigned long *)0x7e00101c))
#define P1T_RAS         (*((volatile unsigned long *)0x7e001020))
#define P1T_RC          (*((volatile unsigned long *)0x7e001024))
#define P1T_RCD         (*((volatile unsigned long *)0x7e001028))
#define P1T_RFC         (*((volatile unsigned long *)0x7e00102c))
#define P1T_RP          (*((volatile unsigned long *)0x7e001030))
#define P1T_RRD         (*((volatile unsigned long *)0x7e001034))
#define P1T_WR          (*((volatile unsigned long *)0x7e001038))
#define P1T_WTR         (*((volatile unsigned long *)0x7e00103c))
#define P1T_XP          (*((volatile unsigned long *)0x7e001040))
#define P1T_XSR         (*((volatile unsigned long *)0x7e001044))
#define P1T_ESR         (*((volatile unsigned long *)0x7e001048))
#define P1MEMCFG2       (*((volatile unsigned long *)0x7e00104c))
#define p1_chip_0_cfg   (*((volatile unsigned long *)0x7e001200))
#define MEM_SYS_CFG     (*((volatile unsigned long *)0x7e00f120))

/*NAND FLASH*/
#define MEM_SYS_CFG     (*((volatile unsigned long *)0x7e00f120))
#define NFCONF          (*((volatile unsigned long *)0x70200000))

#define TACLS           0
#define TWRPH0          2 //1
#define TWRPH1          1

#define NFCONT          (*((volatile unsigned long *)0x70200004))
#define NFCMMD          (*((volatile unsigned long *)0x70200008))
#define NFADDR          (*((volatile unsigned long *)0x7020000c))
#define NFDATA          (*((volatile unsigned char *)0x70200010))

#define NFSTAT          (*((volatile unsigned long *)0x70200028))

/*UART*/
#define ULCON0          (*((volatile unsigned long *)0x7f005000))
#define UCON0           (*((volatile unsigned long *)0x7f005004))
#define UFCON0          (*((volatile unsigned long *)0x7f005008))
#define UMCON0          (*((volatile unsigned long *)0x7f00500c))
#define UBRDIV0         (*((volatile unsigned short *)0x7f005028))
#define UDIVSLOT0       (*((volatile unsigned short *)0x7f00502C))
#define UFSTAT0         (*((volatile unsigned long *)0x7f005018))
#define URXH0           (*((volatile unsigned char *)0x7f005024))
#define UTXH0           (*((volatile unsigned char *)0x7f005020))
