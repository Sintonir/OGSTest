#pragma once
#include"SFML/Graphics.hpp"
#include <iostream>
namespace Scene {
	//sf::Drawable „~„u „t„p„v„„ „y„~„„„u„‚„†„u„z„ƒ„p „t„|„‘ „~„u„{„€„„„€„‚„„‡ „~„u„€„q„‡„€„t„y„}„„‡ „}„~„u „t„u„z„ƒ„„„r„y„z, „„€„„„„€„}„… „‘ „ƒ„€„x„t„p„| „y„~„„„u„‚„†„u„z„ƒ, „r„{„|„„‰„p„„‹„y„z „y„‡ „r „ƒ„u„q„‘.
	class Drawable :public std::enable_shared_from_this<Drawable>
	{
	public:
		using Ptr = std::shared_ptr<Drawable>;
		virtual void Draw(std::shared_ptr<sf::RenderTarget> renderer, const sf::Transform& transform = sf::Transform(), const sf::Color& color = sf::Color::White) = 0;
		virtual void SetColor(const sf::Color& color) = 0;
		virtual sf::FloatRect GetBounds() = 0;
		virtual sf::Color GetColor() = 0;
	};


}