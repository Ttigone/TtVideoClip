#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

#include "video/TtVideoTask.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    // 启用OpenGL调试输出
    // QSurfaceFormat format;
    // format.setOption(QSurfaceFormat::DebugContext);
    // QSurfaceFormat::setDefaultFormat(format);

    // Qt6中Qt Quick默认使用QSGRendererInterface::Direct3D11，因此之前Qt5的项目中使用FBO的例子在Qt6上无法正确渲染，因为框架不会主动调用createRenderer()方法！
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);


    // 注册到QML类型系统
    // 参数依次为：
    // 1. 类型
    // 2. 导入模块的URI
    // 3. 主版本号
    // 4. 次版本号
    // 5. 在QML中使用的类型名称
    qmlRegisterType<OpenGLCubeItem>("CustomOpenGL", 1, 0, "OpenGLCube");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
//    const QUrl url(u"qrc:/ui/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    // cv::VideoCapture video;
    // video.open(0);
    // if (!video.isOpened()) { // 判断摄像头是否成功打开
    //     qDebug() << "fuck";
    //     return -1;
    // }
    // // 连续图像中的每一个称为帧
    // while (1) { // 连续的图像组成视频
    //     cv::Mat frame;
    //     video >> frame;    // 将 VideoCapture实例读取的图像读取到 Mat 实例
    //     if (frame.empty()) // 检查帧是否为空
    //         break;
    //     imshow("Frame", frame);         // 显示帧
    //     char c = (char)cv::waitKey(25); // 25 毫秒的按键,在等待期间按下 ESC 按键则中断循环
    //     if (c == 27)                    // ESC
    //         break;
    // }
    // video.release();         // 释放相机资源
    // cv::destroyAllWindows(); // 销毁显示图像的窗口

    return app.exec();
}

// #include <QGuiApplication>
// #include <QQmlApplicationEngine>

// int main(int argc, char *argv[])
// {
//     QGuiApplication app(argc, argv);

//     QQmlApplicationEngine engine;
//     QObject::connect(
//         &engine,
//         &QQmlApplicationEngine::objectCreationFailed,
//         &app,
//         []() { QCoreApplication::exit(-1); },
//         Qt::QueuedConnection);
//     engine.loadFromModule("Rare", "Main");

//     return app.exec();
// }
