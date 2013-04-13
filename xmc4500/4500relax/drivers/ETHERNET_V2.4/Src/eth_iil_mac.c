/* =============================================================================
** Copyright (C) 2006 Infineon Technologies.
**
** All rights reserved.
** =============================================================================
**
** =============================================================================
**
** This document contains proprietary information belonging to Infineon 
** Technologies. Passing on and copying of this document, and communication of 
** its contents is not permitted without prior written authorisation.
**
** =============================================================================
*/
/* =============================================================================
**
** Revision Information :
** @FILENAME@:       eth_iil_mac.c
** @VERSION@:        2.4
** @DATE@:           20/1/2006 
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: This file provides the API which are related to MAC module. The
**           provided APIs are not directly available to user application
**
** =============================================================================
** References: ETH Design book
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh, Ruby,Rajesh    Release after code review.
** 06/04/2004      Ruby					  Rizal's comments
** 29/04/2004      Ruby					  Rizal's comments
** 12/11/2004      Badarinath Jayashree   CAM Bug Fix done, Version number bumped
**		           (IFIN SCC AI)          to 2.3 to match the version of the C files
** 20/1/2006     Badarinath Jayashree     Version number bumped
**		           (IFIN SCC AI)          to 2.4 to match the version of the C files
** @CHANGE_HISTORY@
** =============================================================================
*/

/*
  Include all the required header files needed for this file
*/
#include "eth_api.h"

/*
*******************************************************************************
* Function Name:     ETH_read_phy
*
* Calling Functions: ETH_initialise_phy
*
* Functions Called:  None
*
* Description:
*   This function writes the value to the register of the phy device specified. 
*
* Input parameters:  
*   ETH_device       - Ethernet controller hardware module identification value
*   ETH_phy_addr     - Address of the PHY device to read or write
*   ETH_reg_addr     - Address inside the PHY to read or write
*   ETH_phy_data    - Pointer to the data to be read from the PHY device
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
void ETH_read_phy(
  ETH_DEVICE    ETH_device,
  ETH_PHY_CTRL *ETH_phy_ctrl,
  IFX_UINT16   *ETH_mdio_data
)
{
  /* Program the SM control register with the register details */
  ETH_HW_MACSMCTRL = BIT32_MASK(ETH_phy_ctrl->reg_num, ETH_HW_PHY_REG_ADDR) |
                     BIT32_MASK(ETH_phy_ctrl->phy_num, ETH_HW_PHY_DEV)      |
                     BIT32_MASK(ETH_HW_RST, ETH_HW_MACSMCTRL_WR)            |
                     BIT32_MASK(ETH_HW_SET, ETH_HW_MACSMCTRL_BUSY);

  /* Loop till the PHY is busy */
  while(ETH_HW_MACSMCTRL & BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY))
  {
  }
  *ETH_mdio_data = (IFX_UINT16)ETH_HW_MACSMDATA;
}

/*
*******************************************************************************
* Function Name:     ETH_check_phy
*
* Calling Functions: ETH_detect_phy
*
* Functions Called:  ETH_read_phy
*
* Description:
*   This function checks the validity of the PHY.
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_phy_address   - Address of the phy which is to be checked for validity
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

ETH_STATUS ETH_check_phy(
 ETH_DEVICE ETH_device,
 IFX_UINT8 ETH_phy_address
)
{
  IFX_UINT16   ctrl_data;
  IFX_UINT16   stat_data;
  ETH_PHY_CTRL phy_ctrl; 
  /* Check the validilty of the PHY */

  /* Read the MDI control register */
  phy_ctrl.phy_num = ETH_phy_address;
  phy_ctrl.reg_num = ETH_HW_PHY_CTRL_REG;
  ETH_read_phy(ETH_device, &phy_ctrl,&ctrl_data);
  
  /* Read the status register twice, bacause of sticky bits */
  phy_ctrl.phy_num = ETH_phy_address;
  phy_ctrl.reg_num = ETH_HW_PHY_STAT_REG;
  ETH_read_phy(ETH_device, &phy_ctrl, &stat_data);
  ETH_read_phy(ETH_device, &phy_ctrl, &stat_data);
  
  if ((ctrl_data == MAX16) ||
     ((stat_data == ETH_HW_RST) && (ctrl_data == ETH_HW_RST)))
  {
    return ETH_ERR;
  }
  return ETH_SUCCESS;
}

