#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include<string>
#include "box.h"

class Ball : public GameObject, public Box
{
	
	float size;
	

	Box getBoundingBox() const;

	 graphics::Brush m_brush_ball;

public:
	void update( float dt) override;
	void draw() override;
	void init() override;


	Ball();
	~Ball();


	float m_velocity_x;
	float m_velocity_y;

};