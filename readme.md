# 中文脚本 zhscript 第二版

* 实现一种不像计算机语言的脚本语言。按照中文语法习惯去书写分析执行语句。
* 通过简单文字接口便可调用标准库（如libstdc）、第三方库、自己扩展的库。
* 不需要空格界定，允许按照文章的样式书写，空格只是排版，保留字也可从中断开。
* 变量名可以很长可以任意字符（保留字加引号的话也能）。
* 跳转（遁出、跳出、重来、再来）可以“穿墙越域”不受限制。
* 定义任意处定义任意处使用。
* 扩展的 sh（webkitsh、cairogsh、vtesh、srcvwsh 等）来使小应用实现更简单。

按 c++1y 思考重新写代码。

较之上一版似 golang 版样加入了 codecache 机制使所有代码段只解析一次、一些可固定项（如参数、循环次数）也不必再每每解释。

借鉴 rustlang 实现模块的简洁明快思路，加入以文件、解释段做为模块的实现，将替代上一版的“库”。

如 golang 版样——

支持多返回值，形如：

	赋予刘、关、张、吕以10、104、100、205。

支持定义的倒挂标注字、参数命名，形如：

	定义打得过【倒挂3】、我1、我2、我3、敌以下代码
		如果算术‘我1’ + ‘我2’ + ‘我3’大于‘敌’那么1。
	上代码。
	如果‘刘’、‘关’、‘张’打得过‘吕’那么 \o/ 否则 /..\。

支持循环的附带次数和变量，形如：

	循环4次显示第‘次’次换行。

同时循环变量名也是该循环的名称，用在“跳出”、“再来”后以直接到该循环。

“算术”、“回车”、“换行”、“制表符”、“ESC”常用应自带。“算术”的语法错不会报错而是做为第二返回值返回。

保留保留字“范围”、“遁出”、“重来”，因为他们可以使不必纠缠于如何跳转。

参数在不存在时将返回空串而非之前的报错“不存在”，这样使得有了类似缺省值并省却那部分判断存在的代码。

参数栈支持如“参数栈2/4”来充分使用起的语法（始/终），以便灵活地再次组织参数进行使用。

定义在名称的解析时不再查找定义以避免逻辑循环甚至程序崩溃，同时，定义便可以重名（覆盖），也新增“被覆盖”的报错，这表示已有定义的名称是该定义的前面部分（这个定义将不会按照你的想法去执行）。

新增“函数集”、“函数”两保留字来专门处理调用动态库的接口，“函数集”用来加载动态库并保留其信息（也是 cache），“函数”用来获取动态库里的函数并保留其信息（也是 cache 并免却每每解释）。

新增“命名”，可以给当前运行区命名，以便后面的直接访问，也将替代上一版的类似功能。在上一版不会报“无法的标注”、“无效的标注”等错，因为无效的标注其实都被忽略，这似乎缺少一个严谨（意外写错了没提示）。

新增标注字“私”，对下一级隐藏。

保留字不再有“不等于”，但“不等于”的逻辑比较还是写做“不等于”，同时因此改动衍生出“不小于等于”、“不小于”、“不大于等于”、“不大于”的可用。

golang 版其实在定义实现上有个问题，因为在解释前必须解析、缓冲出所有代码，导致定义失去了他“任意处定义任意处使用”的灵活性，c++ 第二版增加了 NO 片段，也就是不会缓存每每解析的片段，这样来保持那种“一段代码可以有很多种解释”。

### 生成并测试

从命令行进入项目运行以下命令生成调试版

	make o=d

成功后再运行

	cd test
	./hello.zs

若随后出现

./hello.zs, w o o r r r l l l l d d d d d ! ! ! ! ! !

则意味着吾甚欣慰

### 默认带两套保留字，可以中英文混合编程
如那例可写做

	DEF 打得过[backarg3], my1, my2, my3, he = BEGIN
		IF EXPL $(my1)$ + $(my2)$ + $(my3)$ > $(he)$ THEN yes;
	END;
