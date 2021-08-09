﻿/*$1
互联网的组成：边缘部分和核心部分（网络和连接它们的路由器）
A与B进行通信：进程之间的通信(计算机之间的通信)：有C/S模式与P2P方式，c/s模式的客户端是请求端，主动发起请求
服务器启动后一直不断运行，被动地等待并接收来自各地的客户的通信请求
1.3.2互联网的核心-【路由器】
路由器是实现【分组交换】的核心部件（打电话的时候使用交换机-电路交换，即【电路转接】。这个是面向连接的，在通信的过程中始终占用端到端的通信资源）
在计算机网络中计算机数据具有【突发性】（电路交换的缺点-利用率很低）
分组packet交换switch采用【存储转发】技术，在每一个数据段前面加上‘首部’构成分组'packet'，作为传输单元
首部 包含 ‘地址’等控制信息
*路由器处理packet的过程：
1.收到的分组先放入缓存（对象是分组，方式是分组转发）
2.查找转发表，找到某个目的地址和端口
3.把分组送到适当的端口并把它发出去。
分组交换的优点：高效：动态分配传输带宽，对通信链路是逐段占用 灵活 迅速：可以不先建立连接 可靠：保证可靠的网络协议
分组交换的问题：时延：分组在各节点存储转发的时候需要排队 额外开销：首部
主机和路由器不同，主机是为用户进行信息传输的。
*性能指标:
-速率（额定速率） bit是计算机中数据量的单位，也是信息论中数据量的单位 bps
-带宽:
-吞吐量：单位时间内通过某个网络的数据量。它和带宽是相关的
-时延delay-发送时延-传播时延-处理时延-排队时延-
-往返时间RTT
-利用率包含信道利用率和网络利用率
1.5计算机网络的定义
计算机网络主要是由一些通用的、可编程的硬件互连而成的，这些硬件并非专门用来实现某一特定的目的，
这些可编程的硬件能够用来传送多种不同类型的数据，并能支持广发的和日益增长的应用。
1.5.2计算机网络的分类

1.7计算机网络的体系结构（是计算机网络各层及其协议的集合）
1.7.1计算机网络体系结构的形成
分层可以将庞大而复杂的问题，转化为若干较小的局部问题，而这些较小的局部问题就比较容易研究和处理
网络协议的三个组成要素：语义，语法，同步
-开放系统互连参考模型OSI（7层模型）--非国际标准（事实标准：TCP/IP是四层协议：物理层+数据链路层=网络接口层）
-折中/科学的办法：五层协议 ：【物理层 数据链路层 网络层 传输层 应用层】
1.7.5路由器进行分组转发的时候最高使用到网络层（123），没有使用过传输层和应用层（45）
*/

/*$2物理层
信道：表示某一个方向传送信息的媒体
单向通信：（单工）
双向交替通信：（半双工）
双向同时通信：（全双工）
基带信号：基本频带信号，往往包含较多的低频成分甚至是直流成分，许多信道不能传输这种低频分量或者直流分量，所以必须对基带信号进行调制
调制：基带调制（编码）和带通调制（调幅、调频、调相）
信道的极限容量：会有失真，奈氏准则：码元传输的速率上限，香农公式c=wlog2(1+s/n)(bps)w为信道的带宽hz，s为信道内所传信号的平均功率，n为信道内的高斯噪声功率。
2.3物理层下面的传输媒体：
导引型传输媒体：双绞线、光纤
非导引型传输媒体：自由空间（短波、微波）
*/

