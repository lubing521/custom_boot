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

#define READ_FLAG
#define WRITE_FLAG

#define START_FLAG	1
#define STOP_FLAG	0

int i2c_start_stop(int flag)
{
	unsigned char val;
	
	val = SYSREG_R(IIC0STAT);
	if (flag == START_FLAG)
		val |= (0x1 << 5);
	else
		val &= ~(0x1 << 5);

	SYSREG_W(IIC0STAT, val);
}

int i2c_read(unsigned char chip, unsigned char addr, int alen,
		unsigned char *buff, int len)
{
	int count;
	int i = 0;
	unsigned char val;

	i2c_start_stop(START_FLAG);
	//master reveice mode and enable tx/rx
	SYSREG_W(IIC0STAT, 0xb0);
	
	SYSREG_W(II0DS, (chip << 1) | READ_FLAG);
	i2c_wait_ack();
	
	while (i < len)  {
		buff[i] = SYSREG_R(IIC0DS);
		i2c_send_ack();

		val = SYSREG_R(IIC0STAT);
		if (!(val & (0x1 << 5)))
			goto finish;
		i++
	}

finish:
	i2c_start_stop(STOP_FLAG);
	i2c_wait_ack();

	return 0
}

int i2c_wirte(unsigned char chip, unsigned char addr, int alen,
		unsigned char *buff, int len)
{
	int count;
	unsigned char val;
	int i = 0;
	//start condition, enable rx/tx
	val = SYSREG_R(IIC0STAT);
	val |= 0xf0;
	SYSREG_W(IIC0STAT);
	
	//write slave address
	SYSREG_W((chip << 1) | WRITE_FLAG);
	i2c_wait_ack();

	while (len >= i) {
		SYSREG_W(IIC0DS, buff[i]);
		i2c_wait_ack();
		//stop?
		val = SYSREG_R(IIC0STAT);
		if (val & 0x1)
			goto finish;
		i++;

	}
	
finish:
	i2c_stop(STOP_FLAG);
	i2c_wait_ack()

	return 0
}

void i2c_init(unsigned long saddr)
{
	unsigned long val;

//	val = ((0x3 << 8) | (0x3 << 12)); //i2c1
	val = ((0x2 << 20) | (0x2 << 24)); //i2c0
	
	//select io to i2c mode 
	SYSREG_W(GPBCON, val);

	val = (1 << 7) | (0 << 6) | (1 << 5) | (0 << 4) | (0xf);
	SYSREG_W(IIC0CON, val);
}

