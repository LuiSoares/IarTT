import numpy as np
import random
import time


class Agent:
    def __init__(self, i=0, j=0):
        self.i = i
        self.j = j

    @property
    def loc(self):
        return (self.i, self.j)

    def vmove(self, direction):
        direction = 1 if direction > 0 else -1
        return Agent(self.i + direction, self.j)

    def hmove(self, direction):
        direction = 1 if direction > 0 else -1
        return Agent(self.i, self.j + direction)

    def __repr__(self):
        return str(self.loc)


class QLearning:
    def __init__(self, num_states, num_actions, lr=0.1, discount_factor=1.0):
        self.q = np.zeros((num_states, num_actions))
        self.a = lr
        self.g = discount_factor

    def update(self, st, at, rt, st1):
        q = self.q
        a = self.a
        g = self.g
        self.q[st, at] = (1 - a) * q[st, at] + a * (rt + g * np.max(q[st1]) - q[st, at])


class Sarsa:
    def __init__(self, num_states, num_actions, lr=0.1, discount_factor=1.0):
        self.sar = np.zeros((num_states, num_actions))
        self.a = lr
        self.g = discount_factor

    def update(self, st, at, rt, st1, m):
        moves = m.compute_possible_move()
        random.shuffle(moves)
        move, move_idx = moves[0]
        at1 = move_idx

        sar = self.sar
        a = self.a
        g = self.g
        sar[st, at] = sar[st, at] + a * (rt + g * sar[st1, at1] - sar[st, at])


class Maze:
    def __init__(self, rows=4, columns=4):
        self.env = np.zeros((rows, columns))
        self.agent = Agent(0, 0)

    @property
    def all_actions(self):
        a = self.agent
        return [
            a.vmove(1),
            a.vmove(-1),
            a.hmove(1),
            a.hmove(-1),
        ]

    def reset(self):
        self.agent.i = 0
        self.agent.j = 0

    def state_for_agent(self, a):
        nr, nc = self.env.shape
        return a.i * nc + a.j

    def in_bounds(self, i, j):
        nr, nc = self.env.shape
        return i >= 0 and i < nr and j >= 0 and j < nc

    def agent_in_bounds(self, a):
        return self.in_bounds(a.i, a.j)

    def agent_dient(self, a):
        return not self.env[a.i, a.j] == -1

    def is_valid_new_agent(self, a):
        return self.in_bounds(a.i, a.j) and self.agent_dient(a)

    def compute_possible_move(self):
        moves = self.all_actions
        return [(m, ii) for ii, m in enumerate(moves) if self.is_valid_new_agent(m)]

    def do_a_move(self, a):
        assert self.is_valid_new_agent(a), "Agent can´t go there"
        self.agent = a
        return 10 if self.has_won() else -0.1

    def has_won(self):
        a = self.agent
        return self.env[a.i, a.j] == 1

    def visualize(self):
        assert self.agent_in_bounds(self.agent), "Agent out of bounds"
        e = self.env.copy()
        m = self.agent
        e[m.i, m.j] = 6
        print(e)


def make_test_maze(s=4):
    m = Maze(s, s)
    e = m.env
    h, w = e.shape
    e[-1, -1] = 1
    for i in range(len(e)):
        for j in range(len(e[i])):
            if i in [0, h - 1] and j in [0, w - 1]:
                continue
            if random.randint(0, 10) < 2:
                e[i, j] = -1
    return m


def make_test_maze3():
    m = Maze(3, 3)
    e = m.env
    h, w = e.shape
    e[-1, -1] = 1
    e[1, 1] = -1
    e[1, 2] = -1

    return m


def make_test_maze4():
    m = Maze(4, 4)
    e = m.env
    h, w = e.shape
    e[-1, -1] = 1
    e[1, 1] = -1
    e[1, 2] = -1
    e[1, 3] = -1
    e[2, 1] = -1
    return m


def make_test_maze5():
    m = Maze(5, 5)
    e = m.env
    h, w = e.shape
    e[-1, -1] = 1
    e[1, 1] = -1
    e[1, 2] = -1
    e[1, 3] = -1
    e[2, 1] = -1
    e[3, 4] = -1
    e[3, 3] = -1
    return m


