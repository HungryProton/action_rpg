#include "melee_combat.hpp"
#include "component/action/battle/melee_attack.hpp"

namespace game{

	MeleeCombat::MeleeCombat(){
		Require<MeleeAttack>();
	}

	MeleeCombat::~MeleeCombat(){ }

	void MeleeCombat::BeforeUpdate(){
		this->MessageHandler<IntentMessage>::PollMessages();
	}

	void MeleeCombat::OnUpdate(Entity e){
		MeleeAttack* m = ecs::GetComponent<MeleeAttack>(e);

		if(!m->is_attacking){ return; }

	}

	void MeleeCombat::OnMessage(IntentMessage msg){
		if(msg.intent != Intent::ATTACK){ return; }
	}

}
