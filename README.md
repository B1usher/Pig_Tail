# Pig_Tail
结对作业猪尾巴

&nbsp;
## 一、运行环境
---
微信开发者工具

&nbsp;
## 二、使用方法
---
1、将微信小程序文件夹内文件导入微信开发者工具 或 使用体验版二维码并打开调试模式
https://images.cnblogs.com/cnblogs_com/blogs/704044/galleries/2050576/o_211024154700_oGR_P5fTZQmV63f7QkNoRzbcYK6Q.jpg
2、C++文字版打开Debug文件夹内exe文件!

&nbsp;
## 三、游戏玩法
---
由一名玩家开始，从<卡组>随机抽取翻开一张扑克牌，置于<放置区>上。

切换到另外一名玩家操作，执行1操作，此时插入判定:

若翻开的花色与<放置区>原顶部扑克牌花色相同，需进行以下操作:

将放置区的所有牌收到自己<手牌>内（即”吃“牌）。

在执行1操作前，若玩家<手牌>非空，则:

玩家可选择放弃翻牌，同时需要从<手牌>中选择一张牌置于<放置区>顶部作为替代，判定同2操作。

若<卡组>非空，则重复2操作；

当<卡组>为空，且插入判定结算完成，游戏终止，进行结算判定:

比较两玩家<手牌>卡牌数量:

剩余卡片数量小者获胜;

数量相同则判断为平局。
https://img2020.cnblogs.com/blog/2515504/202109/2515504-20210924095841663-358698831.png
