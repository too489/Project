import pprint
from abc import ABC, abstractmethod
from datetime import datetime
from logger import get_logger
from db.mongodb.mongodb_handler import MongoDBHandler

logger = get_logger("base_strategy")


class Strategy(ABC):
    @abstractmethod
    def run(self):
        pass
    def my_all_assets(self, machine=None,):
        """ 매수매도 주문의 데이터베이스로 저장을 담당
        Args:
             machine(obj): 매수주문하려는 거래소 모듈 객체
             db_handler(obj): 매수주문 정보를 입력할 데이터베이스 모듈 객체
             currency_type(str): 매수주문하려는 화폐종류
             item(dict): 매수 완료 후 데이터베이스에 저장하려는 데이터
             order_type(str):매수방법

        Returns:
            OrderId(str): 매수주문 완료 후의 주문 id

        """
        db_handler = MongoDBHandler(db_name="trader", collection_name="trade_status")
        db_handler.set_db_collection("trader", "assets")
        result = machine.get_All_balance()

        db_handler.insert_item({"time": datetime.now(),
                                    "asset": result,
                                    })

        logger.info(str(datetime.now())+ "자산 : "+ str(result))
        return result



    def order_transaction(self, machine=None,  currency_type=None, price=None ,side=None,order_type="limit",qty=None):
        """ 매수매도 주문의 데이터베이스로 저장을 담당
        Args:
             machine(obj): 매수주문하려는 거래소 모듈 객체
             db_handler(obj): 매수주문 정보를 입력할 데이터베이스 모듈 객체
             currency_type(str): 매수주문하려는 화폐종류
             item(dict): 매수 완료 후 데이터베이스에 저장하려는 데이터
             order_type(str):매수방법

        Returns:
            OrderId(str): 매수주문 완료 후의 주문 id

        """
        if currency_type is None:
            raise Exception("Need to param")
        db_handler = MongoDBHandler(db_name="trader", collection_name="trade_status")
        db_handler.set_db_collection("trader", "trade_status")
        result = machine.order(currency_type=currency_type,
                                   price=price,
                                   qty=qty,  # str(self.BUY_COUNT),
                                   ord_type=order_type,
                                    side=side)
        if (result["state"] == "wait") or (result["state"] == "done"):
            self.db_handler.insert_item({"state": str(result["state"]),
                                    "market": currency_type,
                                    "uuid": str(result["uuid"]),
                                    "volume": float(result["volume"]),
                                    "side": str(result["side"]),
                                    "buy_order_time": str(datetime.now()),
                                    "trade_value": str(result["price"]),
                                    "fee":float(result["paid_fee"]),
                                    })
            self.db_handler.set_db_collection("trader", side)
        if (result["state"] == "wait") or (result["state"] == "done"):
            self.db_handler.insert_item({"state": str(result["state"]),
                                    "market": currency_type,
                                    "uuid": str(result["uuid"]),
                                    "volume": float(result["volume"]),
                                    "side": str(result["side"]),
                                    "buy_order_time": str(datetime.now()),
                                    "trade_value": str(result["price"]),
                                    "fee": float(result["paid_fee"]),
                                    })
            return result["uuid"]

        else:
            logger.info(result)

            print("매매에 실패하였습니다")
            return None


    def order_cancel_transaction(self, machine=None, currency_type=None, item=None):
        """취소주문과 함께 데이터베이스에 필요한 데이터를 업데이트 하는 메서드
        Args:
            machine(obj): 취소주문하려는 거래소 모듈 객체
            db_handler(obj):취소주문 정보를 입력할 데이터베이스 모듈 객체
            currency_type(str): 취소주문하려는 화폐 종류
            item(dict): 취소주문에 필요한 데이터

        Returns:
            OrderId(str): 취소 완료 후의 주문 id

        """
        db_handler = MongoDBHandler(db_name="trader", collection_name="trade_status")
        db_handler.set_db_collection("trader", "trade_status")
        if currency_type is None or item is None:
            raise Exception("Need to param")
        result = machine.cancel_order(order_id=item["uuid"])
        if result[0].get(["error"]):
            logger.info(result)
            logger.info("주문 취소에 실패하였습니다")
        else :
            db_handler.update_items({"uuid": item["uuid"]}, {"$set":{"state":"cancel_ORDERED","cancel_order_time":int(datetime.datetime.now().timestamp()), "transaction":"fail"}})
            pprint.pprint(item['uuid'] , item["market"],"주문이 취소되었습니다")
            return item["uuid"]
            logger.info(result)
            logger.info(item)

    def DB_order_list (self,state="wait"):
        db_handler = MongoDBHandler(db_name="trader", collection_name="trade_status")
        db_handler.set_db_collection("trader", "trade_status")

        return db_handler.find_items({"state": state }, db_name="trader", collection_name="trade_status")

    def Hope_List_Insert(self,result=None):
        db_handler = MongoDBHandler(db_name="trader", collection_name="trade_status")
        db_handler.set_db_collection("trader", "wish_list")
        db_handler.insert_item({"market": result,"time":datetime.now()})


    def update_trade_status(self,  item_id=None, value=None):
        """
        현재 상태를 업데이트 하는 메서드
        Args:
             db_handler(obj): 대상 데이터베이스의 모듈 객체
             item_id(dict): 업데이트 조건
             value(dict): 업데이트 하려는 문서의 칼럼과 값
        """
        db_handler = MongoDBHandler(db_name="trader", collection_name="trade_status")
        if  item_id is None or value is None:
            raise Exception("Need to buy value or status")
        db_handler.set_db_collection("trader", "trade_status")
        db_handler.update_items(item_id, {"$set": value})