/*$3数据链路层-协议的要求：
-封装成帧，帧定界（帧首部SOH和帧尾部EOT（只有数据链路层有帧尾部））
-透明传输：解决首部尾部错误识别的问题，两种方法：字节填充（异步网络）和字符填充（同步网络）
-差错检测 循环冗余校验CRC 它只能做到【无差错接受】做不到可靠传输（即【不丢失、不重复、不失序】）
3.1.1数据链路和帧
3.2点对点协议PPP
-同步传输要比特填充，异步传输要字符填充 7E->7D 5E   7D->7D 5D
-零比特填充 发送端只要发现有5个连续1，则立即填充一个0  
3.3 适配器（网卡）
数据链路层的MAC子层   medium access control
以太网使用了曼彻斯特编码
-CSMA/CD协议（载波监听 多点接入 碰撞检测协议）（先听后发 边听边发 冲突停止 延迟重发）（半双工）（已经不用了）
-争用期（碰撞窗口）= 2倍的传播时延τ = 长度取51.2us 对于10Mbps的以太网 在争用期内可以发送512bit即64字节
这个意味着以太网在发送数据时，若前64字节没有发生冲突则后续的数据就不会发生冲突（截断二进制指数退避算法）
那么以太网最短帧长度为64，凡是小于64的是损坏的帧，一律丢弃。
-强化碰撞：检测到碰撞以后人为发送干扰信号
3.3.5以太网的MAC子层
-硬件地址=物理地址=MAC地址（48位） 即适配器的【标识符】
发往本站的帧：单播【一对一】 广播FF:FF:FF:FF:FF:FF【一对全体】 多播【一对多】
-混杂方式=不是发给他的数据包也可以收到 IP数据报MTU 46-1500字节 控制段=18字节
无效的mac帧：数据字段的长度和长度字段的值不一致；帧的长度不是整数个字节；校验出错；数据字段长度不在46-1500之间；有效的MAC帧
长度不在64-1518之间。 遇到无效的mac帧简单的丢弃，以太网不负责重传丢弃的帧。
3.4扩展的以太网（物理层和数据链路层分别扩展）
-物理层的扩展：使用集线器（还是一个碰撞域。集线器解决不了碰撞、冲突）
-数据链路层的扩展：更加常用，早期使用网桥，现在使用以太网交换机，：：他们全部工作在数据链路层
-以太网交换机：实质上是一个多接口的网桥（通常10几个），
全双工方式，具有并行性（能同时连通多对接口，使多对主机同时通信，相互通信的主机都是独占传输媒体，
无碰撞地传输数据，即数据链路层解决了物理层碰撞问题）
交换机的交换方式：1存储转发方式-交换机的自学习功能-P18（大多数），但是会产生环路，使用【生成树协议STP】
要点：不改变网络的实际拓扑，但在逻辑上则切断某些链路，使得从一台主机到所有其他主机的路径是无环路的。
				2.直通方式（只检查目的MAC地址，立即转发，不检错）
3.4.3虚拟局域网VLAN （不同的交换机）指的是由一些局域网网段构成的与物理位置无关的逻辑组。
-数据报增加新的首部来表示VLAN ID12bit
**note：以太网交换机 不能实现不同网络之间的通信-要交给高层解决
*/


/*$4.网络层
数据链路层做了三件事：
1.物理层帧定界 2.透明传输 3.无差错接受（不是可靠传输）
数据链路层遗留的问题：
1.没有实现可靠传输 2.VLAN等 不支持不同网络之间的通信
目录 4.1网络层提供的两种服务 4.2网际协议IP 4.3划分子网和构造超网 4.4. 网际控制报文协议ICMP\
4.5互联网的路由选择协议 4.6IPV6 4.7IP多播 4.8虚拟专用网VPN和网络地址转换NAT 4.9多协议标记交换MPLS

网络层要不要实现可靠传输：
-一种观点：让网络负责可靠交付（面向连接）建立一个【虚电路服务】（只是逻辑上的连接，但是不太可能做到）
-另一种观点：让端系统保证可靠性，网络提供：：尽最大努力交付的【数据报服务】（这意味着网络层不需要做到可靠传输，交给传输层）
-网络层协议：ARP（2/3） IP（3） ICMP（3/4） IGMP（3/4层） 
*/

