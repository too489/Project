from pymongo import MongoClient
from pymongo.cursor import CursorType
import configparser
from db.base_handler import DBHandler


class MongoDBHandler(DBHandler):
    
    def __init__(self, mode="local", db_name=None, collection_name=None):
        """
        MongoDBHandler __init__ 구현부

        Args:
            mode(str):로컬 DB인지 리모트 DB인지 구분합니다. 예) "local","remote"
            db_name(str):MongoDB에서 데이터베이스에 해당하는 이름을 받습니다.
            collection_name(str):데이터베이스에 속하는 콜렉션 이름을 받습니다.

        Returns:
            None

        Raises:
            db_name과 collection_name이 없으면 Exception을 발생시킵니다.
        """
        if db_name is None or collection_name is None:
            raise Exception("Need to db name and collection name")
        config = configparser.ConfigParser()
        config.read('conf/config.ini')
        self.db_config={}
        self.db_config["local_ip"]=config["MONGODB"]["local_ip"]
        self.db_config["port"] = config["MONGODB"]["port"]
        self.db_config["remote_host"] = config["MONGODB"]["remote_host"]
        self.db_config["remote_port"] = config["MONGODB"]["remote_port"]
        self.db_config["user"] = config["MONGODB"]["user"]
        self.db_config["password"] = config["MONGODB"]["password"]

        if mode == "remote":
            self._client = MongoClient("mongodb://{user}:{password}@{remote_host}:{port}".format(**self.db_config),maxPoolSize=200)
        elif mode == "local":
            self._client = MongoClient("mongodb://{user}:{password}@{local_ip}:{port}".format(**self.db_config),maxPoolSize=200)

        self._db = self._client[db_name]
        self._collection = self._db[collection_name]

    def set_db_collection(self, db_name=None, collection_name=None):
        """
        MongoDB에서 작업하려는 데이터베이스와 콜렉션을 변경할 떄 사용합니다.

        Args:
            db_name(str):MongoDB에서 데이터베이스에 해당하는 이름을 받습니다.
            Collection_name(str): 데이터베이스에 속하는 콜렉션 이름을 받습니다.

        Returns:
            None

        Raises:
        db_name이 없으면 Exception을 발생시킵니다.

        """

        if db_name is None:
            raise Exception("Need to dbname name")

        self._db = self._client[db_name]
        if collection_name is not None:
            self._collection = self._db[collection_name]

    def get_current_db_name(self):
        """
        현재 MongoDB에서 작업 중인 데이터베이스의 이름을 반환합니다.

        Returns:
             self._db.name: 현재 사용 중인 데이터베이스 이름을 반환
        """
        return self._db.name

    def get_current_collection_name(self):
        """
        현재 MongoDB에서 작업 중인 콜렉션의 이름을 반환합니다.

        Returns:
        self._collection.name : 현재 사용 중인 콜렉션 이름을 반환
        """
        return self._collection.name

    def insert_item(self, data, db_name=None,collection_name=None):
        """
        MongoDB에 하나의 문서를 입력하기 위한 메서드입니다.

        Args:
            db_name(str): MongoDB에서 데이터베이스에 해당하는 이름을 받습니다.
            collection_name(str):데이터베이스에 속하는 콜렉션 이름을 받습니다.
        Returns:
            inserted_id: 입력 완료된 문서의 ObjectId를 반환합니다.

        """
        if db_name is not None:
            self._db=self._client[db_name]
        if collection_name is not None:
            self._collection= self._db[collection_name]

        return self._collection.insert_one(data).inserted_id

    def insert_items(self, datas, db_name=None, collection_name=None):
        """
        MongoDB에 다수의 문서를 입력하기 위한 메서드입니다.

        Args:
            db_name(str): MongoDB에서 데이터베이스에 해당하는 이름을 받습니다.
            collection_name(str): 데이터베이스에 속하는 콜렉션 이름을 받습니다.

        Returns:
            inserted_ids :입력 완료된 문서의 ObjectId 리스트를 반환합니다.
        """
        if db_name is not None:
            self._db=self._client[db_name]
        if collection_name is not None:
            self.collection_name = self._db[collection_name]
        return self._collection.insert_many(datas).inserted_ids

    def find_items(self,condition=None, db_name=None, collection_name=None):
        """
        MongoDB에서 다수의 문서를 검색하기 위한 메서드입니다.

        Args:
            condition(dict):검색 조건을 딕셔너리 형태로 받습니다.
            db_name(str):MongoDB에서 데이터베이스에 해당하는 이름을 받습니다.
            collection_name(str):데이터베이스에 속하는 콜렉션 이름을 받습니다.

        Returns:
            Cursor : 커서를 반환합니다.
        """

        if condition is None:
            condition={}
        if db_name is not None:
            self._db= self._client[db_name]
        if collection_name is not None:
            self._collection= self._db[collection_name]
        return self._collection.find(condition, no_cursor_timeout= True, cursor_type= CursorType.EXHAUST)

    def find_item(self,condition=None, db_name=None, collection_name=None):
        """
        MongoDB에서 하나의 문서를 검색하기 위한 메서드입니다.

        Args:
             condition(dict) : 검색 조건을 딕셔너리 형태로 받습니다.
             db_name(str) : MongoDB에서 데이터베이스에 해당하는 이름을 받습니다.
             collection_name(str):데이터베이스에 속하는 콜렉션 이름을 받습니다.

        Returns:
            document: 만약 검색된 문서가 있으면 문서의 내용을 반환합니다.
        """
        if condition is None:
            condition = {}
        if db_name is not None:
            self._db = self._client[db_name]
        if collection_name is not None:
            self._collection = self._db[collection_name]
        return self._collection.find_one(condition)

    def delete_items(self, condition=None, db=None, collection=None):
        """
        MongoDB에서 다수의 문서를 삭제하는 메서드입니다.

        Args:
             condition(dict): 삭제 조건을 딕셔너리 형태로 받습니다.
             db_name(str):MongoDB에서 데이터베이스에 해당하는 이름을 받습니다.
             collection_name(str):데이터베이스에 속하는 콜렉션 이름을 받습니다.

        Returns:
            DeleteResult : PyMongo의 문서의 삭제 결과 객체인 DeleteResult가 반환됩니다.

        """
        if condition is None:
            raise Exception("Need to condition")
        if db is not None:
            self._db= self._client[db]
        if collection is not None:
            self._collection= self._db[collection]
        return self._collection.delete_many(condition)

    def update_items(self,condition=None, update_value=None, db_name=None, collection_name=None):
        """
        MongoDB에서 다수의 문서를 갱신하기 위한 메서드입니다

        Args:
             condition(dict): 업데이트 조건을 딕셔너리 형태로 받습니다.
             update_value(dict): 업데이트 하고자 하는 값을 딕셔너리 형태로 받습니다.
             db_name(str):MongoDB에서 데이터베이스에 해당하는 이름을 받습니다.
             collection_name(str):데이터베이스에 속하는 콜렉션 이름을 받습니다.

        Returns:
            UpdateResult: PyMongo의 문서의 업데이트 결과 객체인 UpdateResult가 반환됩니다.
        """
        if condition is None:
            raise Exception("Need to condition")
        if update_value is None:
            raise Exception("Need to update value")
        if db_name is not None:
            self._db = self._client[db_name]
        if collection_name is not None:
            self._collection = self._db[collection_name]
        return self._collection.update_many(filter=condition, update=update_value)

    def aggregate(self, pipeline=None, db_name=None, collection_name=None):
        """
        MongoDB의 집계 작업을 위한 메서드입니다.

        Args:
            pipeline(dict): 갱신 조건을 딕셔너리 형태로 받습니다.
            db_name(str): MongoDB에서 데이터베이스에 해당하는 이름을 받습니다.
            collection_name(str): 데이터베이스에 속하는 콜렉션 이름을 받습니다.

        Returns:
            CommandCursor: PyMongo의 CommandCursor를 반환합니다.

        """

        if pipeline is None:
            raise Exception("Need to pipeline")
        if db_name is not None:
            self._db = self._client[db_name]
        if collection_name is not None:
            self._collection = self._db[collection_name]
        return self._collection.aggregate(pipeline)