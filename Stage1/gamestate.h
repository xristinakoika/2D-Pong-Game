#pragma once
#include <string>
#include <sgg/graphics.h>
#include "ball.h"




class GameState 
{
private:
	Ball* m_ball = nullptr;
	std::string m_asset_path = "assets\\";

	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_WIN } status_t;
	status_t status = STATUS_START;

	

	int player1_score;
	int player2_score;

	float m_canvas_width = 8.0f;
	float m_canvas_height = 8.0f;

	graphics::Brush m_brush_background_start;
	

	static GameState* m_unique_instance;
	void resetBall();

	

	void checkCollisions();

	graphics::Brush m_brush_background1;
	

	GameState();

	class Player* m_player1 = 0;
	class Player* m_player2 = 0;


	
	class Level* m_current_level = 0;

public:
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	bool m_debugging = false;

	
	void init();
	void draw();
	void update(float dt);

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	class Player* getPlayer()
	{
		return m_player1 , m_player2;
	}

	class Ball* getBall()
	{
		return m_ball;
	}
};
