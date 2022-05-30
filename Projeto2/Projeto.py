import numpy as np

class Agent:
    def __init__(self,i=0,j=0):
        self.i=i
        self.j=j
    @property
    def loc(self):
        return (self.i,self.j)
    
    def vmove(self, direction):
        direction = 1 if direction > 0 else -1
        return Agent(self.i+direction,self.j)
    
    def hmove(self,direction):
        direction=1 if direction>0 else -1
        return  Agent(self.i,self.j+direction)
    
    def __repr__(self):
        return str(self.loc)
    
class Maze:
    def __init__(self,rows=4,columns=4):
        self.env=np.zeros((rows,columns))
        self.agent = Agent(0,0)
        
    def in_bounds(self,i,j):
        nr,nc = self.env.shape
        return i >= 0 and i < nr and j >= 0 and j < nc
    
    def agent_in_bounds(self,a):
        return self.in_bounds(a.i,a.j)
    
    def compute_possible_move(self):
        a = self.agent
        moves = [
            a.vmove(1),
            a.vmove(-1),
            a.hmove(1),
            a.hmove(-1),
        ]
        return [m for m in moves if self.in_bounds(m)]
    
    def visualize(self):
        assert self.agent_in_bounds
        
        
if __name__== '__main__':
    m = Maze()
    print(m.env)
    
    
    //https://www.youtube.com/watch?v=psDlXfbe6ok