#ifndef PARTICLEMANAGER
#define PARTICLEMANAGER

class ParticleManager
{
    friend class CLManager;
    friend class Window;

    public:
        ParticleManager() {};
        virtual ~ParticleManager();

    private:
        int m_initShape = 1;
        bool m_shapeUpdated = false;
        bool m_shapeUpdating = false;
        bool m_update = false;
        bool m_followMouse = true;
        bool m_gravitySet = false;
        bool m_rotate = false;
        GLuint m_colVBO, m_posVBO, m_vao;
        // GLM PROJ + GRAV VEC3 HERE
};

#endif
