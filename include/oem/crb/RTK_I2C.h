#define SMBus_NoPEC 0
#define SMBus_NeedPEC 1
//#define bRWSMBus(a,b,c,d,e,f)  SMBUS_RW_B(a,b,c,d,e)
//#define bRSMBusBlock(BatIC_Channel, SMbusRBK, SMB_ADDR_OEM, SMB_CMD_OEM, SMB_DATA_OEM, 31, &SMB_BCNT)) 
//#define SMBUS_RW_BLK( Channel,  Protocol,  Addr , Cmd,uint32_t *var)
#define bRSMBusBlock(a, b, c, d, e, f, g) SMBUS_RW_BLK(a, b, c ,d,e)
#define I2CCompatibleWrite2Read(a,b,c,d,e,f,g) I2C_Protocol(a,b,c,e,d,f)
#define SMbusChA	0x00	// SMbus channel A index
#define SMbusChB	0x01	// SMbus channel B index
#define SMbusChC    0x02    // SMbus channel C index 
#define SMbusChD    0x03    // SMbus channel D index 
#define SMbusChE    0x04    // SMbus channel E index //981004-220614-A

#define SMbusCh0	0x00	// SMbus channel A index
#define SMbusCh1	0x01	// SMbus channel B index
#define SMbusCh2    0x02    // SMbus channel C index 
#define SMbusCh3    0x03    // SMbus channel D index 
#define SMbusCh4    0x04    // SMbus channel E index //981004-220614-A

#define	SMbusWQ     QuickCommandWr	// Write Quick command
#define	SMbusRQ     QuickCommandRd	// Read Quick command
#define	SMbusSBC	SendByte	// Send Byte command
#define	SMbusRBC	ReceiveByte	// Receive Byte command
#define	SMbusWB		WriteByte	// Write byte command
#define SMbusRB		ReadByte	// Read byte command
#define	SMbusWW 	WriteWord	// Write word command
#define	SMbusRW		ReadWord	// Read  word command
#define	SMbusWBK	WriteBlock	// Write block command
#define	SMbusRBK	ReadBlock	// Read block command


