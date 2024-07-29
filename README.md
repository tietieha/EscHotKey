使用ESC关闭任意窗口、进程

原理是安装一个全局键盘钩子，处理ESC的按键消息，如果是指定进程，就关闭窗口。这个进程列表可以配置。

使用方法很简单，启动后直接最小化就行，会隐藏到系统托盘内。
（目前只有Windows版）

# 编译
现在Repo里的工程文件是Visual Studio 2019的

# 配置
```
;key=要关的进程名
;value=1最小化窗口，2关闭窗口，3隐藏窗口，4退出进程
[esc]
DingTalk.exe=3
EscHotkey.exe=3
cloudmusic.exe=3
```

有些程序最小化和关闭傻傻分不清，如果不能满足你的需求，1、2、3这几个多试试。
4就比较纯粹，强制关闭一个进程。

# 使用
直接双击、最小化。
建议把本程序的快捷方式拖到`C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Startup`目录，这样就可以开机自启动了。
