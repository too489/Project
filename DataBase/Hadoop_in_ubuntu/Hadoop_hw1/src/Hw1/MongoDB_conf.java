package Hw1;

import java.util.ArrayList;

import org.apache.hadoop.io.Text;
import org.bson.Document;

import com.mongodb.BasicDBObject;
import com.mongodb.MongoClient;
import com.mongodb.MongoClientURI;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;

public class MongoDB_conf {
	public MongoDB_conf(String k, ArrayList list) {
		MongoClient mongoClient = new MongoClient(new MongoClientURI("mongodb://root:1883@localhost"));
		MongoDatabase db= mongoClient.getDatabase("Hw1");
		MongoCollection<Document> documentMongoCollection = db.getCollection("save");
		Document document = new Document(k,list.toString());
		documentMongoCollection.insertOne(document);
	}



}
