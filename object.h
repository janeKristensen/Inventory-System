#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;





class Object
{
private:
	enum ObjType { T_RED = 0, T_BLUE, T_GREEN, T_YELLOW, T_MAGENTA } type;
	bool picked = false;
	FloatRect newBounds;
	CircleShape m_dot;
	//Object& obj;

	
	
	
public:
	
	Object();
	FloatRect getGlobalBounds();
	Vector2f getPosition();
	void setPosition(Vector2f m_pos);
	void draw(RenderTarget& target);
	void pickUp(Vector2f pos);
	void drop(Vector2f pos);
	bool isPicked();
	bool mouseIntersect(Vector2f mouse);
	int getType();
	bool compareType(Object& b);
	bool compareType(int m_type);

};

