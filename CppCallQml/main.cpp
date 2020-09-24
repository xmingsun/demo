#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQuickView>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

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

    /*
    //例子1
    QQmlEngine engineQml;                                                                                  //QML引擎
    QQmlComponent component(&engineQml, QUrl(QStringLiteral("qrc:///main.qml")));        //加载QML
    //用QQmlComponent创建一个组件的实例，并且赋值给object*，这步操作非常关键，Object类型可以转换其他任意类型，比如QQuickItem
    QObject* object = component.create();
    object->setProperty("width", 500);                                                            //元对象系统赋值操作
    QQmlProperty(object, "width").write(500);                                               //元对象系统赋值操作
    QQuickItem* item = qobject_cast<QQuickItem*>(object);//把 QObject* 转换成 QQuickItem* 类型
    item->setWidth(50);
    */

    /*
    //例子2
    QQuickView  view;                                                                         //QQuickView对象
    view.setSource( QUrl(QStringLiteral("qrc:///main.qml")));        //加载QML
    view.show();                                                                                  //QQuickView可以显示可视化QML对象
    QQuickItem* root = view.rootObject();                                       //返回当前QQuickView的根节点，底下可以绑定很多节点
                                                                                 //在根节点root中查找有objectName："qml_button"这个标志位保存的QML节点qml_Button
    QObject* button = root->findChild<QObject*>("qml_button");
    button->setProperty("width", 500);
    */


    /*
    //例子3
    QQuickView  view;                                                                         //QQuickView对象
    view.setSource( QUrl(QStringLiteral("qrc:///main.qml")));        //加载QML
    view.show();                                                                                  //QQuickView可以显示可视化QML对象
    QQuickItem* root = view.rootObject();                                       //返回当前QQuickView的根节点，底下可以绑定很多节点
                                                                                 //在根节点root中查找有objectName："qml_button"这个标志位保存的QML节点qml_Button
    QObject* button = root->findChild<QObject*>("qml_button");
    if(button)
    {
//        QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
    }
    */
    return app.exec();
}