/*
*******************************************************************************
* Function Name:     ETH_detect_phy
*
* Calling Functions: ETH_initialise_phy
*
* Functions Called:  ETH_detect_phy
*
* Description:
*   This function does the following:
*   - Checks the validity of the PHY
*   - Detects the PHY address
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_setup         - Configuration parameters
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

ETH_STATUS ETH_detect_phy(
  ETH_DEVICE     ETH_device
)
{
  IFX_UINT8 addr;
  IFX_UINT8 valid_phy = ETH_HW_RST;

  /* The MII interface supports 32 PHY devices */
  /* Check if there is a valid PHY device at the DEFAULT address */
  if(ETH_check_phy(ETH_device, ETH_HW_PHY_DEFAULT_ADDR) == ETH_SUCCESS)
  {
    /* Store the  PHY_DEFAULT_ADDRESS */
    ETH_phy_device_address = ETH_HW_PHY_DEFAULT_ADDR;
    valid_phy              = ETH_HW_SET;
  } 
  else /* If unable to find a valid PHY device at the DEFAULT addr */
  {
    /* Loop through all the PHY addresses */
    for(addr = ETH_HW_MIN_PHY_ADDR; addr <= ETH_HW_MAX_PHY_ADDR; addr++)
    {
      if(ETH_check_phy(ETH_device,addr) == ETH_SUCCESS)
      {
        /* Store the PHY address */
        ETH_phy_device_address = addr; 
        valid_phy              = ETH_HW_SET;
        break;
      }
    } /* end of for */
  } /* end of else */ 
  /* Update the return status */
  if(valid_phy)
  {
    return ETH_SUCCESS;
  }
  else
  {
    return ETH_ERR;
  }
}
/*
*******************************************************************************
* Function Name:     ETH_phy_autoneg
*
* Calling Functions: ETH_initialise_phy
*
* Functions Called:  None
*
* Description:
*   Check if the PHY supports autoneg by reading the autoneg ability bit of the 
*   Status register. If the PHY supports Autoneg, restart Autoneg.
*   and receive control registers.
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_setup         - Configuration parameters
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

ETH_STATUS ETH_phy_autoneg(
  ETH_DEVICE     ETH_device
)
{
  IFX_UINT16   stat_data;
  ETH_PHY_CTRL phy_ctrl; 
  IFX_UINT8     start_autoneg = 0;
  IFX_UINT8     autoneg_comp = 0;
  IFX_UINT16    control_val;

  /* 10 Mbps mode */
  if(ETH_CFG_SPEED == 0)
  {
    control_val = 0x461; /* 802.3 | 10 BaseT | FD | Pause*/
  }
  else
  {
    control_val = 0x461 + 0x180; /* 802.3 | 100 BaseT | FD | Pause */
  }
  if(ETH_CFG_FULLDUPLEX == 0)
  {
    control_val &= ~(0x140); /* Enable HD */
  }
  ETH_HW_MACSMDATA = control_val;
  
  ETH_HW_MACSMCTRL = 0x0C04;
  
  while(ETH_HW_MACSMCTRL & BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY))
  {
  }

  /* Enable Autoneg */
  if(ETH_CFG_SPEED == 0)
  {
    control_val = 0x1100; /* Enable AN | Full Duplex */
  }
  else
  {
    control_val = 0x1100 + 0x2000; /* Enable AN | FD | 100Mbps */
  }
  if(ETH_CFG_FULLDUPLEX == 0)
  {
    control_val &= ~(1<<8); /* Enable HD */
  }
  ETH_HW_MACSMDATA = control_val;
  
  phy_ctrl.phy_num = ETH_phy_device_address;
  phy_ctrl.reg_num = ETH_HW_PHY_CTRL_REG;
  ETH_HW_MACSMCTRL = BIT32_MASK(phy_ctrl.reg_num, ETH_HW_PHY_REG_ADDR)|
                     BIT32_MASK(phy_ctrl.phy_num, ETH_HW_PHY_DEV)     |
                     BIT32_MASK(ETH_HW_SET, ETH_HW_MACSMCTRL_WR)      |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY); 

  while(ETH_HW_MACSMCTRL & BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY))
  {
  }
  
  while(!start_autoneg)
  {
    autoneg_comp = 0;
    if(ETH_CFG_SPEED == 0)
    {
      control_val = 0x1300;
    }
    else
    {
      control_val = 0x1300 + 0x2000;
    }
    if(ETH_CFG_FULLDUPLEX == 0)
    {
      control_val &= ~(1<<8);
    }
    ETH_HW_MACSMDATA = control_val;
  
    phy_ctrl.phy_num = ETH_phy_device_address;
    phy_ctrl.reg_num = ETH_HW_PHY_CTRL_REG;
    ETH_HW_MACSMCTRL = BIT32_MASK(phy_ctrl.reg_num, ETH_HW_PHY_REG_ADDR)|
                       BIT32_MASK(phy_ctrl.phy_num, ETH_HW_PHY_DEV)     |
                       BIT32_MASK(ETH_HW_SET, ETH_HW_MACSMCTRL_WR)      |
                       BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY); 

    while(ETH_HW_MACSMCTRL & BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY))
    {
    }

    while(!autoneg_comp)
    {
      phy_ctrl.phy_num = ETH_phy_device_address;
      phy_ctrl.reg_num = ETH_HW_PHY_STAT_REG;
      ETH_read_phy(ETH_device, &phy_ctrl,&stat_data);
      if(stat_data &(1<<5)) autoneg_comp = 1;
    }
    if(!(stat_data &(1<<4))) start_autoneg = 1;
  }
  return ETH_SUCCESS;
}
/*
*******************************************************************************
* Function Name:     ETH_check_link
*
* Calling Functions: ETH_initialise_mac
*
* Functions Called:  None
*
* Description:
*   This function reads the status register of the PHY and returns ETH_SUCCESS
*   if the link is up & ETH_ERR if the link is down.
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     ETH_SUCCESS if the link is up
*                    ETH_ERR     if the link is down 
*
*******************************************************************************
*/
ETH_STATUS ETH_check_link(ETH_DEVICE ETH_device)
{
  IFX_UINT16 link_state;

  /* Read the PHY status register */
  ETH_HW_MACSMCTRL = 0x0801;
  while(ETH_HW_MACSMCTRL & BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY))
  {
  }
  link_state = (IFX_UINT16)ETH_HW_MACSMDATA;
  if((link_state & 0x0004) == 0x0004) 
  {
    /* The link is up, return SUCCESS */
	return ETH_SUCCESS;
  }
  else
  {
     return ETH_ERR;
  }
}

/*
*******************************************************************************
* Function Name:     ETH_initialise_phy
*
* Calling Functions: ETH_initialise_mac
*
* Functions Called:  None
*
* Description:
*   This function does the following:
*   - Checks the validity of the PHY
*   - Detects the PHY address
*   - Resets the PHY
*   - Initialises the PHY with default values
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_setup         - Configuration parameters
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
ETH_STATUS ETH_initialise_phy(
  ETH_DEVICE     ETH_device,
  ETH_PHY_CONF  *ETH_phy_conf
)
{
  IFX_UINT16 link_state;
  IFX_STINT16 link_down = ETH_HW_SET;
  IFX_UINT16 count = 0;
#define LOOP_NUM_TIMES 10

  /* Test if the PHY is connected else return ERROR_NO_PHY */
  if(ETH_detect_phy(ETH_device) == ETH_ERR) return ETH_ERR;

 /* Initialise the PHY by writing the values in the station 
   management data register */
  if(ETH_phy_conf->auto_negotiate)
  {
    if(ETH_phy_autoneg(ETH_device) == ETH_ERR)
    {
      return ETH_ERR;
    }
  }
  else /* Auto neg not configured */
  {
    ETH_HW_MACSMDATA = 
      BIT32_MASK(ETH_phy_conf->full_duplex,ETH_HW_PHY_CTRL_FULLDUP)|
      BIT32_MASK(ETH_phy_conf->loopback,ETH_HW_PHY_CTRL_LOOPBACK)  |
      BIT32_MASK(ETH_HW_SET,ETH_HW_PHY_CTRL_COL);


    /* Check for speed settings: if speed is 100 Mbps */
    if(ETH_phy_conf->speed == ETH_HW_SET)
    {
      ETH_HW_MACSMDATA |= 
           BIT32_MASK(ETH_phy_conf->speed,ETH_HW_PHY_CTRL_SPEED13);
    }
    
      /* Program the station management control register with the following
       - address of phy
       - address of the register in the phy to written to
       - command (write)
       - busy flag
    */
    ETH_HW_MACSMCTRL = BIT32_MASK(ETH_HW_PHY_CTRL_REG, ETH_HW_PHY_REG_ADDR )|
                       BIT32_MASK(ETH_phy_device_address, ETH_HW_PHY_DEV)|
                       BIT32_MASK(ETH_HW_SET, ETH_HW_MACSMCTRL_WR)|
                       BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY); 

    while(ETH_HW_MACSMCTRL & BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY))
    {
    }
   
  } /* End of else Autoneg not configured */	

  /* Check for the link status */
  /* If the link is not up, loop till the link goes up */
  if (ETH_check_link(ETH_device) != ETH_SUCCESS) 
  {
    while(link_down)
   {
     ETH_HW_MACSMCTRL = 0x0801;
     while(ETH_HW_MACSMCTRL & BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY))
     {
     }
     link_state = (IFX_UINT16)ETH_HW_MACSMDATA;
     if((link_state & 0x0004) == 0x0004)
     {
       link_down = ETH_HW_RST;
	 }
	 count++;
	 if(count > LOOP_NUM_TIMES) 
	 {
	   return ETH_ERR;
	 }
   }
  }	

  return ETH_SUCCESS;
}

/*
*******************************************************************************
* Function Name:     ETH_initialise_mac
*
* Calling Functions: ETH_initialise_dev
*
* Functions Called:  None
*
* Description:
*   Initialise the MAC controller by enabling the bits in corresponding TX
*   and receive control registers.
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_setup         - Configuration parameters
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

ETH_STATUS ETH_initialise_mac(
ETH_DEVICE     ETH_device,
ETH_COM_PARAMS *ETH_setup
)
{
  IFX_UINT8  ETH_no_mac_addrs = 0;

  /* Reset the MAC */
  ETH_HW_MACCTRL = BIT32_MASK(ETH_HW_SET, ETH_HW_MACCTRL_RESET);
  
  /*Set MAC control register configuration data*/
  ETH_HW_MACCTRL = 
    BIT32_MASK(ETH_setup->mac_conf.full_duplex, ETH_HW_MACCTRL_FULLDUP)|
    BIT32_MASK(ETH_setup->mac_conf.loop_back, ETH_HW_MACCTRL_MACLP);

