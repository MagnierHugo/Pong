
struct Particle {
	int X;
	int Y;

	int DirX;
	int DirY;

	int Size;
	int Speed;
};

void UpdateParticles(struct Particle particles[100], float deltaTime)
{
	for (int i = 0; i < 100; i++)
	{
		particles[i].X += particles[i].DirX * particles[i].Speed * deltaTime;
		particles[i].Y += particles[i].DirY * particles[i].Speed * deltaTime;
		particles[i].Size--;
	}
}