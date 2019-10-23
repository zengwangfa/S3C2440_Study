/*
制  作:www.100ask.org深圳百问网科技有限公司
工程师：韦东山
当前版本：v1.0
*/

#ifndef  __S3C2440_SOC_H
#define  __S3C2440_SOC_H

#define     __REG(x)					(*(volatile unsigned int *)(x)) 

/*Memory Controllers*/
#define     BWSCON                   __REG(0x48000000)   //Bus width & wait status control   
#define     BANKCON0                 __REG(0x48000004)   //Boot ROM control                  
#define     BANKCON1                 __REG(0x48000008)   //BANK1 control                     
#define     BANKCON2                 __REG(0x4800000C)   //BANK2 control                     
#define     BANKCON3                 __REG(0x48000010)   //BANK3 control                     
#define     BANKCON4                 __REG(0x48000014)   //BANK4 control                     
#define     BANKCON5                 __REG(0x48000018)   //BANK5 control                     
#define     BANKCON6                 __REG(0x4800001C)   //BANK6 control                     
#define     BANKCON7                 __REG(0x48000020)   //BANK7 control                     
#define     REFRESH                  __REG(0x48000024)   //DRAM/SDRAM refresh control        
#define     BANKSIZE                 __REG(0x48000028)   //Flexible bank size                
#define     MRSRB6                   __REG(0x4800002C)   //Mode register set for SDRAM BANK6 
#define     MRSRB7                   __REG(0x48000030)   //Mode register set for SDRAM BANK7 

/*USB Host Controller*/ 
#define     HcRevision               __REG(0x49000000)
#define     HcControl                __REG(0x49000004)
#define     HcCommonStatus           __REG(0x49000008)
#define     HcInterruptStatus        __REG(0x4900000C)
#define     HcInterruptEnable        __REG(0x49000010)
#define     HcInterruptDisable       __REG(0x49000014)
#define     HcHCCA                   __REG(0x49000018)
#define     HcPeriodCuttentED        __REG(0x4900001C)
#define     HcControlHeadED          __REG(0x49000020)
#define     HcControlCurrentED       __REG(0x49000024)
#define     HcBulkHeadED             __REG(0x49000028)
#define     HcBulkCurrentED          __REG(0x4900002C)
#define     HcDoneHead               __REG(0x49000030)
#define     HcRmInterval             __REG(0x49000034)
#define     HcFmRemaining            __REG(0x49000038)
#define     HcFmNumber               __REG(0x4900003C)
#define     HcPeriodicStart          __REG(0x49000040)
#define     HcLSThreshold            __REG(0x49000044)
#define     HcRhDescriptorA          __REG(0x49000048)
#define     HcRhDescriptorB          __REG(0x4900004C)
#define     HcRhStatus               __REG(0x49000050)
#define     HcRhPortStatus1          __REG(0x49000054)
#define     HcRhPortStatus2          __REG(0x49000058)

/*Interrupt Controller*/
#define     SRCPND                   __REG(0X4A000000)  //Interrupt request status       
#define     INTMOD                   __REG(0X4A000004)  //Interrupt mode control         
#define     INTMSK                   __REG(0X4A000008)  //Interrupt mask control         
#define     PRIORITY                 __REG(0X4A00000C)  //IRQ priority control           
#define     INTPND                   __REG(0X4A000010)  //Interrupt request status       
#define     INTOFFSET                __REG(0X4A000014)  //Interrupt request source offset
#define     SUBSRCPND                __REG(0X4A000018)  //Sub source pending             
#define     INTSUBMSK                __REG(0X4A00001C)  //Interrupt sub mask    
    
