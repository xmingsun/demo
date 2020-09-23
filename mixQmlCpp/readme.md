#一、QML中调用C++接口
##1. QML中可以直接调用C++中的
1）无法调用普通函数  
2）Q_INVOKABLE GenerateAlgorithm algorithm() const;  
需要调用的时候在函数前面增加 Q_INVOKABLE
c、C++中的槽函数可以直接调用。    
  
备注：需要调用的函数，可以用Q_INVOKABLE或者写成槽函数
##在main函数中注册  
1）#include "colormaker.h"    
2）qmlRegisterType<ColorMaker>("an.qt.ColorMaker", 1, 0, "ColorMaker");  
##在使用的qml中调用
1）import an.qt.ColorMaker 1.0  （声明，相当于头文件）  
2）代码实现：
<pre>
ColorMaker
{
    id: colorMaker;
    color: Qt.green;
}

onClicked:
{
    console.log("Cancel Button clicked....")
    colorMaker.start();
}
</pre>

##2. 使用qtquick2applicationviewer访问
1)
<pre>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QtQml>
#include "colorMaker.h"
 
 
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
 
    QtQuick2ApplicationViewer viewer;
    
    viewer.rootContext()->setContextProperty("colorMaker", new ColorMaker);
    
    viewer.setMainQmlFile(QStringLiteral("qml/colorMaker/main.qml"));
    viewer.showExpanded();
 
    return app.exec();
}
</pre>

<pre>
QtQuick2ApplicationViewer viewer;
viewer.rootContext()->setContextProperty("colorMaker", new ColorMaker);
viewer.setMainQmlFile(QStringLiteral("qml/colorMaker/main.qml"));
viewer.showExpanded();
</pre>
  一旦调用 setContextProperty() 导出了属性，就可以在 QML 中使用了，不需要 import 语句哦。下面是 main.qml 修改后的代码：

2)
<pre>
 Component.onCompleted: {
colorMaker.color = Qt.rgba(0,180,120, 255);
//[3]
//colorMaker.setAlgorithm(ColorMaker.LinearIncrease);
colorMaker.setAlgorithm(2);
changeAlgorithm(colorAlgorithm, colorMaker.algorithm());
}
</pre>
直接在qml中使用，之前创建的colorMaker变量

#二、C++中调用QML接口  
1）









#END注意（使用以上两种方法必须满足一下两种条件）
    
a、从 QObject 或 QObject 的派生类继承  
b、使用 Q_OBJECT 宏