#include "DirectSceneCreator.h"
#include "Caption.h"
#include "ReeelsBgrBehaviour.h"
#include "AlignedReelsBehaviour.h"
#include "WinShowFramesBehaviour.h"
#include "WinCaptionBehaviour.h"
#include "ButtonBehaviour.h"
std::shared_ptr<Scene::Scene> DirectSceneCreator::GetScene()
{
	if (!_scene)
		_scene = CreateScene();
	return _scene;
}

std::shared_ptr<Scene::Scene> DirectSceneCreator::CreateScene()
{
	auto font = std::make_shared<sf::Font>();
	bool fontLoaded = font->loadFromFile("Rutheride.otf");

	auto result = std::make_shared<Scene::Scene>();
	auto root = std::make_shared<Scene::Node>();
	result->SetRootObject(root);

	root->AddChild(SetupReelsBgr());
	root->AddChild(SetupMainBgr());
	root->AddChild(SetupControlButtons(font));
	root->AddChild(CreateReelsNode());
	root->AddChild(CreateWinCaptionNode(font));

	return result;
}

Scene::Node::Ptr DirectSceneCreator::CreateReelsNode()
{
	auto reelsNode = std::make_shared<Scene::Node>();
	reelsNode->SetPriority(0);
	reelsNode->setPosition(290, 15);
	auto rotateBeh = std::make_shared<Game::AlignedReelsBehaviour>();
	reelsNode->SetName("reels");
	reelsNode->AddBehaviour(rotateBeh);
	rotateBeh->SetupReels(std::vector<size_t>({ 4, 4, 4 }));
	auto winFrameBeh = std::make_shared<Game::WinShowFramesBehaviour>();
	reelsNode->AddBehaviour(winFrameBeh);
	return reelsNode;
}

Scene::Node::Ptr DirectSceneCreator::CreateWinCaptionNode(std::shared_ptr<sf::Font>& font)
{
	auto winCaptionNode = std::make_shared<Scene::Node>();
	auto winCaptionText = std::make_shared<Scene::Caption>();
	winCaptionText->SetFont(font);
	winCaptionNode->SetName("winCaption");
	winCaptionNode->setPosition(sf::Vector2f(400, 300));
	winCaptionNode->SetDrawable(winCaptionText);
	winCaptionText->SetColor(sf::Color::White);
	winCaptionText->SetOutlineColor(sf::Color::Black);
	winCaptionText->SetOutlineThickness(1);
	winCaptionNode->AddBehaviour(std::make_shared<Game::WinCaptionBehaviour>());
	winCaptionNode->SetActive(false);
	winCaptionNode->SetPriority(100);
	return winCaptionNode;
}

Scene::Node::Ptr DirectSceneCreator::SetupControlButtons(std::shared_ptr<sf::Font> font)
{
	auto result = std::make_shared<Scene::Node>();

	result->AddChild(CreateButton("Start", font, sf::Vector2f(100, 500)));
	result->AddChild(CreateButton("Stop", font, sf::Vector2f(600, 500)));
	result->SetPriority(100);
	result->SetName("buttons");
	return result;
}

Scene::Node::Ptr DirectSceneCreator::CreateButton(std::string text,std::shared_ptr<sf::Font>& font, sf::Vector2f position){
	auto name = "button" + text;
	auto buttonRect = std::make_shared<Scene::SFMLRectangle>();
	const sf::Vector2f sizeRect(100, 60);
	buttonRect->SetColor(sf::Color::Red);
	buttonRect->SetSize(sizeRect);
	auto button = std::make_shared<Scene::Node>();
	button->setPosition(position.x, position.y);
	button->SetName(name);
	button->SetDrawable(buttonRect);
	auto textCaption = std::make_shared<Scene::Caption>();
	textCaption->SetFont(font);
	textCaption->SetText(text);
	auto textNode = std::make_shared<Scene::Node>();
	const sf::FloatRect bounds(textCaption->GetBounds());
	textNode->setOrigin((bounds.width) / 2 + bounds.left, (bounds.height) / 2 + bounds.top);
	textNode->setPosition(sizeRect.x / 2, sizeRect.y / 2);
	textNode->SetDrawable(textCaption);
	button->AddChild(textNode);
	return button;
}

Scene::Node::Ptr DirectSceneCreator::SetupReelsBgr()
{
	auto reelsBgr = std::make_shared<Scene::Node>();
	auto reelsBgrBeh = std::make_shared<Game::ReeelsBgrBehaviour>();
	auto separator = std::make_shared<Scene::SFMLRectangle>();
	separator->SetSize(sf::Vector2f(10, 600));
	separator->SetColor(sf::Color::Cyan);
	auto reelBgr = std::make_shared<Scene::SFMLRectangle>();
	reelBgr->SetSize(sf::Vector2f(110, 600));
	reelBgr->SetColor(sf::Color::Blue);
	reelsBgrBeh->SetBackground(reelBgr);
	reelsBgrBeh->SetSeparator(separator);
	reelsBgr->AddBehaviour(reelsBgrBeh);
	reelsBgr->SetPriority(-1);
	reelsBgr->setPosition(235, 0);
	reelsBgr->SetName("reelsBgr");
	return reelsBgr;
}

Scene::Node::Ptr DirectSceneCreator::SetupMainBgr()
{
	auto color = sf::Color(255, 100, 0);
	auto result = std::make_shared<Scene::Node>();

	auto top = CreateRect(color, 800, 135, 0, 0, 0, 0);
	result->AddChild(top);

	auto bottom = CreateRect(color, 800, 600, 0, 135, 0, 600);
	result->AddChild(bottom);

	auto left = CreateRect(color, 235, 600, 0, 0, 0, 0);
	result->AddChild(left);

	auto right = CreateRect(color, 235, 600, 235, 0, 800, 0);
	result->AddChild(right);

	result->SetPriority(10);
	result->SetName("bgr");
	return result;
}

Scene::Node::Ptr DirectSceneCreator::CreateRect(sf::Color& color,
												float width, float height,
												float originX, float originY,
												float positionX, float positionY) {
	auto node = std::make_shared<Scene::Node>();
	auto nodeRect = std::make_shared<Scene::SFMLRectangle>();
	nodeRect->SetColor(color);
	nodeRect->SetSize(width, height);
	node->SetDrawable(nodeRect);
	node->setOrigin(originX, originY);
	node->setPosition(positionX, positionY);
	return node;
}
