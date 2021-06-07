import DQN_RL
import numpy as np
import random

rl=None
history_length=4
remembered_epoches=None
crt_epoche = 1
oldstates=[]
new_states=[]
actions=[]
rewards=[]
is_terminals=[]
coord=[0,0,0]

def __add__new_state(old_list, new_value):
    if len(old_list)>history_length:
        old_list.pop()
        old_list.insert(0,new_state)
    return old_list

def compute_reward(new_coord_list, destination, hascolide):
    global coord
    dist_o = math.sqrt((new_coord_list[0]-destination[0])**2 +(new_coord_list[1]-destination[1])**2 +(new_coord_list[2]-destination[2])**2)
    dist_n = math.sqrt((destination[0]-coord[0])**2 +(destination[1]-coord[1])**2 +(destination[2]-coord[2])**2)
    coord = new_coord_list

    if hascolide:
        return -4, True
    elif dist_o<dist_n:
        return -1, False
    elif dist_o==dist_n:
        return 1, False
    else:
        return 4, False

def init(input_size, output_size, learning_rate):
    global rl
    save_dir = "."
    try:
        rq = DQN_RL.DQN_RL(input_size = input_size, train_epoc_states_number=history_length, output_size = (output_size,), learning_rate=learning_rate, directory=save_dir)
        return True
    except Exception as e:
        # print(str(e))
        return False
    
    
    
def next_step(*values):
    global actions
    values_list=[]
    for name,val in values:
        if type(val) is tuple:
            values_list += list(val)
        else:
            values_list += [val]
    
    if len(new_states) < history_length:
        values_list = new_states + values_list*(history_length - len(new_states))

    dqn_input = np.asarray(values_list, dtype=np.float32)
    if len(new_states) == None and random.random() > 1/crt_epoche:
        comand = rl.make_decision(dqn_input)
    else:
        comand = np.randint(low=-1, high=1, size=(3,))

    actions = __add__new_state(actions, comand)

    return comand
    

def get_feedback(new_state, x, y, z, collision_detect, destx, desty, destz):
    global new_states
    global oldstates
    global rewards
    global is_terminals

    new_states = __add__new_state(new_states, new_state)
    oldstates = __add__new_state(oldstates, new_states[1])
    
    reward, is_terminal = compute_reward([x,y,z], [destx, desty, destz], collision_detect)

    rewards = __add__new_state(rewards, reward)
    is_terminals = __add__new_state(is_terminals, is_terminal)
    
    if len(rewards) == history_length:
       rl.train_step(old_states, new_states, actions, rewards, is_terminals)
