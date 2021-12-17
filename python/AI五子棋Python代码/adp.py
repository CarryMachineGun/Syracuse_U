# ！/usr/bin/env python
# -*- coding:utf-8 -*-
# author:DuJinYu time: 2018/5/28
# 用于实现ADP算法

import tensorflow as tf
import numpy as np
pattern_dict = {'bla_pattern_01': [1, 1, 1, 1, 1],         'bla_pattern_02': [-1, 1, 1, 1, 1, -1],
                'bla_pattern_03': [-1, 1, 1, 1, -1, -1],   'bla_pattern_04': [-1, -1, 1, 1, 1, -1],
                'bla_pattern_05': [-1, 1, 1, -1, 1, -1],   'bla_pattern_06': [-1, 1, -1, 1, 1, -1],
                'bla_pattern_07': [1, 1, 1, 1, -1],        'bla_pattern_08': [-1, 1, 1, 1, 1],
                'bla_pattern_09': [1, 1, -1, 1, 1],        'bla_pattern_10': [1, -1, 1, 1, 1],
                'bla_pattern_11': [1, 1, 1, -1, 1],        'bla_pattern_12': [-1, -1, 1, 1, -1, -1],
                'bla_pattern_13': [-1, -1, 1, -1, 1, -1],  'bla_pattern_14': [-1, 1, -1, 1, -1, -1],
                'bla_pattern_15': [-1, -1, -1, 1, -1, -1], 'bla_pattern_16': [-1, -1, 1, -1, -1, -1],
                'bla_pattern_17': [-1, 1, -1, -1, 1, -1],  'bla_pattern_18': [1, -1, -1, -1, 1],
                'bla_pattern_19': [1, 1, -1, -1, 1],       'bla_pattern_20': [1, 1, -1, -1, -1],
                'whi_pattern_01': [0, 0, 0, 0, 0],         'whi_pattern_02': [-1, 0, 0, 0, 0, -1],
                'whi_pattern_03': [-1, 0, 0, 0, -1, -1],   'whi_pattern_04': [-1, -1, 0, 0, 0, -1],
                'whi_pattern_05': [-1, 0, 0, -1, 0, -1],   'whi_pattern_06': [-1, 0, -1, 0, 0, -1],
                'whi_pattern_07': [0, 0, 0, 0, -1],        'whi_pattern_08': [-1, 0, 0, 0, 0],
                'whi_pattern_09': [0, 0, -1, 0, 0],        'whi_pattern_10': [0, -1, 0, 0, 0],
                'whi_pattern_11': [0, 0, 0, -1, 0],        'whi_pattern_12': [-1, -1, 0, 0, -1, -1],
                'whi_pattern_13': [-1, -1, 0, -1, 0, -1],  'whi_pattern_14': [-1, 0, -1, 0, -1, -1],
                'whi_pattern_15': [-1, -1, -1, 0, -1, -1], 'whi_pattern_16': [-1, -1, 0, -1, -1, -1],
                'whi_pattern_17': [-1, 0, -1, -1, 0, -1],  'whi_pattern_18': [0, -1, -1, -1, 0],
                'whi_pattern_19': [0, 0, -1, -1, 0],       'whi_pattern_20': [0, 0, -1, -1, -1]}


