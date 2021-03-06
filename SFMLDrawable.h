#pragma once
#include "Drawable.h"
//?@?q???????p?{???~???z ?{?|?p???? SFMLDrawable, ???r?|???????y?z???? ???q?v?????{???z ?t?|?? sf::Drawable, ?p ???p?{?w?u ???q?v?????{?y ?????????????? ???????} ?y?x SFML ?{?p?{ ?u?s?? ?~?p???|?u?t?~?y?{?y
namespace Scene { 
	class SFMLDrawable :public Drawable {
	private:
		std::shared_ptr<sf::Drawable> _drawable;
	protected:
		void SetDrawable(std::shared_ptr<sf::Drawable> drawable);
	public:
		SFMLDrawable() {}
		SFMLDrawable(std::shared_ptr<sf::Drawable> drawable);
		virtual void Draw(std::shared_ptr<sf::RenderTarget> renderer, const sf::Transform& transform = sf::Transform(), const sf::Color& color = sf::Color::White) override;
		virtual void SetOrigin(const sf::Vector2f& origin) = 0;
	};
	class SFMLCircle :public SFMLDrawable {
		std::shared_ptr<sf::CircleShape> _circle = std::make_shared<sf::CircleShape>();
	public:
		using Ptr = std::shared_ptr<SFMLCircle>;
		SFMLCircle();
		void SetRadius(float radius);
		void ChangeToRegularPolygon(size_t points);
		void SetColor(const sf::Color& color);
		sf::Color GetColor();
		void SetOrigin(const sf::Vector2f& origin);
		sf::FloatRect GetBounds();
	};
	class SFMLPolygon :public SFMLDrawable {
		std::shared_ptr<sf::ConvexShape> _polygon;
	public:
		void SetPointsNum(size_t number);
		void SetColor(const sf::Color& color);
		sf::Color GetColor();
		sf::FloatRect GetBounds();
		void SetOrigin(const sf::Vector2f& origin);
	};
	class SFMLRectangle :public SFMLDrawable {
		std::shared_ptr<sf::RectangleShape> _rect = std::make_shared<sf::RectangleShape>();
	public:
		SFMLRectangle();
		void SetSize(sf::Vector2f size);
		void SetSize(float width, float height);
		void SetColor(const sf::Color& color);
		sf::Color GetColor();
		void SetOutlineColor(const sf::Color& color);
		void SetOutlineThickness(float thickness);
		sf::FloatRect GetBounds();
		void SetOrigin(const sf::Vector2f& origin);
	};
}