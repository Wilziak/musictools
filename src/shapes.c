#include "shapes.h"

static void shape_init_vcolor(GLuint *vbo, color_t c, int len)
{
    int i;
    color_t *vcolor;

    vcolor = malloc(sizeof(color_t) * len);

    for(i=0; i<len; i++)
        vcolor[i] = c;

    //Init vertex color buffer
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_t)*len, vcolor, GL_STATIC_DRAW);

    //Map vcolor VBO to binded VAO
    glEnableVertexAttribArray(VERT_ATTR_COLOR);
    glVertexAttribPointer(VERT_ATTR_COLOR, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    free(vcolor);
}

static void shape_init_vpos(GLuint *vbo, GLfloat *vpos, int len)
{
    //Init vertex pos buffer
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, len*sizeof(GL_FLOAT), vpos, GL_STATIC_DRAW);

    //Map vpos VBO to binded VAO
    glEnableVertexAttribArray(VERT_ATTR_POS);
    glVertexAttribPointer(VERT_ATTR_POS, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

shape_t shape_init_square(color_t c)
{
    shape_t s = SHAPE_INIT();

    GLfloat vpos[] = { -0.5f, 0.5f, 0.0f,
                       0.5f, 0.5f, 0.0f,
                       0.5f, -0.5f, 0.0f,
                       -0.5f, -0.5f, 0.0f };

    GLuint elements[] = { 0, 1, 2, 2, 3, 0 };

    s.v_len = 4;
    s.e_len = sizeof(elements);

    //Init VAO
    glGenVertexArrays(1, &s.vao);
    glBindVertexArray(s.vao);

    //Init VBOs
    shape_init_vpos(&s.vpos, vpos, sizeof(vpos));
    shape_init_vcolor(&s.vcolor, c, s.v_len);

    //Init EBO
    glGenBuffers(1, &s.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glBindVertexArray(0); //Unbind VAO
    return s;
}

shape_t shape_init_triangle(color_t c)
{
    shape_t s = SHAPE_INIT();

    GLfloat vpos[] = { 0.0f, 0.5f, 0.0f,
                       -1.0f, -1.0f, 0.0f,
                       1.0f, -1.0f, 0.0f };
    s.v_len = 3;

    //Init VAO
    glGenVertexArrays(1, &s.vao);
    glBindVertexArray(s.vao);

    //Init VBOs
    shape_init_vpos(&s.vpos, vpos, sizeof(vpos));
    shape_init_vcolor(&s.vcolor, c, s.v_len);

    glBindVertexArray(0); //Unbind VAO
    return s;
}

void shape_draw(shape_t *s)
{
    glBindVertexArray(s->vao);

    if(s->ebo) {
        glDrawElements(GL_TRIANGLES, s->e_len, GL_UNSIGNED_INT, 0);
        return;
    }

    glDrawArrays(GL_TRIANGLES, 0, s->v_len);
}