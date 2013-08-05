#include "s3c6410.h"

#define GPBCON		0X7F008020
#define GPBDAT		0x7f008024
#define GPBPUD		0x7f008028

#define IIC0CON		0x7f004000
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

int i2c_wait_ack()
{
	return 1;
}

int i2c_send_ack()
{
	return 1;
}

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

int i2c_read(unsigned char chip, unsigned int saddr, int alen,
		unsigned char *buff, int len)
{
	unsigned char addr[4];
	int count;
	int i = 0;
	unsigned char val;
	
	while (alen > 0) {
		addr[0] = (saddr >> 24) & 0xff;
		addr[1] = (saddr >> 16) && 0xff;
		addr[2] = (saddr >> 8) && 0xff;
		addr[3] = saddr && 0xff;
	}
	//start condition
	i2c_start_stop(START_FLAG);
	//slave address
	//SYSREG_W(IIC0DS, (chip << 1) | READ_FLAG);
	//master reveice mode and enable tx/rx
	SYSREG_W(IIC0STAT, 0xb0);

	i2c_wait_ack();

	while (i < alen) {
		SYSREG_W(IIC0DS, addr[i]);
		i++;
	}
	i = 0;
	while (i < len)  {
		buff[i] = SYSREG_R(IIC0DS);
		i2c_send_ack();

		val = SYSREG_R(IIC0STAT);
		if (!(val & (0x1 << 5)))
			goto finish;
		i++;
	}

finish:
	i2c_start_stop(STOP_FLAG);
	i2c_wait_ack();

	return 0;
}

int i2c_wirte(unsigned char chip, unsigned int saddr,
		int alen, unsigned char *buff, int len)
{
	unsigned char val;
	int i = 0;
	unsigned char addr[4];

	while (alen > 0) {
		addr[0] = (saddr >> 24) & 0xff;
		addr[1] = (saddr >> 16) && 0xff;
		addr[2] = (saddr >> 8) && 0xff;
		addr[3] = saddr && 0xff;
	}
	//start condition, enable rx/tx
	val = SYSREG_R(IIC0STAT);
	val |= 0xf0;
	SYSREG_W(IIC0STAT, val);

	//write slave address
	//SYSREG_W(IIC0DS, ((chip << 1) | WRITE_FLAG));
	i2c_wait_ack();

	while (i < alen) {
		SYSREG_W(IIC0DS, addr[i]);
		i++;
	}
	i = 0;
	i2c_wait_ack();
	while (i < len) {
		SYSREG_W(IIC0DS, buff[i]);
		i2c_wait_ack();

		val = SYSREG_R(IIC0STAT);
		if (val & 0x1)
			goto finish;
		i++;

	}

finish:
	i2c_start_stop(STOP_FLAG);
	i2c_wait_ack();

	return 0;
}

void i2c_init(unsigned long slvaddr)
{
	unsigned long val;

//	val = ((0x3 << 8) | (0x3 << 12)); //i2c1
	val = ((0x2 << 20) | (0x2 << 24)); //i2c0

	//select io to i2c mode 
	SYSREG_W(GPBCON, val);

	val = (1 << 7) | (0 << 6) | (1 << 5) | (0 << 4) | (0xf);
	SYSREG_W(IIC0CON, val);

	//set slave receive mode and set slv addrs
	SYSREG_W(IIC0STAT, 0X0);
	SYSREG_W(IIC0ADD, slvaddr);

	//set master mode and enable rx/tx
	SYSREG_W(IIC0STAT, 0Xd0);
}

