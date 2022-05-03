#include "Node.h"

namespace Scene {


	void Node::AddChild(Node::Ptr object) {
		_childrenByZ[object->GetPriority()].insert(object);
		_childrenByName[object->GetName()].insert(object);
		auto shared = shared_from_this();
		if(object->GetParent().lock()!= shared)
			object->SetParent(shared);
	}

	void Node::SetParent(std::weak_ptr<Node> newParent) {
		if (_parent.lock() == newParent.lock()) {
			return;
		}
		if (auto curr_parent = _parent.lock()) {

			if (curr_parent->HasChild(shared_from_this())) {
				curr_parent->RemoveChild(shared_from_this());
			}
		}
		_parent = newParent;
		if (auto parent = newParent.lock()) {
			if (!parent->HasChild(shared_from_this())) {
				parent->AddChild(shared_from_this());
			}
		}
	}

	void Node::RecursiveReset() {
		ResetNode();
		for (auto& children : _childrenByZ) {
			for (auto& child : children.second) {
				child->RecursiveReset();
			}
		}
	}

	bool Node::HasChild(Node::Ptr child) {
		auto sameName = _childrenByName.find(child->GetName());
		if (sameName == _childrenByName.end()) {
			return false;
		}
		return sameName->second.find(child) != sameName->second.end();
	}

	void Node::RemoveChild(Node::Ptr child) {
		auto sameName = _childrenByName.find(child->GetName());
		if (sameName != _childrenByName.end()) {
			sameName->second.erase(child);
			if (sameName->second.empty())
				_childrenByName.erase(child->GetName());
		}
		auto samePriority = _childrenByZ.find(child->GetPriority());
		if (samePriority != _childrenByZ.end()) {
			samePriority->second.erase(child);
			if (samePriority->second.empty()) {
				_childrenByZ.erase(child->GetPriority());
			}
		}
		if (child->GetParent().lock() == shared_from_this()) {
			child->SetParent(std::weak_ptr<Node>());
		}

	}
	void Node::AddBehaviour(ObjectBehaviour::Ptr behaviour) {
		_behaviours[typeid(*behaviour).name()] = behaviour;
		behaviour->LinkToNode(shared_from_this());
	}
	void Node::SetActive(bool active)
	{
		if (active != _active) {
			_active = active;
			if (active) {
				OnActivate();
				_firstUpdate = true;
				for (auto behaviour : _behaviours) {
					behaviour.second->OnActivate();
				}
			}
			else {
				OnDeactivate();
				for (auto behaviour : _behaviours) {
					behaviour.second->OnDeactivate();
				}
			}
		}

	}

	void Node::SetPriority(float priority) {
		if (priority != _priority) {
			if (auto parent = GetParent().lock()) {
				parent->RemoveChild(shared_from_this());
				_priority = priority;
				parent->AddChild(shared_from_this());
			}
			_priority = priority;
		}
	}

	void Node::SetName(const std::string& name) {
		if (_name == name) {
			return;
		}
		auto parent = _parent.lock();
		if (parent) {
			parent->RemoveChild(shared_from_this());
		}
		_name = name;
		if (parent) {
			parent->AddChild(shared_from_this());
		}
	}

	void Node::SetColor(sf::Color color) {
		_color = color;
		OnColorChange();
	}

	void Node::UpdateNode(float dt)
	{
		if (!_active)
			return;
		if (_firstUpdate) {
			_firstUpdate = false;
			OnFirstUpdate();
		}
		for (auto& behaviour : _behaviours) {
			behaviour.second->Update(dt);
		}
		for (auto& children : _childrenByZ) {
			for (auto child : children.second) {
				child->UpdateNode(dt);
			}
		}
		Update(dt);
	}


	void Node::ResetNode() 
	{
		Reset();
		for (auto behaviour : _behaviours) {
			behaviour.second->Reset();
		}
	}
	void Node::DrawNode(std::shared_ptr<sf::RenderTarget> renderer, const sf::Transform& transform, const sf::Color& color)
	{
		if (!_active) {
			return;
		}
		auto targetColor = color * GetColor();
		auto combinedTransform = transform * getTransform();
		if (_drawable) {
			_drawable->Draw(renderer, combinedTransform, color);
		}
		Draw(renderer, transform, targetColor * _color);
		for (auto& children : _childrenByZ) {
			for (auto& child : children.second) {
				child->DrawNode(renderer, combinedTransform, targetColor);
			}
		}
	}
	sf::Transform Node::GetGlobalTransform() {
		if (auto parent = GetParent().lock()) {
			return getTransform() * parent->GetGlobalTransform();
		}
		else {
			return getTransform();
		}
	}
	sf::Vector2f Node::GetGlobalPosition() {
		if (auto parent = GetParent().lock()) {
			return parent->GetGlobalTransform() * getPosition();
		}
		else {
			return getPosition();
		}
	}
	Node::Ptr Node::GetChildByNameDirect(std::string name) {
		if (_childrenByName.find(name) != _childrenByName.end()) {
			return *_childrenByName.at(name).begin();
		}
		else return Node::Ptr();
	}
	Node::Ptr Node::FindChildByName(std::string name) {
		if (auto found = GetChildByNameDirect(name))
		{
			return found;
		}
		for (auto children : _childrenByName) {
			for (auto child : children.second) {
				if (auto found = child->FindChildByName(name)) {
					return found;
				}
			}
		}
		return Node::Ptr();
	}
}
