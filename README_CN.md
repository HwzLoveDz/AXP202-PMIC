# AXP202-PMIC
AXP202 Power management IC（AXP202电源管理芯片）

![Static Badge](https://img.shields.io/badge/ESP_IDF_v5.0.1-build_pass-green) ![Static Badge](https://img.shields.io/badge/Arduino_IDE-build_pass-green)
  
|   文件名称(file name)   |                描述(description)                    |
|-------------------------|:--------------------------------------------------:|
|       README_CN.md      |   [中文文档(Chinese Document)](../README_CN.md)     |
|       README_EN.md      |   [英文文档(English Document)](../README.md)        |

***

硬件部分开源在立创开源平台，链接地址：https://oshwhub.com/mondraker
有时候周六周天不审核，工程会消失，可以在Github和Gitee看到备份

##### 有问题直接进Q群轰炸我:735791683🧨
* 为什么不用最新版AXP2101呢？首先AXP2101功能太多，目前DIY的小型设备根本用不了那么多。其次由于是主推产品价格相对较贵，是AXP202的10倍（不过要是有朋友需要后期也可以搞一个出来）
* 该项目已经过长期验证，提供封装，3D文件等等，**资料充足（包含ESP-IDF例程以及Arduino例程，中英文手册）**，并且这个邮票孔自己打也**不需要额外收费**，不选半孔工艺自己磨一下就行了🤣
* 一块芯片1.8元，其它都是阻容和电感，一片“自己整”**三块钱以内**
* 相关资料、[BOM表单](https://easyeda.online/ibom/d5313712.html)以及元器件相关链接都在文末附件里
* 过段时间自己会整一批沉金＋半孔工艺的模块出来，和雪花灯一起放在TB小店里：[奥特曼的电子星球](https://m.tb.cn/h.50LlvTB )

# 前言(闲聊)
* Hello，大家好久不见，大半年没发新东西了，小伙伴都以为我隐退了。其实这段时间一直在闭关修炼，忙毕业设计，顺便学习一下ESP-IDF和LVGL。
* 文章可能相对较长，但是这个模块确实非常好用，资料非常齐全，真心希望每一个感兴趣的朋友都可以将他掌握。
* 当然了，后面整理一下资料会把自己这段时间的收获分享给大家。由于过两天要开源的开发板也用到了这个电源模块，因此先开源这个模块。（如下图）

###### [开源视频预告，直接点我](https://b23.tv/cWTMeIv)
**开发板**
* ![_d2b7bf79fa147069585608b29f912e74_2058421563_IMG_20230605_010226.jpg](//image.lceda.cn/pullimage/ffs1rgARrk4CGtXn6rGWq2N8uoxCKglhOAL40ilj.jpeg)
**模块**
* ![_319bb24bc89965f34b9631be8bfa4303_2043390142_IMG_20230405_053358.jpg](//image.lceda.cn/pullimage/SMMdKNWd08V15bfMRKzG1ZhsrKQnsLqi27Mgt0ra.jpeg)
**测试底板**
* ![_cbc7d0fb1028fe7791ffb7d338ac8aa4_-1316819711_IMG_20230405_214929.jpg](//image.lceda.cn/pullimage/q5st1CM3Uui1NpJAk5E47gbGW4pumzQHJbYmYjG8.jpeg)
**注释过的原理图**
* ![image.png](//image.lceda.cn/pullimage/YG8DJv3uosd4ePHwaZi5ePjpApeGVVDAMkGgtFpI.png)
# 正文（AXP202电源管理芯片）
## 注意事项
### 由于芯片功能非常多，因此我分为以下几部分进行大致介绍
1. **功能部分**：这部分主要介绍设计目的，设计思路，芯片功能，芯片参数以及应用场景

2. **硬件部分**：这部分主要介绍了芯片外围电路（详述各个特殊器件功能以及选型），模块外围电路（这部分涉及到默认电源电压设置以及开机方式设置），电源模块测试底板讲解，PCB参数与注意事项（厚度等等），电源模块在电路中的接线（由于电源模块的特殊性导致容易无法通讯）

3. **软件部分**：这部分主要介绍软件实现的功能，例程的使用，注意事项等等

4. **视频与相关链接部分**：这部分主要有AXP173工程的地址，AXP202工程的Github地址，在线bom和焊接点位工具（朋友开发的一种非常厉害的东西）的使用方法以及AXP202模块的视频展示与讲解（反响强烈就推出一手，现在暂时鸽一下下）

## 功能部分
### 设计目的
**1. 在硬件设计时，电源部分一直是万事开头、重中之重。我发现在大家平时的制作里经常讨论的核心问题就是：**
* 电源怎么设计
* 求一个体积小的LDO
* 求一个效率高的DCDC
* 求一个电池充电芯片
* 哪里有便宜的电源芯片

**2. 还有很多玩家经常遇到的问题：**
* 外部输入电源和电池怎么实现高效可靠的电源通路管理
* 怎么实现长按开关机
* 怎么精确的检测电池电量
* 怎么获取电源实时状态
* 低功耗怎么办怎么办怎么办怎么办怎么办怎么办

**那么好，我现在告诉你，有一个芯片，他可以实现上述的所有功能，并且体积小、效率高、功耗低、价格香你心动吗？？？**
![URnAH7cTv6gCuqOy5Z4qxFvb3I1NyOPSmuxq8xZs.jpg](//image.lceda.cn/pullimage/7qMHDGjPcgOlcNlfwt1rZ9sW9wYM6GS07yrAI2Au.jpeg)

### 芯片功能
**1. 上功能。（官方文档如下）**
* ![image.png](//image.lceda.cn/pullimage/7w72JYYedE5s0W1BAYEc86i5ZDeMrI5z0zby43St.png)

**2. 上概述。（官方文档如下）**
* ![image.png](//image.lceda.cn/pullimage/GP2aJmtgdLcGMumzadhl4XKqPvvHQUc1MoMuQIt3.png)

### 芯片参数
**这里主要举例电源输出能力参数，其它电源参数去数据手册里看。（官方文档如下）**
* ![image.png](//image.lceda.cn/pullimage/LSnzo0pJiIUbIjNl9iX3ptXHtbDqOHgLBEbE5z4p.png)

**如果你还需要5V输出，那么使用模块IPSOUT脚＋DCDC5V的buck电路即可轻松实现，输出能力取决于外部供电的输入能力，且芯片专门有一个EXTEN脚控制外部DCDC芯片的EN脚，节省NCU的功能引脚，太香了。（官方文档如下）**
* ![image.png](//image.lceda.cn/pullimage/i5WTlJJDraZPyycNXcWMh9lPiVbAHHEAOXJBBj6d.png)

### 设计思路
**做成邮票孔模块类型方便大家直接使用，因为这种芯片外围的阻容参数都比较奇怪。**
* 为方便PCB电路板的设计与焊接，增加成功率，本设计采用模块化思想，将AXP202外围电路封装为一个邮票孔模块焊接在主板上，将可用户自定义的管脚全部引出，这样就可以方便的在主板上使用相应阻值的电阻来配置这些引脚。

* 为统一封装，本次设计使用了标准2.54mm间距LCC邮票孔，便于焊接，使用了4层PCB设计用以缩小封装体积，引出全部必要的功能。
### 应用场景
**所有包含单片机的设备。（官方文档如下）**
* ![image.png](//image.lceda.cn/pullimage/HEQwvxnE6qjbVrJj8zVFqoB5K8cEPffItrp0ZkWl.png)

## 硬件部分
### 芯片外围电路
**原理图里写的很详细，这里简单概括一下**

* 首先是电源输入部分，**如图左上方区域**。VBAT为电池正极接入端，并联一个0603封装10uF耐压16V的电容用以滤波。ACIN为外部DC电源供电脚，可以容纳5V/2A电源进入，VBUS为外部USB电源输入，可以容纳5V/1A的电源进入，因此分别并联了一个0603封装4.7uF的电容用以电源滤波，故意串联两个2.2ohm的电阻用以防止震荡，降低电容充电速度，更好地吸收电源的噪声。该部分在电源处还可以并联齐纳二极管减少高电压击穿危险，由于模块体积限制以及功能上并不敏感，因此没有添加。BACKUP为外部备用电池正极，接常规RTC/BIOS电池。

* 其次是DCDC降压部分，**如图右上方区域**。这一部分电路为独立区域，需要外部接入系统输入电源IPSOUT,其可以让内部电压IPSOUT降压到电源芯片调压范围之内，如果应用中不需要用到某个 DC-DC只需要将对应的 LX 管脚悬空即可。输出电压2.5V以下时推荐4.7uH电感，输出电压2.5V以上时推荐2.2uH电感，电感饱和电流需大于最大需求电流50%，这里由于4.7uH有0806封装所以全用4.7uH，同样是为了减少体积。R17务必为30mΩ/1%/1206电阻，PCB布线注意芯片42/43脚务必接R17电阻PAD，以确保直接从电阻PAD检测到信号，因为R17为电池充电电流，放电电流与与充电电压的检测电阻，不仅精度要高还需要在布局时严格考虑干扰。

* 之后便是信号与功能引脚的引出，以及芯片内部参考电压外围的电路部分，**如图左下方区域**。以下两个GPIO除了具有常规输入输出能力以外还具有其他功能：GPIO0:ADC/LDO5(输出驱动能力为50mA)，GPIO1:ADC。PWRON为电源芯片开机脚，低电平有效，R24上拉至LDO1防止误触发。N_OE可以用来通过外部电源接入直接开机设备。N_VBUSEN用以选择是否使能VBUS供电。IRQ中断信号引脚，可选上拉至LDO1或MCU_3V3。I2C使用2.2k电阻上拉至MCU_3V3。

* 最后是LDO（低压差线性稳压器）输出部分，**如图右下方区域**。该部分在功能框图中同样为独立区域，需要外部接入系统供电ISPOUT。PWROK为MCU使能引脚，RESET按键接在MCU的EN管脚上可以实现MCU的重启，上拉至MCU供电脚。DC3SET为DCDC3电压设置管脚，接APS或LDO1为3.3V/2.5V，接地为1.8V，悬空为1.2V/1.5V。

* ![image.png](//image.lceda.cn/pullimage/X4woxNgmqruelxnTaWXAmYhlLGWWm0RNQDbuJxbt.png)

### 模块外围电路
**下图中写的很详细，不在赘述**

* ![image.png](//image.lceda.cn/pullimage/VszxQchkluWsXu4dG2SMuFcAxNRDk1XwAHZYWBdA.png)

### 电源模块测试底板讲解
**如上图引出了所有的功能，芯片外部可设置的一些引脚可以使用跳帽设置，并且加入了一个5V的DCDC升压，用以基本测试，地线引出较少，可以自己酌情添加。或者根据要使用的主控芯片自己绘制一个测试板，我这个测试底板只是用以筛选哪家芯片合适以及基本的功能测试，因为自己直接画了ESP32的测试板所以没有再继续优化这个底板（后续可能会有面包板模块吧）。**

### 电源模块在电路中的接线
**相较于普通的I2C模块，电源管理模块还要给主控芯片提供电源，除此之外，AXP202必须在开机状态下，一定要共地，否则两者之间是无法正常通信的。**
![image.png](//image.lceda.cn/pullimage/nLxiASZE4IW4GAFWith4E4AoF3nTgg6F819VBKs1.png)

### PCB参数与邮票孔处理注意事项
**下单打1mm（下面图是1.6mm的非常厚，仅用以演示），四层。不需要半孔工艺，回来之后是卷边的，需要先用镊子把半孔里多余的铜抠出来，然后用800目左右砂纸磨掉就行了。（以下是简单的步骤演示）**

* 处理前（银色代表OK，黄色代表不OK）
* ![image.png](//image.lceda.cn/pullimage/lRpBQKPbU0i1J5V6IaK7F4ISxZmJc6iSZmtUagZd.png)
* 处理中（镊子挑出来）
* ![image.png](//image.lceda.cn/pullimage/jOGUzUurIuknZpiqp5UKYJd5lZsCd9RF7YCeC2fh.png)
* 处理中（挑出来之后）
* ![image.png](//image.lceda.cn/pullimage/N860zAH1iG7s5QtRMuuAAezCrEGovbtPjySwvReO.png)
* ![image.png](//image.lceda.cn/pullimage/nm9qtwo0qybdDF7w6k0nKtD5P99uqkNjXUiJoUMo.png)
* 处理中（打磨打磨）
* 没图了，别太用力就行，磨一磨看一看，别把板边的铜磨出来了。
* 处理后（自己可以用更高目砂纸精细打磨一下）
* ![image.png](//image.lceda.cn/pullimage/BOd3kRjWBB3XF0VdpwqmbQaYnDy1I1ulPjdFDVEL.png)

### PS
**模块上面那个洞是为了方便拆装的**
* ![image.png](//image.lceda.cn/pullimage/MesyEzT6YU60ztrWkv2JfnCbp4E7RthF5Hh8JRpx.png)

## 软件部分
### **[GitHub链接](https://github.com/HwzLoveDz/AXP202-PMIC)**
### **[Gitee链接](https://gitee.com/mondraker/AXP202-PMIC)**
### 声明：
* axp20x库以及Arduino相关例程，均来自于Lewis He大佬，感谢大佬的开源（开源协议：MIT）
* 原GitHub链接： github:https://github.com/lewisxhe/AXP202X_Libraries
* 后续自己的例程都将围绕该库编写，自己添加了其它一些常用的寄存器与功能，比如LED指示灯的充电控制等等，以后的修改将同步更新至GitHub/Gitee

### 说明：
* 该库同时兼容AXP173/192/202等
* 基本实现了芯片所有的功能
* 代码中有相关功能注释，可以配合官方寄存器文档进行学习与编写
* 代码中使用独立的I2C接口进行编写，移植至其他平台只需要写一个接口库即可，非常方便
* **代码中有疑惑可以参照这一篇开源的[AXP173](https://oshwhub.com/mondraker/axp173)进行学习，或者进群轰炸我**

## 视频以及相关链接部分
* **[GitHub个人主页](https://github.com/HwzLoveDz)**
* **[Gitee个人主页](https://gitee.com/mondraker)**
* **[b站个人主页](https://space.bilibili.com/240319986)** **（这里有这次的AXP202(QFN)芯片焊接教程哦）**
* **[在线BOM地址](https://easyeda.online/ibom/d5313712.html)** **（朋友开发，和ibom一样，但是是在线的，并且手机也可以浏览，后期会出一期文章重点介绍他）**
* **QQ交流群号：735791683**
* **器件购买链接在附件BOM中**
* **更全的软件资料都打包在GitHub，登不上GitHub的可以加群下载，因为资料需要实时更新，不在这里给审核添麻烦了**
