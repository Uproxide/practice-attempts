#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

bool isPractice;
int attemptCount;
int practiceAttemptCount;

class $modify(EndLevelLayer) {
	void customSetup() {
		EndLevelLayer::customSetup();
		
		std::string attemptMessage = fmt::format("Practice Mode Attempts: {}", practiceAttemptCount);
		auto attemptLabel = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("attempts-label"));

		if (auto practiceAttemptsLabel = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("practice-attempts-label"_spr))) {
			practiceAttemptsLabel->removeFromParent();
		}

		if (isPractice) {
			if (Mod::get()->getSettingValue<bool>("replace-attempt-count")) {
				attemptLabel->setString(attemptMessage.c_str());
			} else {
				auto jumpLabel = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("jumps-label"));
				auto timeLabel = static_cast<CCLabelBMFont*>(this->getChildByIDRecursive("time-label"));
				auto practiceAttemptsLabel = CCLabelBMFont::create(attemptMessage.c_str(), "goldFont.fnt");

				jumpLabel->setPositionY(jumpLabel->getPositionY() - 15);
				timeLabel->setPositionY(timeLabel->getPositionY() - 15);

				m_mainLayer->addChild(practiceAttemptsLabel);
				practiceAttemptsLabel->setScale(attemptLabel->getScale());
				practiceAttemptsLabel->setPosition(attemptLabel->getPosition());
				practiceAttemptsLabel->setPositionY(practiceAttemptsLabel->getPositionY() - 15);
				practiceAttemptsLabel->setID("practice-attempts-label"_spr);

				attemptLabel->setPositionY(attemptLabel->getPositionY() + 10);
			}
		}

		isPractice = false;
		attemptCount = 1;
		practiceAttemptCount = 1;
	}
};

class $modify(PlayLayer) {
	bool init(GJGameLevel* p0, bool p1, bool p2) {
		if (!PlayLayer::init(p0, p1, p2)) return false;

		isPractice = m_isPracticeMode;
		attemptCount = 1;
		practiceAttemptCount = 1;

		return true;
	}

	void updateAttempts() {
		PlayLayer::updateAttempts();

		attemptCount += 1;

		if (isPractice) {
			practiceAttemptCount += 1;
		}
	}

	void togglePracticeMode(bool p0) {
		PlayLayer::togglePracticeMode(p0);

		isPractice = p0;
	}
};