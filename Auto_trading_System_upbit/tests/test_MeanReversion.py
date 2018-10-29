import unittest
from machine.upbit_machine import UpbitMachine
from Algorithm.MeanReversion import MeanReversionModel


class test_MeanReversion(unittest.TestCase):

    def setUp(self):
        self.upbit_machine=UpbitMachine()

    def test_meanReversion(self) -> None :
        print(MeanReversionModel())

