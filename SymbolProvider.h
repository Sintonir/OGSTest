#pragma once
#include "SFMLDrawable.h"
//„I„~„„„u„‚„†„u„z„ƒ, „r„€„x„r„‚„p„‹„p„„‹„y„z „‚„y„ƒ„…„u„}„„u „€„q„Œ„u„{„„„-„ƒ„y„}„r„€„|„ „„€ „y„‡ id.
class SymbolProviderBase
{
public:
	virtual Scene::Drawable::Ptr GetSymbolDrawable(size_t symbol) = 0;
};
//„I „„‚„€„ƒ„„„u„z„Š„y„z „r„p„‚„y„p„~„„ „ƒ „y„ƒ„„€„|„„x„€„r„p„~„y„u„} „„‚„€„ƒ„„„„‡ „†„€„‚„}.
class SimpleSymbolProvider:public SymbolProviderBase
{
public:
	virtual Scene::Drawable::Ptr GetSymbolDrawable(size_t symbol) override {
		auto result = std::make_shared<Scene::SFMLCircle>();
		result->SetRadius(50.0f);
		result->SetOrigin(sf::Vector2f(50, 50));
		switch (symbol) {
		case 0: {
			result->SetColor(sf::Color::Red);
			break;
		}
		case 1: {
			result->SetColor(sf::Color::Yellow);
			result->ChangeToRegularPolygon(3);
			break;
		}
		case 2: {
			result->SetColor(sf::Color::Green);
			result->ChangeToRegularPolygon(4);
			break;
		}
		default: {
			result->SetColor(sf::Color::Magenta);
			result->ChangeToRegularPolygon(5);
			break;
		}
		}
		return result;
	}
};