# if ETH_CFG_USE_PAUSE == 1
  /*Copy the starting location, where the application desires to write MAC 
    addresses into CAM*/
  ETH_no_mac_addrs = ETH_HW_RST;

  /*Write the pause control MAC addresses into CAM */
  while(ETH_no_mac_addrs < ETH_HW_MAC_PAUSE_ADDR_FLDS)
  {
    /*
      Write the MAC address into ETH_HW_MACCAMDATA register 4 bytes at a time.
      The remaining 2 bytes of cuurent MAC address will be written into CAM in
      next iteration of loop. The 2MSB of previous MAC address and the next 
      2MSBs of MAC address will be added and written in next iteration of loop
    */
    ETH_HW_MACCAMDATA = 
      NTOHL(ETH_setup->cam_data.mac_addrs[ETH_no_mac_addrs]);

    /*The desired address location inside the CAM, each location corresponds 
      to 4 bytes*/
    ETH_HW_MACCAMADDR = ETH_no_mac_addrs;
    ETH_no_mac_addrs++;
 
    /*Wait till the MAC CAM write busy flag cleared*/
    while(ETH_HW_MACCAMADDR & BIT32_MASK(ETH_HW_SET,ETH_HW_MACAMADDR_BSY))
    {
    }
  }
# endif /*ETH_CFG_USE_PAUSE*/

# if ETH_CFG_USE_CAM == 1
  /*Copy the starting location, where the application desires to write MAC 
    addresses into CAM*/
#  if ETH_CFG_USE_PAUSE == 1
  ETH_no_mac_addrs = ETH_setup->cam_data.start_mac_addr + 
                          ETH_HW_MAC_PAUSE_ADDR_FLDS;
#  else
  ETH_no_mac_addrs = ETH_setup->cam_data.start_mac_addr;
#  endif	/*ETH_CFG_USE_PAUSE*/

  /*Write the application provided MAC addresses into CAM */
  /*ETH_no_mac_addrs is the index in the software MAC address array where MAC address
   is stored 4 byte-wise. Sum of no_of_mac_addrs and start_mac_addr gives the number 
   of MAC addresses in  a 6 byte aligned array. that is why RHS is multiplied by 
   ETH_MACADDR_CONV_FACTOR(1.5)
   */
   
   while(ETH_no_mac_addrs < 
    ((ETH_MACADDR_CONV_FACTOR)*
     (ETH_setup->cam_data.no_of_mac_addrs + ETH_setup->cam_data.start_mac_addr)))
  {
    /*
      Write the MAC address into ETH_HW_MACCAMDATA register 4 bytes at a time.
      The remaining 2 bytes of cuurent MAC address will be written into CAM in 
      next iteration of loop. The 2MSB of previous MAC address and the next 
      2MSBs of MAC address will be added and written in next iteration of loop
    */
    ETH_HW_MACCAMDATA = 
      NTOHL(ETH_setup->cam_data.mac_addrs[ETH_no_mac_addrs]);

    /*The desired address location inside the CAM, each location corresponds to
       4 bytes*/
    ETH_HW_MACCAMADDR = ETH_no_mac_addrs;
    ETH_no_mac_addrs++;
 
    /*Wait till the MAC CAM write busy flag cleared*/
    while(ETH_HW_MACCAMADDR & BIT32_MASK(ETH_HW_SET,ETH_HW_MACAMADDR_BSY))
    {
    }
  }
#endif  /*ETH_CFG_USE_CAM*/

# if(ETH_CFG_USE_PAUSE == 1)

  /*Write CAM PAUSE control data and CAM filling data into CAM table*/
  ETH_HW_MACCAMDATA = ETH_HW_PAUSE_FIELDS; /*pause control type and opcode*/
  ETH_HW_MACCAMADDR = ETH_HW_PAUSE_LOC1;
  /*Wait till the MAC CAM write busy flag cleared*/
  while(ETH_HW_MACCAMADDR & BIT32_MASK(ETH_HW_SET,ETH_HW_MACAMADDR_BSY))
  {
  }

  /*Write CAM PAUSE control data and CAM filling data into CAM table*/
  ETH_HW_MACCAMDATA = ETH_CFG_PAUSE_TIME; /*The pause time, 2MSBs*/ 
  ETH_HW_MACCAMADDR = ETH_HW_PAUSE_LOC2;
  /*Wait till the MAC CAM write busy flag cleared*/
  while(ETH_HW_MACCAMADDR & BIT32_MASK(ETH_HW_SET,ETH_HW_MACAMADDR_BSY))
  {
  }

  /*Write CAM PAUSE control data and CAM filling data into CAM table*/
  ETH_HW_MACCAMDATA = ETH_HW_CAM_FILL_DATA;   /*used for pause frame*/
  ETH_HW_MACCAMADDR = ETH_HW_PAUSE_LOC3;
  /*Wait till the MAC CAM write busy flag cleared*/
  while(ETH_HW_MACCAMADDR & BIT32_MASK(ETH_HW_SET,ETH_HW_MACAMADDR_BSY))
  {
  }
    
  /*Write CAM PAUSE control data and CAM filling data into CAM table*/
  ETH_HW_MACCAMDATA = ETH_HW_CAM_FILL_DATA;   /*used for pause frame*/
  ETH_HW_MACCAMADDR = ETH_HW_PAUSE_LOC4;
  /*Wait till the MAC CAM write busy flag cleared*/
  while(ETH_HW_MACCAMADDR & BIT32_MASK(ETH_HW_SET,ETH_HW_MACAMADDR_BSY))
  {
  }

  /*Write CAM PAUSE control data and CAM filling data into CAM table*/
  ETH_HW_MACCAMDATA = ETH_HW_CAM_FILL_DATA;   /*used for pause frame*/
  ETH_HW_MACCAMADDR = ETH_HW_PAUSE_LOC5;
  /*Wait till the MAC CAM write busy flag cleared*/
  while(ETH_HW_MACCAMADDR & BIT32_MASK(ETH_HW_SET,ETH_HW_MACAMADDR_BSY))
  {
  }

# endif /*ETH_CFG_USE_PAUSE*/
                      
#if ETH_CFG_USE_CAM == 1
  /* CAM data activation */
  /*program the MAC CAM control 0 register*/
  /* broadcast,	CAM compare enable, multicast, Negative CAM,	unicast*/
  ETH_HW_MACCAMCTRL0 = 
  BIT32_MASK(ETH_setup->cam_conf.broad_cast, ETH_HW_MACCAMCTRL0_BRDACC)|
  BIT32_MASK(ETH_setup->cam_conf.cam_compare_enable, ETH_HW_MACCAMCTRL0_CMPEN)|
  BIT32_MASK(ETH_setup->cam_conf.multi_cast, ETH_HW_MACCAMCTRL0_GPRACC)|
  BIT32_MASK(ETH_setup->cam_conf.negative_cam, ETH_HW_MACCAMCTRL0_NEGCAM)|
  BIT32_MASK(ETH_setup->cam_conf.uni_cast, ETH_HW_MACCAMCTRL0_STACC);

  /*
    Program the MAC CAM control register 1 to enable the MAC addresses 
    programmed inside CAM to filter incoming frames
  */
