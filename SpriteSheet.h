#ifndef SPRITESHEET_H
#define SPRITESHEET_H

class SpriteSheet{
    public:
        int width;
        int height;
        unsigned char *data;

        ~SpriteSheet();
        SpriteSheet(const char *fname);

};

#endif
