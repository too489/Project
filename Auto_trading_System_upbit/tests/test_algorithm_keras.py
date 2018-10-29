import unittest
import requests
import pprint
from machine.upbit_machine import UpbitMachine
from Algorithm.tensorflow_algorithm_keras import tensorflow_algorithm_keras
from Algorithm.tensorflow_algorithm import tensorflow_algorithm

class Algorithm_test(unittest.TestCase):

    def setUp(self):
        self.upbit_machine=UpbitMachine()

    def test_algorithm(self) -> None :
        # pprint.pprint(tensorflow_algorithm(currency_type="KRW-BTC",term=10,count=500)[0])
        print("리턴된값 : ", tensorflow_algorithm_keras(currency_type="KRW-BTC", term=10, count=1000,view=1))

