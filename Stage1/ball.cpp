#include "ball.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "box.h"

Ball::Ball()
	:  m_velocity_x(2.0f), m_velocity_y(2.0f) {}




void Ball::update(float dt) {
	float delta_time = dt / 1000.0f;

	
	m_pos_x += m_velocity_x * 1.5*delta_time;
	m_pos_y += m_velocity_y * 1.5*delta_time;

	if (m_pos_x >= GameState::getInstance()->getCanvasWidth()) {
	
		m_pos_x = GameState::getInstance()->getCanvasWidth() / 2.0f;
		m_pos_y = GameState::getInstance()->getCanvasHeight() / 2.0f;

		
		
	}
	if (m_pos_x <= 0.0f) {
		m_velocity_x = -m_velocity_x; 
		m_pos_x = 0.1f; 
	}

}
void Ball::draw() {

	graphics::drawDisk(m_pos_x, m_pos_y, m_width/2.0f, m_brush_ball);


}

void Ball::init() {
	
	float ballDiameter = 0.3f; 
	m_width = ballDiameter;
	m_height = ballDiameter;
	m_pos_x = 4.0f; 
	m_pos_y = 4.0f;

	m_brush_ball.fill_opacity = 1.0f;
	m_brush_ball.outline_opacity = 0.0f;
	m_brush_ball.texture = GameState::getInstance()->getFullAssetPath("player.png");

	
}



Ball::~Ball() {

}