class ADP(object):
    def __init__(self, _board, _select_color, _player_turn):
        self.board = _board
        self.select_color = _select_color
        self.player_turn = _player_turn
        self.input_x = [0.]*122

    def init_input(self):
        # pattern_number = 0
        pattern_number_list = []
        for pattern in pattern_dict.values():
            print(pattern)
            pattern_number = self.find_pattern_number(pattern)
            pattern_number_list.append(pattern_number)
        if self.select_color == 1:  # 电脑执黑
            for i in range(len(pattern_number_list)-20):
                self.input_x[i] = pattern_number_list[i]  # 黑子特征图案数量输入节点
                self.input_x[i+20] = pattern_number_list[i+20]  # 白子特征图案数量输入节点
                if self.player_turn == 1:  # 当前轮次，人执黑，电脑执白
                    # 黑子
                    if pattern_number_list[i] != 0:  # 某特征图案出现
                        self.input_x[i+40] = 0
                        self.input_x[i*2+40] = 1
                    else:                            # 某特征图案不出现
                        self.input_x[i+40] = 0
                        self.input_x[i*2+40] = 0
                    # 白子
                    if pattern_number_list[i+20] != 0:
                        self.input_x[i+80] = 1
                        self.input_x[i*2+80] = 0
                    else:
                        self.input_x[i+80] = 0
                        self.input_x[i*2+80] = 0
                    self.input_x[110] = 1
                    self.input_x[111] = 0

                if self.player_turn == 0:  # 当前轮次，人执白，电脑执黑
                    # 黑子
                    if pattern_number_list[i] != 0:
                        self.input_x[i+40] = 0
                        self.input_x[i*2+40] = 1
                    else:
                        self.input_x[i+40] = 0
                        self.input_x[i*2+40] = 0
                    # 白子
                    if pattern_number_list[i+20] != 0:
                        self.input_x[i+80] = 1
                        self.input_x[i*2+80] = 0
                    else:
                        self.input_x[i+80] = 0
                        self.input_x[i*2+80] = 0
                    self.input_x[110] = 1
                    self.input_x[111] = 0

        for i in range(len(pattern_number_list)):
            if self.player_turn == 1:
                self.input_x[i] = pattern_number_list[i]
                self.input_x[40+i] = 0

    def find_pattern_number(self, _pattern):
        # 搜索棋盘中对应20个特征图案的个数并返回个数
        _pattern_number = 0
        k = len(_pattern)
        # x方向
        for i in range(15):
            for j in range(15):
                # tmp_pattern = [self.board[i][j], self.board[i][j+1], self.board[i][j+2],
                #                self.board[i][j+3], self.board[i][j+4], self.board[i][j+5]]
                # if tmp_pattern == _pattern:
                #     _pattern_number += 1
                # x direction
                tmp_pattern = []
                for l in range(k):
                    tmp_pattern = tmp_pattern.append(self.board[i][j+l])
                if tmp_pattern == _pattern:
                    _pattern_number += 1
                # y direction
                tmp_pattern = []
                for l in range(k):
                    tmp_pattern = tmp_pattern.append(self.board[i+l][j])
                if tmp_pattern == _pattern:
                    _pattern_number += 1
                # y=x direction
                tmp_pattern = []
                for l in range(k):
                    tmp_pattern = tmp_pattern.append(self.board[i+l][j-l])
                if tmp_pattern == _pattern:
                    _pattern_number += 1
                # y=-x direction
                tmp_pattern = []
                for l in range(k):
                    tmp_pattern = tmp_pattern.append(self.board[i+l][j+l])
                if tmp_pattern == _pattern:
                    _pattern_number += 1
        return _pattern_number
        # y方向
        # for i in range(15):
        #     for j in range(15):
        #         tmp_pattern = [self.board[i][j], self.board[i+1][j], self.board[i+2][j],
        #                        self.board[i+3][j], self.board[i+4][j], self.board[i+5][j]]
        #         if tmp_pattern == _pattern:
        #             _pattern_number += 1
        # # y=x方向
        # for i in range(15):
        #     for j in range(15):
        #         tmp_pattern = [self.board[i][j], self.board[i-1][j+1], self.board[i-2][j+2],
        #                        self.board[i-3][j+3], self.board[i-4][j+4], self.board[i-5][j+5]]
        #         if tmp_pattern == _pattern:
        #             _pattern_number += 1
        # # y=-x方向
        # for i in range(15):
        #     for j in range(15):
        #         tmp_pattern = [self.board[i][j], self.board[i-1][j-1], self.board[i-2][j-2],
        #                        self.board[i-3][j-3], self.board[i-4][j-4], self.board[i-5][j-5]]
        #         if tmp_pattern == _pattern:
        #             _pattern_number += 1
        #return _pattern_number

    def init_weight(self, _input):
        pass

    def critic_network(self):
        def add_layer(input_data, in_size, out_size, activity_function=None):

            weights = tf.Variable(tf.truncated_normal([in_size, out_size], mean=0, stddev=0.1))  # 用截断的正态分布初始化权重值
            # basis = tf.Variable(tf.zeros([1, outSize]) + 0.1)  # 暂时不需要偏置
            weights_plus_b = tf.matmul(input_data, weights)  # + basis
            if activity_function is None:
                output = weights_plus_b
            else:
                output = activity_function(weights_plus_b)
            return output

        # x_data = np.linspace(-1, 1, 300)[:, np.newaxis]  # 转为列向量
        # noise = np.random.normal(0, 0.05, x_data.shape)
        # y_data = np.square(x_data) + 0.5 + noise

        xs = tf.placeholder(tf.float32, [122, 1])  # 样本数未知，特征数为1，占位符最后要以字典形式在运行中填入
        ys = tf.placeholder(tf.float32, [60, 1])

        l1 = add_layer(xs, 122, 60, activity_function=tf.nn.sigmoid)
        # sigmoid是激励函数的一种，122个输入层节点，60个隐藏节点
        l2 = add_layer(l1, 60, 1, activity_function=tf.nn.sigmoid)
        # 60个隐藏层节点，1个输入层节点
        loss = tf.reduce_mean(tf.reduce_sum(tf.square((ys - l2)), reduction_indices=[1]))  # 需要向相加索引号，redeuc执行跨纬度操作

        train = tf.train.GradientDescentOptimizer(0.1).minimize(loss)  # 选择梯度下降法

        init = tf.initialize_all_variables()
        sess = tf.Session()
        # sess = tf.InteractiveSession()
        sess.run(init)

        # for i in range(10000):
        #     sess.run(train, feed_dict={xs: self.x_data})
        #     if i % 50 == 0:
        #         print(sess.run(loss, feed_dict={xs: x_data, ys: y_data}))

    def action_policy(self):
        pass

    def back_propagation(self):
        pass


if __name__ == "__main__":
    pass

