# ！/usr/bin/env python
# -*- coding:utf-8 -*-
# author:DuJinYu time: 2018/4/29

from tkinter import *
import tkinter.messagebox
from robot import Robot
# from tools import *


class GameGo:

    def __init__(self):
        """
        初始化内容：
            board: 棋盘（二维数组），-1：空；0：白子；1：黑子/ 或者可以设置成1-225，奇数为黑子，偶数为白子
            someone_win: 某人赢了的标志，0：白棋胜；1：黑棋胜   有待商讨/true:false
            mode: 对局模式选择（0/1），0：人人对弈；1：人机对弈
            select_color: 先手选择（0/1），0：选择执白；1：选择执黑
            window: 窗口
            can: 画布，用于绘制棋盘
            white_done: 保存白棋已经下过的点
            black_done: 保存黑棋已经下过的点
            chess_piece_done：保存已经下的点，index为奇数代表黑，偶数代表白
        """
        self.mode = 0  # 默认模式人人对弈
        self.is_start = False
        self.someone_win = False
        self.select_color = 1  # 玩家所执棋子颜色，默认执黑
        self.player_turn = 1  # 玩家默认先手执黑
        self.board = self.init_board()
        self.white_done = []
        self.black_done = []
        self.white_done_done = []
        self.black_done_done = []
        self.window = Tk()
        self.window.title("AI五子棋游戏")
        self.window.geometry("600x470+100+100")
        self.window.resizable(0, 0)
        self.can = Canvas(self.window, bg="green", width=470, height=470)
        self.draw_board()
        self.robot = Robot(self.board)
        self.can.grid(row=0, column=100)
        # self.window.mainloop()

    @staticmethod
    def init_board():
        """初始化抽象棋盘，二维数组"""
        # list1 = [[-1]*15]*15 此数组存在问题
        list1 = [[-1] * 15 for i in range(15)]
        return list1

    def draw_board(self):
        """绘制棋盘"""
        for i in range(0,15):
            if i == 0 or i == 14:
                self.can.create_line((25, 25 + i * 30), (445, 25 + i * 30), width=3)
                self.can.create_line((25 + i * 30, 25), (25 + i * 30, 445), width=3)
            else:
                self.can.create_line((25, 25 + i * 30), (445, 25 + i * 30), width=1)
                self.can.create_line((25 + i * 30, 25), (25 + i * 30, 445), width=1)
        self.can.create_oval(112, 112, 118, 118, fill="black")
        self.can.create_oval(352, 112, 358, 118, fill="black")
        self.can.create_oval(112, 352, 118, 358, fill="black")
        self.can.create_oval(232, 232, 238, 238, fill="black")
        self.can.create_oval(352, 352, 358, 358, fill="black")

    def select_mode(self, mode_flag):
        """模式选择"""
        if self.is_start is False:
            if mode_flag == "pvp":
                """人人对战"""
                print("zhi xing le pvp")
                self.mode = 0
            elif mode_flag == "cvp_b":
                """电脑对战人，电脑执黑"""
                print("zhi xing le cvp_b")
                self.mode = 1
                self.select_color = 0
            elif mode_flag == "cvp_w":
                """电脑对战人，电脑执白"""
                print("zhi xing le cvp_w")
                self.mode = 1
                self.select_color = 1
        else:
            return

    def select_mode1(self):
        """pvp"""
        self.select_mode("pvp")

    def select_mode2(self):
        """cvp_b"""
        self.select_mode("cvp_b")

    def select_mode3(self):
        """cvp_w"""
        self.select_mode("cvp_w")

    def pos_in_game_board(self, position):
        """找到UI棋盘中的位置"""
        return position[0] * 30 + 25, position[1] * 30 + 25

    def pos_to_draw(self, x, y):
        """返回绘制椭圆的外切矩形的两点坐标"""
        return x - 12, y - 12, x + 12, y + 12

    def draw_chess_pieces(self, position, player=None):
        """绘制已经已经下在棋盘上的棋子"""
        # print(player)
        print(position)  # position是二位数组棋盘的坐标
        _x, _y = self.pos_in_game_board(position)
        oval = self.pos_to_draw(_x, _y)
        if player == 0:
            self.can.create_oval(oval, fill="white")
            self.white_done.append([position[0], position[1], 0])
            self.board[position[0]][position[1]] = 0
        elif player == 1:
            self.can.create_oval(oval, fill="black")
            self.black_done.append([position[0], position[1], 1])
            self.board[position[0]][position[1]] = 1
        print("white_done: ", self.white_done)
        print("black_done: ", self.black_done)
        # for i in range(15):
        #     for j in range(15):
        #         print(self.board[i][j], end="  ")
        #     print("\n")

    def not_done(self, position):
        """检测二位数组中相应的点是否被下过"""
        return self.board[position[0]][position[1]] == -1

    def not_done1(self, x, y, chess):
        """检测相应的(x, y)是否已经被下过了，并且是在chess，即black_done或者white_done中"""
        if len(chess) == 0:
            return True
        flag = 0
        # point = x, y
        for p in chess:
            if p[0] == x and p[1] == y:
                flag = 1
        if flag == 1:
            return False
        else:
            return True

    @staticmethod
    def get_pos_in_board(x, y):
        """获得再二维数组棋盘中的位置"""
        return (x + 25) // 30 - 1, (y + 25) // 30 - 1

    def man_play(self, event):
        """人下棋"""
        if self.someone_win is True or self.is_start is False:
            """如果有人赢了或者还没有开始，则不能下棋"""
            return

        ex = event.x
        ey = event.y
        # print(ex, ey)
        if not (10 < ex < 460 and 10 < ey < 460):
            """如果鼠标点击在棋盘外，则不能下棋"""
            return

        pos_in_board = self.get_pos_in_board(ex, ey)
        print(pos_in_board)
        print("mode:", self.mode)
        """
            如果该点没有被下过，则就根据自己所执棋子的黑白落子，
           对手的话就根据模式的值选择人人对弈或者人机对弈
        """
        # if not self.not_done(pos_in_board):
        #     if self.select_color == 1:
        #         self.draw_chess_pieces(pos_in_board, 1)
        #     elif self.select_color == 0:
        #         self.draw_chess_pieces(pos_in_board, 0)
        #
        #     self.someone_win = self.check_someone_win()
        #
        #     if self.mode == 0:
        #         self.ai_play()
        #     elif self.mode == 1:
        #         # self.man_play()
        #         self.can.bind("<Button-1>", lambda x: self.man_play(x))
        #
        #     self.someone_win = self.check_someone_win()
        if self.someone_win is False and self.is_start is True:
            if self.not_done(pos_in_board):
                if self.mode == 0:  # 人人对弈
                    # if self.select_color == 1:
                    #     self.draw_chess_pieces(pos_in_board, 1)
                    #     self.someone_win = self.check_someone_win()
                    #     self.select_color = 0  # 之后会改参数
                    # else:
                    #     self.draw_chess_pieces(pos_in_board, 0)
                    #     self.someone_win = self.check_someone_win()
                    #     self.select_color = 1
                    print("player_turn0:", self.player_turn)
                    self.draw_chess_pieces(pos_in_board, self.player_turn)
                    print("player_turn1:", self.player_turn)
                    self.someone_win = self.check_someone_win()
                    self.player_turn = 1 - self.player_turn
                    print("player_turn2:", self.player_turn)
                else:  # 人机对弈
                    if self.select_color == 1:  # 人执黑先手
                        if self.player_turn == 1:
                            self.draw_chess_pieces(pos_in_board, 1)
                            self.someone_win = self.check_someone_win()
                            self.ai_play()
                            self.someone_win = self.check_someone_win()
                            # self.player_turn = 1
                    else:
                        if self.player_turn == 0:
                            # self.ai_play()
                            # self.someone_win = self.check_someone_win()
                            self.draw_chess_pieces(pos_in_board, 0)
                            self.someone_win = self.check_someone_win()

                            self.ai_play()
                            self.someone_win = self.check_someone_win()
                            # self.player_turn = 1
                        # else:
                            # self.ai_play()
                            # self.player_turn = 0

    def ai_play(self):
        """AI下棋"""
        # tkinter.messagebox.showinfo("ha ha ha", "hai mei you zuo chu lai")
        print("play_turn:", self.player_turn)
        if self.player_turn == 1:
            # 人执黑
            _x, _y, _z = self.robot.MaxValue_po(1, 0)
            position_in_matrix = _x, _y
            # pos = self.pos_in_game_board(position_in_matrix)
            self.draw_chess_pieces(position_in_matrix, 0)
        else:
            # if len(self.black_done) == 0 and len(self.white_done) == 0:
            #     print("dian nao zhi hei xian shou")
            #     # pos = self.pos_in_game_board((8, 8))
            #     pos = 8, 8
            #     self.draw_chess_pieces(pos, 1)  # 下在正中间 目前还不会主动执行
            #     return
            # else:
            #     _x, _y, _ = self.robot.MaxValue_po(0, 1)
            #     position_in_matrix = _x, _y
            #     # pos = self.pos_in_game_board(position_in_matrix)
            #     self.draw_chess_pieces(position_in_matrix, 1)
            _x, _y, _z = self.robot.MaxValue_po(0, 1)
            position_in_matrix = _x, _y
            print("position_in_matrix:", position_in_matrix)
            self.draw_chess_pieces(position_in_matrix, 1)


    def check_someone_win(self):
        """检查是否有人赢了"""
        if self.five_in_a_row(self.black_done):
            self.show_win_info("Black Win!!!")
            return True
        elif self.five_in_a_row(self.white_done):
            self.show_win_info("White Win!!!")
            return True
        else:
            return False

    def five_in_a_row(self, someone_done):
        """存在物五子连珠"""
        if len(someone_done) == 0:
            return False
        else:
            for row in range(15):
                for col in range(15):
                    # position = row, col
                    if ( not self.not_done1(row, col, someone_done) and
                         not self.not_done1(row + 1, col, someone_done) and
                         not self.not_done1(row + 2, col, someone_done) and
                         not self.not_done1(row + 3, col, someone_done) and
                         not self.not_done1(row + 4, col, someone_done)):
                        return True
                    elif (not self.not_done1(row, col, someone_done) and
                          not self.not_done1(row, col + 1, someone_done) and
                          not self.not_done1(row, col + 2, someone_done) and
                          not self.not_done1(row, col + 3, someone_done) and
                          not self.not_done1(row, col + 4, someone_done)):
                        return True
                    elif (not self.not_done1(row, col, someone_done) and
                          not self.not_done1(row+ +1, col + 1, someone_done) and
                          not self.not_done1(row + 2, col + 2, someone_done) and
                          not self.not_done1(row + 3, col + 3, someone_done) and
                          not self.not_done1(row + 4, col + 4, someone_done)):
                        return True
                    elif (not self.not_done1(row, col, someone_done) and
                          not self.not_done1(row + 1, col - 1, someone_done) and
                          not self.not_done1(row + 2, col - 2, someone_done) and
                          not self.not_done1(row + 3, col - 3, someone_done) and
                          not self.not_done1(row + 4, col - 4, someone_done)):
                        return True
                    else:
                        pass
        return False

    def show_win_info(self, winner):
        """提示获胜信息"""
        print(winner)
        tkinter.messagebox.showinfo("Game Over", winner)

    def draw_chess_pieces_done(self, chess):
        """在单步重置的时候画black_done和white_done中的点"""
        for p in chess:
            _x, _y = self.pos_in_game_board(p)
            oval = self.pos_to_draw(_x, _y)
            if p[2] == 0:
                self.can.create_oval(oval, fill="white")
            else:
                self.can.create_oval(oval, fill="black")

    def undo(self):
        """单步悔棋"""
        if self.someone_win is True:
            tkinter.messagebox.showinfo("Warning!", "Someone has won, Undo Is Disable")
            return

        if len(self.black_done) == 0 and len(self.white_done) == 0:
            # self.is_start = True
            return

        if len(self.black_done) > len(self.white_done):
            p = self.black_done.pop()
            # self.black_done_done.append(p)
            print(p)
            print("white_done:", self.white_done, "\n", "black_done", self.black_done)
            self.board[p[0]][p[1]] = -1
            self.player_turn = 1 - self.player_turn
            self.can.delete("all")
            self.draw_board()
            self.can.grid(row=0, column=0)
            self.draw_chess_pieces_done(self.black_done)
            self.draw_chess_pieces_done(self.white_done)
        else:
            p = self.white_done.pop()
            # self.white_done_done.append(p)
            print(p)
            print("white_done:", self.white_done, "\n", "black_done", self.black_done)
            self.board[p[0]][p[1]] = -1
            self.player_turn = 1 - self.player_turn
            self.can.delete("all")
            self.draw_board()
            self.can.grid(row=0, column=0)
            self.draw_chess_pieces_done(self.white_done)
            self.draw_chess_pieces_done(self.black_done)

    def undo_all(self):
        """重置棋盘"""
        self.board = self.init_board()
        print("undo_all:")
        # for i in range(15):
        #     for j in range(15):
        #         print(self.board[i][j], end="  ")
        #     print("\n")
        self.someone_win = False
        self.is_start = False
        self.mode = 0
        self.select_color = 1
        self.player_turn = 1
        self.white_done.clear()
        self.black_done.clear()
        self.can.delete("all")
        self.draw_board()
        self.robot = Robot(self.board)
        self.can.grid(row=0, column=0)

    def redo(self):
        """单步恢复撤销"""
        tkinter.messagebox.showinfo("Alerting", "redo disabled")

    def redo_all(self):
        """一次性恢复所有撤销"""
        tkinter.messagebox.showinfo("Alerting", "redo_all disabled")

    def start_button(self):
        """开始游戏"""
        if self.is_start is False:
            self.is_start = True
            # if self.select_color == 1:  # 我执黑
            #     if self.mode == 0:  # 人人对弈
            #         pass
            #     elif self.mode == 1:  # 人机对弈
            #         pass
            #     # self.draw_chess_pieces()
            # elif self.select_color == 0:
            #     if self.mode == 0:
            #         pass
            #     elif self.mode == 1:
            #         pass
            #     # self.draw_chess_pieces()
            if self.mode == 0:  # 人人对弈
                print("ren ren dui yi")
                # return
            elif self.mode == 1:  # 人机对弈
                print("ren ji dui yi")
                if self.select_color == 1:  # 人执黑先行
                    return
                    # self.ai_play()

                elif self.select_color == 0:  # 机器执黑先行
                    self.player_turn = 0
                    # self.man_play()
                    if len(self.black_done) == 0 and len(self.white_done) == 0:
                        print("dian nao zhi hei xian shou")
                        position_in_matrix = 7, 7
                        self.draw_chess_pieces(position_in_matrix, 1)
                    # TODO 添加AI入口，暂时不能调用self.man_play
                    return
        else:
            return

    def start(self):
        """生成各种功能按钮"""
        b1 = Button(self.window, text="Start", command=self.start_button, width=10)  # width和height的值单位是字符
        b1.place(relx=0, rely=0, x=495, y=100)

        b2 = Button(self.window, text="Undo", command=self.undo, width=10)
        b2.place(relx=0, rely=0, x=495, y=150)

        b3 = Button(self.window, text="Undo All", command=self.undo_all, width=10)
        b3.place(relx=0, rely=0, x=495, y=200)

        b4 = Button(self.window, text="Redo", command=self.redo, width=10)
        b4.place(relx=0, rely=0, x=495, y=250)

        b5 = Button(self.window, text="Redo All", command=self.redo_all, width=10)
        b5.place(relx=0, rely=0, x=495, y=300)

        """生成菜单栏，预留各种功能选项"""
        menu = Menu(self.window)
        submenu = Menu(menu, tearoff=0)
        submenu.add_command(label="New")
        submenu.add_command(label="Rule")
        submenu.add_command(label="Quit")
        menu.add_cascade(label="Game", menu=submenu)

        submenu = Menu(menu, tearoff=0)
        submenu.add_command(label="Player VS Player", command=self.select_mode1)
        submenu.add_command(label="Computer plays black", command=self.select_mode2)
        submenu.add_command(label="Computer plays white", command=self.select_mode3)
        menu.add_cascade(label="ModeSelect", menu=submenu)
        self.window.config(menu=menu)
        # 检测鼠标左键的点击动作，并且返回在canvas中的坐标值
        self.can.bind("<Button-1>", lambda x: self.man_play(x))
        self.window.mainloop()


if __name__ == "__main__":
    game = GameGo()
    game.start()