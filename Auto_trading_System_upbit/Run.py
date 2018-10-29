import multiprocessing
from multiprocessing import Process,Queue
import sys
import threading
import time
from datetime import datetime
from PyQt5.QtCore import pyqtSlot
from PyQt5.QtWidgets import QApplication, QWidget, QDialog, QMainWindow
from PyQt5 import uic
from machine.upbit_machine import UpbitMachine
from Algorithm.tensorflow_algorithm_keras import tensorflow_algorithm_keras
from Algorithm.tensorflow_algorithm import tensorflow_algorithm
from strategy.step_trade import StepTrade
from pusher.slack import PushSlack


class Run(QMainWindow,):
    def __init__(self):

        super(Run,self).__init__()
        uic.loadUi('Auto-trading.ui',self)
        self.machine=UpbitMachine()
        self.setWindowTitle("Auto-trading")
        self.trader = None
        self.Start_Button.clicked.connect(self.on_Start_clicked)
        if(self.Combo_Box_minute.currentText()==" "):
            self.Start_Button.setEnabled(False)
        self.Stop_Button.clicked.connect(self.on_Stop_clicked)
        self.Refresh.clicked.connect(self.load_info)
        self.Setting.clicked.connect(self.Set_minute)
        self.Predict_value_cal.clicked.connect(self.get_Item)
        self.Assets.setText(str(int(self.machine.get_All_balance())))
        self.q=Queue()
        self.ql=Queue()
        self.ass=self.machine.get_All_balance()
        self.first_balance=self.machine.get_All_balance()
        self.term=10
        self.Hope_coin_list=None
        self.pusher = PushSlack()
        self.setinel=1



    @pyqtSlot()
    def on_Start_clicked(self):
        self.Assets.setText(str(int(self.machine.get_All_balance())))
        self.Profit.setText(str(100 - (float(self.ass) / float(self.first_balance)) * 100) + "%")
        self.Start_Button.setEnabled(False)
        self.trader=multiprocessing.Process(target=StepTrade().run,args= (self.term,self.q,self.ql,))
        self.trader.start()
        self.Log_Text.appendPlainText("자동매매 프로그램이 실행되었습니다")

    @pyqtSlot()
    def on_Stop_clicked(self):
        self.trader.terminate()
        self.trader.join()
        self.Start_Button.setEnabled(True)

    @pyqtSlot()
    def Set_minute(self):
        self.Start_Button.setEnabled(True)
        item = self.Combo_Box_minute.currentText()
        item = item.split(" ")
        self.term = item[0]

    @pyqtSlot()
    def get_Item(self):
        self.Log_Text.appendPlainText("잠시만 기다려 주세요.")
        self.Log_Text.appendPlainText("예측까지 5초정도 걸립니다")
        item=self.Combo_Box.currentText()
        item=item.split("-")
        item="KRW-"+item[0]
        self.Predict_Value_Label.setText(str(float(tensorflow_algorithm_keras(currency_type=item,view=1,term=self.term))))
        self.Now_Value_Label.setText(str(int(self.machine.get_now_price(currency_type=item))))


    # @pyqtSlot()
    # def check(self,):
    #     while(1):
    #         self.free_balance = self.machine.get_free_balance()
    #         self.Assets.setText(str(int(self.machine.get_All_balance())))
    #         self.Profit.setText(str(100-(float(self.free_balance)/float(self.first_balance))*100)+"%")
    #         self.Hope_coin_list = StepTrade().get_hopeful_coin()  # 종목선정
    #         self.Coin_Collections.appendPlainText(str(datetime.now()))
    #         for info in self.Hope_coin_list:
    #             self.Coin_Collections.appendPlainText(info)
    #         time.sleep(60*self.term)
    @pyqtSlot()
    def load_info(self):
        self.ass=self.machine.get_All_balance()
        self.Assets.setText(str(int(self.ass)))
        self.Profit.setText(str(100 - round((float(self.ass) / float(self.first_balance)),2) * 100) + "%")
        self.Coin_Collections.appendPlainText(str(datetime.now()))

        if  self.q.empty() :
            pass
        else:
            for data in self.q.get():
                self.Log_Text.appendPlainText(data)
        if  self.ql.empty() :
            self.Hope_coin_list = StepTrade().get_hopeful_coin(term=self.term, ql=self.ql)  # 종목선정
            for info in self.Hope_coin_list:
                self.Coin_Collections.appendPlainText(info)
        else :
            for data1 in self.ql.get():
                self.Coin_Collections.appendPlainText(data1)




app=QApplication(sys.argv)
widget=Run()
widget.show()
sys.exit(app.exec_())

