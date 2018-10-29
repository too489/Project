import pprint

import tensorflow as tf
import numpy as np
import pandas as pd
import datetime
import matplotlib.pyplot as plt

from machine.upbit_machine import UpbitMachine

def tensorflow_algorithm(currency_type=None,term=10,count=500,view=None):
    tf.set_random_seed(1000)
    tf.reset_default_graph()
    input_data_cnt = 5 # 입력데이터의 컬럼갯수 , 변수
    output_data_cnt = 1# 출력데이터의 컬럼갯수

    seq_length = 30 #1개의 시퀀스길이
    rnn_cell_hidden_dim = 20 #각 셀의 (hidden)출력 크기
    forget_bias = 1.0 # 막각편향(기본값 1.0)
    num_stacked_layers = 1 #stacked LSTM layers 갯수
    keep_prob = 1.0 #drop out 할 때 저장할 비율
    epoch_num = 1000 # 데이터를 몇번 반복해서 학습할 것인가 입력
    leaning_rate = 0.01 # 학습률

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

    def lstm_cell():
        cell=tf.contrib.rnn.LSTMCell(num_units = 20, forget_bias = 1.0, state_is_tuple= True, activation = tf.nn.tanh)

        return cell

    # def get_prediction_value(self,prediction_value=prediction_value):
    #     return prediction_value

    upbit = UpbitMachine() #machine 변수선언

    result = upbit.get_candles_data(currency_type=currency_type,term=term,count =count) # 5분간격으로 과거데이터 총 200개 호출
    #print(result)
    data=[] #입력데이터 저장
    data.append(["open","high","low","price","volume"]) #저장 데이터 순서

    for item in result :
        list=[]
        list.append(item["opening_price"])#시장가 추가
        list.append(item["high_price"])#최고가 추가
        list.append(item["low_price"])# 최저가 추가
        list.append(item["trade_price"])# 최종거래 금액
        list.append(item["candle_acc_trade_volume"])# 거래된 양
        data.append(list)

    data=np.array(data[1:]).astype(np.float64)# data를 astype 으로 float64로 변환
    data = np.flip(data, 0)# 최신순에서 과건순으로 변경
    price=data[:, :-1] #price 라는 변수로 거래량만 제외한 변수 추가
    norm_price=nomalization(price) #price를 정규화
    #pprint.pprint(price.dtype)
   # pprint.pprint(price)
    #pprint.pprint(norm_price)

    volume=data[:,-1:]#거래량만 추가
    norm_volume=nomalization(volume)# 거래량을 정규화
   # pprint.pprint(norm_volume)

    x=np.concatenate((norm_price, norm_volume), axis=1)# 정규화된 가격과 거래량을 합침
   # print("x.shape:", x.shape)
    #print("x[0]: " , x[0])

    y = x[:,[-2]] # 최종거래가 저장

    dataX = []#입력데이터 변수지정
    dataY = []#출력데이터 변수지정
    for i in range(0, len(y)-seq_length):
        _x = x[i : i + seq_length]#i번째부터 i+seq_length-1까지 _x에 저장
        _y = y[i + seq_length]#i+seq_length를 출력 한마디로 시퀀스의 바로 다음값으로서 예측한 값이 맞냐 아니냐를 따지는 값
        # if i is 0:
        #     print(_x, "->", _y)#첫번째 행만 테스트 하기 위해 출력
        dataX.append(_x)
        dataY.append(_y)
    train_size = int(len(dataY) * 0.7)#데이터의 70%만 트레이닝
    test_size = int(len(dataY) - train_size)#데이터의 70%를 제외한 부분을 테스트 케이스로 출력
    trainX = np.array(dataX[0:train_size])#train 배열 설정
    trainY = np.array(dataY[0:train_size])#train 결과값 설정

    testX = np.array(dataX[train_size:len(dataX)])#test case 배열 설정
    testY = np.array(dataY[train_size:len(dataY)])#test case 결과값 설정
    X = tf.placeholder(tf.float32, [ None, seq_length, input_data_cnt])#placeholder설정
    Y = tf.placeholder(tf.float32, [None, 1])#placeholder설정

    targets = tf.placeholder(tf.float32, [None, 1])#검증용 지표를 계산 placeholder 지정
    predictions = tf.placeholder(tf.float32, [None, 1])

    for a in range(num_stacked_layers):
        stackedRnns=[lstm_cell()]
    #num_stacked_layers층으로 쌓인 Rnns 생성
    multi_cells = tf.contrib.rnn.MultiRNNCell(stackedRnns,state_is_tuple =True) if num_stacked_layers > 1 else lstm_cell()
    #Rnn 생성
    #Rnn층이 0이면 lstm_cell로실행
    # 왜 c++에서처럼 if 문을 주면 오류가 나지?

    prediction_value, _states= tf.nn.dynamic_rnn(multi_cells, X , dtype = tf.float32)
    # dynamic_rnn은 결과값과 상태를 나타내는 값을 return
    # 반복적인 Neural Network생성

    prediction_value = tf.contrib.layers.fully_connected(prediction_value[:,-1], output_data_cnt,activation_fn=tf.sigmoid)
    #가중치를 더한값을 precition_value로 지정

    loss = tf.reduce_sum(tf.square(prediction_value - Y))
    # 손실값 예상값- 실제값의 제곱을 더한값으로 지정
    optimizer = tf.train.AdamOptimizer(leaning_rate)
    # leaning_rate를 지정하여 최적화를 진행 Adam Algorithm을 이용
    train=optimizer.minimize(loss)#
    #손실값의 gradient를 계산한하여 train에 투입
    rmse = tf.sqrt(tf.reduce_mean(tf.squared_difference(targets, predictions)))
    #합성곱 평균을내어 train 값에 또 다시 제곱근을 한 값을 집어 넣어 return

    train_error_summary = []#train_error라는 배열을 지정하여 오류값 저장
    test_error_summary = []#test_error라는 값을 지정하여 오류값 저장
    test_predict = ''# 테스트 예측값 저장용

    sess = tf.Session()
    sess.run(tf.global_variables_initializer())


    start_time = datetime.datetime.now()# 시작시간을 저장

    for epoch in range(epoch_num):
        #epoch를 이용하여 몇번에 걸쳐 train할것인가를 저장후 epoch값을 저장
        _,_loss=sess.run([train,loss], feed_dict={X:trainX, Y:trainY})
        #x,y의 두개의 예측값을 저장함
        if ((epoch+1)%50 == 0) or (epoch_num-1):
            #값을 다 저장할순 없고 중간중간에 값을 저장하는 if문 생성
            train_predict = sess.run(prediction_value, feed_dict = {X : trainX})
            #예상값을 지정
            train_error = sess.run(rmse,feed_dict = {targets: trainY, predictions: train_predict})
            #만약 그 예측값이 빗나 갔다면 그에 대한 error값을 배열에 저장
            train_error_summary.append(train_error)
            #만약 예측값이 빗나갔으면 빗나간것을 저장

            test_predict = sess.run(prediction_value, feed_dict = {X: testX})
            # test case에서의 예측 값을 저장
            test_error = sess.run(rmse, feed_dict={targets: testY, predictions: test_predict})
            #test case에서의 오류값을 저장
            test_error_summary.append(test_error)
            # print("epoch : {}, train_error(A) :{} , test_error(B):{}, B-A :{}".format(epoch+1, train_error, test_error, test_error-train_error))
    test_predict = reverse_nomalization(price, test_predict)
    if view is None :
        pass
    else:
        end_time=datetime.datetime.now()# 종료 시간 지정
        elapsed_time = end_time - start_time #종료된 시간과 시작시간을 비교하여 elapsed_time을 구함
        print("elapsed_time : ", elapsed_time)
        print("elapsed_time per epoch:", elapsed_time/epoch_num)
        plt.figure("epoch")#도표 1로지정
        plt.plot(train_error_summary, 'g',label="train_error")# train_error값을 green으로 지정
        plt.plot(test_error_summary,'b',label="test_error")#test_error_summary값을 파란색으로 지정
        plt.xlabel("Epoch(x1000)")#x 축의 값에는Epoch x1000이라는 값을 지정
        plt.ylabel("Error Percentage") #오류가 날 확률을 지정

        plt.figure("price") #도표 2로 지정
        testY=reverse_nomalization(price, testY)
        plt.plot(testY, 'r', label="Actual_value") # 실제 값들을 red 로 지정
        plt.plot(test_predict, "b",label="Predict_value") # 예측값들을 파란색으로 지정
        plt.legend(loc=2)
        plt.xlabel("Time") #X축에는 시간을
        plt.ylabel("coin price")# Y축에는 코인값을
        plt.show() #도표를 출력


    np.array([x[len(x) - seq_length:]])

    #역 정규화를 통해 값을 출력 저장
    #과연?
    print("실제값 길이 " + str(len(testY)))
    print("coin name : "+ currency_type)
    print("next_time coin price ", test_predict[0])
    result=test_predict[0]
    result=str(result[0])
    return result
    #최종결과 5분이나 1분봉보다는 30분봉이나 60분봉이 더 좋은 결과를 가져온다는 것을 알 수 있다
    #하지만 가상화폐라는 것이 그 어렵다는 주가_예측보다는 더 외부 영향을 많이 받는 종목이다보니 이 값을 확신할순 없다
    #여기다 sns 에서 부정적인 단어나 긍정적인 단어를 크롤링하여 값에 영향을 주는 값으로 추가하는것은 어떨까?
