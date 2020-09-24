#一、代码实现调用在main()中
<pre>
QObject* root = NULL;
QList<QObject*> rootObjects = engine.rootObjects();
int count = rootObjects.size();

for(int i = 0; i < count; i++)
{
    if(rootObjects.at(i)->objectName() == "rootObject")
    {
        root = rootObjects.at(i);
        break;
    }
}

QObject* button = root->findChild<QObject*>("button_qml_name");
if(button)
{
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
}

</pre>  
  
备注：
rootObjects.at(i)->objectName() == "rootObject"  
QObject* button = root->findChild<QObject*>("button_qml_name");  

**<font color = 'red'>都是OBJECTNAME: "BUTTON_QML_NAME"，并非ID</font>**

#二、C++中调用QML对象
所有的QML对象类型，包括QML引擎内部实现或者实现第三方库，都是QObject子类，都允许QML引擎使用 Qt元对象系统动态实例化任何QML对象类型。
在启动QML时，会初始化一个QQmlEngine作为QML引擎，然后使用QQmlComponent对象加载QML文档，QML引擎会提供一个默认的QQmlContext对象作为顶层执行的上下文，用来执行QML文档中定义的函数和表达式。
QQmlEngine::rootContext() 返回当前引擎QML的上下文，唯一的，QQmlContext* QQuickView::rootContext()
QQuickItem* QQuickView::rootObject() 返回当前QQuickView的根节点，也就是QML的根节点

##1、使用C++加载QML对象
###（1）使用QQmlComponent进行加载，读取QML文档，将转换成C++对象，进行赋值操作。
例子：
QQmlEngine engine;                                                                                  //QML引擎
QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:///main.qml")));        //加载QML
//用QQmlComponent创建一个组件的实例，并且赋值给object*，这步操作非常关键，Object类型可以转换其他任意类型，比如QQuickItem
QObject* object = component.create();                   
object->setProperty("width", 500);                                                            //元对象系统赋值操作
QQmlProperty(object, "width").write(500);                                               //元对象系统赋值操作
QQuickItem* item = qobject_cast<QQuickItem*>(object);                     //把 QObject* 转换成 QQuickItem* 类型
tiem->setWidth(500);                                                                                // QQuickItem* 赋值操作

###（2）使用QQuickView加载，QQuickView是继承QWindow，所有可以加载一个可视化QML对象，并且可以与应用程序的图形用户界面进行融合。
例子：
QQuickView view;                                                                        //QQuickView对象
view.setSource( QUrl(QStringLiteral("qrc:///main.qml")));        //加载QML
view.show();                                                                                  //QQuickView可以显示可视化QML对象
QQuickItem* item = view.rootObject();                                    //返回当前QQuickView的根节点
tiem->setWidth(500);                                                                  //QQuickItem* 赋值操作


##2、使用对象名字访问加载的QML对象
QML中的所有节点都会绑定到根节点树上， QObject::objectName这个属性保存特定对象。QML组件的子对象可以在C++中通过  QObject::findChild()查找到在QML中用 objectName定义的对象。

b ool  QObject:: setProperty (const  char  * name , const  QVariant  & value )  元对象系统的设置函数
T QObject::findChild(const QString &name = QString(), Qt::FindChildOptionsoptions = Qt::FindChildrenRecursively) const  是一个QObject类型的模板函数，意味着可以转成任意类型如：

QPushButton* button = root.findChild<QPushButton*>("qml_button")

QObject* object = root.findChild<QObject*>("qml_object")

QQuickItem* item = root.findChild<QQuickItem*>("qml_item")

如果有多个对象使用objectName："qml_button" 同名 标记， QObject::findChild 返回最后一个标记的QML对象，QObject::findChildren返回所有标记的QML对象存放在QList类型的列表中。

例子：
QQuickView  view;                                                                         //QQuickView对象
view.setSource( QUrl(QStringLiteral("qrc:///main.qml")));        //加载QML
view.show();                                                                                  //QQuickView可以显示可视化QML对象
QQuickItem* root = view.rootObject();                                       //返回当前QQuickView的根节点，底下可以绑定很多节点
                                                                             //在根节点root中查找有objectName："qml_button"这个标志位保存的QML节点qml_Button
QObject* button = root->findChild<QObject*>("qml_button");        
button->setProperty("width", 500);
                                                   //在根节点root中查找有 objectName："qml_item"这个标志位保存的QML节点qml_item，换成QQuickItem*类型
QQuickItem* item = root->findChild<QQuickItem*>("qml_item");    
item->setProperty("color", "red");


##3、使用C++访问QML对象成员
###（1）所有的QML对象都会暴露在Qt的元对象系统，C++可以通过元对象系统的 QMetaObject::invokeMethod()调用QML中注册到元对象系统函数。
例子：
qml中定义的函数：
function qmlFunction(msg)
{
    console.log("QML get message:",msg);
}
C++调用QML函数：
QQmlEngine engine;                                                                                  //QML引擎
QQmlComponent component(&engine,  QUrl(QStringLiteral("qrc:///main.qml")));        //加载QML
QObject* object = component.create();                     //用QQmlComponent创建一个组件的实例，并且赋值给object*，这步操作非常关键，Object类型可以转换其他任意类型，比如QQuickItem
QVariant rValue;
QVariant msg = "Hello for C++"；
QMetaObject::invokeMethod(object,  "qmlFunction",  Q_RETURN_ARG(QVariant,rValue),  Q_ARG(QVariant, msg));

###（2）C++可以接收所有的QML信号，QML也可以接收C++信号，在C++中可以使QObject::connect()进行接收信号槽。
例子：
qml中定义一个信号：
signal qmlSignal(string msg)
C++进行连接信号：
QQuickView  view;                                                                         //QQuickView对象
view.setSource( QUrl(QStringLiteral("qrc:///main.qml")));        //加载QML
view.show();                                                                                  //QQuickView可以显示可视化QML对象
QQuickItem* root = view.rootObject();                                       //返回当前QQuickView的根节点，底下可以绑定很多节点
QObject::connect(root,  SIGNAL(qmlSignal(QString)),  this,  SLOT(Slotqml(QString)));


