![logo0](http://i1.piimg.com/567571/17f3a253350d7d2b.png)![logo1](http://i1.piimg.com/567571/f66b867e7cbfc3ba.png)

# old Driver


Repo for logitech g27 development
## Requirements
Hardware:
* Logitech G27

  ​

Lib:
* G27 drivers
* LogitechSteeringWheelSDK_8.70.319

  ​

## Installing / Getting started
###0x00 Install Logitech G27 drivers
Go to the official website of [__Logitech__](https://support.logitech.com/zh_cn/home) to get the driver.

###0x01 Build
In _**oldDriver**_ folder:
`oldDriver.cpp` : a very simple case to get the data from G27 and then print. Those data can be send to server by __socket__ or __http post__ with the help some library.

`LogitechSteeringWheelLib.lib` : the static link library offered by Logitech in [__**SteeringWheelSDK v8.70.319**__ ](http://gaming.logitech.com/sdk/LogitechSteeringWheelSDK_8.70.319.zip), the latest version can be found on [sdk for developers](http://gaming.logitech.com/zh-cn/developers)

`LogitechSteeringWheelLib.h` : .h file for the library