/*
$4.2网际协议IP
$4.2.1虚拟互连网络（是指逻辑互连的网络，屏蔽了异构性）（互联网（基于TCP的全球IP网）、IP网：使用IP协议的虚拟互连网络）：
网络层第一件事是利用【IP协议】将异构的网络互连起来，需要一些中间设备：
物理层中继系统（转发器）数据链路层（网桥）,网络层中继系统（！！路由器）网络层以上（网关）
--分组在互联网中的传送、直接交付和间接交付、（（5层4321）->（123->321）->...->（12345））
$4.2.2分类的IP地址，32位  A（0...|8位net-id）B（10...|16位net-id）C(110...|24位net-id)  D（1110...多播地址）E（11110...保留为今后使用）类
IP地址就是给每个连接在互联网上的主机或路由器分配一个在全世界范围内唯一的32位的标识符
IP地址的编址方法：
1.分类的IP地址，这是最基本的编址方法
2.子网的划分。这是对最基本的编址方法的改进(RFC950）
3.构成超网：比较新的无分类编址方法
-分类IP地址：
网络号net-id
主机号host-id
-一般不使用的IP地址：
255.255.255.255受限广播，只在本网络上进行广播，各路由器均不转发
neiID.255 对netID上的所有主机进行广播（直接广播）
127.hostID（非全0或者全1的任何数字）本地软件环回测试，测试本地相关协议是不是安装好了
-IP地址的一些重要特点：
1.IP地址是一种分等级的地址结构（IP地址管理机构只需要分配网络号、路由器仅根据目的主机的网络号来转发分组）
2.实际上IP地址是标志一个主机或者路由器的一个接口
-路由器总是有两个或者两个以上的IP地址

4.2.3IP地址与硬件地址
-硬件MAC地址是数据链路层和物理层使用的地址
-IP地址是网络层和以上各层使用的地址，是一种逻辑地址（这种称呼的原因是因为IP地址是软件实现的）
-地址解析协议ARP，主要是在数据封装的时候会用到。

*作用：解决同一个局域网中：从网络层的IP地址解析出在数据链路层使用的硬件地址。如果不是在同一个局域网\
就要通过某个路由器转发到下一个网络。

*工作原理：A->B发送数据报的时候就先向ARP高速缓存中查看有无主机B的IP地址，
如有：查出其对应的MAC地址，再将此硬件地址写入MAC帧，然后通过局域网将该MAC帧发往此硬件地址；
如没有：ARP进程在本局域网上广播发送一个ARP请求分组，收到ARP响应分组后，将得到的IP地址到硬件地址的映射写入ARP高速缓存。

A广播发送ARP请求分组：我系209.0.0.5，硬件地址是X:X:X:X，我想知道209.0.0.6的硬件地址

ARP高速缓存的作用：减少广播请求的数量&为了减少网络上的通信量，A在发送ARP请求分组时就将自己的IP地址到硬件地址的映射写入ARP请求分组

注意的问题：ARP是解决@同一个局域网上的主机或者路由器的IP地址和硬件地址的映射问题、如果要找的主机和源主机不在同一个
局域网上，那么就要通过ARP找到本局域网上某一个路由器（这就是ARP代理）的接口，做一个间接交付，然后通过该路由器转发到下一个网络。

使用ARP的四种典型情况（主机-主机、主机-路由器、路由器-主机、路由器-路由器）

相邻网络的两台主机通信，路由器做出arp代理响应，但是响应报文中目的主机的IP地址和路由器的物理地址不是对应的，

例子：网1包含H1和H2，网2包含H3，网3包含H4，R1连接网1和网2，R2连接网2和网3；
H1->H2 同一个局域网内的主机通信，简单，直接
H1->H4 H1发送ARP广播，R1做出响应，R1发送ARP广播，R2做出响应，R2发送广播，H4做出响应，（最后一次响应的地址映射才是真正对应的）

为什么不直接使用硬件地址进行通信呢：
因为异构网络的特性。全世界存在各式各样的网络，它们使用不同的硬件地址，要想互相通信必须进行异常复杂的硬件地址转换工作，这几乎是不可能的

4.2.5IP数据报的格式 
（一个IP数据包等于首部 +数据，首部最少20个字节，这部分是固定长度，是必须有的。最多60字节（有一些可选字段））
*1-4字节（32bit）：版本号1-4，首部长度(单位：四个字节)5-8，区分服务9-16，报文总长度17-32（最大长度有65535个字节，但受限于MTU）
*5-8字节：标识1-16（是一个计数器），标志17-19（MF|DF|?）（MF=1代表还有分片，DF=0代表允许分片），片内偏移20-32（代表本分片前面有多少@8字节（单位=8字节））
*9-12字节:生存时间TTL1-8（传递的路由器数目），协议9-16（TCP、UDP、ICMP、IGMP、ARP、IP），首部校验和17-32（简单的加法）
*13-16字节：源地址IP
*17-20字节：目的地址IP
*21-60字节：不固定，不够4n字节要填充

IP数据报的分片：3800字节分为1400+1400+1000三个报文，第一个报文片偏移=0/8；第二个报文片偏移=1400/8=175；第三个报文偏移=2800/8=350（第一个数据在原始数据处的位置）

4.2.6IP层转发分组的流程

1.路由表，指明去到某个网络首先要去的路由器。
2.特定主机路由：管理员为某个主机指明的一条路径
3.默认路由：路由表中没有的网络将交付给此路由器，乃最后的选择

路由器分组转发算法:（分组交换、寻址顺序：1.直连主机 2.特定主机路由 3.动态路由生成协议生成的路由表 4.默认路由）
1.从数据报的首部提取目的主机的IP地址D，得出目的网络地址为N
2.若N与此路由器直接相连，则把数据报直接交付目的主机D，否则是间接交付，执行3.
3.若路由表中有目的地址为D的特定主机路由，则吧数据报传送给路由表指明的下一跳路由器，否则执行4.
4.若路由表中有到达网络N的路由，则把数据报传送给路由表指明的下一跳路由器，否则执行5.
5.若路由表中有一个默认路由，则把数据报传送给路由表中所指明的默认路由；否则执行6.
6.报告转发分组出错
*/