# if ETH_CFG_USE_PAUSE == 1
  ETH_HW_MACCAMCTRL1 =  (ETH_setup->cam_data.addr_loc_enable) & 0xFFFFC;
# else
  ETH_HW_MACCAMCTRL1 =  ETH_setup->cam_data.addr_loc_enable;
# endif 

#endif /*ETH_CFG_USE_CAM */


#if ETH_CFG_STAT_LOG == 1
  ETH_HW_MACTX0IMR = BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXIMR_XCOL)  |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXIMR_TXDEF) |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXIMR_PSE)   |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXIMR_UNDER) |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXIMR_XDEF)  |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXIMR_LCAR)  |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXIMR_LCOL)  |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXIMR_CMP);

  ETH_HW_MACRX0IMR = BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXIMR_CTLFRX) |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXIMR_ALIGNE) |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXIMR_CRCE)   |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXIMR_OVER)   |
                     BIT32_MASK(ETH_HW_SET, ETH_HW_MACRXIMR_LOE)   |
                     BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXIMR_GOOD);
#else
  ETH_HW_MACTX0IMR = BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXIMR_PSE);
  ETH_HW_MACRX0IMR = ETH_HW_RST;
#endif /*ETH_CFG_STAT_LOG*/

  /*enable MAC controller interrupts*/
  ETH_HW_MACTX0SRC |= BIT32_MASK(ETH_SRC_CPU, ETH_SRC_TOS)|
                      BIT32_MASK(SYS_ETH_MACTX0, ETH_SRC_SRPN)|
                      BIT32_MASK(ETH_SRC_ENABLE, ETH_SRC_SRE); 


  ETH_HW_MACRX0SRC |= BIT32_MASK(ETH_SRC_CPU, ETH_SRC_TOS)|
                      BIT32_MASK(SYS_ETH_MACRX0, ETH_SRC_SRPN)|
                      BIT32_MASK(ETH_SRC_ENABLE, ETH_SRC_SRE); 

  /* Program the MAC receive control register - long frames, short frames,
     do not check CRC,pass ctrl pkts to upper layer, strip the CRC,	enable 
     the receiver
  */
  ETH_HW_MACRXCTRL = 
    BIT32_MASK(ETH_setup->rx_conf.accept_long, ETH_HW_MACRXCTRL_LOEN)|
    BIT32_MASK(ETH_setup->rx_conf.accept_short, ETH_HW_MACRXCTRL_SHEN)|
    BIT32_MASK(ETH_setup->rx_conf.ignore_crc, ETH_HW_MACRXCTRL_IGNCRC)|
    BIT32_MASK(ETH_setup->rx_conf.pass_ctrl_pkts, ETH_HW_MACRXCTRL_PCTLP)|
    BIT32_MASK(ETH_setup->rx_conf.strip_crc, ETH_HW_MACRXCTRL_STRCRC);

  /* Program the MAC TX control register*/
  ETH_HW_MACTXCTRL = 
    BIT32_MASK(ETH_setup->tx_conf.no_crc, ETH_HW_MACTXCTRL_NOCRC)|  
    BIT32_MASK(ETH_setup->tx_conf.no_defer, ETH_HW_MACTXCTRL_NODEF)|
    BIT32_MASK(ETH_setup->tx_conf.no_pad, ETH_HW_MACTXCTRL_NOPAD)|  
    BIT32_MASK(ETH_setup->tx_conf.sqe_check, ETH_HW_MACTXCTRL_MII10);

   return ETH_SUCCESS;
} /*ETH_initialize_mac*/

/*
*******************************************************************************
* Function Name:     ETH_termiante_mac
*
* Calling Functions: ETH_termiante_dev
*
* Functions Called:  None
*
* Description:
*   Terminate MAC controller by resetting receive and tranmsit controller enable
*   bits in corresponding register. Also reset interrupt control registers.
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_TERMINATE == 1
ETH_STATUS ETH_terminate_mac(ETH_DEVICE ETH_device)
{
  /*Stop the MAC from receiving and sending the frames*/
  ETH_HW_MACCTRL   = BIT32_MASK(ETH_HW_SET, ETH_HW_MACCTRL_HLTIMM)|
                     BIT32_MASK(ETH_HW_SET, ETH_HW_MACCTRL_RESET);

  /* Disable MAC controller interrupts */
  ETH_HW_MACTX0SRC = BIT32_MASK(ETH_HW_RST,ETH_SRC_SRE);
  ETH_HW_MACRX0SRC = BIT32_MASK(ETH_HW_RST,ETH_SRC_SRE);
  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_TERMINATE*/

/*
*******************************************************************************
* Function Name:     ETH_camctrl_caseAodd
*
* Calling Functions: ETH_ctrl_cam
*
* Functions Called:  None
*
* Description: This is the case when the CAM addr have the position
*    ______________
*   |_____________|    
*   |______|
*
*  This function will update the following values
*  - index of the CAM address array in the HW
*  - index of the array of user supplied CAM addresses
*  - position of the start of address in the user supplied CAM array
*
*    Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_cam_prog      - details of the addresses to program in the cam
*
* Output parameters: None
*
* Return Values:     None
*
*******************************************************************************
*/ 
void ETH_camctrl_caseAodd(
  ETH_DEVICE    ETH_device,
  ETH_CAM_PROG *ETH_cam_prog
)
{
  IFX_UINT32 temp1;
  IFX_UINT32 temp2;
  IFX_UINT8 ETH_user_index = ETH_cam_prog->ETH_cam_addr_user;
  IFX_UINT8 ETH_CAM_index  = ETH_cam_prog->ETH_cam_addr_hw;

  /* If the user address starts at the third byte in an element of the user array */
  if(ETH_cam_prog->ETH_user_array_position == ETH_HW_RST)
  {
    /* The address will have to be taken from 2 rows of the user supplied addr */
    temp2 = (ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[ETH_user_index++]
    & 0x0000FFFF);
    temp1 = 0 | (temp2 << 16);

    /* Get the next portion of the user address */
    temp2 = ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[ETH_user_index] & 0xFFFF0000;
    temp1 |= (temp2 >> 16);
    /* Write the user address in the CAM */
    ETH_params.cam_data.mac_addrs[ETH_CAM_index++] = NTOHL(temp1);

    /* Get the last portion of the user address */
    temp2 = ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[ETH_user_index] 
    & 0x0000FFFF;
    temp1 = (temp2 << 16);

    /* Make place for the user addr in the CAM */
    ETH_params.cam_data.mac_addrs[ETH_CAM_index] = ETH_params.cam_data.mac_addrs[ETH_CAM_index] >> 16;

    /* Swap the user addr bits */
    temp1 = (((temp1 & 0x00FF0000) << 8) | ((temp1 & 0xFF000000) >> 8));

    /* Write the user address in the CAM */
    ETH_params.cam_data.mac_addrs[ETH_CAM_index] = 
      (ETH_params.cam_data.mac_addrs[ETH_CAM_index] << 16) | (temp1 >> 16);

    /* Store the values in the ETH_cam_prog structure */
    ETH_cam_prog->ETH_cam_addr_user       = ETH_user_index + 1;
    ETH_cam_prog->ETH_cam_addr_hw         = ETH_CAM_index;
    ETH_cam_prog->ETH_user_array_position = ETH_HW_SET;
  }
  else/* If the user address starts at the first byte in an element of the user array */
  {
    if(ETH_cam_prog->ETH_user_array_position == ETH_HW_SET)
    {
      /* Write the user addr in the CAM */
      ETH_params.cam_data.mac_addrs[ETH_CAM_index++] =
       NTOHL(ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[ETH_user_index]);
      ETH_user_index++; 

      /* Get the next value of the user address */
      temp2 = ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[ETH_user_index];
      /* Make place for the user addr in the CAM */
      ETH_params.cam_data.mac_addrs[ETH_CAM_index] &= 0xFFFF0000;   
   
      /* Write the user address in the CAM */
      ETH_params.cam_data.mac_addrs[ETH_CAM_index] |=
       (((temp2 & 0xFF000000)>> 24) | ((temp2 & 0x00FF0000)>>8));

      /* Store the values in the ETH_cam_prog structure */
      ETH_cam_prog->ETH_cam_addr_user       = ETH_user_index;
      ETH_cam_prog->ETH_cam_addr_hw         = ETH_CAM_index;
      ETH_cam_prog->ETH_user_array_position = ETH_HW_RST;
    } /* end of if */
  } /* end of else */
}

