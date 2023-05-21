#pragma once

// Ό³Έν :
class PuzzleLevel
{
public:
	// constrcuter destructer
	PuzzleLevel();
	~PuzzleLevel();

	// delete Function
	PuzzleLevel(const PuzzleLevel& _Other) = delete;
	PuzzleLevel(PuzzleLevel&& _Other) noexcept = delete;
	PuzzleLevel& operator=(const PuzzleLevel& _Other) = delete;
	PuzzleLevel& operator=(PuzzleLevel&& _Other) noexcept = delete;

protected:

private:

};