/*
4.3 划分子网和构造超网 p28
//纯属一个单位内部的事情。单位对外仍然表现为没有划分子网的网络。
4.3.1划分子网 
从两级IP地址到三级IP地址（从主机号借用若干位作为子网号即：网络号+子网号（subnet-id）+主机号 = 32bit）
4.3.2使用子网时分组的转发 
子网掩码。可以找出IP地址中的子网部分，长度32位，1代表IP地址中对应位为网络号和子网号，0代表主机号\
那么IP地址和子网掩码与运算，得到子网网络地址。默认子网掩码A类：255.0.0.0，B：255.255.0.0，C：255.255.255.0\
子网号不能全1或全0（已经不是）
*IP地址和子网掩码必须同时使用
-判断两个IP地址是否是同一个网络:首先子网掩码要一样，其次IP地址与子网掩码与运算后要一样。

4.3.3 无分类编址CIDR（构造超网）
CIDR主要特点：消除了传统的A类、B类、C类地址以及划分子网的概念，因而可以更加有效地分配IPv4的地址空间。CIDR使用
各种长度的“网络前缀”来代替分类地址中的网络号和子网号，IP地址从三级编址（使用子网掩码）又回到了两级编址。

CIDR使用“斜线记法”在IP地址后加上一个斜线/ 然后写上网络前缀所占的位数。例如220.78.168.0/24

路由聚合：一个CIDR地址块可以表示很多地址，这种地址的聚合称为路由聚合（也称构成超网），这样有利于减少路由器之间的路由选择信息的交换，提高了整个互联网的性能。

虽然CIDR不使用子网。但仍然使用“掩码”这一个名词,但不是子网掩码

CIDR的其他记法：10.0.0.0/10可简写为10/10   或*记法：00001010 00* （星号之前的是网络前缀，*表示主机号可以是任意的）

最长前缀匹配：使用CIDR时，路由表中的每个项目由：网络前缀 和 下一跳地址 组成，查找路由表时可能会得到不止一个匹配结果：
应当从匹配结果中选择具有最长网络前缀的路由：最长前缀匹配。因为网络前缀越长地址块越小，地址越具体

4.4网际控制报文协议ICMP
是为了更有效地转发IP数据报和提高交付成功的机会。允许主机或者路由器报告差错情况和提供有关异常情况的报告

4.4.1ICMP报文种类：
ICMP差错报告报文 和 ICMP询问报文

差错报文分类：终点不可达、 时间超过 、 参数问题 、改变路由（重定向Redirect）

不应该发送ICMP差错报告报文的几种情况：
1.对ICMP差错报告报文不再发送ICMP差错报告报文
2.对第一个分片的数据报片的所有后续都不发送ICMP差错报告报文
3.对具有多播地址的数据报都不发送ICMP差错报告报文
4.对具有特殊地址的如本地回环地址不发送

询问报文有两种：
回送请求和回答报文 
举例：PING 用来测试两个主机的连通性，使用了ICMP的回送请求和回答报文
举例：Traceroute应用，windows是tracert。用来跟踪一个分组从源点到终点的路径。

时间戳请求和回答报文

$4.5互联网的路由选择协议
理想的路由算法：
1.是正确和完整的 2.计算应简单 3.能适应通信量和网络拓扑的变化，即要有自适应性
4.要有稳定性 5.应该是公平的 6.应该是最佳的
1.RIP（路由信息协议）是一个分布式的基于距离向量的路由选择协议，1个路由器等于1个距离，最多允许15个路由器
2.OSPF (开放最短路径优先）是为了克服RIP的缺点
3.BGP 自治域之间的路由选择

路由器的构成：也有五层的组成，数据传输只工作在前三层

4.7.1IP多播的基本概念
目的：更好地支持一对多通信，一对多通信是指一个源点发送到许多个终点，例如实时信息的交付如新闻和股市行情等

网际组管理协议IGMP：是为了让路由器知道多播组成员的信息

4.8 虚拟专用网VPN
隧道=封装
4.8.2网络地址转换
NAT
*/

/*$5传输层p33
5.1运输层协议概述
5.2用户数据报协议UDP
5.3传输控制协议TCP概述
5.4可靠传输的工作原理
5.5TCP报文段的首部格式
5.6TCP可靠传输的实现
5.7TCP的流量控制
5.8TCP的拥塞控制
5.9TCP的运输连接管理
*/

