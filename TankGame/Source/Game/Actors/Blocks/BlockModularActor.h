#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>

namespace Game {

	using namespace Framework2D;

	class BlockFragment;

	constexpr int BlockArrSize = 16;
	constexpr int BlockArrRowSize = 4;

	typedef std::array<BlockFragment*, BlockArrSize> BlockArr;

	/*
	 * This class is represent 4x4 BlockFragment actor container,
	 *  to simulate partial block destruction similar to original game
	 */
	class BlockModular : public Framework2D::Actor
	{
	protected:
		// store matrix 4x4 of BlockFragment*
		BlockArr BlockArray;

		/* On BlockModular instance create will be equal to num of not null BlockFragment*
		 * On every Destroyed BlockFragment* will decrement
		 * if equal to zero -> destroy BlockModular instance
		 */
		int BlocksToDestroyNum;

	public:
		/* 
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */ 
		BlockModular(const std::string& Name, const Vec2& Position, BlockArr&& BlockArray);

		virtual void OnDestroy() override;

		/** Replicate damage to other BlockFragment in Matrix columns/rows */
		void FragmentBlockDamaged(int FragmentIndex, float Damage, Direction Side, Actor* Instigator);

		/** Set to null in array */
		void FragmentBlockDestroyed(int FragmentIndex);

		/** Spawn modular brick block with custom fragment matrix grid, if last param has all 1 in bit repr, then its full block */
		static BlockModular* SpawnModularBrickBlock(Level* Level, Vec2 Position, UINT16 FragmentMask = 0b1111111111111111);
	};
}