/*DMA*/ 
#define     DISRC0                   __REG(0x4B000000)  //DMA 0 initial source              
#define     DISRCC0                  __REG(0x4B000004)  //DMA 0 initial source control      
#define     DIDST0                   __REG(0x4B000008)  //DMA 0 initial destination         
#define     DIDSTC0                  __REG(0x4B00000C)  //DMA 0 initial destination control 
#define     DCON0                    __REG(0x4B000010)  //DMA 0 control                     
#define     DSTAT0                   __REG(0x4B000014)  //DMA 0 count                       
#define     DCSRC0                   __REG(0x4B000018)  //DMA 0 current source              
#define     DCDST0                   __REG(0x4B00001C)  //DMA 0 current destination         
#define     DMASKTRIG0               __REG(0x4B000020)  //DMA 0 mask trigger                
#define     DISRC1                   __REG(0x4B000040)  //DMA 1 initial source              
#define     DISRCC1                  __REG(0x4B000044)  //DMA 1 initial source control      
#define     DIDST1                   __REG(0x4B000048)  //DMA 1 initial destination         
#define     DIDSTC1                  __REG(0x4B00004C)  //DMA 1 initial destination control 
#define     DCON1                    __REG(0x4B000050)  //DMA 1 control                     
#define     DSTAT1                   __REG(0x4B000054)  //DMA 1 count                       
#define     DCSRC1                   __REG(0x4B000058)  //DMA 1 current source              
#define     DCDST1                   __REG(0x4B00005C)  //DMA 1 current destination         
#define     DMASKTRIG1               __REG(0x4B000060)  //DMA 1 mask trigger                
#define     DISRC2                   __REG(0x4B000080)  //DMA 2 initial source              
#define     DISRCC2                  __REG(0x4B000084)  //DMA 2 initial source control      
#define     DIDST2                   __REG(0x4B000088)  //DMA 2 initial destination         
#define     DIDSTC2                  __REG(0x4B00008C)  //DMA 2 initial destination control 
#define     DCON2                    __REG(0x4B000090)  //DMA 2 control                     
#define     DSTAT2                   __REG(0x4B000094)  //DMA 2 count                       
#define     DCSRC2                   __REG(0x4B000098)  //DMA 2 current source              
#define     DCDST2                   __REG(0x4B00009C)  //DMA 2 current destination         
#define     DMASKTRIG2               __REG(0x4B0000A0)  //DMA 2 mask trigger                
#define     DISRC3                   __REG(0x4B0000C0)  //DMA 3 initial source              
#define     DISRCC3                  __REG(0x4B0000C4)  //DMA 3 initial source control      
#define     DIDST3                   __REG(0x4B0000C8)  //DMA 3 initial destination         
#define     DIDSTC3                  __REG(0x4B0000CC)  //DMA 3 initial destination control 
#define     DCON3                    __REG(0x4B0000D0)  //DMA 3 control                     
#define     DSTAT3                   __REG(0x4B0000D4)  //DMA 3 count                       
#define     DCSRC3                   __REG(0x4B0000D8)  //DMA 3 current source              
#define     DCDST3                   __REG(0x4B0000DC)  //DMA 3 current destination         
#define     DMASKTRIG3               __REG(0x4B0000E0)  //DMA 3 mask trigger     

/*Clock & Power Management*/
#define     LOCKTIME                 __REG(0x4C000000)  //PLL lock time counter         
#define     MPLLCON                  __REG(0x4C000004)  //MPLL control                  
#define     UPLLCON                  __REG(0x4C000008)  //UPLL control                  
#define     CLKCON                   __REG(0x4C00000C)  //Clock generator control       
#define     CLKSLOW                  __REG(0x4C000010)  //Slow clock control            
#define     CLKDIVN                  __REG(0x4C000014)  //Clock divider control         
#define     CAMDIVN                  __REG(0x4C000018)  //Camera clock divider control  

