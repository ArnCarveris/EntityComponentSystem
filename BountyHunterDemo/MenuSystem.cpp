///-------------------------------------------------------------------------------------------------
/// File:	MenuSystem.cpp.
///
/// Summary:	Implements the menu system class.
///-------------------------------------------------------------------------------------------------

#include "MenuSystem.h"

#include "Collector.h"
#include "WorldSystem.h"

MenuSystem::MenuSystem()
{
	RegisterEventCallbacks();
}

MenuSystem::~MenuSystem()
{}

void MenuSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&MenuSystem::OnKeyDownEvent);
}

void MenuSystem::OnKeyDownEvent(const KeyDownEvent* event)
{
	switch (event->keyCode)
	{
		// quit game
		case SDLK_ESCAPE:
		case SDLK_q:
			ECS::ECS_Engine->SendEvent<QuitGameEvent>();
			break;

		// pause/resume game
		case SDLK_p:
		{
			static bool s_PAUSED = false;

			if(s_PAUSED == false)
				ECS::ECS_Engine->SendEvent<PauseGameEvent>();
			else
				ECS::ECS_Engine->SendEvent<ResumeGameEvent>();

			s_PAUSED = !s_PAUSED;
			break;
		}

		// toggle fullscreen
		case SDLK_F1:
			ECS::ECS_Engine->SendEvent<ToggleFullscreenEvent>();
			break;

		// cheat: kill all game objects in the world
		case SDLK_F9:
		{
			ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>()->KillAllGameObjects<Collector>();
			break;
		}
	}
}