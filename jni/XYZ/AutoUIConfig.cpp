#include "AutoUIConfig.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

namespace AutoUIConfig {
    AutoTabState g_AutoState = {
        // HeroFeatureSettings (Sidebar Kiri)
        {
            false,  // enabled
            true,   // targetPriority
            false,  // autoPredict
            150,    // comboSpeedMs
            8.5f,   // targetDistanceMax
            false,  // heroJoy
            false,  // heroGusion
            false,  // heroLylia
            false,  // heroWanwan
            false,  // heroXavier
            false   // heroPharsa
        },
        // RetributionFeatureSettings (Sidebar Kanan)
        {
            false,  // enabled
            true,   // buffMonster
            true,   // turtleLord
            false,  // lithoWanderer
            false,  // crabMonster
            7.0f,   // triggerDistance
            50,     // reactionDelayMs
            true    // dynamicHpScaling
        }
    };

    void InitDefaults() {
        memset(&g_AutoState, 0, sizeof(g_AutoState));
        g_AutoState.leftSidebarHero.targetPriority = true;
        g_AutoState.leftSidebarHero.comboSpeedMs = 150;
        g_AutoState.leftSidebarHero.targetDistanceMax = 8.5f;

        g_AutoState.rightSidebarRetri.buffMonster = true;
        g_AutoState.rightSidebarRetri.turtleLord = true;
        g_AutoState.rightSidebarRetri.triggerDistance = 7.0f;
        g_AutoState.rightSidebarRetri.reactionDelayMs = 50;
        g_AutoState.rightSidebarRetri.dynamicHpScaling = true;
    }

    bool SaveToFile(const char* path) {
        int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd < 0) return false;
        ssize_t written = write(fd, &g_AutoState, sizeof(g_AutoState));
        close(fd);
        return (written == sizeof(g_AutoState));
    }

    bool LoadFromFile(const char* path) {
        int fd = open(path, O_RDONLY);
        if (fd < 0) return false;
        ssize_t readBytes = read(fd, &g_AutoState, sizeof(g_AutoState));
        close(fd);
        return (readBytes == sizeof(g_AutoState));
    }
}
