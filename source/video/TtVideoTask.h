#ifndef TTVIDEOTASK_H
#define TTVIDEOTASK_H

#include <QObject>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QQuickFramebufferObject>

// #include <opencv2/opencv.hpp>

// 自定义渲染器实现
class CubeRenderer : public QQuickFramebufferObject::Renderer
{
public:
    CubeRenderer()
        : m_shaderProgram(nullptr), m_vao(0), m_vbo(0), m_ebo(0), m_angle(0), m_initialized(false)
    {
    }
    ~CubeRenderer()
    {
        // 清理资源
        if (m_shaderProgram) {
            delete m_shaderProgram;
            m_shaderProgram = nullptr;
        }

        if (m_vao) {
            // 确保在正确的上下文中释放
            QOpenGLContext* context = QOpenGLContext::currentContext();
            if (context) {
                QOpenGLFunctions* f = context->functions();
                // f->glDeleteVertexArrays(1, &m_vao);
                f->glDeleteBuffers(1, &m_vbo);
                f->glDeleteBuffers(1, &m_ebo);
            }
        }
    }

    // 创建帧缓冲对象
    QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;

    // 执行实际渲染
    void render() override;

    // 在主线程和渲染线程间同步数据
    void synchronize(QQuickFramebufferObject* item) override;

private:
    void initializeGL();

    float m_angle;
    GLuint m_program;
    // OpenGL相关成员...
    QMatrix4x4 m_projection;
    QOpenGLShaderProgram* m_shaderProgram;
    QOpenGLTexture* m_texture;
    QSize m_viewportSize; // 新增成员变量


    GLuint m_vao;       // 顶点数组对象
    GLuint m_vbo;       // 顶点缓冲对象
    GLuint m_ebo;       // 元素缓冲对象
    bool m_initialized; // 跟踪是否已初始化
};


// 自定义 FramebufferObject 项
class OpenGLCubeItem : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(float rotationAngle READ rotationAngle WRITE setRotationAngle NOTIFY rotationAngleChanged)

public:
    OpenGLCubeItem()
    {
        qDebug() << "1";
    }

    // 必须实现此方法创建渲染器
    Renderer* createRenderer() const override;

    float rotationAngle() const { return m_angle; }
    void setRotationAngle(float angle)
    {
        if (m_angle == angle) {
            return;
        }
        m_angle = angle;
        update(); // 触发重绘
        emit rotationAngleChanged();
    }

signals:
    void rotationAngleChanged();

private:
    float m_angle;
};

#endif // TTVIDEOTASK_H
