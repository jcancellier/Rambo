#ifndef HITBOX_H
#define HITBOX_H
//cx and cy in walk.cpp
class HitBox{
    private:
        int top;
        int bottom;
        int left;
        int right;
    public:
        HitBox(int top, int bottom, int left, int right);
};

#endif