/*LCD Controller*/
#define	    LCDCON1  	             __REG(0X4D000000)  //LCD control 1                          
#define	    LCDCON2  	             __REG(0X4D000004)  //LCD control 2                          
#define	    LCDCON3  	             __REG(0X4D000008)  //LCD control 3                          
#define	    LCDCON4  	             __REG(0X4D00000C)  //LCD control 4                          
#define	    LCDCON5  	             __REG(0X4D000010)  //LCD control 5                          
#define	    LCDSADDR1	             __REG(0X4D000014)  //STN/TFT: frame buffer start address 1  
#define	    LCDSADDR2	             __REG(0X4D000018)  //STN/TFT: frame buffer start address 2  
#define	    LCDSADDR3	             __REG(0X4D00001C)  //STN/TFT: virtual screen address set    
#define	    REDLUT   	             __REG(0X4D000020)  //STN: red lookup table                  
#define	    GREENLUT 	             __REG(0X4D000024)  //STN: green lookup table                
#define	    BLUELUT  	             __REG(0X4D000028)  //STN: blue lookup table                 
#define	    DITHMODE 	             __REG(0X4D00004C)  //STN: dithering mode                    
#define	    TPAL     	             __REG(0X4D000050)  //TFT: temporary palette                 
#define	    LCDINTPND	             __REG(0X4D000054)  //LCD interrupt pending                  
#define	    LCDSRCPND	             __REG(0X4D000058)  //LCD interrupt source                   
#define	    LCDINTMSK	             __REG(0X4D00005C)  //LCD interrupt mask                     
#define	    TCONSEL  	             __REG(0X4D000060)  //TCON(LPC3600/LCC3600) control    

/*NAND Flash*/

#define     NFCONF                   __REG(0x4E000000)  //NAND flash configuration             
#define     NFCONT                   __REG(0x4E000004)  //NAND flash control                   
#define     NFCMD                    __REG(0x4E000008)  //NAND flash command                   
#define     NFADDR                   __REG(0x4E00000C)  //NAND flash address                   
#define     NFDATA                   __REG(0x4E000010)  //NAND flash data                      
#define     NFMECC0                  __REG(0x4E000014)  //NAND flash main area ECC0/1          
#define     NFMECC1                  __REG(0x4E000018)  //NAND flash main area ECC2/3          
#define     NFSECC                   __REG(0x4E00001C)  //NAND flash spare area ECC            
#define     NFSTAT                   __REG(0x4E000020)  //NAND flash operation status          
#define     NFESTAT0                 __REG(0x4E000024)  //NAND flash ECC status for I/O[7:0]   
#define     NFESTAT1                 __REG(0x4E000028)  //NAND flash ECC status for I/O[15:8]  
#define     NFMECC0_STATUS           __REG(0x4E00002C)  //NAND flash main area ECC0 status     
#define     NFMECC1_STATUS           __REG(0x4E000030)  //NAND flash main area ECC1 status     
#define     NFSECC_STATUS            __REG(0x4E000034)  //NAND flash spare area ECC status     
#define     NFSBLK                   __REG(0x4E000038)  //NAND flash start block address       
#define     NFEBLK                   __REG(0x4E00003C)  //NAND flash end block address       