/*$5.1运输层协议概述
5.1.1进程之间的通信
传输层通过端口提供应用层@进程之间的逻辑通信，而网络层为@主机之间提供逻辑通信。两台通信的主机可能有多个进程，
所以传输层对下层实现了端口复用和分用功能。发送是向下复用，接收是向上分用。

5.1.2运输层的两个主要协议：传输控制协议TCP 和 用户数据报协议UDP（user datagram protocol）

UDP:一种无连接协议：
提供无连接服务；在传送数据之前不需要先建立连接；传送的数据单位协议是UDP报文；对方的运输层不需要回应；

TCP：一种面向连接的协议：
提供面向连接的服务；传送的数据单位是TCP报文段；TCP不提供广播或者多播服务；
由于TCP要提供可靠的、面向连接的运输服务，因此不可避免地增加了许多的开销；

5.1.3运输层的端口
为了解决不同操作系统下的不同格式的进程标识符之间的不统一问题。使用协议端口号简称端口port。

软件端口和硬件端口：硬件端口是不同硬件设备进行交互的接口，而软件端口是应用层的各种协议进程与运输实体进行层间交互的一种地址。

TCP/IP运输层端口：使用了16位的端口号进行标志。 它只具有本地意义，只是为了标志本计算机应用层中的各进程。

*由此可见：两个计算机中的进程要相互通信，不仅必须知道对方的IP地址（为了找到对方的计算机），而且还要知道对方
的端口号（为了找到对方计算机中的应用进程）。

两大类端口：1.服务器端使用的端口号：
（1）熟知端口，一般为0-1023
（2）登记端口号，1024-49151.为没有熟知端口号的应用程序使用的。必须在IANA登记。
2.客户端使用的端口号：49152-65525 留给客户进程选择暂时使用
*/

/*$5.2.1 UDP概述
UDP只在IP的数据报服务之上增加了很少一点的功能： 复用和分用的功能 + 差错检测的功能

UDP特点：
1.UDP是无连接的，发送数据之前不需要建立连接，因此减少了开销和发送数据之前的时延
2.UDP使用尽最大努力交付（靠的是IP数据报）
3.UDP是面向报文的，它对应用层交下来的报文，既不合并也不拆分，而是保留报文的边界，一次发一个完整的报文
4.UDP没有流量控制、拥塞控制
5.UDP支持一对一，一对多，多对一和多对多的交互通信
6.UDP的首部开销小，只有8字节 = 伪首部（12字节其实丢掉，0字节） + 源端口2 + 目的端口2 + 长度2 + 校验和2
*/

/*$5.3传输控制协议TCP概述
5.3.1TCP最主要的特点：
1.TCP是面向连接的传输层协议
2.每一条TCP连接只能有两个端点，每一条TCP连接只能是点对点的（一对一）
3.TCP提供可靠交付的服务
4.TCP提供全双工通信
5.面向字节流：TCP中的“流stream”指的是流入或流出进程的字节序列。面向字节流是指虽然应用程序和TCP的交互是一次一个数据块，
但是TCP把应用程序交下来的数据看成仅仅是一串无结构的字节流。TCP不保证接收方应用程序收到的数据块和发送方应用程序所发出的数据块具有
对应大小的关系。但是接收方应用程序收到的字节流必须和发送方应用程序发出的字节流完全一样。

注意：
TCP连接是一条虚连接而不是一条真正的物理连接
TCP对应用进程一次把多长的报文发送到TCP的缓存中是不关心的
TCP根据对方给出的@窗口值 和@当前网络拥塞程度 来决定一个报文段应包含多少个字节（UDP发送的报文长度是应用进程给出的）
TCP可把太长的数据块划分短一些再传送
TCP也可等待积累有足够多的字节后再构成报文段发送出去

5.3.2TCP的连接：
TCP把连接作为最基本的抽象
每一条TCP连接有两个端点
TCP连接的端点不是主机，不是主机的IP地址，也不是进程，也不是端口，而是套接字
端口号拼接到IP地址便是套接字socket = （IP地址：端口号）
*/

