#pragma once
#include <stdint.h>
#include <stdbool.h>

namespace AutoUIConfig {
    struct HeroFeatureSettings {
        bool enabled;
        bool targetPriority;
        bool autoPredict;
        int comboSpeedMs;
        float targetDistanceMax;
        bool heroJoy;
        bool heroGusion;
        bool heroLylia;
        bool heroWanwan;
        bool heroXavier;
        bool heroPharsa;
    };

    struct RetributionFeatureSettings {
        bool enabled;
        bool buffMonster;
        bool turtleLord;
        bool lithoWanderer;
        bool crabMonster;
        float triggerDistance;
        int reactionDelayMs;
        bool dynamicHpScaling;
    };

    struct AutoTabState {
        HeroFeatureSettings leftSidebarHero;
        RetributionFeatureSettings rightSidebarRetri;
    };

    extern AutoTabState g_AutoState;
    void InitDefaults();
    bool SaveToFile(const char* path);
    bool LoadFromFile(const char* path);
}