def make_test_maze6():
    m = Maze(6, 6)
    e = m.env
    h, w = e.shape
    e[-1, -1] = 1
    e[1, 1] = -1
    e[1, 2] = -1
    e[1, 3] = -1
    e[2, 1] = -1
    e[3, 4] = -1
    e[3, 3] = -1
    e[5, 1] = -1
    e[4, 1] = -1
    e[4, 5] = -1
    return m


def main():
    print("Do you want to use pre-generated maze ? (s/n)")
    pre = input()
    if pre != 's':
        print("Hi, whats the size of the maze? \n")
        s = int(input())
        ctu = 's'
        while ctu != 'n':
            m = make_test_maze(s)
            m.visualize()
            print("Press 'n' if you want this maze")
            ctu = input()
    else:
        print("Want maze 3 (3x3) , 4 (4x4), 5 ( 5x5) , 6 (6x6) ?")
        s = int(input())
        if s == 3:
            m = make_test_maze3()
            m.visualize()

        elif s == 4:
            m = make_test_maze4()
            m.visualize()

        elif s == 5:
            m = make_test_maze5()
            m.visualize()

        elif s == 6:
            m = make_test_maze6()
            m.visualize()
        else:
            print("Invalid Input")
            return
    print("If you wanna solve it with qlearning select 1 \n")
    print("If you wanna solve it with SARSA select 2")
    ctu = int(input())
    print(" You wanna set the Learning Rate/Discount Factor? (s/n) ?")
    factor = input()
    if ctu == 1:
        if factor == 's':
            print("Whats the Learning Rate ?")
            lr = int(input())
            print("Whats the Discount Factor?")
            df = int(input())
            q = QLearning(s ** 2, 4, lr, df)
        else:
            q = QLearning(s ** 2, 4)
        print("How many times you want the maze to be solved?")
        solution = int(input())
        start = time.time()
        for i in range(solution):
            final_score = 0
            m.reset()
            while not m.has_won():
                moves = m.compute_possible_move()
                random.shuffle(moves)
                move, move_idx = moves[0]
                at = move_idx
                st = m.state_for_agent(m.agent)
                score = m.do_a_move(move)
                final_score += score
                rt = score
                st1 = m.state_for_agent(m.agent)
                q.update(st, at, rt, st1)
            # print(q.q)
            # print(f"final episode with score of {final_score}")
        m.reset()
        score = 0
        while not m.has_won():
            s = m.state_for_agent(m.agent)
            array = q.q[s]
            zero_idx = np.where(np.abs(array) <= 1e-5)[0]
            array[zero_idx] = -5000
            a_idx = np.argmax(array)
            score += m.do_a_move(m.all_actions[a_idx])
        m.visualize()
        print(score)
    if ctu == 2:
        if factor == 's':
            print("Whats the Learning Rate ?")
            lr = int(input())
            print("Whats the Discount Factor?")
            df = int(input())
            sar = Sarsa(s ** 2, 4, lr, df)
        else:
            sar = Sarsa(s ** 2, 4)
        print("How many times you want the maze to be solved?")
        solution = int(input())
        for i in range(solution):
            final_score = 0
            m.reset()
            while not m.has_won():
                moves = m.compute_possible_move()
                random.shuffle(moves)
                move, move_idx = moves[0]
                at = move_idx
                st = m.state_for_agent(m.agent)
                score = m.do_a_move(move)
                final_score += score
                rt = score
                st1 = m.state_for_agent(m.agent)
                sar.update(st, at, rt, st1, m)
            # print(q.q)
            # print(f"final episode with score of {final_score}")
        m.reset()
        score = 0
        while not m.has_won():
            s = m.state_for_agent(m.agent)
            a_idx = np.argmax(sar.sar[s])
            print(sar.sar[s])
            score += m.do_a_move(m.all_actions[a_idx])
        m.visualize()
        # print(score)
        end = time.time()
        print("The time of execution of above program is :", end - start)
        # https://www.geeksforgeeks.org/how-to-check-the-execution-time-of-python-script/


if __name__ == '__main__':
    main()
