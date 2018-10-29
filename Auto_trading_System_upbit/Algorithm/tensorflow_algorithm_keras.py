import pprint

import tensorflow as tf
import numpy as np
import pandas as pd
import datetime
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from machine.upbit_machine import UpbitMachine
import matplotlib.pyplot as plt

def tensorflow_algorithm_keras(currency_type=None,term=10,count=500,view=None):
    look_back=1
    tf.set_random_seed(1000)
    tf.reset_default_graph()


    def data_standardization(data):
        # 표준화 진행
        # return : (값-평균)/정규화값

        data_np= np.asarray(data)
        #배열로 변환

        return (data_np-data_np.mean())/data_np.std()

    def nomalization(data):
        # 정규화를 진행하여 너무 크거나 작은값을 방지
        # return (값-최소값)/(최대값-최소값)

        data_np = np.asarray(data)
        # 배열로

        return (data_np - data_np.min())/(data_np.max() - data_np.min() + 1e-10)
        #0으로 나누는것방지


    def reverse_nomalization(org_data, data):
        # 정규화 값을 원래대로 돌림
        # return (정규화된 값 * (원래값의 최대값 - 원래값의 최소값)+1e-10))+원래값의 최소값

        org_data_np = np.asarray(org_data)
        data_np = np.asarray(data)
        return (data_np *(org_data_np.max() - org_data_np.min() +1e-10)) + org_data_np.min()

    def create_dataset(dataset, look_back=1):
        dataX, dataY = [], []
        for i in range(len(dataset) - look_back - 1):
            a = dataset[i:(i + look_back)]
            dataX.append(a)
            dataY.append(dataset[i + look_back])
        return np.array(dataX), np.array(dataY)

    # def get_prediction_value(self,prediction_value=prediction_value):
    #     return prediction_value

    upbit = UpbitMachine() #machine 변수선언

    result = upbit.get_candles_data(currency_type=currency_type,term=term,count =count) # 5분간격으로 과거데이터 총 200개 호출
    #print(result)
    data=[] #입력데이터 저장
    for item in result :#최근순서
        data.append(item["trade_price"]
                    )# 최종거래 금액
    data = np.array(data).astype(np.float64)
    nptf=nomalization(data)
    # data = np.flip(data, 0)# 최신순에서 과건순으로 변경
    # price=data[:,-2:-1] #price 라는 변수로 거래량만 제외한 변수 추가
    #
    # norm_price=nomalization(price) #price를 정규화 가격만
    #
    # #사이즈 나눔
    train_size=int(len(nptf)*0.7)
    test_size=len(nptf)-train_size
    train, test = nptf[0:train_size], nptf[train_size:len(nptf)]
    #
    trainX, trainY=create_dataset(train)
    testX,testY=create_dataset(test)
    #
    trainX=np.reshape(trainX,(trainX.shape[0],1,trainX.shape[1]))
    testX=np.reshape(testX,(testX.shape[0],1,testX.shape[1]))
    #
    model=Sequential()
    model.add(LSTM(4,input_shape=(1,look_back)))#tanh 를사용
    model.add(Dense(1))
    model.compile(loss='mean_squared_error', optimizer='adam')
    model.fit(trainX,trainY, epochs=100,batch_size=1,verbose=2)


    testPredict=model.predict(testX)
    testPredict=reverse_nomalization(org_data=data,data=testPredict)
    testY=reverse_nomalization(org_data=data,data=testY)
    #testScore=math.sqrt(mean_squared_error(testY, testPredict))
    #print('Train Score: %.2f RMSE' % testScore)


    lastX=nptf[-1]
    lastX=np.reshape(lastX,(1,1,1))
    lastY=model.predict(lastX)
    lastY=reverse_nomalization(org_data=data,data=lastY)
    # print(testY)
    # print(testPredict)
    if view is None :
        pass
    else:
        plt.xlabel("Time") #X축에는 시간을
        plt.ylabel("coin price")# Y축에는 코인값을
        plt.plot(testY, 'r', label="Actual_value") # 실제 값들을 red 로 지정
        plt.plot(testPredict, "b",label="Predict_value") # 예측값들을 파란색으로 지정
        plt.legend(loc=2)
        plt.show()
        print("실제값 길이 " +str(len(testY)))
        print("coin name : "+ currency_type)
        print("next_time coin price ", lastY)
    return lastY[0][0]
