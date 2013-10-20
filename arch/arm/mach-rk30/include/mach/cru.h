#ifndef __MACH_CRU_H
#define __MACH_CRU_H

enum rk_plls_id {
	APLL_ID = 0,
	DPLL_ID,
	CPLL_ID,
	GPLL_ID,
	END_PLL_ID,
};

/*****cru reg offset*****/

#define CRU_MODE_CON		0x40
#define CRU_CLKSEL_CON		0x44
#define CRU_CLKGATE_CON		0xd0
#define CRU_GLB_SRST_FST	0x100
#define CRU_GLB_SRST_SND	0x104
#define CRU_SOFTRST_CON		0x110

#define PLL_CONS(id, i)		((id) * 0x10 + ((i) * 4))

#define CRU_CLKSELS_CON_CNT	(35)
#define CRU_CLKSELS_CON(i)	(CRU_CLKSEL_CON + ((i) * 4))

#define CRU_CLKGATES_CON_CNT	(10)
#define CRU_CLKGATES_CON(i)	(CRU_CLKGATE_CON + ((i) * 4))

#define CRU_SOFTRSTS_CON_CNT	(9)
#define CRU_SOFTRSTS_CON(i)	(CRU_SOFTRST_CON + ((i) * 4))

#define CRU_MISC_CON		(0x134)
#define CRU_GLB_CNT_TH		(0x140)

/********************************************************************/
#define CRU_GET_REG_BIYS_VAL(reg,bits_shift, msk)	(((reg) >> (bits_shift))&(msk))
#define CRU_W_MSK(bits_shift, msk)	((msk) << ((bits_shift) + 16))
#define CRU_SET_BITS(val,bits_shift, msk)	(((val)&(msk)) << (bits_shift))

#define CRU_W_MSK_SETBITS(val,bits_shift,msk) (CRU_W_MSK(bits_shift, msk)|CRU_SET_BITS(val,bits_shift, msk))

/*******************PLL CON0 BITS***************************/

#define PLL_CLKFACTOR_SET(val, shift, msk) \
	((((val) - 1) & (msk)) << (shift))

#define PLL_CLKFACTOR_GET(reg, shift, msk) \
	((((reg) >> (shift)) & (msk)) + 1)

#define PLL_OD_MSK		(0xf)
#define PLL_OD_SHIFT (0x0)

#define PLL_CLKOD(val)		PLL_CLKFACTOR_SET(val, PLL_OD_SHIFT, PLL_OD_MSK)
#define PLL_NO(reg)		PLL_CLKFACTOR_GET(reg, PLL_OD_SHIFT, PLL_OD_MSK)

#define PLL_NO_SHIFT(reg)	PLL_CLKFACTOR_GET(reg, PLL_OD_SHIFT, PLL_OD_MSK)

#define PLL_CLKOD_SET(val)	(PLL_CLKOD(val) | CRU_W_MSK(PLL_OD_SHIFT, PLL_OD_MSK))

#define PLL_NR_MSK		(0x3f)
#define PLL_NR_SHIFT		(8)
#define PLL_CLKR(val)		PLL_CLKFACTOR_SET(val, PLL_NR_SHIFT, PLL_NR_MSK)
#define PLL_NR(reg)		PLL_CLKFACTOR_GET(reg, PLL_NR_SHIFT, PLL_NR_MSK)

#define PLL_CLKR_SET(val)	(PLL_CLKR(val) | CRU_W_MSK(PLL_NR_SHIFT, PLL_NR_MSK))

/*******************PLL CON1 BITS***************************/

#define PLL_NF_MSK		(0x1fff)
#define PLL_NF_SHIFT		(0)
#define PLL_CLKF(val)		PLL_CLKFACTOR_SET(val, PLL_NF_SHIFT, PLL_NF_MSK)
#define PLL_NF(reg)		PLL_CLKFACTOR_GET(reg, PLL_NF_SHIFT, PLL_NF_MSK)