/*Camera Interface*/
#define     CISRCFMT                 __REG(0x4F000000)  //Input source format                                
#define     CIWDOFST                 __REG(0x4F000004)  //Window offset register                             
#define     CIGCTRL                  __REG(0x4F000008)  //Global control register                            
#define     CICOYSA1                 __REG(0x4F000018)  //Y 1st frame start address for codec DMA            
#define     CICOYSA2                 __REG(0x4F00001C)  //Y 2nd frame start address for codec DMA            
#define     CICOYSA3                 __REG(0x4F000020)  //Y 3nd frame start address for codec DMA            
#define     CICOYSA4                 __REG(0x4F000024)  //Y 4th frame start address for codec DMA            
#define     CICOCBSA1                __REG(0x4F000028)  //Cb 1st frame start address for codec DMA           
#define     CICOCBSA2                __REG(0x4F00002C)  //Cb 2nd frame start address for codec DMA           
#define     CICOCBSA3                __REG(0x4F000030)  //Cb 3nd frame start address for codec DMA           
#define     CICOCBSA4                __REG(0x4F000034)  //Cb 4th frame start address for codec DMA           
#define     CICOCRSA1                __REG(0x4F000038)  //Cr 1st frame start address for codec DMA           
#define     CICOCRSA2                __REG(0x4F00003C)  //Cr 2nd frame start address for codec DMA           
#define     CICOCRSA3                __REG(0x4F000040)  //Cr 3nd frame start address for codec DMA           
#define     CICOCRSA4                __REG(0x4F000044)  //Cr 4th frame start address for codec DMA           
#define     CICOTRGFMT               __REG(0x4F000048)  //Target image format of codec DMA                   
#define     CICOCTRL                 __REG(0x4F00004C)  //Codec DMA control related                          
#define     CICOSCPRERATIO           __REG(0x4F000050)  //Codec pre-scaler ratio control                     
#define     CICOSCPREDST             __REG(0x4F000054)  //Codec pre-scaler destination format                
#define     CICOSCCTRL               __REG(0x4F000058)  //Codec main-scaler control                          
#define     CICOTAREA                __REG(0x4F00005C)  //Codec scaler target area                           
#define     CICOSTATUS               __REG(0x4F000064)  //Codec path status                                  
#define     CIPRCLRSA1               __REG(0x4F00006C)  //RGB 1st frame start address for preview DMA        
#define     CIPRCLRSA2               __REG(0x4F000070)  //RGB 2nd frame start address for preview DMA        
#define     CIPRCLRSA3               __REG(0x4F000074)  //RGB 3nd frame start address for preview DMA        
#define     CIPRCLRSA4               __REG(0x4F000078)  //RGB 4th frame start address for preview DMA        
#define     CIPRTRGFMT               __REG(0x4F00007C)  //Target image format of preview DMA                 
#define     CIPRCTRL                 __REG(0x4F000080)  //Preview DMA control related                        
#define     CIPRSCPRERATIO           __REG(0x4F000084)  //Preview pre-scaler ratio control                   
#define     CIPRSCPREDST             __REG(0x4F000088)  //Preview pre-scaler destination format              
#define     CIPRSCCTRL               __REG(0x4F00008C)  //Preview main-scaler control                        
#define     CIPRTAREA                __REG(0x4F000090)  //Preview scaler target area                         
#define     CIPRSTATUS               __REG(0x4F000098)  //Preview path status                                
#define     CIIMGCPT                 __REG(0x4F0000A0)  //Image capture enable command       

/*UART*/
#define     ULCON0                   __REG(0x50000000)  //UART 0 line control      
#define     UCON0                    __REG(0x50000004)  //UART 0 control           
#define     UFCON0                   __REG(0x50000008)  //UART 0 FIFO control      
#define     UMCON0                   __REG(0x5000000C)  //UART 0 modem control     
#define     UTRSTAT0                 __REG(0x50000010)  //UART 0 Tx/Rx status      
#define     UERSTAT0                 __REG(0x50000014)  //UART 0 Rx error status   
#define     UFSTAT0                  __REG(0x50000018)  //UART 0 FIFO status       
#define     UMSTAT0                  __REG(0x5000001C)  //UART 0 modem status    
#define     UTXH0                    __REG(0x50000020)  //UART 0 transmission hold 
#define     URXH0                    __REG(0x50000024)  //UART 0 receive buffer    
#define     UBRDIV0                  __REG(0x50000028)  //UART 0 baud rate divisor 
#define     ULCON1                   __REG(0x50004000)  //UART 1 line control      
#define     UCON1                    __REG(0x50004004)  //UART 1 control           
#define     UFCON1                   __REG(0x50004008)  //UART 1 FIFO control      
#define     UMCON1                   __REG(0x5000400C)  //UART 1 modem control     
#define     UTRSTAT1                 __REG(0x50004010)  //UART 1 Tx/Rx status      
#define     UERSTAT1                 __REG(0x50004014)  //UART 1 Rx error status   
#define     UFSTAT1                  __REG(0x50004018)  //UART 1 FIFO status       
#define     UMSTAT1                  __REG(0x5000401C)  //UART 1 modem status        
#define     UTXH1                    __REG(0x50004020)  //UART 1 transmission hold 
#define     URXH1                    __REG(0x50004024)  //UART 1 receive buffer   
#define     UBRDIV1                  __REG(0x50004028)  //UART 1 baud rate divisor 
#define     ULCON2                   __REG(0x50008000)  //UART 2 line control      
#define     UCON2                    __REG(0x50008004)  //UART 2 control           
#define     UFCON2                   __REG(0x50008008)  //UART 2 FIFO control       
#define     UTRSTAT2                 __REG(0x50008010)  //UART 2 Tx/Rx status      
#define     UERSTAT2                 __REG(0x50008014)  //UART 2 Rx error status   
#define     UFSTAT2                  __REG(0x50008018)  //UART 2 FIFO status       
#define     UTXH2                    __REG(0x50008020)  //UART 2 transmission hold 
#define     URXH2                    __REG(0x50008024)  //UART 2 receive buffer     
#define     UBRDIV2                  __REG(0x50008028)  //UART 2 baud rate divisor 

