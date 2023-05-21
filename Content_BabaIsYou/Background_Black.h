#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

// Ό³Έν :
class Background_Black : public GameEngineActor
{
public:
	// constrcuter destructer
	Background_Black();
	~Background_Black();

	// delete Function
	Background_Black(const Background_Black& _Other) = delete;
	Background_Black(Background_Black&& _Other) noexcept = delete;
	Background_Black& operator=(const Background_Black& _Other) = delete;
	Background_Black& operator=(Background_Black&& _Other) noexcept = delete;

	void Init(const std::string& _FileName);

protected:

private:
	std::string FileName;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};