/*$5.4可靠传输的工作原理P35
5.4.1停止等待协议（优点简单，缺点效率低，信道利用率太低）
1.无差错状态：
就是每发送一个分组就停止发送，等待对方的确认。在收到确认以后再发送下一个分组。

2.出现差错：如何保证B正确收到了M1呢？解决方法：超时重传：
A为每一个已发送的分组都设置了一个超时计时器，
A只要在超时计时器到期之前收到了相应的确认，就撤销该超时计时器，继续发送下一个分组M2

注意：发送完一个分组后，必须保留此分组的一个备份以防重发、分组和确认分组都必须进行编号、超时计时器的重传时间应当比数据在分组传输的平均往返时间更长一些。

自动重传请求ARQ：意思是重传的请求是自动进行的，接收方不需要请求发送方重传某个出错的分组。

5.4.2连续ARQ协议 、 滑动窗口协议0729
滑动窗口协议比较复杂，是TCP协议的精髓所在。
·发送方维持的发送窗口的意义：位于发送窗口内的分组都可以连续发送出去，而不需要等待对方的确认，来提高信道利用率。
·连续ARQ协议规定：发送方每收到一个确认就把发送窗口向前滑动一个分组的位置。

累积确认：接收方采用累积确认的方法，不必对收到的分组逐个发送确认，而是对按序到达的最后一个分组发送确认
这样表示到这个分组为止的所有分组都已经正确收到了

回退N：表示需要退回来重传已经发送过的N个分组

TCP可靠通信的具体实现：
1.TCP连接的每一端都必须设有两个窗口--发送窗口和接收窗口
2.TCP的可靠传输机制用字节的序号进行控制
3.TCP的所有确认都是基于序号而不是基于报文段
4.TCP两端的四个窗口经常是动态变化的
*/

/*$5.5TCP报文段的首部格式
一个TCP报文段分为首部和数据部分，首部前20字节是固定的，TCP首部的最小长度是@20字节
* 1-4字节： 源端口1-16 目的端口17-32
* 5-8字节： 序号
* 9-12字节： 确认号（期望收到对方的下个报文段的数字（已收到+1））
* 13-16字节：数据偏移1-4 保留5-10 URG+ACK+PSH+RST+SYN+FIN 窗口（发送方的接收窗口）17-32
* 17-20字节：校验和1-16 紧急指针（指出紧急数据的字节数） 17-32
* 21-*字节：可选项（长度可变4n） 一种是最大报文段长度MSS，告诉对方TCP：我的缓存能接收的报文段的数据字段的最大长度
* *+1至end 最后的TCP数据
*/

/*5.6TCP可靠传输的实现
5.6.1以字节为单位的滑动窗口
假设A收到了B发来的确认报文段，其中窗口是20字节，而确认号是31（这表明B期望收到的下一个序号是31，小于31的全部收到）
根据这两个数据，A构造出自己的发送窗口：

A的发送窗口大小=20，第一个序号是31。

强调：
1.A的发送窗口并不总是和B的接收窗口一样大（因为有一定的时间滞后）
2.TCP标准没有规定对不按序到达的数据应该如何处理，通常是先临时存放在接收窗口中，等到字节流中缺少的字节收到以后再按序交付上层
3.TCP要求接收方必须有@累积确认的功能，这样可以减小传输开销

5.6.2超时重传时间的选择

TCP采用了一种自适应算法，记录一个报文段发出的时间，以及收到相应的确认的时间，这两个时间差就是报文段的往返时间RTT

加权平均往返时间RTTs = （1-α）* 旧的RTTs + α *（新的RTT样本）

超时重传时间RTO （retransmission Time-Out）：应略大于上面得出的加权平均往返时间RTTs
5.6.3选择确认SACK
若收到的报文段无差错，只是未按序号，中间还缺少一些序号的数据，那么能否设法只传送缺少的数据而不重传已经正确到达接收方的数据?
SACK就是一种可行的处理方法。（TCP的扩展）
*/

