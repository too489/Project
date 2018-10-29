import multiprocessing
from multiprocessing import Process,Pipe
import sys
import threading
import time
from datetime import datetime
from PyQt5.QtCore import pyqtSlot
from PyQt5.QtWidgets import QApplication, QWidget, QDialog, QMainWindow
from PyQt5 import uic
from machine.upbit_machine import UpbitMachine
from Algorithm.tensorflow_algorithm_keras import tensorflow_algorithm_keras
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
        self.Setting.clicked.connect(self.Set_minute)
        self.Predict_value_cal.clicked.connect(self.get_Item)
        self.Assets.setText(str(int(self.machine.get_All_balance())))
        self.free_balance=self.machine.get_free_balance()
        self.first_balance=self.machine.get_free_balance()
        self.parent_conn,self.child_conn=Pipe()
        self.term=10
        self.Hope_coin_list=None
        self.pusher = PushSlack()



    @pyqtSlot()
    def on_Start_clicked(self):

        self.Start_Button.setEnabled(False)
        self.trader=threading.Thread(target=self.roof,args= (self.Coin_Collections,))
        self.trader.start()
        self.Log_Text.appendPlainText("시작")



    @pyqtSlot()
    def on_Stop_clicked(self):

        self.trader.join(timeout=5)
        self.Start_Button.setEnabled(True)

    @pyqtSlot()
    def Set_minute(self):
        self.Start_Button.setEnabled(True)
        item = self.Combo_Box_minute.currentText()
        item = item.split(" ")
        self.term = item[0]

    @pyqtSlot()
    def get_Item(self):
        item=self.Combo_Box.currentText()
        item=item.split("-")
        item="KRW-"+item[0]
        self.Log_Text.appendPlainText("잠시만 기다려 주세요.")
        self.Log_Text.appendPlainText("예측까지 5초정도 걸립니다")
        self.Predict_Value_Label.setText(str(int(tensorflow_algorithm_keras(currency_type=item,view=1,term=self.term))))
        self.Now_Value_Label.setText(str(int(self.machine.get_now_price(currency_type=item))))


    @pyqtSlot()
    def roof(self,Coin_Collections):
        self.pusher.send_message("#general", "가상화폐 자동매매 프로그램이 실행되었습니다")
        while(1):
            self.free_balance = self.machine.get_free_balance()
            self.Assets.setText(str(int(self.machine.get_All_balance())))
            print(self.free_balance,self.first_balance)
            self.Profit.setText(str(100-(float(self.free_balance)/float(self.first_balance))*100)+"%")
            self.Hope_coin_list = StepTrade().get_hopeful_coin()  # 종목선정
           # Coin_Collections.clear()
            self.Coin_Collections.appendPlainText(str(datetime.now()))
            for info in self.Hope_coin_list:
                Coin_Collections.appendPlainText(info)
            StepTrade().run(term=self.term, Log_Text=self.Log_Text,Hope_coin_list=self.Hope_coin_list,free_balance=self.free_balance)
            time.sleep(60*self.term)

app=QApplication(sys.argv)
widget=Run()
widget.show()
sys.exit(app.exec_())

