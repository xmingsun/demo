#一、QML中调用C++接口
##1）QML中可以直接调用C++中的
a、无法调用普通函数  
b、Q_INVOKABLE GenerateAlgorithm algorithm() const;  
需要调用的时候在函数前面增加 Q_INVOKABLE
c、C++中的槽函数可以直接调用。    
  
备注：需要调用的函数，可以用Q_INVOKABLE或者写成槽函数
##在main函数中注册  
1）#include "colormaker.h"    
2）qmlRegisterType<ColorMaker>("an.qt.ColorMaker", 1, 0, "ColorMaker");  
##在使用的qml中调用
1）import an.qt.ColorMaker 1.0  （声明，相当于头文件）
2）

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

  
#二、C++中调用QML接口  
a、
















#END注意（使用以上两种方法必须满足一下两种条件）
    
a、从 QObject 或 QObject 的派生类继承  
b、使用 Q_OBJECT 宏