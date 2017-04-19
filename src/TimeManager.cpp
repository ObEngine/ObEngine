//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "TimeManager.hpp"

namespace obe
{
	namespace Time
	{
		//FPS Counter
		void FPSCounter::tick()
		{
			if (getTickSinceEpoch() - m_lastTick <= 1000)
				m_fpsCounter++;
		}
		void FPSCounter::uTick()
		{
			if (getTickSinceEpoch() - m_lastTick <= 1000)
				m_updCounter++;
			else
			{
				m_saveUPD = m_updCounter;
				m_updCounter = 0;
				m_lastTick = getTickSinceEpoch();
				m_canUpdateFPS = true;
				m_saveFPS = m_fpsCounter;
				m_fpsCounter = 0;
			}
		}
		void FPSCounter::loadFont(sf::Font &font)
		{
			m_text.setFont(font);
			m_text.setCharacterSize(12);
			m_text.setFillColor(sf::Color::White);
		}
		sf::Text FPSCounter::getFPS()
		{
			if (m_canUpdateFPS)
			{
				m_canUpdateFPS = false;
				m_text.setString(std::to_string(m_saveFPS) + " FPS / " + std::to_string(m_saveUPD) + " UPS");
				return m_text;
			}
			return m_text;
		}

		//Chronometer
		Chronometer::Chronometer()
		{

		}
		void Chronometer::start() {
			m_chronoStart = std::chrono::high_resolution_clock::now();
			m_chronoCurrent = std::chrono::high_resolution_clock::now();
			m_started = true;
		}
		void Chronometer::stop() {
			m_started = false;
		}
		unsigned long long int Chronometer::getTime() {
			if (m_started) m_chronoCurrent = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::milliseconds>(m_chronoCurrent - m_chronoStart).count();
		}
		void Chronometer::setLimit(unsigned long long int limit) {
			this->m_limit = limit;
		}
		bool Chronometer::limitExceeded() {
			std::cout << "Limit : " << m_limit << std::endl;
			std::cout << "Current : " << this->getTime() << std::endl;
			return (this->getTime() > m_limit);
		}

		double getTickSinceEpoch()
		{
			return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
		}

		double getTickSinceEpochMicro()
		{
			return std::chrono::system_clock::now().time_since_epoch() / std::chrono::microseconds(1);
		}
	}
}