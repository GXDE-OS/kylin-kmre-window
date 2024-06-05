# 麒麟移动运行环境
## 概 述
麒麟移动运行环境（KMRE）是麒麟团队专为“银河麒麟操作系统”打造的一款兼容安卓App运行的系统环境，用于满足用户对应用软件的多样化需求。KMRE能够让用户在银河麒麟操作系统中安装和运行安卓App，比如游戏、微信、QQ极速版、股票、视频类App等。

### 技术特点
1）支持海量安卓App，一秒启动。

2）可直接使用显卡硬件，无性能损失。

3）安卓App与Linux窗口显示融合。

4）多个App同时运行。

5）App分辨率动态适应，横竖屏幕切换，高分辨率真全屏模式。

6）统一输入法，使用Linux输入法在安卓App中输入文字。

7）统一音频设备，支持语音聊天。

8）支持使用摄像头拍照、录像和视频通话，支持摄像头热插拔，即插即用。

9）文件互通，文字剪切板互通，应用管理统一。

10）支持微信、QQ极速版的新消息通知。

11）支持微信平板模式登录，和手机微信同时在线。

12）支持微信、QQ极速版等应用拖拽文件进行分享。

13）支持安卓App直接访问Linux端文件。

14）支持安卓内的文件使用Linux端的默认工具打开。

15）支持安卓App快速截图分享和录屏分享。

16）支持安卓App共享Linux桌面。

17）支持安卓App内图片和文档的缩放。

18）支持游戏按键设置。

19）升级到安卓11，兼容性、安全性、稳定性大幅提升。

<br>

## 用前必读
因安卓系统本身技术设计，以及KMRE与银河麒麟操作系统共用硬件资源的原因，为了达到较好的使用体验效果，建议用户仔细阅读以下注意事项和已知问题：

1）安卓App在使用固态硬盘时性能会相较于使用机械硬盘有较大提升（安卓操作系统为手机操作系统，其磁盘操作对机械硬盘支持较差）；

2）建议不要同时运行4个以上的App（安卓手机一般只会有一个App在前端活跃运行）；

3）电脑内存建议8G或以上；

4）当前版本支持的处理器包括FT1500A、FT-2000/4、FT-D2000/8、Kirin990、Kirin9006C、Hygon、ZHAOXIN、Kunpeng920、Intel和AMD；

5）当前版本支持的显卡包括：NVIDIA、AMD、INTEL、MALI、JJM、GP101和ZHAOXIN；

6）QQ极速版语音和视频通话正常，但是录像显示异常；

7）在使用音视频通话软件时，需要暂停其他音频/视频的播放，否则音视频通话软件可能会遇到听不到对方声音的问题；

8）当前版本在有些机器上使用摄像头可能存在绿屏现象；

9）带有wifi设备的机器，如笔记本或者台式机插入了无线网卡，这类机器在启动Kmre环境之前，需要保证wifi开关处于开启状态，否则如果wifi开关处于关闭状态时启动Kmre环境，则Kmre环境里的App都无法联网；

10）视频类应用调节屏幕亮度功能不会生效；

11）视频类应用不支持“画中画”功能；

12）不支持定位和传感器相关功能；

13）“钉钉”应用登录后，如在钉钉上使用到打卡等功能，需要先在Kmre环境中登出账号，否则可能出现“虚拟定位软件打卡”问题；

14）“蓝信+”应用，需要在手机上登出账号后，语音通话功能才能成功呼出；

15）如果安卓应用无法连接互联网，请检查是否是docker网络配置与本机局域网的网络配置存在冲突；

16）不支持虚拟机；

17）不支持超级用户root使用；

18）部分应用（如知乎）出现无网络的原因可能与Linux系统时间不对有关，安卓系统内部与Linux系统时间同步，某些安卓应用内部有自己的网络检测机制，当安卓系统时间不是当前时间时，可能会禁止应用使用网络；解决该问题的方法是：Linux系统同步当前时间。

<br>

## 启动和关闭
- 启动KMRE：启动方式1）点击软件商店界面上方的“移动应用”按钮，首先进行KMRE初始化，如图 1所示，待KMRE初始化完成后，软件商店的“移动应用”页面将会出现移动应用列表，在移动应用列表页面可以安装和启动移动应用；启动方式2）从开始菜单启动。

![图 1 初始化KMRE提示框-big](image/1.png)

- 关闭KMRE：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“帮助”->“关闭麒麟移动运行环境”，即可将KMRE关闭，同时关闭所有移动应用的图形窗口。

<br>

## 安装和卸载
- 安装应用：通过软件商店安装或者本地直接双击apk包进行安装。

- 卸载应用：卸载方式1）进入“软件商店” ->“我的” -> “应用卸载”页面，选中需要卸载的软件，点击“卸载”按钮开始卸载；卸载方式2）打开开始菜单，在需要卸载的应用上点击鼠标右键，然后点击“卸载”。

<br>

## 输 入
- 中文输入：KMRE和麒麟系统共享输入法，切换中文输入法后，可以直接在移动应用的输入框中输入中文，如图 2所示。

![图 2 中文输入-big](image/2.png)

- 按键输入：KMRE支持键盘按键输入，包括小键盘和各类组合键，如Ctrl+C、Ctrl+V、Ctrl+A等。

<br>

## 文件互通
- 查看手机存储文件：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“打开移动数据”，即可在文件管理器中查看手机存储的所有文件目录。

