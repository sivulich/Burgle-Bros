#pragma once
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 50 //or whatever you need                       
#define BOOST_MPL_LIMIT_MAP_SIZE 50 //or whatever you need 
#define FUSION_MAX_VECTOR_SIZE 20

#include <iostream>
// Back-end:
#include <boost/msm/back/state_machine.hpp>
// Front-end:
#include <boost/msm/front/state_machine_def.hpp>
// Functors:
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
#include <boost/msm/front/euml/euml.hpp>
//FOR and operator  And_<>
#include <boost/msm/front/euml/operator.hpp>


#include <GameModel.h>
#include <GameGraphics.h>
#include <BurgleNetwork.h>
#include <Configs.h>
#include "./events.h"
#include "../../Sound/SoundEffects.h"
namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;
using namespace euml;

struct GameState_ : public msm::front::state_machine_def<GameState_>
{
	// INICIALIZAR PUNTEROS!
	// FSM variables
	GameModel * model;
	GameGraphics * graphics;
	SoundEffects * sound;
	BurgleNetwork * network;
	int gameMode;
	Timer * guardTimer;
	// Stores current action chosen by player
	action_ID currentAction;

	//-------------------------------------------------------------
	template <class EVT, class FSM>
	void on_entry(EVT const&  event, FSM& fsm)
	{
		std::cout << "Entering Burgle Bros Finite State Machine" << std::endl;

		if (fsm.model->isLocal())
		{
			fsm.model->setBoard();
			fsm.graphics->showOkMessage("Choose initial position!");
			fsm.graphics->showGameScreen();
		}
		else if (fsm.model->isRemote())
		{
			if (fsm.network->isServer())
				fsm.model->setBoard();

			fsm.graphics->showOkMessage("Exchanging info with other player");
			// Cord will be random in next state

		}
		fsm.sound->playBackroundMusic();

	}

	template <class EVT, class FSM>
	void on_exit(EVT const&  event, FSM& fsm)
	{
		std::cout << "Leaving Burgle Bros" << std::endl;
		fsm.graphics->deleteGameScreen();
	}

	//----------------------- STATES -----------------------------//


	struct chooseInitialPos : public msm::front::state<>
	{

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{

			if (fsm.model->isLocal())
			{
				// Set only first floor clickable
				std::cout << "Choose initial pos: ";
				vector<Coord> v;
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						v.push_back(Coord(0, i, j));
				fsm.graphics->setTilesClickable(v);
			}
			else if (fsm.model->isRemote())
			{
				string name = fsm.model->player1()->getName();
				characterType character = fsm.model->player1()->getCharacter();
				Coord initialPos = Coord(0, 2, 0);// random initialpos
				cout << "My name " << name << " My character " << character << endl;
				if (fsm.network->isServer())
				{
					
					pair<Coord, Coord> pos = fsm.model->getInitialGuardPos();
					vector<tileType> tiles = fsm.model->getBoardSetup();
					while (fsm.network->error()==false && fsm.network->startupPhase(name, character, pos.first, pos.second, tiles, initialPos) == false);
					if (fsm.network->error() == true)
						cout << fsm.network->errMessage() << endl;
				}
				else
				{
					while (fsm.network->startupPhase(name, character) == false);

					cout << string("YA TENGO TODO SUPUESTAMENTE") << endl;
					fsm.model->setBoard(fsm.network->remoteBoard());
					/* QUEDA SETEAR ESTO
					Coord fsm.network->remoteGuardPos()
					Coord fsm.network->remoteGuardTarget()
					Coord fsm.network->startingPos() */
				}

				// Set other player name
				fsm.model->player2()->setName(fsm.network->remoteName());
				fsm.model->player2()->setCharacter(fsm.network->remoteCharacter());

				if (fsm.network->iStart() == false)
					fsm.model->remotePlayerStarts();
				fsm.graphics->showGameScreen();

				if (fsm.network->isServer())
					fsm.model->setInitialPosition(initialPos);
				else
					fsm.model->setInitialPosition(fsm.network->startingPos());
				fsm.process_event(ev::coord(initialPos));
			}

		}