/*5.7 TCP的流量控制0730

5.7.1利用滑动窗口实现流量控制
流量控制flow control 表示让发送方的发送速率不要太快，既要让接收方来得及接收，也不要使网络发生堵塞

利用可变窗口进行流量控制举例：A向B发送数据，在建立连接时B告诉A“我的接收窗口rwnd=400字节”
*A发送了1-100，还可以发送300字节
*A发送了101-200，还可以发送200字节
*A发送了201-300，丢失了
*B发送确认帧ACK=1，ack=201，rwnd=300（允许A发送201-500共300个字节，A的发送窗口变成300字节）
*A发送301-400，还能发送100字节新数据
*A发送401-500，不能发送新数据了
*A超时重传201-300，但不能发送新数据
*B确认ACK=1，ack=501，rwnd=100
*A发送501-600，不能再发送新数据
*B确认ACK=1，ack=601，rwnd=0 不允许再发了。会引发死锁问题，当B的rwnd不再为0，B发送一条rwnd=400报文给
A时丢失，则A等B窗口不为0的报文，B也等A发送新的数据。

打破死锁：TCP为每一个连接设有一个持续计时器，计时结束就发送一个零窗口探测报文（仅携带1字节数据），对方在确认这个
报文的时候给出现在的窗口值。若窗口还是0，则收到这个报文的一方就重新设置持续计时器。

·Nagle算法：
	·若发送应用进程把要发送的数据逐个字节地送到TCp发送缓存，则发送方就把第一个数据字节先发送出去，后面到达的数据字节缓存起来。
	·当发送方收到对第一个数据字节的确认后，再把发送缓存中的所有数据组装成一个报文段发送出去，同时继续对随后的数据进行缓存。
	·只有在收到对前一个报文段的确认后才继续发送下一个报文段
	·当到达的数据已经达到发送窗口大小的一半或已经达到报文段的最大长度时就立即发送一个报文段。
5.7.2TCP的传输效率
可以用不同的机制来控制TCP报文段的发送时机：
1.TCP维持一个变量，它等于最大报文段长度MSS，只要缓存中存放的数据达到MSS字节时，就组装一个TCP报文发出去
2.由发送方的应用进程指明要求发送报文段，即TCP支持的推送PUSH操作
3.发送方的一个计时器期限到了，就把当前已有的缓存数据装入报文段（但长度不能超过MSS）
*/

/*5.8拥塞控制
5.8.1拥塞控制的一般原理
拥塞：对资源的需求总和 > 可用资源  类似堵车

·拥塞常常趋于恶化

拥塞控制：防止过多的数据注入到网络中，使网络中的路由器或者链路不致于过载。这是一个全局的过程，涉及到所有的
主机、路由器以及与降低网络传输性能有关的所有因素。

流量控制和拥塞控制的区别：
流量控制往往是指点对点通信量的控制，是个端到端的问题接收端控制发送端，抑制发送端发数据的速率，以便接收端来得及接收
拥塞控制是一个全局的过程。

5.8.2TCP的拥塞控制方法p38
·TCP采用基于窗口的方法进行拥塞控制。属于闭环控制方法
·TCP发送方维持一个拥塞窗口CWND
	·拥塞窗口的大小取决于网络的拥塞程度且动态变化
	·发送端利用拥塞窗口根据网络的拥塞情况调整发送的数据量
	·所以发送窗口的大小其实是 = Min（接收方公告窗口RWND值， 拥塞窗口CWND值）

·拥塞的判断：（分组丢失乃征兆）
	·重传计时器超时：猜想网络“可能”出现了拥塞（堵死了）
	·三次重复ACK：预示可能会出现拥塞
·TCP拥塞控制算法：
	·慢开始：用来确定网络的负载能力。
		·TCP连接初始化的时候，将cwnd设置为1
		·思路：由小到大逐渐增大拥塞窗口数值
		·慢开始门限ssthresh（状态变量）：防止拥塞窗口cwnd增长过大引起网络拥塞
		·发送方每收到一个对新报文段的确认（重传不算）就使cwnd+1
		·每经过一个传输轮次，拥塞窗口就加倍（指数增大）
		·传输轮次：经历的时间=往返时间RTT，它更加强调：把cwnd允许发送的报文段都连续发送出去，并收到了对已经
			发送的最后一个字节的确认。比如，当cwnd=4时，往返时间rtt=连续发送四个报文并收到这四个报文的确认，总共需要的时间
		·设置慢开始门限状态变量ssthresh
			·当cwnd<ssthresh 使用慢开始算法
			·当cwnd>ssthresh 使用拥塞避免算法
			·当cwnd=ssthresh 都可
	·拥塞避免
		·思路：让cwnd缓慢增大，每经过一个传输轮次，cwnd+1,（加法增大）
		·当网络出现拥塞，无论是慢开始还是拥塞避免，只要发生重传定时器超时（严重）则：
			·ssthresh = max（cwnd/2,2)
			·cwnd=1
			·执行慢开始算法
	·快重传：适用于第二种情况，即收到三次重复的ACK报文
	·快恢复

5.8.3主动队列管理AQM
·路由器分组丢弃策略 随机早期检测RED （三个区域，丢弃、以概率P丢弃、排队）
·AQM是对路由器中的分组排队进行智能管理
*/