/*PWM Timer*/                  
#define     TCFG0                    __REG(0x51000000)  //Timer configuration         
#define     TCFG1                    __REG(0x51000004)  //Timer configuration         
#define     TCON                     __REG(0x51000008)  //Timer control               
#define     TCNTB0                   __REG(0x5100000C)  //Timer count buffer 0        
#define     TCMPB0                   __REG(0x51000010)  //Timer compare buffer 0      
#define     TCNTO0                   __REG(0x51000014)  //Timer count observation 0   
#define     TCNTB1                   __REG(0x51000018)  //Timer count buffer 1        
#define     TCMPB1                   __REG(0x5100001C)  //Timer compare buffer 1      
#define     TCNTO1                   __REG(0x51000020)  //Timer count observation 1   
#define     TCNTB2                   __REG(0x51000024)  //Timer count buffer 2        
#define     TCMPB2                   __REG(0x51000028)  //Timer compare buffer 2      
#define     TCNTO2                   __REG(0x5100002C)  //Timer count observation 2   
#define     TCNTB3                   __REG(0x51000030)  //Timer count buffer 3        
#define     TCMPB3                   __REG(0x51000034)  //Timer compare buffer 3      
#define     TCNTO3                   __REG(0x51000038)  //Timer count observation 3   
#define     TCNTB4                   __REG(0x5100003C)  //Timer count buffer 4        
#define     TCNTO4                   __REG(0x51000040)  //Timer count observation 4  