/*
*******************************************************************************
* Function Name:     ETH_camctrl_caseAeven
*
* Calling Functions: ETH_ctrl_cam
*
* Functions Called:  None
*
* Description: This is the case when the CAM addr have the position
*    ______________
*   |_____________|    
*   |______|______|
*   |_____________|
*   .......... or multiples of these....
*
*  This function will update the following values
*  - index of the CAM address array in the HW
*  - index of the array of user supplied CAM addresses
*  - position of the start of address in the user supplied CAM array
*
*    Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_cam_prog      - details of the addresses to program in the cam
*
* Output parameters: None
*
* Return Values:     None
*
*******************************************************************************
*/
void ETH_camctrl_caseAeven(
  ETH_DEVICE    ETH_device,
  ETH_CAM_PROG *ETH_cam_prog
)
{
  IFX_UINT32 temp1;
  IFX_UINT32 temp2;
  IFX_UINT8  count;
  IFX_UINT8 ETH_user_index = ETH_cam_prog->ETH_cam_addr_user;
  IFX_UINT8 ETH_CAM_index  = ETH_cam_prog->ETH_cam_addr_hw;

  /* If the user address starts at the third byte in an element of the user array */
  if(ETH_cam_prog->ETH_user_array_position == ETH_HW_RST)
  {
    /* The address will have to be taken from 2 rows of the user supplied addr */
    for(count = 0; count < ((ETH_cam_prog->ETH_num_addr/2) * 3); count++, ETH_CAM_index++)
    {
     /* Get the first 2 bytes of the user address */
      temp2 = (ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[ETH_user_index++]
               & 0x0000FFFF);
      temp1 = 0 | (temp2 << 16);
      /* Get the first 2 bytes of the user address */
      temp2 = ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[ETH_user_index] & 0xFFFF0000;
      temp1 |= (temp2 >> 16);

      /* Write the user address in the CAM */
      ETH_params.cam_data.mac_addrs[ETH_CAM_index] = NTOHL(temp1);

    } /* end of for */
    /* Store the values in the ETH_cam_prog structure */
    ETH_cam_prog->ETH_cam_addr_user       = ETH_user_index;
    ETH_cam_prog->ETH_cam_addr_hw         = ETH_CAM_index;
    ETH_cam_prog->ETH_user_array_position = ETH_HW_RST;
  } /* end of if */

  /* If the user address starts at the first byte in an element of the user array */
  if(ETH_cam_prog->ETH_user_array_position == ETH_HW_SET)
  {
    for(count = 0;(count < (ETH_cam_prog->ETH_num_addr/2) * 3);count++, ETH_CAM_index++)
    {
      /* Write the user address in the CAM */
      ETH_params.cam_data.mac_addrs[ETH_CAM_index] =
      NTOHL(ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[ETH_user_index]);
      ETH_user_index++;

    }
    /* Store the values in the ETH_cam_prog structure */
    ETH_cam_prog->ETH_cam_addr_user       = ETH_user_index;
    ETH_cam_prog->ETH_cam_addr_hw         = ETH_CAM_index;
    ETH_cam_prog->ETH_user_array_position = ETH_HW_SET;
  } /* end of if */
}
/*
*******************************************************************************
* Function Name:     ETH_camctrl_caseB
*
* Calling Functions: ETH_ctrl_cam
*
* Functions Called:  None
*
* Description: This is the case when the CAM addr have the position
*         ________
*   ______|______|
*  |_____________|
*
*  No parameters are needed in this case as this is always the first 
*  address to be programmed.
*  This function will update the following values
*  - index of the CAM address array in the HW
*  - index of the array of user supplied CAM addresses
*  - position of the start of address in the user supplied CAM array
*
*    Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     None
*
*******************************************************************************
*/
void ETH_camctrl_caseB(
  ETH_DEVICE    ETH_device,
  ETH_CAM_PROG *ETH_cam_prog
)
{
  IFX_UINT32 temp1;	
  IFX_UINT32 temp2;

  /* Since this function will be called only when this is the first address to
    be programmed, user_index = 0 */
  /* Make place for this address in the CAM */
  ETH_params.cam_data.mac_addrs[ETH_cam_prog->ETH_cam_addr_hw] &= 0x0000FFFF;

  /* Get the first two bytes of the user address */
  temp2 = (ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[0] >> 16);

  temp2 = temp2 << 16;
  /* Swap the bits of the user address */
  temp2 = ((temp2 & 0x00FF0000) << 8) | ((temp2 & 0xFF000000) >> 8);

  /* Write the user address in the CAM */
  ETH_params.cam_data.mac_addrs[ETH_cam_prog->ETH_cam_addr_hw++] |= temp2 ;

  /* Get the next 2 byte sof the user address */
  temp2 = ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[0];
  temp2 &= 0x0000FFFF;
  /* Swap the bits of the user address */
  temp2 = ((temp2 & 0x0000FF00) >> 8) | ((temp2 & 0x000000FF) << 8);

  /* Get the next two bytes of the user address */
  temp1 = ETH_cam_prog->ETH_ctrl_data->data.mac_addr_data.mac_addrs[1];
  temp1 &= 0xFFFF0000;
  /* Swap the bits */
  temp1 = ((temp1 & 0xFF000000) >> 8) | ((temp1 & 0x00FF0000) << 8);
  /* Concatenate the 4 bytes together */
  temp1 |= temp2;

  /* Store the user address in the CAM */
  ETH_params.cam_data.mac_addrs[ETH_cam_prog->ETH_cam_addr_hw++] = temp1; 

  /* Store the values in the ETH_cam_prog structure */
  ETH_cam_prog->ETH_cam_addr_user       = 1;
  ETH_cam_prog->ETH_user_array_position = ETH_HW_RST;
}

