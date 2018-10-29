import unittest, inspect
from db.mongodb.mongodb_handler import MongoDBHandler


class MongoDBHandlerTestCase(unittest.TestCase):
    def setUp(self):
        self.mongodb = MongoDBHandler("local", "coiner", "price_info")
        self.mongodb.delete_items({})
        docs=[
            {"currency": "btc", "price": 10000},
            {"currency": "eth", "price": 1000},
            {"currency": "xrp", "price": 100},
            {"currency": "btc", "price": 20000},
            {"currency": "eth", "price": 2000},
            {"currency": "xrp", "price": 200},
        ]
        self.mongodb.insert_items(docs)

    def tearDown(self):
        pass

    def test_set_db_collection(self):
        """
        test set_db
        """

        self.mongodb.set_db_collection("trader", "trade_status")

    def test_get_db_name(self):

        dbname = self.mongodb.get_current_db_name()
        self.assertEqual(dbname, "coin")

    def test_get_collection_name(self):

        collection_name= self.mongodb.get_current_collection_name()
        self.assertEqual(collection_name, "price_info")

    def test_insert_item(self):

        doc = {"item": "item0", "name": "test_insert_item"}
        id = self.mongodb.insert_item(doc)
        assert id
        print(id)

    def test_insert_items(self):

        docs=[
            {"item": "item1", "name": "test_insert_items"},
            {"item": "item2", "name": "test_insert_items"},
        ]
        ids=self.mongodb.insert_items(docs)
        assert ids
        print(ids)

    def test_find_item(self):

        doc = self.mongodb.find_item({"currency":"btc"})
        print(doc)

    def test_find_items(self):

        cursor = self.mongodb.find_item({"currency":"eth"})
        assert cursor
        for doc in cursor:
            print(doc)

    def test_delete_items(self):

        result = self.mongodb.delete_items({"currency":"xrp"})
        assert result
        print(result.deleted_count)

    def test_update_items(self):

        result = self.mongodb.update_items({"currency":"xrp"},{"$set":{"price":300}})
        assert result
        print("matched_count:"+str(result.matched_count))
        print("modified_count:"+str(result.modified_count))

    def test_aggregate(self):
        print(inspect.stack()[0][3])
        pipeline = [
            {"$match": {"currency": "btc"}},
            {"$group": {"_id":"$currency",
                        "min_val":{"$min":"$price"},
                        "max_val":{"$max":"$price"},
                        "sum_val":{"$sum":"$price"},
                        }
            }
        ]
        result = self.mongodb.aggregate(pipeline)
        assert result
        for item in result:
            print(item)


if __name__ == "__main__":
    unittest.main()