- 拖拽文件进行分享：从麒麟系统端拖拽一个文件（仅支持当前用户家目录下的文件）到移动应用的界面，可以选择好友进行分享转发。KMRE目前支持9款应用的文件拖拽，分别是微信、QQ极速版、网易邮箱、Welink、WPS、百度网盘、有道云笔记、蓝信+、企业微信；对3款应用只支持图片分享，分别是爱奇艺、今日头条、印象笔记。

- 文件发送：在微信聊天界面，选择“+”->“文件”->“手机存储”->“0-麒麟文件”,即可将麒麟系统端家目录下的文件发送给微信好友，如图 3所示。

![图 3 微信从手机存储选择文档文件-big](image/3.png)

- 麒麟端软件打开移动应用内的文件：鼠标左键长按微信内收到的文件，在弹出的菜单中点击“其他应用打开”，选择“本地应用打开”，则可以用麒麟系统端关联的工具打开文件。

<br>

## 便捷操作
- 放大缩小：KMRE支持对图片和文档内容的放大缩小：按住“Ctrl”键，并按住鼠标左键进行前后左右移动。

- 鼠标锁定在窗口内：按下F2，鼠标锁定在窗口内，再次按下F2解除鼠标锁定。

- 窗口置顶：点击任何一个移动应用界面标题栏上的“置顶”图标，即可让该移动应用界面处于置顶状态，再次点击取消置顶。

- 截图分享：点击任何一个移动应用界面标题栏上的“截图”图标，即可使用截图工具进行截图并分享给好友。根据麒麟截图版本提供“截图时隐藏当前窗口”功能，截图分享功能暂时只支持微信和QQ。

- 打开设置界面：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“设置”，即可快速进入设置界面。

- 键鼠手柄：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“键鼠手柄”，即可进入键鼠手柄设置界面，该设置仅在非平行界面下可进行。

- 摇一摇：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“摇一摇”，即可使用摇一摇功能。

- 横竖屏切换：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“横竖屏切换”，对于支持横竖屏切换的应用即可根据当前应用的显示状况进行切换。

- 录屏分享：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“录屏”，即可开始录屏，录屏完成后，可直接分享给好友。录屏分享功能暂时只支持微信和QQ。

- 虚拟键盘：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“虚拟键盘”，即可使用虚拟键盘输入。

- 虚拟定位：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“虚拟定位”，在虚拟定位界面输入位置关键词，然后根据提示选择位置后，点击定位到此即可将所选择位置发送到KMRE。

- 打开移动数据目录：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“移动数据”，快速打开KMRE移动数据的目录。

- 调整滚轮灵敏度：点击任何一个移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“滚轮灵敏度”，即可对鼠标滚轮灵敏度进行调整。

<br>

## 配 置
- 显示模式切换：KMRE提供两种显示模式，性能模式和兼容模式，其中性能模式只适用于AMD和Intel显卡，兼容模式适用于所用显卡，如图 4所示。显示界面仅在两种模式都适用时才显示。

![图 4 显示模式切换界面-big](image/4.png)

- 渲染器切换：KMRE提供四种渲染器列表供用户选择，其中“默认”由安卓根据硬件环境自动选择渲染器。用户可以通过“配置”入口，在“渲染器”页面中进行修改，如图 5所示。显示模式处于性能模式状态时，渲染器界面不显示。

![图 5 渲染器切换界面-big](image/5.png)

- 游戏按键白名单设置：在配置界面的“游戏设置”页面，可以将游戏添加到白名单中或从白名单中删除，如图 6所示。点击移动应用界面标题栏上的“菜单”图标，在弹出的菜单中选择“游戏按键”，开始进行按键设置，如图 7所示，游戏操作效果如图 8所示。

![图 6 游戏按键白名单-big](image/6.png)

![图 7 游戏按键设置界面-big](image/7.png)

![图 8 游戏操作效果图-big](image/8.png)

- 修改网络配置：如果Docker默认的网段与用户系统所在的局域网网段一样，如172开头的网段，则会造成网络冲突，导致麒麟系统和KMRE访问网络异常。点击任何一个移动应用界面标题栏上的“配置”图标，进入配置界面的“网络”页面，则可以进行容器的默认网络修改，如图 9所示。

![图 9 设置容器默认网络-big](image/9.png)

- 摄像头切换：如图 10所示，切换KMRE使用的摄像头。

![图 10 摄像头切换界面-big](image/10.png)

- 平行界面：如图 11所示，设置应用是否启用平行界面显示模式。目前平行界面已支持应用有：微信、腾讯新闻、极速版QQ、今日头条、哔哩哔哩、爱奇艺、新浪微博、新浪新闻、网易新闻、京东、网易新闻、西瓜视频、汽车之家、美团、大众点评、斗鱼、虎牙。安装应用后平行界面列表方可显示对应应用。

![图 11 平行界面切换界面-big](image/11.png)

- 镜像清理：如图 12所示，选择镜像进行清理或者一次性清理所有闲置镜像，节省硬盘存储空间。

![图 12 镜像清理界面-big](image/12.png)

- 托盘设置：如图 13所示，设置应用是否显示托盘，应用设置托盘显示后，在标题栏点击关闭时，应用将不会退出运行。

![图 13 托盘设置界面-big](image/13.png)

- 日志收集：如图 14所示，收集日志，方便问题跟踪定位。

![图 14 日志收集界面-big](image/14.png)

<br>

## 开发者模式调试
- 打开开发者调试：
1)连续点击通用设置->版本号5次即可显示开发者模式界面。
2)KMRE设置界面->开发者调试开关开启即可。
3)docker exec -it kmre-1000-kylin ifconfig查看KMRE的IP地址。
4)通过adb connect IP 连接KMRE设备。

- 关闭开发者调试：打开KMRE设置界面->开发者调试开关关闭即可。

<br>