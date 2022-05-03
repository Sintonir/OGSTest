#include "Caption.h"

Scene::Caption::Caption() {
	SetDrawable(_text);
}

void Scene::Caption::SetText(const std::string& text) {
	_text->setString(text);
}

void Scene::Caption::SetFont(std::shared_ptr<sf::Font> font) {
	_font = font;
	_text->setFont(*_font);
}

void Scene::Caption::SetColor(const sf::Color& color) {
	_text->setFillColor(color);
}

sf::Color Scene::Caption::GetColor() {
	return _text->getFillColor();
}

sf::FloatRect Scene::Caption::GetBounds() {
	return _text->getLocalBounds();
}

void Scene::Caption::SetOutlineColor(const sf::Color& color)
{
	_text->setOutlineColor(color);
}

void Scene::Caption::SetOutlineThickness(float thickness) {
	_text->setOutlineThickness(thickness);
}

void Scene::Caption::SetOrigin(const sf::Vector2f& origin)
{
	_text->setOrigin(origin);
}
