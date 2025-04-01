#include"level.h"
#include "gamestate.h"
#include"player.h"
#include "ball.h"
#include "util.h"




void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	GameObject::update(dt);
}

void Level::init()
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background.png");
	

		for (auto p_gob : m_static_objects)
			if (p_gob) p_gob->init();

		for (auto p_gob : m_dynamic_objects)
			if (p_gob) p_gob->init();

		
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = w / 2.0f;
	float offset_y = h / 2.0f;



	//draw background
	graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);



	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();


	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->draw();

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->draw();



}

Level::Level(const std::string name)
{
}

Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;
}