/*$5.9TCP的运输连接管理（就是使连接的建立和释放正常运行）
·5.9.1TCP的连接建立
	·TCP是面向连接的协议
	·TCP连接的建立采用客户服务器方式
	·TCP建立的过程叫握手，需要交换三个TCP报文段，主要是为了防止已失效的连接请求报文段突然又传送到了因而产生错误。
	·三报文握手：
		·A->B ：SYN = 1，seq = x （A进入SYN-SENT状态）
		·B->A ：SYN = 1，ACK = 1，seq = y，ack = x+1 （B进入SYN-RCVD状态）
		·A->B ：ACK = 1，seq = x+1，ack = y +1(A发完进入ESTABLISHED，B收到进入ESTABLISHED)
·5.9.2TCP的连接释放
	·数据传输结束后，通信的双方都可以释放连接
	·TCP连接释放过程是四报文握手
	·理想状态的四报文握手：
		·A->B ：FIN=1，seq=u （A进入FIN-WAIT1，B收到进入CLOSE-WAIT）
		·B->A ：ACK=1，seq=v，ack=u+1  （A的TCP连接处于半关闭状态。B若发送数据A仍要接收）（A收到进入FIN-WAIT2）
		·B->A ：FIN=1，ACK=1，seq=w，ack=u+1（B进入LAST-ACK）
		·A->B : ACK=1，seq=u+1，ack=w+1（A进入TIME-WAIT 2MSL）
		·经过时间2MSL后才真正释放掉，第一保证A发送ACK能够到B，第二防止已经失效的连接请求报文段出现在本连接中。
·5.9.3TCP的有限状态机
*/

/*$TCP整理
·TCP实现可靠传输
	·1.建立连接
		·三次握手
	·2.发送数据
		·采用窗口（序号、发送窗口和接收窗口），
		·确认机制
		·流量控制
		·拥塞控制
			·发现什么时候拥塞、让拥塞来的越晚越好
		·超时重传
	3.连接释放
		·四次挥手
*/

/*$6应用层P40
6.1域名系统DNS--UDP 53端口
	·顶级域名
		·国家 cn us等
		·通用com net org edu gov
		·基础
	·本地域名服务器
6.2文件传送协议
	·FTP--TCP 控制连接是21端口 传输连接是20端口
	·TFTP 简单文件传送协议--UDP自己有差错控制
6.3远程终端协议TELNET
	·TELNET--TCP  23端口 明文，不加密的。
6.4万维网WWW
	·分布式超媒体服务、按需访问
	·工作方式：客户-服务器
	·URL的一般形式：<协议>://<主机>:<端口>/<路径>
	·HTTP--TCP
		·特点：是面向事务的客户服务器协议、1.0是无状态的、本身是无连接的虽然TCP是有连接的。
		·2.0支持多路复用
	·代理服务器：使用高速缓存
6.5电子邮件
	·概述
		电子邮件把邮件发送到收件人使用的邮件服务器。
	·发送邮件：SMTP（TCP25端口）
	·读取邮件：POP3 和 IMAP4
	·通用互联网邮件扩充MIME是对SMTP的补充。主要是定义非ascii码的编码方式
	·UA用户代理。是用户与电子邮件系统的接口、是电子邮件客户端的软件。功能：撰写、显示、处理、通信。
	·电子邮件的格式：收件人邮箱名字@所在主机的域名
	·SMTP通信的三个阶段：建立连接、邮件传送、连接释放
6.6动态主机配置协议DHCP（c/s模式）
	·提供即插即用的机制，允许一台计算机加入新的网络和获取IP地址而不用手工参与
	·步骤：
		·需要IP地址的主机在启动时就向DHCP服务器广播发现报文，这时该主机就成为DHCP客户
		·DCHP服务器广播回答
		·DHCP服务器从IP地址池中取一个地址分配给计算机。
	·两个计时器：0.5T 和 0.875T
6.7简单网络管理协议SNMP--UDP
	·6.7.1网络管理的基本概念
		·包括对硬件软件、服务质量等监视和测试等
		·被管对象，路由器，主机等
	·6.7.2管理信息结构SMI
	·6.7.3管理信息库MIB
	·6.7.4SNMP的协议的读写操作
		·trap 陷阱：表示能够捕捉“事件”
6.8应用进程跨越网络的通信
	·大多数操作系统使用系统调用机制在应用程序和操作系统之间传递控制权
	·不同操作系统网络接口API：
		·套接字的作用：当应用进程需要使用网络进行通信的时候就发出系统调用，请求操作系统为其创建套接字，以便把网络通信所需要的系统资源分配给该进程
		·操作系统（维护一张套接字描述符表，每个进程一个描述符），为上述资源总和用一个“套接字描述符”号码来表示，并把此号码返回给应用进程，后续的所有网络操作都必须使用这个号码。
		·套接字的数据结构：协议族PF_INET、服务：SOCK_STREAM、本地IP、目的IP、本地端口、目的端口
6.9P2P应用
	·电驴
	·BT
*/