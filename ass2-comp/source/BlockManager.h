#pragma once
#include <map>
#include <string>
#include <memory>
#include "Block.h"

class BlockManager
{
	BlockManager(){}
	std::vector<std::shared_ptr<Block>> m_blocks;
public:
	static BlockManager& get()
	{
		static BlockManager instance; // Guaranteed to be destroyed. Instantiated on first use.
		return instance;
	}

	BlockManager(BlockManager const&) = delete;
	void operator=(BlockManager const&) = delete;

	std::shared_ptr<Block> createRootBlock() {
		auto result = std::make_shared<Block>();
		m_blocks.push_back(result);
		return result;
	}

	std::shared_ptr<Block> createRootBlock(std::string name) {
		auto result = std::make_shared<Block>(name);
		m_blocks.push_back(result);
		return result;
	}

	std::vector<std::shared_ptr<Block>> getBlocks() {
		return m_blocks;
	}
};

