#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/modify/PlayerObject.hpp>

namespace eclipse::hacks::Player {

    class NoPlatformerJumpSquish : public hack::Hack {
        void init() override {
            config::setIfEmpty<bool>("player.noplatformersquish", false);
            auto tab = gui::MenuTab::find("Player");
            tab->addToggle("No Platformer Jump Squish", "player.noplatformersquish")
                ->setDescription("Disables the squishing animation when jumping in place while playing platformer levels. (Created by RayDeeUx)")
                ->handleKeybinds();
        }

        [[nodiscard]] const char* getId() const override { return "No Platformer Jump Squish"; }
    };

    REGISTER_HACK(NoPlatformerJumpSquish)

    class $modify(MyPlayerObject, PlayerObject){
        void animatePlatformerJump(float p0) {
            if (config::get<bool>("player.noplatformersquish", true)) { return; }
            PlayerObject::animatePlatformerJump(p0);
        }
    };

}