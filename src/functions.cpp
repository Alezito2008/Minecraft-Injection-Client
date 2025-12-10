#include "functions.h"

#include "mc/Minecraft.h"

void player_jump(JNIEnv* env) {
    Minecraft& mc = Minecraft::get();
    Player* p = mc.getPlayer();

    if (!p)
        std::cout << "Player not found, not jumping" << std::endl;
    
    p->jumpFromGround();
}