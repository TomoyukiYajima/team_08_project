#include "Random.h"
#include <random>

// —”¶¬Ší
static std::mt19937 mt;
// —”‚ÌƒV[ƒh
static unsigned int s_seed{ std::mt19937::default_seed };

void Random::randomize()
{
	std::random_device rd;
	randomize(rd());
}

void Random::randomize(unsigned int seed)
{
	s_seed = seed;
	mt = std::mt19937(s_seed);
}

int Random::rand(int l, int h)
{
	std::uniform_int_distribution<int> dist(l, h);
	return dist(mt);
}

float Random::rand(float l, float h)
{
	std::uniform_real_distribution<float> dist(l, h);
	return dist(mt);
}

unsigned int Random::seed()
{
	return s_seed;
}
