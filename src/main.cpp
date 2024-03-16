#include <Geode/Geode.hpp>

using namespace geode::prelude;

gd::string text;

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(UpdatedGarageLayer, GJGarageLayer)
{
    void setupPage(int const currentPage, IconType const iconType)
    {
        GJGarageLayer::setupPage(currentPage, iconType);
        for (int index{0}; index < getChildrenCount(); ++index)
        {
            if (ListButtonBar *iconSelectionBar{dynamic_cast<ListButtonBar *>(getChild(this, index))};
                iconSelectionBar != nullptr)
            {
                CCNode *menu{getChild(getChild(getChild(getChild(iconSelectionBar, 0), 0), 0), 0)};
                std::vector<CCNode *> itemsToRemove;
                for (int menuIndex{0}; menuIndex < menu->getChildrenCount(); ++menuIndex)
                {
                    CCNode *itemNode{getChild(menu, menuIndex)};
                    UnlockType unlockType;
                    switch (iconType)
                    {
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
                        default:
                            return;
                    }
                    ItemInfoPopup::create(itemNode->getTag(), unlockType)->removeMeAndCleanup();
                    if (std::strstr(text.data(), "2.21") != nullptr)
                    {
                        itemsToRemove.push_back(itemNode);
                    }
                }
                for (CCNode *item: itemsToRemove) item->removeMeAndCleanup();
            }
        }
    }
};

#include <Geode/modify/TextArea.hpp>
class $modify(GetTextDescription, TextArea)
{
    bool init(
        gd::string const str,
        char const *font,
        float const scale,
        float const width,
        CCPoint const anchor,
        float const lineHeight,
        bool const disableColor
    )
    {
        if (!TextArea::init(str, font, scale, width, anchor, lineHeight, disableColor)) return false;
        text = str;
        return true;
    }
};