/*
*******************************************************************************
* Function Name:     ETH_ctrl_mac
*
* Calling Functions: ETH_control_dev
*
* Functions Called:  None
*
* Description:
*   Reset the MAC control configuration parameters like duplex mode and loop back
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_ctrl_data     - Contains new configuration parameters
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_CTRL_MAC == 1 
ETH_STATUS ETH_ctrl_mac(
ETH_DEVICE ETH_device,
ETH_MAC_CONF *ETH_ctrl_data
)
{
 /*
    Copy the configuration data which are to be updated into the ETH_params 
    (global) structure, which will maintain the updated configuartion information
  */
  ETH_params.mac_conf.full_duplex = ETH_ctrl_data->full_duplex;  /*full duplex*/
  ETH_params.mac_conf.loop_back   = ETH_ctrl_data->loop_back;  /*loop back*/
  
  /* Write the new configuration data into MAC control register through global 
     configuration structure*/
  ETH_HW_MACCTRL = BIT32_MASK(ETH_params.mac_conf.full_duplex, ETH_HW_MACCTRL_FULLDUP)|
                   BIT32_MASK(ETH_params.mac_conf.loop_back, ETH_HW_MACCTRL_MACLP);
   
  return ETH_SUCCESS; 
}
#endif /*ETH_CFG_FUNC_CTRL_MAC*/


/*
*******************************************************************************
* Function Name:     ETH_ctrl_cam
*
* Calling Functions: ETH_control_dev
*
* Functions Called:  None
*
* Description:
*   Add or remove the CAM addresses from CAM table and changing the cam configuration 
*   parameters. Only one is posiible at a time
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_ctrl_data     - Either it contains the MAC address or new configuration data
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/ 


#if ETH_CFG_FUNC_CTRL_CAM == 1 
ETH_STATUS ETH_ctrl_cam(
ETH_DEVICE ETH_device,
ETH_CAM_CTRL *ETH_ctrl_data
)
{
  IFX_UINT8 ETH_no_of_fields;   /*number of MAC addresses want to add*/
  IFX_UINT8 ETH_start_mac_addr;      /*starting location of address to edit*/
  IFX_UINT8 ETH_i=0;             /*intermediate variable*/

  IFX_UINT8 ETH_cam_start = 0;
  IFX_UINT8 ETH_cam_end   = 0;
  ETH_CAM_PROG ETH_cam_prog;  

  /*Identify the ioctl command*/
  switch(ETH_ctrl_data->command)
  {
    /*Add the MAC addresses*/
    case ETH_ADD_MAC_ADDR: 
  /*Check for overflow and under flow of requested MAC addresses*/
    if(
       ((ETH_ctrl_data->data.mac_addr_data.start_mac_addr +
        ETH_ctrl_data->data.mac_addr_data.no_of_mac_addrs) > ETH_CAM_TBL_LEN) ||
        ((ETH_ctrl_data->data.mac_addr_data.start_mac_addr +
       ETH_ctrl_data->data.mac_addr_data.no_of_mac_addrs) < ETH_HW_RST)
       )
      {
        return ETH_ERR;
      }
      ETH_start_mac_addr = ETH_ctrl_data->data.mac_addr_data.start_mac_addr + 1;
      ETH_no_of_fields   = ETH_ctrl_data->data.mac_addr_data.no_of_mac_addrs;
      ETH_cam_prog.ETH_ctrl_data = ETH_ctrl_data;
      ETH_i = ETH_start_mac_addr;
      if(ETH_no_of_fields == 0) return ETH_SUCCESS;

   /* Process Case A */
   /* Addresses are divided into 3 cases A, B & C for ease of programming.
    case A addresses are the 1st, 4th, 7th, 10th.. as programmed by the user
    they take the shape 
       ______________
       |_____________|    
       |______|         in the CAM hardware array.

      case B addresses are the 2nd, 5th, 8th ... as programmed by the user
       they take the shape 
        _____________
       |______|______|
       |_____________|	in the CAM hardware array.
   Case C addresses are the 3rd, 6th, 9th ... as programmed by the user
	 They take the same shape as the case B addresses.
  */
  /* Process Case A */                                  
  if(((ETH_start_mac_addr - 1) % 3) == 0) 
  {
    ETH_cam_start =  ETH_start_mac_addr - 1;
    if((ETH_no_of_fields % 2)!= 0)
    {
      if(ETH_no_of_fields == 1)
      {
        ETH_cam_prog.ETH_cam_addr_hw         = ETH_start_mac_addr - 1;
        ETH_cam_prog.ETH_cam_addr_user       = ETH_HW_RST;
        ETH_cam_prog.ETH_user_array_position = ETH_HW_SET;
        ETH_camctrl_caseAodd(ETH_device,&ETH_cam_prog);
      }
      else
      {
        ETH_cam_prog.ETH_cam_addr_hw         = ETH_start_mac_addr - 1;
        ETH_cam_prog.ETH_cam_addr_user       = ETH_HW_RST;
        ETH_cam_prog.ETH_user_array_position = ETH_HW_SET;
        ETH_cam_prog.ETH_num_addr            = ETH_no_of_fields - 1;
        ETH_camctrl_caseAeven(ETH_device,&ETH_cam_prog);

        /* The ETH_cam_prog structure is updated by the call to the prev. function */
        ETH_camctrl_caseAodd(ETH_device,&ETH_cam_prog);
      }  /* else */
     ETH_cam_end = ETH_cam_prog.ETH_cam_addr_hw;
   }	/* if((ETH_no_of_fields % 2)!= 0) */

  /* Even no of addresses */
  else if((ETH_no_of_fields % 2)== 0)
  {
    ETH_cam_prog.ETH_cam_addr_hw         = ETH_start_mac_addr - 1;
    ETH_cam_prog.ETH_cam_addr_user       = ETH_HW_RST;
    ETH_cam_prog.ETH_user_array_position = ETH_HW_SET;
    ETH_cam_prog.ETH_num_addr            = ETH_no_of_fields;
    ETH_camctrl_caseAeven(ETH_device,&ETH_cam_prog);
    ETH_cam_end = ETH_cam_prog.ETH_cam_addr_hw - 1;

   } /* else if((ETH_no_of_fields % 2)== 0) */
 } /* Process Case A */

  /* Process Case B */
  if(((ETH_start_mac_addr - 2) % 3) == 0)
  {
    ETH_cam_start =  ETH_start_mac_addr - 1;
    if((ETH_no_of_fields % 2)== 0)
    {
      ETH_cam_prog.ETH_cam_addr_hw = ETH_start_mac_addr - 1;
      ETH_camctrl_caseB(ETH_device,&ETH_cam_prog);
      if(ETH_no_of_fields > 2)
      {
        /* Only need to update the num of addr in this structure, the rest
          of the values are updated in the call to the previous function */
        ETH_cam_prog.ETH_num_addr = ETH_no_of_fields - 2;
        ETH_camctrl_caseAeven(ETH_device,&ETH_cam_prog);
      }  /* if(ETH_no_of_fields > 2)	*/

      ETH_camctrl_caseAodd(ETH_device,&ETH_cam_prog);
      ETH_cam_end = ETH_cam_prog.ETH_cam_addr_hw;
    }  /*	if((ETH_no_of_fields % 2)== 0)*/
    /* Odd num of addresses */
    else if((ETH_no_of_fields % 2)!= 0)
    {
      ETH_cam_prog.ETH_cam_addr_hw = ETH_start_mac_addr - 1;
      ETH_camctrl_caseB(ETH_device,&ETH_cam_prog);
      if(ETH_no_of_fields > ETH_HW_SET)
      {
        ETH_cam_prog.ETH_num_addr  = ETH_no_of_fields - 1;
        ETH_camctrl_caseAeven(ETH_device,&ETH_cam_prog);
      } /* if(ETH_no_of_fields > 1) */
      ETH_cam_end = ETH_cam_prog.ETH_cam_addr_hw - 1;
    } /* if((ETH_no_of_fields % 2)!= 0) */
  } /* Process Case B */
 
  /* Process case C */
  if((ETH_start_mac_addr % 3) == 0) 
  {
    ETH_cam_start =  ETH_start_mac_addr - 2;
    if((ETH_no_of_fields % 2)== 0)
    {
      ETH_cam_prog.ETH_cam_addr_hw = ETH_start_mac_addr - 2;
      ETH_camctrl_caseB(ETH_device,&ETH_cam_prog);
      if(ETH_no_of_fields > 2)
      {
        /* Only need to update the num of addr in this structure, the rest
          of the values are updated in the call to the previous function */
        ETH_cam_prog.ETH_num_addr = ETH_no_of_fields - 2;
        ETH_camctrl_caseAeven(ETH_device,&ETH_cam_prog);
      }   /* if(ETH_no_of_fields) */
      ETH_camctrl_caseAodd(ETH_device,&ETH_cam_prog);
      ETH_cam_end = ETH_cam_prog.ETH_cam_addr_hw;
    } /* if (ETH_no_of_fields % 2) */
    /* If the num of addresses are odd */
    else if((ETH_no_of_fields % 2)!= 0)
    {
      ETH_cam_prog.ETH_cam_addr_hw = ETH_start_mac_addr - 2;
      ETH_camctrl_caseB(ETH_device,&ETH_cam_prog);
      if(ETH_no_of_fields > 1)
      {
        ETH_cam_prog.ETH_num_addr            = ETH_no_of_fields - 1;
        ETH_camctrl_caseAeven(ETH_device,&ETH_cam_prog);
      }/* end of ETH_no_of_fields */
      ETH_cam_end = ETH_cam_prog.ETH_cam_addr_hw - 1;
    } /* else if*/
  } /* Process case C */

      
   /*First copy the MAC addresses into global structure ETH_params. By 
        using global structure write MAc addresses into CAM table*/
  for(ETH_i = ETH_cam_start; ETH_i <= ETH_cam_end; ETH_i++)
  {        
     /*
      The configuration data is maintained in the ETH_params 
      (global) structure
     */
    ETH_HW_MACCAMDATA = NTOHL(ETH_params.cam_data.mac_addrs[ETH_i]);
    ETH_HW_MACCAMADDR = ETH_i;
    /*Wait till the MAC CAM write busy flag cleared*/
    while(ETH_HW_MACCAMADDR & BIT32_MASK(ETH_HW_SET,ETH_HW_MACAMADDR_BSY))
    {
    }
        
  }/*End of for */
  break; /*ETH_ADD_MAC_ADDR*/

  case ETH_ENABLE_LOC:
    /*
      Copy the configuration data which are to be updated into the ETH_params 
      (global) structure, which will maintain the updated configuartion information
    */
    ETH_params.cam_data.addr_loc_enable = ETH_ctrl_data->data.mac_addr_data.addr_loc_enable;
    /*enable programmed MAC address inside CAM to filter the incoming frames*/
    ETH_HW_MACCAMCTRL1 = ETH_params.cam_data.addr_loc_enable;
    break;

  case ETH_RESET_CONF:
   /*
      Copy the configuration data which are to be updated into the ETH_params 
      (global) structure, which will maintain the updated configuartion information
    */
    ETH_params.cam_conf.broad_cast         = ETH_ctrl_data->data.conf_params.broad_cast;  /*broad cast frames*/
    ETH_params.cam_conf.cam_compare_enable = ETH_ctrl_data->data.conf_params.cam_compare_enable; /*enable the CAM*/
    ETH_params.cam_conf.multi_cast         = ETH_ctrl_data->data.conf_params.multi_cast;  /*multicast frames*/
    ETH_params.cam_conf.negative_cam       = ETH_ctrl_data->data.conf_params.negative_cam;  /*negative CAM*/
    ETH_params.cam_conf.uni_cast           = ETH_ctrl_data->data.conf_params.uni_cast;   /*unicast frames*/
     
    ETH_HW_MACCAMCTRL0 = BIT32_MASK(ETH_params.cam_conf.broad_cast, ETH_HW_MACCAMCTRL0_BRDACC)|
                         BIT32_MASK(ETH_params.cam_conf.cam_compare_enable, ETH_HW_MACCAMCTRL0_CMPEN)|
                         BIT32_MASK(ETH_params.cam_conf.multi_cast, ETH_HW_MACCAMCTRL0_GPRACC)|
                         BIT32_MASK(ETH_params.cam_conf.negative_cam, ETH_HW_MACCAMCTRL0_NEGCAM)|
                         BIT32_MASK(ETH_params.cam_conf.uni_cast, ETH_HW_MACCAMCTRL0_STACC);                                         
    break; /*ETH_RESET_CONF*/ 

    default:
      return ETH_ERR; /*unsupported operation*/        
  
  }/*End of switch*/

 
  return ETH_SUCCESS;
}
#endif  /*ETH_CFG_FUNC_CTRL_CAM*/


