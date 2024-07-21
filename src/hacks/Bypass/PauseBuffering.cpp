#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/modify/UILayer.hpp>

namespace eclipse::hacks::Bypass {

    class PauseBuffering : public hack::Hack {
        void init() override {
            auto tab = gui::MenuTab::find("Bypass");
            tab->addToggle("Pause Buffering", "bypass.pausebuffering")
                ->handleKeybinds()
                ->setDescription("Prevents the game from blocking pause buffering.");
        }

        [[nodiscard]] const char* getId() const override { return "Pause Buffering"; }
    };

    REGISTER_HACK(PauseBuffering)

    class $modify(PauseBuffering_Hook, UILayer) {
        void onPause(cocos2d::CCObject* sender) {
            if (!config::get<bool>("bypass.pausebuffering", false))
                return UILayer::onPause(sender);

            auto* playLayer = PlayLayer::get();
            if (!playLayer) return UILayer::onPause(sender);

            uint32_t original = playLayer->m_gameState.m_pauseCounter;
            playLayer->m_gameState.m_pauseCounter = 0;
            UILayer::onPause(sender);
            playLayer->m_gameState.m_pauseCounter = original;
        }
    };

}
