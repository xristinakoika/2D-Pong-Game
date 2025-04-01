#include "gamestate.h"
#include "level.h"
#include"player.h"
#include "ball.h"
#include "box.h"
#include "util.h"

   

GameState::GameState()
{
}

// Elegxos gia sygkrouseis metaksy mpalas kai paiktwn, kai toixwn.
void GameState::checkCollisions() {
	if (!m_ball || !m_player1 || !m_player2)
		return;

	float canvasWidth = getCanvasWidth();
	float canvasHeight = getCanvasHeight();

	// Pano kai kato toixos - an h mpala xtypisei, antistrefoume thn katheti taxythta.
	if (m_ball->m_pos_y - m_ball->m_height / 2.0f <= 0.0f ||
		m_ball->m_pos_y + m_ball->m_height / 2.0f >= canvasHeight) {
		m_ball->m_velocity_y = -m_ball->m_velocity_y;
	}

	// Elegxos sygkroushs mpalas me ton Player1.
	Box player1Box(m_player1->m_pos_x, m_player1->m_pos_y, m_player1->m_width, m_player1->m_height);
	Box ballBox(m_ball->m_pos_x, m_ball->m_pos_y, m_ball->m_width, m_ball->m_height);

	if (player1Box.intersect(ballBox)) {

		m_ball->m_velocity_x = -m_ball->m_velocity_x;


		float offset = player1Box.intersectSideways(ballBox);
		m_ball->m_pos_x += offset + 0.02f;
	}

	// Elegxos sygkroushs mpalas me ton Player2.
		Box player2Box(m_player2->m_pos_x, m_player2->m_pos_y, m_player2->m_width, m_player2->m_height);
		if (player2Box.intersect(ballBox)) {

			m_ball->m_velocity_x = -m_ball->m_velocity_x;

			float offset = player2Box.intersectSideways(ballBox);
			m_ball->m_pos_x += offset + 0.02f;

		}
		// Elegxos an h mpala ftanei aristera (gkol gia ton Player2).
		if (m_ball->m_pos_x - m_ball->m_width / 2.0f <= 0.0f) {

			player2_score++;
			resetBall();

			if (player2_score == 5) {
				status = STATUS_WIN;
			}
		}
		// Elegxos an h mpala ftanei deksia (gkol gia ton Player1).
		else if (m_ball->m_pos_x + m_ball->m_width / 2.0f >= canvasWidth) {

			player1_score++;
			resetBall();

			if (player1_score == 5) {
				status = STATUS_WIN;
			}
		}
	}
//  reset ths mpalas sto kentro tou ghpedou.
	void GameState::resetBall() {
	
		m_ball->m_pos_x = getCanvasWidth() / 2.0f;
		m_ball->m_pos_y = getCanvasHeight() / 2.0f;
		m_ball->m_velocity_x = 3.0f;
		m_ball->m_velocity_y = 2.0f;
		
		
	
}

void GameState::init()
{ 
	m_brush_background_start.outline_opacity = 0.0f;
	m_brush_background_start.texture = getFullAssetPath("background.png");

	std::string fontPath = getFullAssetPath("orangejuice.ttf");
	printf("Font Path: %s\n", fontPath.c_str());
	graphics::setFont(fontPath);

		m_current_level = new Level();
		m_current_level->init();

		m_player1 = new Player("Player1");
		m_player1->init();

		m_player2 = new Player("Player2");
		m_player2->init();
		

		m_ball = new Ball();
		m_ball->init();

	
	
		player1_score = 0;
		player2_score = 0;
	

	graphics::preloadBitmaps(getAssetDir());
	
}

void GameState::draw()
{

	float w = getCanvasWidth();
	float h = getCanvasHeight();

	
	if (status == STATUS_START) {
		
		graphics::drawRect(w / 2, h / 2, w, h, m_brush_background_start);

		graphics::Brush brushText;
		SETCOLOR(brushText.fill_color, 1.0f, 1.0f, 1.0f); 
		brushText.fill_opacity = 1.0f;
		brushText.outline_opacity = 0.0f;

		char info[40];
		sprintf_s(info, "Press Enter to Start");

		graphics::drawText(m_canvas_width / 4.3 , m_canvas_height / 2 , 0.5, info, brushText);
	}
	else if (status == STATUS_PLAYING) {


		m_current_level->draw();
		

		if (m_ball)
			m_ball->draw();

		if (m_player1)
			m_player1->draw();

		if (m_player2)
			m_player2->draw();

		graphics::Brush brushText;
		SETCOLOR(brushText.fill_color, 1.0f, 1.0f, 1.0f); 
		brushText.fill_opacity = 1.0f;
		brushText.outline_opacity = 0.0f;

		char info[40];
		sprintf_s(info, "  score");

		graphics::drawText(m_canvas_width / 2.5, m_canvas_height/11, 0.4, info, brushText);
	

		
		char scoreText[100];
		sprintf_s(scoreText, " Player1: % d                                   Player2: % d", player1_score, player2_score);
		graphics::drawText(m_canvas_width / 8.8, m_canvas_height/6 , 0.4, scoreText, brushText);
	}

	else if(status==STATUS_WIN){
		graphics::drawRect(w / 2, h / 2, w, h, m_brush_background_start);

		graphics::Brush brushText;
		SETCOLOR(brushText.fill_color, 1.0f, 1.0f, 1.0f);
		brushText.fill_opacity = 1.0f;
		brushText.outline_opacity = 0.0f;

		char info[40];
		sprintf_s(info, "Game over. Press 's' to continue");

		graphics::drawText(m_canvas_width / 6, m_canvas_height / 2, 0.4, info, brushText);


		char winnerInfo[50];
		if (player1_score > player2_score) {
			sprintf_s(winnerInfo, "Winner is  % s ", m_player1->getName().c_str());
		}
		else {
			sprintf_s(winnerInfo, "Winner is %s ", m_player2->getName().c_str());
		}
		graphics::drawText(m_canvas_width / 4.3, m_canvas_height / 1.5, 0.5, winnerInfo, brushText);

	}
	
}

void GameState::update(float dt)
{
	

	if (status == STATUS_START) {
		
		// An o xrhsths patisei Space, arxizei to paixnidi.
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			status = STATUS_PLAYING;
		}
	}
	else if (status == STATUS_PLAYING) {

		if (dt > 500)
			return;

		if (!m_current_level)
			return;


		m_current_level->update(dt);

		if (m_ball)
			m_ball->update(dt);

		if (m_player1)
			m_player1->update(dt);

		if (m_player2)
			m_player2->update(dt);


		checkCollisions();

	}
	// Epanafora me to 's' meta to telos.
	else if (status == STATUS_WIN) {
		if (graphics::getKeyState(graphics::SCANCODE_S)) {
			status = STATUS_START;
			player1_score = 0;
			player2_score = 0;
			m_player1->init();
			m_player2->init();
			
		}
	}
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();

	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_player1)
		delete m_player1;
	if (m_current_level)
		delete m_current_level;
}



std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState:: getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}



GameState* GameState::m_unique_instance = nullptr;