from datetime import datetime
import multiprocessing
import traceback

from Algorithm.tensorflow_algorithm_keras import tensorflow_algorithm_keras
from Algorithm.MeanReversion import MeanReversionModel
from logger import get_logger
from strategy.base_strategy import Strategy
from machine.upbit_machine import UpbitMachine
from pusher.slack import PushSlack
logger = get_logger("step_trade")
import time


class StepTrade(Strategy):
    def __init__(self,):
        self.pusher = PushSlack()

        self.machine=UpbitMachine()
        self.currency_type=self.machine.currency_type
        self.compare_disparity=None
        self.now_price = None
        self.order_balance=20000#float(self.machine.get_free_balance()) / 4# 총보유현금 4등분
        self.free_balance=self.machine.get_free_balance()
        self.term=5
        self.Log_Text=None

        logger.info(self.currency_type)

    def run(self,term=10,queue=None,queue_list=None):
        self.pusher.send_message("#general", "가상 화폐 자동매매 프로그램이 실행되었습니다")
        self.term = term
        while(1):
            self.check_my_order(queue=queue)
            print("다시분석중")
            Hope_coin_list = StepTrade().get_hopeful_coin(term=term,ql=queue_list)  # 종목선정
            buy_processes = [multiprocessing.Process(target=self.buy_trading_logic,args=(arg,queue)) for arg in Hope_coin_list]
            sell_processes = [multiprocessing.Process(target=self.sell_trading_logic, args=(arg,queue)) for arg in self.machine.get_coin_list()]
            for p1 in buy_processes[:4]:
                p1.start()
            for p in buy_processes[:4]:
                p.join()
            time.sleep(60)
            for p2 in buy_processes[4:]:
                p2.start()
            time.sleep(10)
            for p2 in buy_processes[4:]:
                p2.join()
            for p3 in sell_processes:
                p3.start()
            for p3 in sell_processes:
                p3.join()
            print("다음 term 기다리는중",int(self.term),"분 기다리세요")
            time.sleep(int(self.term) * 60)

    def check_my_order(self,queue=None):
        date=[]
        assets=int(self.my_all_assets(machine=self.machine))
        self.check_ordered_state(queue=queue)
        self.pusher.send_message("#general", str(datetime.now())+" 현재 자산 :" + str(assets)+"원 입니다")
        date.append(str(datetime.now()) + " 현재 자산 :" + str(assets) + "원 입니다")

        self.pusher.send_message("#general", "그 중 거래 가능 현금 :" + str(self.free_balance) + "원 입니다")
        date.append("그 중 거래 가능 현금 :" + str(self.free_balance) + "원 입니다")
        queue.put(date)
        #self.check_completed()
        self.check_keep_ordered(queue=queue)

    def check_ordered_state(self,queue=None):
        DB_order_list = self.DB_order_list()
        print(DB_order_list)
        for list in DB_order_list:
            # print(list["uuid"])
            item = self.machine.get_my_order_status(uuid=list["uuid"])  # 구매 리스트를 불러옴 단 딱히 market을 지정하지 않음 전부다 조회하기 위해서 !!!나중에 페이지를 넓히던 방법 강구해야됨
            logger.info(item)#로그파일저장분
            # print(item)
            if (item.get('error')):
                pass
            else:
                # print("여기출력!!!!!!!!!!")
                # print(item['uuid'])
                if item["state"]=="done" :#만약 디비에 wait되어 있던 게 완료되었으면 디비로 저장
                    order_result_dict = item
                    real_amount = float(order_result_dict["executed_volume"])#거래량
                    real_value = float(order_result_dict["avg_price"])#평균 구매가격
                    created_at = float(order_result_dict["created_at"]/1000)#구매시간
                    fee = float(order_result_dict["paid_fee"])# 수수료비율
                    self.update_trade_status(item_id={"uuid":item["uuid"]},
                                             value={"status":"done",
                                                    "real_amount":real_amount,
                                                    "created_at":created_at,
                                                    "real_value":real_value,
                                                    "real_fee":fee,
                                                    "side":item["side"]
                                                            })
                    self.pusher.send_message("#general","completed:" + item["side"] + str(item))#이상없
                    queue.put("completed:" + item["side"] + str(item))#이상없

                elif  item["state"]=="wait" :
                    if item["side"]=="bid":#아직 wait라면
                        if float(item["price"])*1.05 <= self.machine.get_now_price(currency_type=item["market"]) : #체크값
                            logger.info("CancelOrder")
                            logger.info(item)
                            try:
                                self.order_cancel_trasaction(machine=self.machine, item=item)
                            except:
                                error = traceback.format_exc()
                                logger.info(error)
                                self.update_trade_status( item_id={"uuid": item["uuid"]}, value={"transaction": "failed"})
                                print("구매주문 취소")
                                self.pusher.send_message("#general", "해당 코인의 가격이 더 올라 취소되었습니다. 추격매수 말고 기다려주세요"+ str(item))
                                queue.put("해당 코인의 가격이 더 올라 취소되었습니다. 추격매수 말고 기다려주세요"+ str(item))

                    elif item["side"]=="ask":
                        if (item.get('price')):
                            if float(item["price"]) <self.machine.get_now_price(currency_type=item['market']) * 1.05:
                                self.order_cancel_trasaction(machine=self.machine, item=item)
                                #self.update_trade_status(db_handler=self.db_handler, item_id={"uuid": item["uuid"]}, value={"status": "wait"})
                                print("판매주문 취소")
                                self.pusher.send_message("#general", "해당 코인의 가격이 너무 내려 매도 주문이 취소되었습니다, 손절을 추천드립니다" + str(item))
                                queue.put("해당 코인의 가격이 너무 내려 매도 주문이 취소되었습니다, 손절을 추천드립니다" + str(item))
                else :
                    self.update_trade_status( item_id={"uuid": item["uuid"]},value={"status": "CANCEL_ORDERED"})

    def check_completed(self):#굳이 있을 필요가 있나
        DB_order_list = self.DB_order_list(state="done")
        logger.info("ORDER_COMPELETED")
        for item in DB_order_list:
            # print(item)
            logger.info(item)
            try:
                self.order_transaction(machine=self.machine,  item=item, side= item["side"])
                self.pusher.send_message("#general",item["side"]+"ordered : "+str(item))
                # self.Log_Text.appendPlainText(item["side"]+"ordered : "+str(item))
            except:
                error= traceback.format_exc()
                logger.info(error)
                if (item.get('uuid')):
                    self.update_trade_status(item_id={"uuid":item["uuid"]}, value={"transactions":"failed"})

    def get_hopeful_coin(self,term=None,ql=None):#평균회귀 평가모델로 뽑아온 coin목록을 db에넣어
        date =[]
        result = MeanReversionModel(term=term)
        for coin in result:
            date.append(coin)
            self.Hope_List_Insert(result=coin)
        self.currency_type = result
        ql.put(date)
        #print(self.currency_type)
        return result

    def check_keep_ordered(self,queue=None): #여기가 손익라인 #5프로 정도로 한다
        has_coin_list=self.machine.get_has_coin_info_list()
        date=[]
        for item in has_coin_list:
            now_price=self.machine.get_now_price(currency_type=item["market"])
            #print(item['market'])
            if  float(item["price"]) * 1.05 < now_price and float(item["price"]) * 1.05>1000:#수익라인
                self.order_transaction(machine=self.machine,
                                            currency_type=item["market"], side='ask',qty=item["balance"],price=now_price)
                self.pusher.send_message("#general", "보유 중인 "+str(item["market"])+"코인을 수익 매도 하였습니다. info : "+str(item))
                logger.info("sell order from keeped" + str(item["uuid"]))
                date.append("보유 중인 "+str(item["market"])+"코인을 수익 매도 하였습니다. info : "+str(item))
                queue.put(date)

            elif float(item["price"]) *0.95 > now_price and float(item["price"]) * 1.05>1000:#손절라인
                self.order_transaction(machine=self.machine,
                                       currency_type=item["market"],  side='ask',qty=item["balance"],price=now_price)
                self.pusher.send_message("#general", "보유 중인 "+str(item["market"])+"코인을 손절 매도 하였습니다. info : "+str(item))
                date.append("보유 중인 "+str(item["market"])+"코인을 손절 매도 하였습니다. info : "+str(item))
                queue.put(date)
                logger.info(str(item["market"])+"을 매도 하였습니다 " )

    def set_thread_price(self,currency_type = None):

        coin_type=currency_type
    #for coin_type in currency_type:
        price_info = {}
        price_info['market'] = coin_type
        price_info['pridict_price']=tensorflow_algorithm_keras(term=self.term,count=100,currency_type=coin_type)
        bollingerband=self.machine.get_bollingerband(term=self.term,count=20,currency_type=coin_type)
        price_info['bolin_high']=bollingerband['high']
        price_info['bolin_mid'] = bollingerband['mid']
        price_info['bolin_low'] = bollingerband['low']
        price_info['disparity'] = self.machine.get_disparity(term=self.term, count=20, currency_type=coin_type)
        price_info['now_price'] = self.machine.get_now_price(currency_type=coin_type)
        return(price_info)

        # time.sleep(300)

    def buy_trading_logic(self, currency_type=None,queue=None):
        if currency_type is None :
            raise Exception("I have to need info")
        date=[]
        print("구매로직 진입")
        print(currency_type)
        term = self.term
        info = self.set_thread_price(currency_type=currency_type)
        wallet = self.free_balance
        if(float(wallet) > self.order_balance):
            count=0

            if(float(info["pridict_price"])>float(info['now_price'])):
                count+=1
            if(float(info["disparity"])<-1):
                disparity = float(info["disparity"])
                count+=1
            if(float(info["bolin_low"])>float(info['now_price'])):
                count+=1
            if(count>=2):
                print("구매 검토 중")
                time.sleep(int(term) * 60)
                while(1):
                    if(float(self.machine.get_disparity(currency_type=info["market"],term=self.term))>disparity):
                        wallet=self.machine.get_free_balance()
                        now_price=self.machine.get_now_price(currency_type=info["market"])
                        if float(wallet) >= self.order_balance:
                            volume=(self.order_balance)/float(now_price)
                            self.order_transaction(machine=self.machine, qty=volume*0.98, currency_type=info["market"], side="bid", price=now_price)
                            time.sleep(int(term) * 60)
                            self.check_ordered_state()
                            self.pusher.send_message("#general","현재" + str(info["market"]) + "매수 하였습니다 info : " + str(info))
                            date.append("현재" + str(info["market"]) + "매수 하였습니다 info : " + str(info))
                            queue.put(date)
                            self.free_balance = self.machine.get_free_balance()
                            logger.info("buy transaction")
                        else :
                            print("돈없어서 pass")
                            date.append("보유 중인 금액이 부족하여 구매에 실패하였습니다")
                            queue.put(date)
                            self.free_balance = self.machine.get_free_balance()
                        break
                    disparity = float(self.machine.get_disparity(currency_type=info["market"], term=self.term))
                    print("매수 시점 기다리는 중")
                    time.sleep(int(term) * 60)
                    self.check_ordered_state()

    def sell_trading_logic(self, currency_type=None,queue=None):
        if currency_type is None :
            raise Exception("I have to need info")
        date=[]
        print("판매 로직 진입")
        print(currency_type)
        term = self.term
        #info 는 가지고 있는 코인 리스트
        has_coin_info=self.machine.get_has_coin_info()
        print("판매 위해 가지고 있는 코인들 조회")
        evalueation_coin=self.set_thread_price(currency_type=currency_type)
        #print(evalueation_coin)
        count = 0
        if (float(evalueation_coin["pridict_price"]) < float(evalueation_coin['now_price'])):
            count += 1
        if (float(evalueation_coin["disparity"]) > 1):
            disparity = float(evalueation_coin["disparity"])
            count += 1
        if (float(evalueation_coin["bolin_high"]) < float(evalueation_coin['now_price'])):
            count += 1
        if (count >= 2):
            print("판매 검토중")
            time.sleep(int(term) * 60)
            now_price = self.machine.get_now_price(currency_type=evalueation_coin["market"])
            while(1):
                if (float(self.machine.get_disparity(currency_type=evalueation_coin["market"], term=self.term)) < disparity):
                    volume = self.machine.get_coin_valume(evalueation_coin["market"])
                    self.order_transaction(machine=self.machine, qty=float(volume) * 0.98, currency_type=evalueation_coin["market"], side="ask",
                                           price=now_price)
                    time.sleep(int(term) * 60)
                    self.check_ordered_state()
                    logger.info("sell transaction")
                    self.pusher.send_message("#general", "현재" + str(evalueation_coin["market"]) + "매도 하였습니다 info : " + str(evalueation_coin))
                    date.append("현재" + str(evalueation_coin["market"]) + "매도 하였습니다 info : " + str(evalueation_coin))
                    queue.put(date)
                    print("판매 완료")
                    self.free_balance = self.machine.get_free_balance()
                    break
                disparity = float(self.machine.get_disparity(currency_type=evalueation_coin["market"], term=self.term))
                print("매도 시점 기다리는 중")
                time.sleep(int(term) * 60)
                self.check_ordered_state()

if __name__=="main":
    trader = StepTrade()
    trader.run()
