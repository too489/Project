
	package user;

	import java.sql.Connection;
	import java.sql.DriverManager;
	import java.sql.PreparedStatement;
	import java.sql.ResultSet;

	public class UserDAO {

	   private Connection conn;
	   private PreparedStatement pstmt;
	   private ResultSet rs;
	   
	   public UserDAO() {
	      try {
	         String dbURL="jdbc:mysql://localhost:3306/test?serverTimezone=UTC";
	         String dbID="root";
	         String dbPassword="1883"; 
	         Class.forName("com.mysql.jdbc.Driver");
	         conn=DriverManager.getConnection(dbURL,dbID,dbPassword);
	               
	      }catch(Exception e) {
	         e.printStackTrace();
	      }
	   }
	   public int login(String userID,String userPassword) {
	      String SQL="SELECT Pw FROM USER WHERE ID=?";
	      try {
	         pstmt=conn.prepareStatement(SQL);
	         pstmt.setString(1,userID);
	         rs=pstmt.executeQuery();
	         if(rs.next()) {
	            if(rs.getString(1).equals(userPassword))
	               return 1;//����
	            else
	               return 0;//�о����� ����
	         }
	         return -1;//���̵� ����
	      }catch (Exception e) {
	         e.printStackTrace();
	      }
	      return -2;//�����ͺ��̽� ����
	   }
   public int join(User user) {
      String SQL="INSERT INTO USER VALUES (?, ?, ?, ?, ?, ?)";
      try {
    	
         pstmt=conn.prepareStatement(SQL);
         pstmt.setString(1,user.getId());
         pstmt.setString(2,user.getPw());
         pstmt.setString(3,user.getName());
         pstmt.setString(4,user.getEmail());
         pstmt.setString(5,user.getDe_Name());
         pstmt.setInt(6,0);
         pstmt.executeUpdate();
	    
		if(user.getSec1()!=null) {
			 SQL="INSERT INTO Section_Has_Student VALUES (?,?)";
		     pstmt=conn.prepareStatement(SQL);
			  pstmt.setString(1,user.getId());
		      pstmt.setString(2,user.getSec1());
		      pstmt.executeUpdate();
		  }
		if(user.getSec2()!=null) {
			 SQL="INSERT INTO Section_Has_Student VALUES (?,?)";
		     pstmt=conn.prepareStatement(SQL);
			  pstmt.setString(1,user.getId());
		      pstmt.setString(2,user.getSec2());
		      pstmt.executeUpdate();
		  }
		if(user.getSec3()!=null) {
			 SQL="INSERT INTO Section_Has_Student VALUES (?,?)";
		     pstmt=conn.prepareStatement(SQL);
			  pstmt.setString(1,user.getId());
		      pstmt.setString(2,user.getSec3());
		      pstmt.executeUpdate();
		  }
		if(user.getSec4()!=null) {
			 SQL="INSERT INTO Section_Has_Student VALUES (?,?)";
		     pstmt=conn.prepareStatement(SQL);
			  pstmt.setString(1,user.getId());
		      pstmt.setString(2,user.getSec4());
		      pstmt.executeUpdate();
		  }
	    return 1;
	      }catch(Exception e) {
	         e.printStackTrace();
	         System.out.println("��������");
	      }
	      return -1;
	   }
   
   
}