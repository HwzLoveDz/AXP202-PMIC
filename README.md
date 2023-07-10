# AXP202-PMIC
AXP202 Power management IC（AXP202电源管理芯片）

![Static Badge](https://img.shields.io/badge/ESP_IDF_v5.0.1-build_pass-green) ![Static Badge](https://img.shields.io/badge/Arduino_IDE-build_pass-green)
  
|   文件名称(file name)   |                描述(description)                    |
|-------------------------|:--------------------------------------------------:|
|       README_CN.md      |   [中文文档(Chinese Document)](../main/README_CN.md)     |
|       README_EN.md      |   [英文文档(English Document)](../main/README.md)        |

**Note:** The document is machine translated and does not guarantee that all sentences will be smooth or error-free

***

The hardware part is open source in the Lichuang open source platform, link address: https://oshwhub.com/mondraker
Sometimes if it is not reviewed on Saturdays and Sundays, the project will disappear and you can see the backup on Github and Gitee

##### If there is a problem, directly into the Q group to bombard me: 735791683🧨
* Why not use the latest version of AXP2101? First of all, the AXP2101 has too many functions, and the current DIY small devices simply cannot use so much. Secondly, because the price of the main product is relatively expensive, it is 10 times that of AXP202 (but if you have friends who need to do it later, you can also make one)
* The project has been verified for a long time, providing packaging, 3D files, etc., **sufficient information (including ESP-IDF routines and Arduino routines, Chinese and English manuals)**, and this stamp hole is also **no extra charge** at no extra charge, do not choose the half-hole process to grind 🤣 it yourself
* One chip 1.8 yuan, the rest are resistance, capacitance and inductance, a piece of "own whole" **within three dollars**
* Related materials, [BOM form](https://easyeda.online/ibom/d5313712.html), and component-related links are attached at the end of the article
* After a while, I will come out with a whole batch of modules of gold immersion + half-hole process, and put them in the TB shop together with snowflake lights: [Ultraman's electronic planet](https://m.tb.cn/h.50LlvTB )

# Preface (Small Talk)
* Hello, everyone hasn't seen you for a long time, I haven't sent anything new for most of the year, and my friends think I'm retiring. In fact, I have been practicing in retreat during this time, busy with graduation projects, and learning ESP-IDF and LVGL by the way.
* The article may be relatively long, but this module is really easy to use, the information is very complete, I really hope that every interested friend can master him.
* Of course, I will share my gains during this period with you after sorting out the information later. Since the development board to be open source in two days also uses this power module, this module is first open sourced. (as shown below)

###### [Open source video trailer, click me directly](https://b23.tv/cWTMeIv)

**Development Board**
* ![_d2b7bf79fa147069585608b29f912e74_2058421563_IMG_20230605_010226.jpg](//image.lceda.cn/pullimage/ffs1rgARrk4CGtXn6rGWq2N8uoxCKglhOAL40ilj.jpeg)

**Module**
* ![_319bb24bc89965f34b9631be8bfa4303_2043390142_IMG_20230405_053358.jpg](//image.lceda.cn/pullimage/SMMdKNWd08V15bfMRKzG1ZhsrKQnsLqi27Mgt0ra.jpeg)

**Test Baseplate**
* ![_cbc7d0fb1028fe7791ffb7d338ac8aa4_-1316819711_IMG_20230405_214929.jpg](//image.lceda.cn/pullimage/q5st1CM3Uui1NpJAk5E47gbGW4pumzQHJbYmYjG8.jpeg)

**Commented schematics**
* ![image.png](//image.lceda.cn/pullimage/YG8DJv3uosd4ePHwaZi5ePjpApeGVVDAMkGgtFpI.png)
# Body (AXP202 Power Management Chip)
## Notes
### Since the chip has so many functions, I will divide it into the following parts for a general introduction
1. **Function part**: This part mainly introduces the design purpose, design ideas, chip functions, chip parameters and application scenarios

2. **Hardware part**: This part mainly introduces the chip peripheral circuit (detailing the functions and selection of each special device), module peripheral circuit (this part involves the default power supply voltage setting and boot mode setting), power module test backboard explanation, PCB parameters and precautions (thickness, etc.), power module wiring in the circuit (due to the particularity of the power module, it is easy to be unable to communicate)

3. **Software Part**: This part mainly introduces the functions implemented by the software, the use of routines, precautions, etc

4. **Video and related links section**: This part mainly includes the address of AXP173 project, the Github address of AXP202 project, the use of online bom and welding point tools (a very powerful thing developed by friends) and the video display and explanation of AXP202 module (strong response to launch a hand, now temporarily pigeon)

## Features section
### Design purpose
**1. When designing hardware, the power supply part has always been the beginning and top priority. I find that the core issues that are often discussed in everyone's daily production are:**
* How to design the power supply
* Find a small LDO
* Find an efficient DCDC
* Ask for a battery charging chip
* Where to find cheap power chips

**2. There are also many problems that players often encounter :**
* How to achieve efficient and reliable power path management of external input power supply and battery
* How to achieve long press to turn on and off
* How to accurately detect the battery level
* How to get the real-time status of the power supply
* What to do with low power consumption, what to do, what to do

**Well, I'll tell you now that there is a chip that can implement all the above functions, and is small in size, high efficiency, low in power consumption, and attractive in price???**
![URnAH7cTv6gCuqOy5Z4qxFvb3I1NyOPSmuxq8xZs.jpg](//image.lceda.cn/pullimage/7qMHDGjPcgOlcNlfwt1rZ9sW9wYM6GS07yrAI2Au.jpeg)

### Chip function
**1. on the function. (Official documentation is below)**
* ![image.png](//image.lceda.cn/pullimage/7w72JYYedE5s0W1BAYEc86i5ZDeMrI5z0zby43St.png)

**2. on the overview. (Official documentation is below)**
* ![image.png](//image.lceda.cn/pullimage/GP2aJmtgdLcGMumzadhl4XKqPvvHQUc1MoMuQIt3.png)

### Chip parameters
**Here are mainly examples of power output capability parameters, other power parameters go to the data sheet. (Official documentation is below)**
* ![image.png](//image.lceda.cn/pullimage/LSnzo0pJiIUbIjNl9iX3ptXHtbDqOHgLBEbE5z4p.png)

**If you also need 5V output, then the use of module IPSOUT pin + DCDC5V buck circuit can be easily achieved, the output capability depends on the input capability of the external power supply, and the chip has an EXTEN pin to control the EN pin of the external DCDC chip, saving the functional pin of the NCU, too fragrant. (Official documentation is below)**
* ![image.png](//image.lceda.cn/pullimage/i5WTlJJDraZPyycNXcWMh9lPiVbAHHEAOXJBBj6d.png)

### Design ideas
**It is convenient to use the stamp hole module type directly, because the resistance and capacitance parameters on the periphery of this chip are relatively strange.**
* In order to facilitate the design and soldering of PCB circuit boards and increase the success rate, this design adopts modular thinking, the AXP202 peripheral circuit is packaged as a stamp hole module soldered to the motherboard, and all the user-defined pins are led out, so that it is convenient to use the resistance of the corresponding resistance value on the motherboard to configure these pins.

* In order to unify the package, the design uses a standard 2.54mm pitch LCC stamp hole for easy soldering, and a 4-layer PCB design is used to reduce the package size and bring out all the necessary functions.
### Application scenario
**All devices containing a microcontroller. (Official documentation is below)**
* ![image.png](//image.lceda.cn/pullimage/HEQwvxnE6qjbVrJj8zVFqoB5K8cEPffItrp0ZkWl.png)

## Hardware section
### Chip peripheral circuitry
**The schematic is written in detail, here is a brief summary**

* First of all, the power input part, **as shown in the upper left area of the figure**. VBAT is the positive terminal of the battery, and a 0603 package is connected in parallel with a 10uF withstand 16V capacitor for filtering. ACIN is an external DC power supply pin, which can accommodate 5V/2A power supply entry, VBUS is an external USB power input, which can accommodate 5V/1A power supply entry, so a 0603 package 4.7uF capacitor is connected in parallel for power supply filtering, and two 2.2ohm resistors are deliberately connected in series to prevent oscillation, reduce the capacitor charging speed, and better absorb the noise of the power supply. This section can also be paralleled with Zener diodes at the power supply to reduce the risk of high-voltage breakdown, which is not added due to the size limitation of the module and the fact that it is not functionally sensitive. BACKUP is the positive terminal of the external backup battery, connected to a conventional RTC/BIOS battery.

* This is followed by the DCDC buck section, **as shown in the upper right area of the figure**. This part of the circuit is an independent area that requires external access to the system input power supply IPSOUT, which can reduce the internal voltage IPSOUT to the power chip voltage regulation range, if the application does not need to use a DC-DC only need to suspend the corresponding LX pin. 4.7uH inductance is recommended when the output voltage is below 2.5V, 2.2uH inductance is recommended when the output voltage is above 2.5V, and the inductor saturation current needs to be greater than 50% of the maximum required current, here because 4.7uH has 0806 package, so all 4.7uH is used, also to reduce the volume. R17 must be 30mΩ/1%/1206 resistance, PCB layout attention chip 42/43 pin must be connected to R17 resistance PAD to ensure that the signal is detected directly from the resistor PAD, because R17 for the battery charging current, discharge current and charging voltage of the detection resistance, not only high accuracy but also need to strictly consider interference in the layout.

* This is followed by the exit of the signal and function pins, as well as the circuit section outside the internal reference voltage of the chip, **as shown in the lower left area of the figure**. The following two GPIOs have additional functions in addition to the normal input and output capability: GPIO0: ADC/LDO5 (output drive capability of 50mA), GPIO1: ADC. PWRON is the power chip boot pin, active low, R24 pull-up to LDO1 to prevent false triggering. N_OE can be used to power on the device directly via an external power supply. N_VBUSEN to choose whether VBUS power is enabled. IRQ interrupt signal pin with optional pull-up to LDO1 or MCU_3V3. I2C uses a 2.2k resistor to pull up to MCU_3V3.

* Finally, there is the LDO (Low Dropout Linear Regulator) output section, **see the lower right area of the figure**. This part is also a separate area in the functional block diagram, which requires an external access system to supply ISPOUT. PWROK is the MCU enable pin, and the RESET button is connected to the EN pin of the MCU to restart the MCU and pull up to the MCU power supply pin. DC3SET sets the pin for DCDC3 voltage, 3.3V/2.5V for APS or LDO1, 1.8V for ground, and 1.2V/1.5V for floating.

* ![image.png](//image.lceda.cn/pullimage/X4woxNgmqruelxnTaWXAmYhlLGWWm0RNQDbuJxbt.png)

### Module peripheral circuit
**The picture below is very detailed, not to be repeated**

* ! [image.png](//image.lceda.cn/pullimage/VszxQchkluWsXu4dG2SMuFcAxNRDk1XwAHZYWBdA.png)

### Power module test backplane explanation
**As shown in the figure above, all functions are introduced, some pins that can be set externally on the chip can be set using a jump cap, and a 5V DCDC boost is added for basic testing, and the ground wire leads less and can be added at your discretion. Or draw a test board according to the main control chip to be used, my test base board is only used to screen which chip is suitable and basic functional testing, because I directly drew the ESP32 test board, so I did not continue to optimize this base board (there may be a breadboard module later).**

### Wiring of the power module in the circuit
**Compared with ordinary I2C modules, the power management module also provides power to the main control chip, in addition, AXP202 must be in the boot state, must be common, otherwise the two can not communicate normally.**
* ![image.png](//image.lceda.cn/pullimage/nLxiASZE4IW4GAFWith4E4AoF3nTgg6F819VBKs1.png)

### PCB parameters and stamp hole handling considerations
**Place a single 1mm (the picture below is 1.6mm very thick, just for demonstration purposes), four layers. There is no need for the half-hole process, after coming back, it is crimped, and you need to use tweezers to cut out the excess copper in the half-hole, and then grind it off with sandpaper of about 800 mesh. (The following is a simple step-by-step demonstration)**

* Before processing (silver for OK, yellow for OK)
* ![image.png](//image.lceda.cn/pullimage/lRpBQKPbU0i1J5V6IaK7F4ISxZmJc6iSZmtUagZd.png)
* Processing (tweezers pick out)
* ![image.png](//image.lceda.cn/pullimage/jOGUzUurIuknZpiqp5UKYJd5lZsCd9RF7YCeC2fh.png)
* Processing (after picking out)
* ![image.png](//image.lceda.cn/pullimage/N860zAH1iG7s5QtRMuuAAezCrEGovbtPjySwvReO.png)
* ![image.png](//image.lceda.cn/pullimage/nm9qtwo0qybdDF7w6k0nKtD5P99uqkNjXUiJoUMo.png)
* In process (sanding)
* There is no picture, don't try too hard, grind and take a look, don't grind the copper on the edge of the board.
* After treatment (you can use higher mesh sandpaper to polish it finely)
* ![image.png](//image.lceda.cn/pullimage/BOd3kRjWBB3XF0VdpwqmbQaYnDy1I1ulPjdFDVEL.png)

### PS
**The hole on the top of the module is for easy disassembly and assembly**
* ![image.png](//image.lceda.cn/pullimage/MesyEzT6YU60ztrWkv2JfnCbp4E7RthF5Hh8JRpx.png)

## Software section
### **[GitHub link](https://github.com/HwzLoveDz/AXP202-PMIC)**
### **[Gitee link](https://gitee.com/mondraker/AXP202-PMIC)**
### Statement:
* axp20x libraries and Arduino-related routines are all from Lewis He, thanks to the open source (open source license: MIT)
* Original GitHub link: github:https://github.com/lewisxhe/AXP202X_Libraries
* Subsequent routines will be written around this library, adding other commonly used registers and functions, such as LED indicator charging control, etc., and future changes will be updated to GitHub/Gitee

### Description:
* The library is also compatible with AXP173/192/202, etc
* Basically realize all the functions of the chip
* There are relevant function comments in the code, which can be studied and written with the official register document
* The code is written using an independent I2C interface, and only need to write an interface library to port to other platforms, which is very convenient
* **If you have doubts in the code, you can refer to this open source [AXP173](https://oshwhub.com/mondraker/axp173) to learn, or bombard me in the crowd**

## Video and related links section
* **[GitHub profile](https://github.com/HwzLoveDz)**
* **[Gitee profile](https://gitee.com/mondraker)**
* **[bilibili homepage](https://space.bilibili.com/240319986)** **(here is the AXP202 (QFN) chip soldering tutorial)**
* **[Online BOM address](https://easyeda.online/ibom/d5313712.html)** **(developed by a friend, like ibom, but online, and mobile phone can also be browsed, a later issue will focus on him)**
* **QQ Group Number: 735791683**
* **Device purchase link in accessory BOM**
