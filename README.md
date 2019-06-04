# 核数据获取与处理MCA总结报告

# 功能需求与功能结构
## **设计原则:**
本程序在实现MCA基本功能的基础上，对于MCA的界面配色进行了一定的调整，避免重复常见MCA程序的红蓝白配色。
![alt 图片 "界面"](../../mydevelopdata/VSCODE/MCA/总界面.PNG)

## **主要功能**
本程序实现的主要功能有：   
* 导入TXT格式能谱数据作为模拟数据绘图
* 将MCA采集到的数据以TXT格式文件导出
* 工作方式PHA
* 显示全谱区的水平以及垂直刻度
* 自主选择手动&自动量程，并且自动模式下垂直刻度保持更新
* 自主选择预置计数&预置时间&无三种预置模式，采用**Radio Button**确保不会产生冲突
* 预置时间模式下显示已运行时间
* 选择放大区
* 显示放大区的总计数，峰位
* 放大区支持鼠标点击及**A** **D**键实现左右移动光标，显示选中的道址及计数

# 编程环境

* 基于Visual Studio 开发环境
* 基于VC++编程语言，MFC库
* 版本维护采用git控制版本，项目地址见：[MCA](https://github.com/AlbertWulf/MCA)
 
# 屏幕界面规划
## 总体布局：    
![alt 布局 "布局"](../../mydevelopdata/VSCODE/MCA/MCA布局.PNG)
## 具体布局参数
 首先将主界面主要划分为三个区域
* 控制区，即各种控件所在区域，负责MCA的操作
* 菜单区，即菜单栏ToolBar所在区域
* 绘图区    
  
其中绘图区又再次进行了划分：     
* 全谱区，用于显示MCA测量到的能谱的直接显示
* 放大区，用于显示在全谱区进行选择得到的目标区域放大后的显示
* 水平刻度区，用于显示0-1024道址
* 垂直刻度区，用于显示全谱区的计数的量程，并且可以即时更新    
  
主界面的大小为1300x700像素，能适应目前主流屏幕参数

# 功能编程实现方法
首先阐述一下整个程序的处理的逻辑流程：    

. 程序启动时，会利用CFILE类默认读取同目录文件夹下的Cs137.txt文件作为模拟数据,此时已经可以进行MCA的所有操作，如果想更换数据，则可以点“导入TXT”按钮来导入文件。     
## 文件读写功能
主要有三处涉及到文件读写：    
* ControlView初始化时默认进行读入的能谱数据
* “导入TXT”按钮触发的弹框进行能谱数据读写
* “导出TXT”按钮触发的弹框进行重命名的能谱数据的保存    
  
  首先初始化时进行的读入默认数据的操作如下：
```C++
FILE*f=fopen("D:\\mydevelopdata\\VSCODE\\MCA\\Cs137.txt","r");
	for(int i = 0;i<1024;i++){
		fscanf(f,"%d",&((CMCADoc*)m_pDocument)->Data[i]);
	}
```
   首先利用FILE类的fopen方法进行默认文件的读取,接着使用`fscanf()`方法将数据逐行读入存储能谱的数组。    
   “导入TXT”文件的操作如下：    
```C++
void CControlView::OnBnClickedButtonImporttxt()
{
	
	BOOL isOpen = TRUE;		//是否打开(否则为保存)	
	CString defaultDir = L"E:\\FileTest";	//默认打开的文件路径	
	CString fileName = L"";			//默认打开的文件名	
	CString filter = L"文件 (*.doc; *.ppt; *.xls; *.txt)|*.doc;*.ppt;*.xls;*.txt||";	//文件过虑的类型	
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);	
	openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";	
	INT_PTR result = openFileDlg.DoModal();	
	CString filePath = defaultDir + "\\test.doc";	
	if(result == IDOK) {		filePath = openFileDlg.GetPathName();	}
	USES_CONVERSION;
	char * pFileName = T2A(filePath);
	FILE*f=fopen(pFileName,"r");
	for(int i = 0;i<1024;i++){
		fscanf(f,"%d",&((CMCADoc*)m_pDocument)->Data[i]);
	}

}
```
利用`CFileDialog`方法调出选择文件的弹框，接着获取被选中文件的路径，然后利用`FILE`方法进行类似的读取操作。      
“导出TXT”文件的操作是类似的，在此不再赘述。    

## DetailView & TotalView 的绘图操作
### DetailView
首先非常抱歉本人DetailView & TotalView区颠倒了，后期进行改正也比较困难，所以在以下描述中DetailView 指原谱区。    
首先`DetailView`区在点击“开始/暂停”按钮时，触发绘图函数，采集频率1Hz，在绘图函数中将能谱数组读取进行连线绘图，同时进行判断峰的最大值是否超过给定阈值，如果超过，则将峰高度减半，量程加倍，重绘，同时记录下减半的次数，以此还原真实的峰高度。    
再次点击“开始\暂停”时，由于在绘图函数中设置了一个`bool`型变量`willpaint`，初始化为`TRUE`,每次点击该按钮时，都会讲该变量取反，`willpaint = ! willpaint`，从而在判断中实现点击按钮绘图，再次点击暂停的功能。    

 **选中放大区实现方法**    
 本程序选择放大区的操作为：    
 * 按下鼠标左键
 * 向右进行拖拽，拖拽过程中会有即时绘图的响应
 * 松开左键，触发放大区重绘函数
 * 双击右键取消放大区或者重复上述步骤进行下一次放大区的选取

**实现逻辑**    

首先在`DetailView`中添加鼠标左键的响应函数，并且记录初始鼠标`ponit.x`值，作为放大区的起始道址，拖动过程中同时触发`OnMouseMove()`函数，判断鼠标左键是按下状态时，进行放大区的标记的绘图，并且实时进行重绘，不依赖于`OnTimer()`函数进行刷新，当鼠标左键抬起时，触发对应监听函数，此时记录光标位置，作为放大区的结束道址。并且对放大区的绘图进行重绘。    
本程序进行选中放大区的标记是采用的不是绘制矩形，而是选择将能谱选中区域进行填充：    

## TotalView(放大区)    
在放大区需要实现的操作主要有：    
* 鼠标点击后，在`ControlView`中更新对应的峰位，道址，计数等值，并且在鼠标点击位置绘制光标
* 监听键盘的`A``D`键，实现光标位置的左右移动
  
**实现方法**    
鼠标点击事件是通过在`OnLButtonDown()`函数中响应点击事件，获取鼠标点击位置进行划线，并且使用`UpdateViews`进行刷新。      
对于`ControlView`中峰位等控件的更新主要是通过控件的`.SetWindowText(CString str)`方法，每次点击时进行控件值的更改，并且进行更新。    

按键事件主要是通过`OnKeyDown()`监听函数中识别按下的按键，接着使用鼠标控件中的方法对光标，`ControlView`区的数据进行更新。    

## 预置参数设置功能

预置参数有三种模式：    
* 预置计数
* 预置计时
* 无预置    
  
实现通过`Radio Button`控件实现，设置三个该控件，并且划分为同一组，则同时只能选中一个，从而避免出现预置方式冲突的问题，默认预置方式为无预置。 当按钮被选中时，则其对应的属性会被置为`TRUE`。    
在绘图函数中设置判断语句对三个按钮的属性进行判断，判断对应的属性为`TRUE`时，则选择相应的工作方式。如选择定时时，当检测到其属性为`TRUE`时，则在判断中将已运行时间与预置时间进行比较，若到达预置时间时，则停止定时刷新。    

## 自动&手动量程实现方法

首先在`ControlView`区的控件是利用下拉菜单实现，该控件需要绑定一个`MENU`,并且需要对该`MENU`的每一个栏目设置监听函数。下拉菜单共设置以下几个条目：    
* 500
* 1000
* 2000
* 自动
  
默认为自动量程。当选择对应的手动量程的范围时，垂直刻度条进行一次更新后不会再变化，即使能谱高度已经超出显示范围。
**实现方法**
该方法逻辑为：当选择对应的量程时，触发响应的函数响应，将量程首先设置成对应数据，同时，将`bool`型变量`auto_manual`设置为`FASLE`，从而在`paint()`函数进行绘图时，不再检测能谱峰值是否大于阈值。    



