#include "TtVideoTask.h"


QQuickFramebufferObject::Renderer* OpenGLCubeItem::createRenderer() const
{
    qDebug() << "t1";
    return new CubeRenderer();
}

QOpenGLFramebufferObject* CubeRenderer::createFramebufferObject(const QSize& size)
{
    m_viewportSize = size;
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4); // 多采样抗锯齿
    return new QOpenGLFramebufferObject(size, format);
}

void CubeRenderer::render()
{
    // qDebug() << "TEST";
    // // 设置OpenGL状态
    // glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glEnable(GL_DEPTH_TEST);

    // m_shaderProgram->bind();

    // // 更新变换矩阵
    // QMatrix4x4 modelView;
    // modelView.rotate(m_angle, 0.0f, 1.0f, 0.0f);
    // modelView.perspective(45.0f, m_viewportSize.width() / m_viewportSize.height(), 0.1f, 100.0f);

    // // 设置着色器参数
    // m_shaderProgram->bind();
    // m_shaderProgram->setUniformValue("mvp", m_projection * modelView);

    // // 绘制立方体
    // // ...绘制代码...
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // m_shaderProgram->release();

    // // 必须调用update()来请求重新渲染，否则只会渲染一次
    // update();

    if (!m_initialized) {
        initializeGL();
        m_initialized = true;
    }

    if (!QOpenGLContext::currentContext()) {
        qDebug() << "No OpenGL context!";
        return;
    }

    // QOpenGLExtraFunctions* f = QOpenGLContext::currentContext()->extraFunctions();

    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    // f->glEnableVertexAttribArray(0);
    // f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // f->glDisableVertexAttribArray(0);
    QOpenGLExtraFunctions* f = QOpenGLContext::currentContext()->extraFunctions();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_shaderProgram->bind();
    f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_shaderProgram->release();
}

void CubeRenderer::synchronize(QQuickFramebufferObject* item)
{
    qDebug() << "t2";
    OpenGLCubeItem* cubeItem = qobject_cast<OpenGLCubeItem*>(item);
    if (cubeItem) {
        m_angle = cubeItem->rotationAngle();
    }
    m_angle = cubeItem->rotationAngle();
    m_viewportSize = cubeItem->size().toSize();
}

void CubeRenderer::initializeGL()
{
    // if (m_initialized) {
    //     return;
    // }

    // // 获取OpenGL函数指针
    // // QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    // QOpenGLExtraFunctions* f = QOpenGLContext::currentContext()->extraFunctions();

    // // 创建着色器程序
    // m_shaderProgram = new QOpenGLShaderProgram();

    // // 顶点着色器
    // const char* vertexShaderSource = R"(
    //     attribute vec3 position;
    //     attribute vec3 color;
    //     varying vec3 vColor;
    //     uniform mat4 mvpMatrix;

    //     void main() {
    //         gl_Position = mvpMatrix * vec4(position, 1.0);
    //         vColor = color;
    //     }
    // )";

    // // 片段着色器
    // const char* fragmentShaderSource = R"(
    //     varying vec3 vColor;

    //     void main() {
    //         gl_FragColor = vec4(vColor, 1.0);
    //     }
    // )";

    // // 编译和链接着色器
    // m_shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    // m_shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    // m_shaderProgram->link();

    // // 立方体顶点数据 (位置, 颜色)
    // float vertices[] = {
    //     // 位置              // 颜色
    //     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    //     -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
    //     0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    //     0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
    //     -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f};

    // // 立方体的索引
    // unsigned int indices[] = {
    //     0, 1, 2, 2, 3, 0, // 前面
    //     4, 5, 6, 6, 7, 4, // 后面
    //     0, 4, 7, 7, 3, 0, // 左面
    //     1, 5, 6, 6, 2, 1, // 右面
    //     3, 2, 6, 6, 7, 3, // 上面
    //     0, 1, 5, 5, 4, 0  // 下面
    // };

    // // 创建并绑定VAO和VBO
    // f->glGenVertexArrays(1, &m_vao);
    // f->glGenBuffers(1, &m_vbo);
    // f->glGenBuffers(1, &m_ebo);

    // f->glBindVertexArray(m_vao);

    // // 绑定并填充顶点缓冲
    // f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // // 绑定并填充索引缓冲
    // f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    // f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // 设置顶点属性指针
    // // 位置属性
    // f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    // f->glEnableVertexAttribArray(0);
    // // 颜色属性
    // f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // f->glEnableVertexAttribArray(1);

    // // 解绑VAO
    // f->glBindVertexArray(0);

    // // 设置投影矩阵
    // m_projection.perspective(45.0f, m_viewportSize.width() / (float)m_viewportSize.height(), 0.1f, 100.0f);

    // m_initialized = true;
    // 简单三角形测试

    // // 获取OpenGL函数指针
    // QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    qDebug() << "[RENDER] Initializing GL Resources";
    QOpenGLExtraFunctions* f = QOpenGLContext::currentContext()->extraFunctions();
    // 创建简单着色器
    const char* vsrc = "attribute vec3 pos; void main() { gl_Position = vec4(pos,1.0); }";
    const char* fsrc = "void main() { gl_FragColor = vec4(1.0,0.0,0.0,1.0); }";

    m_shaderProgram = new QOpenGLShaderProgram();
    m_shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vsrc);
    m_shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fsrc);
    if (!m_shaderProgram->link()) {
        qDebug() << "Shader Error:" << m_shaderProgram->log();
    }

    // 三角形数据
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    f->glGenBuffers(1, &m_vbo);
    f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    qDebug() << "test3";
}
