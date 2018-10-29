from slacker import Slacker
from pusher.base_pusher import Pusher
import configparser


class PushSlack(Pusher):
    def __init__(self):
        """
        슬랙으로 메시지를 보내기 위한 PushSlack의 __init__메서드
        config.ini 파일로부터 토큰값을 읽어 들여 Slacker 객체를 생성합니다.
        """
        config = configparser.ConfigParser()
        config.read('conf/config.ini')
        token = config['SLACK']['token']
        self.slack = Slacker(token)

    def send_message(self, thread="#general", message=None):
        """
            슬랙의 토큰값에 해당하는 그룹의 thread에 해당하는 채널에 메시지를 전송
            Args:
                thread(str): 슬랙의 채널명
                message(str): 채널로 보낼 메시지
        """
        self.slack.chat.post_message(thread, message)
