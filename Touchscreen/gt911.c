/**
 ******************************************************************************
 * @file    gt911.c
 * @author  Joao Costa - costasjf@gmail.com
 * @brief   This file provides a set of functions needed to manage the GT911
 *          touch screen devices. This driver works with TouchGFX, using single
 *          point detection scheme.
 ******************************************************************************/

/************ INCLUDES ************/

#include "gt911.h"

/* Touch screen driver structure initialization */
TS_DrvTypeDef gt911_ts_drv = {
		gt911_Init,
		gt911_ReadID,
		gt911_TS_Start,
		gt911_TS_DetectTouch,
};


/************ PRIVATE VARIABLES ************/

static gt911_handle_TypeDef gt911_ts_handle; //GT911 touch handle variable
extern I2C_HandleTypeDef hi2c4;

/************ PUBLIC VARIABLES ************/


/************ PRIVATE FUNCTIONS PROTOTYPES ************/
/**
  * @brief  Reads multiple data.
  * @param  i2c_handler : I2C handler
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  MemAddress: Memory address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(I2C_HandleTypeDef *i2c_handler,
                                           uint8_t Addr,
                                           uint16_t Reg,
                                           uint16_t MemAddress,
                                           uint8_t *Buffer,
                                           uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(i2c_handler, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occurred */
    //I2Cx_Error(i2c_handler, Addr);
  }
  return status;
}

/**
  * @brief  Writes a value in a register of the device through BUS in using DMA mode.
  * @param  i2c_handler : I2C handler
  * @param  Addr: Device address on BUS Bus.
  * @param  Reg: The target register address to write
  * @param  MemAddress: Memory address
  * @param  Buffer: The target register value to be written
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteMultiple(I2C_HandleTypeDef *i2c_handler,
                                            uint8_t Addr,
                                            uint16_t Reg,
                                            uint16_t MemAddress,
                                            uint8_t *Buffer,
                                            uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(i2c_handler, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the I2C Bus */
    //I2Cx_Error(i2c_handler, Addr);
  }
  return status;
}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  Value: Data to be written
  * @retval None
  */