#define PLL_CLKF_SET(val)	(PLL_CLKF(val) | CRU_W_MSK(PLL_NF_SHIFT, PLL_NF_MSK))

/*******************PLL CON2 BITS***************************/

#define PLL_BWADJ_MSK		(0xfff)
#define PLL_BWADJ_SHIFT		(0)
#define PLL_CLK_BWADJ_SET(val)	((val) | CRU_W_MSK(PLL_BWADJ_SHIFT, PLL_BWADJ_MSK))

/*******************PLL CON3 BITS***************************/

#define PLL_REST_MSK		(1 << 5)
#define PLL_REST_W_MSK		(PLL_REST_MSK << 16)
#define PLL_REST		(1 << 5)
#define PLL_REST_RESM		(0 << 5)

#define PLL_BYPASS_MSK		(1 << 0)
#define PLL_BYPASS		(1 << 0)
#define PLL_NO_BYPASS		(0 << 0)

#define PLL_PWR_DN_MSK		(1 << 1)
#define PLL_PWR_DN_W_MSK	(PLL_PWR_DN_MSK << 16)
#define PLL_PWR_DN		(1 << 1)
#define PLL_PWR_ON		(0 << 1)

/*******************CLKSEL0 BITS***************************/
//core preiph div
#define CORE_PERIPH_W_MSK	(3 << 22)
#define CORE_PERIPH_MSK		(3 << 6)
#define CORE_PERIPH_2		(0 << 6)
#define CORE_PERIPH_4		(1 << 6)
#define CORE_PERIPH_8		(2 << 6)
#define CORE_PERIPH_16		(3 << 6)
//arm clk pll sel
#define CORE_SEL_PLL_MSK	(1 << 8)
#define CORE_SEL_PLL_W_MSK	(1 << 24)
#define CORE_SEL_APLL		(0 << 8)
#define CORE_SEL_GPLL		(1 << 8)

#define CORE_CLK_DIV_W_MSK	(0x1F << 16)
#define CORE_CLK_DIV_MSK	(0x1F)
#define CORE_CLK_DIV(i)		(((i) - 1) & 0x1F)

/*******************CLKSEL1 BITS***************************/
//aclk div

#define GET_CORE_ACLK_VAL(reg) ((reg)>=4 ?8:((reg)+1))

#define CORE_ACLK_W_MSK		(7 << 16)
#define CORE_ACLK_MSK		(7 << 0)
#define CORE_ACLK_11		(0 << 0)
#define CORE_ACLK_21		(1 << 0)
#define CORE_ACLK_31		(2 << 0)
#define CORE_ACLK_41		(3 << 0)
#define CORE_ACLK_81		(4 << 0)

//hclk div
#define ACLK_HCLK_W_MSK		(3 << 24)
#define ACLK_HCLK_MSK		(3 << 8)
#define ACLK_HCLK_11		(0 << 8)
#define ACLK_HCLK_21		(1 << 8)
#define ACLK_HCLK_41		(2 << 8)
// pclk div
#define ACLK_PCLK_W_MSK		(3 << 28)
#define ACLK_PCLK_MSK		(3 << 12)
#define ACLK_PCLK_11		(0 << 12)
#define ACLK_PCLK_21		(1 << 12)
#define ACLK_PCLK_41		(2 << 12)
#define ACLK_PCLK_81		(3 << 12)
// ahb2apb div
#define AHB2APB_W_MSK		(3 << 30)
#define AHB2APB_MSK			(3 << 14)
#define AHB2APB_11			(0 << 14)
#define AHB2APB_21			(1 << 14)
#define AHB2APB_41			(2 << 14)

/*******************MODE BITS***************************/

#define PLL_MODE_MSK(id)	(0x3 << ((id) * 4))
#define PLL_MODE_SLOW(id)	((0x0<<((id)*4))|(0x3<<(16+(id)*4)))
#define PLL_MODE_NORM(id)	((0x1<<((id)*4))|(0x3<<(16+(id)*4)))
#define PLL_MODE_DEEP(id)	((0x2<<((id)*4))|(0x3<<(16+(id)*4)))

