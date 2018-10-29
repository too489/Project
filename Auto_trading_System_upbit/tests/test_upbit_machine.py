import unittest
import requests
import pprint
from machine.upbit_machine import UpbitMachine
import inspect

class UpbitMachineTestCase(unittest.TestCase):

    def setUp(self):
        self.upbit_machine=UpbitMachine()


    def tearDown(self):
        pass

    def test_set_token(self) -> None:
        # print(inspect.stack()[0][3])
        access_token=self.upbit_machine.set_token(grant_type="password")
        assert access_token
        # print("Access_token:",access_token)

        params = {'Authorization': access_token}
        result = requests.get('https://api.upbit.com/v1/accounts', headers=params)
        # print("it's count  balanece", result.json())

    def test_get_token(self) -> None:
        self.upbit_machine.set_token(grant_type="password")
        access_token=self.upbit_machine.get_token()
        assert access_token
        # print("get_Access_token:",access_token)

    def test_get_ticker(self):
        pass
        # print(inspect.stack()[0][3])
        # ticker=self.upbit_machine.get_ticker("krw-btc")
        # assert ticker
        # pprint.pprint(ticker)

    def test_get_filled_orders(self):
        pass
        # order_book=self.upbit_machine.get_filled_orders(currency_type="krw-btc")
        # pprint.pprint(order_book)
        # pprint.pprint('출력되나?')
        # test=self.upbit_machine.get_disparity(currency_type="KRW-BTC")
        # pprint.pprint(test)

    def test_get_wallet_status(self):
        pass
        # print(inspect.stack()[0][3])
        # wallet_status=self.upbit_machine.get_wallet_status()
        # assert wallet_status
        # pprint.pprint(wallet_status)

    # def test_buy_order(self):
    #     print(inspect.stack()[0][3])
    #     buy_order = self.upbit_machine.buy_order(currency_type="KRW-ETH", price="15000", qty="1", order_type="limit")
    #     assert buy_order
    #     print(buy_order)
    #
    # def test_sell_order(self):
    #     print(inspect.stack()[0][3])
    #     sell_order=self.upbit_machine.sell_order(currency_type="KRW-BTC",price="4000",qty="1",order_type="limit")
    #     assert sell_order
    #     print(sell_order)

    # def test_get_nonce(self):
        # print(inspect.stack()[0][3])
        # nonce=self.upbit_machine.get_nonce()
        # assert nonce
        # print(nonce)
    # def test_cancel_order(self):
    #     print(inspect.stack()[0][3])
    #     cancel_order = self.upbit_machine.cancel_order(currency_type="KRW-BTC", order_id="5064611")
    #     assert cancel_order
    #     print(cancel_order)

    def test_get_myorder_status(self):
        pass
        # print('여기야 여기 ')
        # result=self.upbit_machine.get_ticker(currency_type="KRW-BTC")
        # print(result['trade_price'])
        # my_order= self.upbit_machine.get_my_order_wait_list()
       # assert my_order
       #  for var in my_order:
       #      print(var["uuid"])
       #  print(my_order)
      #      print('마무리는 여기')
        my_order=self.upbit_machine.get_coin_valume("KRW-RFR")
        #my_order=self.upbit_machine.get_has_coin_info_list()

        print(my_order)
    # cancel=self.upbit_machine.cancel_order("4f0331aa-ac02-4489-80e3-333dc3143dc2")
       # print(my_order)

    # def test_value(self):
    #     test=self.upbit_machine.get_bollingerband(currency_type="KRW-BTC")
    #     pprint.pprint(test)

    # def test_check_ordered_state(self):
    #     self.steptrade.check_ordered_state()
