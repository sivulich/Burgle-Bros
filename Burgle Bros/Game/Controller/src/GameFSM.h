#pragma once
#pragma once
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30 //or whatever you need                       
#define BOOST_MPL_LIMIT_MAP_SIZE 30 //or whatever you need 

#include <iostream>
// Back-end:
#include <boost/msm/back/state_machine.hpp>
// Front-end:
#include <boost/msm/front/state_machine_def.hpp>
// Functors:
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
#include <boost/msm/front/euml/euml.hpp>

#include <GameModel.h>
#include <GameGraphics.h>
#include <Configs.h>
#include "./GameFSM.h"
#include "./GameState.h"
#include "./events.h"

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;

struct GameFSM_ : public msm::front::state_machine_def<GameFSM_>
{
	// Default constructor
	GameFSM_() { };

	// Constructor which receives a pointer to the model
	GameFSM_(GameModel * m, GameGraphics * g, Timer * t)
	{
		model = m;
		graphics = g;
		guardTimer = t;
	};

	// FSM variables
	GameModel * model;
	GameGraphics * graphics;
	Timer * guardTimer;
	//-------------------------------------------------------------
	template <class EVT, class FSM>
	void on_entry(EVT const&  event, FSM& fsm)
	{
		std::cout << "Welcome to EDA Burgle Bros" << std::endl;

		// Pass pointers to submachine 
		GameState& s = fsm.get_state<GameState&>();
		s.model = fsm.model;
		s.graphics = fsm.graphics;
		s.guardTimer = fsm.guardTimer;
	}

	template <class EVT, class FSM>
	void on_exit(EVT const&  event, FSM& fsm)
	{
		std::cout << "" << std::endl;
	}

	// Flags
	struct gameClosed {};

	struct exitState : public exit_pseudo_state<none> {};

	//----------------------- STATES -----------------------------//

	struct MenuScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Main Menu" << std::endl;
			fsm.graphics->showMenuScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct RulesScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Rules Menu" << std::endl;
			fsm.graphics->showRulesScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct CreditsScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Credits Menu" << std::endl;
			fsm.graphics->showCreditsScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct ModeScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Mode selection" << std::endl;
			fsm.graphics->showModeScreen();
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct LocalSetupScreen : public msm::front::state<>
	{
		bool player1set;
		bool player2set;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "LocalSetup" << std::endl;
			fsm.graphics->showSetupScreen(1);
			player1set = false;
			player2set = false;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	struct RemoteSetupScreen : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Remote setup" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "" << std::endl;
		}
	};

	// -------------------- ORTHOGONAL REGION ------------------
	// Playing state is always active, unless game is paused or there is an error
	struct playing : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Start playing" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Stop playing" << std::endl;
		}

	};

	struct paused : public msm::front::interrupt_state<mpl::vector<ev::resume, ev::close>>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Paused" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Resuming" << std::endl;
		}
	};

	struct error : public msm::front::interrupt_state<ev::errorHandled>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Entering Error" << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving Error" << std::endl;
		}

	};

	struct exit : public msm::front::terminate_state<>
	{
		typedef mpl::vector1<gameClosed> flag_list;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{}

	};


	//----------------------- ACTIONS -----------------------------//

	struct doMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{

		}
	};


	struct setUpCharacter
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
					if (source.player1set == false)
						fsm.model->player1()->setCharacter(event.character);
					else if (source.player2set == false)
						fsm.model->player2()->setCharacter(event.character);
		}
	};

	struct dolocalSetup
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
				if (source.player1set == false && fsm.model->player1()->hasCharacter())
				{
					source.player1set = true;
					fsm.model->player1()->setName(fsm.graphics->getPlayerName());
					fsm.graphics->showSetupScreen(2);
				}
				else if (source.player2set == false && fsm.model->player2()->hasCharacter())
				{
					// If both have the same character
					if (fsm.model->player1()->getCharacter() == fsm.model->player2()->getCharacter())
					{

					}
					else
					{
						source.player2set = true;
						fsm.model->player2()->setName(fsm.graphics->getPlayerName());
						// Both caracters set so go to game
						fsm.process_event(ev::play());
					}
				}
			}
		};


		struct doRender
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
			{
				fsm.graphics->render();
			}

		};

		///////////// GUARDSSSSS

		struct isMoving
		{
			template <class EVT, class FSM, class SourceState, class TargetState>
			bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
			{
				return 	fsm.currentAction == MOVE;
			}
		};

		// Transition table for main FSM
		struct transition_table : mpl::vector<
			//       Start        Event         Next         Action         Guard
			//  +------------+-------------+------------+--------------+--------------+
			Row < MenuScreen, ev::start, ModeScreen, none, none       >,
			Row < MenuScreen, ev::rules, RulesScreen, none, none       >,
			Row < MenuScreen, ev::credits, CreditsScreen, none, none       >,

			Row < ModeScreen, ev::local, LocalSetupScreen, none, none >,
			Row <ModeScreen, ev::remote, RemoteSetupScreen, none, none >,
			Row <ModeScreen, ev::back, MenuScreen, none, none >,

			Row <RulesScreen, ev::back, MenuScreen, none, none >,

			Row <CreditsScreen, ev::back, MenuScreen, none, none >,

			Row < LocalSetupScreen, ev::back, MenuScreen, none, none >,
			Row < LocalSetupScreen, ev::characterName, none, setUpCharacter, none >,
			Row < LocalSetupScreen, ev::next, none, dolocalSetup, none >,
			Row < LocalSetupScreen, ev::play, GameState, none, none >,

			Row <GameState, ev::back, MenuScreen, none, none >,
			//Row <, , , , >,
			//Row <, , , , >,
			//Row <, , , , >,
			//Row <, , , , >,
			//Row <, , , , >,


			
			//--------------------------Orthogonal region-----------------------------//
			//  +------------+-------------+------------+--------------+--------------+
			Row <   playing, ev::close, exit, none, none     >,
			//Row <   playing, ev::errorReceived, error, none, none     >,
			Row <   playing, ev::pause, paused, none, none     >,
			//Row <   playing, ev::render, none, doRender, none     >,

			//  +------------+-------------+------------+--------------+--------------+
			Row <   paused, ev::pause, playing, none, none     >
			/*Row <   paused, ev::close, exit, none, none     >,
			Row <   paused, ev::render, paused, doRender, none     >,
			//  +------------+-------------+------------+--------------+--------------+
			Row <   error, ev::errorHandled, playing, none, none     >,
			Row <   error, ev::close, exit, none, none     >,
			Row <   error, ev::render, none, doRender, none     >
			//  +------------+-------------+------------+--------------+--------------+*/
		> {};

		typedef mpl::vector<playing, GameState> initial_state;

		// Replaces the default no-transition response.
		template <class FSM, class EVT>
		void no_transition(EVT const&  event, FSM& fsm, int state)
		{
			std::cout << "no transition from state " << state << " on event " << typeid(event).name() << std::endl;
		}
	};
	// Pick a back-end
	typedef msm::back::state_machine<GameFSM_> GameFSM;