/*******************clksel10***************************/

#define PERI_ACLK_DIV_MASK 0x1f
#define PERI_ACLK_DIV_OFF 0

#define PERI_HCLK_DIV_MASK 0x3
#define PERI_HCLK_DIV_OFF 8

#define PERI_PCLK_DIV_MASK 0x3
#define PERI_PCLK_DIV_OFF 12

/*******************gate BITS***************************/

#define CLK_GATE_CLKID(i)	(16 * (i))
#define CLK_GATE_CLKID_CONS(i)	CRU_CLKGATES_CON((i) / 16)

#define CLK_GATE(i)		(1 << ((i)%16))
#define CLK_UN_GATE(i)		(0)

#define CLK_GATE_W_MSK(i)	(1 << (((i) % 16) + 16))

enum cru_clk_gate {
	/* SCU CLK GATE 0 CON */
	CLK_GATE_CORE_PERIPH = CLK_GATE_CLKID(0),
	CLK_GATE_CPU_GPLL_PATH,
	CLK_GATE_DDRPHY,
	CLK_GATE_ACLK_CPU,
	CLK_GATE_HCLK_CPU,
	CLK_GATE_PCLK_CPU,
	CLK_GATE_ATCLK_CPU,
	CLK_GATE_I2S0,
	CLK_GATE_I2S0_FRAC,
	CLK_GATE_I2S1,
	CLK_GATE_I2S1_FRAC,
	CLK_GATE_I2S2,
	CLK_GATE_I2S2_FRAC,
	CLK_GATE_SPDIF,
	CLK_GATE_SPDIF_FRAC,
	CLK_GATE_TESTCLK,

	CLK_GATE_TIMER0 = CLK_GATE_CLKID(1),
	CLK_GATE_TIMER1,
	CLK_GATE_TIMER2,
	CLK_GATE_JTAG,
	CLK_GATE_ACLK_LCDC1_SRC,
	CLK_GATE_OTGPHY0,
	CLK_GATE_OTGPHY1,
	CLK_GATE_DDR_GPLL,
	CLK_GATE_UART0,
	CLK_GATE_FRAC_UART0,
	CLK_GATE_UART1,
	CLK_GATE_FRAC_UART1,
	CLK_GATE_UART2,
	CLK_GATE_FRAC_UART2,
	CLK_GATE_UART3,
	CLK_GATE_FRAC_UART3,

	CLK_GATE_PEIRPH_SRC = CLK_GATE_CLKID(2),
	CLK_GATE_ACLK_PEIRPH,
	CLK_GATE_HCLK_PEIRPH,
	CLK_GATE_PCLK_PEIRPH,
	CLK_GATE_SMC,
	CLK_GATE_MAC,
	CLK_GATE_HSADC,
	CLK_GATE_HSADC_FRAC,
	CLK_GATE_SARADC,
	CLK_GATE_SPI0,
	CLK_GATE_SPI1,
	CLK_GATE_MMC0,
	CLK_GATE_MAC_LBTEST,
	CLK_GATE_SDIO,
	CLK_GATE_EMMC,
	CLK_GATE_TSADC,

	CLK_GATE_ACLK_LCDC0_SRC = CLK_GATE_CLKID(3),
	CLK_GATE_DCLK_LCDC0,
	CLK_GATE_DCLK_LCDC1,
	CLK_GATE_PCLKIN_CIF0,
	CLK_GATE_PCLKIN_CIF1,
	CLK_GATE3_RES5,
	CLK_GATE3_RES6,
	CLK_GATE_CIF0_OUT,
	CLK_GATE_CIF1_OUT,
	CLK_GATE_ACLK_VEPU,
	CLK_GATE_HCLK_VEPU,
	CLK_GATE_ACLK_VDPU,
	CLK_GATE_HCLK_VDPU,
	CLK_GATE_GPU_SRC,
	CLK_GATE3_RES14,
	CLK_GATE_XIN27M,

