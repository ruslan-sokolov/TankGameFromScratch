#include <Framework2D.h>

namespace Game {

	class GameInitializer : public Framework2D::Initializer
	{
	public:
		GameInitializer() 
		{

		}

		~GameInitializer()
		{

		}
		
		void Init() override
		{
			Initializer::Init();
			GAME_LOG(LOG_WARN, "GameInitializer Init()");
		}
	};

}

Framework2D::Initializer* Framework2D::CreateInitializer()
{
	return new Game::GameInitializer();
}