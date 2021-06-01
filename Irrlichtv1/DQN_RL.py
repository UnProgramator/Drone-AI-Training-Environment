import tensorflow as tf
import keras as ks
import numpy as np
import time
import sys

def debug_call(*args, file=sys.stdout):
    print(time.ctime(time.time())," ", *args, file=file) 

class DQN_RL:
    """
    class for implementing a deep Q-network Reinforcement Learning AI
    """
    fileDir=None
    imputSize=None

    def __init__(self, input_size, train_epoc_states_number, output_size, learning_rate, directory='.' ):
        debug_call('creating deep q-network')
        self.__learning_rate=learning_rate
        self.__state_size = input_size
        self.__history_length = train_epoc_states_number
        

        self.__build_deep_q_network()
        debug_call('deep q-network created succesfuly')

    def __build_deep_q_network(self):
        """
        build a simple 1-dymensional deep q network - imput is an array, not an image/image-like
        """
        input = ks.Input(shape = (self.__state_size, self.__history_length))
        tmp = ks.layers.Conv1D(filters=16,kernel_size=4, strides=2, activation='relu', kernel_initializer=ks.initializers.VarianceScaling(scale=2.))(input)
        tmp = ks.layers.Conv1D(filters=32,kernel_size=2, strides=1, activation='relu', kernel_initializer=ks.initializers.VarianceScaling(scale=2.))(tmp)   
        tmp = ks.layers.Flatten()(tmp)
        tmp = ks.layers.Dense(64, activation='tanh', kernel_initializer=initializers.VarianceScaling(scale=2.))(tmp) # am schimbat relu cu tanh
        predict = ks.layers.Dense(output_size, activation='tanh', kernel_initializer=initializers.VarianceScaling(scale=2.))(tmp) # am schimbat relu cu tanh pentru a scoate val intre [-1,1]
        self.decision_network = ks.Model(inputs=input, outputs=predict)
        self.decision_network.compile(optimizer=ks.optimizers.Adam(self.learning_rate), loss=losses.Huber())
        self.decision_network.summary()

    def make_decizion(self, state): #deci functia asta face o decizie
        state = state.reshape((-1, self.__state_size, self.__history_length))
        return np.asarray(self.decision_network(state)).argmax(axis=1)

    def train_step(self, old_states_list, new_states_list, actions_list, rewards_list, is_terminal_list):
        #take list and make numpy.array from them
        old_states = np.asarray(old_states_list)
        new_states = np.asarray(new_states_list)
        actions = np.asarray(actions_list)
        rewards = np.asarray(rewards_list)
        is_terminal = np.asarray(is_terminal_list)

        q_new_state = np.max(self.target_predict(new_states), axis=1)
        target_q = rewards + (self.gamma*q_new_state * (1-is_terminal))
        one_hot_actions = ks.utils.to_categorical(actions, self.num_actions)# using tf.one_hot causes strange errors

        loss = self._gradient_train(old_states, target_q, one_hot_actions)

        return loss

    @tf.function
    def _gradient_train(self, old_states, target_q, one_hot_actions): # ----------------
        with tf.GradientTape() as tape:
            q_values = self.decision_network(old_states)
            current_q = tf.reduce_sum(tf.multiply(q_values, one_hot_actions), axis=1)
            loss = losses.Huber()(target_q, current_q)

            variables = self.decision_network.trainable_variables
            gradients = tape.gradient(loss, variables)
            self.decision_network.optimizer.apply_gradients(zip(gradients, variables))

        return loss

    def save_network(self): # copy-paste
        debug_call("saving..")
        self.decision_network.save_weights(self.checkpoint_dir)
        debug_call("saved")