	CLK_GATE_HCLK_PERI_AXI_MATRIX = CLK_GATE_CLKID(4),
	CLK_GATE_PCLK_PERI_AXI_MATRIX,
	CLK_GATE_ACLK_CPU_PERI,
	CLK_GATE_ACLK_PERI_AXI_MATRIX,
	CLK_GATE_ACLK_PEI_NIU,
	CLK_GATE_HCLK_USB_PERI,
	CLK_GATE_HCLK_PERI_AHB_ARBI,
	CLK_GATE_HCLK_EMEM_PERI,
	CLK_GATE_HCLK_CPUBUS,
	CLK_GATE_HCLK_AHB2APB,
	CLK_GATE_ACLK_STRC_SYS,
	CLK_GATE_ACLK_L2MEM_CON,
	CLK_GATE_ACLK_INTMEM,
	CLK_GATE_PCLK_TSADC,
	CLK_GATE_HCLK_HDMI,

	CLK_GATE_ACLK_DMAC1 = CLK_GATE_CLKID(5),
	CLK_GATE_ACLK_DMAC2,
	CLK_GATE_PCLK_EFUSE,
	CLK_GATE_PCLK_TZPC,
	CLK_GATE_PCLK_GRF,
	CLK_GATE_PCLK_PMU,
	CLK_GATE_HCLK_ROM,
	CLK_GATE_PCLK_DDRUPCTL,
	CLK_GATE_ACLK_SMC,
	CLK_GATE_HCLK_NANDC,
	CLK_GATE_HCLK_SDMMC0,
	CLK_GATE_HCLK_SDIO,
	CLK_GATE_HCLK_EMMC,
	CLK_GATE_HCLK_OTG0,
	CLK_GATE_HCLK_OTG1,
	CLK_GATE_ACLK_GPU,

	CLK_GATE_ACLK_LCDC0 = CLK_GATE_CLKID(6),
	CLK_GATE_HCLK_LCDC0,
	CLK_GATE_HCLK_LCDC1,
	CLK_GATE_ACLK_LCDC1,
	CLK_GATE_HCLK_CIF0,
	CLK_GATE_ACLK_CIF0,
	CLK_GATE_HCLK_CIF1,
	CLK_GATE_ACLK_CIF1,
	CLK_GATE_ACLK_IPP,
	CLK_GATE_HCLK_IPP,
	CLK_GATE_HCLK_RGA,
	CLK_GATE_ACLK_RGA,
	CLK_GATE_HCLK_VIO_BUS,
	CLK_GATE_ACLK_VIO0,
	CLK_GATE_ACLK_VCODEC,
	CLK_GATE_SHCLK_VIO_H2H,

	CLK_GATE_HCLK_EMAC = CLK_GATE_CLKID(7),
	CLK_GATE_HCLK_SPDIF,
	CLK_GATE_HCLK_I2S0_2CH,
	CLK_GATE_HCLK_I2S1_2CH,
	CLK_GATE_HCLK_I2S_8CH,
	CLK_GATE_HCLK_HSADC,
	CLK_GATE_HCLK_PIDF,
	CLK_GATE_PCLK_TIMER0,
	CLK_GATE_PCLK_TIMER1,
	CLK_GATE_PCLK_TIMER2,
	CLK_GATE_PCLK_PWM01,
	CLK_GATE_PCLK_PWM23,
	CLK_GATE_PCLK_SPI0,
	CLK_GATE_PCLK_SPI1,
	CLK_GATE_PCLK_SARADC,
	CLK_GATE_PCLK_WDT,

