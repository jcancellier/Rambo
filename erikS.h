typedef double Flt;
typedef double Vec[3];
typedef Flt     Matrix[4][4];
void renderBackground(float s, float sh, float w, float h );
void pauseScreen();
void renderlevel();

 class Level {

    public:

        unsigned char arr[21][700];
        int nrows, ncols;
        int dynamicHeight[180];
        int tilesize[2];
        Flt ftsz[2];
        Flt tile_base;
        Level();

        void removeCrLf(char *str);
	void renderlevel();
};

