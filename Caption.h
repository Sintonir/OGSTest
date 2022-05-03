#pragma once
#include "SFMLDrawable.h"
namespace Scene {
	class Caption :
		public SFMLDrawable
	{
		std::shared_ptr<sf::Text> _text = std::make_shared<sf::Text>();
		std::shared_ptr<sf::Font> _font;
	public:
		Caption();
		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<sf::Font> font);
		void SetColor(const sf::Color& color);
		sf::Color GetColor();
		sf::FloatRect GetBounds();
		void SetOutlineColor(const sf::Color& color);
		void SetOutlineThickness(float thickness);
		void SetOrigin(const sf::Vector2f& origin);
	};

}
