﻿#pragma once
/*
1.1.1操作系统的概念、功能和目标

处理机管理-存储器管理-文件管理-设备管理
命令接口-程序接口-GUI
**操作系统的特征**并发-共享-虚拟-异步****
并发：指两个或多个事件在同一时间间隔内发生。
共享：互斥共享和同时共享
虚拟：是指把一个物理上的实体变为若干个逻辑上的对应物。
异步：在多道程序环境下允许多个程序并发执行，但由于资源有限，进程的执行\
	不是一贯到底的，而是走走停停，以不可预知的速度向前推进，这就是进程的异步性

多道程序技术
*/
/*
1.1.3操作系统的发展和分类
手工操作阶段-批处理阶段：单道批处理系统-批处理阶段：多道批处理系统\
分时操作系统：时间片为单位-实时操作系统：优先响应一些紧急的任务，特点\
=及时性和可靠性，分类=硬实时系统+软实时系统
-其他几种操作系统：网络操作系统，分布式操作系统，个人计算机操作系统
*/

/*
1.1.4操作系统的运行机制和体系结构
*指令=处理器能识别、执行最基本的命令
*类别=特权指令 + 非特权指令
*两种处理器状态=用户态（目态）+核心态（管态）..用程序状态字寄存器PSW区分,用户态与核心态之间的转换是通过*中断*实现的
*两种程序=内核程序+应用程序
*操作系统的微内核：最接近纯硬件的一层=时钟管理+中断处理+原语（设备驱动、CPU切换等）
*大内核=微内核+（进程管理+存储管理等）
*大内核高性能但是代码庞大，结构混乱，难以维护。微内核相反.
*/

/*1.1.5中断和异常
*中断机制的诞生：早期的计算机各程序只能串行运行
*本质：只要发生中断就需要操作系统介入、开展管理工作
*概念和作用：
1.中断发生时CPU立即进入核心态 
2.当中断发生后当前的进程暂停运行并由操作系统内核对中断进行处理
*分类=内中断（异常）+外中断（狭义中断），区别在于信号来源是CPU内部还是外部。
1.内中断=自愿中断/指令中断 + 强迫中断/硬件故障与软件中断等。（内中断=陷入trap+故障fault+终止abort）
2.外中断=外设I/O中断请求+人工干预
*外中断处理过程：
1.每条指令执行结束以后，CPU检查是否有外部中断信号
2.若有则保护被中断进程的CPU环境 
3.根据中断信号类型输入相应的中断处理程序 （核心态）
4.恢复\原进程的CPU环境并退出中断，返回原进程继续往下执行。
*/

/*1.1.6系统调用
*什么是系统调用：操作系统作为用户和计算机硬件之间的接口，需要向上提供一些简单易用的服务，主要包括*命令接口和*程序接口，其中程序接口由一组系统调用组成。
系统调用是操作系统提供给应用程序（程序员）使用的接口，可以理解为一种可供应用程序调用的特殊函数，应用程序可以发出系统调用请求来获得操作系统的服务。
*为什么要有系统调用：打印机、打印店问题。应用程序通过系统调用请求操作系统的服务。稳定 、安全
*分类：
1.设备管理：完后设备的请求、释放、启动等功能
2.文件管理：完成文件的读写创建删除等
3.进程控制：完成进程的创建、撤销、阻塞、唤醒等
4.进程通信：完成进程之间的消息传递、信号传递等
5.内存管理：完成内存的分配、回收等功能

*/