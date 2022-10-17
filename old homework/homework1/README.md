# This is the homework No.1
## 运行方式
## problem1
我在当前目录新建了test文件夹里面随便塞了一些.c .h文件  
直接运行  time find test/ -name "*.c" -o -name "*.h" -type f | xargs grep hello -n 即可  
也可以把“/test”部分替换成任意位置，比如“~/”，“/“，但有些目录可能没有权限，这时就要在find前面加上sudo,即 time sudo find ....  
## problem2 & problem3
cmakelists.txt中有两个excutable  
直接运行即可  
代码文件  
main.cpp -> problem 2  
main2.cpp -> problem 3  
## problem 1
### 思路
find加-name，通配符*.c，*.o,  
-o代表或者  
-type f代表只查找文件不查找目录  
用xargs将find的输出作为grep的输入，在文本中查找hello  
-n可显示匹配到的文本所在行数
time用于统计耗时  


开始在想有什么办法能统计耗时，而且我没太明白shell命令是否shell脚本也可以
于是就用shell脚本计时，在文件solve.sh中  
然后发现 time这个命令可以输出后面这个命令的耗时，不一定非要用脚本才能统计耗时    
time find test/ -name "*.c" -o -name "*.h" -type f | xargs grep hello -n   
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
由于有拖影，用长宽比足够大来筛选出长条形的矩形，即为运动的子弹  
子弹位置的标记则直接标记在矩形的中心
#### 子弹计数
发现刚射出的子弹的矩形更长，而且角度比较小，以此可以判断是否有新子弹射出  
若前一帧有子弹，则不计数
若前一帧无，当前帧有，则计数+1
然后把数字标记在刚射出的子弹位置

    