# TODO

将music中的乐谱信息发送出去。不区分LED, 按帧依次循环发送。

需实现按键切换发送led_message内容

在发送乐谱中, 需要在乐谱内容开头和结尾发送对应标识符

~~~c++
#define MUSIC_START	0xF0	//乐谱开始标志
#define MUSIC_END	0xFF	//乐谱结束标志
~~~

