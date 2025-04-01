#include "player.h"
#include<sgg/graphics.h>
#include "gamestate.h"
#include "box.h"


;


void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;

	const float velocity = 10.0f;

	 if (m_name == "Player1") {

		 if (graphics::getKeyState(graphics::SCANCODE_I))
			 m_pos_y -= delta_time * 1.8 * velocity / 2;
		 if (graphics::getKeyState(graphics::SCANCODE_K))
			 m_pos_y += delta_time * 1.8 * velocity / 2;

	}
	
	 else if (m_name == "Player2") {

		if (graphics::getKeyState(graphics::SCANCODE_W))
			m_pos_y -= delta_time * 1.8 *  velocity / 4;
		if (graphics::getKeyState(graphics::SCANCODE_S))
			m_pos_y += delta_time * 1.8 * velocity / 4;
	}
	
	
		m_pos_x = std::max(0.0f, std::min(m_pos_x, m_state->getCanvasWidth() - 0.1f));
		m_pos_y = std::max(0.5f, std::min(m_pos_y, m_state->getCanvasHeight() - 0.5f));



	GameObject::update(dt);
}

void Player::init()


{
	if (m_name == "Player1") {
		m_width = 0.1f;
		m_height = 0.9f;
	
		m_pos_x = m_state->getCanvasWidth() - 0.3f;
		m_pos_y = m_state->getCanvasHeight() / 2.0f;
	}
	else if (m_name == "Player2") {
		m_width = 0.1f;
		m_height = 0.9f;

		m_pos_x =  0.3f;
		m_pos_y = m_state->getCanvasHeight() / 2.0f;
	}

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;


}

void Player::draw()
{
	if (m_name == "Player1") {
		graphics::drawRect(m_pos_x , m_pos_y,m_width, m_height, m_brush_player);
	}

	if (m_name == "Player2") {
		graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_player);
	}
}