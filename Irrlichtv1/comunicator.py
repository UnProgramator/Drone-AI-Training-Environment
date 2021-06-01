import DQN_RL
import numpy as np

rl=None
history_length=4
remembered_epoche_count=4
remembered_epoches=None
oldstates=[]
coord=[0,0,0]

def __add__new_state(new_state):
    global oldstates
    if len(oldstates)>history_length:
        oldstates.pop()
        oldstates.insert(0,new_state)

def init(input_size, output_size, learning_rate):
    global rl
    save_dir = "."

    rq = DQN_rl(input_size = (input_size, history_length), train_epoc_states_number=remembered_epoche_count, output_size = output_size, learning_rate=learning_rate, directory=save_dir)

    
def next_step(values):
    values_list=[]
    for name,val in values:
        if type(val) is tuple:
            values_list += list(val)
        else:
            values_list += [val]
    dqn_input = np.asarray(values_list, dtype=np.float32)
    

def get_feedback(new_state, x, y, z, collision_detect):
    __add__new_state(new_state)
    new_coord = [x,y,z]