		template <class EVT, class FSM>
		typename boost::enable_if<typename has_CoordProp<EVT>::type, void>::type
			on_exit(EVT const&  event, FSM& fsm)
		{
			// Set again all tiles clickable
			fsm.graphics->setAllClickable();
		}

		template <class EVT, class FSM>
		typename boost::disable_if<typename has_CoordProp<EVT>::type, void>::type
			on_exit(EVT const&  event, FSM& fsm)
		{}
	};


	struct chooseAction : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Choose action: ";
			fsm.graphics->printInHud(string("Choose an action"));
			vector<string> v = fsm.model->currentPlayer()->gettActions();
			for (auto& s : v)
				std::cout << s << " ";
			std::cout << std::endl;
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			// Set all tiles clickable
			fsm.graphics->setAllClickable();
		}
	};

	struct chooseLoot : public msm::front::state<>
	{
		lootType chosenLoot;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{

		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			// Desmarcar las tiles 
			fsm.graphics->setAllClickable();
		}
	};

	struct checkActionTokens : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{

			if (fsm.model->gameOver() == true)
				fsm.process_event(ev::gameOver());

			if (fsm.model->currentPlayer()->getActionTokens() == 0 || fsm.model->currentPlayer()->isOnRoof())
			{
				fsm.process_event(ev::no());
				std::cout << "Your turn ends" << std::endl;
			}
			else
			{
				fsm.process_event(ev::yes());
				std::cout << "Action tokens left: " << fsm.model->currentPlayer()->getActionTokens() << std::endl;
			}

		}
	};

	struct askConfirmation : public msm::front::state<>
	{
		lootType lootToOffer;

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Are you sure? Yes/No" << std::endl;
		}

	};

	struct askConfirmationMove : public msm::front::state<>
	{
		Coord destinationCoord;
		tileType destinationType;

		template <class EVT, class FSM>
		typename boost::enable_if<typename has_CoordProp<EVT>::type, void>::type
			on_entry(EVT const&  event, FSM& fsm)
		{
			cout << "Entering ask confirmation" << endl;
			destinationCoord = event.c;

			if (destinationCoord != ROOF)
			{
				Tile * tile = fsm.model->getBoard()->getTile(event.c);
				destinationType = tile->getType();

				confirmation conf = fsm.model->currentPlayer()->needConfirmationToMove(event.c);
				if (tile->is(DEADBOLT))
				{
					if (conf == _ASK)
						fsm.graphics->askQuestion(string("To move to the deadbolt you must spend 3 action tokens. Are you sure?"));
					else if (conf == _CANT_MOVE)
					{
						fsm.graphics->showOkMessage(string("You cant move to the deadbolt! You don't have enough action tokens."));
						fsm.process_event(ev::no());
					}
				}
				else if (tile->is(LASER))
					fsm.graphics->askQuestion(string("Do you want to spend 1 extra action token to enter the laser room? If not you trigger an alarm."));
				else if (tile->is(KEYPAD) && conf == _DICE)
				{
					if (fsm.model->currentPlayer()->isLocal())
						fsm.process_event(ev::throwDice());
				}
			}
		}

		template <class EVT, class FSM>
		typename boost::disable_if<typename has_CoordProp<EVT>::type, void>::type
			on_entry(EVT const&  event, FSM& fsm) {};


		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			if (is_same<EVT, ev::yes>::value)
			{
				cout << "Passing coord" << endl;
				fsm.process_event(ev::coord(destinationCoord));
			}
		}

	};

	struct beginTurn : public msm::front::state<>
	{

		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			std::cout << "Starting Turn" << std::endl;
			fsm.currentAction = NO_TYPE;
			fsm.graphics->printInHud(fsm.model->currentPlayer()->getName() + string("'s turn."));

			if (fsm.model->currentPlayer()->has(PERSIAN_KITTY) || fsm.model->currentPlayer()->has(CHIHUAHUA))
			{
				if (fsm.model->currentPlayer()->isLocal())
				{
					fsm.process_event(ev::throwDice(fsm.model->currentPlayer()->throwDice()));
				}
				//else is remote
			}
			else fsm.process_event(ev::done());

		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			fsm.currentAction = NO_TYPE;
			std::cout << "" << std::endl;
		}
	};

	struct guardTurn : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			if (fsm.model->currentPlayer()->isOnRoof())
				fsm.process_event(ev::passGuard());
			else
			{
				std::cout << "Its the guards turn" << std::endl;
				fsm.guardTimer->start();
			}
		}

		template <class EVT, class FSM>
		void on_exit(EVT const&  event, FSM& fsm)
		{
			std::cout << "Leaving guard turn" << std::endl;
			fsm.guardTimer->stop();
		}

	};

	struct gameEnded : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			if (typeid(EVT) == typeid(ev::burglarsWin))
				fsm.graphics->showOkMessage(string("You win!"));
			else if (typeid(EVT) == typeid(ev::gameOver))
				fsm.graphics->showOkMessage(string("You lose!"));

		}
	};

	struct idle : public msm::front::state<>
	{
		template <class EVT, class FSM>
		void on_entry(EVT const&  event, FSM& fsm)
		{
			cout << "IDLE..." << endl;

		}
	};

	struct waitingForNetwork : public msm::front::state<>
	{};

	//----------------------- ACTIONS -----------------------------//

	struct doSetInitialPos
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Setting initial position to  " << event.c << std::endl;
			fsm.model->setInitialPosition(event.c);
		}
	};


	struct doMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{

			std::cout << "Moving to " << event.c.toString() << std::endl;
			fsm.graphics->printInHud(string("Moving to ") + event.c.toString());

			unsigned int safeNumber = fsm.model->currentPlayer()->move(event.c, event.safeNumber);

			// If other player is remote send move
			if (fsm.model->otherPlayer()->isRemote())
			{
				fsm.network->sendMove(event.c, safeNumber);
				fsm.process_event(ev::waitForNetwork());
			}


			// If coming from ask confirmation state, the player agreed to spent tokens
			if (is_same<SourceState, askConfirmationMove>::value)
				fsm.model->currentPlayer()->spentOK();


			if (fsm.model->currentPlayer()->getCharacter() != ACROBAT)
				fsm.model->getBoard()->checkOnePlayer(fsm.model->currentPlayer(), fsm.model->currentPlayer()->getPosition().floor);

			fsm.model->check4Cameras();
			// HACER UNA FUNCION POSITION GUARD DEL MODELO
			//fsm.model->getBoard()->getFloor(fsm.model->currentPlayer()->getPosition().floor)->getGuard()->positionGuard();
			fsm.model->positionGuard();
			//COMENTO PARA PROBAR EL ROOF fsm.model->currentPlayer()->gettActions();
			fsm.currentAction = NO_TYPE;
		}
	};

	struct dontMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			tileType destTile = fsm.model->getBoard()->getTile(source.destinationCoord)->getType();
			if (destTile == DEADBOLT || destTile == KEYPAD)
				fsm.model->currentPlayer()->removeActionToken();
			else fsm.model->currentPlayer()->move(source.destinationCoord);
		}
	};

	struct doPeek
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Peeking " << event.c.toString() << std::endl;
			fsm.graphics->printInHud(string("Peeking ") + event.c.toString());

			unsigned int safeNumber = fsm.model->currentPlayer()->peek(event.c, event.safeNumber);

			// If other player is remote send peek
			if (fsm.model->otherPlayer()->isRemote())
			{
				fsm.network->sendPeek(event.c, safeNumber);
				fsm.process_event(ev::waitForNetwork());
			}

			fsm.currentAction = NO_TYPE;
		}
	};

	struct doUseToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.model->currentPlayer()->useToken();

		}
	};

	struct doAddToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Adding token" << std::endl;
			fsm.model->currentPlayer()->addToken();
			fsm.currentAction = NO_TYPE;
		}
	};

	struct dontAddToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{

			fsm.currentAction = NO_TYPE;
		}
	};

	struct doThrowDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Throwing dice" << std::endl;
			//fsm.model->currentPlayer()->throwDice();
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doCrackSafe
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			Tile * currTile = fsm.model->getBoard()->getTile(fsm.model->currentPlayer()->getPosition());
			bool b = false;
			if (fsm.model->currentPlayer()->isLocal())
			{
				vector<int> dices;
				while (true)
				{
					int dice = fsm.model->currentPlayer()->throwDice();
					dices.push_back(dice);
					if (fsm.model->currentPlayer()->throwDice(dice))// Cant throw more dices or keypad crackes
					{
						fsm.graphics->showDices(string("You threw this dices."), dices);
						break;
					}
				}
			}
		}
	};

	struct dontThrowDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Throwing dice" << std::endl;
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doOpenKeypad
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Trying to open Keypad" << std::endl;
			Tile * destTile = fsm.model->getBoard()->getTile(source.destinationCoord);
			if (fsm.model->currentPlayer()->isLocal())
			{
				vector<int> dices;
				while (true)
				{
					int dice = fsm.model->currentPlayer()->throwDice();
					dices.push_back(dice);
					if (((Keypad *)destTile)->tryToOpen(dice, fsm.model->currentPlayer()) == true)// Cant throw more dices or keypad crackes
					{
						if (destTile->canMove(fsm.model->currentPlayer())) //Keypad decodes
						{
							fsm.graphics->showDices(string("You threw a 6 and decoded the keypad! Now you can enter freely."), dices);
							fsm.process_event(ev::yes());
						}
						else
						{
							fsm.graphics->showDices(string("You couldn't decode the keypad!"), dices);
							fsm.process_event(ev::no());
						}
						break;
					}
				}
			}
		}
	};

	struct doCreateAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Creating Alarm" << std::endl;
			bool b = fsm.model->currentPlayer()->createAlarm(event.c);
			if (b == false)
				std::cout << "Cant create Alarm!" << std::endl;
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doSpyPatrol
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Spying patrol deck" << std::endl;
			fsm.model->spyPatrol(fsm.model->currentPlayer()->getPosition().floor);
			fsm.graphics->spyPatrolCard(fsm.model->currentPlayer()->getPosition().floor);
			fsm.currentAction = SPY_PATROL;
		}
	};

	struct doStayTop
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Card staying on top of deck" << std::endl;
			fsm.model->stopSpying(fsm.model->currentPlayer()->getPosition().floor);
			fsm.graphics->hideTopPatrol(fsm.model->currentPlayer()->getPosition().floor);
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doSendBottom
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Card  sent to bottom" << std::endl;
			fsm.model->sendBottom(fsm.model->currentPlayer()->getPosition().floor);
			fsm.graphics->hideTopPatrol(fsm.model->currentPlayer()->getPosition().floor);
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doPlaceCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Placing crow token" << std::endl;
			bool b = fsm.model->currentPlayer()->placeCrow(event.c);
			if (b == false)
				std::cout << "Cant place crow token!" << std::endl;
			fsm.currentAction = NO_TYPE;
		}
	};

	struct doPickUpLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Pick up loot" << std::endl;
			fsm.model->currentPlayer()->pickUpLoot();
			fsm.currentAction = NO_TYPE;
		}
	};


	struct  doOfferLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			// Guardo en el estado askConfirmation el loot que quiero ofrecer
			target.lootToOffer = toEnum_lootType(event.type.c_str());
			string name = fsm.model->currentPlayer()->getName();

			fsm.graphics->askQuestion(name + string(" is offering you the ") + event.type + string(". Do you accept it?"));
		}
	};

	struct doRequestLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			// Guardo en el estado askConfirmation el loot que quiero pedir
			target.lootToOffer = toEnum_lootType(event.type.c_str());
			string name = fsm.model->currentPlayer()->getName();

			fsm.graphics->askQuestion(name + string(" is requesting you the ") + event.type + string(". Do you accept?"));
		}
	};

	struct doGetLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Getting loot " << string(toString(source.lootToOffer)) << " from " << fsm.model->otherPlayer()->getName() << std::endl;
			fsm.model->currentPlayer()->receiveLoot(source.lootToOffer);
		}
	};

	struct dontGetLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << fsm.model->otherPlayer()->getName() << " rejected your request." << std::endl;
		}
	};

	struct doGiveLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Giving loot " << string(toString(source.lootToOffer)) << " to " << fsm.model->otherPlayer()->getName() << std::endl;
			fsm.model->currentPlayer()->giveLoot(source.lootToOffer);
		}
	};

	struct dontGiveLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << fsm.model->otherPlayer()->getName() << " rejected your offer." << std::endl;
		}
	};

	struct doEndTurn
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Player turn ended" << std::endl;
			fsm.model->endTurn();
			fsm.currentAction = NO_TYPE;

			// If other player is remote send pass 
			if (is_same<EVT, ev::pass>::value && fsm.model->otherPlayer()->isRemote())
			{
				fsm.network->sendPass();
				fsm.process_event(ev::waitForNetwork());
			}
		}
	};

	struct changeTurn
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (fsm.model->otherPlayer()->isOnRoof())
			{
				std::cout << "Keep playing, you are alone!" << std::endl;
			}
			else
			{
				std::cout << "Changing turns" << std::endl;
				fsm.model->changeTurn();
				fsm.currentAction = NO_TYPE;
			}
		}
	};



	struct doKittyAction
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			vector<int> dices;
			dices.push_back(event.number);
			bool b = false;
			if (fsm.model->currentPlayer()->has(PERSIAN_KITTY) == true)
			{
				b = true;
				if (fsm.model->doKittyAction(event.number)) fsm.graphics->showDices(string("You threw a 1 or a 2 and the kitty escaped your grasp."), dices);
				else fsm.graphics->showDices(string("You either haven't thrown a 1 or a 2, or no alarm tiles where flipped. The kitty remains in your grasp."), dices);
			}

			if (fsm.model->currentPlayer()->has(CHIHUAHUA))
			{
				fsm.currentAction = THROW_DICE;
				if (!b) fsm.process_event(ev::throwDice(event.number));
				else
				{
					if (fsm.model->currentPlayer()->isLocal())
					{
						fsm.process_event(ev::throwDice(fsm.model->currentPlayer()->throwDice()));
					}
					//else remoto
				}
			}
			else
			{
				fsm.currentAction = NO_TYPE;
				fsm.process_event(ev::done());
			}
		}
	};

	struct doChihuahuaAction
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			vector<int> dices;
			dices.push_back(event.number);
			if (fsm.model->doChihuahuaAction(event.number)) fsm.graphics->showDices(string("You threw a 6. The alarm was triggered by the Chihuahua's barks"), dices);
			else fsm.graphics->showDices(string("You didn't throw a 6. You silenced the Chihuahua before the alarm was triggered."), dices);
			fsm.currentAction = NO_TYPE;
			fsm.process_event(ev::done());
		}
	};

	struct moveGuard
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Moving guard" << std::endl;
			fsm.model->moveGuard();

			if (fsm.model->gameOver())
				fsm.process_event(ev::gameOver());
			else if (fsm.model->guardIsMoving() == false)
			{
				fsm.process_event(ev::passGuard());
				fsm.guardTimer->stop();
			}
		}
	};

	struct resetGame
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Reset game" << std::endl;
		}
	};


	struct showMove
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Tiles availables to move: ";
			fsm.graphics->printInHud(string("Choose a tile available to move..."));
			vector<Coord> v = fsm.model->currentPlayer()->whereCanIMove();
			Coord::printVec(v);
			std::cout << std::endl;

			fsm.currentAction = MOVE;
			// Distinguir las tiles disponibles para moverse
			fsm.graphics->setTilesClickable(v);
		}
	};

	struct showPeek
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Tiles availables to peek: ";
			fsm.graphics->printInHud(string("Choose a tile available to peek..."));
			vector<Coord> v = fsm.model->currentPlayer()->whereCanIPeek();
			Coord::printVec(v);
			std::cout << std::endl;
			fsm.currentAction = PEEK;
			// Distinguir las tiles disponibles para moverse
			fsm.graphics->setTilesClickable(v);

		}
	};

	struct showAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Alarm can be created on the following tiles: ";
			vector<Coord> v = fsm.model->currentPlayer()->getAdjacentJuicer();
			Coord::printVec(v);
			std::cout << std::endl;
			fsm.currentAction = CREATE_ALARM;
			// Distinguir las tiles disponibles para crear la alarma
			fsm.graphics->setTilesClickable(v);
		}
	};

	struct showCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Crow token can placed in following tiles: ";
			vector<Coord> v = fsm.model->getTilesXDist(2, fsm.model->currentPlayer());
			Coord::printVec(v);
			std::cout << std::endl;
			fsm.currentAction = PLACE_CROW;
			// Distinguir las tiles disponibles para poner el Crow token
			fsm.graphics->setTilesClickable(v);

		}
	};

	struct showPickUpLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			fsm.currentAction = PICK_UP_LOOT;
		}
	};

	struct prepAddToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Preparing to add token: ";
			fsm.currentAction = ADD_TOKEN;

		}
	};

	struct prepThrowDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Preparing to throw dice: ";
			fsm.currentAction = THROW_DICE;

		}
	};

	struct showOfferLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Preparing to offer loot: ";
			fsm.currentAction = OFFER_LOOT;
			fsm.graphics->showAvailableLoots(string("Choose the loot you want to offer:"), fsm.model->currentPlayer()->getAvailableLoots());
		}
	};

	struct prepRequest
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			std::cout << "Preparing to request loot: ";
			fsm.currentAction = REQUEST_LOOT;
			fsm.graphics->showAvailableLoots(string("Choose the loot you want to request:"), fsm.model->otherPlayer()->getAvailableLoots());

		}
	};

	struct showEndMessage
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		void operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			if (is_same<EVT, ev::burglarsWin>::value)
				fsm.graphics->showOkMessage(string("You win!"));
			else if (is_same<EVT, ev::gameOver>::value)
				fsm.graphics->showOkMessage(string("Yow loose"));
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

	struct needsConfirmation
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.model->currentPlayer()->needConfirmationToMove(event.c) != _MOVE;
		}
	};

	struct isPeeking
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == PEEK;
		}
	};

	struct isCreatingAlarm
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == CREATE_ALARM;
		}
	};

	struct isSpying
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == SPY_PATROL;
		}
	};

	struct isPlacingCrow
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == PLACE_CROW;
		}
	};

	struct isAddingToken
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == ADD_TOKEN;
		}
	};

	struct isThrowingDice
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == THROW_DICE;
		}
	};

	struct isThrowing4Kitty
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return (fsm.currentAction == NO_TYPE);
		}
	};

	struct isThrowing4Chihuahua
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return (fsm.currentAction == THROW_DICE);
		}
	};

	struct isCrackingSafe
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == ROLL_DICE_FOR_LOOT;
		}
	};

	struct isPickingLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == PICK_UP_LOOT;
		}
	};

	struct isOfferingLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == OFFER_LOOT;
		}
	};

	struct isRequestingLoot
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.currentAction == REQUEST_LOOT;
		}
	};

	struct gameIsRemote
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.gameMode == GameFSM_::MODE::REMOTE;
		}
	};

	struct gameIsLocal
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.gameMode == GameFSM_::MODE::LOCAL;
		}
	};

	struct playerIsLocal
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.model->currentPlayer()->isLocal() == true;
		}
	};

	struct playerIsRemote
	{
		template <class EVT, class FSM, class SourceState, class TargetState>
		bool operator()(EVT const& event, FSM& fsm, SourceState& source, TargetState& target)
		{
			return fsm.model->currentPlayer()->isLocal() == false;
		}
	};


	// Transition table
	struct transition_table : mpl::vector<
		//       Start					Event					Next				Action            Guard
		//  +-----------+-------------+------------+--------------+--------------+-----------------+-----------+

		Row < chooseInitialPos, ev::coord, chooseAction, doSetInitialPos, none				>,

		Row < chooseAction, ev::pass, guardTurn, doEndTurn, none				>,

		Row < chooseAction, ev::movee, none, showMove, none				>,
		Row < chooseAction, ev::coord, checkActionTokens, doMove, And_<isMoving, Not_<needsConfirmation>>			>,
		Row < chooseAction, ev::coord, askConfirmationMove, none, And_<isMoving, needsConfirmation>			>,


		Row < chooseAction, ev::peek, none, showPeek, none				>,
		Row < chooseAction, ev::coord, checkActionTokens, doPeek, isPeeking			>,

		Row	< chooseAction, ev::createAlarm, none, showAlarm, none				>,
		Row	< chooseAction, ev::coord, checkActionTokens, doCreateAlarm, isCreatingAlarm   >,

		Row < chooseAction, ev::placeCrow, none, showCrow, none				>,
		Row	< chooseAction, ev::coord, chooseAction, doPlaceCrow, isPlacingCrow		>,

		Row < chooseAction, ev::spyPatrol, askConfirmation, doSpyPatrol, none				>,
		Row < chooseAction, ev::addToken, checkActionTokens, doAddToken, none				>,
		Row < chooseAction, ev::useToken, chooseAction, doUseToken, none				>,
		Row < chooseAction, ev::throwDice, checkActionTokens, doCrackSafe, none				>,
		Row < chooseAction, ev::offerLoot, chooseLoot, showOfferLoot, none				>,
		Row < chooseAction, ev::requestLoot, chooseLoot, prepRequest, none				>,
		Row < chooseAction, ev::pickUpLoot, chooseAction, doPickUpLoot, none				>,

		//  +------------+-------------+------------+--------------+--------------+
		Row < askConfirmation, ev::yes, checkActionTokens, doStayTop, isSpying			>,
		Row < askConfirmation, ev::no, checkActionTokens, doSendBottom, isSpying			>,
		Row < askConfirmation, ev::yes, chooseAction, doGiveLoot, isOfferingLoot	>,
		Row < askConfirmation, ev::no, chooseAction, dontGiveLoot, isOfferingLoot	>,
		Row < askConfirmation, ev::yes, chooseAction, doGetLoot, isRequestingLoot	>,
		Row < askConfirmation, ev::no, chooseAction, dontGetLoot, isRequestingLoot	>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < askConfirmationMove, ev::yes, askConfirmationMove, none, none			>,
		Row < askConfirmationMove, ev::no, checkActionTokens, dontMove, none >,
		Row < askConfirmationMove, ev::coord, checkActionTokens, doMove, none			>,
		Row < askConfirmationMove, ev::throwDice, none, doOpenKeypad, none	>,

		//  +------------+-------------+------------+--------------+--------------+

		Row < chooseLoot, ev::lootType, askConfirmation, doOfferLoot, isOfferingLoot	>,
		Row < chooseLoot, ev::lootType, askConfirmation, doRequestLoot, isRequestingLoot	>,
		Row < chooseLoot, ev::cancel, chooseAction, none, none	>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < checkActionTokens, ev::no, guardTurn, doEndTurn, none				>,
		Row < checkActionTokens, ev::yes, chooseAction, none, none				>,
		Row < checkActionTokens, ev::gameOver, gameEnded, none, none				>,
		Row < checkActionTokens, ev::burglarsWin, gameEnded, none, none				>,
		//  +------------+-------------+------------+--------------+--------------+
		Row < guardTurn, ev::movee, none, moveGuard, none				>,
		Row < guardTurn, ev::passGuard, beginTurn, changeTurn, none				>,
		Row < guardTurn, ev::gameOver, gameEnded, none, none				>,
		//  +------------+-------------+------------+--------------+--------------+f
		Row < beginTurn, ev::done, chooseAction, none, none				>,
		Row < beginTurn, ev::throwDice, none, doKittyAction, isThrowing4Kitty	>,
		Row < beginTurn, ev::throwDice, none, doChihuahuaAction, isThrowing4Chihuahua	>,


		//  +------------+-------------+------------+--------------+--------------+
		Row < gameEnded, ev::playAgain, chooseAction, resetGame, none				>,
		Row < gameEnded, ev::ok, none, none, none				>,
		//  +------------+-------------+------------+--------------+--------------+

		Row < idle, ev::waitForNetwork, waitingForNetwork, none, gameIsRemote				>,
		Row < waitingForNetwork, ev::ack, idle, none, gameIsRemote				>

	> {};

	// Replaces the default no-transition response.
	template <class FSM, class EVT>
	void no_transition(EVT const&  event, FSM& fsm, int state)
	{
		std::cout << "no transition from state " << state << " on event " << typeid(event).name() << std::endl;
	}

	///typedef mpl::vector<idle, chooseInitialPos> initial_state;
	typedef chooseInitialPos initial_state;

};
// Pick a back-end
typedef msm::back::state_machine<GameState_> GameState;