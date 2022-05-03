#pragma once
#include "SceneManager.h"
#include "SFMLDrawable.h"
#include "ButtonBehaviour.h"

//„I„ƒ„„€„|„„x„…„u„„„ƒ„‘ „r „€„ƒ„~„€„r„~„€„} „y„x-„x„p „~„u„‡„r„p„„„{„y „r„‚„u„}„u„~„y - „„€ „r„€„x„}„€„w„~„€„ƒ„„„y „‘ „q„ „ƒ„t„u„|„p„| „ƒ„‰„y„„„„r„p„~„y„u „ƒ„ˆ„u„~„ „y„x „{„€„~„†„y„s„…„‚„p„ˆ„y„€„~„~„„‡ „†„p„z„|„€„r.
class DirectSceneCreator :
    public SceneManager
{
private:
    std::shared_ptr<Scene::Scene> _scene;
    std::shared_ptr<Scene::Scene> CreateScene();
    Scene::Node::Ptr CreateReelsNode();
    Scene::Node::Ptr CreateWinCaptionNode(std::shared_ptr<sf::Font>& font);
    Scene::Node::Ptr SetupControlButtons(std::shared_ptr<sf::Font> font);
    Scene::Node::Ptr CreateButton(std::string text,
 std::shared_ptr<sf::Font>& font,
        sf::Vector2f position
       );
    Scene::Node::Ptr SetupReelsBgr();

    Scene::Node::Ptr SetupMainBgr();
    Scene::Node::Ptr  CreateRect(sf::Color& color, 
        float width, float height,
        float originX, float originY,
        float positionX, float positionY
    );
public:
    std::shared_ptr<Scene::Scene>GetScene();

};

