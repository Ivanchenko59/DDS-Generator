# DDS-Generator

## Description
This project is a continuation of the [DDS generator project](https://github.com/Ivanchenko59/AD9833-DDS-Generator), which I did on the STM32F401. 

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

Тут реальные фотки

## Demonstration video

какое то фото

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

<img src="https://user-images.githubusercontent.com/80352225/184502752-71bc7429-2ef9-4094-ba6a-3fadb3849047.png" width="500">

![зображення](https://user-images.githubusercontent.com/80352225/184502754-1759c41a-24f4-4da2-9529-92b81a2dffe7.png)
![зображення](https://user-images.githubusercontent.com/80352225/184502761-d8381a91-a918-4bf0-9d69-e6505a29a833.png)
![зображення](https://user-images.githubusercontent.com/80352225/184502764-559bbd52-4270-47ff-9c60-12bf3216f2c8.png)



Плата проектировалась под корпус.

## Software
про мою либу, про нехватку памяти и тайни принтф

## Bills of material and cost

## Futures 


## Disclaimer
The following project is shared "as is", with the sole objective of being useful. 
The creator of the described piece of hardware and its associated software cannot guarantee its correct functioning under any circumstance. 
The author of this project will not be held responsible for any material, personal or economic losses to you or any third parties that may arise from using this design. 
This project will not be used under any circumstances on systems whose responsibility is critical, or from which people's lives depend upon, directly or indirectly.
