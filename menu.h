#pragma once

class menu
{
public:
	static menu* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new menu(); }
	void PlayGame();
	void CreditsGame();
	void StartGame();

	void update();

	bool getStart() { return m_isStart; }
	bool getCredits() { return m_isCredits; }
	bool getPlay() { return m_isPlay; }
	bool getMenu() { return m_isMenu; }

	void setMenu(bool ok) { m_isMenu = ok;}
private:
	menu() : m_isCredits(0), m_isStart(0), m_isPlay(0), m_isMenu(0) {};
	bool m_isCredits, m_isPlay, m_isStart, m_isMenu;

	static menu* s_Instance;
};