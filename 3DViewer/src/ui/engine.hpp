#ifndef ENGINE_H
#define ENGINE_H
#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QColorDialog>
#include <QOpenGLFunctions>

extern "C" {
#include "../obj_parser/parser.h"
}

class GraphEngine : public QOpenGLWidget
{
    Q_OBJECT
public:
    GraphEngine(QWidget* parent = nullptr);
    ~GraphEngine();

    void InitModel(const char *filename);
    void DrawModel();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


private:
    object model;

    char *filename;

    GLdouble *vertexes_model;
    GLuint *indexes_model;
    GLuint indexes_quantity;

    float max_element;
    float min_element;

    float widget_width;
    float widget_height;

    bool inited = false;
    bool freed = false;

    GLushort line_type;
    GLint point_type;
};

#endif // ENGINE_H
