import numpy as np
import pandas as pd
from pandas import Series

from db.mongodb import mongodb_handler
import statsmodels.tsa.stattools as ts

from machine.upbit_machine import UpbitMachine

def MeanReversionModel(term=None):

    def calcADF(data):
        """
            공적분 관계인지에 관해 테스트
        :param data:들어오는 데이터 set
        :return:각자의 결과값
        """
        ADF_result = ts.adfuller(data)
        Evaluation_values=ADF_result[4]

        return ADF_result[0], Evaluation_values["1%"], Evaluation_values["5%"], Evaluation_values["10%"]


    def calHurstExponent(data,lags_count=100): #위아래 일정적으로 움직이는가 아니면 정말 랜덤워크인가
        lags =range(2, lags_count)
        ts = np.log(data)
        tau = [np.sqrt(np.std(np.subtract(ts[lag:], ts[:-lag]))) for lag in lags]
        poly = np.polyfit(np.log(lags),np.log(tau),1)
        result = poly[0]*2.0
        return result

    def calcHalfLife(data): # 평균으로 다시 돌아오는 속도를 나타낸다
        price=pd.Series(data)
        lagged_price = price.shift(1).fillna(method = "bfill")
        delta = price - lagged_price
        beta = np.polyfit(lagged_price, delta , 1)[0]
        half_life = (-1*np.log(2)/beta)
        return half_life

    def assessADF(test_stat, adf_1, adf_5, adf_10):# 평가기준 검정통계량값이 1%5%10%보다 어느하나라도 높아야 평균회귀모델로 취급할수있음
        if test_stat < adf_10:
            return 3
        elif test_stat < adf_5:
            return 2
        elif test_stat < adf_1:
            return 1
        return 0

    def assessHurst(hurst):#허스트 지수값이 0.5보다 아래이면 평균회귀 05보다 높으면 추세성향 그러니깐 한쪾으로 움직인다
        if hurst > 0.4:
            return 0
        if hurst < 0.1:
            return 3
        elif hurst < 0.2:
            return 2
        return 1

    def assessHalflife(percentile, halflife): #평균으로 회귀하는 속도를 나타낸다 한마디로 변동이 잦냐 아니냐를 평가하는기준이됨
        for index in range(len(percentile)):
            if halflife <= percentile[index]:
                if index < 2:
                    return 3
                elif index < 3:
                    return 2
                elif index < 4:
                    return 1
        return 0

    def getPercentileIndex(percentile_arr, value):
        for index in range(len(percentile_arr)):
            if value <= percentile_arr[index]:
                return index
        return len(percentile_arr)

    def Search_Coin(term=10,count=500):#평균 5분봉으로 500개정도를 뽑아서 테스트로 사용 하지만 실제사용에선 30분 주기로 할것임
        upbit = UpbitMachine()  # machine 변수선언
        test_result={'index':[], 'coin':[],'adf_statistic':[],'adf_1':[],'adf_5':[],'adf_10':[],'hurst':[],'halflife':[]}
        index=0
        for coin in upbit.currency_type:#타입에 있는 모든 코인 조회
            result = upbit.get_candles_data(currency_type=coin, term=term, count=count)  # 5분간격으로 과거데이터 총 200개 호출
            # print(count)
            # print(coin)
            # print(term)

            data = []  # 입력데이터 저장

            for item in result:
                data.append(item["trade_price"])  # 최종거래 금액
            test_result['index']=index
            test_result['coin'].append(coin)
            test_result['hurst'].append(calHurstExponent(data))
            test_result['halflife'].append(calcHalfLife(data))
            test_stat,adf_1,adf_5,adf_10=calcADF(data)
            test_result['adf_statistic'].append(test_stat)
            test_result['adf_1'].append(adf_1)
            test_result['adf_5'].append(adf_5)
            test_result['adf_10'].append(adf_10)
            index+=1
        df_result= pd.DataFrame(test_result)

        df_result['rank_adf']=0
        df_result['rank_hurst']=0
        df_result['rank_halflife']=0
        halflife_percentile = np.percentile(df_result['halflife'],np.arange(0, 100, 10))
        for row_index in  range(df_result.shape[0]):
            df_result.loc[row_index, 'rank_adf'] = assessADF(df_result.loc[row_index, 'adf_statistic'],df_result.loc[row_index, 'adf_1'], df_result.loc[row_index, 'adf_5'], df_result.loc[row_index, 'adf_10'])
            df_result.loc[row_index, 'rank_hurst'] = assessHurst(df_result.loc[row_index, 'hurst'])
            df_result.loc[row_index, 'rank_halflife'] = assessHalflife(halflife_percentile, df_result.loc[row_index, 'halflife'])
            df_result['rank'] = df_result['rank_adf'] + df_result['rank_hurst'] + df_result['rank_halflife']
#        print(df_result['coin'])
        ratio=0.8
        percentile_column = np.percentile(df_result['rank'], np.arange(0, 100, 10))
        ratio_index = np.trunc(ratio * len(percentile_column))
        result = {}
        result_list=[]
        for row_index in range(df_result.shape[0]):
            percentile_index = getPercentileIndex(percentile_column, df_result.loc[row_index, 'rank'])
            if percentile_index >= ratio_index:
                result[df_result.loc[row_index, 'index']] = df_result.loc[row_index, 'coin']
                result_list.append(df_result.loc[row_index,'coin'])
        #최종리스트를 데베에 저장
        #print("회귀분석 내",result_list)
        return result_list
    return Search_Coin(term=term)

