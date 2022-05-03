#pragma once
#include<SFML/Graphics.hpp>
#include "ObjectBehaviour.h"
#include "Drawable.h"
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
namespace Scene {
	//„P„€„x„r„€„|„‘„u„„ „ƒ„„„‚„€„y„„„ „y„u„‚„p„‚„‡„y„ „€„q„Œ„u„{„„„€„r, „p „„„p„{„w„u „{„€„~„„„‚„€„|„y„‚„€„r„p„„„ „y„‡ „„€„r„u„t„u„~„y„u „ƒ „„€„}„€„‹„„ „~„p„q„€„‚„p ObjectBehaviour
	//„M„€„w„~„€ „ƒ„€„x„t„p„„„ „~„p„ƒ„|„u„t„~„y„{„€„r, „{„€„„„€„‚„„u „q„…„t„…„„ „‚„u„p„|„y„x„€„r„„r„p„„„ „x„p„‹„y„‹„v„~„~„„u „†„…„~„{„ˆ„y„y, „~„p „„‚„p„{„„„y„{„u „r„ƒ„u „†„…„~„{„ˆ„y„y „{„‚„€„}„u Draw „„‚„€„‹„u „‚„u„p„|„y„x„€„r„p„„„ „r Behaviour.
	class Node :
		public sf::Transformable, public std::enable_shared_from_this<Node>
	{
	public:using Ptr = std::shared_ptr<Node>;
	private:
		std::map<float, std::unordered_set<Node::Ptr>> _childrenByZ;
		std::unordered_map<std::string, std::unordered_set<Node::Ptr>> _childrenByName;
		std::weak_ptr<Node> _parent;
		//„B „{„p„‰„u„ƒ„„„r„u „{„|„„‰„p „y„ƒ„„€„|„„x„…„u„„„ƒ„‘ „‚„u„p„|„„~„„z „„„y„ „q„u„‡„u„z„r„y„€„‚„p, „„„p„{„y„} „€„q„‚„p„x„€„} „~„u „}„€„w„u„„ „q„„„„ „q„€„|„u„u „€„t„~„€„s„€ „q„u„‡„u„z„r„y„€„‚„p „„„€„s„€ „w„u „„„y„„p.
		std::unordered_map<std::string, ObjectBehaviour::Ptr> _behaviours;
		bool _active = true;
		bool _firstUpdate = true;
		std::string _name;
		float _priority = 0;
		sf::Color _color = sf::Color::White;
		std::shared_ptr<Drawable> _drawable;
	protected:
		virtual void OnActivate() {}
		virtual void OnDeactivate() {}
		virtual void Update(float dt) {}
		virtual void OnFirstUpdate() {}
		virtual void Reset() {}
		virtual void OnColorChange() {}
		virtual void Draw(std::shared_ptr<sf::RenderTarget> renderer, const sf::Transform& transform = sf::Transform(), const sf::Color& color = sf::Color::White) {}
	public:
		void AddChild(Node::Ptr object);
		std::weak_ptr<Node> GetParent() {
			return _parent;
		}
		void SetParent(std::weak_ptr<Node> newParent);
		void RecursiveReset();
		bool HasChild(Node::Ptr child);
		void RemoveChild(Node::Ptr child);
		void RemoveAllChildren() {
			_childrenByName.clear();
			_childrenByZ.clear();
		}
		void AddBehaviour(ObjectBehaviour::Ptr behaviour);
		void RemoveBehaviour(std::string name) {
			_behaviours.erase(name);
		}
		template<typename T>
		std::shared_ptr<T> GetBehaviour() {
			auto behaviourName = typeid(T).name();
			if (_behaviours.find(behaviourName) != _behaviours.end())
				return std::dynamic_pointer_cast<T>(_behaviours.at(behaviourName));
			return std::shared_ptr<T>();
		}
		void SetActive(bool active);
		bool IsActive() {
			return _active;
		}
		void SetPriority(float priority);
		float GetPriority() {
			return _priority;
		}
		void SetName(const std::string& name);
		std::string GetName() {
			return _name;
		}
		void SetColor(sf::Color color);
		sf::Color GetColor() {
			return _color;
		}
		void UpdateNode(float dt);
		void ResetNode();
		void DrawNode(std::shared_ptr<sf::RenderTarget> renderer, const sf::Transform& transform = sf::Transform(), const sf::Color& color = sf::Color::White);
		void SetDrawable(std::shared_ptr<Drawable> drawable) {
			_drawable = drawable;
		}
		std::shared_ptr<Drawable>GetDrawable() {
			return _drawable;
		}
		sf::Transform GetGlobalTransform();
		sf::Vector2f GetGlobalPosition();
		Node::Ptr GetChildByNameDirect(std::string name);
		Node::Ptr FindChildByName(std::string name);
	};

}