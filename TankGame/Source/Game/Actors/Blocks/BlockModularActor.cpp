#include "BlockModularActor.h"

#include <Framework2D/Gameplay/Level.h>
#include <Game/Game.h>

#include "BlockFragmentActor.h"

namespace Game {

	BlockModular::BlockModular(const std::string& Name, const Vec2& Position, BlockArr&& BlockArray)
		: Actor(Name, Position), BlockArray(std::move(BlockArray)), BlocksToDestroyNum(0)
	{
		// BlockFragments set indexes
		for (int i = 0; i < BlockArrSize; ++i)
		{
			auto& Block = BlockArray[i];

			if (Block)
			{
				++BlocksToDestroyNum;
				
				Block->ModularOwner = this;
				Block->ModularIndex = i;
			}
		}

		// Initialize actor size
		for (auto& BlockFragment : BlockArray)
		{
			if (BlockFragment != nullptr)
			{
				SetSize(BlockFragment->GetSize().X * 4, BlockFragment->GetSize().Y * 4);
				break;
			}
		}
	}

	void BlockModular::OnDestroy()
	{
		for (int i = 0; i < BlockArrSize; i++)
		{
			auto& Block = BlockArray[i];

			if (Block != nullptr)
			{
				Block->ModularOwner = nullptr;
				Block->Destroy();
			}
		}
	}

	void BlockModular::FragmentBlockDamaged(int FragmentIndex, float Damage, Direction Side, Actor* Instigator)
	{
		int DamagedRow = FragmentIndex / BlockArrRowSize;
		int DamagedColumn = FragmentIndex % BlockArrRowSize;

		if (Side == Direction::RIGHT || Side == Direction::LEFT) // Vertical case
		{
			int IndexVertical;

			for (int i = 0; i < BlockArrRowSize; ++i)
			{
				IndexVertical = i * BlockArrRowSize + DamagedColumn;
				auto& Block = BlockArray[IndexVertical];

				// replicate damage in column
				if (IndexVertical != FragmentIndex && Block && Block->HealthComp)
				{
					Block->HealthComp->OnDamage(Damage, Side, Instigator);
				}
			}
		}
		else  // Horizontal case
		{
			int IndexHorizontal;

			for (int i = 0; i < BlockArrRowSize; ++i)
			{
				IndexHorizontal = DamagedRow * BlockArrRowSize + i;
				auto& Block = BlockArray[IndexHorizontal];

				// replicate damage in row
				if (IndexHorizontal != FragmentIndex && Block && Block->HealthComp)
				{
					Block->HealthComp->OnDamage(Damage, Side, Instigator);
				}
			}
		}
	}

	void BlockModular::FragmentBlockDestroyed(int FragmentIndex)
	{
		BlockArray[FragmentIndex] = nullptr;
		if (!--BlocksToDestroyNum) Destroy();
	}

	BlockModular* BlockModular::SpawnModularBrickBlock(Level* Level, Vec2 Position, UINT16 FragmentMask)
	{
		BlockArr Bricks;

		// helpers to spawn block fragment with sprites in chess order
		bool bTextureSwapChessOrder;
		int Even;
		int Index;
		int BitInMask;

		BlockFragment* SpawnedBrickFrag;
		Vec2 BrickFragPos = Position;

		constexpr float BrickFragSize_X = (GameConst::GAME_CHUNK_W / BlockArrRowSize);  // hack ;>
		constexpr float BrickFragSize_Y = (GameConst::GAME_CHUNK_H / BlockArrRowSize);

		// Spawn BlockFragment instances
		for (int i = 0; i < BlockArrRowSize; ++i) 
		{
			BrickFragPos.X = Position.X;

			Even = i % 2;

			for (int j = 0; j < BlockArrRowSize; ++j)
			{
				Index = i * BlockArrRowSize + j;
				BitInMask = 1 << Index;

				bTextureSwapChessOrder = (Index + Even) % 2 == 0;
				
				if ((FragmentMask & BitInMask) == BitInMask)
				{
					SpawnedBrickFrag = Level->SpawnActorFromClass<BlockFragment>("BrickBlock", BrickFragPos, Anchor::TOP_LEFT,
						bTextureSwapChessOrder ? ResPath::T_BRICK_0 : ResPath::T_BRICK_1,
						GameConst::BRICK_BASIC_HEALTH);
				}
				else
				{
					SpawnedBrickFrag = nullptr;
				}

				Bricks[Index] = SpawnedBrickFrag;

				BrickFragPos.X = Position.X + BrickFragSize_X * (j + 1);
			}

			BrickFragPos.Y = Position.Y + BrickFragSize_Y * (i + 1);
		}

		auto SpawnedModularBrick = Level->SpawnActorFromClass<BlockModular>("BrickBlock", Position, Anchor::TOP_LEFT, std::move(Bricks));

		return SpawnedModularBrick;
	}

}