	CLK_GATE_PCLK_UART0 = CLK_GATE_CLKID(8),
	CLK_GATE_PCLK_UART1,
	CLK_GATE_PCLK_UART2,
	CLK_GATE_PCLK_UART3,
	CLK_GATE_PCLK_I2C0,
	CLK_GATE_PCLK_I2C1,
	CLK_GATE_PCLK_I2C2,
	CLK_GATE_PCLK_I2C3,
	CLK_GATE_PCLK_I2C4,
	CLK_GATE_PCLK_GPIO0,
	CLK_GATE_PCLK_GPIO1,
	CLK_GATE_PCLK_GPIO2,
	CLK_GATE_PCLK_GPIO3,
	CLK_GATE_PCLK_GPIO4,
	CLK_GATE8_RES14,
	CLK_GATE_PCLK_GPIO6,

	CLK_GATE_CLK_CORE_DBG = CLK_GATE_CLKID(9),
	CLK_GATE_PCLK_DBG,
	CLK_GATE_CLK_TRACE,
	CLK_GATE_ATCLK,
	CLK_GATE_CLK_L2C,
	CLK_GATE_ACLK_VIO1,
	CLK_GATE_PCLK_PUBL,
	CLK_GATE_ACLK_INTMEM0,
	CLK_GATE_ACLK_INTMEM1,
	CLK_GATE_ACLK_INTMEM2,
	CLK_GATE_ACLK_INTMEM3,

	CLK_GATE_MAX,
};

#define SOFT_RST_ID(i)		(16 * (i))

enum cru_soft_reset {
	SOFT_RST_GLB1 = SOFT_RST_ID(0),
	SOFT_RST_GLB2,
	SOFT_RST_MCORE,
	SOFT_RST_CORE0,
	SOFT_RST_CORE1,
	SOFT_RST_0RES5,
	SOFT_RST_0RES6,
	SOFT_RST_MCORE_DBG,
	SOFT_RST_CORE0_DBG,
	SOFT_RST_CORE1_DBG,
	SOFT_RST_0RES10,
	SOFT_RST_0RES11,
	SOFT_RST_CORE0_WDT,
	SOFT_RST_CORE1_WDT,
	SOFT_RST_STRC_SYS_AXI,
	SOFT_RST_L2C,

	SOFT_RST_1RES0 = SOFT_RST_ID(1),
	SOFT_RST_CPUSYS_AHB,
	SOFT_RST_L2MEM_CON_AXI,
	SOFT_RST_AHB2APB,
	SOFT_RST_DMA0,
	SOFT_RST_INTMEM,
	SOFT_RST_ROM,
	SOFT_RST_I2S0,
	SOFT_RST_I2S1,
	SOFT_RST_I2S2,
	SOFT_RST_SPDIF,
	SOFT_RST_TIMER0,
	SOFT_RST_TIMER1,
	SOFT_RST_TIMER2,
	SOFT_RST_EFUSE_APB,

	SOFT_RST_GPIO0 = SOFT_RST_ID(2),
	SOFT_RST_GPIO1,
	SOFT_RST_GPIO2,
	SOFT_RST_GPIO3,
	SOFT_RST_GPIO4,
	SOFT_RST_2RES5,
	SOFT_RST_GPIO6,
	SOFT_RST_UART0,
	SOFT_RST_UART1,
	SOFT_RST_UART2,
	SOFT_RST_UART3,
	SOFT_RST_I2C0,
	SOFT_RST_I2C1,
	SOFT_RST_I2C2,
	SOFT_RST_I2C3,
	SOFT_RST_I2C4,

	SOFT_RST_PWM0 = SOFT_RST_ID(3),
	SOFT_RST_PWM1,
	SOFT_RST_DAP_PO,
	SOFT_RST_DAP,
	SOFT_RST_DAP_SYS,
	SOFT_RST_TPIU_ATB,
	SOFT_RST_PMU_APB,
	SOFT_RST_GRF,
	SOFT_RST_PMU,
	SOFT_RST_PERIPHSYS_AXI,
	SOFT_RST_PERIPHSYS_AHB,
	SOFT_RST_PERIPHSYS_APB,
	SOFT_RST_PERIPH_NIU,
	SOFT_RST_CPU_PERI,
	SOFT_RST_EMEM_PERI,
	SOFT_RST_USB_PERI,