/*USB Device*/  
#define     FUNC_ADDR_REG            __REG(0x52000140)  //Function address                            
#define     PWR_REG                  __REG(0x52000144)  //Power management                            
#define     EP_INT_REG               __REG(0x52000148)  //interrupt pending and clear                 
#define     USB_INT_REG              __REG(0x52000158)  //USB interrupt pending and clear             
#define     EP_INT_EN_REG            __REG(0x5200015C)  //Interrupt enable                            
#define     USB_INT_EN_REG           __REG(0x5200016C)  //Interrupt enable                            
#define     FRAME_NUM1_REG           __REG(0x52000170)  //Frame number lower byte                     
#define     FRAME_NUM2_REG           __REG(0x52000174)  //Frame number higher byte                    
#define     INDEX_REG                __REG(0x52000178)  //Register index                              
#define     EP0_CSR                  __REG(0x52000184)  //Endpoint 0 status                           
#define     IN_CSR1_REG              __REG(0x52000184)  //In endpoint control status                  
#define     IN_CSR2_REG              __REG(0x52000188)  //In endpoint control status                  
#define     MAXP_REG                 __REG(0x52000180)  //Endpoint max packet                         
#define     OUT_CSR1_REG             __REG(0x52000190)  //Out endpoint control status                 
#define     OUT_CSR2_REG             __REG(0x52000194)  //Out endpoint control status                 
#define     OUT_FIFO_CNT1_REG        __REG(0x52000198)  //Endpoint out write count                    
#define     OUT_FIFO_CNT2_REG        __REG(0x5200019C)  //Endpoint out write count                    
#define     EP0_FIFO                 __REG(0x520001C0)  //Endpoint 0 FIFO                             
#define     EP1_FIFO                 __REG(0x520001C4)  //Endpoint 1 FIFO                             
#define     EP2_FIFO                 __REG(0x520001C8)  //Endpoint 2 FIFO                             
#define     EP3_FIFO                 __REG(0x520001CC)  //Endpoint 3 FIFO                             
#define     EP4_FIFO                 __REG(0x520001D0)  //Endpoint 4 FIFO                             
#define     EP1_DMA_CON              __REG(0x52000200)  //EP1 DMA Interface control                   
#define     EP1_DMA_UNIT             __REG(0x52000204)  //EP1 DMA Tx unit counter                     
#define     EP1_DMA_FIFO             __REG(0x52000208)  //EP1 DMA Tx FIFO counter                     
#define     EP1_DMA_TTC_L            __REG(0x5200020C)  //EP1 DMA Total Tx counter                    
#define     EP1_DMA_TTC_M            __REG(0x52000210)  //EP1 DMA Total Tx counter                    
#define     EP1_DMA_TTC_H            __REG(0x52000214)  //EP1 DMA Total Tx counter                    
#define     EP2_DMA_CON              __REG(0x52000218)  //EP2 DMA interface control                   
#define     EP2_DMA_UNIT             __REG(0x5200021C)  //EP2 DMA Tx Unit counter                     
#define     EP2_DMA_FIFO             __REG(0x52000220)  //EP2 DMA Tx FIFO counter                     
#define     EP2_DMA_TTC_L            __REG(0x52000224)  //EP2 DMA total Tx counter                    
#define     EP2_DMA_TTC_M            __REG(0x52000228)  //EP2 DMA total Tx counter                    
#define     EP2_DMA_TTC_H            __REG(0x5200022C)  //EP2 DMA Total Tx counter                    
#define     EP3_DMA_CON              __REG(0x52000240)  //EP3 DMA Interface control                   
#define     EP3_DMA_UNIT             __REG(0x52000244)  //EP3 DMA Tx Unit counter                     
#define     EP3_DMA_FIFO             __REG(0x52000248)  //EP3 DMA Tx FIFO counter                     
#define     EP3_DMA_TTC_L            __REG(0x5200024C)  //EP3 DMA Total Tx counter                    
#define     EP3_DMA_TTC_M            __REG(0x52000250)  //EP3 DMA Total Tx counter                    
#define     EP3_DMA_TTC_H            __REG(0x52000254)  //EP3 DMA Total Tx counter                    
#define     EP4_DMA_CON              __REG(0x52000258)  //EP4 DMA Interface control                   
#define     EP4_DMA_UNIT             __REG(0x5200025C)  //EP4 DMA Tx Unit counter                     
#define     EP4_DMA_FIFO             __REG(0x52000260)  //EP4 DMA Tx FIFO counter                     
#define     EP4_DMA_TTC_L            __REG(0x52000264)  //EP4 DMA Total Tx counter                    
#define     EP4_DMA_TTC_M            __REG(0x52000268)  //EP4 DMA Total Tx counter                    
#define     EP4_DMA_TTC_H            __REG(0x5200026C)  //EP4 DMA Total Tx counter       
        
/* WOTCHDOG register */  
#define     WTCON                    __REG(0x53000000) 
#define     WTDAT                    __REG(0x53000004) 
#define     WTCNT                    __REG(0x53000008) 
        
/* I2C registers */ 
#define     IICCON  	             __REG(0x54000000)  // IIC control                    
#define     IICSTAT 	             __REG(0x54000004)  // IIC status                     
#define     IICADD  	             __REG(0x54000008)  // IIC address                    
#define     IICDS   	             __REG(0x5400000c)  // IIC data shift                 
#define     IICLC		             __REG(0x54000010)  //IIC multi-master line control   
                                                        
/*IIS*/                                                 
#define     IISCON 	                 __REG(0x55000000)  //HW,W R/W IIS control
#define     IISMOD 	                 __REG(0x55000004)  //IIS mode            
#define     IISPSR 	                 __REG(0x55000008)  //IIS prescaler       
#define     IISFCON	                 __REG(0x5500000C)  //IIS FIFO control    
#define     IISFIFO	                 __REG(0x55000010)  //HW IIS FIFO entry   
        
