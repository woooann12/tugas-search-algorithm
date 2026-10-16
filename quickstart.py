from westworld.environment import GridEnvironment
from westworld.agents import BaseAgent
from westworld.objects import BaseCollectible
from westworld.simulation import Simulation
from westworld.colors import *

class Food(BaseCollectible):
    pass

class Rabbit(BaseAgent):

    def __init__(self, x, y, curiosity=5):
        super().__init__(x, y, color=(139, 69, 19), curiosity=curiosity)

    def step(self):
        targets = self.find_closest(name="Food", k=1)
        if len(targets) > 0:
            target = targets[0]
            self.move_towards(obj=target, naive=True)
        else:
            self.wander()

food_spawner = lambda x, y: Food(x, y, color=(220, 150, 50), img_asset="ball")
rabbit_spawner = lambda x, y: Rabbit(x, y, curiosity=5)

env = GridEnvironment(20, 10, 20, show_grid=True,
                      background_color=(102, 178, 102),
                      grid_color=(127, 191, 127),
                      toroidal=True)
env.spawn(rabbit_spawner, 4)
env.spawn(food_spawner, 24)
env.render()

sim = Simulation(env, fps=5, name="Quickstart")
_, _ = sim.run_episode(n_steps=50, save=True, replay=True, save_format="gif")