	SOFT_RST_DMA1 = SOFT_RST_ID(4),
	SOFT_RST_SMC,
	SOFT_RST_MAC,
	SOFT_RST_4RES3,
	SOFT_RST_NANDC,
	SOFT_RST_USBOTG0,
	SOFT_RST_USBPHY0,
	SOFT_RST_OTGC0,
	SOFT_RST_USBOTG1,
	SOFT_RST_USBPHY1,
	SOFT_RST_OTGC1,
	SOFT_RST_4RES11,
	SOFT_RST_HSADC,
	SOFT_RST_PIDFILTER,
	SOFT_RST_4RES14,
	SOFT_RST_DDRMSCH,

	SOFT_RST_TZPC = SOFT_RST_ID(5),
	SOFT_RST_MMC0,
	SOFT_RST_SDIO,
	SOFT_RST_EMMC,
	SOFT_RST_SPI0,
	SOFT_RST_SPI1,
	SOFT_RST_WDT,
	SOFT_RST_SARADC,
	SOFT_RST_DDRPHY,
	SOFT_RST_DDRPHY_APB,
	SOFT_RST_DDRCTRL,
	SOFT_RST_DDRCTRL_APB,
	SOFT_RST_TSADC,
	SOFT_RST_DDRPHY_CTL,

	SOFT_RST_HDMI = SOFT_RST_ID(6),
	SOFT_RST_HDMI_AHB,
	SOFT_RST_VIO0_AXI,
	SOFT_RST_VIO_BUS_AHB,
	SOFT_RST_LCDC0_AXI,
	SOFT_RST_LCDC0_AHB,
	SOFT_RST_LCDC0_DCLK,
	SOFT_RST_LCDC1_AXI,
	SOFT_RST_LCDC1_AHB,
	SOFT_RST_LCDC1_DCLK,
	SOFT_RST_IPP_AXI,
	SOFT_RST_IPP_AHB,
	SOFT_RST_RGA_AXI,
	SOFT_RST_RGA_AHB,
	SOFT_RST_CIF0,
	SOFT_RST_CIF1,

	SOFT_RST_VCODEC_AXI = SOFT_RST_ID(7),
	SOFT_RST_VCODEC_AHB,
	SOFT_RST_VIO1_AXI,
	SOFT_RST_CPU_VCODEC,
	SOFT_RST_VCODEC_NIU_AXI,
	SOFT_RST_7RES5,
	SOFT_RST_7RES6,
	SOFT_RST_7RES7,
	SOFT_RST_GPU_AXI,
	SOFT_RST_7RES9,
	SOFT_RST_GPU_NIU_AXI,
	SOFT_RST_7RES11,
	SOFT_RST_7RES12,
	SOFT_RST_TFUN_ATB,
	SOFT_RST_TFUN_APB,
	SOFT_RST_CTI4_APB,

	SOFT_RST_TPIU_APB = SOFT_RST_ID(8),
	SOFT_RST_TRACE,
	SOFT_RST_CORE_DBG,
	SOFT_RST_DBG_APB,
	SOFT_RST_CTI0,
	SOFT_RST_CTI0_APB,
	SOFT_RST_CTI1,
	SOFT_RST_CTI1_APB,
	SOFT_RST_PTM_CORE0,
	SOFT_RST_PTM_CORE1,
	SOFT_RST_PTM0,
	SOFT_RST_PTM0_ATB,
	SOFT_RST_PTM1,
	SOFT_RST_PTM1_ATB,
	SOFT_RST_CTM,
	SOFT_RST_TS,

	SOFT_RST_MAX,
};

/*****cru reg end*****/

static inline void cru_set_soft_reset(enum cru_soft_reset idx, bool on)
{
	const void __iomem *reg = RK30_CRU_BASE + CRU_SOFTRSTS_CON(idx >> 4);
	u32 val = on ? 0x10001U << (idx & 0xf) : 0x10000U << (idx & 0xf);
	writel_relaxed(val, reg);
	dsb();
}

#endif
