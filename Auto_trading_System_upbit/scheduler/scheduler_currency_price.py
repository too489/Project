import configparser
from celery import Celery, Task
from db.mongodb import mongodb_handler
from datetime import datetime
import time
from machine.upbit_machine import UpbitMachine

app=Celery('currency_info', backend='redis://localhost:6379/0',broker ='redis://localhost:6379/0')

app.conf.beat_schedule={
    'add-every-1-min':{
        'task':'scheduler.scheduler_currency_price.get_currency_info',
        'schedule':60.0,
        'args':(),
    }
}

@app.task
def get_currency_info():
    upbit=UpbitMachine()
    currency_type=["KRW-BTC","KRW-ETH","KRW-EOS","KRW-XRP","KRW-TRX","KRW-NEO"]
    for item in currency_type:
        result=upbit.get_filled_orders(currency_type=item)
        mongodb = mongodb_handler.MongoDBHandler("local", "coiner", "price_info")

        d = datetime.fromtimestamp(result["timestamp"]/1000)
        result["year"] = d.year
        result["month"] = d.month
        result["day"] = d.day
        result["hour"] = d.hour
        result["minute"] = d.minute
        result["second"] = d.second
        result["amount"] = float(item["trade_volume"])
        result["timestamp"] = item["timestamp"]/1000
        result["disparity"] = upbit.get_disparity(currency_type=item)
        result.pop("sequential_id")
        ids = mongodb.insert_items(result)
        print(ids)
    # result_btc = upbit.get_filled_orders(currency_type="KRW-BTC")
    # result_eth = upbit.get_filled_orders(currency_type="KRW-ETH")
    # result_eos = upbit.get_filled_orders(currency_type="KRW-EOS")
    # result_xrp = upbit.get_filled_orders(currency_type="KRW-XRP")
    # result_trx = upbit.get_filled_orders(currency_type="KRW-TRX")
    # result_neo = upbit.get_filled_orders(currency_type="KRW-NEO")
    # mongodb = mongodb_handler.MongoDBHandler("local", "coiner", "price_info")
    # result_list= result_btc + result_eth + result_eos + result_xrp + result_trx + result_neo
    # if len(result_list) != 0 :
    #     for item in result_list:
    #         d = datetime.fromtimestamp(item["timestamp"]/1000)
    #         item["year"] = d.year
    #         item["month"] = d.month
    #         item["day"] = d.day
    #         item["hour"] = d.hour
    #         item["minute"] = d.minute
    #         item["second"] = d.second
    #         item["amount"] = float(item["trade_volume"])
    #         item["timestamp"] = item["timestamp"]/1000
    #         item.pop("sequential_id")
    #     ids = mongodb.insert_items(result_list)
    #     print(ids)