/*I/O port*/
#define     GPACON                   __REG(0x56000000)  //Port A control                           
#define     GPADAT                   __REG(0x56000004)  //Port A data                                      
#define     GPBCON                   __REG(0x56000010)  //Port B control                                   
#define     GPBDAT                   __REG(0x56000014)  //Port B data                                      
#define     GPBUP                    __REG(0x56000018)  //Pull-up control B                                
#define     GPCCON                   __REG(0x56000020)  //Port C control                                   
#define     GPCDAT                   __REG(0x56000024)  //Port C data                                      
#define     GPCUP                    __REG(0x56000028)  //Pull-up control C                                
#define     GPDCON                   __REG(0x56000030)  //Port D control                                   
#define     GPDDA1T                  __REG(0x56000034)  //Port D data                                      
#define     GPDUP                    __REG(0x56000038)  //Pull-up control D                                
#define     GPECON                   __REG(0x56000040)  //Port E control                                   
#define     GPEDAT                   __REG(0x56000044)  //Port E data                                      
#define     GPEUP                    __REG(0x56000048)  //Pull-up control E                                
#define     GPFCON                   __REG(0x56000050)  //Port F control                                   
#define     GPFDAT                   __REG(0x56000054)  //Port F data                                      
#define     GPFUP                    __REG(0x56000058)  //Pull-up control F                                
#define     GPGCON                   __REG(0x56000060)  //Port G control                                   
#define     GPGDAT                   __REG(0x56000064)  //Port G data                                      
#define     GPGUP                    __REG(0x56000068)  //Pull-up control G                                
#define     GPHCON                   __REG(0x56000070)  //Port H control                                   
#define     GPHDAT                   __REG(0x56000074)  //Port H data                                      
#define     GPHUP                    __REG(0x56000078)  //Pull-up control H                                
#define     GPJCON                   __REG(0x560000D0)  //Port J control                                   
#define     GPJDAT                   __REG(0x560000D4)  //Port J data                                      
#define     GPJUP                    __REG(0x560000D8)  //Pull-up control J                                
#define     MISCCR                   __REG(0x56000080)  //Miscellaneous control                            
#define     DCLKCON                  __REG(0x56000084)  //DCLK0/1 control                                  
#define     EXTINT0                  __REG(0x56000088)  //External interrupt control register 0            
#define     EXTINT1                  __REG(0x5600008C)  //External interrupt control register 1            
#define     EXTINT2                  __REG(0x56000090)  //External interrupt control register 2            
#define     EINTFLT0                 __REG(0x56000094)  //? W R/W Reserved                                 
#define     EINTFLT1                 __REG(0x56000098)  //Reserved                                         
#define     EINTFLT2                 __REG(0x5600009C)  //External interrupt filter control register 2     
#define     EINTFLT3                 __REG(0x560000A0)  //External interrupt filter control register 3     
#define     EINTMASK                 __REG(0x560000A4)  //External interrupt mask                          
#define     EINTPEND                 __REG(0x560000A8)  //External interrupt pending                       
#define     GSTATUS0                 __REG(0x560000AC)  //R External pin status                            
#define     GSTATUS1                 __REG(0x560000B0)  //R/W Chip ID                                      
#define     GSTATUS2                 __REG(0x560000B4)  //Reset status                                     
#define     GSTATUS3                 __REG(0x560000B8)  //Inform register                                  
#define     GSTATUS4                 __REG(0x560000BC)  //Inform register                                  
#define     MSLCON                   __REG(0x560000CC)  //Memory sleep control register                    
        
