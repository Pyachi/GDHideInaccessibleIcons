#include <Geode/Geode.hpp>

using namespace geode::prelude;

gd::string text;
std::unordered_map<UnlockType, std::unordered_map<int, bool>> mapCachedIconStatuses;

#include <Geode/modify/GJGarageLayer.hpp>

class $modify(UpdatedGarageLayer, GJGarageLayer) {
    [[maybe_unused]] CCArray *getItems(int itemCount, int page, IconType iconType, int selectedTag) {
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Get list of all icons
        CCArray *allItems{new CCArray};
        for (int pageIndex{0}; pageIndex < itemCount / 36 + 1; ++pageIndex) {
            CCArray *pageItems{GJGarageLayer::getItems(itemCount, pageIndex, iconType, selectedTag)};
            for (int itemsIndex{0}; itemsIndex < pageItems->count(); ++itemsIndex) {
                allItems->addObject(pageItems->objectAtIndex(itemsIndex));
            }
        }
        GJGarageLayer::getItems(1, page, iconType, selectedTag);
        std::vector<int> indicesToRemove;
        for (int index{0}; index < allItems->count(); ++index) {
            CCMenuItemSpriteExtra *item{dynamic_cast<CCMenuItemSpriteExtra *>(allItems->objectAtIndex(index))};
            UnlockType unlockType;
            switch (iconType) {
                case IconType::Cube:
                    unlockType = UnlockType::Cube;
                    break;
                case IconType::Ship:
                    unlockType = UnlockType::Ship;
                    break;
                case IconType::Ball:
                    unlockType = UnlockType::Ball;
                    break;
                case IconType::Ufo:
                    unlockType = UnlockType::Bird;
                    break;
                case IconType::Wave:
                    unlockType = UnlockType::Dart;
                    break;
                case IconType::Robot:
                    unlockType = UnlockType::Robot;
                    break;
                case IconType::Spider:
                    unlockType = UnlockType::Spider;
                    break;
                case IconType::Swing:
                    unlockType = UnlockType::Swing;
                    break;
                case IconType::Jetpack:
                    unlockType = UnlockType::Jetpack;
                    break;
                case IconType::DeathEffect:
                case IconType::Special:
                    continue;
            }
            if (mapCachedIconStatuses[unlockType].contains(item->getTag())) {
                if (!mapCachedIconStatuses[unlockType][item->getTag()]) {
                    indicesToRemove.push_back(index);
                }
            } else {
                ItemInfoPopup::create(item->getTag(), unlockType)->removeMeAndCleanup();
                if (std::strstr(text.data(), "2.21") != nullptr) {
                    mapCachedIconStatuses[unlockType][item->getTag()] = false;
                    indicesToRemove.push_back(index);
                } else if (std::strstr(text.data(), "gauntlet") != nullptr) {
                    if (std::strstr(text.data(), "Fire") == nullptr &&
                        std::strstr(text.data(), "Ice") == nullptr &&
                        std::strstr(text.data(), "Poison") == nullptr &&
                        std::strstr(text.data(), "Shadow") == nullptr &&
                        std::strstr(text.data(), "Lava") == nullptr &&
                        std::strstr(text.data(), "Bonus") == nullptr &&
                        std::strstr(text.data(), "Chaos") == nullptr &&
                        std::strstr(text.data(), "Demon") == nullptr &&
                        std::strstr(text.data(), "Time") == nullptr &&
                        std::strstr(text.data(), "Crystal") == nullptr &&
                        std::strstr(text.data(), "Magic") == nullptr &&
                        std::strstr(text.data(), "Spike") == nullptr &&
                        std::strstr(text.data(), "Monster") == nullptr &&
                        std::strstr(text.data(), "Doom") == nullptr &&
                        std::strstr(text.data(), "Death") == nullptr &&
                        std::strstr(text.data(), "Water") == nullptr &&
                        std::strstr(text.data(), "Portal") == nullptr &&
                        std::strstr(text.data(), "Castle") == nullptr &&
                        std::strstr(text.data(), "World") == nullptr &&
                        std::strstr(text.data(), "Galaxy") == nullptr &&
                        std::strstr(text.data(), "Universe") == nullptr &&
                        std::strstr(text.data(), "Discord") == nullptr &&
                        std::strstr(text.data(), "Split") == nullptr) {
                        mapCachedIconStatuses[unlockType][item->getTag()] = false;
                        indicesToRemove.push_back(index);
                    }
                } else mapCachedIconStatuses[unlockType][item->getTag()] = true;
            }
        }
        auto iter{indicesToRemove.rbegin()};
        auto const end{indicesToRemove.rend()};
        for (; iter != end; ++iter) {
            allItems->removeObjectAtIndex(*iter);
        }
        CCArray *items{new CCArray};
        for (int itemIndex{page * 36};
             itemIndex < std::min(page * 36 + 36, static_cast<int>(allItems->count())); ++itemIndex) {
            items->addObject(allItems->objectAtIndex(itemIndex));
        }
        return items;
    }
};

#include <Geode/modify/TextArea.hpp>

class $modify(GetTextDescription, TextArea) {
    bool init(
            gd::string const str,
            char const *font,
            float const scale,
            float const width,
            CCPoint const anchor,
            float const lineHeight,
            bool const disableColor
    ) {
        if (!TextArea::init(str, font, scale, width, anchor, lineHeight, disableColor)) return false;
        text = str;
        return true;
    }
};