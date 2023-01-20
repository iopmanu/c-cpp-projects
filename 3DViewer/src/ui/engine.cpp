#include "engine.hpp"

void GraphEngine::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
}

void GraphEngine::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-max_element, max_element, -max_element, max_element, -max_element, max_element);
}


void GraphEngine::paintGL()
{
        this->InitModel("/home/iopmanu/C8_3DViewer_v1.0-0/src/objects/test.obj");
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClearColor(255, 255, 255, 1.0);
        DrawModel();
}

void GraphEngine::DrawModel() {
    //glLineStipple(1, line_type);
    //glEnable(GL_LINE_STIPPLE);
    //glVertexPointer(3, GL_FLOAT, 0, vertexes_model);
    //glEnableClientState(GL_VERTEX_ARRAY)

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glVertexPointer(3, GL_DOUBLE, 0, vertexes_model);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(1, 0, 0);
    glDrawArrays(GL_POINTS, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    for (size_t i = 0; i < model.conf.vertex_quantity * 4; i++) {
        printf("%lf ", vertexes_model[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }


/*
    if (point_type != 0) {
        if (point_type == 1) {
            glEnable(GL_POINT_SMOOTH);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        } else {
            glDisable(GL_POINT_SMOOTH);
            glDisable(GL_BLEND);
        }

        //glPointSize()

        if (model != NULL) {
         // glDrawElements(GL_POINTS, indexes_quantity, GL_UNSIGNED_INT, indexes_model);
        }
    }
 */
}

GraphEngine::GraphEngine(QWidget *parent)
    : QOpenGLWidget{parent}, max_element(0), min_element(0),
      inited(false), freed(true), line_type(0xFFFF), point_type(2)
{
}

void GraphEngine::InitModel(const char *filename) {
    if (reading_obj_file(filename, &model)) {
        return;
    } else {
        vertexes_model = new GLdouble[model.conf.vertex_quantity * 4];

        indexes_quantity = 0;
        for (size_t i = 0; i < model.conf.surfaces_quantity; i++) {
            indexes_quantity += model.surfaces[i].points_quantity;
        }
        indexes_model = new GLuint[indexes_quantity * 2];

        for (size_t k = 0; k < model.conf.vertex_quantity; k++) {
            for (size_t i = 0; i < 4; i++) {
                for (int j = 0; j < 1; j++) {
                    //fprintf(stderr, "%ld ", i);
                    fprintf(stderr, "%lf ", model.vertices[k].matrix[i][j]);
                        vertexes_model[k * 4 + i] = model.vertices[k].matrix[i][j];

                       if (std::fabs(max_element) < std::fabs(model.vertices[k].matrix[i][j])) {
                       max_element = std::fabs(model.vertices[k].matrix[i][j]);
                    }
                }
            }
            //printf("\n");
        }
        printf("\n\n\n\n\n");

        min_element = - max_element;

        size_t offset = 0;

        for (size_t k = 0; k < model.conf.surfaces_quantity; k++) {
            for (size_t i = 0; i < model.surfaces[k].points_quantity; i++) {
                indexes_model[offset] = model.surfaces[k].vertices_sequence[i];
            }
            offset += model.surfaces[k].points_quantity;
        }

        inited = true;
    }
}


GraphEngine::~GraphEngine()
{
    /*if (freed) {
        delete [] vertexes_model;
        delete [] indexes_model;
    }
    if (inited) {
        object_dtor(model);
    }*/
}
