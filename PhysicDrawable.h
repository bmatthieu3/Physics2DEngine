#ifndef __PHYSIC_DRAWABLE_H_
#define __PHYSIC_DRAWABLE_H_

#include <GL/gl.h>
#include <GL/glu.h>

class PhysicDrawable {
    public:
        PhysicDrawable() {

        };
        virtual ~PhysicDrawable() {

        }
    
        virtual void draw() const = 0;
    private:
        float r, g, b;
};

#endif