import configparser
from datetime import datetime
import pprint

import jwt  # PyJWT
import time
import requests

from machine.base_machine import Machine
from urllib.parse import urlencode

class UpbitMachine(Machine):
    """
    업비트용 거래모듈
    """
    BASE_API_URL = "https://api.upbit.com"
    currency_type = ["KRW-BTC", "KRW-ETH", "KRW-EOS", "KRW-TRX", "KRW-NEO", "KRW-XRP", "KRW-ADA", "KRW-ELF", "KRW-BCH", "KRW-XLM", "KRW-QTUM", "KRW-ADT", "KRW-STORM", "KRW-ETC", "KRW-SNT", "KRW-STEEM", "KRW-DASH", "KRW-BTG", "KRW-XMR", "KRW-GAS", "KRW-STRAT"]

    def __init__(self):
        """
        config.ini에 client_id,client_secret,username,password 정보를 읽어옴
        """
        config = configparser.ConfigParser()
        config.read('conf/config.ini')
        self.CLIENT_ID = config['UPBIT']['client_id']
        self.CLIENT_SECRET = config['UPBIT']['client_secret']
        self.USER_NAME = config['UPBIT']['username']
        self.USER_PASSWORD = config['UPBIT']['password']
        self.access_token = None
        self.refresh_token = None
        self.token_type = None
        self.query=None
        self.exchange_token=None


    def set_token(self,grant_type="password"):
        """
        거래하기위한 토큰을 생성

        returns :
            토큰을 반환

        """
        payload = {
            'access_key': self.CLIENT_ID,
            'nonce': int(time.time() * 1000),
        }
        if self.query is not None:
            payload['query'] = urlencode(self.query)

        jwt_token = jwt.encode(payload, self.CLIENT_SECRET, algorithm='HS256').decode('utf-8')
        self.access_token = 'Bearer {}'.format(jwt_token)
        return self.access_token

    def get_token(self):
        """
            토큰이 있으면 반환
        Return :
            액세스토큰 asscess_token이 있는경우반환합니다
        Rises:
            토큰이 없으면 발생
        """
        if self.access_token is not None:
            return self.access_token
        else:
            raise Exception("Need to set_token")

    def get_ticker(self,currency_type=None):
        """
            마지막 체결정보를 구함
        Args:
            currency_type 화폐종류 입력

        Returns:
            결과를 딕셔너리로 반환
            결과필드는 timestamp,last,bid,ask,high,low,volume으로 구성
        Raise:
            currency_type이 없으면 예외처리
        """
        if currency_type is None:
            raise Exception('Need to currency type')
        params={"markets":currency_type}
        ticker_api_path = "/v1/ticker"
        url_path = self.BASE_API_URL + ticker_api_path

        res_ticker = requests.get(url_path, params=params)
        response = res_ticker.json()[0]
        return response

    def get_now_price(self,currency_type=None):
        """
            마지막 체결정보를 구함
        Args:
            currency_type 화폐종류 입력

        Returns:
            결과를 딕셔너리로 반환
            결과필드는 timestamp,last,bid,ask,high,low,volume으로 구성
        Raise:
            currency_type이 없으면 예외처리
        """
        if currency_type is None:
            raise Exception('Need to currency type')
        time.sleep(1)
        params={"markets":currency_type}
        ticker_api_path = "/v1/ticker"
        url_path = self.BASE_API_URL + ticker_api_path

        res_ticker = requests.get(url_path, params=params)
        response = res_ticker.json()[0]
        return response["trade_price"]
        

    def get_filled_orders(self , currency_type , per="minute"):
        """
            가장 최근 체결정보를 구하는 메서드입니다.
        Args:
            currency_type(str) : 화폐종류 입력
            per(str): 체결시간 정보를 설정합니다. 형식 : [HHmmss 또는 HH:mm:ss]
        Returns:
            최근 체결정보를 딕셔너리의 리스트형태로 반환합니다.
        """

        if currency_type is None:
            raise Exception("Need to currency_type")
        params={'market':currency_type , 'time':per}
        orders_api_path="/v1/trades/ticks"
        url_path=self.BASE_API_URL+orders_api_path
        res = requests.get(url_path,params=params)
        result = res.json()
        return result

    def get_candles_data(self, currency_type, term = 5 , count = 20):
        """
            가장 최근 체결정보를 구하는 메서드입니다.
        Args:
            currency_type(str) : 화폐종류 입력
            term : 산출하려는 시간
            count : candle의 갯수

        Returns:
            최근 체결정보를 딕셔너리의 리스트형태로 반환합니다.
        """

        if currency_type is None:
            raise Exception("Need to currency_type")

        orders_api_path = "/v1/candles/minutes/"
        url_path = self.BASE_API_URL + orders_api_path + str(term)
        params = {'market': currency_type, "count": str(count)}
        res = requests.get(url_path, params=params)
        result_array = res.json()
        return result_array

    def get_wallet_status(self):
        """
            사용자의.지갑정보를.조회하는.메서드입니다

        Returns:
            사용자의.지갑에.화폐별.잔액을.딕셔너리.형태로.반환합니다.
        """
        #time.sleep(1)
        wallet_status_api_path="/v1/accounts"
        url_path=self.BASE_API_URL+wallet_status_api_path
        headers=self.get_headers()
        res=requests.get(url_path, headers=headers)
        result=res.json()
        return result
    def get_All_balance(self,):
        """
            전재산

        Returns:
            사용자의.지갑에.화폐별.잔액을.딕셔너리.형태로.반환합니다.
        """
        #time.sleep(1)
        wallet_status_api_path="/v1/accounts"
        url_path=self.BASE_API_URL+wallet_status_api_path
        headers=self.get_headers()
        res=requests.get(url_path, headers=headers)

        r=res.json()
        sum=0
        for result in r:
            if(result["currency"]=="KRW"):
                sum+=float(result['balance'])
            else:
                result["currency"]="KRW-"+result["currency"]
                now_price = self.get_ticker(currency_type=result["currency"])["trade_price"]
                val=now_price*float(result["balance"])
                sum+=val
        return sum

    def get_coin_list(self,):
        """
            가지고있는 코인 리스트

        Returns:
            사용자의.지갑에.화폐별.잔액을.딕셔너리.형태로.반환합니다.
        """
        #time.sleep(1)
        wallet_status_api_path = "/v1/accounts"
        url_path = self.BASE_API_URL + wallet_status_api_path
        headers = self.get_headers()
        res = requests.get(url_path, headers=headers)
        result = res.json()
        list=[]
        for res in result:
            if (float(res["balance"])*float(res["avg_krw_buy_price"]))<500 or res["currency"]=="KRW":
                pass
            else :
                list.append("KRW-"+res["currency"])
        return list

    def get_has_coin_info_list(self,):
        """
            가지고있는 코인 리스트

        Returns:
            사용자의.지갑에.화폐별.잔액을.딕셔너리.형태로.반환합니다.
        """
        coin_info_list=[]

        result=self.get_wallet_status()

        for item in result:
            info = {}
            if item["currency"]=="KRW":
                pass
            else:
                info["balance"]=item["balance"]
                info["price"]=item["avg_krw_buy_price"]
                info["market"]=("KRW-"+item["currency"])
                coin_info_list.append(info)
        return coin_info_list

    def get_has_coin_info(self, currency_type=currency_type):
        """
            가지고있는 코인 리스트
        Returns:
            사용자의.지갑에.화폐별.잔액을.딕셔너리.형태로.반환합니다.
        """
        result = self.get_wallet_status()
        for item in result:
            info = {}
            if item["currency"] == "KRW":
                pass
            else:
                info["balance"] = item["balance"]
                info["price"] = item["avg_krw_buy_price"]
                info["market"] = ("KRW-" + item["currency"])
                if(info["market"]==currency_type):
                    return info



    def get_coin_valume(self,currency_type=None):
        """
            코인의 volume을 출력

        Returns:
            사용자의.지갑에.화폐별.잔액을.딕셔너리.형태로.반환합니다.
        """
        # time.sleep(1)
        wallet_status_api_path = "/v1/accounts"
        url_path = self.BASE_API_URL + wallet_status_api_path
        headers = self.get_headers()
        res = requests.get(url_path, headers=headers)

        result = res.json()
       # print(result)
        for res in result:
            if (res["currency"] == "KRW"):
                pass
            else:
                str =currency_type.split("-")
                if(res["currency"]==str[1]):
                    return res["balance"]

    def get_free_balance(self):
        """
            현금조회

        Returns:
            사용자의.지갑에.화폐별.잔액을.딕셔너리.형태로.반환합니다.
        """
        wallet_status_api_path="/v1/accounts"
        url_path=self.BASE_API_URL+wallet_status_api_path
        headers=self.get_headers()
        res=requests.get(url_path, headers=headers)
        result=res.json()

        for res in result:
       #     print(result)
            if(res["currency"]=="KRW"):
                return res["balance"]

    def order(self , currency_type=None, price=None , qty=None, side = None , ord_type="limit"):
        """
            매수 매도 주문

        Note:
            화폐종류마다.최소주문수량은.다를수있습니다.
            이메서드는.지정가거래만.지원합니다.

        Args:함
            currency_type(str):화폐의 종류
            price(str):1개 수량주문에 해당하는.원화(krw)값
            qty(str):주문수량입니다.
            side(str): bid ask정

        Returns:
            주문의 상태를 반환합니다.
        """
        #self.set_token()  # 꼼수로해놓음.
        #time.sleep(1)
        #print(currency_type,price,qty)
        if currency_type is None or price is None or qty is None:
            raise Exception("Need to param")
        buy_order_api_path = "/v1/orders"
        url_path = self.BASE_API_URL + buy_order_api_path
        #data = self.get_data(currency_type=currency_type, price=price, qty=qty, side=side,ord_type=ord_type)
        data={"market":currency_type,"side":side,"volume":str(qty),"price":str(price),"ord_type":ord_type}
        headers = self.get_headers(query=data)
        res = requests.post(url_path, headers=headers,data=data)
        result = res.json()
        return result

    def get_nonce(self):
        return str(int(time.time()))

    def get_token(self,query=None):
        payload = {
            'access_key': self.CLIENT_ID,
            'nonce': int(time.time() * 1000),
        }
        if query is not None:
            #print(query)
            payload['query'] = urlencode(query)

        return jwt.encode(payload, self.CLIENT_SECRET, algorithm='HS256').decode('utf-8')

    def get_data(self,currency_type=None, price=None, qty=None, ord_type="limit", side=None):
        return {"market":currency_type,
                "side": side,
                "volume": qty,
                "price": price,
                "ord_type": ord_type,
                }

    def get_headers(self,query=None):
        headers={'Authorization':'Bearer %s' % self.get_token(query=query)}
        return headers

    def cancel_order(self,order_id=None):
        """취소주문을 실행하는 메서드 입니다.

        Args:
            order_id(str):취소주문하려는 주문의 ID

        Returns:
            주문의 상태를 반환
        """

        query={"uuid":order_id}
        if order_id is None:
            raise Exception("Need to params")
        cancel_order_api_path="/v1/order"
        url_path=self.BASE_API_URL + cancel_order_api_path
        headers=self.get_headers(query)
        res = requests.delete(url_path, headers=headers, data=query)
        result = res.json()
        time.sleep(1)
        return result

    def get_my_order_wait_list(self,):
        """
        
        :param currency_type: 
        :return:해당 마켓의 오더리스트들을 뽑아온다 [] 배열로받아옴
        """

        list_transaction_api_path= "/v1/orders"
        url_path= self.BASE_API_URL + list_transaction_api_path
        #params={}
        headers=self.get_headers()#params)# 주문중인 전부다 뽑아옴
        res = requests.get(url_path, headers=headers)#, data=params)
        result=res.json()
        return result

    def get_my_order_status(self,  uuid=None):
        """사용자의 주문 상세 정보를 조회하는 메서드입니다.

        Args:
            currency_type(str): 화폐 종류
            order_id(str): 거래 ID

        Returns:
            order_id에 해당하는 주문의 상세 정보를 반환합니다.
        """
        if  uuid is None:
            raise Exception("Need to  order id")
        #time.sleep(1)
        list_transaction_api_path= "/v1/order"
        url_path= self.BASE_API_URL + list_transaction_api_path
        params={"uuid": uuid }
        headers=self.get_headers(params)
        res = requests.get(url_path, headers=headers, data=params)
        result=res.json()
        return result

    def get_disparity(self, currency_type=None, term=5, count=20):
        """
        currency_type : 화폐 종류
        term : 산출하려는 시간
        count : 이동평균선 기준 시간
        return : 이격도 출력
        """
        if currency_type is None:
            raise Exception("Need to currency_type")
        #time.sleep(1)
        orders_api_path="/v1/candles/minutes/"
        url_path=self.BASE_API_URL+orders_api_path+str(term)
        params = {'market': currency_type, "count": str(count)}
        res = requests.get(url_path, params=params)
        result_array = res.json()
        current_price=result_array[0]["trade_price"]

        sum=0
        for item in result_array:
            sum+=item["trade_price"]

        moving_average = sum / 20
        return ((current_price/moving_average)-1)*100

    def get_bollingerband(self, currency_type=None, term=5, count=20):
        """
        currency_type : 화폐 종류
        term : 산출하려는 시간
        count : 이동평균선 기준 시간
        return : 중심선과 상한선 하한선 high,low,mid의 dict로 출력
        """
        if currency_type is None:
            raise Exception("Need to currency_type")
        #time.sleep(1)
        orders_api_path = "/v1/candles/minutes/"
        orders_api_path = "/v1/candles/minutes/"
        url_path = self.BASE_API_URL + orders_api_path + str(term)
        params = {'market': currency_type, "count": str(count)}
        res = requests.get(url_path, params=params)
        result_array = res.json()
        sum = 0
        bollingerband_value=0
        for item in result_array:
            sum += item["trade_price"]


        moving_average = sum / 20
        for item in result_array:
            bollingerband_value += abs(moving_average-item["trade_price"])

        result = {"mid": moving_average,"high":moving_average+(bollingerband_value*2),"low":moving_average-(bollingerband_value*2) }
       # pprint.pprint(result)
        return result