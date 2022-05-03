#include "SFMLDrawable.h"

void Scene::SFMLDrawable::SetDrawable(std::shared_ptr<sf::Drawable> drawable) {
	_drawable = drawable;
}

Scene::SFMLDrawable::SFMLDrawable(std::shared_ptr<sf::Drawable> drawable) :_drawable(drawable) {}

void Scene::SFMLDrawable::Draw(std::shared_ptr<sf::RenderTarget> renderer, const sf::Transform& transform, const sf::Color& color) {
	auto currentColor = GetColor();
	auto targetColor = color * currentColor;
	SetColor(targetColor);
	if (_drawable)
		renderer->draw(*_drawable, transform);
	SetColor(currentColor);
}

void Scene::SFMLPolygon::SetPointsNum(size_t number) {
	if (!_polygon) {
		_polygon = std::make_shared<sf::ConvexShape>(number);
	}
	else
		_polygon->setPointCount(number);
	SetDrawable(_polygon);
}

void Scene::SFMLPolygon::SetColor(const sf::Color& color) {
	_polygon->setFillColor(color);
}

sf::Color Scene::SFMLPolygon::GetColor() {
	return _polygon->getFillColor();
}

sf::FloatRect Scene::SFMLPolygon::GetBounds() {
	return _polygon->getLocalBounds();
}

void Scene::SFMLPolygon::SetOrigin(const sf::Vector2f& origin)
{
	_polygon->setOrigin(origin);
}

Scene::SFMLRectangle::SFMLRectangle() {
	SetDrawable(_rect);
}

void Scene::SFMLRectangle::SetSize(sf::Vector2f size) {
	_rect->setSize(size);
}
void Scene::SFMLRectangle::SetSize(float width, float height) {
	_rect->setSize(sf::Vector2f(width,height));
}

void Scene::SFMLRectangle::SetColor(const sf::Color& color) {
	_rect->setFillColor(color);
}

sf::Color Scene::SFMLRectangle::GetColor() {
	return _rect->getFillColor();
}

void Scene::SFMLRectangle::SetOutlineColor(const sf::Color& color) {
	_rect->setOutlineColor(color);
}

void Scene::SFMLRectangle::SetOutlineThickness(float thickness) {
	_rect->setOutlineThickness(thickness);
}

sf::FloatRect Scene::SFMLRectangle::GetBounds() {
	return _rect->getLocalBounds();
}

void Scene::SFMLRectangle::SetOrigin(const sf::Vector2f& origin)
{
	_rect->setOrigin(origin);
}

Scene::SFMLCircle::SFMLCircle() {
	SetDrawable(_circle);
}

void Scene::SFMLCircle::SetRadius(float radius) {
	_circle->setRadius(50);
	SetDrawable(_circle);
}

void Scene::SFMLCircle::ChangeToRegularPolygon(size_t points) {
	if (_circle)
		_circle->setPointCount(points);
}

void Scene::SFMLCircle::SetColor(const sf::Color& color) {
	_circle->setFillColor(color);
}

sf::Color Scene::SFMLCircle::GetColor() {
	return _circle->getFillColor();
}

void Scene::SFMLCircle::SetOrigin(const sf::Vector2f& origin) {
	_circle->setOrigin(origin);
}

sf::FloatRect Scene::SFMLCircle::GetBounds() {
	return _circle->getLocalBounds();
}
