#一、QML中调用C++接口
##1）QML中可以直接调用C++中的
a、无法调用普通函数  
b、Q_INVOKABLE GenerateAlgorithm algorithm() const;  
需要调用的时候在函数前面增加 Q_INVOKABLE
  
  
  
#二、C++中调用QML接口  
a、