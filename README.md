# DDS-Generator

## Description
This project is a continuation of the [DDS generator project](https://github.com/Ivanchenko59/AD9833-DDS-Generator), which I did on the STM32F401.
<br/>Please be careful, the project is still under development.

The purpose of this project is to create a small ***educational 
project*** based on the STM32 microcontroller using the HAL library, and also, ***writing a library of the AD9833 chip for experience***.


## About the project

A simple signal generator on the AD9833 chip, which is a DDS generator of different waveform and frequency.
The maximum frequency of the output signal is 12.5 MHz with a reference signal frequency of 25 MHz.
The STM32G030F6P6TR microcontroller is used to control the DDS generator.
A TFT display with a diagonal of 1.8 inches is used to display information.
To conrtor the microcontroller, I used an encoder with hardware filtering on a Schmidt trigger.
As well as two variable resistors for adjusting the amplitude and offset of the output signal.
The device is powered by an external voltage source of 12-24 V.

![real](https://user-images.githubusercontent.com/80352225/184535827-93554862-d8d9-4a83-a0f8-d5a4b4c77bb9.png)


## Demonstration video

#### User interface
[![Watch the video](https://img.youtube.com/vi/uW_SvFu_fgc/maxresdefault.jpg)](https://youtu.be/watch?v=uW_SvFu_fgc)

#### Old video from the previous repo
[![Watch the video](https://img.youtube.com/vi/vuJpcqhaOHE/maxresdefault.jpg)](https://youtu.be/watch?v=vuJpcqhaOHE)



## Hardware
![PCB](https://user-images.githubusercontent.com/80352225/184502538-2017a99e-a252-4bb0-b0b4-01e5778f5521.png)

To obtain +12V -12V voltage for the output amplified signal of the generator, 
I used the simplest converter circuit from unipolar to bipolar power, built on a voltage divider with a common point, 
and zero stabilization using an operational amplifier and transistors.

Digital and analog ground are separate to reduce output signal noise.

Amplification and offset of the signal is performed by introducing variable resistors into the feedback loop of the operational amplifier.
According to the principle of operation of the DDS generator and the Nyquist theorem, the maximum frequency of generation is 12.5 MHz for a sinusoidal signal, 
however, such a signal is not suitable for use. 

![real_signal](https://user-images.githubusercontent.com/80352225/184502605-d94545ff-11dc-41c4-9f69-12b37e33ed89.png)

For this, an LC filter of order 7 with a cutoff frequency of 12 MHz was calculated.

![frequency_response](https://user-images.githubusercontent.com/80352225/184502660-c1378533-367a-41c0-becf-198d0a95220e.png)

We have a signal without distortion and amplitude reduction, up to 5 MHz.

![signal_filter](https://user-images.githubusercontent.com/80352225/184502667-ee98db24-779c-41ca-882a-cac6ef6d8d4d.png)


## Software
### CubeMX Connectivity 
![cubemx](https://user-images.githubusercontent.com/80352225/184538673-1ab3bb5b-ec7c-4a1b-81c4-84b61ac819d7.png)

### SPI Config for ST7735 display

````C++
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
````
Redefine SPI PORT if necessary in st7735.h file
````C++
#define ST7735_SPI_PORT   hspi1
````

### SPI Config for AD9833 Gen

````C++
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
````

Redefine SPI PORT if necessary in AD9833.h file
````C++
#define AD9833_SPI_PORT   hspi2
````

### Config Timer for rotary encoder
Enable "Combined Channels" to Encoder Mode in any Timer. The default settings are fine.
<br/>Edit TIM PORT definition in encoder.h
````C++
#define ENC_TIM_PORT      htim3
````
### Lack of memory
I ran into an out-of-memory problem because STM32G030 has only 32KB of FLASH memory. This is quite small when using the HAL library.
<br/>So I used ![custom sprinf_ implementation](https://github.com/mpaland/printf) cuz original sprintf weight too much.
<br/>I also selected Optimization level to -Os that means optimize for size.
<br/>After that I was able to compile the code.

![memory](https://user-images.githubusercontent.com/80352225/184540004-554691e8-f233-4bc1-9f92-76c356c65294.png)

## Bill of materials
You can find ![bill of materials](hardware/Bill_of_Materials.xlsx) in repository.
<br/>Electronic components cost about $15. The PCB's cost $2 for 5 pieces and $10 for shipping.
<br/>Total cost: around $30

## Futures 
- [x] Make PCB board
- [ ] Add oscilloscope measurements
- [ ] Add Sweep mode
- [ ] Add Noise mode

## Disclaimer
The following project is shared "as is", with the sole objective of being useful. 
The creator of the described piece of hardware and its associated software cannot guarantee its correct functioning under any circumstance. 
The author of this project will not be held responsible for any material, personal or economic losses to you or any third parties that may arise from using this design. 
This project will not be used under any circumstances on systems whose responsibility is critical, or from which people's lives depend upon, directly or indirectly.
