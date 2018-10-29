import unittest
from pusher.slack import PushSlack


class TestSlacker(unittest.TestCase):
    def setUp(self):
        self.pusher = PushSlack()

    def test_send_message(self):
        self.pusher.send_message("#general", "This is the 테스트 msg")

    def tearDown(self):
        pass


if __name__ == "__main__":
    unittest.main()