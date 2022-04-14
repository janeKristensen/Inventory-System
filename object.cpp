#include "object.h"

Object::Object() 
{
	Vector2f startPos = (Vector2f(15, 20) + Vector2f(8 * rand() % 1500, 5 * rand() % 1000));
	m_dot.setRadius(25);
	

	int seed = rand() % 6;
	switch (seed)
	{
	case 1:
		m_dot.setFillColor(Color::Red);
		type = ObjType::T_RED;
		break;
	case 2:
		m_dot.setFillColor(Color::Blue);
		type = ObjType::T_BLUE;
		break;
	case 3:
		m_dot.setFillColor(Color::Green);
		type = ObjType::T_GREEN;
		break;
	case 4:
		m_dot.setFillColor(Color::Yellow);
		type = ObjType::T_YELLOW;
		break;

	default:
		m_dot.setFillColor(Color::Magenta);
		type = ObjType::T_MAGENTA;
		break;
	}

	m_dot.setPosition(startPos);
}


FloatRect Object::getGlobalBounds()
{
	return m_dot.getGlobalBounds();
}

Vector2f Object::getPosition()
{
	return m_dot.getPosition();
}

void Object::setPosition(Vector2f m_pos)
{
	m_dot.setPosition(m_pos);
}

void Object::draw(RenderTarget& target)
{
	target.draw(m_dot);
}

void Object::pickUp(Vector2f pos)
{
	picked = true;
	m_dot.setPosition(pos);
}

void Object::drop(Vector2f pos)
{
	picked = false;
	m_dot.setPosition(pos);
}

bool Object::isPicked()
{
	return picked;
}


bool Object::mouseIntersect(Vector2f mouse)
{
	if (m_dot.getGlobalBounds().contains(mouse))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Object::getType()
{
	return type;
}

bool Object::compareType(Object& b)
{
	if (this->type == b.getType())
	{
		return true;
	}
}

bool Object::compareType(int m_type)
{
	if (this->type == m_type)
	{
		return true;
	}
}

