#define GPBCON		0X7F008020
#define GPBDAT		0x7f008024
#define GPBPUD		0x7f008028

#define II0CCON		0x7f004000
#define IIC0STAT	0x7f004004
#define IIC0ADD		0x7f004008
#define IIC0DS		0x7f00400c
#define IIC0LC		0x7f004010

#define II1CCON		0x7f00f000
#define IIC1STAT	0x7f00f004
#define IIC1ADD		0x7f00f008
#define IIC1DS		0x7f00f00c
#define IIC1LC		0x7f00f010

void i2c_read()
{
	
}

void i2c_init(void)
{
	unsigned long val;

//	val = ((0x3 << 8) | (0x3 << 12)); //i2c1
	val = ((0x2 << 20) | (0x2 << 24)); //i2c0
	
	//select io to i2c mode 
	SYSREG_W(GPBCON, val);

	val = (1 << 7) | (0 << 6) | (1 << 5) | (0 << 4) | (0xf);
	SYSREG_W(IIC0CON, val);

	SYSREG_W(IIC0STAT, 0x10);

//address???
	SYSREG_W(IIC0ADD, 0X000)
}