void TS_IO_Write(uint8_t Addr, uint16_t Reg, uint8_t Value)
{
  I2Cx_WriteMultiple(&hi2c4, Addr, Reg, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&Value, 1);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Data to be read
  */
uint8_t TS_IO_Read(uint8_t Addr, uint16_t Reg)
{
  uint8_t read_value = 0;
  I2Cx_ReadMultiple(&hi2c4, Addr, Reg, I2C_MEMADD_SIZE_16BIT, (uint8_t*)&read_value, 1);
  return read_value;
}

/**
  * @brief  TS delay
  * @param  Delay: Delay in ms
  * @retval None
  */
void TS_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/**
 * @brief  Returns if I2C was previous initialized or not.
 * @param  None.
 * @retval : I2C initialization status.
 */
static uint8_t gt911_Get_I2C_InitializedStatus(void);

/**
 * @brief  I2C initialize if needed.
 * @param  None.
 * @retval : None.
 */
static void gt911_I2C_InitializeIfRequired(void);

/**
 * @brief  Basic static configuration of TouchScreen
 * @param  DeviceAddr: GT911 Device address for communication on I2C Bus.
 * @retval Status GT911_STATUS_OK or GT911_STATUS_NOT_OK.
 */
static uint32_t gt911_TS_Configure(uint16_t DeviceAddr);


/************ PUBLIC FUNCTIONS DEFINITION ************/

/**
 * @brief  Initializes the gt911 i2c communication bus from MCU to GT911
 * @param  DeviceAddr: gt911 address for i2c communication
 * @retval None
 */
void gt911_Init(uint16_t DeviceAddr)
{
	//Wait 200ms after power up before accessing gt911 registers
	TS_IO_Delay(200);

	/* Initialize I2C link if needed */
	gt911_I2C_InitializeIfRequired();

	gt911_ts_handle.i2cInitialized = GT911_I2C_NOT_INITIALIZED;
	gt911_ts_handle.currActiveTouchNb = 0;
}

/**
 * @brief  Read the gt911 device ID, pre initialize I2C in case of need to be
 *         able to read the GT911 device ID, and verify this is a GT911.
 * @param  DeviceAddr: I2C GT911 Slave address.
 * @retval The Device ID (two bytes).
 */
uint8_t gt911_ReadID(uint16_t DeviceAddr)
{
	uint8_t attemptscount = 0;
	uint8_t devicefounded = 0;

	//Initialize I2C link if needed
	gt911_I2C_InitializeIfRequired();

	//Maximum of 4 attempts to read ID
	for(attemptscount = 0; ((attemptscount < 3) && !(devicefounded)); attemptscount++)
	{
		//Read gt911 ID registers: ASCII -> "9110"
		if((TS_IO_Read(DeviceAddr, GT911_CHIP_ID_REG1) == 0x39) && \
				(TS_IO_Read(DeviceAddr, GT911_CHIP_ID_REG2) == 0x31) &&\
				(TS_IO_Read(DeviceAddr, GT911_CHIP_ID_REG3) == 0x31) &&\
				(TS_IO_Read(DeviceAddr, GT911_CHIP_ID_REG4) == 0x00))
		{
			/* Set device as found */
			devicefounded = 1;
		}
	}
	/* Return the device ID value */
	return devicefounded;
}

/**
 * @brief  Configures the touch Screen IC device to start detecting touches
 * @param  DeviceAddr: Device address on communication Bus (I2C slave address).
 * @retval None.
 */
uint16_t max_l=0, max_m=0;
uint16_t config_ver = 0;
void gt911_TS_Start(uint16_t DeviceAddr)
{
	uint8_t CTP_CFG_GT911[] =  {
	  0x00,0x20,0x03,0xE0,0x01,0x05,0x0D,0x00,0x01,0x08,
	  0x28,0x0F,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00,
	  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8A,0x2A,0x0C,
	  0x45,0x47,0x0C,0x08,0x00,0x00,0x00,0x02,0x02,0x2D,
	  0x00,0x00,0x00,0x00,0x00,0x03,0x64,0x32,0x00,0x00,
	  0x00,0x28,0x64,0x94,0xC5,0x02,0x07,0x00,0x00,0x04,
	  0x9C,0x2C,0x00,0x8F,0x34,0x00,0x84,0x3F,0x00,0x7C,
	  0x4C,0x00,0x77,0x5B,0x00,0x77,0x00,0x00,0x00,0x00,
	  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	  0x00,0x00,0x18,0x16,0x14,0x12,0x10,0x0E,0x0C,0x0A,
	  0x08,0x06,0x04,0x02,0xFF,0xFF,0x00,0x00,0x00,0x00,
	  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	  0x00,0x00,0x16,0x18,0x1C,0x1D,0x1E,0x1F,0x20,0x21,
	  0x22,0x24,0x13,0x12,0x10,0x0F,0x0A,0x08,0x06,0x04,
	  0x02,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
	  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	  0x00,0x00,0x00,0x00,0x24,0x01
	};//186
	//uint8_t teste[2] = {0, 0};
	/* Minimum static configuration of GT911 */
	gt911_TS_Configure(DeviceAddr);

	/* By default set GT911 IC in Polling mode : no INT generation on GT911 for new touch available */
	/* Note TS_INT is active low                                                                      */
	//gt911_TS_DisableIT(DeviceAddr);

	uint8_t chksum = 0;

	config_ver = TS_IO_Read(DeviceAddr, 0x8047);
	TS_IO_Write(DeviceAddr, 0x8047, config_ver+1);
	//	//Reads current touch number register velue:
	//	touch_number = TS_IO_Read(DeviceAddr, 0x804C);

	//Writes the number of touch points config register:
	TS_IO_Write(DeviceAddr, 0x804C, 0x01);

	TS_IO_Write(DeviceAddr, 0x8048, 0x20);
	TS_IO_Write(DeviceAddr, 0x8049, 0x03);
	TS_IO_Write(DeviceAddr, 0x804A, 0xE0);
	TS_IO_Write(DeviceAddr, 0x804B, 0x01);

	//Calculates new checksum:
	for(uint16_t reg = 0x8047; reg <= 0x80FE; ++reg)
	{
		chksum += TS_IO_Read(DeviceAddr, reg);
	}
	chksum = ~chksum +1;

	TS_IO_Write(DeviceAddr, 0x80FF, chksum);
	TS_IO_Write(DeviceAddr, 0x8100, 0x01);

	TS_IO_Write(DeviceAddr, 0x8041, 0x00);

	TS_IO_Delay(10);

	//Cleans the status register for the new touch read
	TS_IO_Write(DeviceAddr, GT911_TP_STAT_REG, 0);

	/* By default set GT911 IC in Polling mode : no INT generation on GT911 for new touch available */
	/* Note TS_INT is active low                                                                      */
	//gt911_TS_DisableIT(DeviceAddr);
}

/**
 * @brief  Return if there is touches detected or not.
 *         Try to detect new touches and forget the old ones (reset internal global
 *         variables).
 * @param  DeviceAddr: Device address on communication Bus.
 * @retval : Number of active touches detected (can be 0, 1 or 2).
 */

uint8_t coordinates[4] = {0, 0, 0, 0};

uint8_t gt911_TS_DetectTouch(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y)
{
	volatile uint8_t nbTouch = 0;
	volatile uint8_t touch_status = 0;
	volatile uint8_t ucReadData = 0;
	static uint16_t coord;

	//Read register GT911_TD_STAT_REG to check number of touches detection
	touch_status = TS_IO_Read(DeviceAddr, GT911_TP_STAT_REG);
	//touch_status = TS_IO_Read(DeviceAddr, 0x81A8);
	nbTouch = touch_status & GT911_4LSB_MASK; //Just the 4 LSB refers to active touch points

	if(touch_status)
	{
		ucReadData = TS_IO_Read(DeviceAddr, 0x8150);
		coord = (ucReadData & GT911_TOUCH_POS_LSB_MASK) >> GT911_TOUCH_POS_LSB_SHIFT;
		/* Read high part of X position */
		ucReadData = TS_IO_Read(DeviceAddr, 0x8151);
		coord |= ((ucReadData & GT911_TOUCH_POS_MSB_MASK) >> GT911_TOUCH_POS_MSB_SHIFT) << 8;
		/* Send back ready X position to caller */
		*X = coord;

		/* Read low part of Y position */
		ucReadData = TS_IO_Read(DeviceAddr, 0x8152);
		coord = (ucReadData & GT911_TOUCH_POS_LSB_MASK) >> GT911_TOUCH_POS_LSB_SHIFT;
		/* Read high part of Y position */
		ucReadData = TS_IO_Read(DeviceAddr, 0x8153);
		coord |= ((ucReadData & GT911_TOUCH_POS_MSB_MASK) >> GT911_TOUCH_POS_MSB_SHIFT) << 8;
		/* Send back ready Y position to caller */
		*Y = coord;

		//Cleans the status register for the new touch read
		TS_IO_Write(DeviceAddr, GT911_TP_STAT_REG, 0);

		//Is data ready for reading and touch detected?
		if(nbTouch > 1)
		{
			nbTouch = 0;
		}
	}

	/* Update gt911 driver internal global : current number of active touches */
	gt911_ts_handle.currActiveTouchNb = nbTouch;

	return(nbTouch);
}


/* Static functions bodies-----------------------------------------------*/


/**
 * @brief  Return the status of I2C was initialized or not.
 * @param  None.
 * @retval : I2C initialization status.
 */
static uint8_t gt911_Get_I2C_InitializedStatus(void)
{
	return(gt911_ts_handle.i2cInitialized);
}

/**
 * @brief  I2C initialize if needed.
 * @param  None.
 * @retval : None.
 */
static void gt911_I2C_InitializeIfRequired(void)
{
	if(gt911_Get_I2C_InitializedStatus() == GT911_I2C_NOT_INITIALIZED)
	{
		/* Initialize TS IO BUS layer (I2C) */
		TS_IO_Init();

		/* Set state to initialized */
		gt911_ts_handle.i2cInitialized = GT911_I2C_INITIALIZED;
	}
}

/**
 * @brief  Basic static configuration of TouchScreen
 * @param  DeviceAddr: GT911 Device address for communication on I2C Bus.
 * @retval Status GT911_STATUS_OK or GT911_STATUS_NOT_OK.
 */
static uint32_t gt911_TS_Configure(uint16_t DeviceAddr)
{
	uint32_t status = GT911_STATUS_OK;

	/* Nothing special to be done for GT911 */

	return(status);
}
