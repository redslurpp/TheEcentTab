// The Ecent Tab
// Made by redslurpp, dedicated to DJ LeFave

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

using namespace geode::prelude;

class $modify(EcentSearchLayer, LevelSearchLayer) {
	// type should not matter as it's just a toggle between lists and levels
	bool init(int type) {
		if (!LevelSearchLayer::init(type))
			return false;

		// try to get the recent button, so we can replace the sprite with our own
		if (auto qsRecent = static_cast<CCMenuItemSpriteExtra*>(this->getChildByIDRecursive("recent-button"))) {
			// create our new sprite
			auto spr = SearchButton::create(
				"GJ_longBtn04_001.png",
				"Ecent",
				0.5f,
				"GJ_sRecentIcon_001.png"
			);

			// now set the sprite, and pray to god that this actually works
			qsRecent->setSprite(spr);
		}

		return true;
	}
};

class $modify(EcentLevelBrowserLayer, LevelBrowserLayer) {
	bool init(GJSearchObject* req) {
		if (!LevelBrowserLayer::init(req))
			return false;

		auto list = this->getChildByIDRecursive("GJListLayer");

		// only if we are searching recent levels
		if (req->m_searchType == SearchType::Recent) {
			auto winSize = CCDirector::get()->getWinSize();

			// we decide which sprite to use, depending on what type of thing we are searching
			auto spriteName = "ecentLevels.png"_spr;
			
			// for lists
			if (req->m_searchMode == 1)
				spriteName = "ecentLists.png"_spr;


			// create our new header
			auto headerSprite = CCSprite::create(spriteName);
			headerSprite->setID("header-sprite");

			// this may look like a mess (because it is, why did i do this), but it positions the label above the list
			headerSprite->setPosition(ccp(winSize.width/2, list->getContentSize().height + list->getPositionY() + 5 + headerSprite->getContentSize().height/2));
			this->addChild(headerSprite);
			headerSprite->setZOrder(2);
		}

		return true;
	}

	gd::string getSearchTitle() {
		gd::string ret = LevelBrowserLayer::getSearchTitle();
		
		// we only return blank when browsing ecent, as the custom header will go on top, so we don't want the original text
		if (this->m_searchObject->m_searchType == SearchType::Recent)
			return "";

		return ret;
	}

};
