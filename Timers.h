#ifndef TIMERS_H
#define TIMERS_H

class Timers{
    public:
        double physicsRate;
        double oobillion;
        struct timespec timeStart, timeEnd, timeCurrent;
        struct timespec walkTime, ramboWeaponOutTime, menuSelectionTime;
        struct timespec enemySpawnTime, ramboCollisionTime;
        Timers();
        double timeDiff(struct timespec*, struct timespec*);
        void timeCopy(struct timespec*, struct timespec*);
        void recordTime(struct timespec*);
};


#endif