/*
*******************************************************************************
* Function Name:     ETH_ctrl_mac_tx
*
* Calling Functions: ETH_control_dev
*
* Functions Called:  None
*
* Description:
*   Change the MAC transmission control parameters
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_ctrl_data     - Contains the MAC new TX configuration data
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_CTRL_MAC_TX == 1 
ETH_STATUS ETH_ctrl_mac_tx(
ETH_DEVICE ETH_device,
ETH_MAC_TX_CONF *ETH_ctrl_data
)
{
  /*
    Copy the configuration data which are to be updated into the ETH_params 
    (global) structure, which will maintain the updated configuartion information
  */
  ETH_params.tx_conf.no_crc     =  ETH_ctrl_data->no_crc;   /*Do not add CRC*/
  ETH_params.tx_conf.no_defer   =  ETH_ctrl_data->no_defer;/*Do not check for delay*/
  ETH_params.tx_conf.no_pad     =  ETH_ctrl_data->no_pad;/*Do not add pad*/
  ETH_params.tx_conf.sqe_check  =  ETH_ctrl_data->sqe_check; /*signal quality error check*/
  ETH_params.tx_conf.send_pause =  ETH_ctrl_data->send_pause;  /*send pause*/
  ETH_params.tx_conf.tx_enable  =  ETH_ctrl_data->tx_enable;   /*enable MAC TX*/
  
  /*Write the new configuration data into MAC tx control register through global configuration structure*/
  ETH_HW_MACTXCTRL = BIT32_MASK(ETH_params.tx_conf.no_crc, ETH_HW_MACTXCTRL_NOCRC)|
                     BIT32_MASK(ETH_params.tx_conf.no_defer, ETH_HW_MACTXCTRL_NODEF)|
                     BIT32_MASK(ETH_params.tx_conf.no_pad, ETH_HW_MACTXCTRL_NOPAD)|
                     BIT32_MASK(ETH_params.tx_conf.sqe_check, ETH_HW_MACTXCTRL_MII10)|
                     BIT32_MASK(ETH_params.tx_conf.tx_enable, ETH_HW_MACTXCTRL_TXEN)|
                     BIT32_MASK(ETH_params.tx_conf.send_pause, ETH_HW_MACTXCTRL_SDPSE);

  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_CTRL_MAC_TX*/

