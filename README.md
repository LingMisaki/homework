# This is the homework No.1
cmakelists.txt中有两个excutable  
main.cpp -> problem 2  
main2.cpp -> problem 3  
## problem 1
## problem 2
### 思路：
BGR转HSV  
提取红⾊和橙⾊   
中值滤波  
开运算  
轮廓提取  
寻找外接矩形  
## problem 3
### 思路
与第二题类似，提取绿色然后找矩形（偏转）  
由于有拖影，用长宽比筛选出长条的矩形，即为运动的子弹  
子弹位置的标记则直接标记在矩形的中心
#### 子弹计数
若前一帧有子弹，则不计数
若前一帧无，当前帧有，则计数+1
然后把数字标记在刚射出的子弹位置

    