/*RTC*/     
#define     RTCCON 		             __REG(0x57000040)  //RTC control       
#define     TICNT  		             __REG(0x57000044)  //Tick time count   
#define     RTCALM 		             __REG(0x57000050)  //RTC alarm control 
#define     ALMSEC 		             __REG(0x57000054)  //Alarm second      
#define     ALMMIN 		             __REG(0x57000058)  //Alarm minute      
#define     ALMHOUR		             __REG(0x5700005C)  //Alarm hour        
#define     ALMDATE		             __REG(0x57000060)  //alarm day         
#define     ALMMON 		             __REG(0x57000064)  //Alarm month       
#define     ALMYEAR		             __REG(0x57000068)  //Alarm year        
#define     BCDSEC 		             __REG(0x57000070)  //BCD second        
#define     BCDMIN 		             __REG(0x57000074)  //BCD minute        
#define     BCDHOUR		             __REG(0x57000078)  //BCD hour          
#define     BCDDATE		             __REG(0x5700007C)  //BCD day           
#define     BCDDAY 		             __REG(0x57000080)  //BCD date          
#define     BCDMON 		             __REG(0x57000084)  //BCD month         
#define     BCDYEAR		             __REG(0x57000088)  //BCD year      
        
/*A/D Converte*/
#define     ADCCON                   __REG(0x58000000)  //ADC control                        
#define     ADCTSC                   __REG(0x58000004)  //ADC touch screen control           
#define     ADCDLY                   __REG(0x58000008)  //ADC start or interval delay        
#define     ADCDAT0                  __REG(0x5800000C)  //ADC conversion data                
#define     ADCDAT1                  __REG(0x58000010)  //ADC conversion data                
#define     ADCUPDN                  __REG(0x58000014)  //Stylus up or down interrupt status 

/*SPI CONTROL REGISTER*/ 
#define     SPCON0                   __REG(0x59000000)  //SPI channel 0 control register
#define     SPSTA0                   __REG(0x59000004)  //SPI channel 0 status register
#define     SPPIN0                   __REG(0x59000008)  //SPI channel 0 pin control register
#define     SPPRE0                   __REG(0x5900000C)  //SPI cannel 0 baud rate prescaler register
#define     SPTDAT0                  __REG(0x59000010)  //SPI channel 0 Tx data register
#define     SPRDAT0                  __REG(0x59000014)  //SPI channel 0 Rx data register
#define     SPCON1                   __REG(0x59000020)  //SPI channel 1 control register                                     
#define     SPSTA1                   __REG(0x59000024)  //SPI channel 1 status register                                     
#define     SPPIN1                   __REG(0x59000028)  // SPI channel 1 pin control register
#define     SPPRE1                   __REG(0x5900002C)  //SPI cannel 1 baud rate prescaler register
#define     SPTDAT1                  __REG(0x59000030)  //SPI channel 1 Tx data register                                    
#define     SPRDAT1                  __REG(0x59000034)  //SPI channel 1 Rx data register

/*SD Interface*/
#define     SDICON   		         __REG(0x5A000000)  //SDI control            
#define     SDIPRE   		         __REG(0x5A000004)  //SDI baud rate prescaler
#define     SDICARG  		         __REG(0x5A000008)  //SDI command argument   
#define     SDICCON  		         __REG(0x5A00000C)  //SDI command control    
#define     SDICSTA  		         __REG(0x5A000010)  //SDI command status     
#define     SDIRSP0  		         __REG(0x5A000014)  //SDI response           
#define     SDIRSP1  		         __REG(0x5A000018)  //SDI response           
#define     SDIRSP2  		         __REG(0x5A00001C)  //SDI response           
#define     SDIRSP3  		         __REG(0x5A000020)  //SDI response           
#define     SDIDTIMER		         __REG(0x5A000024)  //SDI data / busy timer  
#define     SDIBSIZE 		         __REG(0x5A000028)  //SDI block size         
#define     SDIDCON  		         __REG(0x5A00002C)  //SDI data control       
#define     SDIDCNT  		         __REG(0x5A000030)  //SDI data remain counter
#define     SDIDSTA  		         __REG(0x5A000034)  //SDI data status        
#define     SDIFSTA  		         __REG(0x5A000038)  //SDI FIFO status        
#define     SDIIMSK  		         __REG(0x5A00003C)  //SDI interrupt mask     
#define     SDIDAT   		         __REG(0x5A000040)  //SDI data               

#endif