/*
*******************************************************************************
* Function Name:     ETH_ctrl_mac_rx
*
* Calling Functions: ETH_control_dev
*
* Functions Called:  None
*
* Description:
*   Change the MAC receiver control parameters
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_ctrl_data     - Contains the MAC new receive configuration data
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_CTRL_MAC_RX == 1 
ETH_STATUS ETH_ctrl_mac_rx (
ETH_DEVICE ETH_device,
ETH_MAC_RX_CONF *ETH_ctrl_data
)
{
  /*
    Copy the configuration data which are to be updated into the ETH_params 
    (global) structure, which will maintain the updated configuartion information
  */
  ETH_params.rx_conf.accept_long    =  ETH_ctrl_data->accept_long;  /*accept long frames*/
  ETH_params.rx_conf.accept_short   =  ETH_ctrl_data->accept_short; /*accept short frames*/
  ETH_params.rx_conf.ignore_crc     =  ETH_ctrl_data->ignore_crc; /*do not check CRC*/
  ETH_params.rx_conf.pass_ctrl_pkts =  ETH_ctrl_data->pass_ctrl_pkts; /*pass control packets to LLC */
  ETH_params.rx_conf.strip_crc      =  ETH_ctrl_data->strip_crc;    /*remove the CRC*/
  ETH_params.rx_conf.rx_enable      =  ETH_ctrl_data->rx_enable;   /*enable MAC RX*/

  /*Write the new configuration data into MAC rx control register through global configuration structure*/
  ETH_HW_MACRXCTRL = BIT32_MASK(ETH_params.rx_conf.accept_long, ETH_HW_MACRXCTRL_LOEN)|
                     BIT32_MASK(ETH_params.rx_conf.accept_short, ETH_HW_MACRXCTRL_SHEN)|
                     BIT32_MASK(ETH_params.rx_conf.ignore_crc, ETH_HW_MACRXCTRL_IGNCRC)|
                     BIT32_MASK(ETH_params.rx_conf.pass_ctrl_pkts, ETH_HW_MACRXCTRL_PCTLP)|
                     BIT32_MASK(ETH_params.rx_conf.strip_crc, ETH_HW_MACRXCTRL_STRCRC)|
                     BIT32_MASK(ETH_params.rx_conf.rx_enable,ETH_HW_MACRXCTRL_RXEN);

  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_CTRL_MAC_RX*/


/*
*******************************************************************************
* Function Name:     ETH_ctrl_mac_phy
*
* Calling Functions: ETH_control_dev
*
* Functions Called:  None
*
* Description:
*   Change the physical device configuration settings
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_ctrl_data     - Contains the Phy device new configuration data
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_CTRL_MAC_PHY == 1 
ETH_STATUS ETH_ctrl_mac_phy(
ETH_DEVICE   ETH_device,
ETH_PHY_CTRL *ETH_ctrl_data
)
{
  IFX_UINT8 i = 0;
  if((ETH_ctrl_data->phy_num > ETH_HW_SUP_PHYDEV) || (ETH_ctrl_data->reg_num > ETH_HW_SUP_PHYREG))
  {
    return ETH_ERR;
  }


  /*write new configuration data into MAC station management data register*/
  if(ETH_ctrl_data->control == ETH_HW_SET)
  {
    ETH_HW_MACSMDATA = *ETH_ctrl_data->data; 
  }

  /*Write control data into MAC sttaion management control register*/
  ETH_HW_MACSMCTRL = BIT32_MASK(ETH_ctrl_data->control, ETH_HW_MACSMCTRL_WR)|
                     BIT32_MASK(ETH_ctrl_data->phy_num, ETH_HW_PHY_DEV)|
                     BIT32_MASK(ETH_ctrl_data->reg_num, ETH_HW_PHY_REG_ADDR);  

  /*Delay provided for the busy flag to being set*/
  i++; i++;

  /*Wait till the busy flag cleared*/
  while(ETH_HW_MACSMCTRL & BIT32_MASK(ETH_HW_SET,ETH_HW_MACSMCTRL_BUSY))
  {
  }

  if(ETH_ctrl_data->control == ETH_HW_RST)
  {
    *ETH_ctrl_data->data = ETH_HW_MACSMDATA; 
  }

  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_CTRL_MAC_PHY*/


/*
*******************************************************************************
* Function Name:     ETH_MACRX0_ISR
*
* Calling Functions: MACRX0 interrupt
*
* Functions Called:  
*
* Description:
*   This function will take the approprite action depend upon the interrupt 
*   occurred either by calling user provided routine or the defalut action 
*   provided by HAL
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

void ETH_MACRX0_ISR (IFX_UINT8 ETH_dev)
{
  /*Copy the interrupt status register value*/
  ETH_isr_val = ETH_HW_MACRX0ISR;

# if ETH_CFG_STAT_LOG == 1
  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXISR_CTLFRX)) /*control fram ereceived*/
  {
    ETH_statistics.rx_pause++;
  }
  
  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXISR_ALIGNE))/*alignment error*/
  {
    ETH_statistics.rx_align_err++;  
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXISR_CRCE)) /*CRC error*/
  {
    ETH_statistics.rx_crc_err++; 
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXISR_OVER)) /*over run error*/
  {
     ETH_statistics.rx_over++;
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXISR_LOE))  /*long frame error*/
  {
    ETH_statistics.rx_lng_frm++;
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXISR_GOOD))  /*received frame is good*/
  {
    ETH_statistics.rx_good_frms++;
  }
#endif /*ETH_CFG_STAT_LOG*/

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXISR_RXPE)) /*parity error*/
  {
  } 

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXISR_MROLL))  /*missed error count roll over*/
  {
     /*No action*/ 
  }
  
} /*end of MAC rx0 isr*/




/*
*******************************************************************************
* Function Name:     ETH_MACTX0_ISR
*
* Calling Functions: MACTX0 interrupt
*
* Functions Called:  
*
* Description:
*   This function will take the approprite action depend upon the interrupt 
*   occurred either by calling user provided routine or the defalut action 
*   provided by HAL
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

void ETH_MACTX0_ISR (IFX_UINT8 ETH_dev)
{
  ETH_isr_val = ETH_HW_MACTX0ISR;
 
  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_PSE)) /*pause send interrupt*/
  {
    ETH_HW_MACCAMCTRL1 = ETH_cam_addrs;

#   if ETH_CFG_STAT_LOG == 1
    ETH_statistics.tx_pause++;
#   endif /*ETH_CFG_STAT_LOG*/
  }

# if ETH_CFG_STAT_LOG == 1
  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_UNDER)) /*under run error*/
  {
    ETH_statistics.tx_under++;
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_XCOL))  /*excessive collision error*/
  {
    ETH_statistics.tx_excs_coll++;
  }
  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_TXDEF)) /*tx deferral error*/
  {
    ETH_statistics.tx_def++;
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_XDEF)) /*excessive deferral error*/
  {
    ETH_statistics.tx_def++;
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_LCAR)) /*lost carrier error*/
  {
    ETH_statistics.tx_lst_car++;
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_LCOL)) /*late collision*/
  {
    ETH_statistics.tx_late_coll++;
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_CMP)) /*one frame sent or discarded*/
  {
    ETH_statistics.tx_good_frms++;
  }
#endif /*ETH_CFG_STAT_LOG*/

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_TXHLTD))  /*tx halted*/
  {
    /*No action */
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_SQERR)) /*signal quality error*/
  {
  }

  if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXISR_TXP))  /*parity error*/
  {
  }

} /*end of MAC TX) isr*/

